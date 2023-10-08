#include "EESQuoteDemo.h"
#include <iostream>

#ifndef SHENGLI_WINDOWS
#include <unistd.h>
#endif // !SHENGLI_WINDOWS


using std::cout;
using std::cin;
using std::endl;

QuoteDemo::QuoteDemo(void)
{
	m_eesApi = NULL;
	m_handle = NULL;
	m_regSymCount = 0;
	m_b_logoned = false;

}

QuoteDemo::~QuoteDemo(void)
{
}

void QuoteDemo::Run()
{
	InputParam();

	bool ret = Init();
	if (!ret)
	{
		Pause();
		return;
	}
	
	while (!m_b_logoned)
	{
#ifdef SHENGLI_WINDOWS
		Sleep(1);
#else
		sleep(1);
#endif

		puts("wait logon service!");
	}

#ifdef SHENGLI_WINDOWS
	Sleep(3);
#else
	sleep(3);
#endif

    // 在这里添加调试输出语句，以查看是否成功调用了OnLoginResponse函数
    printf("OnLoginResponse was called successfully.\n");

	m_eesApi->RegisterSymbol(EQS_EXCHANGE_SH, "11008800");
	m_eesApi->QuerySymbolQuote(EQS_EXCHANGE_SH, "11008800");
	m_eesApi->UnregisterSymbol(EQS_EXCHANGE_SH, "11008800");

	Pause();
	Close();
}

bool QuoteDemo::Init()
{
	bool ret = LoadEESQuote();
	if (!ret)
	{
		return false;
	}
	m_eesApi->RegQuoteType(m_c_need_quote_type);
	/*
	EqsTcpInfo			info;
	vector<EqsTcpInfo>	vec_info;

	memset(&info, 0, sizeof(EqsTcpInfo));
	strcpy(info.m_eqsIp, m_quoteServerIp.c_str());
	info.m_eqsPort = m_quotePort;
	vec_info.push_back(info);
	*/
	EqsLoginParam 		temp;

	strcpy(temp.m_loginId, m_logonId.c_str());
	strcpy(temp.m_password, m_logonPwd.c_str());

	ret = m_eesApi->ConnServer(m_vec_ServerInfo, this, temp);
	if (!ret)
	{
		printf("初始化EES行情服API对象失败!\n");
		return false;
	}
	else
	{
		printf("初始化EES行情服API对象成功!\n");
	}

	return true;
}

void QuoteDemo::Close()
{
	if (m_eesApi)
	{
		m_eesApi->DisConnServer();
	}

	UnloadEESQuote();
}


void QuoteDemo::Pause()
{
	string str_temp;

	printf("\n按任意字符继续:\n");
	cin >> str_temp;
}

bool QuoteDemo::LoadEESQuote()
{
#ifdef WIN32
	
	return Windows_LoadEESQuote();

#else
	
	return Linux_LoadEESQuote();

#endif
}

void QuoteDemo::UnloadEESQuote()
{
#ifdef WIN32

	return Windows_UnloadEESQuote();

#else

	return Linux_UnloadEESQuote();

#endif
}

bool QuoteDemo::Windows_LoadEESQuote()
{
#ifdef WIN32

	m_handle =  LoadLibrary(EES_QUOTE_DLL_NAME);
	if (!m_handle)
	{
		printf("加载EES行情动态库(%s)失败\n", EES_QUOTE_DLL_NAME);
		return false;
	}

	funcCreateEESQuoteApi createFun = (funcCreateEESQuoteApi)GetProcAddress(m_handle, CREATE_EES_QUOTE_API_NAME);
	if (!createFun)
	{
		printf("获取EES行情接口函数地址(%s)失败!\n", CREATE_EES_QUOTE_API_NAME);
		return false;
	}

	m_distoryFun = (funcDestroyEESQuoteApi)GetProcAddress(m_handle, DESTROY_EES_QUOTE_API_NAME);
	if (!createFun)
	{
		printf("获取EES行情接口函数地址(%s)失败!\n", DESTROY_EES_QUOTE_API_NAME);
		return false;
	}

	m_eesApi = createFun();
	if (!m_eesApi)
	{
		printf("创建EES行情对象失败!\n");
		return false;
	}

#endif

	return true;
}
void QuoteDemo::Windows_UnloadEESQuote()
{
#ifdef WIN32
	if (m_eesApi)
	{
		m_distoryFun(m_eesApi);
		m_eesApi = NULL;
		m_distoryFun = NULL;
	}

	if (m_handle)
	{
		FreeLibrary(m_handle);
		m_handle = NULL;
	}
#endif
}

