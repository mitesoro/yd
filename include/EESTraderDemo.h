/*!****************************************************************************
@note   Copyright (coffee), 2005-2014, Shengli Tech. Co., Ltd.
@file   EESTraderDemo.h
@date   2014/4/27   12:46
@author zhou.hu

\brief  本类演示EES交易API的使用示例

@note
******************************************************************************/
#pragma once
#ifdef SHENGLI_WINDOWS
/// add by zhou.hu review 2014/4/22 Windwos平台引用的头文件
#include <Windows.h>

typedef HMODULE		T_DLL_HANDLE;

#else
/// add by zhou.hu review 2014/4/22 linux平台引用的头文件
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

typedef void*		T_DLL_HANDLE;

#endif

#include <string>
#include "ShengliTraderApi.h"

#define SHENGLI_TRADER_DLL_1_8_NAME ("libRemStockTradeApi_1.8.so")
#define SHENGLI_TRADER_DLL_1_8_TcpDirect_NAME ("libRemStockTradeApi_1.8_TcpDirect.so")

#define SHENGLI_TRADER_DLL_1_9_NAME ("libRemStockTradeApi_1.9.so")
#define SHENGLI_TRADER_DLL_1_9_TcpDirect_NAME ("libRemStockTradeApi_1.9_TcpDirect.so")

using std::string;

class TraderDemo : public CShengliStockTraderSpi
{
public:
	TraderDemo(void);
	virtual ~TraderDemo(void);

	/// \brief 测试入口函数
	void Run();

	void ReReconnect();

private:
	/// \brief 初始化
	bool Init();
	/// \brief 关闭
	void Close();

	/// \brief 延时函数
	void DemoSleep();
	/// \brief 暂停
	void Pause();

private:
	/// \brief 加载EES交易API的动态库
	bool LoadEESTrader();
	/// \brief 释放EES交易API的动态库
	void UnloadEESTrader();

	/// \brief Windows版加载交易API的动态库
	bool Windows_LoadEESTrader();
	/// \brief Windows版释放交易API的动态库
	void Windows_UnloadEESTrader();

	/// \brief Linux版本加载交易API的动态库
	bool Linux_LoadEESTrader();
	/// \brief Linux版本释放交易API的动态库
	void Linux_UnloadEESTrader();

	/// \brief 初始化参数调整方法
	void InputParam();

private:
	/// \brief 用户登录
	int ReqUserLogon();

	/// 代理登录 
	int ProxyReqLogon();

	/// 代理提交采集信息
	int ProxySubmitCapInfo();

	/// 测试本地采集
	int TestLocalCap();

	/// \brief 用户密码修改
	int ReqChangePassword();
	/// \brief 客户号列表查询
	int ReqQueryClientIdList();
	/// \brief 资金账号列表查询
	int ReqQueryAccountList();
	/// \brief 合约列表查询
	int ReqQuerySymbolList();
	/// \brief ETF成份股查询
	int ReqQueryETFMember();
	/// \brief 期权细节查询
	int ReqQueryOptionDetail();
	/// \brief 账户费率查询
	int ReqQueryAccountTradeFee();
	/// \brief 仓位查询
	int ReqQueryNormalPosition();
	/// \brief 期权仓位查询
	int ReqQueryOptionPosition();

	/// 资金信息查询
	int ReqQueryBpList();
	/// \brief 交易信息rewind请求
	int ReqRewindTradingInfo();
	/// \brief 客户号资金状态查询
	int ReqQueryClientBpStatus();
	/// \brief 交易所席位连接查询
	int ReqQueryMarketSession();
	/// \brief opstation上报
	int OpStationReport();
	/// \brief 获取订单最大token值
	int GetMaxToken();
	/// \brief 下单
	int EnterOrder();
	int EnterQuoteOrder();
	int BatchEnterQuoteOrder();
	int CancelQuoteOrder();

	int EnterCreateCombStrategyOrder();
	int EnterRelieveCombStrategyOrder();
	int EnterCombExerciseOrder();

	int EnterCashInOutList();

	int NodeOutBp();
	int Subscribe();

	int ReqRewindQuoteOrder();


	/// \brief 撤单
	int CancelOrder();
	int ReconnTest();
	int ReqQueryTradeAccountList();
	int ResendLogonMsg();

	/// \brief 风控门限值查询
	int ReqQueryRiskRuleThresholds();

	/// \brief 风控累加值查询
	int ReqQueryRiskRuleAccumulateVal();

