/*!
* \file  ShengliStockUserTraderApiStruct.h
* \brief 查询客户端公共的头文件
*
* 此文件描述了交易客户端结构体的定义
*
* \author  SHENGLI
* \version 1.0
* \date    2014-04-18
*/

#ifndef SECURITY_STOCKTRADERSTRUCT_H
#define SECURITY_STOCKTRADERSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../../common/C++/ShengliStockUserApiCommonStruct.h"

#pragma pack(push, 1)

///下单
struct CShengliStockEnterOrderField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户端编号
	TShengliStockClientOrderTokenType	ClOrdToken;
	///客户号
	TShengliStockClientIdType			ClientID;
	///证券类型
	TShengliStockSecurityTypeType		SecurityType;
	///证券子类型
	TShengliStockSecurityTypeType		SecuritySubType;	
	///资金账号
	TShengliStockAccountType			FundAccount;	
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///方向
	TShengliStockSideType				Side;
	///数量
	TShengliStockQtyType				OrderQty;
	///最小成交数量
	TShengliStockQtyType				MinQty;
	///订单类型
	TShengliStockPriceTypeType			PriceType;
	///市价单时有效,最多成交价位数,0表示不限
	TShengliStockMaxPriceLevelsType		MaxPriceLevels;
	///单子的存活时间
	TShengliStockTIFType				TIF;
	///价格
	TShengliStockOrderPriceType			Price;
	///止损价
	TShengliStockOrderPriceType			StopPrice;
	///代码
	TShengliStockSymbolType				SecurityCode;
	///交易类型
	TShengliStockCashMarginFlagType		CashMarginFlag;
	///会话ID,不关心时填0即可
	TShengliStockSessionIDType			SessionID;
	///会话模式
	TShengliStockSessoinSelModeType		SessionSelMode;
	///客户使用,回报时将回传
	TShengliStockUserInfoType			UserInfo;	
	///OpStation记录ID
	TShengliStockRecordID				RecordID;
	/// 强平标记
	/**
		0:正常交易，非强平
		1~254: 强平单，同时代表强平的原因ID
	*/	
	TShengliStockForceCoverFlag			ForceCoverFlag ;
	//被硬件忽略的消息1
	TShengliStockToBypassByte			ToBypass1;
	//软件数据库落库
	TShengliStockDelegateType			DelegateType;
	//被硬件忽略的消息2
	TShengliStockToBypassByte			ToBypass2;
	//被硬件忽略的消息3
	TShengliStockToBypassByte			ToBypass3;
	//被硬件忽略的消息4
	TShengliStockToBypassByteUInt		ToBypass4;	
	// 组合单边平仓里面的组合ID
	TShengliStockSecondaryOrderType		SecondaryOrderID;
};

/// 订单扩展
struct CShengliStockExternOrder
{
	///可用资金
	TShengliStockAmountType				AvailBp;
	///仓位数量
	TShengliStockPosQtyType				PositonQty;
};

///撤单
struct CShengliStockCxlOrderField
{
	///要撤订单的UserId，配合OrigClOrdToken使用。
	TShengliStockOrigUserIdType			OrigUserId;
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户端编号
	TShengliStockClientOrderTokenType	ClOrdToken;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///盛立系统产生的单子号
	TShengliStockOrderIDType            OrigOrderID;
	///要撤订单的ClOrdToken
	TShengliStockClientOrderTokenType   OrigClOrdToken;
	///单子被取消后所希望剩下的数量
	///单子取消的数量 
	TShengliStockQtyType                LeavesQty;
	///客户使用,回报时将回传
	TShengliStockUserInfoType1			UserInfo1;

	//委托方式
	TShengliStockDelegateType		DelegateType;
    //保留字段
    TShengliStockToBypassUShort		ToBypass1;
    TShengliStockToBypassByte		ToBypass2;
    TShengliStockToBypassByte		ToBypass3;
    TShengliStockToBypassByte		ToBypass4;
};

///向主席锁定/解锁标的券数量请求
struct  CShengliStockFrzUnderlyingSymbolQtyReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///请求ID
	TShengliStockRequestIDType			RequestID;
	///交易所ID
	TShengliStockExchangeIDType			ExchangeID;
	///市场代码
	TShengliStockSymbolType				SecurityCode;
	///锁定解锁标志
	TShengliStockFrzFlagType			FrzFlag;
	///数量
	TShengliStockQtyType				Quantity;
	///评定
	TShengliStockTextType				Remark;
	///划转类型
	TShengliPosInOutSourceType			InOutSource;
	///流水号
	TShengliSeqNo						SeqNo;
};

///同主席划入划出资金请求
struct CShengliStockInOutFundAccountAmountReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///请求ID
	TShengliStockRequestIDType			RequestID;
	///交易所ID
	TShengliStockExchangeIDType			ExchangeID;
	///划入划出标志
	TShengliStockFrzFlagType			InOutFlag;
	///数量
	TShengliStockAmountType				Amount;
	///评定
	TShengliStockTextType				Remark;
};

