#include "EESTraderDemo.h"
#include <iostream>
#include <stdio.h>

#include "../include/trade/C++/shengli_systeminfo.h"

#include <string>
using namespace std;

using std::cout;
using std::cin;
using std::endl;

#ifdef SHENGLI_WINDOWS
#ifdef WIN64
	#ifdef _DEBUG	// debug 64
		#define SHENGLI_OPT_TRADE_API_NAME "RemStockTradeApiD.1.8.dll"
	#else			// release 64
		#define SHENGLI_OPT_TRADE_API_NAME "RemStockTradeApi.1.8.dll"
	#endif
#else
	#ifdef _DEBUG // debug 32
		#define SHENGLI_OPT_TRADE_API_NAME "RemStockTradeApiD32.1.8.dll"
	#else		  // release 32
		#define SHENGLI_OPT_TRADE_API_NAME "RemStockTradeApi32.1.8.dll"
	#endif
#endif
#endif



#ifndef SHENGLI_WINDOWS
#include <sys/time.h>
#include <time.h>
#else
#include <sys/timeb.h>

int gettimeofday(struct timeval* tp, struct timezone * tzp)
{
	struct timeb timebuffer;
	ftime(&timebuffer);
	tp->tv_sec = (long)timebuffer.time;
	tp->tv_usec = timebuffer.millitm * 1000;

	return 0;
}
#endif


#ifndef REM_API_VERSION
#	define 	REM_API_VERSION 8
#endif 


template<typename T>
T GetInputValue(string desc)
{
	cout << desc;

	T val;
	cin >> val;
	return val;
}

#define SHOW_HELP					"help"
#define REQ_LOGON					"logon"
#define PROXY_LOGON					"proxy_logon"
#define PROCY_SUBMIT_CAP_INFO		"proxy_submit_cap"

#define CHANGE_PWD					"change_pwd"
#define QUERY_CLIENT_ID_LIST		"qry_client"
#define QUERY_ACCOUNT_LIST			"qry_account"
#define QUERY_TRADE_ACCOUNT_LIST	"qry_trade_acct"
#define QUERY_SYMBOL_LIST			"qry_symbol"
#define QUERY_ETF_MEMBER			"qry_etf_member"
#define QUERY_OPTION_DETAIL			"qry_option_detail"
#define QUERY_NORMAL_POSITION		"qry_normal_pos"
#define QUERY_OPTION_POSITION		"qry_option_pos"
#define QUERY_CLIENT_BP_STATUS		"qry_client_bp"
//#define QUERY_MARKET_SESSION		""
#define RESEND_LOGON_MSG			"relogon"
#define ENTER_ORDER					"order"
#define ENTER_QUOTE_ORDER			"quote_order"
#define BATCH_QUOTE_ORDER			"batch_quote_order"
#define CXL_ORDER					"cxl_order"
#define CXL_QUOTE_ORDER				"cxl_quote_order"
#define QUIT						"quit"
#define RECONN						"reconn"
#define OPSTATION_REPORT			"qry_opstation"
#define REWIND_TRADING_INFO			"rewind_trading"

#define	ORDER_COMB_CREATE			"create_comb_order"
#define ORDER_COMB_RELIEVE			"relieve_comb_order"
#define ORDER_COMB_EXERCISE			"comb_exercise_order"
#define QUERY_CASH_INOUT			"qry_cash_inout"
#define QUERY_RISK_RULE_THRESHOLDS	"qry_risk_rule_thresholds"
#define QUERY_RISK_RULE_ACCUMULATE	"qry_risk_rule_accumulate"
#define QUERY_RISK_MONITOR_VALUE    "qry_risk_monitor_value"
#define QUERY_SYMBOL_MARGIN_INFO	"qry_symbol_margin_info"
#define QUERY_SYMBOL_FEE_INFO       "qry_symbol_fee_info"

/* 主柜交互接口 */
#define REQ_FRZ_UNDERLYING     "req_frz_underlying"	    // 冻结解冻标的
#define INOUT_AMOUNT           "inout_amount"           // 出入金划转
#define QRY_UNDERLYING         "qry_underlying"         // 查询标的情况
#define QRY_ACCT_AVAIL_FUND	   "qry_acct_avail_fund"	// 查询主席账户资金可用

#define QUERY_SIGNING_BANK_INFO     "qry_signing_bank_info"
#define QUERY_BANK_BALANCE_INFO     "qry_bank_balance_info"
#define REQ_ONE_STEP_TRANSFER_IN_CASH		"req_one_step_transfer_in_cash"
#define REQ_ONE_STEP_TRANSFER_OUT_CASH		"req_one_step_transfer_out_cash"

#define REQ_QUERY_DELETAGE_INFO			"qry_delegate_list"

#define TEST_LCOAL_CAP				"test_local_cap"

#define NODE_OUT_BP					"node_out_bp"

#define SUBSCRIBE					"subscribe"
#define RewindQuoteOrder			"rewind_quote_order"
#define QUERY_ENTRUST				"qry_entrust"
#define QUERY_EXECUTION				"qry_execution"

#define QueryOutFundAcctAmountDetail		"query_out_fund_acct_amount_detail"

void show_help()
{
	printf("\n");
	printf("This Is A Show Demo\n");
	printf("\t%s \t\tsend logon msg\n", REQ_LOGON);
	printf("\t%s \t\tResend Logon Msg , not proxy logon\n", RESEND_LOGON_MSG);

	printf("\t%s \t\tsend proxy logon msg\n", PROXY_LOGON);
	printf("\t%s \t\tsend proxy submit capture client info\n", PROCY_SUBMIT_CAP_INFO);
	printf("\t%s \t\ttest local encrypt info \n", TEST_LCOAL_CAP);

	printf("\t%s \t\tShow Help\n", SHOW_HELP);
	printf("\t%s \t\tSubscribe\n", SUBSCRIBE);
	printf("\t%s \t\tQuery Cash InOut\n", QUERY_CASH_INOUT);
	printf("\t%s \t\tQuery Client Id List\n", QUERY_CLIENT_ID_LIST);
	printf("\t%s \t\tQuery Account List\n", QUERY_ACCOUNT_LIST);
	printf("\t%s \t\tQuery Symbol List\n", QUERY_SYMBOL_LIST);
	printf("\t%s \t\tQuery ETF Member\n", QUERY_ETF_MEMBER);
	printf("\t%s \t\tQuery Option Detail\n", QUERY_OPTION_DETAIL);
	//	printf("%s \t\tQuery Account Trade Fee\n");
	printf("\t%s \t\tQuery normal Position\n", QUERY_NORMAL_POSITION);
	printf("\t%s \t\tQuery option Position\n", QUERY_OPTION_POSITION);
	printf("\t%s \t\tRewind Trading Info\n", REWIND_TRADING_INFO);
	printf("\t%s \t\tRewind Quote Order\n", RewindQuoteOrder);
	printf("\t%s \t\tQuery Client Bp Status\n", QUERY_CLIENT_BP_STATUS);
	//	printf("\t%s \t\tQuery Market Session\n", QUERY_MARKET_SESSION);
	printf("\t%s \t\tReconn \n", RECONN);
	printf("\t%s \t\tOpStation report\n", OPSTATION_REPORT);
	printf("\t%s \t\tQuery Trade Account List\n", QUERY_TRADE_ACCOUNT_LIST);

	printf("\t%s \t\tnode out bp \n", NODE_OUT_BP);

	printf("\t____________________________\n");
	printf("\t%s \t\tEnter Order\n", ENTER_ORDER);
	printf("\t%s \t\tEnter Quote Order\n", ENTER_QUOTE_ORDER);
	printf("\t%s \t\tBATCH Quote Order\n", BATCH_QUOTE_ORDER);
	printf("\t%s \t\tCancel Order\n", CXL_ORDER);
	printf("\t%s \t\tCancel Quote Order\n", CXL_QUOTE_ORDER);
	printf("\t%s \t\tcreate comb strategy position.\n", ORDER_COMB_CREATE);
	printf("\t%s \t\trelieve comb strategy position.\n", ORDER_COMB_RELIEVE);
	printf("\t%s \t\tenter comb exercise order .\n", ORDER_COMB_EXERCISE);
	printf("\t%s \t\tQuery risk rule thresholds .\n", QUERY_RISK_RULE_THRESHOLDS);
	printf("\t%s \t\tQuery risk rule accumulate .\n", QUERY_RISK_RULE_ACCUMULATE);
	printf("\t%s \t\tQuery risk monitor value .\n", QUERY_RISK_MONITOR_VALUE);
	printf("\t%s \t\tQuery symbol marign info .\n", QUERY_SYMBOL_MARGIN_INFO);
	printf("\t%s \t\tQuery symbol fee info .\n", QUERY_SYMBOL_FEE_INFO);

	printf("\t%s \t\tReq frz underlying\n", REQ_FRZ_UNDERLYING);
	printf("\t%s \t\tInout amount\n", INOUT_AMOUNT);
	printf("\t%s \t\tQry underlying\n", QRY_UNDERLYING);
	printf("\t%s \t\tQry acct avail fund\n", QRY_ACCT_AVAIL_FUND);

	printf("\t%s \t\tQuery signing bank info .\n", QUERY_SIGNING_BANK_INFO);
	printf("\t%s \t\tQuery bank balance info .\n", QUERY_BANK_BALANCE_INFO);

	printf("\t%s \t\tRequest one step transfer in cash info.\n", REQ_ONE_STEP_TRANSFER_IN_CASH);
	printf("\t%s \t\tRequest one step transfer out cash info.\n", REQ_ONE_STEP_TRANSFER_OUT_CASH);

	printf("\t%s \t\tRequest query delegate type list\n", REQ_QUERY_DELETAGE_INFO ) ;
	printf("\t%s \t\tQuery entrust list.\n", QUERY_ENTRUST);
	printf("\t%s \t\tQuery entrust execution.\n", QUERY_EXECUTION);

    printf("\t%s \t\tQuery out fund acct amount detail\n", QueryOutFundAcctAmountDetail);

	printf("\t%s \t\tQuit\n", QUIT);
	printf("\n");
}

TraderDemo::TraderDemo(void)
{
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	m_request_id = timestamp.tv_sec * 1000000 + timestamp.tv_usec;
	m_request_id &= 0x0FFFFFFF;

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	shengli_get_system_terminal_info(buffer, sizeof(buffer));
	m_opstation_info = buffer;
	m_RequestNum = 0;
    m_CurCursorMark = 0;
	m_single_RequestNum = 10;
}

TraderDemo::~TraderDemo(void)
{
}

void TraderDemo::Run()
{
	InputParam();

	bool ret = Init();
	if (!ret)
	{
		Pause();
		return;
	}

	char buf[1024];

	bool running = true;
	while (running)
	{
		printf("Demo : ");
		fflush(stdout);
		fgets(buf, sizeof(buf), stdin);
		int len = strlen(buf);
		if (len <= 0)
		{
			continue;
		}
		buf[len - 1] = 0x00;

		string cmd = buf;


		if (cmd == SHOW_HELP)  show_help();
		if (cmd == QUERY_CASH_INOUT)   EnterCashInOutList();
		if (cmd == QUERY_CLIENT_ID_LIST)   ReqQueryClientIdList();
		if (cmd == QUERY_ACCOUNT_LIST)   ReqQueryAccountList();
		if (cmd == QUERY_SYMBOL_LIST)   ReqQuerySymbolList();
		if (cmd == QUERY_ETF_MEMBER)   ReqQueryETFMember();
		if (cmd == QUERY_OPTION_DETAIL)   ReqQueryOptionDetail();
		if (cmd == QUERY_NORMAL_POSITION)   ReqQueryNormalPosition();
		if (cmd == QUERY_OPTION_POSITION)   ReqQueryOptionPosition();
		if (cmd == REWIND_TRADING_INFO)   ReqRewindTradingInfo();
		if (cmd == QUERY_CLIENT_BP_STATUS)   ReqQueryBpList();
		//	if ( cmd == QUERY_MARKET_SESSION)   ReqQueryMarketSession();
		if (cmd == ENTER_ORDER)   EnterOrder();
		if (cmd == ENTER_QUOTE_ORDER)	EnterQuoteOrder();
		if (cmd == BATCH_QUOTE_ORDER)	BatchEnterQuoteOrder();
		if (cmd == CXL_ORDER)   CancelOrder();
		if (cmd == CXL_QUOTE_ORDER) CancelQuoteOrder();
		if (cmd == RECONN)   ReconnTest();
		if (cmd == OPSTATION_REPORT)   OpStationReport();
		if (cmd == RESEND_LOGON_MSG)   ResendLogonMsg();
		if (cmd == QUERY_TRADE_ACCOUNT_LIST)  ReqQueryTradeAccountList();

		if (cmd == ORDER_COMB_CREATE)  EnterCreateCombStrategyOrder();
		if (cmd == ORDER_COMB_RELIEVE) EnterRelieveCombStrategyOrder();
		if (cmd == ORDER_COMB_EXERCISE) EnterCombExerciseOrder();
		if (cmd == QUERY_RISK_RULE_THRESHOLDS) ReqQueryRiskRuleThresholds();
		if (cmd == QUERY_RISK_RULE_ACCUMULATE) ReqQueryRiskRuleAccumulateVal();
		if (cmd == QUERY_RISK_MONITOR_VALUE) ReqQueryRiskMonitorValue();
		if (cmd == QUERY_SYMBOL_MARGIN_INFO) ReqQuerySymbolMarginInfo();
		if (cmd == QUERY_SYMBOL_FEE_INFO) ReqQuerySymbolFeeInfo();

		if (cmd == REQ_FRZ_UNDERLYING) ReqFrzUnderlying();
		if (cmd == INOUT_AMOUNT) InoutAmount();
		if (cmd == QRY_UNDERLYING) QryUnderlying();
		if (cmd == QRY_ACCT_AVAIL_FUND) QryAcctAvailFund();

		if (cmd == QUERY_SIGNING_BANK_INFO) ReqQuerySigningBankInfo();
		if (cmd == QUERY_BANK_BALANCE_INFO) ReqQueryBankBalanceInfo();

		if (cmd == REQ_ONE_STEP_TRANSFER_IN_CASH) ReqOneStepTransferInCash(); 
		if (cmd == REQ_ONE_STEP_TRANSFER_OUT_CASH) ReqOneStepTransferOutCash();

		if (cmd == REQ_LOGON)	 ReqUserLogon();
		if (cmd == PROXY_LOGON) ProxyReqLogon();
		if (cmd == PROCY_SUBMIT_CAP_INFO)  ProxySubmitCapInfo();
		if (cmd == TEST_LCOAL_CAP) TestLocalCap();

		if (cmd == NODE_OUT_BP) NodeOutBp();
		if (cmd == SUBSCRIBE) Subscribe();
		if (cmd == RewindQuoteOrder) ReqRewindQuoteOrder();
		if ( cmd == REQ_QUERY_DELETAGE_INFO ) ReqQueryDelegateInfo();
		if (cmd == QUERY_ENTRUST) ReqQueryEntrustList(0);
		if (cmd == QUERY_EXECUTION) ReqQueryEntrustExecution(0);

		if ( cmd == QueryOutFundAcctAmountDetail) ReqQueryOutFundAccountAmountNodeDetail();

		if (cmd == QUIT)   running = false;

	}

	Close();
}

bool TraderDemo::Init()
{
	bool ret = LoadEESTrader();
	if (!ret)
	{
		return false;
	}

	char ch_trade_front_addr[128] = { 0 };
	sprintf(ch_trade_front_addr, "tcp://%s:%d", m_traderServerIp.c_str(), m_traderServerPort);

	char ch_query_front_addr[128] = { 0 };
	sprintf(ch_query_front_addr, "tcp://%s:%d", m_queryServerIp.c_str(), m_queryServerPort);
	m_tradeApi->RegisterFront(ch_trade_front_addr, ch_query_front_addr);

	m_tradeApi->RegisterSpi(this);


	CShengliStockConnConfigField conn;
	// conn.TradeRecvNum = -1;
//	conn.TradeProcNum = 2;
	// conn.QueryRecvNum = -1;
//	conn.QueryProcNum = 4;
//	conn.TradeSyncMethod = SOCKET_THREAD_ASYNC;
//	conn.QuerySyncMethod = SOCKET_THREAD_ASYNC;
//	conn.TradeRecvSleepTime = 2000000;
//	conn.TradeProcSleepTime = 0;
//	conn.QueryRecvSleepTime = 3000000;
//	conn.QueryProcSleepTime = 0;
	conn.IsReconn = NOT_AUTO_RECONN;
	conn.ReconnTime = 5;
//
	m_tradeApi->InitSocketThreadMode(&conn);

	m_tradeApi->Init();
	return true;
}

void TraderDemo::Close()
{
	if (m_tradeApi)
	{
		m_tradeApi->DisConnServer();
	}

	UnloadEESTrader();
}

void TraderDemo::DemoSleep()
{
#ifdef SHENGLI_WINDOWS

	Sleep(1000);
#else

	usleep(1000000);

#endif

}

void TraderDemo::Pause()
{
	string str_temp;
	printf("\nPress Any Key To Continue......\n");
	cin >> str_temp;
}

bool TraderDemo::LoadEESTrader()
{
#ifdef SHENGLI_WINDOWS

	return Windows_LoadEESTrader();

#else

		return Linux_LoadEESTrader();

#endif
}

void TraderDemo::UnloadEESTrader()
{
#ifdef SHENGLI_WINDOWS

	return Windows_UnloadEESTrader();

#else

	return Linux_UnloadEESTrader();

#endif
}

