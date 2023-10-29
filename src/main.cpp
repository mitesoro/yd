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

    const char *key = "test";
    const char *value = "1lkjlknlk";
    redisReply *reply = (redisReply *)redisCommand(context, "SET %s %s", key, value);

    if (reply == NULL) {
        printf("设置键值对失败\n");
    } else {
        printf("键值对设置成功\n");
        freeReplyObject(reply);
    }

    // 使用GET命令获取键的值
    redisReply *reply1 = (redisReply *)redisCommand(context, "GET %s", key);

    if (reply1 == NULL) {
        printf("获取键值失败\n");
    } else if (reply1->type == REDIS_REPLY_STRING) {
        printf("键的值为: %s\n", reply1->str);
    } else {
        printf("键不存在或者不是字符串类型\n");
    }

    freeReplyObject(reply1);


//    startExample5("../config_files/config.txt","23300021","12345678","fu2401");
    // 暂停执行 3 秒钟，等待listener 连接成功
    std::this_thread::sleep_for(std::chrono::seconds(13));
    return 0;
}