///向其他节点划出资金请求
struct CShengliStockTrasnBpReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///资金账号类型
	TShengliStockAccountTypeType		FundAccountType;
	///交易所
	TShengliStockExchangeIDType			Exchange;
	///请求ID
	TShengliStockRequestIDType			RequestID;
	///数量
	TShengliStockAmountType				Amount;
};

///交易所状态变化报告
struct CShengliStockExchangeStatusReportField
{
	///交易所代码
	TShengliStockExchangeIDType			ExchID;
	///交易所连接代号
	TShengliStockSessionIDType			SessionID;
	///交易所状态
	TShengliStockExchSessionSatusType	SessionStatus;
};

///订单拒绝
struct CShengliStockOrderRejectedField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///下单时指定的ClOrdToken
	TShengliStockClientOrderTokenType	ClOrdToken;
	///REM拒绝时该值为0. 交易所拒绝时为REM系统单号
	TShengliStockOrderIDType			OrderID;
	///拒绝的时间戳
	TShengliStockTimeStampType			RejectTimeStamp;
	///系统拒绝
	TShengliStockRejectedByType			RejectedBy;
	///拒绝原因
	TShengliStockRejectReasonType		RejectReason;
	///语法检查结果
	TShengliStockGrammerResultType		GrammarResult;
	///被动标志，只有交易所拒绝的情况有可能
	TShengliStockOrderCxlPassiveFlagType PassiveFlag;
	///风控检查结果
	TShengliStockRiskResultType			RiskResult;
	///错误原因文字
	TShengliStockReasonTextType			ReasonText;
};

///撤单拒绝
struct CShengliStockOrderCxlRejectedField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///订单凭证
	TShengliStockClientOrderTokenType	ClOrdToken;
	///单号
	TShengliStockOrderIDType            OrderID;
	///REM系统拒绝的时间戳，或者如果是交易所拒绝，REM处理交易所拒绝的时间戳
	TShengliStockTimeStampType          RejectTimeStamp;
	///如果是交易所撤单拒绝，交易所消息中提供的时间戳。
	TShengliStockTimeStampType			ExchangeTransTimestamp;
	///系统拒绝
	TShengliStockRejectedByType			RejectedBy;
	///拒绝原因
	TShengliStockRejectReasonType		RejectReason;
	///语法检查
	TShengliStockGrammerResultType		GrammarResult;
	///被动撤单标志
	TShengliStockOrderCxlPassiveFlagType PassiveFlag;
	///风控检查结果
	TShengliStockRiskResultType			RiskResult;
	///错误原因文字
	TShengliStockCxlRejectReasonTextType ReasonText;
	///被撤订单的UserID，找不到原单的场景时填0
	TShengliStockUserIDType				OrigUserID;
	///被撤订单的ClOrdToken，找不到原单的场景时填0
	TShengliStockClientOrderTokenType	OrigClOrdToken;
};

/// ETF申购赎回成交回报
/// Head
typedef CShengliStockOrderExecedField CShengliStockEtfExecHeadField;
/// Body
struct  CShengliStockEtfExecBodyField
{
	///成份股证券代码
	TShengliStockSymbolType				MemberSecurityCode;
	///股份交付数量
	TShengliStockQtyType				DeliveryQty;
	///交易所
	TShengliStockExchangeIDType			MemberExchID;
	///现金替代比例
	TShengliStockSubstCashRateType		SubstCashRate;
};

///向主席锁定/解锁标的券数量请求响应
struct  CShengliStockFrzUnderlyingSymbolQtyField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///交易所ID
	TShengliStockExchangeIDType			ExchangeID;
	///请求ID
	TShengliStockRequestIDType			RequestID;
	///市场编码
	TShengliStockSymbolType				SecurityCode;
	///锁定解锁标志
	TShengliStockFrzFlagType			FrzFlag;
	///数量
	TShengliStockQtyType				Quantity;
	///结果标号
	TShengliStockResultType				Result;
	///结果内容
	TShengliStockTextType				MsgText;
	///返回消息类型
	TShengliStockSyncRspMsgType			MsgType;
};

///同主席划入划出资金请求响应
struct CShengliStockInOutFundAccountAmountField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账户
	TShengliStockAccountType			FundAccount;
	///请求ID
	TShengliStockRequestIDType			RequestID;
	///划入划出标志
	TShengliStockFrzFlagType			RrzFlag;
	///数量
	TShengliStockAmountType				Amount;
	///结果标号
	TShengliStockResultType				Result;
	///消息内容
	TShengliStockTextType				MsgText;
};

