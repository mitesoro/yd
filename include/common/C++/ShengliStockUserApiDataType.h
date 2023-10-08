/*!
* \file  ShengliStockUserApiDataType.h
* \brief 交易和查询客户端公共的头文件
*
* 此文件描述了使用交易和查询客户端的公共类型的定义
*
* \author  SHENGLI
* \version 1.0
* \date    2014-04-18
*/
#pragma once

#ifndef SHENGLI_STOCK_DATATYPE_H
#define SHENGLI_STOCK_DATATYPE_H

#define SL_REM_SEC_API_VERSION		("1.0.0.1")

#ifndef PRICE_TYPE
#define PRICE_TYPE
///本结构体用于方便处理用Int64表示的，精确到最多4位小数的浮点类型，大多用于价格字段
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

	operator double ()
	{
		return  (double)(m_val) * 1.0 / 10000.0; ;
	}

};

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
 		if (val >= 0)
			m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入
		else
			m_val = (val - 0.00005) * 10000;			
	}

	T_PRICE_4& operator = (const double val)
	{
		if (val >= 0)
			m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入		
		else
			m_val = (val - 0.00005) * 10000;
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

	operator double ()
	{
		return  (double)(m_val) * 1.0 / 10000.0; ;
	}
};

struct T_RATE_8
{
protected:
	long long int m_val;

public:
	T_RATE_8()
	{
		m_val = 0;
	}

	T_RATE_8& operator = (double val)
	{
		if (val >= 0)
			m_val = (val + 0.000000005) * 100000000.0 ;//+0.000000005表示4舍5入		
		else
			m_val = (val - 0.000000005) * 100000000.0 ;//+0.000000005表示4舍5入		
		return *this ;
	}

	double get_double() const 
	{		
		return (double)(m_val) * 1.0 / 100000000.0 ;
	}

	long long int get_long() const 
	{
		return m_val;
	}

	operator double ()
	{
		return (double)(m_val) * 1.0 / 100000000.0 ;
	}

};
#endif

typedef T_PRICE_4 t_sl_decimal_4; // 总共18位，小数占4位
typedef T_RATE_8 t_sl_rate_8; // 比例, 小数占8位
/////////////////////////////////////////////////////////////////////////
///TShengliStockUserIDType是一个用户ID类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int			TShengliStockOrigUserIdType;



/////////////////////////////////////////////////////////////////////////
///TShengliStockErrNoType是一个错误值 类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockErrNoType;									


/////////////////////////////////////////////////////////////////////////
///TShengliStockProtoVersionType是一个协议版本号类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int			TShengliStockProtoVersionType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockUserIDType是一个帐户ID类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int			TShengliStockUserIDType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockTradingDateType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef int				TShengliStockTradingDateType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockUpdateVersionType是一个期权信息更新版本类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockUpdateVersionType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockClientIdType是一个客户号ID类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockClientIdType[17];

/////////////////////////////////////////////////////////////////////////
///TShengli8ByteReserved 是一个8字节保留字段
/////////////////////////////////////////////////////////////////////////
typedef unsigned char	TShengli8ByteReserved;

/////////////////////////////////////////////////////////////////////////
///TShengliStockClientNameType是一个客户名称类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockClientNameType[64];


/////////////////////////////////////////////////////////////////////////
///TShengliStockBranchIdType是一个客户名称类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockBranchIdType[9];


/////////////////////////////////////////////////////////////////////////
///TShengliStockClientIrderTokenType是一个下单时客户端编号类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int	TShengliStockClientOrderTokenType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockForceCoverFlag是一个强平标记和原因类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char	TShengliStockForceCoverFlag;

/////////////////////////////////////////////////////////////////////////
///TShengliStockAccountType是一个交易帐户类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockAccountType[17];

/////////////////////////////////////////////////////////////////////////
///TShengliStockTradeAccountType是一个交易帐户类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockTradeAccountType[24];


/////////////////////////////////////////////////////////////////////////
///TShengliStockAccountNameType是一个交易帐户名称类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockAccountNameType[64];

/// IP信息
typedef char			TShengliStockIP[40];

/// 端口
typedef unsigned short	TShegliStockPort;

/// 采集的机器信息
typedef char			TShengliStockLocalSystemInfoType[352];

/// 登录时间要求 
typedef char			TShengliStockLoginTimeType[24];

/// 看穿式登录异常信息
typedef char			TShengliStockExceptionFlagType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockAccountDelegate是一个资金账户的适当性权限类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockAccountDelegate[1024];

/////////////////////////////////////////////////////////////////////////
///TShengliStockAccountFinanchingExerciseType 账户是否支持融资行权
/////////////////////////////////////////////////////////////////////////
typedef int			TShengliStockAccountFinanchingExerciseType;
///不支持融资行权
#define SHENGLI_STOCK_AFE_NO		0
///支持融资行权
#define SHENGLI_STOCK_AFE_YES		1


/////////////////////////////////////////////////////////////////////////
///TShengliStockLogonIDType是一个登录名ID类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockLogonIDType[33];

/////////////////////////////////////////////////////////////////////////
///TShengliStockLogonPwdType是一个登录名密码类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockLogonPwdType[33];

/////////////////////////////////////////////////////////////////////////
///TShengliStockClientMacType是一个客户端Mac类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockClientMacType[18];

/////////////////////////////////////////////////////////////////////////
///TShengliStockClientProdInfoType是一个客户端名称类型
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockClientProdInfoType[32];


/////////////////////////////////////////////////////////////////////////
///TShengliStockAppIDType 看穿式监管的APPid 
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockAppIDType[33];

/////////////////////////////////////////////////////////////////////////
///TShengliStockAuthCodeType 看穿式监管的验证码
/////////////////////////////////////////////////////////////////////////
typedef char			TShengliStockAuthCodeType[65];

/////////////////////////////////////////////////////////////////////////
///TShengliStockLogonTypeInfoType是一个登录时的登录模式
/////////////////////////////////////////////////////////////////////////

typedef unsigned char	TShengliStockLogonTypeInfoType;
///用户登录
#define SHENGLI_STOCK_USER_LOGON					0
///资金账户登录
#define SHENGLI_STOCK_FUND_ACC_LOGON				1
/// 客户号登录 
#define SHENGLI_STOCK_CUST_LOGON					2

/////////////////////////////////////////////////////////////////////////
///TShengliStockTimeStampType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long	TShengliStockTimeStampType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockLogonResultType是一个登录返回值类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockLogonResultType;
/////////////////////////////////////////////////////////////////////////
///TShengliStockToBypassByte
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockToBypassByte;

/////////////////////////////////////////////////////////////////////////
///TShengliStockToBypassUShort
/////////////////////////////////////////////////////////////////////////
typedef unsigned short TShengliStockToBypassUShort;

/////////////////////////////////////////////////////////////////////////
///TShengliStockToBypassUInt
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockToBypassByteUInt;

/////////////////////////////////////////////////////////////////////////
/// TShengliStockDelegateType 是委托方式
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockDelegateType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockClientTypeType是用来区分客户端的类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockClientTypeType;

/// api
#define SHENGLI_STOCK_CLIENT_TYPE_API           0
/// RemTrade
#define SHENGLI_STOCK_CLIENT_TYPE_REMTRADE      1


/////////////////////////////////////////////////////////////////////////
///TShengliStockRemResultCode是检测中继模式密码校验的RemCode检测结果
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockRemResultCode;

/////////////////////////////////////////////////////////////////////////
///TShengliStockResultCode是中继模式密码校验中的返回结果
/////////////////////////////////////////////////////////////////////////
typedef short TShengliStockResultCode;

