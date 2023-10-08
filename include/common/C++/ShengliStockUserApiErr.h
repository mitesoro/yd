/*!
* \file  ShengliStockUserApiErr.h
* \brief 交易和查询客户端公共的头文件
*
* 此文件描述了使用交易和查询客户端的错误类型
*
* \author  SHENGLI
* \version 1.0
* \date    2014-04-18
*/

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

/// 不支持的交易类别
#define INVALID_TRADE_TYPE			18

#endif

/// 登录返回的错误码

/// 登录成功
#define 	LOGON_LR_SUCCESS 					0	
/// 密码错误
#define 	LOGON_LR_USERPWD_INCORRECT			1		
/// 用户配置问题
#define 	LOGON_LR_CONFIG_INCORRECT			2		
/// 用户已经登录
#define 	LOGON_LR_ALREADY_LOGON 				3		
///	在已登录的连接,又发送其他用户的登录请求
#define 	LOGON_LR_INVALID_RELOGON			4 	
/// 用户信息不正确
#define 	LOGON_LR_MISSING_CLIENT_INFO		5		
///	系统内部错误
#define 	LOGON_LR_INTERNAL_ERROR 			6		
///	未使用查询通道，2017-05-22开始，强制要求使用
#define 	LOGON_LR_NOT_USING_QUERY_PORT       7		
///	连接查询通道失败，这个错误不会在服务器上报，只会在客户端API内部报出
#define 	LOGON_LR_CONNECT_QUERY_PORT_FAILED 	8	
///	ip mac 认证失败
#define 	LOGON_LR_AUTH_FAILED				9		
///	用户状态错误
#define 	LOGON_LR_USER_STATUS				10	
/// appid 认证失败
#define 	LOGON_LR_APP_ID_AUTH_FAILED			11	
/// 权限不足
#define		LOGON_LR_LESS_PERMISSION			12
/// 没有重复登录权限
#define		LOGON_LR_LESS_RELOGON_PERMISSION	13
/// 用户是新增加
#define		LOGON_LR_USER_IS_NEW_ONE			14
/// 用户登录超时
#define		LOGON_LR_USER_LOGON_TIMEOUT			15		
/// 委托方式不支持
#define		LOGON_LR_USER_OPERWAY_ERROR			16
/// 不支持资金账户登录
#define		LOGON_LR_NOT_SUPPORT_FUCC_LOGON		17
/// 无可用连接
#define		LOGON_LR_HAVE_NO_USED_CONNECT		18 
/// 不支持用户登录
#define		LOGON_LR_NOT_SUPPORT_USER_LOGON		19
/// 无绑定的资金账户
#define		LOGON_LR_HAVE_NO_RELATION_FUCC		20 
/// 用户下无该资金账户 （中继服务，资金账户密码校验）
#define		LOGON_LR_ZJ_HAVE_NO_RELATION_FUCC	21 
/// 用户类型错误（OT和QRY不允许操作员登录）
#define		LOGON_LR_USER_TYPE					22 
/// 服务不支持主柜密码校验
#define		LOGON_LR_NOT_SUPPORT_CENTER_CHECK	23  
/// 与集中柜台连接异常
#define		LOGON_LR_CENTER_CONNECT_ERROR		24 
/// 资金账户被冻结
#define     LOGON_LR_USER_IS_FROZEN             25
/// 资金账户被注销
#define     LOGON_LR_USER_IS_LOGOUT             26
/// 用户下客户资金账户及股东账户信息不完整
#define     LOGON_LR_USER_INCOMPLETE            27
/// 不需要进行集中柜台密码校验
#define     LOGON_LR_NOT_NEED_CHECK             28
/// 客户未绑定到具体的资金账户
#define     LOGON_LR_CLIENTID_NOT_BIND_FUNDACC_CHECK 29
/// 资金账户登录主柜错误
#define		LOGON_LR_CENTER_LOGON_ERROR			30
///	系统资源不足,不允许新用户连接上来	
#define 	LOGON_LR_SYSTEM_CRITICAL			99	


/// 客户号错误
#define CLIENT_ERROR			1000

/// 资金账户错误
#define FUND_ACCT_ERROR			1001

/// 资金错误
#define AMOUNT_ERROR			1002

/// 出入金错误
#define INOT_BP_ERROR			1003