///向交易节点划转资金请求响应
struct CShengliStockTrasnBpField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///资金账号类型
	TShengliStockAccountTypeType		FundAccountType;
	///交易所
	TShengliStockExchangeIDType			Exchange;
	///请求ID
	TShengliStockRequestIDType			RequestID;
	///数量
	TShengliStockAmountType				Amount;
	///结果标号
	TShengliStockResultType				Result;
	///消息内容
	TShengliStockTextType				MsgText;
};

///系统信息上报
struct CShengliSystemMsgReportField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///消息类型
	int									MsgType;
	///消息码
	int									MsgCode;
	///消息内容
	TShengliStockTextType				MsgText;
};

struct CShengliOpStationReportReq
{
	///用户key
	TShengliOpStaionCustomerKey			CustomerKey;
	///上报内容
	TShengliOpStationReportContent		OpStationContent;
};

struct CShengliOpStationReportResp
{
	///用户key
	TShengliOpStaionCustomerKey			CustomerKey;
	///上报结果
	TShengliOpStationReportResult		Result;
	///OpStationID
	TShengliOpStationID					OpStationID;
	///用户ID
	TShengliUserID						UserID;
};

///客户号资金状态查询请求
struct CShengliStockReqQueryBpStatusField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
};

///查询出入金
struct CShengliStockQueryCashInOutField
{
	///用户ID
	TShengliStockUserIDType			UserID;
	///客户号
	TShengliStockClientIdType		ClientID;
	///资金账号
	TShengliStockAccountType		FundAccount;
};

///查询出入金的返回
struct CShengliStockRespCashInOutField
{
	///用户ID
	TShengliStockUserIDType					UserID;
	///客户号
	TShengliStockClientIdType				ClientID;
	///资金账号
	TShengliStockAccountType				FundAccount;
	///资金账号类型
	TShengliStockAccountTypeType			FundAccountType;
	///出入金源
	TShengliBpInOutSourceType				InOutSource;
	///出入金标识
	TShengliBpInOutFlagType					CashInOutFlag;
	///业务资金(实际返回金额是放大1w倍的)
	TShengliStockCashInOutAmountType		ModifyBp;
	///上报时间
	TShengliStockCashInOutTimeType			UpDt;
	///流水序号
    TShengliSeqNo                       	SeqNo;
	///查询结果
    TShengliStockCashInOutQueryResultType 	Result;
    ///结果内容
    TShengliStockTextType                 	MsgText;
};

/// 证券划拨记录查询
struct CShengliStockQueryTransferPositionField
{
	///用户ID
	TShengliStockUserIDType			UserID;
	///客户号
	TShengliStockClientIdType		ClientID;
	///资金账号
	TShengliStockAccountType		FundAccount;
};

/// 证券划拨记录查询
struct CShengliStockRespTransferPositionField
{	
	///流水序号
    TShengliSeqNo                       SeqNo;
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///资金账号类型
	TShengliStockAccountTypeType		FundAccountType;
	///出入源
	TShengliPosInOutSourceType			InOutSource;
	///出入标识
	TShengliPosInOutFlagType			InOutFlag;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///代码
	TShengliStockSymbolType				SecurityCode;
	/// 股东账户
	TShengliStockAccountType			TradeAccount;	
	///PBU
	TShengliPBU							TradePosPbu;
	// 今仓，昨仓标记
	TShengliStockPosDayType				OvnOrToday ; 	
	// 调整数量 
	TShengliStockQtyType				PosDeltaQty ; 
	///上报时间
	TShengliStockCashInOutTimeType		UpDt;
	///状态
	TShengliOperatorCheckFlagType		State;
	///评定
	TShengliStockTextType				Remark;
} ;

/// 查询风控阈值  请求结构体
struct CShengliStockReqQueryRiskThresholdValueField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	/// 风控ID号
	TShengliRiskRuleID					RiskRuleID;
	///证券类型  填空
	TShengliStockSecurityTypeType		SecurityType;
	///证券子类型  填空
	TShengliStockSecurityTypeType		SecuritySubType;
	///交易所  填空
	TShengliStockExchangeIDType			ExchID;
	///代码  填空
	TShengliStockSymbolType				SecurityCode;
};

/// 查询风控阈值  返回结构体
struct CShengliStockReqQueryRiskThresholdValueRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///风控ID号
	TShengliRiskRuleID					RiskRuleID;
	///风控类型
	TShengliRiskRuleType				RiskRuleType;	
	///证券类型
	TShengliStockSecurityTypeType		SecurityType;
	///证券子类型 
	TShengliStockSecurityTypeType		SecuritySubType;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///代码
	TShengliStockSymbolType				SecurityCode;	
	///参数个数	最大为3 
	TShengliRiskRuleParamCount			ParamCount;	
	///门限值 
	TShengliRiskValue					RiskThreholdValue[3];
	///查询结果
	TShengliQueryResult					Result;
};

