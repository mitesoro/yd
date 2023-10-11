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

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Logic and data behind the server's behavior.
//定义了一个名为 GreeterServiceImpl 的类，该类继承自 Greeter::Service，并实现了 SayHello 方法：
class GreeterServiceImpl final : public Greeter::Service {
//    SayHello 方法接收一个 HelloRequest 对象作为参数，将其中的名字与前缀 "Hello " 进行拼接，并将结果设置到 HelloReply 对象中，最后返回 Status::OK 表示成功。
    Status SayHello(ServerContext *context, const HelloRequest *request,
                    HelloReply *reply) override {
        std::string prefix("Hello ");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }
};

//定义了一个名为 RunServer 的函数，用于启动 gRPC 服务器：
void RunServer(uint16_t port) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    GreeterServiceImpl service;

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

//absl::ParseCommandLine 用于解析命令行参数，absl::GetFlag(FLAGS_port) 获取 --port 参数的值，并将其作为参数传递给 RunServer 函数。
int main(int argc, char **argv) {
    // 加载yd 运行库
    string userID, pwd, appID, authCode, exchangeID, ydApiFunc, useProtocol, udpTradeIP, udpTradePort;
    read_and_print_user_info("../config_files/user_info.txt", userID, pwd, appID, authCode, exchangeID, ydApiFunc, useProtocol, udpTradePort);
    getServerIP("../config_files/yd_config.txt", udpTradeIP);
    cout << "当前易达API版本号：" << getYDVersion() << endl;
    cout << "当前使用易达功能[basic(基础版) | extended(扩展版)]为：" << ydApiFunc << endl;
    print_yd_config("../config_files/yd_config.txt");
    myYDListener * plistener = get_plistener(ydApiFunc, userID, pwd, appID, authCode, exchangeID, useProtocol, udpTradeIP, udpTradePort);
    // 暂停执行 3 秒钟，等待listener 连接成功
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // 登录
    plistener->login();

    absl::ParseCommandLine(argc, argv);
    RunServer(absl::GetFlag(FLAGS_port));
    return 0;
}