bool QuoteDemo::Linux_LoadEESQuote()
{
#ifndef WIN32
	m_handle =  dlopen(EES_QUOTE_DLL_NAME, RTLD_LAZY);
	if (!m_handle)
	{
		printf("加载EES行情动态库(%s)失败\n", EES_QUOTE_DLL_NAME);
		return false;
	}

	funcCreateEESQuoteApi createFun = (funcCreateEESQuoteApi)dlsym(m_handle, CREATE_EES_QUOTE_API_NAME);
	if (!createFun)
	{
		printf("获取EES创建函数地址失败!\n");
		return false;
	}

	m_distoryFun = (funcDestroyEESQuoteApi)dlsym(m_handle, DESTROY_EES_QUOTE_API_NAME);
	if (!createFun)
	{
		printf("获取EES销毁函数地址失败!\n");
		return false;
	}

	m_eesApi = createFun();
	if (!m_eesApi)
	{
		printf("创建EES行情对象失败!\n");
		return false;
	}

#endif

	return true;
}

void QuoteDemo::Linux_UnloadEESQuote()
{
#ifndef WIN32
	if (m_eesApi)
	{
		m_distoryFun(m_eesApi);
		m_eesApi = NULL;
		m_distoryFun = NULL;
	}

	if (m_handle)
	{
		dlclose(m_handle);
		m_handle = NULL;
	}
#endif
}