/// 查询风控统计值 头部消息
struct CShengliStockReqQueryHeaderField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	/// 查询个数  指向 CShengliStockReqQueryRiskValueField 的个数 
	TShengliRiskRuleParamCount			QryRiskCount;
};

/// 查询 风控统计值 结构体
struct CShengliStockReqQueryRiskValueField
{
	/// 风控ID号
	TShengliRiskRuleID					RiskRuleID;
	///证券类型  填空
	TShengliStockSecurityTypeType		SecurityType;
	///证券子类型  填空
	TShengliStockSecurityTypeType		SecuritySubType;
	///交易所  填空
	TShengliStockExchangeIDType			ExchID;
	///代码  填空
	TShengliStockSymbolType				SecurityCode;
};


/// 查询风控统计值   返回结构体
struct CShengliStockReqQueryRiskValueRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///风控ID号
	TShengliRiskRuleID					RiskRuleID;
	///风控类型
	TShengliRiskRuleType				RiskRuleType;
	///证券类型
	TShengliStockSecurityTypeType		SecurityType;
	///证券子类型 
	TShengliStockSecurityTypeType		SecuritySubType;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///代码
	TShengliStockSymbolType				SecurityCode;
	///门限值 
	TShengliRiskValue					RiskValue;
	///查询结果
	TShengliQueryResult					Result;
	///更新时间
	TShengliRiskValueUpdTimeType		UpdTime;
};

///查询账户旁路风控当前值
struct CShengliStockReqQueryAcctMonitorValueField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
};

///查询账户旁路风控 返回结构体
struct CShengliStockReqQueryAcctMonitorValueRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///账户监控ID号
	TShengliAcctMonitorID				AcctMoniotrID;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///监控条目
	TShengliStockResultText				MonitorEntryDisp;
	///监控备注
	TShengliStockTextType				Memo;
	///实时值 
	TShengliRiskValue					CurrentValue;
	///预警线1
	TShengliRiskValue					Precaution1;
	///查询结果
	TShengliQueryResult					Result;
	///更新时间
	TShengliRiskValueUpdTimeType		UpdTime;
	///标的
	TShengliStockSymbolType				Symbol;
};

///报价下单
struct CShengliQuoteEnterOrderField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户端编号
	TShengliStockClientOrderTokenType	ClOrdToken;
	///客户号
	TShengliStockClientIdType			ClientID;
	///证券类型
	TShengliStockSecurityTypeType		SecurityType;
	///证券子类型
	TShengliStockSecurityTypeType		SecuritySubType;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///方向
	TShengliStockSideType				Side;
	///代码
	TShengliStockSymbolType				SecurityCode;
	///申报类型
 	TShengliQuoteReqType				ReqType;
	///报价类型
	TShengliQuoteType					QuoteType;
	///买价
	TShengliStockOrderPriceType			BidPx;
	///买数量
	TShengliStockQtyType				BidQty;
	///买方向
	TShengliQuoteSideType				BidSide;
	///卖价
	TShengliStockOrderPriceType			AskPx;
	///卖数量
	TShengliStockQtyType				AskQty;
	///卖方向
	TShengliQuoteSideType				AskSide;
	///询价请求编号(回应报价的时候，要填,其它填空串)
	TShengliQuoteReqID					QuoteReqID;
	///供客户使用，柜台回报时将回传
	TShengliStockUserInfoType2			UserInfo;
	///供客户使用，深交所交易所回报时将回传
	TShengliStockExchangeUserInfoType	ExchangeUserInfo;
	///委托方式
	TShengliStockDelegateType			DelegateType;
	///OpStation记录ID
	TShengliStockRecordID				RecordID;
};

///交易所询价
struct CShengliExchangeInqueryField
{
	///报价PBU
	TShengliQuotePBU					ReportPbu;
	///提交PBU
	TShengliQuotePBU					SubmitPbu;
	///交易所
	TShengliStockExchangeIDType			Exchange;
	///代码
	TShengliStockSymbolType				SecurityCode;
	///所有者类型
	TShengliRemOwnerType				OwnerType;
	///交易转发时间
	TShengliStockTimeStampType			TransactTime;
	///市场单号
	TShengliMarketOrderID				MarketOrderID;
	///执行单号
	TShengliExecID						ExecID;
	///客户订单编号
	TShengliClOrdID						ClOrdID;
	///证券账户
	TShengliExchangeAccount				ExchangeAccount;
	///询价请求编号
	TShengliQuoteReqID					QuoteReqID;
	///询价请求事务类型
	TShengliQuoteRequestTransType		QuoteRequestTransType;
	///询价请求类型
	TShengliQuoteRequestType			QuoteRequestType;
	///询价请求状态
	TShengliQuoteRequestStatus			QuoteRequestStatus;
	///私有报价
	TShengliPrivateQuote				PrivateQuote;
	///数量
	TShengliStockQtyType				OrderQty;
	///价格
	TShengliStockOrderPriceType			Price;
	///方向
	TShengliStockSideType				Side;
	///询价请求失效时间	
	TShengliStockTimeStampType			ExpireTime;
	///报价类型
	TShengliQuoteType					QuoteType;
	///报价价格类型，预留
	TShengliQuotePriceType				QuotePriceType;
	///备注
	TShengliMemo						Memo;
};

