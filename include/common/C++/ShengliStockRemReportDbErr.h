/*!
* \file  ShengliStockRemReportDbErr.h
* \brief 交易和查询客户端公共的头文件
*
* 此文件描述了使用交易和查询客户端的错误类型
*
* \author  SHENGLI
* \version 1.0
* \date    2014-04-18
*/

#pragma  once

#ifndef _EES_TRADE_REM_MARKET_ERROR_H_
#define _EES_TRADE_REM_MARKET_ERROR_H_

/// 没有错误
#ifndef NO_REM_MARKET_ERROR
#define NO_REM_MARKET_ERROR    0	
#endif

/// 未知错误。
#define RemMarkeErr_NotDef						1	
/// 没有找到账户的PBU。
#define RemMarkeErr_NotFindAccountPbu			1		
/// 没有找到账户订单对应的订单管理区间。 
#define RemMarkeErr_NotFindOrderReffRange		2				
/// 订单区间没有配置报盘库
#define RemMarkeErr_NotLinkDb					3			
/// 报盘库未连接
#define RemMarkeErr_NotConnDb					4				
/// 订单 reff 越界
#define RemMarkeErr_OutofOrderReff				5			
/// 不支持的 side 标记 
#define RemMarkeErr_NotSupportSide				6			
/// 不支持的价格类型 
#define RemMarkeErr_NotSupportPriceType			7				
/// 不支持的订单生命周期 
#define RemMarkeErr_NotSupportTif				8				
/// 写报盘错误
#define RemMarkeErr_WriteDbError				9			
/// 找不到要撤销的订单
#define RemMarkeErr_NotFindOrigOrd				10				

/// 报单错误 账户配置的PBU与网关里面不一样。
#define RemMarkeErr_AccountPbuError				11				

#endif
