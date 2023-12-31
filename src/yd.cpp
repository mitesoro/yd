#if defined(__linux__)
	#include <sys/socket.h>
	#include<unistd.h>    // close(关闭描述符)
	#include<arpa/inet.h> // 协议字段
#endif

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstdlib>
#include<set>
#include<unordered_map>
#include<yd.h>
#include <hiredis/hiredis.h>
#include <json.hpp>
#include <ctime>

using namespace std;

const unsigned MAX_POSITION_COUNT = 100; // 持仓查询返回最大条数
const unsigned MAX_TRADE_COUNT = 100;   // 成交查询返回最大条数
const unsigned MAX_ORDER_COUNT = 100;   // 报单查询返回最大条数

string stringToUpper(string &inputString)
{
	for (char &c : inputString)
		c = toupper(c);
	return inputString;
}

vector<string> splitCmdLine(string &cmdLine)
{
	vector<string>cmdWords;
	for (int i = 1, j = 0 ; i < cmdLine.size(); ++i)
	{
		if ((!isspace(cmdLine[i-1])) && (isspace(cmdLine[i])))
		{
			cmdWords.push_back(cmdLine.substr(j, i - j));
			j = i + 1;
		}
		if (i == (cmdLine.size() - 1))
			cmdWords.push_back(cmdLine.substr(j, i - j + 1));
	}
	return cmdWords;
}

void print_yd_config(const string &fname)
{
	// 读取易达配置文件关键信息
	ifstream infile(fname);
	string serverIP, tradeTCPPort, udpTrading, line;
	size_t pos;
	if (infile)
	{
		while (getline(infile, line))
		{
			if (line[0] != '#')
			{
				if (line.find("TradingServerIP=") != string::npos)
				{
					pos = line.find("=");
					serverIP = line.substr(pos + 1);
					cout << "serverIP " << serverIP << endl;
				}
				else if (line.find("TradingServerPort=") != string::npos)
				{
					pos = line.find("=");
					tradeTCPPort = line.substr(pos + 1);
					cout << "tradeTCPPort " << tradeTCPPort << endl;
				}
				else if (line.find("UDPTrading=") != string::npos)
				{
					pos = line.find("=");
					udpTrading = line.substr(pos + 1);
					cout << "udptrading " << udpTrading	<< endl;
				}
			}
		}
	}
	else{
		cerr << "读取" << fname << "失败" << endl;
	}
	infile.close();
}

void getServerIP(const string &fname, string &serverIP)
{
	// 读取易达配置文件关键信息
	ifstream infile(fname);
	string YDserverIP, line;
	size_t pos;
	if (infile)
	{
		while (getline(infile, line))
		{
			if (line.find("TradingServerIP=") != string::npos)
			{
				pos = line.find("=");
				YDserverIP = line.substr(pos + 1);
				serverIP = YDserverIP;
				serverIP = serverIP.substr(0, serverIP.length() - 1);
				break;
			}
		}
	}
}

void read_and_print_user_info(const string &fname, string &userID, string &pwd, string &appID, string &authCode, string &exchangeID, string &ydApiFunc, string &useProtocol, string &udpTradePort)
{
	ifstream infile(fname);
	string line, key, value;
	istringstream is;
	if (infile)
	{
		//cout << "读取当前配置文件" << endl;
		while (getline(infile, line) && !line.empty())
		{
			if (line[0] == '#')
				continue;
			is.str(line);
			is >> key >> value;
			cout << key << " " << value << endl;
			if (key == "userid")
				userID = value;
			else if (key == "pwd")
				pwd = value;
			else if (key == "appid")
				appID = value;
			else if (key == "authcode")
				authCode = value;
			else if (key == "exchangeid")
				exchangeID = value;
			else if (key == "ydapifunc")
				ydApiFunc = value;
			else if (key == "useprotocol")
				useProtocol = value;
			else if (key == "udptradeport")
				udpTradePort = value;
			else
				cerr << "\t用户信息文件字段有误" << endl;
			is.clear();
		}
	}
	else
		cerr << "\t打开用户信息文件失败" << endl;
	infile.close();
}

myYDListener * get_plistener(redisContext* context,string &ydApiFunc, string &userID, string &pwd, string &appID, string &authCode, string &exchangeID, string useProtocol, string udpTradeIP, string udpTradePort)
{
	const char *fname = "../config_files/config.txt";
	if (ydApiFunc == "extended" && useProtocol == "no")
	{
		YDExtendedApi *ydApi = makeYDExtendedApi(fname);
		return new myYDListener(ydApi, context,userID.c_str(), pwd.c_str(), appID.c_str(), authCode.c_str(), exchangeID);
	}
	else if (ydApiFunc == "extended" && useProtocol == "yes")
	{
		YDExtendedApi *ydApi = makeYDExtendedApi(fname);
		return new myYDListenerUDP(ydApi, context,userID.c_str(), pwd.c_str(), appID.c_str(), authCode.c_str(), exchangeID, udpTradeIP, udpTradePort);
	}
	else
	{
		cerr << "配置文件模式输入错误" << endl;
		exit(1);
	}
}

// ==========================================   myYDListener 成员函数  ================================================
// myYDListener的构造函数
myYDListener::myYDListener(YDApi *ydApi, redisContext* context, const char *userID, const char *pwd, const char *appID, const char *authCode, string exchangeID) : m_ydApi(ydApi), m_context(context), m_userID(userID), m_pwd(pwd), m_appID(appID), m_authCode(authCode)
{
    cout << "-----------------"<< exchangeID << "\n"<< endl;
	m_exchangeID = stringToUpper(exchangeID);
	if (!m_ydApi->start(this))
		cout << "无法启动ydApi" << endl;
	else
		cout << "成功启动ydApi" << endl;
}

void myYDListener::notifyReadyForLogin(bool hasLoginFailed)
{
	cout << "notifyReadyForLogin:: hasLoginFailed: " << hasLoginFailed << endl;
}