/// 中继登录请求
struct CShengliStockProxySubmitDataField
{
	/// AppID
	TShengliStockAppIDType				AppID;//终端客户的APPID
	/// AuthCode
	TShengliStockAuthCodeType			AuthCode;//终端客户的AppId对应的AuthCode
	/// 客户终端公网IP
	TShengliStockIP						TerminalPubNetIP;
	/// 客户终端公网端口号
	TShegliStockPort					TerminalPubNetPort;
	/// 客户终端登入时间
	TShengliStockLoginTimeType			TerminalLoginTime;
	/// 异常标识
	TShengliStockExceptionFlagType		ExceptionFlag;
	/// RealyID 必须是本次连接的登录请求中一致的APPidRelayId,不强制填写
	TShengliStockAppIDType				RelayID;
	/// 终端采集信息密文
	TShengliStockLocalSystemInfoType	TerminalSystemInfo; 
	///终端客户使用的资金账号
	TShengliStockAccountType			FundAccount ;//	可选，不填时，使用中继登录用户绑定的首个资金账号
};

/// 中继提交客户采集信息的返回结构
struct CShengliStockRspInfoField
{
	/// 错误码
	int									MsgCode;
	/// 错误内容
	TShengliStockTextType				MsgText;
};

//订阅请求
struct CShengliStockSubscribeField
{
	TShengliUserID						UserID;
};

//订阅回复
struct CShengliStockRespSubscribeField
{
	TShengliUserID						UserID;
	TShengliStockErrNoType				ErrCode;
	TShengliStockErrText				ErrText;
};

//推送交易所订单单号
struct CShengliStockRespMktCltOrdIDField
{
	TShengliUserID						UserID;
	TShengliStockClientIdType			ClientID;
	TShengliStockAccountType			FundAccount;
	TShengliStockOrderType				OrderType;
	TShengliStockClientOrderTokenType	CltOrderToken;
	TShengliUserID						OperUserID;
	TShengliStockOrderIDType			OrderID;
	TShengliUserID						OrigUserID;
	TShengliStockClientOrderTokenType	OrigCltOrderToken;
	TShengliStockOrderIDType			OrigOrderID;
	TShengliMktCltOrdID					MarketCltOrderID;
};

///报价单回滚请求
struct CShengliStockQuoteRewindReqField
{
	/// 用户ID
	TShengliStockUserIDType				UserID;
	/// 客户号
	TShengliStockClientIdType			ClientID;
	/// 要开始同步的消息序号
	TShengliStockMsgIndexType			NextMsgIndex;
};

///报价单回滚完成
struct CShengliStockQuoteOrderRewindFinishField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///错误码
	TShengliStockErrorCodeType			ErrCode;
};

///查询合约保证金信息
struct CShengliStockQuerySymbolMarginInfoReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///合约信息
    TShengliStockSymbolType 			SecurityCode;
};

///查询合约保证金回复信息
struct CShengliStockQuerySymbolMarginInfoRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///合约信息
    TShengliStockSymbolType 			SecurityCode;
    ///开仓保证金
    TShengliStockAmountType				OpenMarin;
    ///交易所保证金
    TShengliStockAmountType				ExchangeMarin;
    ///风险保证金
    TShengliStockAmountType				RiskMargin;
    ///结果标号
    TShengliStockQueryResultType        Result;
};

///查询合约费用信息
struct CShengliStockQuerySymbolFeeInfoReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///交易所
	TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///合约信息
    TShengliStockSymbolType 			SecurityCode;
};

struct TShengFeeConfigInfo
{
    ///按金额收取比例
    TShengliRate       					m_FeeAmount; 
	///每手收取的金额
    TShengliStockAmountType				m_FeeQty;
	///费用最小值
    TShengliStockAmountType				m_FeeMin;
	///费用最大值 ，只有交易所有效    
    TShengliStockAmountType				m_FeeMax;    
	///费用类型
	TShengliStockRemFeeType				m_FeeType ;
};

///查询合约费用回复信息
struct CShengliStockQuerySymbolFeeInfoRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///合约信息
    TShengliStockSymbolType 			SecurityCode;
	///合约类型
	TShengliStockSecurityTypeType		SecurityType;
	///合约子类型
    TShengliStockSecuritySubTypeType    SecuritySubType;
    ///side
	TShengliStockSideType 				Side;
	///配置个数
	TShengliFeeConfigCount				ValidCount;
	///结果标号
    TShengliStockQueryResultType        Result;
	///手续费配置信息
	TShengFeeConfigInfo					FeeConfig[FEE_CONFIG_MAX_COUNT];
};

