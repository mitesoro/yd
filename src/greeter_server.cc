#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else

#include "helloworld.grpc.pb.h"

#endif

#if defined(__linux__)
#include <sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#endif

#include<ydApi.h>
#include<ydDataStruct.h>
#include<ydDataType.h>
#include<ydError.h>
#include<ydUtil.h>
#include<yd.h>
#include <thread>
#include <hiredis/hiredis.h>
#include <unordered_set>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
using helloworld::OrderRequest;
using helloworld::OrderReply;
using helloworld::QueryOrderReply;
using helloworld::QueryOrderRequest;

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Logic and data behind the server's behavior.
//定义了一个名为 GreeterServiceImpl 的类，该类继承自 Greeter::Service，并实现了 SayHello 方法：
class GreeterServiceImpl final : public Greeter::Service {
private:
    myYDListener* listener; // 添加成员变量
public:
    // 构造函数，接收 myYDListener 对象作为参数
    // 通过在构造函数声明前添加 explicit 关键字，你告诉编译器只能使用显式构造函数调用来创建 GreeterServiceImpl 对象，而不允许隐式转换。
    explicit GreeterServiceImpl(myYDListener* listener) : listener(listener) {}

//    SayHello 方法接收一个 HelloRequest 对象作为参数，将其中的名字与前缀 "Hello " 进行拼接，并将结果设置到 HelloReply 对象中，最后返回 Status::OK 表示成功。
    Status SayHello(ServerContext *context, const HelloRequest *request,
                    HelloReply *reply) override {
        std::string prefix("Hello ");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }
    // 参数要引用 QueryOrderRequest
    Status QueryOrder(ServerContext *context, const QueryOrderRequest *request,
                      QueryOrderReply *reply) override {
        reply->set_os(listener->qryOrderSys(request->or_()));
        listener->qryOrders();
        return Status::OK;
    }

    Status CancelOrder(ServerContext *context, const QueryOrderRequest *request,
                      QueryOrderReply *reply) override {
        listener->cancelOrder(request->or_(), YD_YOF_Normal);

        return Status::OK;
    }

    Status Order(ServerContext *context, const OrderRequest *request,
                 OrderReply *reply) override {
        Parameters params;
        // 从 gRPC 请求中获取合约参数值
        if (!request->c().empty()) { // 合约
            params["/c"] = request->c();
        }
        if (request->p() > 0.0) { // 价格
            params["/p"] = std::to_string(request->p());
        }
        if (request->v() > 0) { // 数量
            params["/v"] = std::to_string(request->v());
        }
        if (request->order_id() > 0) {
            params["order_id"] = std::to_string(request->order_id());
        }
        if (request->buy()) {
            params["buy"] = "buy";  // 设置 buy 参数
        }
        if (request->open()) {
            params["open"] = "open";  // 设置 open 参数
        }
        if (request->sell()) {
            params["sell"] = "sell";
        }
        if (request->close()) {
            params["close"] = "close";
        }
        if (request->closetoday()) {
            params["closetoday"] = "closetoday";
        }
        if (request->closeyes()) {
            params["closeyes"] = "closeyes";
        }
        if (request->forceclose()) {
            params["forceclose"] = "forceclose";
        }
        if (request->hedge()) {
            params["hedge"] = "hedge";
        }
        if (request->spec()) {
            params["spec"] = "spec";
        }
        if (request->arbi()) {
            params["arbi"] = "arbi";
        }
        if (request->fak()) {
            params["fak"] = "fak";
        }
        if (request->fok()) {
            params["fok"] = "fok";
        }
        bool success;
        int orderRef;
        int errorNo;
        printParams(params);
        std::tie(success, orderRef, errorNo) = listener->putOrder(params);
        reply->set_success(success);
        reply->set_orderref(orderRef);
        reply->set_errorno(errorNo);
        return Status::OK;
    }

    static void printParams(const Parameters& params) {
        for (const auto& pair : params) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};



//定义了一个名为 RunServer 的函数，用于启动 gRPC 服务器：
void RunServer(uint16_t port, myYDListener* listener) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    GreeterServiceImpl service(listener);

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

// 订阅行情
void sub(myYDListener* listener, redisContext* c)
{
    // 在后台执行的任务代码
    std::cout << "Background task is running..." << std::endl;
    // 这里可以添加更多的后台任务逻辑
    std::unordered_set<std::string> subscribed;
    while (true) {
        std::cout << "Background task is running..." << std::endl;
        redisReply* reply = (redisReply*)redisCommand(c, "HGETALL symbol");
        if (reply == NULL) {
            printf("Error: %s\n", c->errstr);
        }
        printf("reply->type: %d\n", reply->type);
        if (reply->type == REDIS_REPLY_ARRAY) {
            printf("reply->elements: %zu\n", reply->elements);
            for (int i = 0; i < reply->elements; i += 2) {
                printf("%s: %s\n", reply->element[i]->str, reply->element[i + 1]->str);
                std::string instrumentID = reply->element[i]->str;
                if (subscribed.find(instrumentID) == subscribed.end()) {
                    listener->sub(instrumentID);
                    subscribed.insert(instrumentID);
                }
            }
            freeReplyObject(reply);
        }
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}

//absl::ParseCommandLine 用于解析命令行参数，absl::GetFlag(FLAGS_port) 获取 --port 参数的值，并将其作为参数传递给 RunServer 函数。
int main(int argc, char **argv) {
    // 创建Redis连接
    // Redis 服务器的主机和端口
    const char* redis_host = "127.0.0.1"; // 根据实际情况修改主机地址
    int redis_port = 6379; // 根据实际情况修改端口
    // Redis 服务器的密码
    const char* redis_password = "123456"; // 设置密码

    // 创建 Redis 连接上下文
    redisContext* context = redisConnect(redis_host, redis_port);

    if (context == NULL || context->err) {
        if (context) {
            std::cerr << "Error: " << context->errstr << std::endl;
            redisFree(context);
        } else {
            std::cerr << "Unable to allocate redis context" << std::endl;
        }
        return 1;
    }

    // 加载yd 运行库
    string userID, pwd, appID, authCode, exchangeID, ydApiFunc, useProtocol, udpTradeIP, udpTradePort;
    read_and_print_user_info("../config_files/user_info.txt", userID, pwd, appID, authCode, exchangeID, ydApiFunc, useProtocol, udpTradePort);
//    getServerIP("../config_files/yd_config.txt", udpTradeIP);
    getServerIP("../config_files/config.txt", udpTradeIP);
    cout << "当前易达API版本号：" << getYDVersion() << endl;
    cout << "当前使用易达功能[basic(基础版) | extended(扩展版)]为：" << ydApiFunc << endl;
    print_yd_config("../config_files/config.txt");
//    print_yd_config("../config_files/yd_config.txt");
    myYDListener * listener = get_plistener(context,ydApiFunc, userID, pwd, appID, authCode, exchangeID, useProtocol, udpTradeIP, udpTradePort);
    // 暂停执行 3 秒钟，等待listener 连接成功
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // 登录
    listener->login();
    // 开启线程订阅行情
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::thread taskThread(sub, listener, context);

    absl::ParseCommandLine(argc, argv);
    RunServer(absl::GetFlag(FLAGS_port), listener);
    std::this_thread::sleep_for(std::chrono::seconds(300));
    redisFree(context);
    return 0;
}