///登录成功
#define SHENGLI_STOCK_LOGON_SUCCESS					0
///用户名或密码错误
#define SHENGLI_STOCK_LOGON_ERR_UerNameOrPwd		1
///用户存在配置问题
#define SHENGLI_STOCK_LOGON_ERR_Config				2
///已登录
#define SHENGLI_STOCK_LOGON_ERR_DupLogon			3
///在已登录的连接,又发送用户的登录请求
#define SHENGLI_INVALID_RELOGON						4
/// 登录验证失败
#define  SHENGLI_STOCK_LOGON_ERR_AUTH_FAILED		9
/// 登录状态错误
#define  SHENGLI_STOCK_LOGON_ERR_STATUS				10
/// 登录用户缺少该服务的登录权限
#define  SHENGLI_STOCK_LESS_PERMISSION				12
/// 登录用户已登陆过，缺少重复登录权限
#define  SHENGLI_STOCK_LESS_RELOGON_PERMISSION		13
/// 登录用户是新加的，目前系统不支持动态增加用户
#define  SHENGLI_USER_IS_NEW_ONE					14
/// 登录缺少权限（包括用户的查询权限及用户的重复登录权限）
#define  SHENGLI_STOCK_LESS_PERMISSION				12	
///登录用户已登陆过，缺少重复登录权限
#define SHENGLI_STOCK_LESS_RELOGON_PERMISSION       13
///登录用户是新加的，目前系统不支持动态增加用户
#define SHENGLI_USER_IS_NEW_ONE                     14
///用户登录超时
#define LOGON_LR_USER_LOGON_TIMEOU                  15
///委托方式不支持
#define LOGON_LR_USER_OPERWAY_ERROR                 16
///不支持资金账户登录
#define LOGON_LR_NOT_SUPPORT_FUCC_LOGON             17
///无可用连接 资金账户登录满了
#define LOGON_LR_HAVE_NO_USED_CONNECT               18
///不支持用户登录
#define LOGON_LR_NOT_SUPPORT_USER_LOGON             19
///无绑定的资金账户
#define LOGON_LR_HAVE_NO_RELATION_FUCC              20
///用户下无该资金账户 （中继服务，资金账户密码校验）
#define LOGON_LR_ZJ_HAVE_NO_RELATION_FUCC           21
///用户类型错误（OT和QRY不允许操作员登录）
#define LOGON_LR_USER_TYPE                          22
///服务不支持主柜密码校验
#define LOGON_LR_NOT_SUPPORT_CENTER_CHECK           23
///与集中柜台连接异常
#define LOGON_LR_CENTER_CONNECT_ERROR               24
///资金账户登录主柜错误
#define LR_USER_IS_FROZEN                           25
///资金账户被注销
#define LR_USER_IS_LOGOUT                           26
///用户下客户资金账户及股东账户信息不完整
#define LR_USER_INCOMPLETE                          27
///不需要进行集中柜台密码校验
#define LR_NOT_NEED_CHECK                           28
///客户未绑定到具体的资金账户
#define LR_CLIENTID_NOT_BIND_FUNDACC_CHECK          29
///资金账户登录主柜错误
#define LR_CENTER_LOGON_ERROR                       30
///系统资源不足,不允许新用户连接上来
#define LOGON_LR_SYSTEM_CRITICAL                    99

/////////////////////////////////////////////////////////////////////////
///TShengliStockChangePasswordResultType是一个修改登录密码返回值类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockChangePasswordResultType;
///成功
#define SHENGLI_STOCK_ChangePasswordResult_Success			0	
///老密码不对
#define SHENGLI_STOCK_ChangePasswordResult_OldPwdNotMatch	1	
///新密码非法
#define SHENGLI_STOCK_ChangePasswordResult_NewPwdInvalid		2	
///尚未登录
#define	SHENGLI_STOCK_ChangePasswordResult_NotLogIn			3		
///系统后台其他问题
#define	SHENGLI_STOCK_ChangePasswordResult_InternalError		99		


/////////////////////////////////////////////////////////////////////////
///TShengliStockAccountTypeType是一个账户类型类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockAccountTypeType;
///普通账户
#define SHENGLI_STOCK_AccountType_Normal 0
///融资融券账户
#define SHENGLI_STOCK_AccountType_Credit 1
///衍生品账户(期权用)
#define SHENGLI_STOCK_AccountType_Option 2


/////////////////////////////////////////////////////////////////////////
///TShengliStockPrevilegeType是一个客户号操作权限类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long int TShengliStockPrevilegeType;
///所有权限
#define SHENGLI_STOCK_Previlege_OpenAndClose            99		
///只读
#define SHENGLI_STOCK_Previlege_ReadOnly                 1	
///只能平仓
#define SHENGLI_STOCK_Previlege_CloseOnly                2		


/////////////////////////////////////////////////////////////////////////
///TShengliStockTradeType是一个交易分类类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char    TShengliStockTradeTypeType;	

/////////////////////////////////////////////////////////////////////////
///TShengliStockPosDirection是一个仓位方向类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char    TShengliStockPosDirectionType;
///多头仓位
#define SHENGLI_STOCK_Position_Long  1
///空头仓位
#define SHENGLI_STOCK_Position_Short 5
///备兑仓位
#define SHENGLI_STOCK_Position_Covered 9

/////////////////////////////////////////////////////////////////////////
///TShengliStockPosQtyType是一个仓位数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int   TShengliStockPosQtyType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockTotalLongPositionQtyType是一个仓位数量类型
/////////////////////////////////////////////////////////////////////////
typedef long   TShengliStockTotalLongPositionQtyType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockFeeIdxType是一个费率组合类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char    TShengliStockFeeIdxType;
///手续费
#define SHENGLI_STOCK_Fee_Commision 0
///印花税
#define SHENGLI_STOCK_Fee_Stamp	   1
///过户费
#define SHENGLI_STOCK_Fee_Transfer  2

/////////////////////////////////////////////////////////////////////////
///TShengliStockFeeRateType是一个按比例收取的费率类型
/////////////////////////////////////////////////////////////////////////
typedef long long int TShengliStockFeeRateType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockExchangeAccountType是一个交易所类型
/////////////////////////////////////////////////////////////////////////
typedef char   TShengliStockExchangeAccountType[16];

/// id类型 
typedef unsigned long long	TShengliStockId;

/// 字符串日期类型 
typedef char	TShengliStockDate[16];

/// 字符串时间类型 
typedef char	TShengliStockDatetime[32];

/////////////////////////////////////////////////////////////////////////
///TShengliStockCoverFlagType是一个期权仓位专用备兑标志类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char   TShengliStockCoverFlagType;
///普通
#define SHENGLI_STOCK_Opt_Position_Normal 0
///备兑仓
#define SHENGLI_STOCK_Opt_Position_Bd     1


/////////////////////////////////////////////////////////////////////////
///TShengliStockSymbolType是一个交易合约编码类型  全部数据用 数字0 补齐
/////////////////////////////////////////////////////////////////////////
// "CNSJC"	"认购牛市价差策略"
// "CXSJC"	"认购熊市价差策略"
// "KKS"	"宽跨式空头"
// "KS"	"跨式空头"
// "PNSJC"	"认沽牛市价差策略"
// "PXSJC"	"认沽熊市价差策略" 
typedef char    TShengliStockSymbolType[9];			

/////////////////////////////////////////////////////////////////////////
///TShengliStockSymbolType是一个交易合约编码类型
/////////////////////////////////////////////////////////////////////////
typedef char    TShengliStockSecondaryOrderType[20];

/////////////////////////////////////////////////////////////////////////
///TShengliStockRequestIDType是一个REQ ID类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int  TShengliStockRequestIDType;		

/////////////////////////////////////////////////////////////////////////
///TShengliStockFrzFlagType是一个Frz Flag类型
/////////////////////////////////////////////////////////////////////////
typedef char  TShengliStockFrzFlagType;	
#define		StockFrzFlag_lock		'0'		///< 冻结
#define		StockFrzFlag_unlock		'1'		///< 解冻

/////////////////////////////////////////////////////////////////////////
///TShengliStockSyncRspMsgType是一个SYNC返回消息的类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char  TShengliStockSyncRspMsgType;	
#define		RspMsgType_Sync		0		///< SYNC定义
#define		RspMsgType_Ctp		1		///< CTP定义


/////////////////////////////////////////////////////////////////////////
///TShengliBpInOutFlagType是一个出入金类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char  TShengliBpInOutFlagType;
#define		BpInOutFlag_in		0		///< 划入
#define		BpInOutFlag_out		1		///< 划出

/////////////////////////////////////////////////////////////////////////
///TShengliBpInOutSourceType是一个出入金的源
/////////////////////////////////////////////////////////////////////////
typedef unsigned char  TShengliBpInOutSourceType;
#define		BpInoutSource_unknow			0	// 未知
#define		BpInoutSource_lmc				1	// 人工出入金
#define		BpInoutSource_node				2	// 节点之间划转
#define		BpInoutSource_master_counter	3	// 与主席实时划拔
#define		BpInoutSource_platform			4	// 资金划拨平台
#define 	BpInoutSource_outside_module    5 	// 外部管理模块出入金
#define		BpInoutSource_bank_drive		6	// 银衍划拨