///查询签约银行信息
struct CShengliStockQuerySigningBankInfoReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所(非必填)
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///渠道(非必填)
	TShengliChannelType					Channel;
	//银衍业务标识
	TShengliCubsbTrdIDType				CubsbTrdID;
};

///查询签约银行回复信息
struct CShengliStockQuerySigningBankInfoRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///银行名称
	TShengliExtOrgNameType				ExtOrgName;
	///结果标号
    TShengliQueryBankInfoResultType     Result;
	///消息
	TShengliStockTextType				MsgText;
	///是否校验账户密码
	TShengliCheckPasswdType			    CheckFundPasswd; 
	///是否校验银行密码
	TShengliCheckPasswdType			    CheckBankPasswd; 
};

///查询银行余额
struct CShengliStockQueryBankBalanceInfoReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所(非必填)
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///渠道(非必填)
	TShengliChannelType					Channel;
    //资金账户密码(非必填)
    TShengliPwdType						AcctPwd;
	//银行密码(非必填)
	TShengliPwdType						BankPwd;
};

///查询银行余额回复消息
struct CShengliStockQueryBankBalanceInfoRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///机构代码
	TShengliOrgCodeType					OrgCode;
	///资金余额
	TShengliStockAmountType				FundBln;
	///结果标号
    TShengliQueryBankInfoResultType     Result;
	///消息
	TShengliStockTextType				MsgText;
};

///一步式入金
struct CShengliStockOneStepTransferInCashReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所(非必填)
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///转账金额
	TShengliStockAmountType				TransAmt;
	///渠道(非必填)
	TShengliChannelType					Channel;
	//资金账户密码(非必填)
	TShengliPwdType						AcctPwd;
	//银行密码(非必填)
	TShengliPwdType						BankPwd;
};

///一步式入金回复消息
struct CShengliStockOneStepTransferInCashRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///转账金额
	TShengliStockAmountType				TransAmt;
	///结果标号
    TShengliOneStepTransferResultType   Result;
    ///消息
	TShengliStockTextType				MsgText;

};

///一步式出金
struct CShengliStockOneStepTransferOutCashReqField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所(非必填)
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///转账金额
	TShengliStockAmountType				TransAmt;
    ///渠道(非必填)
    TShengliChannelType					Channel;
	//资金账户密码(非必填)
	TShengliPwdType						AcctPwd;
	//银行密码(非必填)
	TShengliPwdType						BankPwd;
};

///一步式出金回复消息
struct CShengliStockOneStepTransferOutCashRespField
{
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
    ///交易所
    TShengliStockExchangeIDType			ExchID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///币种
	TShengliCurrencyType				Currency;
	///银行代码
	TShengliExtOrgType					ExtOrg;
	///转账金额
	TShengliStockAmountType				TransAmt;
	///结果标号
    TShengliOneStepTransferResultType   Result;
	///消息
	TShengliStockTextType				MsgText;
};

///银行冲正(没有使用)
struct CShengliStockBankReversalReqField
{

};

///银行冲正回复消息(没有使用)
struct CShengliStockBankReversalRespField
{

};

///异常处理(没有使用)
struct CShengliStockBankTransferExceptionHandlingReqField
{

};

///异常处理(没有使用)
struct CShengliStockBankTransferExceptionHandlingRespField
{

};


// 客户端 类型
struct CShengliStockTradeClientTypeReqField
{
	TShengliStockUserIDType				UserID;  	///<  用户ID
	TShengliStockClientProdInfoType     ProcInfo ;  ///< 产品类型
} ;

// 查询 支持的委托方式
struct CShengliStockQueryDelegateTypeReqField
{
	TShengliStockUserIDType				UserID;  	///<  用户ID
} ;

// 查询 支持的委托方式
struct CShengliStockQueryDeletageTypeRespField
{
	TShengliStockUserIDType				UserID;  	///<  用户ID
	TShengliStockDelegateType			DelegateType; ///< 委托方式
	TShengliStockTextType				DelegateDesc ; ///< 委托方描述	
} ;