void QuoteDemo::InputParam()
{
	

	m_quoteServerIp = "119.188.3.12";
	m_quotePort = 20006;
	m_logonId = "27800310";
	m_logonPwd = "123456";

	string str_temp;
	string str_no = "n";

	cout << "IP		: " << m_quoteServerIp << endl;
	cout << "PORT	: " << m_quotePort << endl;
	cout << "USER	: " << m_logonId << endl;
	cout << "PWD	: " << m_logonPwd << endl;
	cout << "ancontinue  ";

	EqsTcpInfo tcp_info;

	sprintf(tcp_info.m_eqsId, "1");
	sprintf(tcp_info.m_eqsIp, "%s", m_quoteServerIp.c_str());
	tcp_info.m_eqsPort = m_quotePort;
	tcp_info.m_quote_source_type = 0x0F;
//	m_need_quote_type = 0x0F;

	m_vec_ServerInfo.push_back(tcp_info);
	memset(&tcp_info, 0, sizeof(EqsTcpInfo));

//	sprintf(tcp_info.m_eqsId, "2");
//	sprintf(tcp_info.m_eqsIp, "10.1.59.22" );
//	tcp_info.m_eqsPort = 20006;
//	tcp_info.m_quote_source_type = 0x0F;
//
//	m_vec_ServerInfo.push_back(tcp_info);
//	memset(&tcp_info, 0, sizeof(EqsTcpInfo));
//
//	sprintf(tcp_info.m_eqsId, "3");
//	sprintf(tcp_info.m_eqsIp, "10.1.51.29");
//	tcp_info.m_eqsPort = 20006;
//	tcp_info.m_quote_source_type = 0x0F;
//
//	m_vec_ServerInfo.push_back(tcp_info);
//	memset(&tcp_info, 0, sizeof(EqsTcpInfo));
//
//	sprintf(tcp_info.m_eqsId, "4");
//	sprintf(tcp_info.m_eqsIp, "10.1.59.70");
//	tcp_info.m_eqsPort = 20006;
//	tcp_info.m_quote_source_type = 0x0F;
//
//	m_vec_ServerInfo.push_back(tcp_info);


//	bool				b_key = true;
//	char				c_temp;
//	string				str_temp;
//	string				str_no = "n";
//
//	string				str_quoteServerIp = "119.188.3.12";
//	int					i_quotePort = 20006;
//	EqsTcpInfo			tcp_info;
//
//	m_logonId = "27800310";
//	m_logonPwd = "123456";
//
//	do
//	{
//		cout << "IP		: " << str_quoteServerIp << endl;
//		cout << "PORT	: " << i_quotePort << endl;
//		cout << "USER	: " << m_logonId << endl;
//		cout << "PWD	: " << m_logonPwd << endl;
//		cout << "USING DEFAULT? (y/n) ";
//		cin >> str_temp;
//		if (str_no != str_temp)
//		{
//			break;
//		}
//
//		cout << "USING DEFAULT USER " << m_logonId << " (y/n) ";
//		cin >> str_temp;
//		if (str_no == str_temp)
//		{
//			cout << "ENTER NEW USER: ";
//			cin >> str_temp;
//			m_logonId = str_temp;
//		}
//
//		cout << "USING DEFAULT PWD " << m_logonPwd << " (y/n) ";
//		cin >> str_temp;
//		if (str_no == str_temp)
//		{
//			cout << "ENTER NEW PWD: ";
//			cin >> str_temp;
//			m_logonPwd = str_temp;
//		}
//
//	} while (0);
//
//	cout << "NEED SSE_OPT" << " (y/n) ";
//	cin >> str_temp;
//	if (str_no != str_temp)
//	{
//		m_c_need_quote_type |= SSE_OPT;
//	}
//
//	cout << "NEED SSE_CS" << " (y/n) ";
//	cin >> str_temp;
//	if (str_no != str_temp)
//	{
//		m_c_need_quote_type |= SSE_CS;
//	}
//
//	cout << "NEED SZE_OPT" << " (y/n) ";
//	cin >> str_temp;
//	if (str_no != str_temp)
//	{
//		m_c_need_quote_type |= SZE_OPT;
//	}
//
//	cout << "NEED SZE_CS" << " (y/n) ";
//	cin >> str_temp;
//	if (str_no != str_temp)
//	{
//		m_c_need_quote_type |= SZE_CS;
//	}
//
//	// 配置多个行情服务信息
//	while(b_key)
//	{
//		c_temp &= 0x0000;
//		memset(&tcp_info, 0, sizeof(EqsTcpInfo));
//
//		cout << "USING DEFAULT IP " << str_quoteServerIp << " (y/n) ";
//		cin >> str_temp;
//		if (str_no == str_temp)
//		{
//			cout << "ENTER NEW IP: ";
//			cin >> str_temp;
//			str_quoteServerIp = str_temp;
//		}
//
//		cout << "USING DEFAULT PORT " << i_quotePort << " (y/n) ";
//		cin >> str_temp;
//		if (str_no == str_temp)
//		{
//			cout << "ENTER NEW PORT: ";
//			cin >> str_temp;
//			i_quotePort = atoi(str_temp.c_str());
//		}
//
//
//		/*
//		SSE_OPT = 0x0001, 上海期权
//		SSE_CS = 0x0002,  上海证券
//		SZE_OPT = 0x0004, 深圳期权
//		SZE_CS = 0x0008,  深圳证券
//		*/
//
//
//		cout << "QUOTE_TYPE SSE_OPT" << " (y/n) ";
//		cin >> str_temp;
//		if (str_no != str_temp)
//		{
//			c_temp |= SSE_OPT;
//		}
//
//		cout << "QUOTE_TYPE SSE_CS" << " (y/n) ";
//		cin >> str_temp;
//		if (str_no != str_temp)
//		{
//			c_temp |= SSE_CS;
//		}
//
//		cout << "QUOTE_TYPE SZE_OPT" << " (y/n) ";
//		cin >> str_temp;
//		if (str_no != str_temp)
//		{
//			c_temp |= SZE_OPT;
//		}
//
//		cout << "QUOTE_TYPE SZE_CS" << " (y/n) ";
//		cin >> str_temp;
//		if (str_no != str_temp)
//		{
//			c_temp |= SZE_CS;
//		}
//
//		sprintf(tcp_info.m_eqsIp, "%s", str_quoteServerIp.c_str());
//		tcp_info.m_eqsPort = i_quotePort;
//		tcp_info.m_quote_source_type = c_temp;
//
//		m_vec_ServerInfo.push_back(tcp_info);
//
//		cout << "ADD AGAIN ?" << " (y/n) ";
//		cin >> str_temp;
//		if (str_no == str_temp)
//		{
//			b_key = false;
//		}
//	}
	
}


void QuoteDemo::Logon()
{
}