	/// \brief 旁路风控查询
	int ReqQueryRiskMonitorValue();

	/// \brief 查询合约保证金信息
	int ReqQuerySymbolMarginInfo();

	/// \brief 查询合约费用信息
	int ReqQuerySymbolFeeInfo();

	/// \brief 查询签约银行信息
	int ReqQuerySigningBankInfo();
	
	/// \brief 查询银行余额信息
	int ReqQueryBankBalanceInfo();

	/// \brief 请求一步式银转衍
	int ReqOneStepTransferInCash();

	/// \brief 请求一步式衍转银
	int ReqOneStepTransferOutCash();

	int ReqQueryDelegateInfo() ;

	/// \brief 请求冻结解冻标的
	int ReqFrzUnderlying();

	/// \brief 请求出入金
	int InoutAmount();

	/// \brief 查询标的券数量
	int QryUnderlying();

	/// \brief 查询主席资金可用
	int QryAcctAvailFund();

	/// \brief 查询委托
	int ReqQueryEntrustList(unsigned long long index);
	/// \brief 查询委托成成交
	int ReqQueryEntrustExecution(unsigned long long index);

    // \brief 查询账户内部，交易所划转记录
    int ReqQueryOutFundAccountAmountNodeDetail();

private:
	///	\brief	连接消息的回调
	virtual void OnConnected(TShengliStockErrNoType errNo, const char* pErrStr);
	///	\brief	连接断开消息的回调
	virtual void OnDisconnected(TShengliStockErrNoType errNo, const char* pErrStr);
	/// \brief 查询连接断开消息的回调
	virtual void OnQueryDisconnected(TShengliStockErrNoType errNo, const char* pErrStr);