void myYDListener::login()
{
	if (!m_ydApi->login(m_userID, m_pwd, m_appID, m_authCode))
		cout << "\t无法登录" << endl;
}

void myYDListener::notifyLogin(int errorNo, int maxOrderRef, bool isMonitor)
{

	if (errorNo)
		cerr << "\tnotifyLogin::登录失败，错误码：" << errorNo << endl;
	else
	{
		cout << "\tnotifyLogin::登录成功" << endl;
		m_maxOrderRef = maxOrderRef;
	}
}

void myYDListener::notifyEvent(int apiEvent)
{
    // 调用 getCurrentTimeAsString 函数获取当前时间的字符串表示
    std::string currentTimeString = getCurrentTimeAsString();
    cout << "\t"<< currentTimeString <<" notifyEvent:: 事件回调，事件类型：" << apiEvent  << endl;
}

std::string myYDListener::getCurrentTimeAsString() {
    // 获取当前时间
    std::time_t currentTime = std::time(nullptr);

    // 将当前时间转换为本地时间
    std::tm* localTime = std::localtime(&currentTime);

    // 使用 strftime 函数将本地时间格式化为字符串
    char timeString[100];
    std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);

    // 返回当前时间的字符串表示
    return {timeString};
}

void myYDListener::notifyFinishInit()
{
	m_pExchange = m_ydApi->getExchangeByID(m_exchangeID.c_str());
	cout << "\tnotifyFinishInit::完成初始化" << endl;
	const YDAccount * pAccount = m_ydApi->getAccount(0);
	cout << "AccountFlag=" << pAccount->AccountFlag << endl;
}

void myYDListener::disconnect()
{
	m_ydApi->disconnect();
	cout << "\t与服务器的连接已断开" << endl;
}

void myYDListener::chgPwd(string &oldPwd, string &newPwd)
{
	m_ydApi->changePassword(m_userID, oldPwd.c_str(), newPwd.c_str());
}

void myYDListener::notifyChangePassword(int errorNo)
{
	if (errorNo)
		cout << "\tnotifyChangePassword::密码修改失败" << endl;
	else
		cout << "\tnotifyChangePassword::密码修改成功" << endl;
}

void myYDListener::sub(string &instrumentID)
{
	const YDInstrument *ins = m_ydApi->getInstrumentByID(instrumentID.c_str());
	if (ins == nullptr)
		cerr << "\t订阅失败，合约代码错误：" << instrumentID << endl;
	else
	{
		if (m_ydApi->subscribe(ins))
			cout << instrumentID << "\t订阅成功" << endl;
		else
			cerr << "\t网络断开，订阅失败" << endl;
	}
}

void myYDListener::notifyMarketData(const YDMarketData *pMarketData)
{
//	cout << "\tnotifyMarketData::当前行情" << endl;
//	cout << "\t合约代码：" << pMarketData->m_pInstrument->InstrumentID;
//	cout << "\t交易日：" << pMarketData->TradingDay;
//	cout << "\t前结算价：" << pMarketData->PreSettlementPrice;
//	cout << "\t前收盘价：" << pMarketData->PreClosePrice;
//	cout << "\t前持仓量：" << pMarketData->PreOpenInterest;
//	cout << "\t涨停价：" << pMarketData->UpperLimitPrice;
//	cout << "\t跌停价：" << pMarketData->LowerLimitPrice;
//	cout << "\t最新价：" << pMarketData->LastPrice;
//	if (pMarketData->BidPrice)
//		cout << "\t买入价：" << pMarketData->BidPrice;
//	else
//		cout << "\t无买入价";
//	if (pMarketData->AskPrice)
//		cout << "\t卖出价：" << pMarketData->AskPrice;
//	else
//		cout << "\t无卖出价";
//	if (pMarketData->BidVolume)
//		cout << "\t买入量：" << pMarketData->BidVolume;
//	else
//		cout << "\t无买入量";
//	if (pMarketData->AskVolume)
//		cout << "\t卖出量：" << pMarketData->AskVolume;
//	else
//		cout << "\t无卖出量";
//	cout << "\t成交金额：" << pMarketData->Turnover;
//	cout << "\t持仓量：" << pMarketData->OpenInterest;
//	cout << "\t成交量：" << pMarketData->Volume;
//	cout << endl;

    // 将 YDMarketData 对象转换为 JSON
    nlohmann::json json;
    json["symbol_id"] = pMarketData->m_pInstrument->InstrumentID; // 合约代码
    json["instrument_ref"] = pMarketData->InstrumentRef; // 合约序号
    json["trading_day"] = pMarketData->TradingDay; // 交易日。
    json["pre_settlement_price"] = pMarketData->PreSettlementPrice; // 前结算价。
    json["pre_close_price"] = pMarketData->PreClosePrice; // 前收盘价。
    json["pre_open_interest"] = pMarketData->PreOpenInterest; // 前持仓量。
    json["upper_limit_price"] = pMarketData->UpperLimitPrice; // 涨停板价。
    json["lower_limit_price"] = pMarketData->LowerLimitPrice; // 跌停板价。
    json["last_price"] = pMarketData->LastPrice; // 最新价。
    json["bid_price"] = pMarketData->BidPrice; // 买入价。为零代表无买入价。
    json["ask_price"] = pMarketData->AskPrice; // 卖出价。为零代表无卖出价。
    json["bid_volume"] = pMarketData->BidVolume; // 买入量。为零代表无买入价。
    json["ask_volume"] = pMarketData->AskVolume; // 卖出量。为零代表无卖出价。
    json["turnover"] = pMarketData->Turnover; // 成交金额。
    json["open_interest"] = pMarketData->OpenInterest; // 持仓量。
    json["volume"] = pMarketData->Volume; // 成交量。
    json["time_stamp"] = pMarketData->TimeStamp; // 时间戳，是整数，表示从该交易日开始到此时间的毫秒数。每个交易日从17点开始，即17:00:00对应时间戳0。周一的时间和周六的不区分。
    json["average_price"] = pMarketData->AveragePrice; // 市场均价


    // 打印 JSON 字符串
//    std::cout << json.dump() << std::endl;

    const char* channel = "channel_name";
    std::string json1 = json.dump();

    // 构建命令参数数组
    const char* argv[3];
    size_t argvlen[3];

    argv[0] = "PUBLISH";
    argvlen[0] = strlen(argv[0]);

    argv[1] = channel;
    argvlen[1] = strlen(channel);

    argv[2] = json1.c_str();
    argvlen[2] = json1.length();

    redisReply* reply = (redisReply*)redisCommandArgv(m_context, 3, argv, argvlen);
    if (reply == NULL) {
        std::cout << "Failed to publish message" << std::endl;
    } else {
//        std::cout << "Message published: " << reply->integer << std::endl;
        freeReplyObject(reply);
    }
}

