/*! 
* \file  EESQuoteDefine.h
* \brief EES行情类型定义头文件
*  
* 此文件描述了使用EES行情的类型的定义
*  
* \author  SHENGLI
* \version 1.0
* \date    2014-04-18
*/  

#pragma  once 

#include <string.h>

/// \brief EES行情服务器EQS标识长度
#define EES_EQS_ID_LEN         15

/// \brief EES行情服务器EQS登录名长度
#define EES_EQS_USER_ID_LEN    32

/// \brief EES行情服务器EQS登录密码长度
#define EES_EQS_PASSWORD_LEN   32

/// \brief EES行情类型
enum EqsExchangeId
{
  EQS_INVALID_TYPE = 0, ///< 无效类型
  EQS_EXCHANGE_SH = 100,           ///< 上海股票
  EQS_EXCHANGE_SZ = 101,           ///< 深圳股票  
};

/// \brief 日志级别
enum EesEqsLogLevel
{
  QUOTE_LOG_LV_DEBUG = 0,  ///< 调试信息
  QUOTE_LOG_LV_INFO  = 1,  ///< 信息
  QUOTE_LOG_LV_WARN  = 2,  ///< 警告
  QUOTE_LOG_LV_ERROR = 3,  ///< 错误
  QUOTE_LOG_LV_FATAL = 4,  ///< 致命错误
  QUOTE_LOG_LV_USER  = 5,  ///< 用于给用户显示的消息
  QUOTE_LOG_LV_END         ///< 结尾标志
};

enum quote_source_type
{
	SSE_OPT = 0x01, /**< 上海期权 */
	SSE_CS = 0x02, /**< 上海证券 */
	SZE_OPT = 0x04, /**< 深圳期权 */
	SZE_CS = 0x08, /**< 深圳证券 */
};

#ifndef PRICE_TYPE
#define PRICE_TYPE
struct T_PRICE32_4
{
protected:
	int m_val;

public:
	T_PRICE32_4()
	{
		m_val = 0;
	}

	T_PRICE32_4(const double &val)
	{
		if (val >= 0)
			m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入		
		else
			m_val = (val - 0.00005) * 10000;
	}

	T_PRICE32_4& operator = (double val)
	{
		if (val >= 0)
			m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入		
		else
			m_val = (val - 0.00005) * 10000;

		return *this;
	}

	double get_double()	 const
	{
		return (double)(m_val) * 1.0 / 10000.0;
	}

	int get_long() const
	{
		return m_val;
	}

	bool operator > (const T_PRICE32_4 & obj)
	{
		return m_val > obj.m_val;
	}

	bool operator < (const T_PRICE32_4 & obj)
	{
		return m_val < obj.m_val;
	}

	bool operator == (const T_PRICE32_4 & obj)
	{
		return m_val == obj.m_val;
	}
};


///本结构体用于方便处理用Int64表示的，精确到最多4位小数的浮点类型，大多用于价格字段
struct T_PRICE_4
{
protected:
	long long int m_val;

public:
	T_PRICE_4()
	{
		m_val = 0;
	}

	T_PRICE_4(const double &val)
	{
		if ( val >= 0 )
			m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入	
		else
			m_val = (val - 0.00005) * 10000;//+0.0005表示4舍5入		
	}

	T_PRICE_4& operator = (const double val)
	{
		if ( val >= 0 )
			m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入	
		else
			m_val = (val - 0.00005) * 10000;//+0.0005表示4舍5入			

		return *this;
	}
	
	T_PRICE_4& operator = (const long long int val)
	{
		m_val = val;	
		return *this;
	}

	T_PRICE_4& operator = (const long val)
	{
		return operator=((const long long int)val);
	}

	T_PRICE_4& operator = (const int val)
	{
		return operator=((const long long int)val);
	}

	T_PRICE_4 operator - (const T_PRICE_4& obj)
	{
		T_PRICE_4 ret(0.0);
		ret.m_val = m_val - obj.m_val;
		return ret;
	}
	
	T_PRICE_4& operator + (const T_PRICE_4& obj)
	{
		m_val = m_val + obj.m_val;
		return *this;
	}
	
	T_PRICE_4& operator +=(const T_PRICE_4& obj)
	{
		m_val = m_val + obj.m_val;
		return *this;
	}
	