void QuoteDemo::ShowQuote(EESMarketDepthQuoteData* pDepthQuoteData)
{
	printf("-------------EESMarketDepthQuoteData-----------------\n");
	printf("TradingDay:%s\n", pDepthQuoteData->TradingDay);
	printf("InstrumentID:%s\n", pDepthQuoteData->InstrumentID);
	printf("ExchangeID:%s\n", pDepthQuoteData->ExchangeID);
	printf("ExchangeInstID:%s\n", pDepthQuoteData->ExchangeInstID);
	printf("LastPrice:%.2f\n", pDepthQuoteData->LastPrice.get_double());
	printf("PreSettlementPrice:%.2f\n", pDepthQuoteData->PreSettlementPrice.get_double());
	printf("PreClosePrice:%.2f\n", pDepthQuoteData->PreClosePrice.get_double());
	//printf("PreOpenInterest:%.2f\n", pDepthQuoteData->PreOpenInterest);
	printf("PreOpenInterest:%lld\n", pDepthQuoteData->PreOpenInterest);
	printf("OpenPrice:%.2f\n", pDepthQuoteData->OpenPrice.get_double());
	printf("HighestPrice:%.2f\n", pDepthQuoteData->HighestPrice.get_double());
	printf("LowestPrice:%.2f\n", pDepthQuoteData->LowestPrice.get_double());
	printf("Volume:%lld\n", pDepthQuoteData->Volume);
	printf("Turnover:%.2f\n", pDepthQuoteData->Turnover.get_double());
	//printf("OpenInterest:%.2f\n", pDepthQuoteData->OpenInterest);
	printf("OpenInterest:%lld\n", pDepthQuoteData->OpenInterest);
	printf("ClosePrice:%.2f\n", pDepthQuoteData->ClosePrice.get_double());
	printf("SettlementPrice:%.2f\n", pDepthQuoteData->SettlementPrice.get_double());
	printf("UpperLimitPrice:%.2f\n", pDepthQuoteData->UpperLimitPrice.get_double());
	printf("LowerLimitPrice:%.2f\n", pDepthQuoteData->LowerLimitPrice.get_double());
	printf("PreDelta:%.2f\n", pDepthQuoteData->PreDelta.get_double());
	printf("CurrDelta:%.2f\n", pDepthQuoteData->CurrDelta.get_double());
	printf("UpdateTime:%s\n", pDepthQuoteData->UpdateTime);
	printf("UpdateMillisec:%d\n", pDepthQuoteData->UpdateMillisec);

	printf("BidPrice1:%.2f\n", pDepthQuoteData->BidPrice1.get_double());
	printf("BidVolume1:%d\n", pDepthQuoteData->BidVolume1);
	printf("AskPrice1:%.2f\n", pDepthQuoteData->AskPrice1.get_double());
	printf("AskVolume1:%d\n", pDepthQuoteData->AskVolume1);
	printf("BidPrice2:%.2f\n", pDepthQuoteData->BidPrice2.get_double());
	printf("BidVolume2:%d\n", pDepthQuoteData->BidVolume2);
	printf("AskPrice2:%.2f\n", pDepthQuoteData->AskPrice2.get_double());
	printf("AskVolume2:%d\n", pDepthQuoteData->AskVolume2);
	printf("BidPrice3:%.2f\n", pDepthQuoteData->BidPrice3.get_double());
	printf("BidVolume3:%d\n", pDepthQuoteData->BidVolume3);
	printf("AskPrice3:%.2f\n", pDepthQuoteData->AskPrice3.get_double());
	printf("AskVolume3:%d\n", pDepthQuoteData->AskVolume3);
	printf("BidPrice4:%.2f\n", pDepthQuoteData->BidPrice4.get_double());
	printf("BidVolume4:%d\n", pDepthQuoteData->BidVolume4);
	printf("AskPrice4:%.2f\n", pDepthQuoteData->AskPrice4.get_double());
	printf("AskVolume4:%d\n", pDepthQuoteData->AskVolume4);
	printf("AskPrice5:%.2f\n", pDepthQuoteData->AskPrice5.get_double());
	printf("AskVolume5:%d\n", pDepthQuoteData->AskVolume5);
	printf("BidPrice5:%.2f\n", pDepthQuoteData->BidPrice5.get_double());
	printf("BidVolume5:%d\n", pDepthQuoteData->BidVolume5);
	printf("AveragePrice:%.2f\n", pDepthQuoteData->AveragePrice.get_double());
	/*
	printf("BidPrice1:%.2f\n", pDepthQuoteData->BidPrice1);
	printf("BidVolume1:%lld\n", pDepthQuoteData->BidVolume1);
	printf("AskPrice1:%.2f\n", pDepthQuoteData->AskPrice1);
	printf("AskVolume1:%lld\n", pDepthQuoteData->AskVolume1);
	printf("BidPrice2:%.2f\n", pDepthQuoteData->BidPrice2);
	printf("BidVolume2:%lld\n", pDepthQuoteData->BidVolume2);
	printf("AskPrice2:%.2f\n", pDepthQuoteData->AskPrice2);
	printf("AskVolume2:%lld\n", pDepthQuoteData->AskVolume2);
	printf("BidPrice3:%.2f\n", pDepthQuoteData->BidPrice3);
	printf("BidVolume3:%lld\n", pDepthQuoteData->BidVolume3);
	printf("AskPrice3:%.2f\n", pDepthQuoteData->AskPrice3);
	printf("AskVolume3:%lld\n", pDepthQuoteData->AskVolume3);
	printf("BidPrice4:%.2f\n", pDepthQuoteData->BidPrice4);
	printf("BidVolume4:%lld\n", pDepthQuoteData->BidVolume4);
	printf("AskPrice4:%.2f\n", pDepthQuoteData->AskPrice4);
	printf("AskVolume4:%lld\n", pDepthQuoteData->AskVolume4);
	printf("AskPrice5:%.2f\n", pDepthQuoteData->AskPrice5);
	printf("AskVolume5:%lld\n", pDepthQuoteData->AskVolume5);
	printf("BidPrice5:%.2f\n", pDepthQuoteData->BidPrice5);
	printf("BidVolume5:%lld\n", pDepthQuoteData->BidVolume5);
	printf("AveragePrice:%.2f\n", pDepthQuoteData->AveragePrice);
	*/

	printf("\n");
}