/// 查询委托请求
struct CShengliStockReqQueryEntrustField
{
	///请求序号
	TShengliStockRequestIDType		 RequestID;
	///用户ID
	TShengliStockUserIDType			UserID;
	///客户号
	TShengliStockClientIdType		ClientID;
	///资金账号
	TShengliStockAccountType		FundAccount;
	///查询源
	TShengliQueryFlag				QryFlag;
	///委托编码ID
	TShengliStockEntrustIDType		OrderID;
	///客户端编号
	TShengliStockClientOrderTokenType	ClOrdToken;
	///市场
	TShengliStockExchangeIDType		ExchID;
	///证券代码
	TShengliStockSymbolType			SecurityCode;
	///委托方向
	TShengliStockSideType			Side;
	///订单状态数量
	TShengliStockRequestNumType		StateNum;
	///订单状态
	TShengliStockOrderStateType		OrderState[16];
	//起始序号
	TShengliSeqNumber64				StartIdx;
	///本次查询最大返回数量(最大单次查询上限为10000)
	TShengliStockRequestNumType     RequestNum;
};

/// 查询委托响应
struct CShengliStockRespQueryEntrustField
{
	///请求序号
	TShengliStockRequestIDType				RequestID;
	///用户ID
	TShengliStockUserIDType					UserID;
	///当前序号
	TShengliSeqNumber32						CurIdx;
	/// 当前记录在服务器中游标 
	TShengliStockCursorMarkType				CurCursorMark;
	///委托用户ID
	TShengliStockUserIDType					Entrust_UserID;
	///客户号
	TShengliStockClientIdType				ClientID;
	///资金账号
	TShengliStockAccountType				FundAccount;
	///客户端编号
	TShengliStockClientOrderTokenType		ClOrdToken;
	///REM系统单cluster唯一编号，撤单标识原始订单号OrigOrderID
	TShengliStockOrderIDType				OrderID;
	///交易所单号
	TShengliStockExchangeOrderIDType		ExchangeOrderID;
	///面向交易所的ordertoken
	TShengliStockExchangeOrderTokenType		ExchangeOrderToken;
	///市场
	TShengliStockExchangeIDType				ExchID;
	///代码
	TShengliStockSymbolType					SecurityCode;
	///证券类型
	TShengliStockSecurityTypeType			SecurityType;
	///证券子类型
	TShengliStockSecuritySubTypeType		SecuritySubType;
	///方向
	TShengliStockSideType					Side;
	///订单类型
	TShengliStockPriceTypeType				PriceType;
	///数量
	TShengliStockQtyType					OrderQty;
	///最小成交数量
	TShengliStockQtyType					MinQty;
	///市价单时有效,最多成交价位数,0表示不限
	TShengliStockMaxPriceLevelsType			MaxPriceLevels;
	///单子的存活时间
	TShengliStockTIFType					TIF;
	///会话ID
	TShengliStockSessionIDType				SessionID;
	///价格
	TShengliStockOrderPriceType				Price;
	///止损价
	TShengliStockOrderPriceType				StopPrice;
	///交易类型
	TShengliStockCashMarginFlagType			CashMarginFlag;
	///会话模式
	TShengliStockSessoinSelModeType			SessionSelMode;
	///交易所接受标志
	TShengliStockExchangeAcceptFlagType		ExchangeAcceptFlag;
	///总成交量
	TShengliStockQtyType					FilledQty;
	///订单状态
	TShengliStockOrderStatusType			OrderState;
	///被动单/外部单标志
	TShengliStockPassiveOrderFlagType		PassiveOrderFlag;
	///只要不为0，就是强平的原因
	TShengliStockForceCoverFlag				ForceCoverFlag; 
	///收到订单的时间，单位为纳秒
	TShengliStockTimeStampType				RecvTimestamp;
	///REM内核(硬件)处理完毕接受的时间戳，和开始发往交易所的时间戳相同&REM接受撤单请求并发往交易所的时间戳
	TShengliStockTimeStampType				AcceptTimestamp;
	///REM系统收到交易所接受的时间戳
	TShengliStockTimeStampType				ExchangeAcceptTimestamp;
	///交易所提供的撤单时间戳，交易所接受时，交易所给出的时间戳
	TShengliStockTimeStampType				ExchangeTransTimestamp;
	//交易所营业部
	TShengliStockBranchIdType				BranchID;
	///下单时候的UserInfo，UserInfo1为opstationID，UserInfo2为用户的自定义数据
	TShengliStockUserInfo1Type				UserInfo1;
	TShengliStockUserInfoType				UserInfo2;
	///委托方式
	TShengliStockDelegateType				DelegateType;
	///撤单状态
	TShengliStockMarketCxlReqStatusType		CxlReqStatus;
	///订单特有
	///--期权扩展字段--///
	///期权合约过期日
	TShengliStockTradingDateType			ExpireDate;
	///交易所
	TShengliStockExchangeIDType				UnderlyingExchID;
	///期权标的证券代码
	TShengliStockSymbolType					UnderlyingSecurityCode;
	///期权合约账户代码
	TShengliStockContractAccountCodeType	ContractAccountCode;
	///期权合约代码
	TShengliStockContractIDType				ContractID;
	///期权看涨看跌
	TShengliStockCallOrPutType				CallOrPut;
	///期权行权价
	TShengliStockOrderPriceType				StrikePrice;
	///报价单特有
	///申报类型
	TShengliQuoteReqType					QuoteReqType;
	///卖边价格	
	TShengliStockOrderPriceType				AskPrice;
	///卖边数量	
	TShengliStockQtyType					AskQty;
	///卖边方向	
	TShengliQuoteSideType					AskSide;
	///卖边订单状态	
	TShengliStockOrderStatusType			AskOrderState;
	///卖边总成交量
	TShengliStockQtyType					AskFilledQty;
	///买边价格	
	TShengliStockOrderPriceType				BidPrice;
	///买边数量	
	TShengliStockQtyType					BidQty;
	///买边方向	
	TShengliQuoteSideType					BidSide;
	///买边订单状态	
	TShengliStockOrderStatusType			BidOrderState;
	///买边总成交量
	TShengliStockQtyType					BidFilledQty;
	///UserInfo
	TShengliStockUserInfoType2				UserInfo3;
	///ExchangeUserinfo
	TShengliStockExchangeUserInfoType		ExchangeUserinfo;
	// 多腿信息	
	CShengliStockExternCombOrder			Extern;	// 扩展信息
	CShengliStockCombLegField				Leg[4];	// 多腿信息，最多4腿
};