void myYDListener::unsub(string &instrumentID)
{
	const YDInstrument *ins = m_ydApi->getInstrumentByID(instrumentID.c_str());
	if (ins == nullptr)
		cerr << "\t取消订阅失败，合约代码错误：" << instrumentID << endl;
	else
	{
		if (m_ydApi->unsubscribe(ins))
			cout << "\t取消订阅成功" << endl;
		else
			cerr << "\t网络断开，取消订阅失败" << endl;
	}
}
// 定义参数类型
using Parameters = std::unordered_map<std::string, std::string>;

std::tuple<bool, int, int>  myYDListener::putOrder(const Parameters& params)
{
	YDInputOrder inputOrder{};
	memset(&inputOrder, 0, sizeof(inputOrder));
	// 默认市价(FAK)、投机
	inputOrder.OrderType = YD_ODT_Market;
	inputOrder.HedgeFlag = YD_HF_Speculation;
	inputOrder.YDOrderFlag = YD_YOF_Normal;
	inputOrder.ConnectionSelectionType = YD_CS_Any;
	const YDInstrument *pInstrument = nullptr;
    // 循环遍历参数字典
    for (const auto& entry : params) {
        const std::string& key = entry.first;
        const std::string& value = entry.second;

        if (key == "/c") {  // 合约
            pInstrument = m_ydApi->getInstrumentByID(value.c_str());
        } else if (key == "/p") {  // 价格
            inputOrder.Price = atof(value.c_str());
            if (inputOrder.Price > 0)
                inputOrder.OrderType = YD_ODT_Limit;
        } else if (key == "/v") {  // 数量
            inputOrder.OrderVolume = atoi(value.c_str());
        } else if (key == "buy") {  // 买
            inputOrder.Direction = YD_D_Buy;
        } else if (key == "sell") {  // 卖
            inputOrder.Direction = YD_D_Sell;
        } else if (key == "open") {  // 开仓
            inputOrder.OffsetFlag = YD_OF_Open;
        }else if (key == "close")  //平仓
            inputOrder.OffsetFlag = YD_OF_Close;
        else if (key == "closetoday") //平今
            inputOrder.OffsetFlag = YD_OF_CloseToday;
        else if (key == "closeyes")  //平老
            inputOrder.OffsetFlag = YD_OF_CloseYesterday;
        else if (key == "forceclose")  // 强平
            inputOrder.OffsetFlag = YD_OF_ForceClose;
        else if (key == "hedge")  //套保
            inputOrder.HedgeFlag = YD_HF_Hedge;
        else if (key == "spec")  //投机
            inputOrder.HedgeFlag = YD_HF_Speculation;
        else if (key == "arbi")  //套利
            inputOrder.HedgeFlag = YD_HF_Arbitrage;
        else if (key == "fak")  // FAK
            inputOrder.OrderType = YD_ODT_FAK;
        else if (key == "fok")   // FOK
            inputOrder.OrderType = YD_ODT_FOK;
    }
    inputOrder.OrderGroupID = 0;
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
    inputOrder.OrderRef = ++m_maxOrderRef;
    cout << "\tgetNextOrderRef OrderRef: " << inputOrder.OrderRef << endl;
//	if (ydExApi != nullptr)
//	{
//		if (ydExApi->checkAndInsertOrder(&inputOrder, pInstrument))
//		{
//			cout << "\t【报单检查正确，发送成功】" << endl;
//			cout << "\tcheckAndInsertOrder OrderRef: " << inputOrder.OrderRef << endl;
//            return std::make_tuple(true, inputOrder.OrderRef, 0);
//		}
//		else{
//            cout << "\t报单失败，错误码：" << inputOrder.ErrorNo << endl;
//            cout << "\tcheckAndInsertOrder OrderRef: " << inputOrder.OrderRef << endl;
//            return std::make_tuple(false, inputOrder.OrderRef, inputOrder.ErrorNo);
//        }
//	}
//	else
//	{
//		if (m_ydApi->insertOrder(&inputOrder, pInstrument))
//		{
//			cout << "\t【报单发送成功】" << endl;
//			cout << "\tinsertOrder OrderRef: " << inputOrder.OrderRef << endl;
//            return std::make_tuple(true, inputOrder.OrderRef, 0);
//		}
//		else{
//            cout << "\t报单发送失败，错误码：" << inputOrder.ErrorNo << endl;
//            cout << "\tinsertOrder OrderRef: " << inputOrder.OrderRef << endl;
//            return std::make_tuple(false, inputOrder.OrderRef, inputOrder.ErrorNo);
//        }
//	}

    if (m_ydApi->insertOrder(&inputOrder, pInstrument))
    {
        cout << "\t【报单发送成功】" << endl;
        cout << "\tinsertOrder OrderRef: " << inputOrder.OrderRef << endl;
        return std::make_tuple(true, inputOrder.OrderRef, 0);
    }
    else{
        cout << "\t报单发送失败，错误码：" << inputOrder.ErrorNo << endl;
        cout << "\tinsertOrder OrderRef: " << inputOrder.OrderRef << endl;
        return std::make_tuple(false, inputOrder.OrderRef, inputOrder.ErrorNo);
    }
}