	double get_double()	 const
	{
		return (double)(m_val) * 1.0 / 10000.0;
	}

	long long int get_long() const
	{
		return m_val;
	}

	bool operator ==(const T_PRICE_4& obj)
	{
		return m_val == obj.m_val ;
	}
};
#endif

#pragma  pack(push, 1)

/////////////////////////////////////////////////////////////////////////
///EESQuoteDateType是一个日期类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteDateType[9];
/////////////////////////////////////////////////////////////////////////
///EESQuoteInstrumentIDType是一个合约代码类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteInstrumentIDType[31];
/////////////////////////////////////////////////////////////////////////
///EESQuoteExchangeIDType是一个交易所代码类型
/// 取值范围
/// 上交所 SHH
/// 深交所 SHZ
/// 上期所 SHFE
/// 中金所 CFFEX
/// 大商所 DCE
/// 郑商所 CZCE
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteExchangeIDType[9];
/////////////////////////////////////////////////////////////////////////
///EESQuotePriceType是一个价格类型
/////////////////////////////////////////////////////////////////////////
typedef T_PRICE32_4	 EESQuotePriceType;
/////////////////////////////////////////////////////////////////////////
///EESQuoteLargeVolumeType是一个大额数量类型
/////////////////////////////////////////////////////////////////////////
typedef long long int EESQuoteLargeVolumeType;
/////////////////////////////////////////////////////////////////////////
///EESQuoteVolumeType是一个数量类型
/////////////////////////////////////////////////////////////////////////
typedef  int EESQuoteVolumeType;
/////////////////////////////////////////////////////////////////////////
///EESQuoteMoneyType是一个资金类型
/////////////////////////////////////////////////////////////////////////
typedef T_PRICE_4 EESQuoteMoneyType;
/////////////////////////////////////////////////////////////////////////
///EESQuoteRatioType是一个比率类型
/////////////////////////////////////////////////////////////////////////
typedef T_PRICE32_4 EESQuoteRatioType;
/////////////////////////////////////////////////////////////////////////
///EESQuoteExchangeInstIDType是一个合约在交易所的代码类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteExchangeInstIDType[31];
/////////////////////////////////////////////////////////////////////////
///EESQuoteMillisecType是一个时间（毫秒）类型
/////////////////////////////////////////////////////////////////////////
typedef int EESQuoteMillisecType;
/////////////////////////////////////////////////////////////////////////
///TStockTimeType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteTimeType[9];
/////////////////////////////////////////////////////////////////////////
///EESQuoteSourceType是一个行情源类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteSourceType; // 上海期权0x01 -- 上海证券0x02 -- 深圳期权0x04 -- 深圳证券0x08


///EESQuoteDeltaType是一个虚实值类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteDeltaType ;
/// \brief 实值
#define EES_DeltaType_IN_OF_MONEY     1
/// \brief 平值
#define EES_DeltaType_AT_OF_MONEY     0
/// \brief 虚值
#define EES_DeltaType_OUT_OF_MONEY    -1

/////////////////////////////////////////////////////////////////////////
///EESQuoteTradingPhaseType是一个实时阶段及标志类型
/////////////////////////////////////////////////////////////////////////
typedef char EESQuoteTradingPhaseType[8]; 



/// \brief EES行情服务器配置信息
struct EqsTcpInfo
{
  EqsTcpInfo()
  {
	  memset(this, 0, sizeof(*this));
  }

  char				m_eqsId[EES_EQS_ID_LEN + 1]; ///< eqcID
  char				m_eqsIp[EES_EQS_ID_LEN + 1]; ///< TCP服务器IP地址
  unsigned short	m_eqsPort;                   ///< TCP服务器端口号 
  char				m_quote_source_type;		 ///< 行情源类型
};

/// \brief EES行情服务器登陆信息
struct EqsLoginParam
{
  EqsLoginParam()
  {
	  memset(this, 0, sizeof(*this));
  }
  char  m_loginId[EES_EQS_USER_ID_LEN + 1];   ///< 登录名
  char  m_password[EES_EQS_PASSWORD_LEN + 1]; ///< 登录密码
};

