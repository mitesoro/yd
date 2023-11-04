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

    startExample5("../config_files/config.txt","23300021","12345678","fu2401");
    // 暂停执行 3 秒钟，等待listener 连接成功
    std::this_thread::sleep_for(std::chrono::seconds(13));
    return 0;
}