/////////////////////////////////////////////////////////////////////////
///TShengliPosInOutFlagType 是一个出入仓类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char  TShengliPosInOutFlagType;
#define		PosInOutFlag_in		0		///< 划入
#define		PosInOutFlag_out	1		///< 划出

/////////////////////////////////////////////////////////////////////////
///TShengliPosInoutSourceType 是一个出入仓的源
/////////////////////////////////////////////////////////////////////////
typedef unsigned char  TShengliPosInOutSourceType;
#define		PosInoutSource_unknow						0	// 未知
#define		PosInoutSource_lmc							1	// 人工
#define		PosInoutSource_master_counter				3	// 与主席实时划拔
#define     PosInOutSource_auto							4   // 自动出入
#define 	PosInOutSource_auto_unfrz_master_counter    5   // 自动解冻主席的仓位

/////////////////////////////////////////////////////////////////////////
///TShengliOperatorCheckFlagType 是一个操作复核标记类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char  TShengliOperatorCheckFlagType;
#define		OperatorCheck_untreated						0	// 未处理
#define		OperatorCheck_risk_check_accept				1	// 风险度校验通过
#define		OperatorCheck_risk_check_reject				2	// 风险度校验拒绝
#define		OperatorCheck_operator_success				3	// 操作成功
#define		OperatorCheck_operator_failed				4	// 操作失败

/////////////////////////////////////////////////////////////////////////
///TShengliStockAmountType是一个Amount类型
/////////////////////////////////////////////////////////////////////////
typedef t_sl_decimal_4  TShengliStockAmountType;	

/////////////////////////////////////////////////////////////////////////
///TShengliStockTextType是一个TEXT类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockTextType[256];	

/////////////////////////////////////////////////////////////////////////
///TShengliStockSymbolNameType是一个交易合约名称类型
/////////////////////////////////////////////////////////////////////////
typedef char    TShengliStockSymbolNameType[88];	



/////////////////////////////////////////////////////////////////////////
///TShengliTradeNodeType是一个交易节点类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliTradeNodeType[256];


/////////////////////////////////////////////////////////////////////////
///TShengliStockCoverTodayFlagType是一个是否可以平今类型
/////////////////////////////////////////////////////////////////////////
typedef int	     TShengliStockCoverTodayFlagType;	
///不能平今
#define SHENGLI_STOCK_CANNOT_COVER_TODAY                     0	
///可以平今
#define SHENGLI_STOCK_CAN_COVER_TODAY                        1	



/////////////////////////////////////////////////////////////////////////
///TShengliStockCurrencyType是一个货币类型
/////////////////////////////////////////////////////////////////////////
typedef char    TShengliStockCurrencyType[4];

/////////////////////////////////////////////////////////////////////////
///TShengliStockParValueType是一个面值类型
/////////////////////////////////////////////////////////////////////////
typedef double    TShengliStockParValueType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockIsFinancingType是一个可融资类型
/////////////////////////////////////////////////////////////////////////
typedef char    TShengliStockIsFinancingType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockIsLendingType是一个可融券类型
/////////////////////////////////////////////////////////////////////////
typedef char    TShengliStockIsLendingType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockSecurityTypeType是一个交易品种类型类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSecurityTypeType;	
///所有品种类型
#define SHENGLI_STOCK_SecType_All							0	
///股票
#define SHENGLI_STOCK_SecType_CS							1	
///ETF
#define SHENGLI_STOCK_SecType_ETF							2	
/// 债券
#define SHENGLI_STOCK_SecType_BONDS							3
/// 逆回购 
#define SHENGLI_STOCK_SecType_REPO							4	
///期权
#define SHENGLI_STOCK_SecType_OPTION						9	
	

/////////////////////////////////////////////////////////////////////////
///TShengliStockSecuritySubTypeType是一个交易品种类型类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSecuritySubTypeType;	


/// 股票子类型 
#define	 SHENGLI_STOCK_CS_SECU_SUB_TYPE_A_STOCK			0	///< A股
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_ZXB				1	///< 中小板
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_CYB				2	///< 创业板
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_B_STOCK			3	///< B股
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_H_STOCK			4	///< H股
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_US				5	///< 美股
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_US_ADR			6	///< 美股ADR
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_EXT				7	///< 扩展版
#define  SHENGLI_STOCK_CS_SECU_SUB_TYPE_OPS				8	///<  优先股


/// 债券子类型
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_GVN		0	///<政府债券
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_ENT		1	///<企业债券
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_DFZ		2	///<地方债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_CVT		3	///<可转换债券
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_CPF		4	///< 公司债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_FBF		5	///< 金融债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_CBD		6	///< 可分离，可转债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_CCF		7	///< 可交换公司债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_CPD		8	///< 可交换私幕债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_PD		9	///< 私募债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_CSD		10	///< 次级债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_AD		11	///< 资产支持证券
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_BSD		12	///< 证券公司短期债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_OBD		13	///< 可交换私幕债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_DST		14	///< 可交换私幕债
#define	 SHENGLI_STOCK_BOND_SECU_SUB_TYPE_DVP		15	///< 地方分销

/// 基金子类型

#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_NORMAL		0   ///<一般
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_CEF			1   ///<封闭式基金
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_LOF			2   ///<LOF基金
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_ETF			3   ///<ETF基金
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_FJ			4	///< 分级 基金
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_KFS			5	///< 开放式基金（仅申赎）
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_SSSGHB		6	///< 实时申赎货币基金
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_DSC			7	///< 单市股票ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_KSC			8	///< 跨市股票ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_KJ			9	///< 跨境ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_SWZQ		10	///< 实物债券ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_XJZQ		11	///< 现金债券ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_HB			12	///< 货币ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_HJ			13	///< 黄金ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_SPQH		14	///< 商品期货ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_GG			15	///< 杠杆ETF
#define	 SHENGLI_STOCK_MF_SECU_SUB_TYPE_CROSS_LOF	16	///<跨境LOF

/// 回购子类型
#define	 SHENGLI_STOCK_REPO_SECU_SUB_TYPE_CRP		0	///<质押式国债回购
#define	 SHENGLI_STOCK_REPO_SECU_SUB_TYPE_BRP		1	///<质押式企业回购	
#define	 SHENGLI_STOCK_REPO_SECU_SUB_TYPE_ORP		2	///<买断式国债回购	

/// 期权子类型 
#define	 SHENGLI_STOCK_OPTION_SECU_SUB_TYPE_ETF		0	///< ETF期权 
#define	 SHENGLI_STOCK_OPTION_SECU_SUB_TYPE_ABS		1	///< 股票期权


/////////////////////////////////////////////////////////////////////////
///TShengliStockSubstCashFlagType是一个现金替代标志类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSubstCashFlagType;
///不能替代
#define SHENGLI_STOCK_SubstCashFlag_NoSub	0
///可以替代
#define SHENGLI_STOCK_SubstCashFlag_CanSub	1
///现金替代
#define SHENGLI_STOCK_SubstCashFlag_CashSub	2
///退补
#define SHENGLI_STOCK_SubstCashFlag_BackSub	3


/////////////////////////////////////////////////////////////////////////
///TShengliStockOptionType是一个期权类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockOptionType;

///欧式期权
#define SHENGLI_STOCK_EuropeanOption	'E'
///美式期权
#define SHENGLI_STOCK_AmericanOption	'A'



/////////////////////////////////////////////////////////////////////////
///TShengliStockVolMultiplerType是一个合约单位类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockVolMultiplerType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockSubstCashRate是一个替换现金比例类型
/////////////////////////////////////////////////////////////////////////
typedef double TShengliStockSubstCashRateType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockContractAccountCodeType是一个期权合约账户代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockContractAccountCodeType[7];

/////////////////////////////////////////////////////////////////////////
///TShengliStockContractIDType是一个期权合约代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockContractIDType[21];


/////////////////////////////////////////////////////////////////////////
///TShengliStockCallOrPutType是一个期权看涨看跌类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockCallOrPutType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockSessionCountType是一个交易所连接个数类型
/////////////////////////////////////////////////////////////////////////
typedef char  TShengliStockSessionCountType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockSessionIDListType是一个交易所连接代号类型
/////////////////////////////////////////////////////////////////////////
typedef char  TShengliStockSessionIDListType[255];