void myYDListener::notifyOrder(const YDOrder *pOrder, const YDInstrument *pInstrument, const YDAccount *pAccount)
{

	if (pOrder->ErrorNo == 0)
	{
		cout << "\tnotifyOrder::交易所接受报单/撤单" << endl;
		cout << "\tOrderRef: " << pOrder->OrderRef << "\tOrderLocalID: " << pOrder->OrderLocalID;
		cout << "\tOrderSysID: " << pOrder->OrderSysID;
		cout << "\tLongOrderSysID: " << pOrder->LongOrderSysID;
		cout << "\t报单状态：";
		switch (pOrder->OrderStatus)
		{
		case YD_OS_Queuing:
			cout << "交易所确认报单(部成或未成)";
			break;
		case YD_OS_Canceled:
			cout << "报单已被撤销";
			break;
		case YD_OS_AllTraded:
			cout << "全部成交";
			break;
		default:
			cout << "未知";
		}
		cout << "\t报单已成交量：" << pOrder->TradeVolume;
		cout << endl;
	}
	else
	{
		cout << "\tnotifyOrder::交易所拒绝报单";
		cout << "\tOrderRef: " << pOrder->OrderRef;
		cout << "\t错误码：" << pOrder->ErrorNo;
		cout << endl;
	}

    // 将 YDMarketData 对象转换为 JSON
    nlohmann::json json;
    json["order_ref"] = pOrder->OrderRef; // 订单序号
    json["order_local_id"] = pOrder->OrderLocalID; // d
    json["long_order_sys_id"] = pOrder->LongOrderSysID; // d
    json["order_sys_id"] = pOrder->OrderSysID; // d
    json["order_status"] = pOrder->OrderStatus; // 报单状态
    json["trade_volume"] = pOrder->TradeVolume; // 报单已成交量
    json["error_no"] = pOrder->ErrorNo; // 交易日。

    const char* channel = "channel_notify_order";
    std::string json1 = json.dump();

    // 构建命令参数数组
    const char* argv[3];
    size_t argvlen[3];

    argv[0] = "PUBLISH";
    argvlen[0] = strlen(argv[0]);

    argv[1] = channel;
    argvlen[1] = strlen(channel);

    argv[2] = json1.c_str();
    argvlen[2] = json1.length();

    redisReply* reply = (redisReply*)redisCommandArgv(m_context, 3, argv, argvlen);
    if (reply == NULL) {
        std::cout << "Failed to publish message" << std::endl;
    } else {
//        std::cout << "Message published: " << reply->integer << std::endl;
        freeReplyObject(reply);
    }
}

void myYDListener::notifyFailedOrder(const YDInputOrder *pFailedOrder, const YDInstrument *pInstrument, const YDAccount *pAccount)
{
	cout << "\tnotifyFailedOrder::易达柜台拒绝报单" << endl;
	cout << "\tOrderRef: " << pFailedOrder->OrderRef;
	cout << "\t错误码：" << pFailedOrder->ErrorNo;
	cout << endl;
}

void myYDListener::notifyTrade(const YDTrade *pTrade, const YDInstrument *pInstrument, const YDAccount *pAccount)
{
	cout << "\tnotifyTrade::成交回报" << endl;
	cout << "\tOrderRef: " << pTrade->OrderRef;
	cout << "\tOrderSysID: " << pTrade->OrderSysID;
	cout << "\torderLocalID: " << pTrade->OrderLocalID;
	cout << "\t买卖方向：";
	switch (pTrade->Direction)
	{
	case YD_D_Buy:
		cout << "买";
		break;
	case YD_D_Sell:
		cout << "卖";
		break;
	default:
		cerr << "错误";
	}
	cout << "\t开平仓标志：";
	switch (pTrade->OffsetFlag)
	{
	case YD_OF_Open:
		cout << "开仓";
		break;
	case YD_OF_Close:
		cout << "平仓";
		break;
	case YD_OF_CloseToday:
		cout << "平今仓";
		break;
	case YD_OF_CloseYesterday:
		cout << "平历史仓";
		break;
	case YD_OF_ForceClose:
		cout << "强平";
		break;
	default:
		cerr << "错误";
 	}
	cout << "\t套保标志：";
	switch (pTrade->HedgeFlag)
	{
	case YD_HF_Speculation:
		cout << "投机";
		break;
	case YD_HF_Arbitrage:
		cout << "套利";
		break;
	case YD_HF_Hedge:
		cout << "保值";
		break;
	default:
		cerr << "未知";
	}
	cout << "\t成交价格：" << pTrade->Price;
	cout << "\t成交数量：" << pTrade->Volume;
	cout << endl;
}

void myYDListener::qryFund()
{
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
	if (ydExApi != nullptr)
	{
		const YDExtendedAccount *pAccount = ydExApi->getExtendedAccount();
		cout << fixed;
		cout << "\t平仓盈亏：" << pAccount->CloseProfit;
		cout << "\t权利金：" << pAccount->CashIn;
		cout << "\t所有非期货品种的平仓盈亏：" << pAccount->OtherCloseProfit;
		cout << "\t手续费：" << pAccount->Commission;
		cout << "\t保证金：" << pAccount->Margin;
		cout << "\t持仓盈亏：" << pAccount->PositionProfit;
		cout << "\t资金余额：" << pAccount->Balance;
		cout << "\t可用资金：" << pAccount->Available;
		cout << "\t用户报单数：" << pAccount->UsedOrderCount;
		cout << "\t期权执行保证金：" << pAccount->ExecMargin;
		cout << endl;
	}
	else
	{
		cout << "\t易达基础版不支持资金查询；";
		cout << "需根据报单、成交情况和当前价格自行计算平仓盈亏、期权品种现金出入、手续费、持仓盈亏、已使用保证金、当前余额和可用金额" << endl;
	}
}