bool TraderDemo::Windows_LoadEESTrader()
{
#ifdef SHENGLI_WINDOWS

	m_handle = LoadLibrary(SHENGLI_OPT_TRADE_API_NAME);
	if (!m_handle)
	{
		printf("Load %s Failed %d\n", SHENGLI_OPT_TRADE_API_NAME, ::GetLastError());
		return false;
	}

	FuncCreateShengliOptTraderApi createFun = (FuncCreateShengliOptTraderApi)GetProcAddress(m_handle, CREATE_SHENGLI_TRADER_API_NAME);
	if (!createFun)
	{
		printf("Get %s Addr Failed!\n", CREATE_SHENGLI_TRADER_API_NAME);
		return false;
	}

	m_distoryFun = (FuncDestroyShengliOptTraderApi)GetProcAddress(m_handle, DESTROY_SHENGLITRADER_API_NAME);
	if (!createFun)
	{
		printf("Get %s Addr Failed!\n", DESTROY_SHENGLITRADER_API_NAME);
		return false;
	}

	m_tradeApi = createFun("./");
	if (!m_tradeApi)
	{
		printf("Create REM Object Failed!\n");
		return false;
	}

#endif

	return true;
}

void TraderDemo::Windows_UnloadEESTrader()
{
#ifdef SHENGLI_WINDOWS

	if (m_tradeApi)
	{
		m_distoryFun(m_tradeApi);
		m_tradeApi = NULL;
		m_distoryFun = NULL;
	}

	if (m_handle)
	{
		FreeLibrary(m_handle);
		m_handle = NULL;
	}
#endif
}

bool TraderDemo::Linux_LoadEESTrader()
{
#ifndef SHENGLI_WINDOWS
	if (true)
	{
		m_handle = dlopen(SHENGLI_TRADER_DLL_1_8_NAME, RTLD_LAZY);
        if (!m_handle)
        {
            printf("Load %s Failed, err:%s.\n", SHENGLI_TRADER_DLL_1_8_NAME, dlerror());
            return false;
        }
    }

	FuncCreateShengliOptTraderApi createFun = (FuncCreateShengliOptTraderApi)dlsym(m_handle, CREATE_SHENGLI_TRADER_API_NAME);
	if (!createFun)
	{
		printf("Get %s Addr Failed!\n", CREATE_SHENGLI_TRADER_API_NAME);
		return false;
	}

	m_distoryFun = (FuncDestroyShengliOptTraderApi)dlsym(m_handle, DESTROY_SHENGLITRADER_API_NAME);
	if (!createFun)
	{
		printf("Get %s Addr Failed!\n", DESTROY_SHENGLITRADER_API_NAME);
		return false;
	}

	m_tradeApi = createFun(NULL);
	if (!m_tradeApi)
	{
		printf("Create REM Object Failed!\n");
		return false;
	}
	printf(" api version :%s\n", m_tradeApi->GetVersion());

#endif

	return true;
}

void TraderDemo::Linux_UnloadEESTrader()
{
#ifndef SHENGLI_WINDOWS
	if (m_tradeApi)
	{
		m_distoryFun(m_tradeApi);
		m_tradeApi = NULL;
		m_distoryFun = NULL;
	}

	if (m_handle)
	{
		dlclose(m_handle);
		m_handle = NULL;
	}
#endif
}

void TraderDemo::InputParam()
{
	// m_traderServerIp = "10.1.59.11";
	// m_traderServerPort = 20000;

    // m_queryServerIp = "10.1.59.11";
    // m_queryServerPort = 20001;
    m_traderServerIp   = "10.1.59.113";
    m_traderServerPort = 24000;

    m_queryServerIp   = "10.1.59.113";
    m_queryServerPort = 24001;

    m_logonId = "99990001";
	m_logonPwd = "1";
	m_clinetId = "99990001";
	m_fundAccount = "77770001";
	//m_logonType = 0;


	m_delegateType = '@';//濮旀墭鏂瑰紡
	m_app_id = "1";
	m_auth_code = "1";

	//m_traderServerIp = "10.1.51.152";
	//m_traderServerPort = 20000;

	//m_queryServerIp = "10.1.51.35";
	//m_queryServerPort = 20001;

	//m_logonId = "99990002";
	//m_logonPwd = "1";
	m_local_mac = "00:00:00:00:00:00";
	//m_clinetId = "99990002";
	//m_fundAccount = "77770002";



	cout << "Trade Svr IP : " << m_traderServerIp << endl;
	cout << "Trade Svr Port : " << m_traderServerPort << endl;
	cout << "Query Svr IP : " << m_queryServerIp << endl;
	cout << "Query Svr Port : " << m_queryServerPort << endl;
	cout << "Login ID : " << m_logonId << endl;
	cout << "Login Password : " << m_logonPwd << endl;

	cout << "MAC(Format 00-01-02-03-04-05) : " << endl;
	cout << "Client Id : " << m_clinetId << endl;
	cout << "Fund Account : " << m_fundAccount << endl;

}

int TraderDemo::ReqUserLogon()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.LogonID, m_logonId.c_str());
	strcpy(req.Password, m_logonPwd.c_str());
	strcpy(req.ClientProdInfo, "Test");
	strcpy(req.ClientMac, m_local_mac.c_str());
	strcpy(req.AppID, m_app_id.c_str());
	strcpy(req.AuthCode, m_auth_code.c_str());
	// req.LogonType = 0;
	// req.DelegateType = 'Y';
	// m_delegateType = 'Y';

	return m_tradeApi->ReqUserLogon(&req, 10086);
}

/// 浠ｇ悊鐧诲綍 
int TraderDemo::ProxyReqLogon()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.LogonID, m_logonId.c_str());
	strcpy(req.Password, m_logonPwd.c_str());
	strcpy(req.ClientProdInfo, "Test");
	strcpy(req.ClientMac, m_local_mac.c_str());
	strcpy(req.AppID, m_app_id.c_str());
	strcpy(req.AuthCode, m_auth_code.c_str());
    req.LogonType    = 0;

    return m_tradeApi->ReqUserProxyLogon(&req, 10086);
}

/// 浠ｇ悊鎻愪氦閲囬泦淇℃伅
int TraderDemo::ProxySubmitCapInfo()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}
	CShengliStockProxySubmitDataField  reqMsg;

	strcpy(reqMsg.AppID, "1");
	strcpy(reqMsg.AuthCode, "1");
	strcpy(reqMsg.TerminalPubNetIP, "ip");
	reqMsg.TerminalPubNetPort = 1234;
	strcpy(reqMsg.TerminalLoginTime, "time");
	reqMsg.ExceptionFlag = '0';
	strcpy(reqMsg.RelayID, "relay_id");

	char buf[2048] = { 0 };
	int len = shengli_get_encrypt_local_symbolinfo(ENCRYPT_FLAG_TEST, NULL, buf, 2048);
	buf[len] = 0x00;
	strcpy(reqMsg.TerminalSystemInfo, buf);
	strcpy(reqMsg.FundAccount, "acct");

	return m_tradeApi->ReqProxySubmitInfo(&reqMsg, 1000);
}

int TraderDemo::TestLocalCap()
{
	char buf[2048];

	int n_ret = shengli_get_encrypt_local_symbolinfo(ENCRYPT_FLAG_TEST, "10.1.1.1", buf, 2048);

	if (n_ret > 0)
		printf("%s\n", buf);
	else if (n_ret == 0)
		printf("cap error.\n");
	else if (n_ret < 0)
		printf("cncrypt error.\n");

	n_ret = shengli_get_encrypt_local_symbolinfo(ENCRYPT_FLAG_CFMMC, "10.1.1.1", buf, 2048);

	if (n_ret > 0)
		printf("%s\n", buf);
	else if (n_ret == 0)
		printf("cap error.\n");
	else if (n_ret < 0)
		printf("cncrypt error.\n");

	n_ret = shengli_get_encrypt_local_symbolinfo(ENCRYPT_FLAG_CFMMC, "", buf, 2048);

	if (n_ret > 0)
		printf("%s\n", buf);
	else if (n_ret == 0)
		printf("cap error.\n");
	else if (n_ret < 0)
		printf("cncrypt error.\n");

	n_ret = shengli_get_encrypt_local_symbolinfo(ENCRYPT_FLAG_CFMMC, NULL, buf, 2048);
	if (n_ret > 0)
		printf("%s\n", buf);
	else if (n_ret == 0)
		printf("cap error.\n");
	else if (n_ret < 0)
		printf("cncrypt error.\n");

	return 0;
}

int TraderDemo::NodeOutBp()
{
	CShengliStockTrasnBpReqField reqMsg;

	reqMsg.UserID = m_userID;
	strcpy(reqMsg.ClientID, "333");
	strcpy(reqMsg.FundAccount, "22222");
	reqMsg.FundAccountType = 2;
	reqMsg.Exchange = 100;
	reqMsg.RequestID = 10;
	reqMsg.Amount = 10;

	return m_tradeApi->ReqOutFundAccountAmountNode(&reqMsg, 0);
}



int TraderDemo::ReqChangePassword()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	string oldMd5Pwd = GetInputValue<string>("Old Password:");
	string newMd5Pwd = GetInputValue<string>("New Password:");

	CShengliStockReqChangePwdField req;
	memset(&req, 0, sizeof(CShengliStockReqChangePwdField));
	req.UserID = m_userID;
	strcpy(req.OldMd5Pwd, oldMd5Pwd.c_str());
	strcpy(req.NewMd5Pwd, newMd5Pwd.c_str());

	return m_tradeApi->ReqChangePassword(&req);
}

int TraderDemo::ReqQueryClientIdList()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqQueryClientIDListField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryClientIDListField));
	req.UserID = m_userID;
	return m_tradeApi->ReqQueryClientIdList(&req, 0);
}

int TraderDemo::ReqQueryAccountList()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqQueryAccountListField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryAccountListField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());
	return m_tradeApi->ReqQueryAccountList(&req, 0);
}

int TraderDemo::ReqQuerySymbolList()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqQuerySecurityCodeField req;
	memset(&req, 0, sizeof(CShengliStockReqQuerySecurityCodeField));
	req.UserID = m_userID;
	req.SecurityType = 0;
	return m_tradeApi->ReqQuerySymbolList(&req, 0);
}

int TraderDemo::ReqQueryETFMember()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	int exchId = 101;
	string symbol = "159441";

	CShengliStockReqQueryEtfMemberField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryEtfMemberField));
	req.UserID = m_userID;
	req.ExchID = exchId;
	strcpy(req.SecurityCode, "159441");

	return m_tradeApi->ReqQueryETFMember(&req, 0);
}

int TraderDemo::ReqQueryOptionDetail()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	int exchId = GetInputValue<int>("Exchange ID:");
//	string symbol = GetInputValue<string>("Security Code:");

	CShengliStockReqQueryOptionDetailField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryOptionDetailField));
	req.UserID = m_userID;
	req.ExchID = exchId;
//	strcpy(req.UnderlyingSecurityCode, symbol.c_str());

	return m_tradeApi->ReqQueryOptionDetail(&req, 0);
}

int TraderDemo::ReqQueryAccountTradeFee()
{
	printf("not support");
	return 0;
	//if (!m_tradeApi)
	//{
	//	printf("Unavailable Trade Object\n");
	//	return -1;
	//}

	//CShengliStockReqQueryAccountTradeFeeField req;
	//memset(&req, 0, sizeof(CShengliStockReqQueryAccountTradeFeeField));
	//req.UserID = m_userID;
	//strcpy(req.ClientID, m_clinetId.c_str());

	//return m_tradeApi->ReqQueryAccountTradeFee(&req, 0);
}

int TraderDemo::ReqQueryNormalPosition()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqQueryPositionField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryPositionField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());

	return m_tradeApi->ReqQueryNormalPosition(&req, 0);
}
int TraderDemo::ReqQueryOptionPosition()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqQueryPositionField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryPositionField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());

	return m_tradeApi->ReqQueryOptionPosition(&req, 0);
}

int TraderDemo::ReqQueryBpList()
{
	CShengliStockReqQueryBpStatusField  req;
	memset(&req, 0, sizeof(CShengliStockReqQueryPositionField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());

	return m_tradeApi->ReqQueryClientBpStatus(&req, 0);
}

int TraderDemo::ReqRewindTradingInfo()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqTradeInfoRewindField req;
	memset(&req, 0, sizeof(CShengliStockReqTradeInfoRewindField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());

	return m_tradeApi->ReqRewindTradingInfo(&req, 0);
}

int TraderDemo::ReqQueryClientBpStatus()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqQueryBpStatusField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryBpStatusField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());

	return m_tradeApi->ReqQueryClientBpStatus(&req, 0);
}

int TraderDemo::ReqQueryMarketSession()
{
	printf("not support");
	return 0;

	// 	if (!m_tradeApi)
	// 	{
	// 		printf("Unavailable Trade Object\n");
	// 		return -1;
	// 	}
	// 
	// 	CShengliStockReqQueryExchSessionField req;
	// 	memset(&req, 0, sizeof(CShengliStockReqQueryExchSessionField));
	// 	req.UserID = m_userID;
	// 
	// 	return m_tradeApi->ReqQueryMarketSession(&req);
}

int TraderDemo::Subscribe()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockSubscribeField req;
	memset(&req, 0, sizeof(CShengliStockSubscribeField));
	req.UserID = m_userID;

	return m_tradeApi->ReqSubscribe(&req, 0);
}


int TraderDemo::ReqRewindQuoteOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockQuoteRewindReqField req;
	memset(&req, 0, sizeof(CShengliStockQuoteRewindReqField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());
	req.NextMsgIndex = 1;

	return m_tradeApi->ReqQuoteOrderRewind(&req);
}

int TraderDemo::OpStationReport()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliOpStationReportReq opstationReport;
	memset(&opstationReport, 0, sizeof(CShengliOpStationReportReq));

	while (1)
	{
		printf("please enter customer key:");
		fflush(stdout);
		fgets(opstationReport.CustomerKey, sizeof(opstationReport.CustomerKey), stdin);
		int len = strlen(opstationReport.CustomerKey);
		if (len <= 0)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	while (1)
	{
		printf("please enter opstation content(enter 'auto' auto collection opstation info):");
		fflush(stdout);
		fgets(opstationReport.OpStationContent, sizeof(opstationReport.OpStationContent), stdin);
		if (strncmp(opstationReport.OpStationContent, "auto", 4) == 0)
		{
			strcpy(opstationReport.OpStationContent, m_opstation_info.c_str());
			break;
		}
		int len = strlen(opstationReport.OpStationContent);
		if (len <= 0)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	m_tradeApi->ReqOpStationReport(&opstationReport);
	return 0;
}

int TraderDemo::ResendLogonMsg()
{
	return ReqUserLogon();
}

int TraderDemo::ReqQueryRiskRuleThresholds()
{
	if (m_tradeApi)
	{
		CShengliStockReqQueryRiskThresholdValueField req;
		memset(&req, 0, sizeof(CShengliStockReqQueryRiskThresholdValueField));
		memcpy(req.ClientID, "99991208", sizeof("99991208"));
		memcpy(req.FundAccount, "88881208", sizeof("88881208"));
		req.RiskRuleID = 34;
		m_tradeApi->ReqQueryRiskRuleThresholds(&req, 0);
	}
	return 0;
}

int TraderDemo::ReqQueryRiskRuleAccumulateVal()
{
	if (m_tradeApi)
	{
		CShengliStockReqQueryHeaderField req;
		memset(&req, 0, sizeof(CShengliStockReqQueryHeaderField));
		memcpy(req.ClientID, "99991208", sizeof("99991208"));
		memcpy(req.FundAccount, "88881208", sizeof("88881208"));
		req.QryRiskCount = 4;
		CShengliStockReqQueryRiskValueField risk_rule_val[4];
		memset(risk_rule_val, 0, sizeof(CShengliStockReqQueryRiskValueField) * req.QryRiskCount);
		risk_rule_val[0].RiskRuleID = 35;
		risk_rule_val[1].RiskRuleID = 48;
		risk_rule_val[2].RiskRuleID = 49;
		risk_rule_val[3].RiskRuleID = 34;

		m_tradeApi->ReqQueryRiskRuleAccumulateVal(&req, risk_rule_val, 0);
	}
	return 0;
}

int TraderDemo::ReqQueryRiskMonitorValue()
{
	if (m_tradeApi)
	{
		CShengliStockReqQueryAcctMonitorValueField req;
		memset(&req, 0, sizeof(req));
		memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
		memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));
		m_tradeApi->ReqQueryAcctMonitorValue(&req, 0);
	}
	return 0;
}

int TraderDemo::ReqQuerySymbolMarginInfo()
{
	if (m_tradeApi)
    {
        CShengliStockQuerySymbolMarginInfoReqField req;
        memset(&req, 0, sizeof(req));
        req.UserID = m_userID;
        memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));

		int exch_id = GetInputValue<int>("Exch id (100:sh 101:sz): ");
		if (exch_id != 100 && exch_id != 101)
		{
			puts("please enter correct exchange id info");
			return 0;
		}
		req.ExchID = exch_id;
        memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));

        std::string str_security_code = GetInputValue<string>("Security Code (enter 'all' is query total symbol): ");

		if (str_security_code != "all")
            memcpy(req.SecurityCode, str_security_code.c_str(), sizeof(req.SecurityCode));
			
        m_tradeApi->ReqQuerySymbolMarginInfo(&req, 0);
    }
    return 0;
}

int TraderDemo::ReqQuerySymbolFeeInfo()
{
	if (m_tradeApi)
	{
		CShengliStockQuerySymbolFeeInfoReqField req;
		memset(&req, 0, sizeof(req));
		req.UserID = m_userID;
		memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
		int exch_id = GetInputValue<int>("Exch id (100:sh 101:sz): ");
		if (exch_id != 100 && exch_id != 101)
		{
			puts("please enter correct exchange id info");
			return 0;
		}
		req.ExchID = exch_id;
		memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));

        std::string str_security_code = GetInputValue<string>("Security Code (enter 'all' is query total symbol): ");
		if (str_security_code != "all")
			memcpy(req.SecurityCode, str_security_code.c_str(), sizeof(req.SecurityCode));

		m_tradeApi->ReqQuerySymbolFeeInfo(&req, 0);
	}
	return 0;
}

