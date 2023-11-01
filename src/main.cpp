#if defined(__linux__)
#include <sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include<ydApi.h>
#include<ydDataStruct.h>
#include<ydDataType.h>
#include<ydError.h>
#include<ydUtil.h>
#include<yd_info.h>
#include <thread>

#include <hiredis/hiredis.h>

using namespace std;



int main(){
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

    const char* channel = "channel_name";
    const char* json = "{\"key\": \"value\"}";

    // 构建命令参数数组
    const char* argv[3];
    size_t argvlen[3];

    argv[0] = "PUBLISH";
    argvlen[0] = strlen(argv[0]);

    argv[1] = channel;
    argvlen[1] = strlen(channel);

    argv[2] = json;
    argvlen[2] = strlen(json);

    redisReply* reply = (redisReply*)redisCommandArgv(context, 3, argv, argvlen);
    if (reply == NULL) {
        std::cout << "Failed to publish message" << std::endl;
    } else {
        std::cout << "Message published: " << reply->integer << std::endl;
        freeReplyObject(reply);
    }





//    startExample9("../config_files/config.txt","23300021","12345678","fu2401");
    // 暂停执行 3 秒钟，等待listener 连接成功
    std::this_thread::sleep_for(std::chrono::seconds(13));
    redisFree(context);
    return 0;
}