/// 查询委托成交请求
struct CShengliStockReqQueryEntrustExecutionField
{
	///请求序号
	TShengliStockRequestIDType		 	RequestID;
	///用户ID
	TShengliStockUserIDType				UserID;
	///客户号
	TShengliStockClientIdType			ClientID;
	///资金账号
	TShengliStockAccountType			FundAccount;
	///查询源
	TShengliQueryFlag					QryFlag;
	///REM系统cluster唯一成交编号	
	TShengliStockExecIDType_32			ExecID;
	///委托编码ID
	TShengliStockEntrustIDType			OrderID;
	///客户端编号
	TShengliStockClientOrderTokenType	ClOrdToken;
	///市场
	TShengliStockExchangeIDType			ExchID;
	///证券代码
	TShengliStockSymbolType				SecurityCode;
	///委托方向
	TShengliStockSideType				Side;
	//起始序号
	TShengliSeqNumber64					StartIdx;
	///本次查询最大返回数量(最大单次查询上限为10000)
	TShengliStockRequestNumType      	RequestNum;
};

/// 查询委托成交响应
struct CShengliStockRespQueryEntrustExecutionField
{
	///请求序号
	TShengliStockRequestIDType				RequestID;
	///用户ID
	TShengliStockUserIDType					UserID;
	///当前序号
	TShengliSeqNumber32						CurIdx;
	/// 当前记录在服务器中游标 
	TShengliStockCursorMarkType				CurCursorMark;
	///委托用户ID
	TShengliStockUserIDType					Entrust_UserID;
	///客户号
	TShengliStockClientIdType				ClientID;
	///资金账号
	TShengliStockAccountType				FundAccount;
	///客户端编号
	TShengliStockClientOrderTokenType		ClOrdToken;
	///REM系统单cluster唯一编号，撤单标识原始订单号OrigOrderID
	TShengliStockOrderIDType				OrderID;
	///交易所单号
	TShengliStockExchangeOrderIDType		ExchangeOrderID;
	///面向交易所的ordertoken
	TShengliStockExchangeOrderTokenType		ExchangeOrderToken;
	///市场
	TShengliStockExchangeIDType				ExchID;
	///代码
	TShengliStockSymbolType					SecurityCode;
	///证券类型
	TShengliStockSecurityTypeType			SecurityType;
	///证券子类型
	TShengliStockSecuritySubTypeType		SecuritySubType;
	///方向
	TShengliStockSideType					Side;
	///被动单/外部单标志
	TShengliStockPassiveOrderFlagType		PassiveOrderFlag;
	///本次成交价
	TShengliStockOrderPriceType				LastPrice;
	///本次成交量	
	TShengliStockQtyType					LastQty;
	///剩余数量	
	TShengliStockQtyType					LeavesQty;
	///开平标记	
	TShengliQuoteSideType					PositionSide;
	///买卖标记	
	TShengliStockSideType					AskOrBid;
	///订单状态	
	TShengliStockOrderStatusType			OrderState;
	///REM系统cluster唯一成交编号	
	TShengliStockExecIDType_32				ExecID;
	///交易所成交ID	
	TShengliStockExchangeExecIDType			ExchangeExecID;
	///交易所接受时，交易所给出的时间戳	
	TShengliStockTimeStampType				ExchangeTransTimestamp;
	///UserInfo
	TShengliStockUserInfoType2				UserInfo3;
	///ExchangeUserinfo
	TShengliStockExchangeUserInfoType		ExchangeUserinfo;
};


#pragma pack(pop)

#endif