void show_position_shfe_or_ine(const YDExtendedPosition *ppos)
{
	cout << "\t合约代码：" << ppos->getInstrument()->InstrumentID;
	cout << "\t持仓方向：";
	switch (ppos->PositionDirection)
	{
	case YD_PD_Long:
		cout << "多头";
		break;
	case YD_PD_Short:
		cout << "空头";
		break;
	default:
		cerr << "未知";
	}
	cout << "\t持仓量：" << ppos->Position;
	cout << "\t套保标志：";
	switch (ppos->HedgeFlag)
	{
	case YD_HF_Speculation:
		cout << "投机";
		break;
	case YD_HF_Hedge:
		cout << "保值";
		break;
	default:
		cerr << "未知";
	}
	cout << "\t持仓盈亏：" << ppos->PositionProfit;
	cout << "\t平仓盈亏：" << ppos->CloseProfit;
}

void myYDListener::qry_position_shfe_or_ine(YDExtendedApi *ydExApi)
{
	const YDExtendedPositionFilter history_pos_filter{ YD_PSD_History, -1, -1, NULL, NULL, NULL };
	const YDExtendedPosition *history_pos[MAX_POSITION_COUNT];
	unsigned total_count = ydExApi->findExtendedPositions(&history_pos_filter, MAX_POSITION_COUNT, history_pos);
	if (total_count > MAX_POSITION_COUNT)
		cout << "\t历史持仓记录总共有" << total_count << "条，返回的仅是部分持仓结果(100条)，需增大MAX_POSITION_COUNT参数来获得全部历史持仓" << endl;
	unsigned n = min(total_count, MAX_POSITION_COUNT);
	cout << "\t【历史仓】" << endl;
	for (size_t i = 0; i != n; ++i)
	{
		show_position_shfe_or_ine(history_pos[i]);
		cout << "\t-------------------------" << endl;
	}
	const YDExtendedPositionFilter today_pos_filter{ YD_PSD_Today, -1, -1, NULL, NULL, NULL };
	const YDExtendedPosition *today_pos[MAX_POSITION_COUNT];
	total_count = ydExApi->findExtendedPositions(&today_pos_filter, MAX_POSITION_COUNT, today_pos);
	if (total_count > MAX_POSITION_COUNT)
		cout << "\t今日持仓记录总共有" << total_count << "条，返回的仅是部分持仓结果(100条)，需增大MAX_POSITION_COUNT参数来获得全部今日持仓" << endl;
	n = min(total_count, MAX_POSITION_COUNT);
	cout << "\t【今仓】" << endl;
	for (size_t i = 0; i != n; ++i)
	{
		show_position_shfe_or_ine(today_pos[i]);
		cout << endl;
	}
}

void myYDListener::qry_position_cffex(YDExtendedApi *ydExApi)
{
	const YDExtendedPositionFilter pos_filter{ YD_PSD_History, -1, -1, NULL, NULL, NULL, NULL };
	const YDExtendedPosition *pos[MAX_POSITION_COUNT];
	unsigned total_count = ydExApi->findExtendedPositions(&pos_filter, MAX_POSITION_COUNT, pos);
	if (total_count > MAX_POSITION_COUNT)
		cout << "\t持仓记录总共有" << total_count << "条，返回的仅是部分持仓结果(100条)，需增大MAX_POSITION_COUNT参数来获得全部持仓" << endl;
	unsigned n = min(total_count, MAX_POSITION_COUNT);
	cout << "\t【总持仓】" << endl;
	for (size_t i = 0; i != n; ++i)
	{
		cout << "\t合约代码：" << pos[i]->getInstrument()->InstrumentID;
		cout << "\t持仓方向：";
		switch (pos[i]->PositionDirection)
		{
		case YD_PD_Long:
			cout << "多头";
			break;
		case YD_PD_Short:
			cout << "空头";
			//cout << "\tBaseMarginRate: " << pos[i]->getMarginRate()->BaseMarginRate;
			//cout << "\tLinearFactor: " << pos[i]->getMarginRate()->LinearFactor;
			//cout << "\tLowerBoundaryCoef: " << pos[i]->getMarginRate()->LowerBoundaryCoef;
			/*if (pos[i]->getInstrument()->OptionsType == YD_OT_CallOption)
				cout << "\t按金额计算保证金率：" << pos[i]->getMarginRate()->CallMarginRatioByMoney;
			else if (pos[i]->getInstrument()->OptionsType == YD_OT_PutOption)
				cout << "\t按金额计算保证金率：" << pos[i]->getMarginRate()->PutMarginRatioByMoney;
			else
				cerr << "错误的期权类型";*/
			break;
		default:
			cerr << "未知";
		}
		cout << "\t持仓量(剩余昨仓)：" << pos[i]->YDPositionForCommission;
		cout << "\t持仓量(总持仓)：" << pos[i]->Position;
		cout << "\t套保标志：";
		switch (pos[i]->HedgeFlag)
		{
		case YD_HF_Speculation:
			cout << "投机";
			break;
		case YD_HF_Arbitrage:
			cout << "套利";
			break;
		case YD_HF_Hedge:
			cout << "保值";
			break;
		default:
			cerr << "未知";
		}
		cout << "\t持仓盈亏：" << pos[i]->PositionProfit;
		cout << "\t平仓盈亏：" << pos[i]->CloseProfit;
		// cout << "\t非期货品种的平仓盈亏(期权)：" << pos[i]->OtherCloseProfit;
		cout << "\t保证金：" << pos[i]->Margin;

		/*cout << "\t按金额计算的开仓手续费率：" << pos[i]->getCommissionRate()->OpenRatioByMoney;
		cout << "\t按数量计算的开仓手续费率：" << pos[i]->getCommissionRate()->OpenRatioByVolume;
		cout << "\t按金额计算的平昨手续费率：" << pos[i]->getCommissionRate()->CloseRatioByMoney;
		cout << "\t按数量计算的平昨手续费率：" << pos[i]->getCommissionRate()->CloseRatioByVolume;
		cout << "\t按金额计算的平今手续费率：" << pos[i]->getCommissionRate()->CloseTodayRatioByMoney;
		cout << "\t按数量计算的平今手续费率：" << pos[i]->getCommissionRate()->CloseTodayRatioByVolume;
		cout << "\t按数量计算的报单手续费率：" << pos[i]->getCommissionRate()->OrderCommByVolume;
		cout << "\t按数量计算的撤单手续费率：" << pos[i]->getCommissionRate()->OrderActionCommByVolume;*/
		cout << endl;
	}
}