/// \brief EES行情结构
struct EESMarketDepthQuoteData
{
  EESQuoteDateType            TradingDay;     ///<交易日
  EESQuoteInstrumentIDType    InstrumentID;   ///<合约代码
  EESQuoteExchangeIDType      ExchangeID;     ///<交易所代码
  EESQuoteExchangeInstIDType  ExchangeInstID; ///<合约在交易所的代码
  EESQuotePriceType           LastPrice;      ///<最新价
  EESQuotePriceType           PreSettlementPrice; ///<上次结算价
  EESQuotePriceType           PreClosePrice;    ///<昨收盘
  EESQuoteLargeVolumeType     PreOpenInterest; ///<昨持仓量..
  EESQuotePriceType           OpenPrice;       ///<今开盘
  EESQuotePriceType           HighestPrice;    ///<最高价
  EESQuotePriceType           LowestPrice;     ///<最低价
  EESQuoteLargeVolumeType     Volume;          ///<数量..
  EESQuoteMoneyType           Turnover;        ///<成交金额
  EESQuoteLargeVolumeType     OpenInterest;    ///<持仓量..
  EESQuotePriceType           ClosePrice;      ///<今收盘
  EESQuotePriceType           SettlementPrice; ///<本次结算价
  EESQuotePriceType           UpperLimitPrice; ///<涨停板价
  EESQuotePriceType           LowerLimitPrice; ///<跌停板价
  EESQuoteRatioType           PreDelta;        ///<昨虚实度
  EESQuoteRatioType           CurrDelta;       ///<今虚实度
  EESQuoteTimeType            UpdateTime;      ///<最后修改时间
  EESQuoteMillisecType        UpdateMillisec;  ///<最后修改毫秒
  EESQuotePriceType           BidPrice1;       ///<申买价一
  EESQuoteVolumeType          BidVolume1;      ///<申买量一
  EESQuotePriceType           AskPrice1;       ///<申卖价一
  EESQuoteVolumeType          AskVolume1;      ///<申卖量一
  EESQuotePriceType           BidPrice2;       ///<申买价二
  EESQuoteVolumeType          BidVolume2;      ///<申买量二
  EESQuotePriceType           AskPrice2;       ///<申卖价二
  EESQuoteVolumeType          AskVolume2;      ///<申卖量二
  EESQuotePriceType           BidPrice3;       ///<申买价三
  EESQuoteVolumeType          BidVolume3;      ///<申买量三
  EESQuotePriceType           AskPrice3;       ///<申卖价三
  EESQuoteVolumeType          AskVolume3;      ///<申卖量三
  EESQuotePriceType           BidPrice4;       ///<申买价四
  EESQuoteVolumeType          BidVolume4;      ///<申买量四
  EESQuotePriceType           AskPrice4;       ///<申卖价四
  EESQuoteVolumeType          AskVolume4;      ///<申卖量四
  EESQuotePriceType           BidPrice5;       ///<申买价五
  EESQuoteVolumeType          BidVolume5;      ///<申买量五
  EESQuotePriceType           AskPrice5;       ///<申卖价五
  EESQuoteVolumeType          AskVolume5;      ///<申卖量五
  EESQuotePriceType           AveragePrice;    ///<当日均价
  EESQuoteDeltaType			  MoneyInOrOut;	   ///<虚实值
  EESQuoteTradingPhaseType	  TradingPhaseCode; ///<实时阶段及标志
};

/// \brief EES行情价格数据(用于行情服务于其他服务交互使用)
/// \note 新增昨收价, 昨结算价
struct EESMarketQuoteData
{
	EESQuotePriceType						BidPrice1;						///<申买价一
	EESQuotePriceType						AskPrice1;						///<申卖价一
	EESQuotePriceType						LastPrice;						///<最新价
	EESQuotePriceType						OpenPrice;						///<今开盘
	EESQuotePriceType						LowestPrice;					///<最低价
	EESQuotePriceType						HighestPrice;					///<最高价
	EESQuotePriceType						PreClosePrice;					///<昨收盘
	EESQuotePriceType						PreSettlementPrice;				///<上次结算价
	EESQuoteDeltaType						MoneyInOrOut;					///<虚实值
	EESQuoteExchangeIDType					ExchangeID;						///<交易所代码
	EESQuoteInstrumentIDType				InstrumentID;					///<合约代码
};

#pragma  pack(pop)