	///	\brief	登录消息的回调
	virtual void OnRspUserLogon(CShengliStockRespUserLoginField* pLogon, int nRequestID);
	///	\brief	修改密码响应回调
	virtual void OnRspChangePassword(CShengliStockRespChangePwdField* pChangePwd, int nRequestID);
	///	\brief	查询客户号列表的返回事件
	virtual void OnRspQueryClientId(CShengliStockClientIDListField* pClientInfo, int nRequestID, bool bIsLast);
	///	\brief	查询资金账户列表的返回事件
	virtual void OnRspQueryAccount(CShengliStockAccountListField* pAccountInfo, int nRequestID, bool bIsLast);
	///	\brief	查询合约列表的返回事件
	virtual void OnRspQuerySymbol(CShengliStockNormalSecurityCodeField* pSymbolInfo, int nRequestID, bool bIsLast);
	///	\brief	查询ETF成份股查询的返回事件
	virtual void OnRspQueryETFMember(CShengliStockEtfMemberField* pEtfMember, int nRequestID, bool bIsLast);
	///	\brief	查询期权细节的返回事件
	virtual void OnRspQueryOptionDetail(CShengliStockOptionSecurityCodeField* pOption, int nRequestID, bool bIsLast);
	///	\brief	查询帐户交易费用的返回事件 
	virtual void OnRspQueryAccountTradeFee(CShengliStockAccountTradeFeeField* pFee, int nRequestID, bool bIsLast);
	///	\brief	查询仓位列表的返回事件
	virtual void OnRspQueryNormalPosition(CShengliStockNormalPositionField* pPos, int nRequestID, bool bIsLast);
	/// 查询仓位列表的期权仓位返回事件
	virtual void OnRspQueryOptionPosition(CShengliStockOptionPositionField* pPos, int nRequestID, bool bIsLast);
	/// 查询仓位列表的期权组合策略仓位返回事件
	virtual void OnRspQueryOptionCombStrategyPosition(CShengliStockOptionCombStrategyPositionField* pPos, int nRequestID, bool bIsLast);
	///	\brief	订单rewind的返回事件
	virtual void OnRtnOrderRewind(CShengliStockOrderAcceptedField* pOrder, int nRequestID);
	///	\brief	成交rewind的返回事件
	virtual void OnRtnExecRewind(CShengliStockOrderExecedField* pExec, int nRequestID);
	///	\brief	撤单请求rewind响应
	virtual void OnRtnCxlReqRewind(CShengliStockOrderCxledField* pCxlReq, int nRequestID);
	///	\brief	客户号订单rewind完成的返回事件
	virtual void OnRtnOrderRewindFinish(CShengliStockOrderRewindFinishField* pOrderFinish, int nRequestID);
	///	\brief	成交rewind完成的返回事件
	virtual void OnRtnExecRewindFinish(CShengliStockExecRewindFinishField* pExecFinish, int nRequestID);
	///	\brief	撤销请求rewind完成的返回事件
	virtual void OnRtnCxlReqRewindFinish(CShengliStockCxlReqRewindFinishField* pCxlReqFinish, int nRequestID);
	///	\brief	客户号资金状态查询的返回事件
	virtual void OnRspQueryClientBpStatus(CShengliStockBpStatusField* pBpInfo, int nRequestID, bool bIsLast);
	///	\brief	交易所连接查询的返回事件
	virtual void OnRspQueryMarketSession(CShengliStockExchangeConnectField* pSession, int nRequestID, bool bIsLast);
	///	\brief	交易所状态变化通知事件
	virtual void OnRtnMarketStatusChangeReport(CShengliStockExchangeStatusReportField* pReport);
	///	\brief	订单接受的返回事件
	virtual void OnRtnOrderAccepted(CShengliStockOrderAcceptedField* pAccept);
	///	\brief	订单拒绝的返回事件
	virtual void OnRtnOrderRejected(CShengliStockOrderRejectedField* pReject);
	///	\brief	成交回报的返回事件
	virtual void OnRtnOrderExecuted(CShengliStockOrderExecedField* pExec);
	///	\brief	撤单成功的返回事件
	virtual void OnRtnOrderCxled(CShengliStockOrderCxledField* pCxled);
	///	\brief	撤单拒绝的返回事件
	virtual void OnRtnOrderCxlRejected(CShengliStockOrderCxlRejectedField* pCxlRejected);
	///	\brief	ETF申购赎回成交的返回事件
	virtual void OnRtnETFExecuted(CShengliStockEtfExecHeadField* pHead, CShengliStockEtfExecBodyField* pBody, bool bIsLast);
	///	\brief	查询股东账户列表的返回事件
	virtual void OnRspQueryTradeAccountList(CShengliTradeAccountListField * pTradeAccount, int nRequestID, bool bIsLast);
	///	\brief	OpStation回报的返回事件
	virtual void OnRecvOpStationReportMsg(CShengliOpStationReportResp* p_Field);
	/// \brief	查询风控门限值的返回事件
	virtual void OnRspQueryRiskRuleThresholds(CShengliStockReqQueryRiskThresholdValueRespField* pRsp, int nRequestID, bool bIsLast);
	/// \brief	查询风控实时累加值的返回事件
	virtual void OnRspQueryRiskRuleAccumulate(CShengliStockReqQueryRiskValueRespField* pRsp, int nRequestID, bool bIsLast);
	/// \brief 查询旁路风控实时值的返回事件
	virtual void OnRspQueryAcctMonitorValue(CShengliStockReqQueryAcctMonitorValueRespField* pResp, int nRequestID, bool bIsLast);

	///回复查询出入金列表回调
	virtual void OnRspQueryCashInOutList(CShengliStockRespCashInOutField* p_Field, int nRequestID, bool bIsLast);

	virtual void OnRspPushCashInOut(CShengliStockRespCashInOutField* p_Field);

	/// 中继提交采集信息返回消息回调
	virtual void OnRspProxySubmitInfo(CShengliStockRspInfoField *pRspInfo, int nRequestId);


	/// 订阅交易所订单单号回复
	virtual void OnRspSubscribeInfo(CShengliStockRespSubscribeField *p_Field, int nRequestID);

	/// 推送交易所订单单号消息
	virtual void OnRspPushMktCltOrdIDMsg(CShengliStockRespMktCltOrdIDField * p_Field);

	/// 推送通用信息
	virtual void OnRspCommonMsg(CShengliStockCommonMsgField* p_Field);

	///期权做市订单接受的返回事件
	virtual void OnRtnQuoteOrderAccepted(CShengliStockQuoteOrderAcceptedField* pAccept);

	///期权做市订单交易所接受的返回事件
	virtual void OnRtnQuoteOrderExchAccepted(CShengliStockQuoteOrderExchAcceptedField* pAccept);

	///期权做市订单拒绝的返回事件
	virtual void OnRtnQuoteOrderRejected(CShengliStockQuoteOrderRejectedField* pReject);

	///期权做市成交回报的返回事件
	virtual void OnRtnQuoteOrderExecuted(CShengliStockQuoteOrderExecedField* pExec);