void myYDListener::qry_position_dce(YDExtendedApi *ydExApi)  // 与中金所的区别仅在于套保标志没有套利
{
	const YDExtendedPositionFilter pos_filter{ YD_PSD_History, -1, -1, NULL, NULL, NULL };
	const YDExtendedPosition *pos[MAX_POSITION_COUNT];
	unsigned total_count = ydExApi->findExtendedPositions(&pos_filter, MAX_POSITION_COUNT, pos);
	if (total_count > MAX_POSITION_COUNT)
		cout << "\t持仓记录总共有" << total_count << "条，返回的仅是部分持仓结果(100条)，需增大MAX_POSITION_COUNT参数来获得全部持仓" << endl;
	unsigned n = min(total_count, MAX_POSITION_COUNT);
	cout << "\t【总持仓】" << endl;
	for (size_t i = 0; i != n; ++i)
	{
		cout << "\t合约代码：" << pos[i]->getInstrument()->InstrumentID;
		cout << "\t持仓方向：";
		switch (pos[i]->PositionDirection)
		{
		case YD_PD_Long:
			cout << "多头";
			break;
		case YD_PD_Short:
			cout << "空头";
			break;
		default:
			cerr << "未知";
		}
		cout << "\t持仓量(剩余昨仓)：" << pos[i]->YDPositionForCommission;
		cout << "\t持仓量(总持仓)：" << pos[i]->Position;
		cout << "\t套保标志：";
		switch (pos[i]->HedgeFlag)
		{
		case YD_HF_Speculation:
			cout << "投机";
			break;
		case YD_HF_Hedge:
			cout << "保值";
			break;
		default:
			cerr << "未知";
		}
		cout << "\t持仓盈亏：" << pos[i]->PositionProfit;
		cout << "\t平仓盈亏：" << pos[i]->CloseProfit;
		cout << endl;
	}
}

void myYDListener::qryPosition()
{
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
	if (ydExApi != nullptr)
	{
		if ((m_exchangeID == "CFFEX") || (m_exchangeID == "SSE") || (m_exchangeID == "SZSE"))
			qry_position_cffex(ydExApi);
		else if ((m_exchangeID == "SHFE") || (m_exchangeID == "INE"))
			qry_position_shfe_or_ine(ydExApi);
		else if (m_exchangeID == "DCE")
			qry_position_dce(ydExApi);
		else
			cerr << "交易所代码有误，无法查询其持仓情况" << endl;
	}
	else
	{
		cout << "\t易达基础版不支持即时持仓查询，只能获取日初持仓" << endl;
		cout << "\t【日初持仓(静态数据)】" << endl;
		int n = m_ydApi->getPrePositionCount();
		for (int i = 0; i != n; ++i)
		{
			const YDPrePosition *pos = m_ydApi->getPrePosition(i);
			cout << "\t合约代码：" << pos->m_pInstrument->InstrumentID;
			cout << "\t持仓方向：";
			switch (pos->PositionDirection)
			{
			case YD_PD_Long:
				cout << "多头";
				break;
			case YD_PD_Short:
				cout << "空头";
				break;
			default:
				cerr << "未知";
			}
			cout << "\t套保标志：";
			switch (pos->HedgeFlag)
			{
			case YD_HF_Speculation:
				cout << "投机";
				break;
			case YD_HF_Hedge:
				cout << "保值";
				break;
			default:
				cerr << "未知";
			}
			cout << "\t昨持仓量：" << pos->PrePosition;
			cout << "\t昨结算价：" << pos->PreSettlementPrice;
			cout << endl;
		}
	}
}

void showOrder(const YDExtendedOrder *pOrder)
{
	cout << "\tOrderRef: " << pOrder->OrderRef;
	cout << "\tOrderSysID: " << pOrder->OrderSysID;
	cout << "\t合约代码: " << pOrder->m_pInstrument->InstrumentID;
	cout << "\t买卖方向：";
	switch (pOrder->Direction)
	{
	case YD_D_Buy:
		cout << "买";
		break;
	case YD_D_Sell:
		cout << "卖";
		break;
	default:
		cerr << "错误";
	}
	cout << "\t报单数量：" << pOrder->OrderVolume;
	cout << "\t开平仓标志：";
	switch (pOrder->OffsetFlag)
	{
	case YD_OF_Open:
		cout << "开仓";
		break;
	case YD_OF_Close:
		cout << "平仓";
		break;
	case YD_OF_CloseToday:
		cout << "平今仓";
		break;
	case YD_OF_CloseYesterday:
		cout << "平历史仓";
		break;
	case YD_OF_ForceClose:
		cout << "强平";
		break;
	default:
		cout << "错误";
	}
	cout << "\t报单状态：";
	switch (pOrder->OrderStatus)
	{
	case YD_OS_Queuing:
		cout << "交易所确认报单(部成或未成)";
		break;
	case YD_OS_Canceled:
		cout << "报单已被撤销";
		break;
	case YD_OS_AllTraded:
		cout << "全部成交";
		break;
	default:
		cout << "未知";
	}
	cout << "\t报单已成交量：" << pOrder->TradeVolume;
	cout << endl;
}