void QuoteDemo::OnEqsConnected()
{
	printf("--------------OnEqsConnected----------------\n");
	printf("connected");
	printf("\n");

	Logon();
}

void QuoteDemo::OnEqsDisconnected()
{
	printf("--------------OnEqsDisconnected----------------\n");
	printf("disconnected");
	printf("\n");
}

void QuoteDemo::OnLoginResponse(const char* eqsId, bool bSuccess, const char* pReason)
{
	printf("-------------OnLoginResponse-----------------\n");
	if (bSuccess)
	{
		printf("login successed");
		m_eesApi->QuerySymbolList(eqsId);

		m_b_logoned = true;
	}
	else
	{
		printf("login failed, reason:%s", pReason);
	}

    // 添加以下调试输出语句，以查看函数是否被调用
    printf("OnLoginResponse called\n");
	
	printf("\n");
}

void QuoteDemo::OnQuoteUpdated(EqsExchangeId exchangeId, EESMarketDepthQuoteData* pDepthQuoteData)
{
	ShowQuote(pDepthQuoteData);
}

void QuoteDemo::OnWriteTextLog(EesEqsLogLevel nlevel, const char* pLogText, int nLogLen)
{
	printf("--------------OnWriteTextLog----------------\n");
	printf("OnWriteTextLog called, %s", pLogText);
	printf("\n");
}

void QuoteDemo::OnSymbolRegisterResponse(EqsExchangeId exchangeId, const char* pSymbol, bool bSuccess)
{
	printf("--------------OnSymbolRegisterResponse---------------\n");
	printf("RegisterSymbol %s %s %s", exchangeId == EQS_EXCHANGE_SH ? "SHH" : "SHZ", pSymbol, bSuccess ? "successed" : "failed");
	printf("\n");
}

void QuoteDemo::OnSymbolUnregisterResponse(EqsExchangeId exchangeId, const char* pSymbol, bool bSuccess)
{
	printf("--------------OnSymbolUnregisterResponse----------------\n");
	printf("Unregister %s %s %s", exchangeId == EQS_EXCHANGE_SH ? "SHH" : "SHZ", pSymbol, bSuccess ? "successed" : "failed");
	printf("\n");
}

void QuoteDemo::OnSymbolListResponse(const char* eqsId, EqsExchangeId exchangeId, const char* pSymbol, bool bLast)
{
	printf("---------------OnSymbolListResponse---------------\n");
	printf("Recv Symbol %s %s", exchangeId == EQS_EXCHANGE_SH ? "SHH" : "SHZ", pSymbol);
	printf("\n");

	string strSymbol = pSymbol;
	if (!strSymbol.empty() && m_regSymCount < 10)
	{
		if ( strcmp(pSymbol, "10001772") == 0 || 
			strcmp(pSymbol, "510050") == 0  ) 
		{
			m_eesApi->RegisterSymbol(exchangeId, pSymbol, eqsId);
			++m_regSymCount;
		}
	}
}