/////////////////////////////////////////////////////////////////////////
///TShengliStockSessionIDType是一交易所连接代号个类型
/////////////////////////////////////////////////////////////////////////
typedef char  TShengliStockSessionIDType;



///////////////////////////////////////////////////////
///TShengliStockMarketOrderIdType是一个交易所订单号类型
/////////////////////////////////////////////////////////////////////////
typedef char    TShengliStockMarketOrderIdType[25];                  


/////////////////////////////////////////////////////////////////////////
///TShengliStockMarketExecIdType是一个交易所成交号类型
/////////////////////////////////////////////////////////////////////////
typedef char	TShengliStockMarketExecIdType[25];


/////////////////////////////////////////////////////////////////////////
///TShengliStockMarketSessionIdType是一个交易所席位代码类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockMarketSessionIdType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockExchSessionSatusType是一个交易所连接状态类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockExchSessionSatusType;
///断开
#define SHENGLI_STOCK_ExchSessionSatus_Disconnected 0
///连接
#define SHENGLI_STOCK_ExchSessionSatus_Connected    1


/////////////////////////////////////////////////////////////////////////
///TShengliStockSideType是一个买卖方向类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSideType;		
///买开仓
#define SHENGLI_STOCK_SideType_OpenLong                  1	
///卖平仓
#define SHENGLI_STOCK_SideType_CloseTodayLong			2	
/// 逆回购
#define	SHENGLI_stock_SideType_SellRepo					3	
///ETF申购
#define SHENGLI_STOCK_SideType_ETFBuy 10
///ETF赎回
#define SHENGLI_STOCK_SideType_ETFSell 11
///融资买入
#define SHENGLI_STOCK_SideType_RZMR   20
///卖券还款
#define SHENGLI_STOCK_SideType_MQHK   21
///现金还款
#define SHENGLI_STOCK_SideType_XJHK   22
///担保品买入
#define SHENGLI_STOCK_SideType_CollateralBuy 23
///担保品卖出
#define SHENGLI_STOCK_SideType_CollateralSell 24
///买券还券
#define SHENGLI_STOCK_SideType_MQHQ 25
///现券还券
#define SHENGLI_STOCK_SideType_XQHQ 26
///融券卖出
#define SHENGLI_STOCK_SideType_RQMC 27
/// 期权备兑开仓
#define SHENGLI_STOCK_SideType_OPT_BDKC 30
/// 期权备兑平仓
#define SHENGLI_STOCK_SideType_OPT_BDPC 31
/// 期权行权
#define SHENGLI_STOCK_SideType_OPT_Exercise 32
/// 期权备兑锁定申报
#define SHENGLI_STOCK_SideType_OPT_BDSDSB 33
/// 期权备兑解锁申报
#define SHENGLI_STOCK_SideType_OPT_BDJSSB 34
/// 期权买开仓
#define SHENGLI_STOCK_SideType_OPT_BUY_OPEN		35
/// 期权卖平仓
#define SHENGLI_STOCK_SideType_OPT_SELL_CLOSE	36
/// 期权卖开仓
#define SHENGLI_STOCK_SideType_OPT_SELL_OPEN	37
/// 期权买平仓
#define SHENGLI_STOCK_SideType_OPT_BUY_CLOSE	38

/// 期权强制卖平仓
#define SHENGLI_STOCK_SideType_OPT_FORCE_SELL_CLOSE			39
/// 期权强制买平仓
#define SHENGLI_STOCK_SideType_OPT_FORCE_BUY_CLOSE			40
/// 期权强制平备兑仓
#define SHENGLI_STOCK_SideType_OPT_FORCE_CLOSE_COVERED_CALL	41
/// 期权合并申报行权
#define  SHENGLI_STOCK_SideType_OPT_COMB_EXERCISE	       43 
/// 期权构建组合策略
#define  SHENGLI_STOCK_SideType_OPT_COMB_POS_CREATE		    44
/// 期权解除组合策略
#define  SHENGLI_STOCK_SideType_OPT_COMB_POS_RELIEVE	    45
///<期权备兑转普通
#define  SHENGLI_STOCK_SideType_OPT_COVERED_TO_NORMAL       46
///<期权普通转备兑
#define  SHENGLI_STOCK_SideType_OPT_NORMAL_TO_COVERED       47
///<期权解除组合策略（券商强制解除）
#define  SHENGLI_STOCK_SideType_OPT_FORCE_COMB_POS_RELIEVE  48
///<做市报价单
#define  SHENGLI_STOCK_SideType_MARKET_ORDER				49
///<单边平仓(只支持深圳)
#define SHENGLI_STOCK_SideType_OPT_ONE_SIDE_CLOSE 			50 
///<强制单边平仓(只支持深圳)
#define SHENGLI_STOCK_SideType_OPT_FORCE_ONE_SIDE_CLOSE 	51 


/////////////////////////////////////////////////////////////////////////
///TShengliStockPriceTypeType是一个价格类型类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockPriceTypeType;
///市价单
#define SHENGLI_STOCK_PriceType_Market 1
///限价单
#define SHENGLI_STOCK_PriceType_Limit  2
///本方最优
#define SHENGLI_STOCK_PriceType_Local  3


/////////////////////////////////////////////////////////////////////////
///TShengliStockMaxPriceLevelsType是一个价格等级类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned short TShengliStockMaxPriceLevelsType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockTIFType是一个单子存活时间类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockTIFType;
///DayOrder
#define SHENGLI_STOCK_TIF_DayOrder 0
///IOC(不成交马上取消)
#define SHENGLI_STOCK_TIF_IOC      1


/////////////////////////////////////////////////////////////////////////
///TShengliStockCashMarginFlagType是一个交易类型类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockCashMarginFlagType;
///普通交易
#define  SHENGLI_STOCK_CashMarginFlag_Cash 1
///融资融券开仓
#define  SHENGLI_STOCK_CashMarginFlag_Open 2
///融资融券平仓
#define  SHENGLI_STOCK_CashMarginFlag_Close 3


/////////////////////////////////////////////////////////////////////////
///TShengliStockSessoinSelModeType是一个会话模式类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSessoinSelModeType;
///客户指派sessionid
#define  SHENGLI_STOCK_SessoinSelMode_Custom 1
///默认rem内部轮询
#define  SHENGLI_STOCK_SessoinSelMode_Internal 0


/////////////////////////////////////////////////////////////////////////
///TShengliStockUserInfoType是一个供客户使用的类型
/////////////////////////////////////////////////////////////////////////
// typedef char TShengliStockUserInfoType[8];
typedef char TShengliStockUserInfoType[4];

/////////////////////////////////////////////////////////////////////////
///TShengliStockUserInfo1Type是一个供客户使用的类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockUserInfo1Type;

/////////////////////////////////////////////////////////////////////////
///TShengliStockRecordID是一个
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockRecordID;

/////////////////////////////////////////////////////////////////////////
///TShengliStockUserInfoType1是一个供客户使用的类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockUserInfoType1;


/////////////////////////////////////////////////////////////////////////
///TShengliStockExchangeIDType是一个交易所ID类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockExchangeIDType;					
///上交所
#define SHENGLI_STOCK_ExchangeID_SH_CS                    100
///深交所
#define SHENGLI_STOCK_ExchangeID_SZ_CS                    101


/////////////////////////////////////////////////////////////////////////
///TShengliBindingTradeAcctType是一个是否绑定到交易节点的类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliBindingTradeAcctType;
///上交所
#define SHENGLI_BindingTradeAcct                    1
///深交所
#define SHENGLI_NotBindingTradeAcct                   0

