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

    redisReply* reply = (redisReply*)redisCommand(context, "PUBLISH channel_name message");
    if (reply == NULL) {
        printf("Failed to publish message\n");
    } else {
        printf("Message published: %lld\n", reply->integer);
        freeReplyObject(reply);
    }





//    startExample5("../config_files/config.txt","23300021","12345678","fu2401");
    // 暂停执行 3 秒钟，等待listener 连接成功
    std::this_thread::sleep_for(std::chrono::seconds(13));
    redisFree(context);
    return 0;
}