void QuoteDemo::OnQuerySymbolQuoteResponse(EqsExchangeId exchangeId, const char* pSymbol, EESMarketDepthQuoteData* pDepthQuoteData)
{
    printf("---------------OnQuerySymbolQuoteResponse---------------\n");
    printf("Recv Symbol %s %s", exchangeId == EQS_EXCHANGE_SH ? "SHH" : "SHZ", pSymbol);
	printf("\n");

	printf("--------------EESMarketDepthQuoteData-----------------\n");
	printf("TradingDay:%s\n", pDepthQuoteData->TradingDay);
	printf("InstrumentID:%s\n", pDepthQuoteData->InstrumentID);
	printf("ExchangeID:%s\n", pDepthQuoteData->ExchangeID);
	printf("ExchangeInstID:%s\n", pDepthQuoteData->ExchangeInstID);
	printf("LastPrice:%.2f\n", pDepthQuoteData->LastPrice.get_double());
	printf("PreSettlementPrice:%.2f\n", pDepthQuoteData->PreSettlementPrice.get_double());
	printf("PreClosePrice:%.2f\n", pDepthQuoteData->PreClosePrice.get_double());
	//printf("PreOpenInterest:%.2f\n", pDepthQuoteData->PreOpenInterest);
	printf("PreOpenInterest:%lld\n", pDepthQuoteData->PreOpenInterest);
	printf("OpenPrice:%.2f\n", pDepthQuoteData->OpenPrice.get_double());
	printf("HighestPrice:%.2f\n", pDepthQuoteData->HighestPrice.get_double());
	printf("LowestPrice:%.2f\n", pDepthQuoteData->LowestPrice.get_double());
	printf("Volume:%lld\n", pDepthQuoteData->Volume);
	printf("Turnover:%.2f\n", pDepthQuoteData->Turnover.get_double());
	//printf("OpenInterest:%.2f\n", pDepthQuoteData->OpenInterest);
	printf("OpenInterest:%lld\n", pDepthQuoteData->OpenInterest);
	printf("ClosePrice:%.2f\n", pDepthQuoteData->ClosePrice.get_double());
	printf("SettlementPrice:%.2f\n", pDepthQuoteData->SettlementPrice.get_double());
	printf("UpperLimitPrice:%.2f\n", pDepthQuoteData->UpperLimitPrice.get_double());
	printf("LowerLimitPrice:%.2f\n", pDepthQuoteData->LowerLimitPrice.get_double());
	printf("PreDelta:%.2f\n", pDepthQuoteData->PreDelta.get_double());
	printf("CurrDelta:%.2f\n", pDepthQuoteData->CurrDelta.get_double());
	printf("UpdateTime:%s\n", pDepthQuoteData->UpdateTime);
	printf("UpdateMillisec:%d\n", pDepthQuoteData->UpdateMillisec);

	printf("BidPrice1:%.2f\n", pDepthQuoteData->BidPrice1.get_double());
	printf("BidVolume1:%d\n", pDepthQuoteData->BidVolume1);
	printf("AskPrice1:%.2f\n", pDepthQuoteData->AskPrice1.get_double());
	printf("AskVolume1:%d\n", pDepthQuoteData->AskVolume1);
	printf("BidPrice2:%.2f\n", pDepthQuoteData->BidPrice2.get_double());
	printf("BidVolume2:%d\n", pDepthQuoteData->BidVolume2);
	printf("AskPrice2:%.2f\n", pDepthQuoteData->AskPrice2.get_double());
	printf("AskVolume2:%d\n", pDepthQuoteData->AskVolume2);
	printf("BidPrice3:%.2f\n", pDepthQuoteData->BidPrice3.get_double());
	printf("BidVolume3:%d\n", pDepthQuoteData->BidVolume3);
	printf("AskPrice3:%.2f\n", pDepthQuoteData->AskPrice3.get_double());
	printf("AskVolume3:%d\n", pDepthQuoteData->AskVolume3);
	printf("BidPrice4:%.2f\n", pDepthQuoteData->BidPrice4.get_double());
	printf("BidVolume4:%d\n", pDepthQuoteData->BidVolume4);
	printf("AskPrice4:%.2f\n", pDepthQuoteData->AskPrice4.get_double());
	printf("AskVolume4:%d\n", pDepthQuoteData->AskVolume4);
	printf("AskPrice5:%.2f\n", pDepthQuoteData->AskPrice5.get_double());
	printf("AskVolume5:%d\n", pDepthQuoteData->AskVolume5);
	printf("BidPrice5:%.2f\n", pDepthQuoteData->BidPrice5.get_double());
	printf("BidVolume5:%d\n", pDepthQuoteData->BidVolume5);
	printf("AveragePrice:%.2f\n", pDepthQuoteData->AveragePrice.get_double());

}