/////////////////////////////////////////////////////////////////////////
///TShengliStockQtyType是一个数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockQtyType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockResultType是一个返回结果类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockResultType;
// 0: 没有错误
#define SHENGLI_STOCK_NO_ERR 0
// 1: 账户关系不完整
#define SHENGLI_STOCK_FUND_ACCOUNT_STRUCT_ERROR  1
// 2: 账户类型错误
#define SHENGLI_STOCK_FUND_ACCOUNT_TYPE_ERROR 2
// 3: 股票类型错误
#define SHENGLI_STOCK_SYMBOL_TYPE_ERROR 3
// 4: 可用券不够
#define SHENGLI_STOCK_AVAIL_POS_QTY_ERROR 4
// 5: 可用资金不够
#define SHENGLI_STOCK_AVAIL_BP_ERROR 5
// 6: qmcs消息的req id已存在
#define SHENGLI_STOCK_EXIST_SEQ_ID_ERROR 6
// 7: qmsc消息的req id不存在
#define SHENGLI_STOCK_NOT_EXIST_SEQ_ID_ERROR 7
// 8: 获取交易所账户失败
#define SHENGLI_STOCK_NOT_FIND_EXCHANGE_ACCOUNT 8
// 9: 没有找到sync_trade服务, 消息发送失败
#define SHENGLI_STOCK_NOT_FIND_SYNC_TRADE_SERVICE 9
// 10: sync_trade服务处理失败
#define SHENGLI_STOCK_SYNC_TRADE_SERVICE_PROC_FAILED 10
// 11: 触发风控
#define SHENGLI_STOCK_TRIGGER_RISK_CONTROL 11
// 12: 可取金额不足
#define SHENGLI_STOCK_DESIRABLE_BP_ERROR 12
// 13: 获取出出入金条件失败
#define SHENGLI_STOCK_GET_GX_JZ_INOUT_CASH_FILTER_FALED 13
// 14: 金额或者数量需要大于0
#define SHENGLI_STOCK_AVAIL_VALUE_ERROR 14
// 15: 冻结解冻标志位错误
#define SHENGLI_STOCK_FRZ_UNFRZ_FLAG_ERROR 15
// 16: 地址不正确
#define SHENGLI_STOCK_SYNC_SERVICE_ADDRESS_ERROR 16
// 17: 认证错误
#define SHENGLI_STOCK_SYNC_SERVICE_AUTH_ERROR 17
// 18: 登录错误
#define SHENGLI_STOCK_SYNC_SERVICE_LOGON_ERROR 18

/////////////////////////////////////////////////////////////////////////
///TShengliStockQueryResultType是一个查询返回结果类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockQueryResultType;
// 成功
#define SHENGLI_STOCK_QUERY_SUCCESS 0
// 未找到客户号信息
#define SHENGLI_STOCK_QUERY_FAILED_BY_NOT_FOUND_CLIENT_INFO 1
// 未找到资金账号信息
#define SHENGLI_STOCK_QUERY_FAILED_BY_NOT_FOUND_FUND_ACCOUNT_INFO 2
// 未找到合约信息
#define SHENGLI_STOCK_QUERY_FAILED_BY_NOT_FOUND_OPTION_SYMBOL 3
// 合约列表为空
#define SHENGLI_STOCK_QUERY_FAILED_BY_OPTION_SYMBOL_LIST_IS_EMPTY 4
// 交易所信息错误
#define SHENGLI_STOCK_QUERY_FAILED_BY_EXCHANGE_ID_INFO_ERROR 5

/////////////////////////////////////////////////////////////////////////
///TShengliStockOrderPriceType是一个订单价格类型
/////////////////////////////////////////////////////////////////////////
typedef t_sl_decimal_4 TShengliStockOrderPriceType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockMarginPriceType是一个保证金类型
/////////////////////////////////////////////////////////////////////////
typedef double TShengliStockMarginPriceType;



/////////////////////////////////////////////////////////////////////////
///TShengliStockOrderIDType是一个单子号类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long TShengliStockOrderIDType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockExchangeOrderIDType是一个交易所单号类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockExchangeOrderIDType[20];


/////////////////////////////////////////////////////////////////////////
///TShengliStockExchangeAcceptFlagType是一个交易所接受类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockExchangeAcceptFlagType;
///交易所尚未接受
#define SHENGLI_STOCK_ExchangeAcceptFlag_No 0
///交易所已接受
#define SHENGLI_STOCK_ExchangeAcceptFlag_Yes 1

/// 持仓类型
typedef unsigned char	TShengliStockPosDayType;
/// 未知
#define SHENGLI_STOCK_DayType_unknow	0
/// 今仓
#define SHENGLI_STOCK_DayType_Today	1
/// 昨仓
#define SHENGLI_STOCK_DayType_Ovn	2

/////////////////////////////////////////////////////////////////////////
///TShengliStockOrderStatusType是一个订单状态类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockOrderStatusType;
///bit0=1：已关闭, (拒绝/全部成交/已撤销)
#define SHENGLI_STOCK_OrderStatus_Closed					0x01	
///bit4=1：已撤单（bit0必须为1）
#define SHENGLI_STOCK_OrderStatus_Cancelled				0x10
///bit5=1：有过任意数量的成交
#define SHENGLI_STOCK_OrderStatus_Executed				0x20
///bit6=1：交易所接受
#define SHENGLI_STOCK_OrderStatus_MktAccept				0x40	
///bit7=1：交易所拒绝
#define SHENGLI_STOCK_OrderStatus_MktReject				0x80


/////////////////////////////////////////////////////////////////////////
///TShengliStockPassiveOrderFlagType是一个被动单/外部单标志类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockPassiveOrderFlagType;
///普通单
#define  SHENGLI_STOCK_PassiveOrderFlag_Custom 0
///被动单
#define  SHENGLI_STOCK_PassiveOrderFlag_Passive 1
///外部单
#define  SHENGLI_STOCK_PassiveOrderFlag_External 2


/////////////////////////////////////////////////////////////////////////
///TShengliStockRejectByType是一个订单拒绝类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockRejectedByType;
///REM系统拒绝
#define SHENGLI_STOCK_RejectedBy_Rem 0
///交易所拒绝
#define SHENGLI_STOCK_RejectedBy_Exchange 1
///报盘程序拒绝
#define SHENGLI_STOCK_RejectedBy_MI		2	

/////////////////////////////////////////////////////////////////////////
///TShengliStockRejectReasonType是一个拒绝原因类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned short TShengliStockRejectReasonType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockGrammerResultType是一个语法检查结果类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockGrammerResultType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockRiskResultType是一个风控检查结果类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockRiskResultType[16];


/////////////////////////////////////////////////////////////////////////
///TShengliStockReasonTextType是一个错误原因类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockReasonTextType[88];

/////////////////////////////////////////////////////////////////////////
///TShengliStockCxlRejectReasonTextType 撤单拒绝的错误原因类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockCxlRejectReasonTextType[80];


/////////////////////////////////////////////////////////////////////////
///TShengliStockExecIDType是一个64位成交编号类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long TShengliStockExecIDType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockExecIDType是一个32位成交编号类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockExecIDType_32;

/////////////////////////////////////////////////////////////////////////
///TShengliStockExecPassiveFlagType是一个被动成交标志类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockExecPassiveFlagType;
///普通成交
#define SHENGLI_STOCK_ExecPassiveFlag_Normal 0
///被动成交
#define SHENGLI_STOCK_ExecPassiveFlag_Passive 1


/////////////////////////////////////////////////////////////////////////
///TShengliStockExchangeExecIDType是一个交易所成交编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockExchangeExecIDType[20];


/////////////////////////////////////////////////////////////////////////
///TShengliStockOrderCxlPassiveFlagType是一个被动撤单类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockOrderCxlPassiveFlagType;
///正常撤单
#define  SHENGLI_STOCK_OrderCxlPassiveFlag_Normal 0
///REM操作原进行的被动撤单
#define  SHENGLI_STOCK_OrderCxlPassiveFlag_Rem    1

/////////////////////////////////////////////////////////////////////////
///TShengliStockCxlReqStatusType是一个撤单状态类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockCxlReqStatusType;
///撤单请求挂起中
#define  SHENGLI_STOCK_CxlReqStatus_Pending	1
///撤单请求已成功, 订单被撤销
#define  SHENGLI_STOCK_CxlReqStatus_Cxled	2
///撤单请求被交易所拒绝, 订单保持原状态
#define  SHENGLI_STOCK_CxlReqStatus_Rejected	3