int myYDListener::qryOrderSys(int orderSysID)
{
	cout << "\t【orderSysID报单查询】" << endl;
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
	if (ydExApi != nullptr)
	{
		const YDExtendedOrder *pOrder = ydExApi->getOrder(orderSysID, m_pExchange);
		if (pOrder == nullptr){
            cerr << "\tOrderSysID错误，查无此单" << endl;
            return -1;
        }
		else{
            showOrder(pOrder);
            return pOrder->OrderStatus;
        }
	}
	else{
        cout << "\t易达基础版没有报单查询功能" << endl;
        return -1;
    }

}

int myYDListener::qryOrderRef(int orderRef)
{
	cout << "\t【orderRef报单查询】" << endl;
	cout << "\t" << orderRef << endl;
	const YDAccount *pAccount = m_ydApi->getAccount(0);
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
	if (ydExApi != nullptr)
	{
		const YDExtendedOrder *pOrder = ydExApi->getOrder(orderRef,0, pAccount);
		if (pOrder == nullptr){
            cerr << "\tOrderSysID错误，查无此单" << endl;
            return -1;
        }
        else{
            showOrder(pOrder);
            return pOrder->OrderStatus;
        }

	}
	else{
        cout << "\t易达基础版没有报单查询功能" << endl;
        return -1;
    }
}

void myYDListener::qryOrders()
{
	cout << "\t【报单查询】" << endl;
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
	if (ydExApi != nullptr)
	{
		const YDOrderFilter of{ -1, -1, -1, NULL, NULL, NULL, NULL, NULL };
		const YDExtendedOrder *orders[MAX_ORDER_COUNT];
		unsigned total_count = ydExApi->findOrders(&of, MAX_ORDER_COUNT, orders);
		if (total_count > MAX_ORDER_COUNT)
			cout << "\t报单总共有" << total_count << "条，返回的仅是部分报单(100条)，需增大MAX_ORDER_COUNT参数来获得全部报单" << endl;
		unsigned n = min(total_count, MAX_ORDER_COUNT);
		if (n == 0)
			cout << "\t没有报单" << endl;
		else
		{
			for (size_t i = 0; i != n; ++i)
				showOrder(orders[i]);
		}
	}
	else
		cout << "\t易达基础版没有报单查询功能" << endl;
}

void  myYDListener::qryTrade()
{
	cout << "\t【成交查询】" << endl;
	YDExtendedApi *ydExApi = static_cast<YDExtendedApi *>(m_ydApi);
	if (ydExApi != nullptr)
	{
		const YDTradeFilter tf{ -1, -1, NULL, NULL, NULL, NULL };
		const YDExtendedTrade *trades[MAX_TRADE_COUNT];
		unsigned total_count = ydExApi->findTrades(&tf, MAX_TRADE_COUNT, trades);
		if (total_count > MAX_TRADE_COUNT)
			cout << "\t成交记录总共有" << total_count << "条，返回的仅是部分成交结果(100条)，需增大MAX_TRADE_COUNT参数来获得全部成交" << endl;
		unsigned n = min(total_count, MAX_TRADE_COUNT);
		if (n == 0)
			cout << "\t无成交记录" << endl;
		else
		{
			for (size_t i = 0; i != n; ++i)
			{
				cout << "\tOrderRef: " << trades[i]->OrderRef;
				cout << "\tOrderSysID: " << trades[i]->OrderSysID;
				cout << "\t合约代码：" << trades[i]->m_pInstrument->InstrumentID;
				cout << "\t买卖方向：";
				switch (trades[i]->Direction)
				{
				case YD_D_Buy:
					cout << "买";
					break;
				case YD_D_Sell:
					cout << "卖";
					break;
				default:
					cerr << "错误";
				}
				cout << "\t开平仓标志：";
				switch (trades[i]->OffsetFlag)
				{
				case YD_OF_Open:
					cout << "开仓";
					break;
				case YD_OF_Close:
					cout << "平仓";
					break;
				case YD_OF_CloseToday:
					cout << "平今仓";
					break;
				case YD_OF_CloseYesterday:
					cout << "平历史仓";
					break;
				case YD_OF_ForceClose:
					cout << "强平";
					break;
				default:
					cerr << "错误";
				}
				cout << "\t套保标志：";
				switch (trades[i]->HedgeFlag)
				{
				case YD_HF_Speculation:
					cout << "投机";
					break;
				case YD_HF_Arbitrage:
					cout << "套利";
					break;
				case YD_HF_Hedge:
					cout << "保值";
					break;
				default:
					cerr << "未知";
				}
				cout << "\t成交价格：" << trades[i]->Price;
				cout << "\t成交数量：" << trades[i]->Volume;
				cout << endl;
			}
		}
	}
	else
		cout << "\t易达基础版没有成交单查询功能" << endl;
}

void myYDListener::cancelOrder(int orderSysID, int orderFlag)
{
	YDCancelOrder cancel_order;
	memset(&cancel_order, 0, sizeof(cancel_order));
	cancel_order.ConnectionSelectionType = YD_CS_Any;
	cancel_order.YDOrderFlag = orderFlag;
	cancel_order.OrderSysID = orderSysID;
    cancel_order.OrderGroupID = 5;
	if (m_ydApi->cancelOrder(&cancel_order, m_pExchange))
	{
		cout << "\t【撤单发送成功】" << endl;
		cout << "\t撤单OrderSysID: " << cancel_order.OrderSysID << endl;
	}
	else
		cout << "\t网络断开，发送撤单请求失败" << endl;
}

