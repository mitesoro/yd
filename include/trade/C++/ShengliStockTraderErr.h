#pragma  once

#ifndef _EES_TRADE_API_ERROR_H_
#define _EES_TRADE_API_ERROR_H_

/// 没有错误
#ifndef NO_ERROR
#define NO_ERROR                    0	
#endif

/// 连接服务失败
#define CONN_SERVER_FAILED          1

/// 连接服务失败，一般会在服务器断开时候这个错误
#define REMOTE_DISCONN_SERVER       2	

/// 本地网络断开，会在本地主动断开的时候，产生这个错误
#define LOCAL_DISCONN_SERVER        3

/// 网络出错，网络异常，会产生这个错误
#define NEWWORK_ERROR               4

/// 登录服务失败，会在登录的时候产生
#define LOGON_FAILED                5	

/// 用户进行操作，是需要提前登录的，如果没有登录会产生这个错误
#define NOT_LOGON                   6

/// 操作之前，需要连接服务器
#define NO_CONN_SERVER              7	

/// 错误的交易对象句柄
#define HANDLE_ERRNOR               8	 

/// 设置订单 token 错误
#define ORDER_TOKEN_ERROR			9

/// 非法的密码，目前只支持全空密码检测
#define INVALID_PASSWORD_ERROR		10

/// 查询太频繁 。
#define INVALID_QUERY_FLOW_CONTROL		11

#endif

/// 登录返回的错误码
#define 	LOGON_LR_SUCCESS 							0		// 	登录成功
#define 	LOGON_LR_USERPWD_INCORRECT		1		// 	密码错误
#define 	LOGON_LR_CONFIG_INCORRECT			2		// 	用户配置问题
#define 	LOGON_LR_ALREADY_LOGON 				3		// 	用户已经登录
#define 	LOGON_LR_INVALID_RELOGON			4 	//	在已登录的连接,又发送其他用户的登录请求
#define 	LOGON_LR_MISSING_CLIENT_INFO		5		// 	用户信息不正确
#define 	LOGON_LR_INTERNAL_ERROR 			6		//	系统内部错误
#define 	LOGON_LR_NOT_USING_QUERY_PORT 7		//	未使用查询通道，2017-05-22开始，强制要求使用
#define 	LOGON_LR_CONNECT_QUERY_PORT_FAILED 	8	//	连接查询通道失败，这个错误不会在服务器上报，只会在客户端API内部报出
#define 	LOGON_LR_AUTH_FAILED				9		//	ip mac 认证失败
#define 	LOGON_LR_USER_STATUS				10	//	用户状态错误
#define 	LOGON_LR_APP_ID_AUTH_FAILED			11	//  appid 认证失败
#define 	LOGON_LR_SYSTEM_CRITICAL			99	//	系统资源不足,不允许新用户连接上来	