/////////////////////////////////////////////////////////////////////////
///TShengliStockBcostType是一个合约买入成本类型
/////////////////////////////////////////////////////////////////////////
typedef double TShengliStockBcostType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockMktVaLType是一个市值类型
/////////////////////////////////////////////////////////////////////////
typedef double TShengliStockMktVaLType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockPremiumType是一个权利金额类型
/////////////////////////////////////////////////////////////////////////
typedef double TShengliStockPremiumType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockOpeningQtyType是一个开仓中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockOpeningQtyType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockCoveringQtyType是一个平仓中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockCoveringQtyType;


/////////////////////////////////////////////////////////////////////////
///TShengliStockQueryTypeType是一个委托成交查询结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockQueryTypeType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockRequestNumType是一个委托查询数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockRequestNumType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockCursorMarkType是一个委托成交查询结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long TShengliStockCursorMarkType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockTotalNumType是一个委托成交查询结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockTotalNumType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockCurIndexType是一个委托成交查询结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockCurIndexType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockEntrustTypeType是一个委托成交查询结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliStockEntrustTypeType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockPositionStrType是一个委托成交查询结构体中字符串类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockPositionStrType[97];

/////////////////////////////////////////////////////////////////////////
///TShengliStockEntrustIDType是一个委托编号类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long TShengliStockEntrustIDType;

/////////////////////////////////////////////////////////////////////////
///TShengliOpStaionCustomerKey是一个OPSTATION上报结构体中字符串类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliOpStaionCustomerKey[64];

/////////////////////////////////////////////////////////////////////////
///TShengliOpStationReportResult是一个OPSTATION上报结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliOpStationReportResult;

/////////////////////////////////////////////////////////////////////////
///TShengliOpStationID是一个OPSTATION上报结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliOpStationID;

/////////////////////////////////////////////////////////////////////////
///TShengliOpStationReportContent是一个OPSTATION上报结构体中字符串类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliOpStationReportContent[256];

/////////////////////////////////////////////////////////////////////////
///TShengliUserID是一个OPSTATION上报结构体中数量类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliUserID;

/////////////////////////////////////////////////////////////////////////
///TShengliTradeNode是股东账号列表查询上报结构体中字符串类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliTradeNode[20];

/////////////////////////////////////////////////////////////////////////
///TShengliPermission是账号和股东账号列表查询上报结构体中权限类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliPermission;


/////////////////////////////////////////////////////////////////////////
///TShengliRiskRuleID 风控ID号
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliRiskRuleID ;
///下面列出的rule 是我们只支持查询的风控ID
///公司对风险度
#define RiskRuleID_Corporate_Hedging_Risk 34
///买入额度
#define	RiskRuleID_BUY_Amount			  35
///公司风险度
#define RiskRuleID_CompanyRisk			  48
///交易所风险度
#define RiskRuleID_ExchangeRisk			  49
///净买入额(目前不支持)
#define	RiskRuleID_NetBuyAmouRnt		  54


/////////////////////////////////////////////////////////////////////////
///TShengliRiskRuleType  风控类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliRiskRuleType;
///全局风控，针对所有账户
#define	RISK_TYPE_GLOBAL				1
///证券类型级风控， SecuType有效
#define	RISK_TYPE_SECU_TYPE				2
///账户级风控，FundAccount 有效
#define	RISK_TYPE_ACCOUNT				3
///账户标的物级风控，FundAccount，ExchangeID, SecuCode(标的物) 有效
#define	RISK_TYPE_ACCOUNT_UNDERLYING	4
///账户合约层风控，FundAccount，ExchangeID, SecuCode(证券代码,合约代码) 有效
#define	RISK_TYPE_ACCOUNT_SECU_CODE		5


/////////////////////////////////////////////////////////////////////////
///TShengliRiskRuleParamCount  风控参数个数
/////////////////////////////////////////////////////////////////////////
typedef unsigned int	TShengliRiskRuleParamCount;

/////////////////////////////////////////////////////////////////////////
///TShengliRiskValue  风控值
/////////////////////////////////////////////////////////////////////////
typedef t_sl_decimal_4	TShengliRiskValue;

/////////////////////////////////////////////////////////////////////////
///TShengliRate  比例
/////////////////////////////////////////////////////////////////////////
typedef t_sl_rate_8 TShengliRate;


/////////////////////////////////////////////////////////////////////////
///TShengliFeeConfigCount  费用配置个数
/////////////////////////////////////////////////////////////////////////
typedef unsigned int	TShengliFeeConfigCount;

#define FEE_CONFIG_MAX_COUNT 8 


/////////////////////////////////////////////////////////////////////////
///TShengliQueryResult 查询结果
/////////////////////////////////////////////////////////////////////////
typedef unsigned char	TShengliQueryResult;
/// 风控查询成功
#define QUERY_RISK_RULE_RESULT_SUCCESS							0
/// 风控查询失败未找到客户号
#define QUERY_RISK_RULE_RESULT_CLIENT_NOT_FOUND					1
/// 风控查询失败未找到资金账户
#define QUEYR_RISK_RULE_RESULT_FUND_ACCT_NOT_FOUND				2
/// 风控查询失败未找到对应的风控ID
#define QUERY_RISK_RULE_RESULT_RISK_RULE_ID_NOT_FOUND			3
/// 风控查询失败对应的风控ID未配置
#define QUERY_RISK_RULE_RESULT_RISK_RULE_ID_NOT_CONFIG			4
/// 风控查询失败该风控不支持查询
#define QUERY_RISK_RULE_RESULT_RISK_RULE_ID_NOT_SUPPORT_QUERY	5

/////////////////////////////////////////////////////////////////////////
///TShengliRiskValueUpdTimeType是一个风控更新时间格式
/////////////////////////////////////////////////////////////////////////
typedef char TShengliRiskValueUpdTimeType[24];

/////////////////////////////////////////////////////////////////////////
///TShengliAcctMonitorID是一个账户监控ID
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliAcctMonitorID;

/////////////////////////////////////////////////////////////////////////
///TShengliSeqNo是出入金序号类型
/////////////////////////////////////////////////1////////////////////////
typedef unsigned long long TShengliSeqNo;

/////////////////////////////////////////////////////////////////////////
///TShengliStockCashInOutFlag是一个出入金标志类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockCashInOutFlag;

/////////////////////////////////////////////////////////////////////////
///TShengliStockCashInOutTimeType是一个出入金时间格式
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockCashInOutTimeType[24];

/////////////////////////////////////////////////////////////////////////
///TShengliStockCashInOutAmountType是一个出入金格式
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long  TShengliStockCashInOutAmountType;
/////////////////////////////////////////////////////////////////////////
///TShengliStockErrText 消息内容
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockErrText[36];

/////////////////////////////////////////////////////////////////////////
///TShengliOrderType 订单类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockOrderType;

/////////////////////////////////////////////////////////////////////////
///TShengliMktCltOrdID	市场客户单号
/////////////////////////////////////////////////////////////////////////
typedef char TShengliMktCltOrdID[11];

/////////////////////////////////////////////////////////////////////////
///TShengliStockErrorText错误消息
/////////////////////////////////////////////////////////////////////////
typedef char	TShengliStockErrorText[256];
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
///TShengliStockErrCodeType是一个是否断开连接类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockErrCodeType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockResultText 消息内容
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockResultText[64];

/////////////////////////////////////////////////////////////////////////
///TShengliStockDisconnFlag是一个是否断开连接类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockDisconnFlag;

/////////////////////////////////////////////////////////////////////////
///TShengliOpStation是一个是否断开连接类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliOpStation[256];


/////////////////////////////////////////////////////////////////////////
///TShengliStockBindCpuNumType是一个绑核类型
/////////////////////////////////////////////////////////////////////////
typedef int TShengliStockBindCpuNumType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockSyncMethodType是一个同步方式类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSyncMethodType;

//同步
#define SOCKET_THREAD_SYNC  0
//异步
#define SOCKET_THREAD_ASYNC 1

/////////////////////////////////////////////////////////////////////////
///TShengliStockTimeType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned long long TShengliStockTimeType;

/////////////////////////////////////////////////////////////////////////
///TShengliStockReconnType是一个是否自动重连类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockReconnType;

//不自动重连
#define NOT_AUTO_RECONN 0
//自动重连
#define AUTO_RECONN		1

/////////////////////////////////////////////////////////////////////////
///TShengliStockSwitchType是一个开关类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockSwitchType;

//关闭
#define SWITCH_CLOSE 0
//开启
#define SWITCH_OPEN 1