void myYDListener::notifyFailedCancelOrder(const YDFailedCancelOrder *pFailedCancelOrder, const YDExchange *pExchange, const YDAccount *pAccount)
{
	cout << "\tnotifyFailedCancelOrder::易达柜台拒绝撤单请求" << endl;
	cout << "\t撤单OrderSysID: " << pFailedCancelOrder->OrderSysID;
	cout << "\t错误码：" << pFailedCancelOrder->ErrorNo;
	cout << endl;
}

void myYDListener::notifyCaughtUp()
{
	cout << "\tmyYDListener::notifyCaughtUp::可以开始API下单" << endl;
}

myYDListenerUDP::myYDListenerUDP(YDApi *ydApi, redisContext* context,const char *userID, const char *pwd, const char *appID, const char *authCode, string exchangeID, string serverIP, string port):
myYDListener::myYDListener(ydApi, context,userID, pwd, appID, authCode, exchangeID)
{
	// 构造服务器地址结构体
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(atoi(port.c_str()));
	inet_pton(AF_INET, serverIP.c_str(), &m_addr.sin_addr.s_addr);
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket < 0)
	{
		cerr << "\t客户端socket创建失败" << endl;
		exit(1);
	}
	else
	{
		cout << "\t客户端socket创建成功" << endl;
	}
}

myYDListenerUDP::~myYDListenerUDP()
{
	close(m_socket);
}

void myYDListenerUDP::notifyCaughtUp()
{
	cout << "\tmyYDListenerUDP::notifyCaughtUp::可以开始裸协议下单" << endl;
}


order_raw_protocol myYDListenerUDP::put_protocol_helper(const Parameters& params) {
    order_raw_protocol pro;
    memset(&pro, 0, sizeof(order_raw_protocol));
    int n = m_ydApi->getClientPacketHeader(m_ydApi->YD_CLIENT_PACKET_INSERT_ORDER, pro.header, 16);
    if (n == 0) {
        cerr << "获取报单协议头失败" << endl;
    }

    // 默认市价、投机; 席位选定任意
    pro.orderType = 2;
    pro.hedgeFlag = 1;
    pro.connectionSelection = 0;
    pro.orderRef = ++m_maxOrderRef;

    if (params.find("/c") != params.end()) {  // 合约
        const std::string& instrument = params.at("/c");
        pro.instrumentRef = m_ydApi->getInstrumentByID(instrument.c_str())->InstrumentRef;
    }

    if (params.find("/p") != params.end()) {  // 价格
        const std::string& priceStr = params.at("/p");
        pro.price = atof(priceStr.c_str());
        if (pro.price > 0) {
            pro.orderType = 0;
        }
    }

    if (params.find("/v") != params.end()) {  // 数量
        const std::string& volumeStr = params.at("/v");
        pro.orderVolume = atoi(volumeStr.c_str());
    }

    if (params.find("buy") != params.end()) {  // 买
        pro.direction = 0;
    } else if (params.find("sell") != params.end()) {  // 卖
        pro.direction = 1;
    }

    if (params.find("open") != params.end()) {  // 开仓
        pro.offsetFlag = 0;
    } else if (params.find("close") != params.end()) {  // 平仓
        pro.offsetFlag = 1;
    } else if (params.find("closetoday") != params.end()) { // 平今
        pro.offsetFlag = 3;
    } else if (params.find("closeyes") != params.end()) {  // 平老
        pro.offsetFlag = 4;
    }

    if (params.find("hedge") != params.end()) {  // 套保
        pro.hedgeFlag = 3;
    } else if (params.find("spec") != params.end()) {  // 投机
        pro.hedgeFlag = 1;
    } else if (params.find("arbi") != params.end()) {  // 套利
        pro.hedgeFlag = 2;
    } else if (params.find("fak") != params.end()) {  // FAK
        pro.orderType = 1;
    } else if (params.find("fok") != params.end()) {  // FOK
        pro.orderType = 3;
    }

    return pro;
}


std::tuple<bool, int, int>  myYDListenerUDP::putOrder(const Parameters& params)
{
	order_raw_protocol pro = put_protocol_helper(params);
	if (sendto(m_socket, (char *)&pro, sizeof(order_raw_protocol), 0, (sockaddr *)&m_addr, sizeof(m_addr)) == -1){
        cerr << "裸协议报单(UDP)失败" << endl;
        return std::make_tuple(false, pro.orderRef, 0);
    }


	else
	{
		cout << "\t【裸协议报单(UDP)发送成功】" << endl;
		cout << "\tOrderRef: " << pro.orderRef << endl;
        return std::make_tuple(true, pro.orderRef, 0);
	}
}

cancel_raw_protocol myYDListenerUDP::cancel_protocol_helper(int orderSysID)
{
	cancel_raw_protocol pro;
	memset(&pro, 0, sizeof(cancel_raw_protocol));
	int n = m_ydApi->getClientPacketHeader(m_ydApi->YD_CLIENT_PACKET_CANCEL_ORDER, pro.header, 16);
	if (n == 0)
		cerr << "获取撤单协议头失败" << endl;
	pro.orderSysID = orderSysID;
	pro.exchangeRef = m_pExchange->ExchangeRef;
	pro.connectionSelection = 0;
	return pro;
}

void myYDListenerUDP::cancelOrder(int orderSysID, int orderFlag)
{
	cancel_raw_protocol pro = cancel_protocol_helper(orderSysID);
	if (sendto(m_socket, (char *)&pro, sizeof(cancel_raw_protocol), 0, (sockaddr *)&m_addr, sizeof(m_addr)) == -1)
		cerr << "裸协议撤单(UDP)失败" << endl;
	else
	{
		cout << "\t【裸协议撤单(UDP)发送成功】" << endl;
		cout << "\t撤单OrderSysID: " << pro.orderSysID << endl;
	}
}