int TraderDemo::ReqQuerySigningBankInfo()
{
	if (m_tradeApi)
	{
		CShengliStockQuerySigningBankInfoReqField req;
		memset(&req, 0, sizeof(CShengliStockQuerySigningBankInfoReqField));
		req.UserID = m_userID;
		memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
        int exch_id = GetInputValue<int>("Exch id (100:sh 101:sz): ");
        if (exch_id != 100 && exch_id != 101)
		{
			puts("please enter correct exchange id info");
			return 0;
		}
		req.ExchID = exch_id;
		req.Currency = '0';
		memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));
		int i_cubsbtrdid = GetInputValue<int>("CubsbTrdID (11:OutCash 12:InCash): ");
        if (i_cubsbtrdid == SHENGLI_STOCK_CUBSB_TRD_BANK_TO_DERIVE)
        {
            req.CubsbTrdID = SHENGLI_STOCK_CUBSB_TRD_BANK_TO_DERIVE;
        }
        else
		{
            req.CubsbTrdID = SHENGLI_STOCK_CUBSB_TRD_DERIVE_TO_BANK;
		}

		m_tradeApi->ReqQuerySigningBankInfo(&req, m_request_id++);
	}
	return 0;
}

int TraderDemo::ReqQueryBankBalanceInfo()
{
	if (m_tradeApi)
	{
		CShengliStockQueryBankBalanceInfoReqField req;
        memset(&req, 0, sizeof(CShengliStockQueryBankBalanceInfoReqField));
        req.UserID = m_userID;
		memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
        int exch_id = GetInputValue<int>("Exch id (100:sh 101:sz): ");
        if (exch_id != 100 && exch_id != 101)
		{
			puts("please enter correct exchange id info");
			return 0;
		}
		string BankCode;
		do
		{	
			BankCode = GetInputValue<string>("Bank code:");
			if (BankCode.size() != 4)
			{
				printf("Please enter 4 digits bank code. current error bank code [%s].\n", BankCode.c_str());
				continue;
			}
			break;

		}while(1);
		req.ExtOrg = atoi(BankCode.c_str());
		req.ExchID = exch_id;
		req.Currency = '0';
		memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));

		m_tradeApi->ReqQueryBankBalanceInfo(&req, m_request_id++);
	}
	return 0;
}

int TraderDemo::ReqOneStepTransferInCash()
{
	if (!m_tradeApi)
	{
        printf("Unavailable Trade Object\n");
        return -1;
	}

	CShengliStockOneStepTransferInCashReqField req;
	memset(&req, 0, sizeof(CShengliStockOneStepTransferInCashReqField));
	req.UserID = m_userID;
	memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
	memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));
    int exch_id  = GetInputValue<int>("Exch id (100:sh 101:sz): ");
    if (exch_id != 100 && exch_id != 101)
    {
        puts("please enter correct exchange id info");
        return 0;
    }
    req.ExchID = exch_id;
	req.Currency = '0';

	do 
	{
        req.TransAmt    = GetInputValue<double>("Transf amount: ");
		if (req.TransAmt.get_double() <= 0)
		{
			printf("Please enter greater than or equal to 0. current error amount [%lf].\n", req.TransAmt.get_double());
			continue;
		}
        string BankCode = GetInputValue<string>("Bank code:");
		if (BankCode.size() != 4)
		{
			printf("Please enter 4 digits bank code. current error bank code [%s].\n", BankCode.c_str());
			continue;
		}
		req.ExtOrg = atoi(BankCode.c_str());

		break;

    } while(1);

	m_tradeApi->ReqOneStepTransferInCash(&req, m_request_id++);

	return 0;
}


int TraderDemo::ReqOneStepTransferOutCash()
{
	if (!m_tradeApi)
	{
        printf("Unavailable Trade Object\n");
	    return -1;
	}

	CShengliStockOneStepTransferOutCashReqField req;
	memset(&req, 0, sizeof(CShengliStockOneStepTransferOutCashReqField));
	req.UserID = m_userID;
	memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
	memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));
    int exch_id  = GetInputValue<int>("Exch id (100:sh 101:sz): ");
    if (exch_id != 100 && exch_id != 101)
    {
        puts("please enter correct exchange id info");
        return 0;
    }
    req.ExchID = exch_id;
	req.Currency = '0';

	do 
	{
        req.TransAmt    = GetInputValue<double>("Transf amount: ");
		if (req.TransAmt.get_double() <= 0)
		{
			printf("Please enter greater than or equal to 0. current error amount [%lf].\n", req.TransAmt.get_double());
			continue;
		}
        string BankCode = GetInputValue<string>("Bank code:");
		if (BankCode.size() != 4)
		{
			printf("Please enter 4 digits bank code. current error bank code [%s].\n", BankCode.c_str());
			continue;
		}
		req.ExtOrg = atoi(BankCode.c_str());
		
		break;
    } while(1);
	

	m_tradeApi->ReqOneStepTransferOutCash(&req, m_request_id++);

	return 0;
}

int TraderDemo::ReqQueryDelegateInfo() 
{
	if (!m_tradeApi)
	{
        printf("Unavailable Trade Object\n");
	    return -1;
	}

	CShengliStockQueryDelegateTypeReqField req ;
	req.UserID = m_userID ;

	m_tradeApi->ReqDelegateTypeList(&req, 0 ) ; 

	return 0 ; 
}

int TraderDemo::ReqFrzUnderlying()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockFrzUnderlyingSymbolQtyReqField req;
	req.UserID = m_userID;
	memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
	string str_fund_acct;
	while(1)
	{
		str_fund_acct = GetInputValue<string>("fund account: ");
		if (!str_fund_acct.empty())
			break;
	}
	memcpy(req.FundAccount, str_fund_acct.c_str(), sizeof(req.FundAccount));
	req.ExchangeID = GetInputValue<int>("Exch id (100:sh 101:sz): ");
	req.FrzFlag = GetInputValue<char>("0:frz 1:unfrz: ");
	req.Quantity = GetInputValue<int>("enter quantity: ");
	string str_secu_code;
	while(1)
	{
        str_secu_code = GetInputValue<string>("security code: ");
		if (!str_secu_code.empty())
			break;
    }
	memcpy(req.SecurityCode, str_secu_code.c_str(), sizeof(req.SecurityCode));
	req.RequestID = ++m_request_id;

	m_tradeApi->ReqFrzUnderlyingSymbolQty(&req, req.RequestID);

	return 0;
}

int TraderDemo::InoutAmount()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockInOutFundAccountAmountReqField req;
	req.UserID = m_userID;
	memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
	req.ExchangeID = GetInputValue<int>("Exch id (100:sh 101:sz): ");
	memcpy(req.FundAccount, m_fundAccount.c_str(), sizeof(req.FundAccount));
	req.InOutFlag = GetInputValue<char>("0:in 1:out: ");
	req.Amount = GetInputValue<double>("inout amount: ");
	req.RequestID = ++m_request_id;

	m_tradeApi->ReqInOutFundAccountAmount(&req, req.RequestID);

	return 0;
}

int TraderDemo::QryUnderlying()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockReqUnderlyingSymbolQtyField req;
	req.UserID = m_userID;
	memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
    string str_fund_acct;
    while(1)
	{
		str_fund_acct = GetInputValue<string>("fund account: ");
		if (!str_fund_acct.empty())
			break;
	}
	memcpy(req.FundAccount, str_fund_acct.c_str(), sizeof(req.FundAccount));
	req.ExchangeID = GetInputValue<int>("Exch id (100:sh 101:sz): ");
    string str_secu_code;
    while(1)
	{
        str_secu_code = GetInputValue<string>("security code: ");
		if (!str_secu_code.empty())
			break;
    }
	memcpy(req.SecurityCode, str_secu_code.c_str(), sizeof(req.SecurityCode));
	req.RequestID = ++m_request_id;

	m_tradeApi->ReqQueryUnderlyingSymbolQty(&req, req.RequestID);

	return 0;
}

int TraderDemo::QryAcctAvailFund()
{
    if (!m_tradeApi)
    {
        printf("Unavailable Trade Object\n");
        return -1;
    }

	CShengliStockReqQryChairmanAcctAvailBpFiled msg;
	string str_client_id = GetInputValue<string>("clientID: ");
	string str_fund_acct = GetInputValue<string>("fundacct: ");
	
	snprintf(msg.ClientID, sizeof(msg.ClientID), "%s", str_client_id.c_str()); 
	snprintf(msg.FundAccount, sizeof(msg.FundAccount), "%s", str_fund_acct.c_str()); 

	msg.RequestID = GetInputValue<unsigned int>("req_id: ");
	msg.CurrencyType = CURRENCY_CNY;
	msg.UserID = m_userID;

	m_tradeApi->ReqQueryChairmanAcctAvailBp(&msg, msg.RequestID);

    return 0;
}

int TraderDemo::ReqQueryEntrustList(unsigned long long index)
{
	if (m_tradeApi)
	{
		CShengliStockReqQueryEntrustField req;
        memset(&req, 0, sizeof(CShengliStockReqQueryEntrustField));
		req.RequestID = ++m_RequestNum;
        strcpy(req.ClientID, "99990001");
        strcpy(req.FundAccount, "77770001");
        req.QryFlag = QueryFlag_Node;
		// req.OrderID = 2;
		// req.ClOrdToken = 1;
		// req.ExchID = 100;
        // strcpy(req.SecurityCode, "11016807");
		req.StateNum = 0;
        req.OrderState[0] = 64;
		req.OrderState[1] = 96;
		// req.Side = 44;
		req.StartIdx = index;
		req.RequestNum = m_single_RequestNum;

		m_tradeApi->ReqQueryEntrustList(&req);
    }
	return 0;
}

int TraderDemo::ReqQueryEntrustExecution(unsigned long long index)
{
	if (m_tradeApi)
	{
		CShengliStockReqQueryEntrustExecutionField req;
        memset(&req, 0, sizeof(CShengliStockReqQueryEntrustExecutionField));
		req.RequestID = ++m_RequestNum;
        strcpy(req.ClientID, "99990001");
        strcpy(req.FundAccount, "77770001");
        req.QryFlag = QueryFlag_Node;
		// req.ExecID = 3;
		// req.OrderID = 2;
		// req.ClOrdToken = 2;
		req.ExchID = 100;
        // strcpy(req.SecurityCode, "11016810");
		// req.Side = 49;
		req.StartIdx = index;
		req.RequestNum = m_single_RequestNum;

		m_tradeApi->ReqQueryEntrustExecutionList(&req);
    }
	return 0;
}

int TraderDemo::ReqQueryOutFundAccountAmountNodeDetail()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockTrasnBpQueryField req;
	req.UserID = m_userID;
    memcpy(req.ClientID, m_clinetId.c_str(), sizeof(req.ClientID));
    memcpy(req.FundAccount, "22220001", sizeof(req.FundAccount));

	m_tradeApi->ReqQueryOutFundAccountAmountNodeDetail(&req, 100);
	return 0;
}

int TraderDemo::GetMaxToken()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	unsigned int maxToken = 0;
	m_tradeApi->GetMaxToken(&maxToken);
	return maxToken;
}

int TraderDemo::EnterOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockEnterOrderField orderField;
	memset(&orderField, 0, sizeof(CShengliStockEnterOrderField));
	orderField.UserID = m_userID;
	orderField.ClOrdToken = GetMaxToken() + 1;

	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(orderField.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(orderField.FundAccount, str_account.c_str());

	int exch = GetInputValue<int>("Exchange ID : ");
	orderField.ExchID = exch;

	string symbol = GetInputValue<string>("Security Code : ");
	strcpy(orderField.SecurityCode, symbol.c_str());

	int qty = GetInputValue<int>("Qty : ");
	orderField.OrderQty = qty;

	double price = GetInputValue<double>("Price : ");
	orderField.Price = price;

	int i_side = GetInputValue<int>("Side : ");

	orderField.SecurityType = SHENGLI_STOCK_SecType_OPTION;
	orderField.Side = i_side;
	orderField.MinQty = 0;
	orderField.PriceType = 2;
	orderField.MaxPriceLevels = 0;
	orderField.TIF = 0;
	orderField.DelegateType = m_delegateType;
	memcpy(orderField.UserInfo, "77", sizeof(orderField.UserInfo));
	orderField.RecordID = 258;
	return m_tradeApi->EnterOrder(&orderField);
}

int TraderDemo::EnterQuoteOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliQuoteEnterOrderField orderField;
	memset(&orderField, 0, sizeof(CShengliQuoteEnterOrderField));
	orderField.UserID = m_userID;
	orderField.ClOrdToken = GetMaxToken() + 1;
	orderField.Side = 49;

	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(orderField.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(orderField.FundAccount, str_account.c_str());

	//int req_type = GetInputValue<int>("ReqType : ");
	//orderField.ReqType = req_type;

	//int exch = GetInputValue<int>("Exchange ID : ");
	//orderField.ExchID = exch;

	//string symbol = GetInputValue<string>("Security Code : ");
	//strcpy(orderField.SecurityCode, symbol.c_str());

	//int bid_qty = GetInputValue<int>("Bid_Qty : ");
	//orderField.BidQty = bid_qty;

	//double bid_price = GetInputValue<double>("Bid_Price : ");
	//orderField.BidPx = bid_price;

	//int bid_side = GetInputValue<char>("Bid_Side : ");
	//orderField.BidSide = bid_side;

	//int ask_qty = GetInputValue<int>("Ask_Qty : ");
	//orderField.AskQty = ask_qty;

	//double ask_price = GetInputValue<double>("Ask_Price : ");
	//orderField.AskPx = ask_price;

	//int ask_side = GetInputValue<char>("Ask_Side : ");
	//orderField.AskSide = ask_side;




	orderField.ExchID = 100;
	string symbol = "10003205";
	strcpy(orderField.SecurityCode, symbol.c_str());

	orderField.ReqType = 1;
	orderField.QuoteType = 1;
	orderField.BidPx = 0.0085;
	orderField.BidQty = 10;
	orderField.BidSide = QUOTE_OPEN_SIDE;
	orderField.AskPx = 0.0086;
	orderField.AskQty = 10;
	orderField.AskSide = QUOTE_OPEN_SIDE;

	orderField.UserInfo = 77;

	return m_tradeApi->EnterQuoteOrder(&orderField);
}

int TraderDemo::BatchEnterQuoteOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	int max_ordtoken = GetMaxToken() + 1;

	CShengliQuoteEnterOrderField plist[50];

	for (int i = 0; i < 50; i++)
	{
		CShengliQuoteEnterOrderField orderField;
		memset(&orderField, 0, sizeof(CShengliQuoteEnterOrderField));
		orderField.UserID = m_userID;
		orderField.ClOrdToken = max_ordtoken++;
		orderField.Side = 49;

		string str_client_id;
		if (m_clinetId.empty())
		{
			str_client_id = GetInputValue<string>("Client ID : ");
		}
		else
		{
			str_client_id = m_clinetId;
		}
		strcpy(orderField.ClientID, str_client_id.c_str());

		string str_account;
		if (m_fundAccount.empty())
		{
			str_account = GetInputValue<string>("Fund Account : ");
		}
		else
		{
			str_account = m_fundAccount;
		}
		strcpy(orderField.FundAccount, str_account.c_str());

		orderField.ExchID = 100;
		string symbol = "20001501";
		strcpy(orderField.SecurityCode, symbol.c_str());

		orderField.ReqType = 1;
		orderField.QuoteType = 1;
		orderField.BidPx = 1;
		orderField.BidQty = 10 + i;
		orderField.BidSide = QUOTE_OPEN_SIDE;
		orderField.AskPx = 2;
		orderField.AskQty = 10 + i;
		orderField.AskSide = QUOTE_OPEN_SIDE;

		orderField.UserInfo = 77;

		plist[i] = orderField;
	}


	return m_tradeApi->BatchEnterQuoteOrder(plist, 50, 40, 0);

}

int TraderDemo::CancelQuoteOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliQuoteEnterOrderField orderField;
	memset(&orderField, 0, sizeof(CShengliQuoteEnterOrderField));
	orderField.UserID = m_userID;
	orderField.ClOrdToken = GetMaxToken() + 1;

	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(orderField.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(orderField.FundAccount, str_account.c_str());

	orderField.ExchID = 101;

	string symbol = "30001501";
	strcpy(orderField.SecurityCode, symbol.c_str());

	orderField.Side = 49;
	orderField.ReqType = 1;
	orderField.QuoteType = 1;
	orderField.BidPx = 0;
	orderField.BidQty = 0;
	orderField.BidSide = QUOTE_OPEN_SIDE;
	orderField.AskPx = 0;
	orderField.AskQty = 0;
	orderField.AskSide = QUOTE_OPEN_SIDE;

	orderField.UserInfo = 77;

	return m_tradeApi->EnterQuoteOrder(&orderField);
}

int TraderDemo::EnterCreateCombStrategyOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockEnterOrderField orderField;
	memset(&orderField, 0, sizeof(CShengliStockEnterOrderField));
	orderField.UserID = m_userID;
	orderField.ClOrdToken = GetMaxToken() + 1;

	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(orderField.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(orderField.FundAccount, str_account.c_str());

	orderField.ExchID = SHENGLI_STOCK_ExchangeID_SH_CS;

	memcpy(orderField.SecurityCode, "510050", 6);

	int qty = 10;;
	orderField.OrderQty = qty;

	orderField.Price = 0;

	orderField.Side = SHENGLI_STOCK_SideType_OPT_COMB_POS_CREATE;
	orderField.MinQty = 0;
	orderField.PriceType = 2;
	orderField.MaxPriceLevels = 0;
	orderField.TIF = 0;
	memcpy(orderField.UserInfo, "77", sizeof(orderField.UserInfo));
	orderField.RecordID = 258;

	CShengliStockExternCombOrder externCombOrder;
	memset(&externCombOrder, 0, sizeof(externCombOrder));
	// externCombOrder.SecondaryOrderID; 
	memcpy(externCombOrder.StrategyID, "CNSJC", 5); //	缁勫悎绛栫暐缂栫爜
	externCombOrder.Nolegs = 2;

	CShengliStockCombLegField leg[2];
	memcpy(leg[0].LegSecurityID, "20001502", 8);		//	鎴愪唤鍚堢害浠ｇ爜锛堟湡鏉僣ode锛�
	leg[0].Exchange = SHENGLI_STOCK_ExchangeID_SH_CS;			//	浜ゆ槗鎵€
	leg[0].LegPosDir = SHENGLI_STOCK_Position_Long;			//	鎸佷粨鏂瑰悜
	leg[0].LegOrderQty = qty;			//	鎴愪唤鍚堢害鏁伴噺

	memcpy(leg[1].LegSecurityID, "20001501", 8);		//	鎴愪唤鍚堢害浠ｇ爜锛堟湡鏉僣ode锛�
	leg[1].Exchange = SHENGLI_STOCK_ExchangeID_SH_CS;			//	浜ゆ槗鎵€
	leg[1].LegPosDir = SHENGLI_STOCK_Position_Short;			//	鎸佷粨鏂瑰悜
	leg[1].LegOrderQty = qty;	//	鎴愪唤鍚堢害鏁伴噺	

	return m_tradeApi->EnterCombOrder(&orderField, &externCombOrder, leg);
}

int TraderDemo::EnterRelieveCombStrategyOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockEnterOrderField orderField;
	memset(&orderField, 0, sizeof(CShengliStockEnterOrderField));
	orderField.UserID = m_userID;
	orderField.ClOrdToken = GetMaxToken() + 1;

	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(orderField.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(orderField.FundAccount, str_account.c_str());

	orderField.ExchID = SHENGLI_STOCK_ExchangeID_SH_CS;

	memcpy(orderField.SecurityCode, "510050", 6);

	int qty = 1;
	orderField.OrderQty = qty;

	orderField.Price = 0;

	orderField.Side = SHENGLI_STOCK_SideType_OPT_COMB_POS_RELIEVE;
	orderField.MinQty = 0;
	orderField.PriceType = 2;
	orderField.MaxPriceLevels = 0;
	orderField.TIF = 0;
	memcpy(orderField.UserInfo, "77", sizeof(orderField.UserInfo));
	orderField.RecordID = 258;

	CShengliStockExternCombOrder externCombOrder;
	memset(&externCombOrder, 0, sizeof(externCombOrder));
	memcpy(externCombOrder.SecondaryOrderID, "1111130000000001", 16);
	memcpy(externCombOrder.StrategyID, "CNSJC", 5); //	缁勫悎绛栫暐缂栫爜
	externCombOrder.Nolegs = 2;

	CShengliStockCombLegField leg[2];
	memcpy(leg[0].LegSecurityID, "20001502", 8);		//	鎴愪唤鍚堢害浠ｇ爜锛堟湡鏉僣ode锛�
	leg[0].Exchange = SHENGLI_STOCK_ExchangeID_SH_CS;			//	浜ゆ槗鎵€
	leg[0].LegPosDir = SHENGLI_STOCK_Position_Long;			//	鎸佷粨鏂瑰悜
	leg[0].LegOrderQty = qty;			//	鎴愪唤鍚堢害鏁伴噺

	memcpy(leg[1].LegSecurityID, "20001501", 8);		//	鎴愪唤鍚堢害浠ｇ爜锛堟湡鏉僣ode锛�
	leg[1].Exchange = SHENGLI_STOCK_ExchangeID_SH_CS;			//	浜ゆ槗鎵€
	leg[1].LegPosDir = SHENGLI_STOCK_Position_Short;			//	鎸佷粨鏂瑰悜
	leg[1].LegOrderQty = qty;	//	鎴愪唤鍚堢害鏁伴噺	

	return m_tradeApi->EnterCombOrder(&orderField, &externCombOrder, leg);
}

int TraderDemo::EnterCombExerciseOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockEnterOrderField orderField;
	memset(&orderField, 0, sizeof(CShengliStockEnterOrderField));
	orderField.UserID = m_userID;
	orderField.ClOrdToken = GetMaxToken() + 1;

	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(orderField.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(orderField.FundAccount, str_account.c_str());

	orderField.ExchID = SHENGLI_STOCK_ExchangeID_SH_CS;

	memcpy(orderField.SecurityCode, "510050", 6);

	int qty = 1;
	orderField.OrderQty = qty;

	orderField.Price = 0;

	orderField.Side = SHENGLI_STOCK_SideType_OPT_COMB_EXERCISE;
	orderField.MinQty = 0;
	orderField.PriceType = 2;
	orderField.MaxPriceLevels = 0;
	orderField.TIF = 0;
	memcpy(orderField.UserInfo, "77", sizeof(orderField.UserInfo));
	orderField.RecordID = 258;

	CShengliStockCombLegField leg[2];
	memcpy(leg[0].LegSecurityID, "11008802", 8);		//	鎴愪唤鍚堢害浠ｇ爜锛堟湡鏉僣ode锛�
	leg[0].Exchange = SHENGLI_STOCK_ExchangeID_SH_CS;			//	浜ゆ槗鎵€
	leg[0].LegPosDir = SHENGLI_STOCK_Position_Long;			//	鎸佷粨鏂瑰悜
	leg[0].LegOrderQty = qty;			//	鎴愪唤鍚堢害鏁伴噺

	memcpy(leg[1].LegSecurityID, "11008803", 8);		//	鎴愪唤鍚堢害浠ｇ爜锛堟湡鏉僣ode锛�
	leg[1].Exchange = SHENGLI_STOCK_ExchangeID_SH_CS;			//	浜ゆ槗鎵€
	leg[1].LegPosDir = SHENGLI_STOCK_Position_Long;			//	鎸佷粨鏂瑰悜
	leg[1].LegOrderQty = qty;	//	鎴愪唤鍚堢害鏁伴噺	

	return m_tradeApi->EnterCombExercise(&orderField, 2, leg);
}

int TraderDemo::EnterCashInOutList()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}
	CShengliStockQueryCashInOutField field;
	memset(&field, 0, sizeof(CShengliStockQueryCashInOutField));
	field.UserID = m_userID;
	strcpy(field.ClientID, m_clinetId.c_str());

	return m_tradeApi->ReqQueryCashInOutList(&field, 1);
}


int TraderDemo::CancelOrder()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Trade Object\n");
		return -1;
	}

	CShengliStockCxlOrderField field;
	memset(&field, 0, sizeof(CShengliStockCxlOrderField));
	field.UserID = m_userID;
	field.ClOrdToken = GetMaxToken() + 1;
	field.DelegateType = m_delegateType;
	string str_client_id;
	if (m_clinetId.empty())
	{
		str_client_id = GetInputValue<string>("Client ID : ");
	}
	else
	{
		str_client_id = m_clinetId;
	}
	strcpy(field.ClientID, str_client_id.c_str());

	string str_account;
	if (m_fundAccount.empty())
	{
		str_account = GetInputValue<string>("Fund Account : ");
	}
	else
	{
		str_account = m_fundAccount;
	}
	strcpy(field.FundAccount, str_account.c_str());

	unsigned long long orig_id = GetInputValue<unsigned long long>("Orig Order ID : ");
	field.OrigOrderID = orig_id;

	unsigned int orig_token = GetInputValue<unsigned int>("Orig Order Token : ");
	field.OrigClOrdToken = orig_token;
	field.LeavesQty = 0;
	return m_tradeApi->CancelOrder(&field);
}

int TraderDemo::ReconnTest()
{
	if (m_tradeApi)
	{
		m_tradeApi->DisConnServer();
		UnloadEESTrader();
	}
	Init();
	return 0;
}

void TraderDemo::OnConnected(TShengliStockErrNoType errNo, const char* pErrStr)
{
	if (errNo != NO_ERROR)
	{
		printf("\nConnect Failed(%d), %s!\n", errNo, pErrStr);
		return;
	}
	// ProxyReqLogon();
	ReqUserLogon();
}

void TraderDemo::OnDisconnected(TShengliStockErrNoType errNo, const char* pErrStr)
{
	printf("\nDisconnected(%d), %s!\n", errNo, pErrStr);
}

/// \brief 鏌ヨ杩炴帴鏂紑娑堟伅鐨勫洖璋�
void TraderDemo::OnQueryDisconnected(TShengliStockErrNoType errNo, const char* pErrStr)
{
	printf("\nQuery Disconnected(%d), %s!\n", errNo, pErrStr);
}

void TraderDemo::OnRspUserLogon(CShengliStockRespUserLoginField* pLogon, int nRequestID)
{
	if (!pLogon)
	{
		printf("\nRecv Logon Resp, But Null!\n");
		return;
	}

	if (pLogon->Result != SHENGLI_STOCK_LOGON_SUCCESS)
	{
        printf("\nLogon failed, Result [%d] MsgText[%s]\n", pLogon->Result, pLogon->MsgText);
        printf("Msg request [%u]\n", nRequestID);
        return;
	}

	m_userID = pLogon->UserID;
	m_clinetId = pLogon->LogonID;

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Logon Ok\n");
	printf("---------------------------------------------------------\n");
	printf("ProtoVersion :     %d\n", pLogon->ProtoVersion);
	printf("LogonID		 :     %s\n", pLogon->LogonID);
	printf("UserID		 :     %d\n", pLogon->UserID);
	printf("TradingDate  :     %d\n", pLogon->TradingDate);
	printf("MaxToken     :     %d\n", pLogon->MaxToken);
	printf("DefClientID  :     %s\n", pLogon->DefClientID);
    printf("RequestID    :     %u\n", nRequestID);
	printf("\n");

}