/////////////////////////////////////////////////////////////////////////
///TShengliStockEthNameType是一个网卡名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliStockEthNameType[20];


///TShengliStockMsgIndex	消息index
typedef unsigned int TShengliStockMsgIndexType;

/// TShengliQuoteType 报价类型
typedef unsigned char   TShengliQuoteType;

#define QUOTE_TYPE_TRADE				1		///<  可交易报价

///TShengliQuoteSideType是一个报价开平方向类型
typedef char TShengliQuoteSideType;

#define QUOTE_OPEN_SIDE					'O'		///<开仓
#define QUOTE_CLOSE_SIDE				'C'		///<平仓

///TShengliQuoteReqID是一个询价请求编号类型
typedef char TShengliQuoteReqID[11];

///TShengliQuotePBU是一个报告/提交PBU类型
typedef char TShengliQuotePBU[7];

/// pbu 
typedef char TShengliPBU[8];

///TShengliRemOwnerType是一个所有者类型
typedef unsigned char TShengliRemOwnerType;

///TShengliMarketOrderID是一个市场单号类型
typedef char TShengliMarketOrderID[17];

///TShengliExecID是一个执行单号类型
typedef char TShengliExecID[17];

///TShengliClOrdID是一个客户订单编号类型
typedef char TShengliClOrdID[11];

///TShengliExchangeAccount是一个证券账户类型
typedef char TShengliExchangeAccount[13];

///TShengliQuoteRequestTransType是一个询价请求事务类型
typedef unsigned short TShengliQuoteRequestTransType;

#define QuoteRequestTransType_NewOrder		0  ///<  新订单
#define QuoteRequestTransType_Cancel		1  ///<  撤销

///TShengliStockReqType	申报类型
typedef unsigned char TShengliStockReqType;

///TShengliStockPfpFlag	盘后定价交易标志
typedef unsigned char TShengliStockPfpFlagType;

///TShengliStockExchangeOrderToken	面向交易所的ordertoken
typedef char TShengliStockExchangeOrderTokenType[16];

///TShengliStockOpstation	opstation
typedef unsigned long long TShengliStockOpstationType;

///TShengliStockUserInfoType2 是一个供客户使用的类型(新的8字节的）
typedef unsigned long long TShengliStockUserInfoType2;

///TShengliStockExchangeUserInfoType 是一个供客户使用的类型，交易所回报时将回传
typedef unsigned long long TShengliStockExchangeUserInfoType;

///TShengliStockRejectTextType是一个错误原因类型（新的8字节）
typedef char TShengliStockRejectTextType[8];

///TShengliStockPassiveOptrType是被动操作的操作员ID类型
typedef unsigned int TShengliStockPassiveOptrType;

///TShengliStockPassiveOptrType是被动操作的操作员ID类型
typedef unsigned int TShengliStockPassiveOptrType;

///TShengliStockErrorCodeType是错误码类型
typedef unsigned int TShengliStockErrorCodeType;


/////////////////////////////////////////////////////////////////////////
///TShengliCurrencyType是一个货币类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliCurrencyType;

//0:人民币
#define CURRENCY_CNY	'0'
//1:港币
#define CURRENCY_HKD	'1'
//2 : 美元
#define CURRENCY_USD	'2'

/////////////////////////////////////////////////////////////////////////
///TShengliExtOrgType是一个外部机构类型(备注: 银行代码)
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliExtOrgType;


/////////////////////////////////////////////////////////////////////////
///TShengliExtOrgNameType是一个外部机构名称类型(备注: 银行名称)
/////////////////////////////////////////////////////////////////////////
typedef char TShengliExtOrgNameType[32];


/////////////////////////////////////////////////////////////////////////
///TShengliOrgCodeType是一个外部机构类型(备注: 银行代码)
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliOrgCodeType;

/////////////////////////////////////////////////////////////////////////
///TShengliPwdType是一个密码类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliPwdType[33];

/////////////////////////////////////////////////////////////////////////
///TShengliCubsbTrdIDType是一个银衍业务标识类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliCubsbTrdIDType;
///银转衍
#define SHENGLI_STOCK_CUBSB_TRD_BANK_TO_DERIVE 11
///衍转银
#define SHENGLI_STOCK_CUBSB_TRD_DERIVE_TO_BANK 12

/////////////////////////////////////////////////////////////////////////
///TShengliCheckPasswdType是一个是否校验密码类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliCheckPasswdType;

/////////////////////////////////////////////////////////////////////////
///TShengliTransType是一个转账类型
/////////////////////////////////////////////////////////////////////////
typedef char TShengliTransType;
///银转衍
#define SHENGLI_STOCK_TRANS_TYPE_BANK_TO_DERIVE '1'
///衍转银
#define SHENGLI_STOCK_TRANS_TYPE_DERIVE_TO_BANK '2'

/////////////////////////////////////////////////////////////////////////
///TShengliChannelType是一个渠道类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliChannelType;

/////////////////////////////////////////////////////////////////////////
///TShengliQueryBankInfoResultType是一个查询签约银行信息返回结果类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliQueryBankInfoResultType;
///查询成功
#define SHENGLI_STOCK_QUERY_BANK_INFO_SUCCESS 0
///查询失败未找到用户信息
#define SHENGLI_STOCK_QUERY_BANK_INFO_FAILED_NOT_FOUND_USER_INFO 1
///查询失败未找到客户信息
#define SHENGLI_STOCK_QUERY_BANK_INFO_FAILED_NOT_FOUND_CLIENT_INFO 2
///查询失败未找到资金账号信息
#define SHENGLI_STOCK_QUERY_BANK_INFO_FAILED_NOT_FOUND_FUND_ACCOUNT_INFO 3
///查询失败检查req id失败
#define SHENGLI_STOCK_QUERY_BANK_INFO_FAILED_CHECK_REQ_ID_FAILED 6
///查询失败未找到sync_trade服务
#define SHENGLI_STOCK_QUERY_BANK_INFO_FAILED_NOT_FOUND_SYNC_TRADE_SERVICE 9
///查询失败主柜处理失败
#define SHENGLI_STOCK_QUERY_BANK_INFO_FAILED_JZ_PROCESS_FAILED 10

/////////////////////////////////////////////////////////////////////////
///TShengliOneStepTransferResultType是一个一步式请求结果类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned int TShengliOneStepTransferResultType;
///一步式转账成功
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_SUCCESS 0
///一步式转账失败未找到用户信息
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_NOT_FOUND_USER_INFO 1
///一步式转账失败未找到客户信息
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_NOT_FOUND_CLIENT_INFO 2
///一步式转账失败未找到资金账号信息
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_NOT_FOUND_FUND_ACCOUNT_INFO 3
///一步式转账失败划转方向不对
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_TRANSFER_DIR_FAILED 4
///一步式转账失败检查req id失败
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_CHECK_REQ_ID_FAILED 6
///一步式转账失败未找到sync_trade服务
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_NOT_FOUND_SYNC_TRADE_SERVICE 9
///一步式转账失败主柜处理失败
#define SHENGLI_STOCK_ONE_STEP_TRANSFER_FAILED_JZ_PROCESS_FAILED 10

/////////////////////////////////////////////////////////////////////////
///TShengliStockCxlReqStatusType是一个撤单状态类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockMarketCxlReqStatusType;
///当前订单接受无撤单
#define	 SHENGLI_STOCK_Market_Cxl_None		0
///撤单请求挂起中
#define  SHENGLI_STOCK_Market_Cxl_Pending	1
///撤单请求已成功, 双边订单已经撤销（做市仅上交所有效）
#define  SHENGLI_STOCK_Market_Cxled	2
///撤单请求被交易所拒绝, 订单保持原状态
#define  SHENGLI_STOCK_Market_Cxl_Rejected	3
///交易所主动撤单
#define	 SHENGLI_STOCK_Market_Exchange_Cxled	4
///撤单请求已经成功，仅BID订单已经撤销（上交所做市有效）
#define  SHENGLI_STOCK_Market_SH_BID_Cxled		5
///撤单请求已经成功，仅ASK订单已经撤销（上交所做市有效）
#define  SHENGLI_STOCK_Market_SH_ASK_Cxled		6
///交易所主动撤单，仅BID订单已经撤销（深交所做市有效）
#define  SHENGLI_STOCK_Market_SZ_BID_Cxled		7
///交易所主动撤单，仅ASK订单已经撤销（深交所做市有效）
#define  SHENGLI_STOCK_Market_SZ_ASK_Cxled		8