	///期权做市撤单成功的返回事件
	virtual void OnRtnQuoteOrderCxled(CShengliStockQuoteOrderCxledField* pCxled);

	///期权做市撤单拒绝的返回事件
	virtual void OnRtnQuoteOrderCxlRejected(CShengliStockQuoteOrderCxlRejectedField* pCxlRejected);

	///报价单回滚完成返回事件
	virtual void OnRtnQuoteOrderRewindFinish(CShengliStockQuoteOrderRewindFinishField* pRewindFinish);

	///查询合约保证金返回事件
	virtual void OnRspQuerySymbolMarginInfo(CShengliStockQuerySymbolMarginInfoRespField* pResp, int nRequestID, bool bIsLast);

	///查询合约费用返回事件
	virtual void OnRspQuerySymbolFeeInfo(CShengliStockQuerySymbolFeeInfoRespField* pResp, int nRequestID, bool bIsLast);

	///查询签约银行返回事件
	virtual void OnRspQuerySigningBankInfo(CShengliStockQuerySigningBankInfoRespField* pResp, int nRequestID, bool bIsLast);

	///查询银行余额返回事件
	virtual void OnRspQueryBankBalanceInfo(CShengliStockQueryBankBalanceInfoRespField* pResp, int nRequestID);

	///银转衍返回事件
	virtual void OnRspOneStepTransferInCashInfo(CShengliStockOneStepTransferInCashRespField * pResp , int nRequestID);

	///衍转银返回事件
	virtual void OnRspOneStepTransferOutCashInfo(CShengliStockOneStepTransferOutCashRespField* pResp, int nRequestID);
	
	///查询委托方式列表 
	virtual void OnRspDelegateTypeList(CShengliStockQueryDeletageTypeRespField* pResp, int nRequestID, bool bIsLast) ;

	///主席标的券划转回调事件
	virtual void OnRspFrozenUnderlyingSymbolQty(CShengliStockFrzUnderlyingSymbolQtyField* pResp, int nRequestID);

	//同主席资金划拨返回事件
	virtual void OnRtnInOutFundAccountMargin(CShengliStockInOutFundAccountAmountField* pResp, int nRequestID);

	//查询主席标的券数量回调事件
	virtual void OnRspQueryUnderlyingSymbolQty(CShengliStockUnderlyingSymbolQtyField* pUnderlyingSymbolQty, int nRequestID);

	//查询主席账户资金可用回调事件
	virtual void OnRspQueryChairmanAcctAvailBp(CShengliStockQryChairmanAcctAvailBpRespFiled* pChairAcctAvailBp, int nRequestID);

    ///查询委托返回事件
    virtual void OnRtnQueryEntrustList(CShengliStockRespQueryEntrustField *pField, bool bIsLast);

    ///查询委托成交返回事件
    virtual void OnRtnQueryEntrustExecution(CShengliStockRespQueryEntrustExecutionField *pField, bool bIsLast);

    //查询向交易节点资金划转回调
    virtual void OnQueryOutFundAccountAmountNode(CShengliStockTrasnQueryBpDetailField* pFields, int nRequestID, bool bIsLast);

private:
    CShengliStockTraderApi *    m_tradeApi;   ///< EES交易API接口
    T_DLL_HANDLE                m_handle;     ///< EES交易API句柄
    FuncDestroyShengliOptTraderApi m_distoryFun; ///< EES交易API动态库销毁函数

    string						m_traderServerIp;		///< 交易服务器IP地址
	int							m_traderServerPort;		///< 交易服务器端口

	string						m_queryServerIp;		///< 查询服务器地址
	int							m_queryServerPort;		///< 查询服务器地址	

	long long int 				m_request_id;			///< 随着时间变化

	string						m_logonId;				///< 登录交易服器编号
	string						m_logonPwd;				///< 登录交易服器密码

	string                      m_clinetId;             ///< 客户号
	string                      m_fundAccount;
	string						m_local_mac;			///< 本机MAC地址

	string						m_app_id;
	string						m_auth_code;

	int                         m_userID;               ///< 用户ID

	char						m_delegateType;			///< 委托方式
	
	string						m_opstation_info;		///< 站点信息

	unsigned int				m_RequestNum;
	unsigned long long			m_CurCursorMark;		///< 委托查询定位串
	int 						m_cur_index;
	int							m_single_RequestNum;	///< 单次查询委托请求数量
};