void TraderDemo::OnRspChangePassword(CShengliStockRespChangePwdField* pChangePwd, int nRequestID)
{
	if (!pChangePwd)
	{
		printf("\nRecv Change Password Resp, But Null!\n");
		return;
	}

	if (pChangePwd->Result != SHENGLI_STOCK_ChangePasswordResult_Success)
	{
		printf("\nChange Password failed, %d\n", pChangePwd->Result);
		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Change Password Ok\n");
	printf("UserID:       %d\n", pChangePwd->UserID);
	printf("---------------------------------------------------------\n");
	printf("\n");
}

void TraderDemo::OnRspQueryClientId(CShengliStockClientIDListField* pClientInfo, int nRequestID, bool bIsLast)
{
	if (!pClientInfo && !bIsLast)
	{
		printf("\nRecv Query Client ID Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query Client ID Resp\n");
		return;
	}

	// m_clientiId 取锟斤拷一锟斤拷
	if (m_clinetId.empty())
	{
		m_clinetId = pClientInfo->ClientID;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Query Client Id\n");
	printf("---------------------------------------------------------\n");
	printf("UserID    :     %d\n", pClientInfo->UserID);
	printf("ClientID  :     %s\n", pClientInfo->ClientID);

	printf("\n");
}

void TraderDemo::OnRspQueryAccount(CShengliStockAccountListField* pAccountInfo, int nRequestID, bool bIsLast)
{
	if (!pAccountInfo && !bIsLast)
	{
		printf("\nRecv Query Account Resp, But Null!\n");
		return;
	}

	printf("Result[%u] MsgText[%s].\n", pAccountInfo->Result, pAccountInfo->MsgText);

	if (bIsLast)
	{
		printf("\nRecv All Query Account Resp\n");
		return;
	}

	if (m_fundAccount.empty())
	{
		m_fundAccount = pAccountInfo->FundAccount;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Query Account\n");
	printf("---------------------------------------------------------\n");
	printf("UserID:                                    %d\n", pAccountInfo->UserID);
	printf("ClientID:                                  %s\n", pAccountInfo->ClientID);
	printf("FundAccount:                               %s\n", pAccountInfo->FundAccount);
	printf("FundAccountType:                           %d\n", pAccountInfo->FundAccountType);

	printf("BizPrevilegeBody.Lev2MarketPer:            %d\n", pAccountInfo->BizPrevilegeBody.Lev2MarketPer);
	printf("BizPrevilegeBody.BondMatchPer:             %d\n", pAccountInfo->BizPrevilegeBody.BondMatchPer);
	printf("BizPrevilegeBody.BondPledgeBuybackPer:     %d\n", pAccountInfo->BizPrevilegeBody.BondPledgeBuybackPer);
	printf("BizPrevilegeBody.SigMarketEtfPer:          %d\n", pAccountInfo->BizPrevilegeBody.SigMarketEtfPer);
	printf("BizPrevilegeBody.CrossMaketEtfPer:         %d\n", pAccountInfo->BizPrevilegeBody.CrossMaketEtfPer);
	printf("BizPrevilegeBody.CrossBorderEtfPer:        %d\n", pAccountInfo->BizPrevilegeBody.CrossBorderEtfPer);
	printf("BizPrevilegeBody.HkStockSharePer:          %d\n", pAccountInfo->BizPrevilegeBody.HkStockSharePer);

	printf("VarietyPrevilegeBody.AbSecurityPer:        %d\n", pAccountInfo->VarietyPrevilegeBody.AbSecurityPer);
	printf("VarietyPrevilegeBody.NationalDebtPer:      %d\n", pAccountInfo->VarietyPrevilegeBody.NationalDebtPer);
	printf("VarietyPrevilegeBody.LocalDebtPer:         %d\n", pAccountInfo->VarietyPrevilegeBody.LocalDebtPer);
	printf("VarietyPrevilegeBody.EnterpriseDebtPer:    %d\n", pAccountInfo->VarietyPrevilegeBody.EnterpriseDebtPer);
	printf("VarietyPrevilegeBody.CompDebtPer:          %d\n", pAccountInfo->VarietyPrevilegeBody.CompDebtPer);
	printf("VarietyPrevilegeBody.FinancialDebtPer:     %d\n", pAccountInfo->VarietyPrevilegeBody.FinancialDebtPer);
	printf("VarietyPrevilegeBody.ConvertibleBondPer:   %d\n", pAccountInfo->VarietyPrevilegeBody.ConvertibleBondPer);
	printf("VarietyPrevilegeBody.ExchCompDebtPer:      %d\n", pAccountInfo->VarietyPrevilegeBody.ExchCompDebtPer);
	printf("VarietyPrevilegeBody.ExchPriDebtPer:       %d\n", pAccountInfo->VarietyPrevilegeBody.ExchPriDebtPer);
	printf("VarietyPrevilegeBody.PriDebtPer:           %d\n", pAccountInfo->VarietyPrevilegeBody.PriDebtPer);
	printf("VarietyPrevilegeBody.SecondaryDebtPer:     %d\n", pAccountInfo->VarietyPrevilegeBody.SecondaryDebtPer);
	printf("VarietyPrevilegeBody.AbSecurityPer:        %d\n", pAccountInfo->VarietyPrevilegeBody.AbSecurityPer);
	printf("VarietyPrevilegeBody.SecuCompShortDebtPer: %d\n", pAccountInfo->VarietyPrevilegeBody.SecuCompShortDebtPer);
	printf("VarietyPrevilegeBody.LofFundPer:           %d\n", pAccountInfo->VarietyPrevilegeBody.LofFundPer);
	printf("VarietyPrevilegeBody.ClosedFundPer:        %d\n", pAccountInfo->VarietyPrevilegeBody.ClosedFundPer);
	printf("VarietyPrevilegeBody.SigMarketEtfVarPer:   %d\n", pAccountInfo->VarietyPrevilegeBody.SigMarketEtfVarPer);
	printf("VarietyPrevilegeBody.CrossMarketEtfVarPer: %d\n", pAccountInfo->VarietyPrevilegeBody.CrossMarketEtfVarPer);
	printf("VarietyPrevilegeBody.CrossBorderEtfVarPer: %d\n", pAccountInfo->VarietyPrevilegeBody.CrossBorderEtfVarPer);
	printf("VarietyPrevilegeBody.EntityBondEtfPer:     %d\n", pAccountInfo->VarietyPrevilegeBody.EntityBondEtfPer);
	printf("VarietyPrevilegeBody.CashBondEtfPer:       %d\n", pAccountInfo->VarietyPrevilegeBody.CashBondEtfPer);
	printf("VarietyPrevilegeBody.CurrencyEtfPer:       %d\n", pAccountInfo->VarietyPrevilegeBody.CurrencyEtfPer);
	printf("VarietyPrevilegeBody.GoldEtfPer:           %d\n", pAccountInfo->VarietyPrevilegeBody.GoldEtfPer);
	printf("VarietyPrevilegeBody.CrossBorderLofPer:    %d\n", pAccountInfo->VarietyPrevilegeBody.CrossBorderLofPer);
	printf("\n");
}

void TraderDemo::OnRspQuerySymbol(CShengliStockNormalSecurityCodeField* pSymbolInfo, int nRequestID, bool bIsLast)
{
	if (!pSymbolInfo && !bIsLast)
	{
		printf("\nRecv Query Symbol Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query Symbol Resp\n");
		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Query Symbol\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                  :   %d\n", pSymbolInfo->UserID);
	printf("ExchID                  :   %d\n", pSymbolInfo->ExchID);
	printf("SecurityType            :   %d\n", pSymbolInfo->SecurityType);
	printf("SecuritySubtype         :   %d\n", pSymbolInfo->SecuritySubtype);
	printf("SecurityCode            :   %s\n", pSymbolInfo->SecurityCode);
	printf("SecurityName            :   %s\n", pSymbolInfo->SecurityName);
	printf("CoverTodayFlag          :   %d\n", pSymbolInfo->CoverTodayFlag);
	printf("Currency				:   %s\n", pSymbolInfo->Currency);
	printf("ParValue				:   %lf\n", pSymbolInfo->ParValue.get_double());
	printf("BuyMinQty				:   %u\n", pSymbolInfo->BuyMinQty);
	printf("SellMinQty				:   %u\n", pSymbolInfo->SellMinQty);
	printf("MinOrderQty             :   %u\n", pSymbolInfo->MinOrderQty);
	printf("MaxOrderQty             :   %u\n", pSymbolInfo->MaxOrderQty);
	printf("PreClosePrice           :   %lf\n", pSymbolInfo->PreClosePrice.get_double());
	printf("MinTickPrice            :   %lf\n", pSymbolInfo->MinTickPrice.get_double());
	printf("UpLimitPrice            :   %lf\n", pSymbolInfo->UpLimitPrice.get_double());
	printf("LowLimitPrice           :   %lf\n", pSymbolInfo->LowLimitPrice.get_double());
	printf("IsFinancing             :   %c\n", pSymbolInfo->IsFinancing);
	printf("IsLending				:   %c\n", pSymbolInfo->IsLending);
	printf("\n");
}

void TraderDemo::OnRspQueryETFMember(CShengliStockEtfMemberField* pEtfMember, int nRequestID, bool bIsLast)
{
	if (!pEtfMember)
	{
		printf("\nRecv Query Symbol Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv Query Symbol Finish All Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Query ETF Member\n");
	printf("---------------------------------------------------------\n");
	printf("UserID             :     %d\n", pEtfMember->UserID);
	printf("ExchID             :     %d\n", pEtfMember->ExchID);
	printf("SecurityCode	   :     %s\n", pEtfMember->SecurityCode);
	printf("MemberSecurityCode :     %s\n", pEtfMember->MemberSecurityCode);
	printf("MemberExchID       :     %d\n", pEtfMember->MemberExchID);
	printf("Share              :     %d\n", pEtfMember->Share);
	printf("SubstCashFlag      :     %d\n", pEtfMember->SubstCashFlag);
	printf("PermiumRatio       :     %0.4f\n", pEtfMember->PermiumRatio);
	printf("DiscountRatio      :     %0.4f\n", pEtfMember->DiscountRatio);
	printf("Creation           :     %0.4f\n", pEtfMember->CreationCashSubstitute.get_double());
	printf("Redemption         :     %0.4f\n", pEtfMember->RedemptionCashSubstitute.get_double());

	printf("\n");
}

void TraderDemo::OnRspQueryOptionDetail(CShengliStockOptionSecurityCodeField* pOption, int nRequestID, bool bIsLast)
{
	if (!pOption && !bIsLast)
	{
		printf("Recv Query Option Detail Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("Recv All Query Option Detail Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Query Option Detail\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", pOption->UserID);
	printf("ExchID                   :     %d\n", pOption->ExchID);
	printf("SecurityType             :     %d\n", pOption->SecurityType);
	printf("SecuritySubType          :     %d\n", pOption->SecuritySubType);
	printf("SecurityCode	         :     %s\n", pOption->SecurityCode);
	printf("SecurityName             :     %s\n", pOption->SecurityName);
	printf("ExpireDate		         :     %d\n", pOption->ExpireDate);
	printf("UnderlyingSecurityCode   :     %s\n", pOption->UnderlyingSecurityCode);
	printf("UnderlyingSecurityName   :     %s\n", pOption->UnderlyingSecurityName);
	printf("UnderlyingSecurityType             :     %d\n", pOption->UnderlyingSecurityType);
	printf("UnderlyingSecuritySubType          :     %d\n", pOption->UnderlyingSecuritySubType);
	printf("OptionType                :     %c\n", pOption->OptionType);
	printf("VolMultipler         :     %u\n", pOption->VolMultipler);
	printf("StartDate         :     %d\n", pOption->StartDate);
	printf("EndDate         :     %d\n", pOption->EndDate);
	printf("DeliveryDate         :     %d\n", pOption->DeliveryDate);
	printf("ExerciseDate         :     %d\n", pOption->ExerciseDate);
	printf("UpdateVersion         :     %d\n", pOption->UpdateVersion);
	printf("TotalLongPosition         :     %ld\n", pOption->TotalLongPosition);
	printf("SecurityClosePx         :     %lf\n", pOption->SecurityClosePx.get_double());
	printf("SettlePrice         :     %lf\n", pOption->SettlePrice.get_double());
	printf("UnderlyingClosePx         :     %lf\n", pOption->UnderlyingClosePx.get_double());
	printf("DailyPriceUpLimit         :     %lf\n", pOption->DailyPriceUpLimit.get_double());
	printf("DailyPriceDownLimit         :     %lf\n", pOption->DailyPriceDownLimit.get_double());

	printf("LmtMinOrderQty         :     %u\n", pOption->LmtMinOrderQty);
	printf("LmtMaxOrderQty         :     %u\n", pOption->LmtMaxOrderQty);
	printf("MktMinOrderQty         :     %u\n", pOption->MktMinOrderQty);
	printf("MktMaxOrderQty         :     %u\n", pOption->MktMaxOrderQty);
	printf("MinTickPrice         :     %lf\n", pOption->MinTickPrice.get_double());

	printf("ContractAccountCode      :     %s\n", pOption->ContractAccountCode);
	printf("ContractID               :     %s\n", pOption->ContractID);
	printf("UnderlyingExchID         :     %d\n", pOption->UnderlyingExchID);
	printf("CallOrPut                :     %c\n", pOption->CallOrPut);
	printf("StrikePrice              :     %.5f\n", pOption->StrikePrice.get_double() ) ;

	printf("LmtBuyOrdMaxFloor         :     %u\n", pOption->LmtBuyOrdMaxFloor ) ; 	
	printf("LmtSellOrdMaxFloor         :     %u\n", pOption->LmtSellOrdMaxFloor ) ; 
	printf("MktBuyOrdMaxFloor         :     %u\n", pOption->MktBuyOrdMaxFloor ) ; 	
	printf("MktSellOrdMaxFloor         :     %u\n", pOption->MktSellOrdMaxFloor ) ; 


	printf("\n");
}

void TraderDemo::OnRspQueryAccountTradeFee(CShengliStockAccountTradeFeeField* pFee, int nRequestID, bool bIsLast)
{
	if (!pFee && !bIsLast)
	{
		printf("\nRecv Query Account TradeFee Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query Account TradeFee Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Query Account Trade Fee\n");
	printf("---------------------------------------------------------\n");
	printf("UserID          :     %d\n", pFee->UserID);
	printf("ClientID        :     %s\n", pFee->ClientID);
	printf("AccountType	    :     %d\n", pFee->AccountType);
	printf("FundAccount		:     %s\n", pFee->FundAccount);
	printf("ExchID          :     %d\n", pFee->ExchID);
	printf("TradeType       :     %d\n", pFee->TradeType);
	printf("PosDir          :     %d\n", pFee->PosDir);
	printf("FeeIdx          :     %d\n", pFee->FeeIdx);
	printf("FeeAmount       :     %lld\n", pFee->FeeAmount);
	printf("FeeQty          :     %lld\n", pFee->FeeQty);
	printf("FeeMin          :     %lld\n", pFee->FeeMin);
	printf("\n");
}

void TraderDemo::OnRspQueryNormalPosition(CShengliStockNormalPositionField* pPos, int nRequestID, bool bIsLast)
{
	if (!pPos && !bIsLast)
	{
		printf("\nRecv Query Normal Position Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query Normal Position Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Query Position\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                    :     %d\n", pPos->UserID);
	printf("ClientID                  :     %s\n", pPos->ClientID);
	printf("AccountType               :     %d\n", pPos->AccountType);
	printf("FundAccount	              :     %s\n", pPos->FundAccount);
	printf("ExchID			          :     %d\n", pPos->ExchID);
	printf("SecurityType              :     %d\n", pPos->SecurityType);
	printf("SecuritySubType           :     %d\n", pPos->SecuritySubType);
	printf("SecurityCode              :     %s\n", pPos->SecurityCode);
	printf("InitOvnPosQty             :     %d\n", pPos->InitOvnPosQty);
	printf("CurOvnQty                 :     %d\n", pPos->CurOvnQty);
	printf("CurQty                    :     %d\n", pPos->CurQty);
	printf("AvailQty                  :     %d\n", pPos->AvailQty);
	printf("OvnCoveredLockedQty       :     %d\n", pPos->OvnCoveredLockedQty);
	printf("CoveredLockedQty          :     %d\n", pPos->CoveredLockedQty);
	printf("OvnCoveredLockPendingQty  :     %d\n", pPos->OvnCoveredLockPendingQty);
	printf("CoveredLockPendingQty     :     %d\n", pPos->CoveredLockPendingQty);
	printf("CoveredPledgedQty         :     %d\n", pPos->CoveredPledgedQty);
	printf("CoveredUnlockPendingQty   :     %d\n", pPos->CoveredUnlockPendingQty);
	printf("ClosePosPendingQty        :     %d\n", pPos->ClosePosPendingQty);
	printf("AvgPx                     :     %lf\n", pPos->AvgPx.get_double());
	printf("\n");
}

void TraderDemo::OnRspQueryOptionPosition(CShengliStockOptionPositionField* pPos, int nRequestID, bool bIsLast)
{
	if (!pPos && !bIsLast)
	{
		printf("\nRecv Query Position Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query Position Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Query Position\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                    :     %d\n", pPos->UserID);
	printf("ClientID                  :     %s\n", pPos->ClientID);
	printf("AccountType               :     %d\n", pPos->AccountType);
	printf("FundAccount	              :     %s\n", pPos->FundAccount);
	printf("ExchID			          :     %d\n", pPos->ExchID);
	printf("SecurityType              :     %d\n", pPos->SecurityType);
	printf("SecuritySubType           :     %d\n", pPos->SecuritySubType);
	printf("SecurityCode              :     %s\n", pPos->SecurityCode);
	printf("PositionDirection         :     %d\n", pPos->PositionDirection);
	printf("InitOvnPosQty             :     %d\n", pPos->InitOvnQty);
	printf("CurQty                    :     %d\n", pPos->CurQty);
	printf("AvailQty                  :     %d\n", pPos->AvailQty);
	printf("CurMargin                 :     %f\n", pPos->CurMargin.get_double());
	printf("AvgPx                     :     %f\n", pPos->AvgPx.get_double());
	printf("Bcost                     :     %lf\n", pPos->Bcost.get_double());
	printf("Mktval                    :     %lf\n", pPos->Mktval.get_double());
	printf("Premium                   :     %lf\n", pPos->Premium.get_double());
	printf("OpeningQty                :     %u\n", pPos->OpeningQty);
	printf("CoveringQty               :     %u\n", pPos->CoveringQty);
	printf("OpeningFrozenBp           :     %lf\n", pPos->OpeningFrozenBp.get_double());
	printf("\n");
}

/// 鏌ヨ浠撲綅鍒楄〃鐨勬湡鏉冪粍鍚堢瓥鐣ヤ粨浣嶈繑鍥炰簨浠�
void TraderDemo::OnRspQueryOptionCombStrategyPosition(CShengliStockOptionCombStrategyPositionField* pPos, int nRequestID, bool bIsLast)
{
	if (!pPos && !bIsLast)
	{
		printf("\nRecv Query option comb strategy Position Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query optin comb strategy Position Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("UserID:%d \n", pPos->m_UserID);
	printf("CustID:%s        \n", pPos->m_CustID);
	printf("FundAccount:%s       \n", pPos->m_FundAccount);
	printf("exchange_id:%d        \n", pPos->m_exchange_id);
	printf("trade_acct:%s        \n", pPos->m_trade_acct);
	printf("comb_id:%s        \n", pPos->m_comb_id);
	printf("day_type:%d       \n ", pPos->m_day_type);
	printf("comb_strategy_id:%s        \n", pPos->m_comb_strategy_id);
	printf("underlying_secu_code:%s        \n", pPos->m_underlying_secu_code);
	printf("m_init_share:%d   \n", pPos->m_init_share);
	printf("share:%d   \n", pPos->m_share);
	printf("frz_share:%d \n", pPos->m_frz_share);
	printf("margin:%0.2f  \n", pPos->m_margin.get_double());
	printf("leg_count:%d  \n", pPos->m_leg_count);

	for (unsigned int i = 0; i < pPos->m_leg_count; ++i)
	{
		printf("leg: %u\n", i + 1);
		printf("  LegSecuCode:%s", pPos->m_leg[i].m_secu_code);
		printf("  LegPosDir:%d", pPos->m_leg[i].m_pos_dir);
		printf("  LegInitShare:%d", pPos->m_leg[i].m_init_share);
		printf("  LegShare:%d", pPos->m_leg[i].m_share);
		printf("  LegMargin:%0.4f", pPos->m_leg[i].m_margin.get_double());
		printf("\n");
	}
}

void TraderDemo::OnRtnOrderRewind(CShengliStockOrderAcceptedField* pOrder, int nRequestID)
{
	if (!pOrder)
	{
		printf("\nRecv Order Rewind Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Order Rewind\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", pOrder->UserID);
	printf("ClOrdToken		         :     %d\n", pOrder->ClOrdToken);
	printf("ClientID                 :     %s\n", pOrder->ClientID);
	printf("SecurityType             :     %d\n", pOrder->SecurityType);
	printf("SecuritySubType          :     %d\n", pOrder->SecuritySubType);
	printf("FundAccount              :     %s\n", pOrder->FundAccount);
	printf("ExchID                   :     %d\n", pOrder->ExchID);
	printf("Side                     :     %d\n", pOrder->Side);
	printf("OrderQty		         :     %d\n", pOrder->OrderQty);
	printf("MinQty                   :     %d\n", pOrder->MinQty);
	printf("PriceType                :     %d\n", pOrder->PriceType);
	printf("MaxPriceLevels           :     %d\n", pOrder->MaxPriceLevels);
	printf("TIF                      :     %d\n", pOrder->TIF);
	printf("Price			         :     %.5f\n", pOrder->Price.get_double());
	printf("StopPrice                :     %.5f\n", pOrder->StopPrice.get_double());
	printf("SecurityCode	         :     %s\n", pOrder->SecurityCode);
	printf("CashMarginFlag           :     %d\n", pOrder->CashMarginFlag);
	printf("SessionID                :     %c\n", pOrder->SessionID);
	printf("SessionSelMode           :     %d\n", pOrder->SessionSelMode);
	printf("UserInfo                 :     %s\n", pOrder->UserInfo2);
	printf("OrderID			         :     %lld\n", pOrder->OrderID);
	printf("ExchangeOrderID          :     %s\n", pOrder->ExchangeOrderID);
	printf("ExchangeAcceptFlag       :     %d\n", pOrder->ExchangeAcceptFlag);
	printf("OrderState               :     %d\n", pOrder->OrderState);
	printf("PassiveOrderFlag         :     %d\n", pOrder->PassiveOrderFlag);
	printf("RecvTimestamp            :     %lld\n", pOrder->RecvTimestamp);
	printf("AcceptTimestamp          :     %lld\n", pOrder->AcceptTimestamp);
	printf("ExchangeAcceptTimestamp  :     %lld\n", pOrder->ExchangeAcceptTimestamp);
	printf("ExchangeTransTimestamp   :     %lld\n", pOrder->ExchangeTransTimestamp);
	printf("ClosedTimestamp          :     %lld\n", pOrder->ClosedTimestamp);
	printf("FilledQty                :     %d\n", pOrder->FilledQty);
	printf("ExpireDate               :     %d\n", pOrder->ExpireDate);
	printf("UnderlyingSecurityCode   :     %s\n", pOrder->UnderlyingSecurityCode);
	printf("ContractAccountCode      :     %s\n", pOrder->ContractAccountCode);
	printf("ContractID               :     %s\n", pOrder->ContractID);
	printf("UnderlyingExchID         :     %d\n", pOrder->UnderlyingExchID);
	printf("CallOrPut                :     %c\n", pOrder->CallOrPut);
	printf("StrikePrice              :     %.5f\n", pOrder->StrikePrice.get_double());
	printf("ForceCoverFlag           :     %d\n", pOrder->ForceCoverFlag);
	printf("\n");
}

void TraderDemo::OnRtnExecRewind(CShengliStockOrderExecedField* pExec, int nRequestID)
{
	if (!pExec)
	{
		printf("\nRecv Exec Rewind Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Exec Rewind\n");
	printf("---------------------------------------------------------\n");
	printf("UserID             :     %d\n", pExec->UserID);
	printf("ClOrdToken		   :     %d\n", pExec->ClOrdToken);
	printf("ClientID           :     %s\n", pExec->ClientID);
	printf("FundAccount        :     %s\n", pExec->FundAccount);
	printf("OrderID			   :     %lld\n", pExec->OrderID);
	printf("ExecID			   :     %lld\n", pExec->ExecID);
	printf("Qty				   :     %d\n", pExec->LastQty);
	printf("Price			   :     %.5f\n", pExec->LastPrice.get_double());
	printf("LastQty            :     %d\n", pExec->LastQty);
	printf("PassiveFlag        :     %d\n", pExec->PassiveFlag);
	printf("ExchangeOrderID    :     %s\n", pExec->ExchangeOrderID);
	printf("ExchangeExecID     :     %s\n", pExec->ExchangeExecID);
	printf("ExchangeTimestamp  :     %lld\n", pExec->ExchangeTimestamp);
	printf("Side               :     %d\n", pExec->Side);
	printf("SecuCode           :     %s\n", pExec->SecuCode);
	// printf("ExecTimestamp      :     %lld\n",  pExec->ExecTimestamp);
	printf("\n");
}

void TraderDemo::OnRtnCxlReqRewind(CShengliStockOrderCxledField* pCxlReq, int nRequestID)
{
	if (!pCxlReq)
	{
		printf("\nRecv Cxl Req Rewind Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Cxl Req Rewind\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                    :     %d\n", pCxlReq->UserID);
	printf("ClOrdToken			      :     %d\n", pCxlReq->ClOrdToken);
	printf("ClientID                  :     %s\n", pCxlReq->ClientID);
	printf("FundAccount               :     %s\n", pCxlReq->FundAccount);
	printf("OrigOrderID			      :     %lld\n", pCxlReq->OrigOrderID);
	printf("OrigClOrdToken		      :     %d\n", pCxlReq->OrigClOrdToken);
	printf("LeavesQty                 :     %d\n", pCxlReq->LeavesQty);
	printf("AcceptTimestamp           :     %lld\n", pCxlReq->AcceptTimestamp);
	printf("CxledTimestamp            :     %lld\n", pCxlReq->CxledTimestamp);
	printf("ExchangeTransTimestamp    :     %lld\n", pCxlReq->ExchangeTransTimestamp);
	printf("ExchangeOrderID           :     %s\n", pCxlReq->ExchangeOrderID);
	printf("OrigUserID                :     %d\n", pCxlReq->OrigUserID);
	printf("LeavesQty                 :     %d\n", pCxlReq->LeavesQty);
	printf("ExchID                    :     %d\n", pCxlReq->ExchID);
	printf("PassiveFlag               :     %d\n", pCxlReq->PassiveFlag);
	printf("CxlReqStatus              :     %d\n", pCxlReq->CxlReqStatus);
	printf("\n");
}

void TraderDemo::OnRtnOrderRewindFinish(CShengliStockOrderRewindFinishField* pOrderFinish, int nRequestID)
{
	if (!pOrderFinish)
	{
		printf("\nRecv Order Rewind Finish Resp, But Null!\n");
		return;
	}

	printf("\nRecv Order Rewind Finish Resp\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                    :     %d\n", pOrderFinish->UserID);
	printf("ClientID                  :     %s\n", pOrderFinish->ClientID);
	printf("\n");
}

void TraderDemo::OnRtnExecRewindFinish(CShengliStockExecRewindFinishField* pExecFinish, int nRequestID)
{
	if (!pExecFinish)
	{
		printf("\nRecv Exec Rewind Finish Resp, But Null!\n");
		return;
	}

	printf("\nRecv Exec Rewind Finish Resp\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                    :     %d\n", pExecFinish->UserID);
	printf("ClientID                  :     %s\n", pExecFinish->ClientID);
	printf("\n");
}

void TraderDemo::OnRtnCxlReqRewindFinish(CShengliStockCxlReqRewindFinishField* pCxlReqFinish, int nRequestID)
{
	if (!pCxlReqFinish)
	{
		printf("\nRecv Cxl Req Rewind Finish Resp, But Null!\n");
		return;
	}

	printf("\nRecv Cxl Req Rewind Finish Resp\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                    :     %d\n", pCxlReqFinish->UserID);
	printf("ClientID                  :     %s\n", pCxlReqFinish->ClientID);
	printf("\n");
}

void TraderDemo::OnRspQueryClientBpStatus(CShengliStockBpStatusField* pBpInfo, int nRequestID, bool bIsLast)
{
	if (!pBpInfo && !bIsLast)
	{
		printf("\nRecv Query Client Bp Status Resp, But Null!\n");
		return;
	}

	printf("Result[%u] MsgText[%s].\n", pBpInfo->Result, pBpInfo->MsgText);

	if (bIsLast)
	{
		printf("\nRecv All Query Client Bp Status Resp\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Client Bp Status\n");
	printf("---------------------------------------------------------\n");
	printf("UserID              :     %d\n", pBpInfo->UserID);
	printf("ClientID            :     %s\n", pBpInfo->ClientID);
	printf("FundAccount			:     %s\n", pBpInfo->FundAccount);
	printf("InitialBp			:     %.5f\n", pBpInfo->InitialBp.get_double());
	printf("AvailableBp			:     %.5f\n", pBpInfo->AvailableBp.get_double());
	printf("MarketEquity		:     %.5f\n", pBpInfo->MarketEquity.get_double());
	printf("InitEquity			:     %.5f\n", pBpInfo->InitEquity.get_double());
	printf("InitMargin			:     %.5f\n", pBpInfo->InitMargin.get_double());
	printf("\n");
}

void TraderDemo::OnRspQueryMarketSession(CShengliStockExchangeConnectField* pSession, int nRequestID, bool bIsLast)
{
	if (!pSession && !bIsLast)
	{
		printf("\nRecv Query Market Session Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv Query Market Session Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Market Session\n");
	printf("---------------------------------------------------------\n");
	printf("UserID              :     %d\n", pSession->UserID);
	printf("ExchID				:     %d\n", pSession->ExchID);
	printf("SessionCount		:     %c\n", pSession->SessionCount);
	printf("SessionID           :     %s\n", pSession->SessionID);
	printf("\n");
}

void TraderDemo::OnRtnMarketStatusChangeReport(CShengliStockExchangeStatusReportField* pReport)
{
	if (!pReport)
	{
		printf("\nRecv Market Status Change Report Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Market Status Change Report\n");
	printf("---------------------------------------------------------\n");
	printf("UserID              :     %d\n", pReport->ExchID);
	printf("SessionID			:     %c\n", pReport->SessionID);
	printf("SessionStatus		:     %d\n", pReport->SessionStatus);
	printf("\n");
}

void TraderDemo::OnRtnOrderAccepted(CShengliStockOrderAcceptedField* pAccept)
{
	if (!pAccept)
	{
		printf("\nRecv Order Accepted Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Order Accepted\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", pAccept->UserID);
	printf("ClOrdToken		         :     %d\n", pAccept->ClOrdToken);
	printf("ClientID                 :     %s\n", pAccept->ClientID);
	printf("SecurityType             :     %d\n", pAccept->SecurityType);
	printf("SecuritySubType          :     %d\n", pAccept->SecuritySubType);
	printf("FundAccount              :     %s\n", pAccept->FundAccount);
	printf("ExchID                   :     %d\n", pAccept->ExchID);
	printf("Side                     :     %d\n", pAccept->Side);
	printf("OrderQty		         :     %d\n", pAccept->OrderQty);
	printf("MinQty                   :     %d\n", pAccept->MinQty);
	printf("PriceType                :     %d\n", pAccept->PriceType);
	printf("MaxPriceLevels           :     %d\n", pAccept->MaxPriceLevels);
	printf("TIF                      :     %d\n", pAccept->TIF);
	printf("Price                    :     %.5f\n", pAccept->Price.get_double());
	printf("StopPrice	             :     %.5f\n", pAccept->StopPrice.get_double());
	printf("SecurityCode             :     %s\n", pAccept->SecurityCode);
	printf("CashMarginFlag	         :     %d\n", pAccept->CashMarginFlag);
	printf("SessionID                :     %c\n", pAccept->SessionID);
	printf("SessionSelMode           :     %d\n", pAccept->SessionSelMode);
	printf("UserInfo                 :     %s\n", pAccept->UserInfo2);
	printf("OrderID			         :     %lld\n", pAccept->OrderID);
	printf("ExchangeOrderID          :     %s\n", pAccept->ExchangeOrderID);
	printf("ExchangeAcceptFlag       :     %d\n", pAccept->ExchangeAcceptFlag);
	printf("OrderState               :     %d\n", pAccept->OrderState);
	printf("PassiveOrderFlag         :     %d\n", pAccept->PassiveOrderFlag);
	printf("RecvTimestamp            :     %lld\n", pAccept->RecvTimestamp);
	printf("AcceptTimestamp          :     %lld\n", pAccept->AcceptTimestamp);
	printf("ExchangeAcceptTimestamp  :     %lld\n", pAccept->ExchangeAcceptTimestamp);
	printf("ExchangeTransTimestamp   :     %lld\n", pAccept->ExchangeTransTimestamp);
	printf("ClosedTimestamp          :     %lld\n", pAccept->ClosedTimestamp);
	printf("FilledQty                :     %d\n", pAccept->FilledQty);
	printf("ExpireDate               :     %d\n", pAccept->ExpireDate);
	printf("UnderlyingSecurityCode   :     %s\n", pAccept->UnderlyingSecurityCode);
	printf("ContractAccountCode      :     %s\n", pAccept->ContractAccountCode);
	printf("ContractID               :     %s\n", pAccept->ContractID);
	printf("UnderlyingExchID         :     %d\n", pAccept->UnderlyingExchID);
	printf("CallOrPut                :     %c\n", pAccept->CallOrPut);
	printf("StrikePrice              :     %.5f\n", pAccept->StrikePrice.get_double());
	printf("ForceCoverFlag           :     %d\n", pAccept->ForceCoverFlag);
	printf("extern info ------------------------------------------\n");
	printf("SecondaryOrder			 :     %s\n", pAccept->Extern.SecondaryOrderID);
	printf("StrategyID               :     %s\n", pAccept->Extern.StrategyID);

	for (int i = 0; i < pAccept->Extern.Nolegs; ++i)
	{
		printf("Leg:%d\n", i + 1);
		printf("  SecuCode:      :  %s\n", pAccept->Leg[i].LegSecurityID);
		printf("  Exchange:		 :  %d\n", pAccept->Leg[i].Exchange);
		printf("  PosDir:        :  %d\n", pAccept->Leg[i].LegPosDir);
		printf("  LegQty         :  %d\n", pAccept->Leg[i].LegOrderQty);
	}

	printf("\n");
}

void TraderDemo::OnRtnOrderRejected(CShengliStockOrderRejectedField* pReject)
{
	if (!pReject)
	{
		printf("\nRecv Order Rejected Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Order Rejected\n");
	printf("---------------------------------------------------------\n");
	printf("UserID          :     %d\n", pReject->UserID);
	printf("ClOrdToken      :     %d\n", pReject->ClOrdToken);
	printf("OrderID			:     %lld\n", pReject->OrderID);
	printf("RejectTimeStamp :     %lld\n", pReject->RejectTimeStamp);
	printf("RejectedBy		:     %d\n", pReject->RejectedBy);
	printf("RejectReason    :     %d\n", pReject->RejectReason);
	printf("GrammarResult	:     %d\n", pReject->GrammarResult);
	printf("PassiveFlag     :     %d\n", pReject->PassiveFlag);
	printf("RiskResult      :     %s\n", pReject->RiskResult);
	printf("ReasonText      :     %s\n", pReject->ReasonText);
	printf("\n");

	RejectReasonDesc  rej;

	printf("ReasonText      :     %s\n", rej.GetOrderRejectDesc(pReject->GrammarResult, pReject->RiskResult).c_str());
	TShengliStockRiskResultType temp_str_msg;
	printf("ReasonText      :     %s\n", rej.GetOrderRejectDesc(8209, temp_str_msg).c_str());

}

void TraderDemo::OnRtnOrderExecuted(CShengliStockOrderExecedField* pExec)
{
	if (!pExec)
	{
		printf("\nRecv Order Executed Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Order Executed\n");
	printf("---------------------------------------------------------\n");
	printf("UserID             :     %d\n", pExec->UserID);
	printf("ClOrdToken		   :     %d\n", pExec->ClOrdToken);
	printf("ClientID           :     %s\n", pExec->ClientID);
	printf("FundAccount        :     %s\n", pExec->FundAccount);
	printf("OrderID			   :     %lld\n", pExec->OrderID);
	printf("ExecID			   :     %lld\n", pExec->ExecID);
	printf("Price			   :     %.5f\n", pExec->LastPrice.get_double());
	printf("Qty				   :     %d\n", pExec->LastQty);
	printf("PassiveFlag        :     %d\n", pExec->PassiveFlag);
	printf("ExchangeOrderID    :     %s\n", pExec->ExchangeOrderID);
	printf("ExchangeExecID     :     %s\n", pExec->ExchangeExecID);
	printf("ExchangeTimestamp  :     %lld\n", pExec->ExchangeTimestamp);
	//printf("ExecTimestamp      :     %lld\n",    pExec->ExecTimestamp);

	printf("extern info ------------------------------------------\n");
	printf("SecondaryOrder     :     %s\n", pExec->Extern.SecondaryOrderID);
	printf("StrategyID         :     %s\n", pExec->Extern.StrategyID);

	for (int i = 0; i < pExec->Extern.Nolegs; ++i)
	{
		printf("Leg:%d\n", i + 1);
		printf("  SecuCode:      :  %s\n", pExec->Leg[i].LegSecurityID);
		printf("  Exchange:      :  %d\n", pExec->Leg[i].Exchange);
		printf("  PosDir:        :  %d\n", pExec->Leg[i].LegPosDir);
		printf("  LegQty         :  %d\n", pExec->Leg[i].LegOrderQty);
	}
	printf("\n");
}

void TraderDemo::OnRtnOrderCxled(CShengliStockOrderCxledField* pCxled)
{
	if (!pCxled)
	{
		printf("\nRecv Order Cxled Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Order Cxled\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", pCxled->UserID);
	printf("ClOrdToken			     :     %d\n", pCxled->ClOrdToken);
	printf("ClientID                 :     %s\n", pCxled->ClientID);
	printf("FundAccount              :     %s\n", pCxled->FundAccount);
	printf("OrigOrderID			     :     %lld\n", pCxled->OrigOrderID);
	printf("OrigClOrdToken		     :     %d\n", pCxled->OrigClOrdToken);
	printf("LeavesQty                :     %d\n", pCxled->LeavesQty);
	printf("AcceptTimestamp          :     %lld\n", pCxled->AcceptTimestamp);
	printf("CxledTimestamp           :     %lld\n", pCxled->CxledTimestamp);
	printf("ExchangeTransTimestamp   :     %lld\n", pCxled->ExchangeTransTimestamp);
	printf("ExchangeOrderID          :     %s\n", pCxled->ExchangeOrderID);
	printf("OrigUserID               :     %d\n", pCxled->OrigUserID);
	printf("LeavesQty                :     %d\n", pCxled->LeavesQty);
	printf("ExchID                   :     %d\n", pCxled->ExchID);
	printf("PassiveFlag              :     %d\n", pCxled->PassiveFlag);
	printf("CxlReqStatus             :     %d\n", pCxled->CxlReqStatus);
	printf("\n");
}

void TraderDemo::OnRtnOrderCxlRejected(CShengliStockOrderCxlRejectedField* pCxlRejected)
{
	if (!pCxlRejected)
	{
		printf("\nRecv Order Cxl Rejected Resp, But Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("Order Cxl Rejected\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", pCxlRejected->UserID);
	printf("ClOrdToken               :     %d\n", pCxlRejected->ClOrdToken);
	printf("OrderID			         :     %lld\n", pCxlRejected->OrderID);
	printf("RejectTimeStamp          :     %lld\n", pCxlRejected->RejectTimeStamp);
	printf("ExchangeTransTimestamp   :     %lld\n", pCxlRejected->ExchangeTransTimestamp);
	printf("RejectedBy		         :     %d\n", pCxlRejected->RejectedBy);
	printf("RejectReason             :     %d\n", pCxlRejected->RejectReason);
	printf("GrammarResult            :     %d\n", pCxlRejected->GrammarResult);
	printf("PassiveFlag              :     %d\n", pCxlRejected->PassiveFlag);
	printf("RiskResult               :     %s\n", pCxlRejected->RiskResult);
	printf("ReasonText               :     %s\n", pCxlRejected->ReasonText);
	printf("\n");
}

void TraderDemo::OnRtnETFExecuted(CShengliStockEtfExecHeadField* pHead, CShengliStockEtfExecBodyField* pBody, bool bIsLast)
{
	if (!pHead)
	{
		printf("\nRecv ETF executed Resp, but pHead is Null!\n");
		return;
	}

	if (!pBody)
	{
		printf("\nRecv ETF executed Resp, but pBody is Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("ETF Executed\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", pHead->UserID);
	printf("ClOrdToken               :     %d\n", pHead->ClOrdToken);
	printf("ClientID                 :     %s\n", pHead->ClientID);
	printf("FundAccount              :     %s\n", pHead->FundAccount);
	printf("OrderID                  :     %lld\n", pHead->OrderID);
	printf("ExecID                   :     %lld\n", pHead->ExecID);
	printf("LastPrice                :     %.5f\n", pHead->LastPrice.get_double());
	printf("LastQty                  :     %d\n", pHead->LastQty);
	printf("PassiveFlag              :     %d\n", pHead->PassiveFlag);
	printf("ExchangeOrderID          :     %s\n", pHead->ExchangeOrderID);
	printf("ExchangeExecID           :     %s\n", pHead->ExchangeExecID);
	printf("ExchangeTimestamp        :     %lld\n", pHead->ExchangeTimestamp);
	//printf("ExecTimestamp            :     %lld\n",   pHead->ExecTimestamp);
	printf("---------------------------------------------------------\n");
	printf("MemberSecurityCode       :     %s\n", pBody->MemberSecurityCode);
	printf("DeliveryQty              :     %d\n", pBody->DeliveryQty);
	printf("MemberExchID             :     %d\n", pBody->MemberExchID);
	printf("SubstCashRate            :     %.5f\n", pBody->SubstCashRate);
	printf("\n");

}
void TraderDemo::OnRecvOpStationReportMsg(CShengliOpStationReportResp* p_Field)
{
	if (!p_Field)
	{
		printf("\nRecv OP Station Resp, but p_Field is Null!\n");
		return;
	}

	printf("\n---------------------------------------------------------\n");
	printf("OpStationReport\n");
	printf("---------------------------------------------------------\n");
	printf("UserID                   :     %d\n", p_Field->UserID);
	printf("Result               	 :     %d\n", p_Field->Result);
	printf("OpStationID              :     %d\n", p_Field->OpStationID);
	printf("CustomerKey              :     %s\n", p_Field->CustomerKey);
	printf("\n");
}

void TraderDemo::OnRspQueryRiskRuleThresholds(CShengliStockReqQueryRiskThresholdValueRespField * pRsp, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		switch (pRsp->Result)
		{
		case 0:
			printf("query complete! query result: %s", "success");
			break;
		case 1:
			printf("query complete! query result: %s", "not found client id");
			break;
		case 2:
			printf("query complete! query result: %s", "not found fund account");
			break;
		case 3:
			printf("query complete! query result: %s", "not found risk rule id");
			break;
		case 4:
			printf("query complete! query result: %s", "risk rule not config");
			break;
		case 5:
			printf("query complete! query result: %s", "unable to query the risk rule id");
			break;
		default:
			printf("not found result!");
			break;
		}
	}

	printf("cust id:%s\nfund account:%s\n"			\
		"risk rule:%d\nrisk rule type:%d\n"			\
		"security type:%d\nsecurity sub type:%d\n"	\
		"exchange id:%d\nsecurity code:%s\n"		\
		"param count:%d\n",
		pRsp->ClientID, pRsp->FundAccount,
		pRsp->RiskRuleID, pRsp->RiskRuleType,
		pRsp->SecurityType, pRsp->SecuritySubType,
		pRsp->ExchID, pRsp->SecurityCode,
		pRsp->ParamCount);
	if (pRsp->ParamCount == 1)
	{
		printf("define threshold:%.4f\n", pRsp->RiskThreholdValue[0].get_double());
	}
	else if (pRsp->ParamCount == 2)
	{
		printf("define threshold:%.4f\n", pRsp->RiskThreholdValue[0].get_double());
		printf("define threshold:%.4f\n", pRsp->RiskThreholdValue[1].get_double());
	}
	else if (pRsp->ParamCount == 3)
	{
		printf("define threshold:%.4f\n", pRsp->RiskThreholdValue[0].get_double());
		printf("define threshold:%.4f\n", pRsp->RiskThreholdValue[1].get_double());
		printf("define threshold:%.4f\n", pRsp->RiskThreholdValue[2].get_double());
	}
	puts("=========================================================");

}

void TraderDemo::OnRspQueryRiskRuleAccumulate(CShengliStockReqQueryRiskValueRespField * pRsp, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		switch (pRsp->Result)
		{
		case 0:
			printf("query complete! query result: %s", "success");
			break;
		case 1:
			printf("query complete! query result: %s", "not found client id");
			break;
		case 2:
			printf("query complete! query result: %s", "not found fund account");
			break;
		case 3:
			printf("query complete! query result: %s", "not found risk rule id");
			break;
		case 4:
			printf("query complete! query result: %s", "risk rule not config");
			break;
		case 5:
			printf("query complete! query result: %s", "unable to query the risk rule id");
			break;
		default:
			printf("not found result!");
			break;
		}
	}

	printf("cust id:%s\nfund account:%s\n"			\
		"risk rule:%d\nrisk rule type:%d\n"			\
		"security type:%d\nsecurity sub type:%d\n"	\
		"exchange id:%d\nsecurity code:%s\n"		\
		"risk valuies:%.4f\n",
		pRsp->ClientID, pRsp->FundAccount,
		pRsp->RiskRuleID, pRsp->RiskRuleType,
		pRsp->SecurityType, pRsp->SecuritySubType,
		pRsp->ExchID, pRsp->SecurityCode,
		pRsp->RiskValue.get_double());
	puts("=========================================================");
}

void TraderDemo::OnRspQueryAcctMonitorValue(CShengliStockReqQueryAcctMonitorValueRespField * pResp, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		printf("\nRecv Acct Monitor Value Finish!\n");
		return;
	}

	printf("cust id:%s\nfund account:%s\n"			\
		"acct monitor id:%d\nexchange id:%d\n"			\
		"current value:%.4f\nprecaution1:%.4f\n"		\
		"upd time:%s\n",
		pResp->ClientID, pResp->FundAccount,
		pResp->AcctMoniotrID, pResp->ExchID,
		pResp->CurrentValue.get_double(), pResp->Precaution1.get_double(),
		pResp->UpdTime);
	puts("=========================================================");
}

int TraderDemo::ReqQueryTradeAccountList()
{
	if (!m_tradeApi)
	{
		printf("Unavailable Query Object\n");
		return -1;
	}

	CShengliStockReqQueryTradeAccountListField req;
	memset(&req, 0, sizeof(CShengliStockReqQueryTradeAccountListField));
	req.UserID = m_userID;
	strcpy(req.ClientID, m_clinetId.c_str());
	return m_tradeApi->ReqQueryTradeAccountList(&req, 10);
}

void TraderDemo::OnRspQueryTradeAccountList(CShengliTradeAccountListField * pTradeAccount, int nRequestID, bool bIsLast)
{
	if (!pTradeAccount && !bIsLast)
	{
		printf("\nRecv Query Trade Account Resp, But Null!\n");
		return;
	}

	if (bIsLast)
	{
		printf("\nRecv All Query Trade Account Resp\n");
		return;
	}

	if (m_fundAccount.empty())
	{
		m_fundAccount = pTradeAccount->FundAccount;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Query Trade Account\n");
	printf("---------------------------------------------------------\n");
	printf("UserID:                                        %d\n", pTradeAccount->UserID);
	printf("ClientID:                                      %s\n", pTradeAccount->ClientID);
	printf("FundAccount:                                   %s\n", pTradeAccount->FundAccount);
	printf("FundAccountType:                               %d\n", pTradeAccount->FundAccountType);
	printf("TradeAccount                                   %s\n", pTradeAccount->TradeAccount);
	printf("Exchange                                       %d\n", pTradeAccount->Exchange);
	printf("BindingFlag                                    %d\n", pTradeAccount->BindingFlag);
	printf("RequestID                                      %d\n", pTradeAccount->RequestID);
	printf("InvestorPrevilegeBody.MarketPricePer           %d\n", pTradeAccount->InvestorPrevilegeBody.MarketPricePer);
	printf("InvestorPrevilegeBody.BuyStStockPer            %d\n", pTradeAccount->InvestorPrevilegeBody.BuyStStockPer);
	printf("InvestorPrevilegeBody.BuyOutStockPer           %d\n", pTradeAccount->InvestorPrevilegeBody.BuyOutStockPer);
	printf("InvestorPrevilegeBody.StartBoardPer            %d\n", pTradeAccount->InvestorPrevilegeBody.StartBoardPer);
	printf("InvestorPrevilegeBody.KechuangBoardPer         %d\n", pTradeAccount->InvestorPrevilegeBody.KechuangBoardPer);
	printf("InvestorPrevilegeBody.StructuredFundPer        %d\n", pTradeAccount->InvestorPrevilegeBody.StructuredFundPer);
	printf("InvestorPrevilegeBody.BondMarketInvestorPer    %d\n", pTradeAccount->InvestorPrevilegeBody.BondMarketInvestorPer);
	printf("InvestorPrevilegeBody.BondMarketQualifiedPer   %d\n", pTradeAccount->InvestorPrevilegeBody.BondMarketQualifiedPer);
	printf("InvestorPrevilegeBody.BondPledgeBuybackPer     %d\n", pTradeAccount->InvestorPrevilegeBody.BondPledgeBuybackPer);
	printf("InvestorPrevilegeBody.HkStockSharePer          %d\n", pTradeAccount->InvestorPrevilegeBody.HkStockSharePer);
	printf("InvestorPrevilegeBody.OptUQIPer                %d\n", pTradeAccount->InvestorPrevilegeBody.OptUQIPer);
	printf("InvestorPrevilegeBody.OptLevel1Per             %d\n", pTradeAccount->InvestorPrevilegeBody.OptLevel1Per);
	printf("InvestorPrevilegeBody.OptLevel2Per             %d\n", pTradeAccount->InvestorPrevilegeBody.OptLevel2Per);
	printf("InvestorPrevilegeBody.OptLevel3Per             %d\n", pTradeAccount->InvestorPrevilegeBody.OptLevel3Per);
	printf("TradeNodeID                                    %s\n", pTradeAccount->TradeNodeID);
	printf("\n");
}


void TraderDemo::OnRspQueryCashInOutList(CShengliStockRespCashInOutField* p_Field, int nRequestID, bool bIsLast)
{
	if (!p_Field && !bIsLast)
	{
		printf("\nRecv Query Cash InOut List, But Null!\n");
		return;
	}

	printf("Result[%u]. MsgText[%s].\n", p_Field->Result, p_Field->MsgText);

	if (bIsLast)
	{
		printf("\nRecv All Cash InOut List Resp\n");
		return;
	}

	if (m_fundAccount.empty())
	{
		m_fundAccount = p_Field->FundAccount;
	}


	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Query Cash InOut List\n");
	printf("---------------------------------------------------------\n");
	printf("UserID:                                        %d\n", p_Field->UserID);
	printf("ClientID:                                      %s\n", p_Field->ClientID);
	printf("FundAccount:                                   %s\n", p_Field->FundAccount);
	printf("CashInOutFlag                                  %c\n", p_Field->CashInOutFlag);
	printf("ModifyBp                                       %llu\n", p_Field->ModifyBp);
	printf("UpDt                                           %s\n", p_Field->UpDt);
	printf("SeqNo                                          %llu\n", p_Field->SeqNo);
	printf("\n");
}


void TraderDemo::OnRspPushCashInOut(CShengliStockRespCashInOutField* p_Field)
{
	if (m_fundAccount.empty())
	{
		m_fundAccount = p_Field->FundAccount;
	}


	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("Push Cash InOut Report\n");
	printf("---------------------------------------------------------\n");
	printf("UserID:                                        %d\n", p_Field->UserID);
	printf("ClientID:                                      %s\n", p_Field->ClientID);
	printf("FundAccount:                                   %s\n", p_Field->FundAccount);
	printf("CashInOutFlag                                  %d\n", p_Field->CashInOutFlag);
	printf("ModifyBp                                       %llu\n", p_Field->ModifyBp);
	printf("UpDt                                           %s\n", p_Field->UpDt);
	printf("SeqNo                                          %llu\n", p_Field->SeqNo);
	printf("\n");
}


/// 涓户鎻愪氦閲囬泦淇℃伅杩斿洖娑堟伅鍥炶皟
void TraderDemo::OnRspProxySubmitInfo(CShengliStockRspInfoField *pRspInfo, int nRequestId)
{

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp proxy submit info \n");
	printf("---------------------------------------------------------\n");
	printf("ReqID:					%d\n", nRequestId);
	printf("MsgCode					%d\n", pRspInfo->MsgCode);
	printf("MsgText					%s\n", pRspInfo->MsgText);
	printf("\n");

}

/// 璁㈤槄浜ゆ槗鎵€璁㈠崟鍗曞彿鍥炲
void TraderDemo::OnRspSubscribeInfo(CShengliStockRespSubscribeField *p_Field, int nRequestID)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp subscribe info \n");
	printf("---------------------------------------------------------\n");
	printf("ReqID:					%d\n", nRequestID);
	printf("UserID					%d\n", p_Field->UserID);
	printf("ErrCode					%d\n", p_Field->ErrCode);
	printf("ErrText					%s\n", p_Field->ErrText);
	printf("\n");
}

/// 鎺ㄩ€佷氦鏄撴墍璁㈠崟鍗曞彿娑堟伅
void TraderDemo::OnRspPushMktCltOrdIDMsg(CShengliStockRespMktCltOrdIDField * p_Field)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp MktClOrderID info \n");
	printf("---------------------------------------------------------\n");
	printf("UserID						%d\n", p_Field->UserID);
	printf("ClientID					%s\n", p_Field->ClientID);
	printf("FundAccount					%s\n", p_Field->FundAccount);
	printf("OrderType					%d\n", p_Field->OrderType);
	printf("CltOrderToken				%d\n", p_Field->CltOrderToken);
	printf("OperUserID					%d\n", p_Field->OperUserID);
	printf("OrderID						%llu\n", p_Field->OrderID);
	printf("OrigUserID					%d\n", p_Field->OrigUserID);
	printf("OrigCltOrderToken			%d\n", p_Field->OrigCltOrderToken);
	printf("OrigOrderID					%llu\n", p_Field->OrigOrderID);
	printf("MarketCltOrderID			%s\n", p_Field->MarketCltOrderID);
	printf("\n");
}

///鏈熸潈鍋氬競璁㈠崟鎺ュ彈鐨勮繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderAccepted(CShengliStockQuoteOrderAcceptedField* pAccept)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp quote_order_accept info \n");
	printf("MsgIndex					%d\n", pAccept->MsgIndex);
	printf("OrderID						%llu\n", pAccept->OrderID);
	printf("BidQty						%d\n", pAccept->BidQty);
	printf("BidPrice					%lf\n", pAccept->BidPrice.get_double());
	printf("BidSide						%d\n", pAccept->BidSide);
	printf("BidOrderState				%d\n", pAccept->BidOrderState);
	printf("AskQty						%d\n", pAccept->AskQty);
	printf("AskPrice					%lf\n", pAccept->AskPrice.get_double());
	printf("AskSide						%d\n", pAccept->AskSide);
	printf("AskOrderState				%d\n", pAccept->AskOrderState);
	printf("ExchangeAcceptFlag			%d\n", pAccept->ExchangeAcceptFlag);
	printf("---------------------------------------------------------\n");
}

///鏈熸潈鍋氬競璁㈠崟浜ゆ槗鎵€鎺ュ彈鐨勮繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderExchAccepted(CShengliStockQuoteOrderExchAcceptedField* pAccept)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp quote_order_exch_accept info \n");
	printf("MsgIndex					%d\n", pAccept->MsgIndex);
	printf("OrderID						%llu\n", pAccept->OrderID);
	printf("BidQty						%d\n", pAccept->BidQty);
	printf("BidPrice					%lf\n", pAccept->BidPrice.get_double());
	printf("BidSide						%d\n", pAccept->BidSide);
	printf("BidOrderState				%d\n", pAccept->BidOrderState);
	printf("AskQty						%d\n", pAccept->AskQty);
	printf("AskPrice					%lf\n", pAccept->AskPrice.get_double());
	printf("AskSide						%d\n", pAccept->AskSide);
	printf("AskOrderState				%d\n", pAccept->AskOrderState);
	printf("CxlReqStatus				%d\n", pAccept->CxlReqStatus);
	printf("BidOriOrderID				%llu\n", pAccept->BidOriOrderID);
	printf("BidLeavesQty				%d\n", pAccept->BidLeavesQty);
	printf("AskOriOrderID				%llu\n", pAccept->AskOriOrderID);
	printf("AskLeavesQty				%d\n", pAccept->AskLeavesQty);
	printf("ExchangeAcceptFlag			%d\n", pAccept->ExchangeAcceptFlag);
	printf("---------------------------------------------------------\n");
}

///鏈熸潈鍋氬競璁㈠崟鎷掔粷鐨勮繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderRejected(CShengliStockQuoteOrderRejectedField* pReject)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp quote_order_reject info \n");
	printf("msg_index					%d\n", pReject->MsgIndex);
	printf("GrammarResult				%d\n", pReject->GrammarResult);
	printf("GrammarSubResult			%d\n", pReject->GrammarSubResult);
	printf("RejectedBy					%d\n", pReject->RejectedBy);
	printf("RejectReason				%d\n", pReject->RejectReason);
	printf("RejectText					%s\n", pReject->RejectText);

	RejectReasonDesc  rej;

	printf("ReasonText      :     %s\n", rej.GetOrderRejectDesc(pReject->GrammarResult, pReject->RiskResult).c_str());

	printf("---------------------------------------------------------\n");
}

///鏈熸潈鍋氬競鎴愪氦鍥炴姤鐨勮繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderExecuted(CShengliStockQuoteOrderExecedField* pExec)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp quote_order_execution info \n");
	printf("msg_index					%d\n", pExec->MsgIndex);
	printf("LastPrice					%lf\n", pExec->LastPrice.get_double());
	printf("LastQty						%d\n", pExec->LastQty);
	printf("LeavesQty					%d\n", pExec->LeavesQty);
	printf("PositionSide				%d\n", pExec->PositionSide);
	printf("AskOrBid					%d\n", pExec->AskOrBid);
	printf("ExecID						%u\n", pExec->ExecID);
	printf("---------------------------------------------------------\n");
}

///鏈熸潈鍋氬競鎾ゅ崟鎴愬姛鐨勮繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderCxled(CShengliStockQuoteOrderCxledField* pCxled)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp quote_order_cxled info \n");
	printf("msg_index						%d\n", pCxled->MsgIndex);
	printf("BidOriOrderID					%llu\n", pCxled->BidOriOrderID);
	printf("BidLeavesQty					%d\n", pCxled->BidLeavesQty);
	printf("AskOriOrderID					%llu\n", pCxled->AskOriOrderID);
	printf("AskLeavesQty					%d\n", pCxled->AskLeavesQty);
	printf("CxlReqStatus					%d\n", pCxled->CxlReqStatus);
	printf("---------------------------------------------------------\n");
}

///鏈熸潈鍋氬競鎾ゅ崟鎷掔粷鐨勮繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderCxlRejected(CShengliStockQuoteOrderCxlRejectedField* pCxlRejected)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp quote_order_cxl_reject info \n");
	printf("msg_index					%d\n", pCxlRejected->MsgIndex);
	printf("RejectedBy					%d\n", pCxlRejected->RejectedBy);
	printf("---------------------------------------------------------\n");
}

///鎶ヤ环鍗曞洖婊氬畬鎴愯繑鍥炰簨浠�
void TraderDemo::OnRtnQuoteOrderRewindFinish(CShengliStockQuoteOrderRewindFinishField* pRewindFinish)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("rewind quote order finish \n");
	printf("---------------------------------------------------------\n");
}

/// 鎺ㄩ€侀€氱敤淇℃伅

void TraderDemo::OnRspCommonMsg(CShengliStockCommonMsgField* p_Field)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp CommonMsg info \n");
	printf("---------------------------------------------------------\n");
	printf("ErrCode						%d\n", p_Field->ErrCode);
	printf("DisconnFlag					%d\n", p_Field->DisconnFlag);
	printf("Reason						%s\n", p_Field->Reason);
	printf("\n");
}


	///鏌ヨ鍚堢害淇濊瘉閲戣繑鍥炰簨浠�
void TraderDemo::OnRspQuerySymbolMarginInfo(CShengliStockQuerySymbolMarginInfoRespField* pResp, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		puts("finish\n");
		return;
	}

	if (pResp->Result != 0)
	{
		switch(pResp->Result)
		{
			case 1:
				puts("Query symbol margin failed by not found client info");
			break;
			case 2:
				puts("Query symbol margin failed by not found fund account info");
			break;
			case 3:
				puts("Query symbol margin failed by not found option symbol info");
			break;
			case 4:
				puts("Query symbol margin failed by option symbol list is empty");
			break;			
			case 5:
				puts("Query symbol margin failed by exchange id info error");
			break;
			default:
                puts("Location result");
            break;
		}

		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp Symbol Margin info \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("OpenMargin                   %lf\n", pResp->OpenMarin.get_double());
	printf("ExchangeMargin               %lf\n", pResp->ExchangeMarin.get_double());
	printf("RiskMargin                   %lf\n", pResp->RiskMargin.get_double());
	printf("\n");
}

	///鏌ヨ鍚堢害璐圭敤杩斿洖浜嬩欢
void TraderDemo::OnRspQuerySymbolFeeInfo(CShengliStockQuerySymbolFeeInfoRespField* pResp, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		puts("finish");
		return;
	}

	if (pResp->Result != 0)
	{
		switch(pResp->Result)
		{
			case 1:
				puts("Query symbol fee failed by not found client info");
			break;
			case 2:
				puts("Query symbol fee failed by not found fund account info");
			break;
			case 3:
				puts("Query symbol fee failed by not found option symbol info");
			break;
			case 4:
				puts("Query symbol fee failed by option symbol list is empty");
			break;
            case 5:
                puts("Query symbol fee failed by exchange id info error");
			break;
			default:
                puts("Location result");
            break;
		}

		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp Symbol Fee info \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Security Code                %s\n", pResp->SecurityCode);
	printf("Side                         %d\n", pResp->Side);
	printf("Security Type                %d\n", pResp->SecurityType);
	printf("Security Sub Type            %d\n", pResp->SecuritySubType);
	printf("Valid Count                  %d\n", pResp->ValidCount);
	for (size_t i = 0; i < pResp->ValidCount; i++)
	{
		puts("[");
		printf("\tFee Type                     %d\n", pResp->FeeConfig[i].m_FeeType) ;
        printf("\tFee Amount                   %0.8lf\n", pResp->FeeConfig[i].m_FeeAmount.get_double());
        printf("\tFee Qty                      %0.4lf\n", pResp->FeeConfig[i].m_FeeQty.get_double());
        printf("\tFee Min                      %0.4lf\n", pResp->FeeConfig[i].m_FeeMin.get_double());
        printf("\tFee Max                      %0.4lf\n", pResp->FeeConfig[i].m_FeeMax.get_double());
        puts("]");
        if (i != pResp->ValidCount - 1)
			puts(",");		
    }
	printf("\n");
}


	///鏌ヨ绛剧害閾惰杩斿洖浜嬩欢
void TraderDemo::OnRspQuerySigningBankInfo(CShengliStockQuerySigningBankInfoRespField* pResp, int nRequestID, bool bIsLast)
{
    if (bIsLast)
    {
        puts("finish");
        return;
    }

	if (pResp->Result != 0)
	{
		switch (pResp->Result)
		{
		case 1:
			puts("Query failed. Not found user info.");
			break;
		case 2:
			puts("Query failed. Not found client info.");
			break;
		case 3:
			puts("Query failed. Not found fund account info.");
			break;
		case 4:
			puts("Query failed. Check request id failed.");
			break;		
		case 5:
			puts("Query failed. Not found sync trade service.");
			break;
		case 7:
			puts("Query failed. Query info is empty.");
			break;		
		case 10:
			puts("Query failed. System process failed.");
			break;
		default:
			break;
		}

		printf("error info [%s]\n", pResp->MsgText);
		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp Signing bank info \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Currency                     %d\n", pResp->Currency);
	printf("Bank Code                    %d\n", pResp->ExtOrg);
	printf("Bank Name                    %s\n", pResp->ExtOrgName);
	printf("Check Fund Passwd            %d\n", pResp->CheckFundPasswd);
	printf("Check Bank Passwd            %d\n", pResp->CheckBankPasswd);
	printf("\n");
	

}

    ///鏌ヨ閾惰浣欓杩斿洖浜嬩欢
void TraderDemo::OnRspQueryBankBalanceInfo(CShengliStockQueryBankBalanceInfoRespField* pResp, int nRequestID)
{
	if (pResp->Result != 0)
	{
		switch (pResp->Result)
		{
		case 1:
			puts("Query failed. Not found user info.");
			break;
		case 2:
			puts("Query failed. Not found client info.");
			break;
		case 3:
			puts("Query failed. Not found fund account info.");
			break;
		case 4:
			puts("Query failed. Check request id failed.");
			break;		
		case 5:
			puts("Query failed. Not found sync trade service.");
			break;
		case 7:
			puts("Query failed. Query info is empty.");
			break;		
		case 10:
			puts("Query failed. System process failed.");
			break;
		default:
			break;
		}

		printf("error info [%s]\n", pResp->MsgText);
		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp Bank balance info \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Currency                     %d\n", pResp->Currency);
	printf("Branch Code                  %d\n", pResp->OrgCode);
	printf("Bank Code                    %d\n", pResp->ExtOrg);
	printf("Fund Bln                     %lf\n", pResp->FundBln.get_double());
	printf("\n");

}


void TraderDemo::OnRspOneStepTransferInCashInfo(CShengliStockOneStepTransferInCashRespField * pResp , int nRequestID)
{
	if (pResp->Result != 0)
	{
		switch (pResp->Result)
		{
		case 1:
			puts("One step transfer in cash failed. Not found user info.");
			break;
		case 2:
			puts("One step transfer in cash failed. Not found client info.");
			break;
		case 3:
			puts("One step transfer in cash failed. Not found fund account info.");
			break;
		case 4:
			puts("One step transfer in cash failed. Check request id failed.");
			break;		
		case 5:
			puts("One step transfer in cash failed. Not found sync trade service.");
			break;
		case 10:
			puts("One step transfer in cash failed. System process failed.");
			break;
		default:
			break;
		}

		printf("error info [%s]\n", pResp->MsgText);
		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp One step transfer in cash resp info \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Currency                     %c\n", pResp->Currency);
	printf("Bank Code                    %d\n", pResp->ExtOrg);
	printf("Transf Amount                %lf\n", pResp->TransAmt.get_double());
	printf("\n");
}

void TraderDemo::OnRspOneStepTransferOutCashInfo(CShengliStockOneStepTransferOutCashRespField* pResp, int nRequestID)
{
	if (pResp->Result != 0)
	{
		switch (pResp->Result)
		{
		case 1:
			puts("One step transfer out cash failed. Not found user info.");
			break;
		case 2:
			puts("One step transfer out cash failed. Not found client info.");
			break;
		case 3:
			puts("One step transfer out cash failed. Not found fund account info.");
			break;
		case 4:
			puts("One step transfer out cash failed. Transf type failed.");
			break;		
		case 5:
			puts("One step transfer out cash failed. Bp not enough failed.");
			break;		
		case 9:
			puts("One step transfer out cash failed. Not found sync trade service.");
			break;
		case 10:
			puts("One step transfer out cash failed. System process failed.");
			break;
		case 11:
			puts("One step transfer out cash failed. Trigger risk control.");
			break;
		default:
			break;
		}

		printf("error info [%s]\n", pResp->MsgText);
		return;
	}

	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp one step transfer out cash resp info \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Currency                     %c\n", pResp->Currency);
	printf("Bank Code                    %d\n", pResp->ExtOrg);
	printf("Transf Amount                %lf\n", pResp->TransAmt.get_double());
	printf("\n");
}


///鏌ヨ濮旀墭鏂瑰紡鍒楄〃 
void TraderDemo::OnRspDelegateTypeList(CShengliStockQueryDeletageTypeRespField* pResp, int nRequestID, bool bIsLast)
{
	if ( bIsLast )
	{
		printf("delegate query finished. \n");
		printf("---------------------------------------------------------\n");		
		return ;
	}

	printf("DelegateType[%c] DelegateDesc[%s]\n",  pResp->DelegateType, pResp->DelegateDesc) ;
	m_delegateType = pResp->DelegateType;
}

/// 冻结解冻标的券回调事件
void TraderDemo::OnRspFrozenUnderlyingSymbolQty(CShengliStockFrzUnderlyingSymbolQtyField* pResp, int nRequestID)
{
	printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp frz underlyging symbol qty \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("ExchangeID                   %d\n", pResp->ExchangeID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Frzflag                      %c\n", pResp->FrzFlag);
	printf("Quantity                     %d\n", pResp->Quantity);
	printf("SecurityCode                 %s\n", pResp->SecurityCode);
	printf("RequestID                    %d\n", pResp->RequestID);
	printf("Result                       %d\n", pResp->Result);
	printf("MsgText                      %s\n", pResp->MsgText);
	printf("MsgType                      %d\n", pResp->MsgType);
	printf("\n");
}

void TraderDemo::OnRtnInOutFundAccountMargin(CShengliStockInOutFundAccountAmountField* pResp, int nRequestID)
{
    printf("\n");
    printf("---------------------------------------------------------\n");
	printf("resp inout amount result \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Inoutflag                    %c\n", pResp->RrzFlag);
	printf("Amount                       %lf\n", pResp->Amount.get_double());
	printf("RequestID                    %d\n", pResp->RequestID);
	printf("Result                       %d\n", pResp->Result);
	printf("MsgText                      %s\n", pResp->MsgText);
	printf("\n");
}

void TraderDemo::OnRspQueryUnderlyingSymbolQty(CShengliStockUnderlyingSymbolQtyField* pResp, int nRequestID)
{
    printf("\n");
    printf("---------------------------------------------------------\n");
	printf("resp qry underlyging result \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("Quantity                     %d\n", pResp->Quantity);
	printf("SecurityCode                 %s\n", pResp->SecurityCode);
	printf("RequestID                    %d\n", pResp->RequestID);
	printf("Result                       %d\n", pResp->Result);
	printf("MsgText                      %s\n", pResp->MsgText);
	printf("MsgType                      %d\n", pResp->MsgType);
	printf("\n");
}

void TraderDemo::OnRspQueryChairmanAcctAvailBp(CShengliStockQryChairmanAcctAvailBpRespFiled* pResp, int nRequestID)
{
	printf("\n");
    printf("---------------------------------------------------------\n");
	printf("resp qry chairman acct avail bp result \n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %d\n", pResp->UserID);
	printf("ClientID                     %s\n", pResp->ClientID);
	printf("FundAccount                  %s\n", pResp->FundAccount);
	printf("RequestID                    %d\n", pResp->RequestID);
	printf("CurrencyType                 %c\n", pResp->CurrencyType);
	printf("AvaibleBp                    %lf\n", pResp->AvaibleBp.get_double());
	printf("Result                       %d\n", pResp->Result);
	printf("MsgText                      %s\n", pResp->MsgText);
	printf("\n");	
}

/// 查询委托列表返回事件
void TraderDemo::OnRtnQueryEntrustList(CShengliStockRespQueryEntrustField *pField, bool bIsLast)
{
	if (bIsLast)
	{
        printf("------------ recv query Entrustlist resp finish! requestnum:%d  index:%d--------------\n", pField->RequestID, m_cur_index);
        if (m_cur_index == m_single_RequestNum && 0 != m_CurCursorMark)
        {
			usleep(100000);
            ReqQueryEntrustList(++m_CurCursorMark);
		}
        m_cur_index = 0;
        return;
	}

	printf("-------------------------------------------------\n");
	printf("---------recv query Entrustlist--------------\n");
	printf("request					%d\n",pField->RequestID);		
	printf("curidx					%d\n",pField->CurIdx);		
	printf("CurCursorMark			%llu\n",pField->CurCursorMark);		
	printf("clientid				%s\n",pField->ClientID);		
	printf("fundaccount				%s\n",pField->FundAccount);		
	printf("side					%d\n",pField->Side);		
	printf("orderid					%llu\n",pField->OrderID);		
	printf("SecurityCode					%s\n",pField->SecurityCode);		
	printf("UnderlyingSecurityCode					%s\n",pField->UnderlyingSecurityCode);		
	printf("BranchID					%s\n",pField->BranchID);		
	printf("orderState					%d\n",pField->OrderState);		
	printf("userinfo2					%s\n",pField->UserInfo2);		

	if (pField->Side == SHENGLI_STOCK_SideType_OPT_COMB_EXERCISE
		|| pField->Side == SHENGLI_STOCK_SideType_OPT_COMB_POS_CREATE
		|| pField->Side == SHENGLI_STOCK_SideType_OPT_COMB_POS_RELIEVE
		|| pField->Side == SHENGLI_STOCK_SideType_OPT_FORCE_COMB_POS_RELIEVE)
	{
        printf("SecondaryOrderID			%s\n", pField->Extern.SecondaryOrderID);
        printf("StrategyID					%s\n", pField->Extern.StrategyID);
        printf("Nolegs						%d\n", pField->Extern.Nolegs);
        for (int i = 0; i < pField->Extern.Nolegs; ++i)
        {
            printf("LegSecurityID					%s\n", pField->Leg[i].LegSecurityID);
            printf("Exchange						%d\n", pField->Leg[i].Exchange);
            printf("LegPosDir						%d\n", pField->Leg[i].LegPosDir);
            printf("LegOrderQty						%d\n", pField->Leg[i].LegOrderQty);
        }
    }
	else if (pField->Side == SHENGLI_STOCK_SideType_MARKET_ORDER)
	{
		printf("leg1_state					%d\n",pField->BidOrderState);	
		printf("leg2_state					%d\n",pField->AskOrderState);	
	}

	m_CurCursorMark = pField->CurCursorMark;
	m_cur_index++;
	// printf("-------------------------------------------------\n");
}

/// 查询委托成交返回事件
void TraderDemo::OnRtnQueryEntrustExecution(CShengliStockRespQueryEntrustExecutionField *pField, bool bIsLast)
{
	if (bIsLast)
    {
        printf("------------ recv query EntrustExecutionlist resp finish! requestnum:%d--------------\n", pField->RequestID);
		if (m_cur_index == m_single_RequestNum && 0 != m_CurCursorMark)
		{
			usleep(100000);
            ReqQueryEntrustExecution(++m_CurCursorMark);
        }
        m_cur_index = 0;
        return;
    }

	printf("-------------------------------------------------\n");
    printf("--------recv query EntrustExecutionlist resp\n");
	printf("request					%d\n",pField->RequestID);		
	printf("curidx					%d\n",pField->CurIdx);		
	printf("CurCursorMark			%llu\n",pField->CurCursorMark);		
	printf("clientid				%s\n",pField->ClientID);		
	printf("fundaccount				%s\n",pField->FundAccount);		
	printf("side					%d\n",pField->Side);		
	printf("orderid					%llu\n",pField->OrderID);		
	printf("execid					%d\n",pField->ExecID);		
	printf("PositionSide			%d\n",pField->PositionSide);		
	printf("AskOrBid				%d\n",pField->AskOrBid);		
	printf("LastPrice				%.5f\n",pField->LastPrice.get_double());		
	printf("LastQty					%d\n",pField->LastQty);		

	m_CurCursorMark = pField->CurCursorMark;
	m_cur_index++;
	printf("-------------------------------------------------\n");


}

void TraderDemo::OnQueryOutFundAccountAmountNode(CShengliStockTrasnQueryBpDetailField* pFields, int nRequestID, bool bIsLast)
{
	if (bIsLast)
    {
        printf("---------------------------------------------------------\n");
        printf("---------qry out fund account amount resp finish!--------\n");
        printf("---------------------------------------------------------\n");
        printf("/////////////////////////////////////////////////////////\n");
        return;
    }

    printf("\n");
	printf("---------------------------------------------------------\n");
	printf("resp qry out fund account amount node\n");
	printf("---------------------------------------------------------\n");
	printf("ClientID                     %s\n", pFields->mClientID);
	printf("Exchange                     %d\n", pFields->mExchange);
	printf("FundAccount                  %s\n", pFields->mFundAccount);
	printf("ID                           %llu\n", pFields->mID);
	printf("OutAmount                    %lf\n", pFields->mOutAmount.get_double());
	printf("TradingDate                  %s\n", pFields->mTradingDate);
	printf("UpTime                       %s\n", pFields->mUpDt);
	printf("Result                       %d\n", pFields->mResult);
	printf("MsgText                      %s\n", pFields->mMsgText);
	printf("\n");	
}