/// TShengliQuoteType 报价类型
typedef unsigned char   TShengliQuoteType;

//0:人民币
// #define CURRENCY_CNY	'0'
//1:港币
// #define CURRENCY_HKD	'1'
//2 : 美元
// #define CURRENCY_USD	'2'


#define QUOTE_TYPE_TRADE				1		///<  可交易报价

///TShengliQuoteSideType是一个报价开平方向类型
typedef char TShengliQuoteSideType;

#define QUOTE_OPEN_SIDE					'O'		///<开仓
#define QUOTE_CLOSE_SIDE				'C'		///<平仓

///TShengliQuoteReqID是一个询价请求编号类型
typedef char TShengliQuoteReqID[11];

///TShengliQuotePBU是一个报告/提交PBU类型
typedef char TShengliQuotePBU[7];

///TShengliRemOwnerType是一个所有者类型
typedef unsigned char TShengliRemOwnerType;

///TShengliMarketOrderID是一个市场单号类型
typedef char TShengliMarketOrderID[17];

///TShengliExecID是一个执行单号类型
typedef char TShengliExecID[17];

///TShengliClOrdID是一个客户订单编号类型
typedef char TShengliClOrdID[11];

///TShengliExchangeAccount是一个证券账户类型
typedef char TShengliExchangeAccount[13];

///TShengliQuoteRequestTransType是一个询价请求事务类型
typedef unsigned short TShengliQuoteRequestTransType;

#define QuoteRequestTransType_NewOrder		0  ///<  新订单
#define QuoteRequestTransType_Cancel		1  ///<  撤销

///TShengliQuoteReqType是一个报价申报类型
typedef unsigned char TShengliQuoteReqType;

#define QuoteReqType_NewOrder		1  ///<  新订单
#define QuoteReqType_Cancel			2  ///<  撤销
#define QuoteReqType_Canceled_Before_Mkt_Accept	3 ///<撤单乱序

///TShengliQuoteRequestType是一个询价请求类型
typedef unsigned short TShengliQuoteRequestType;

#define QuoteRequestType_Submit          101		///<提交
#define QuoteRequestType_Transmit        102      ///<转发

///TShengliQuoteRequestStatus是一个询价请求状态类型
typedef unsigned char TShengliQuoteRequestStatus;

#define QuoteRequestStatus_Accepted          0		///<已接受
#define QuoteRequestStatus_Cancelled         4		///<已撤销
#define QuoteRequestStatus_Refused           5		///<已拒绝
#define QuoteRequestStatus_TimeOut           7		///<已超时
#define QuoteRequestStatus_Filled            8		///<已成交

///TShengliPrivateQuote是一个私有报价类型
typedef unsigned char TShengliPrivateQuote;

#define PrivateQuote_Private          0		///<私有报价
#define PrivateQuote_Public           1     ///<公开报价

///TShengliQuotePriceType是一个报价价格类型
typedef unsigned short TShengliQuotePriceType;

#define QuotePriceType_Percent				1		///<百分比
#define QuotePriceType_PerShare             2       ///<每股

///TShengliMemo是一个备注类型
typedef char TShengliMemo[161];

///TShengliStockOutCashConditionFLagType是一个出金判断条件类型
typedef unsigned char  TShengliStockOutCashConditionFLagType;
// 根据可用资金来判断是否能够出金
#define CHECK_AVAIL_BP		   0
// 根据可取资金来判断是否能够出金
#define CHECK_DESIRABLE_BP     1

/// TShengliStockReferancePriceMode 引用价格类型
typedef unsigned char TShengliStockReferancePriceMode ;
#define ReferancePriceModePreSettlt 	1  // 昨收价
#define ReferancePriceModeLast 			2 // 最新价
#define ReferancePriceModeMax 			3 // Max（昨收价，最新价）


/// 费用类型
typedef unsigned char TShengliStockRemFeeType ; 
#define FeeType_StampDuty 		1  ///< 印花税
#define FeeType_TransferFee 	2  ///< 过户费
#define FeeType_TransactionFee  3  ///< 交易规费
#define FeeType_BorkerageFee    4  ///< 结算费
#define FeeType_SettlementFee   5  ///< 经手费
#define FeeType_Commission      6  ///< 手续费，佣金


/// 行权是否验仓
typedef unsigned char TShengliExerciseCheckPosType ; 
#define ExerciseCheckPos_NoCheck 	0  ///< 行权不验仓
#define ExerciseCheckPos_Check 	    1  ///< 行权验仓

///TShengliQueryFlag是一个查询源类型
typedef unsigned char TShengliQueryFlag;

#define QueryFlag_Node              0       ///< 从节点查询
#define QueryFlag_DataBase          1       ///< 从数据库查询,暂不支持

///TShengliSeqNumber64是一个64位序号类型
typedef unsigned long long TShengliSeqNumber64;

///TShengliSeqNumber32是一个32位序号类型
typedef unsigned int TShengliSeqNumber32;

/////////////////////////////////////////////////////////////////////////
///TShengliStockOrderStateType2是一个订单状态类型
/////////////////////////////////////////////////////////////////////////
typedef unsigned char TShengliStockOrderStateType;

#define SHENGLI_STOCK_OrderState_Pending            0       ///< 待报
#define SHENGLI_STOCK_OrderState_ExchAccept         64      ///< 交易所接受
#define SHENGLI_STOCK_OrderState_Cancelled          81      ///< 交易所撤单接受，订单已关闭
#define SHENGLI_STOCK_OrderState_Part_Execution     96      ///< 部分成交
#define SHENGLI_STOCK_OrderState_Full_Execution     97      ///< 全成
#define SHENGLI_STOCK_OrderState_Exec_Cancelled     113     ///< 部成部撤
#define SHENGLI_STOCK_OrderState_Reject             129     ///< 交易所拒绝，废单
    
#define SHENGLI_STOCK_OrderState_Closed             1       ///< 已关闭，目前仅存在于单边报价单
#define SHENGLI_STOCK_OrderState_ExchAccept_Closed  65  ///< 交易所接受并关闭订单，目前仅存在于报价撤单

/// 资金账户列表查询响应结果类型
typedef unsigned int TShengliStockAcctListQueryResultType;
/// 0: 资金账户列表查询成功
#define ACCT_LIST_QUERY_RESULT_SUCCESS 0
/// 1: 查询失败, 用户ID或者客户号填写错误
#define ACCT_LIST_QUERY_RESULT_USER_ID_OR_CUST_ID_FAILED 1
/// 2: 查询失败, 未找到对应客户号信息
#define ACCT_LIST_QUERY_RESULT_NOT_FOUND_CUST_INFO 2

/// 客户号资金状态查询响应结果类型
typedef unsigned int TShengliStockBpStatusQueryResultType;
/// 0: 客户号资金状态查询响应结果成功
#define BP_STATUS_QUERY_RESULT_SUCCESS 0
/// 1: 查询失败, 用户ID或者客户号填写错误
#define BP_STATUS_QUERY_RESULT_USER_ID_OR_CUST_ID_FAILED 1

/// 查询出入金列表返回响应结果类型
typedef unsigned int TShengliStockCashInOutQueryResultType;
/// 0: 查询出入金列表成功
#define CASH_IN_OUT_QUERY_RESULT_SUCCESS 0
/// 1: 查询失败, 用户ID或者客户号填写错误
#define CASH_IN_OUT_QUERY_RESULT_USER_ID_OR_CUST_ID_FAILED 1

/// 查询向交易节点资金划转响应结果类型
typedef unsigned int TShengliStockTransfBpDetailQueryResultType;
/// 0: 查询交易节点资金划拨成功
#define TRANSF_BP_DETAIL_QUERY_RESULT_SUCCESS 0
/// 1: 查询失败, 用户ID或者客户号信息错误.
#define TRANSF_BP_DETAIL_QUERY_RESULT_USER_ID_OR_CUST_ID_FAILED 1
/// 2: 查询失败, 数据库查询操作失败
#define TRANSF_BP_DETAIL_QUERY_RESULT_OPERATOR_DB_FAILED 2
/// 3: 查询失败, 出金记录为空
#define TRANSF_BP_DETAIL_QUERY_RESULT_QUERY_EMPTY 3

#endif  

