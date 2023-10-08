/*!
* \file  RejectReasonDesc.h
* \brief 交易和查询客户端公共的头文件
*
* 此文件描述了使用交易和查询客户端公共的所需的类型和函数
*
* \author  SHENGLI
* \version 1.0
* \date    2014-04-18
*/

#pragma once

#include <string>
using std::string;

class RejectReasonDesc
{
	string m_cxlOrderGrammarDesc[33];
	string m_newOrdergrammarDesc[33];
	string m_riskRuleDesc[64];

public:
	
	RejectReasonDesc()
	{
		/// 撤单
		m_cxlOrderGrammarDesc[1] = "1.用户不合法;";
		m_cxlOrderGrammarDesc[2] = "2.下单ID数字校验;";
		m_cxlOrderGrammarDesc[3] = "3.订单号不合法;";
		m_cxlOrderGrammarDesc[4] = "4.订单已经在撤单中;";
		m_cxlOrderGrammarDesc[5] = "5.订单已成交;";
		m_cxlOrderGrammarDesc[6] = "6.订单已撤单;";
		m_cxlOrderGrammarDesc[7] = "7.订单已拒绝;";
		m_cxlOrderGrammarDesc[8] = "8.交易所session;";
		m_cxlOrderGrammarDesc[9] = "9.被动订单;";
		m_cxlOrderGrammarDesc[10] = "10.订单不支持撤单;";
		m_cxlOrderGrammarDesc[11] = "11.普通用户对超级用户的订单进行撤单;";
		m_cxlOrderGrammarDesc[12] = "12.行权单的撤单时无市场accept;";
		m_cxlOrderGrammarDesc[13] = "13.报单ID范围超限;";
		m_cxlOrderGrammarDesc[14] = "14.撤单的RecordNum为0;";
		
		/// 下单
		m_newOrdergrammarDesc[1]  = "1.下单ID数字校验;";
		m_newOrdergrammarDesc[2]  = "2.下单目的地不合法;";
		m_newOrdergrammarDesc[3]  = "3.单子存活时间非法;";
		m_newOrdergrammarDesc[4]  = "4.价格不合法;";
		m_newOrdergrammarDesc[5]  = "5.合约不存在;";
		m_newOrdergrammarDesc[6]  = "6.下单数量不合法;";
		m_newOrdergrammarDesc[7]  = "7.账户不存在或没有权限;";
		m_newOrdergrammarDesc[8]  = "8.买卖方向不合法;";
		m_newOrdergrammarDesc[9]  = "9.权限不合法;";
		m_newOrdergrammarDesc[10] = "10.系统容量超限;";
		m_newOrdergrammarDesc[11] = "11.用户不合法;";
		m_newOrdergrammarDesc[12] = "12.市价单组合非法;";
		m_newOrdergrammarDesc[13] = "13.交易所session;";
		m_newOrdergrammarDesc[14] = "14.行权日期不正确;";
		m_newOrdergrammarDesc[15] = "15.报单ID范围超限;";
		m_newOrdergrammarDesc[16] = "16.限制买入风险警示板股票;";
		m_newOrdergrammarDesc[17] = "17.债券交易权限检查失败;";
		m_newOrdergrammarDesc[18] = "18.业务行为权限检查失败;";
		m_newOrdergrammarDesc[19] = "19.交易品种权限检查失败;";
		m_newOrdergrammarDesc[20] = "20.期权组合策略非法";
		m_newOrdergrammarDesc[21] = "21.违反委托组合策略申报约束";
		m_newOrdergrammarDesc[22] = "22.违反组合策略行权价约束";
		m_newOrdergrammarDesc[23] = "23.期权组合解除时，委托pbu、accountid、SecurityID和组合持仓不匹配。";
		m_newOrdergrammarDesc[24] = "24.期权组合解除时，找不到seqID ";
		m_newOrdergrammarDesc[25] = "25.期权合并行权非法";
        m_newOrdergrammarDesc[26] = "26.港股合约没有买权限";
        m_newOrdergrammarDesc[27] = "27.该ETF不支持申购/赎回操作";
        m_newOrdergrammarDesc[28] = "28.client有ETF申赎订单在处理";
        m_newOrdergrammarDesc[29] = "29.非做市商不允许下双边报价";
        m_newOrdergrammarDesc[30] = "30.不允许重复申购";
        m_newOrdergrammarDesc[31] = "31.硬件看门狗检测到软件异常";

		/// 风控
		m_riskRuleDesc[1] = "1.验资;";
		m_riskRuleDesc[2] = "2.验仓;";
		m_riskRuleDesc[3] = "3.验价;";
		m_riskRuleDesc[4] = "4.订单手数限制;";
		m_riskRuleDesc[5] = "5.自成交检查;";
		m_riskRuleDesc[6] = "6.订单报价百分比超限:与最近成交价相比;";
		m_riskRuleDesc[7] = "7.订单报价百分比超限:与昨结算/昨收价相比;";
		m_riskRuleDesc[8] = "8.累计订单发出次数限制;";
		m_riskRuleDesc[9] = "9.累计撤单发出次数限制;";
		m_riskRuleDesc[10]= "10.累计委托申报次数限制;";
		m_riskRuleDesc[11]= "11.大额订单撤单次数限制;";
		m_riskRuleDesc[12]= "12.大额订单下单次数限制;";
		m_riskRuleDesc[13]= "13.大额订单委托申报次数限制;";
		m_riskRuleDesc[14]= "14.在指定时间段1内收到订单次数上限;";
		m_riskRuleDesc[15]= "15.在指定时间段2内收到订单次数上限;";
		m_riskRuleDesc[16]= "16.在指定时间段3内收到订单次数上限;";
		m_riskRuleDesc[17]= "17.在指定时间1内撤单次数上限;";
		m_riskRuleDesc[18]= "18.在指定时间2内撤单次数上限;";
		m_riskRuleDesc[19]= "19.在指定时间3内撤单次数上限;";
		m_riskRuleDesc[20]= "20.在指定时间1内委托申报次数上限;";
		m_riskRuleDesc[21]= "21.在指定时间2内委托申报次数上限;";
		m_riskRuleDesc[22]= "22.在指定时间3内委托申报次数上限;";
		m_riskRuleDesc[23]= "23.在指定时间1内下订单被市场拒绝次数上限;";
		m_riskRuleDesc[24]= "24.在指定时间2内下订单被市场拒绝次数上限;";
		m_riskRuleDesc[25]= "25.在指定时间3内下订单被市场拒绝次数上限;";
		m_riskRuleDesc[26]= "26.在指定时间1内下订单被柜台系统拒绝次数上限;";
		m_riskRuleDesc[27]= "27.在指定时间2内下订单被柜台系统拒绝次数上限;";
		m_riskRuleDesc[28]= "28.在指定时间3内下订单被柜台系统拒绝次数上限;";
		m_riskRuleDesc[29]= "29.在指定时间1内撤单被市场拒绝次数上限;";
		m_riskRuleDesc[30]= "30.在指定时间2内撤单被市场拒绝次数上限;";
		m_riskRuleDesc[31]= "31.在指定时间3内撤单被市场拒绝次数上限;";
		m_riskRuleDesc[32]= "32.禁止交易symbol;";
		m_riskRuleDesc[33]= "33.证券买卖控制;";
		m_riskRuleDesc[34]= "34.公司对冲风险度;";
		m_riskRuleDesc[35]= "35.买入额度上限;";
		m_riskRuleDesc[36]= "36.同一合约品种权利仓持仓数量上限;";
		m_riskRuleDesc[37]= "37.同一市场期权品种单日买入开仓数量上限;";
		m_riskRuleDesc[38]= "38.同一市场期权品种单日卖出开仓数量上限;";
		m_riskRuleDesc[39]= "39.同一合约品种义务仓持仓数量上限;";
		m_riskRuleDesc[40]= "40.同一市场期权权利仓持仓数量上限;";
		m_riskRuleDesc[41]= "41.同一市场期权义务仓持仓数量上限;";
		m_riskRuleDesc[42]= "42.同一合约品种总持仓数量上限;";
		m_riskRuleDesc[43]= "43.同一市场期权总持仓数量上限;";
		m_riskRuleDesc[44]= "44.同一期权标的证券持仓数量上限;";
		m_riskRuleDesc[45]= "45.同一合约品种当日买入开仓数量上限;";
		m_riskRuleDesc[46]= "46.同一合约品种当日开仓数量上限;";
		m_riskRuleDesc[47]= "47.账户+合约交易控制;";
		m_riskRuleDesc[48]= "48.实时风险值一;";
		m_riskRuleDesc[49] = "49.实时风险值二;";
		m_riskRuleDesc[50] = "50.同一合约品种当日卖出开仓数量上限;";
		m_riskRuleDesc[51] = "51.同一期权合约品种当日成交数量上限;";
		m_riskRuleDesc[52] = "52.同一期权合约品种单笔委托数量上限;";
		m_riskRuleDesc[53] = "53.风险警示买入超限;";
		m_riskRuleDesc[54] = "54.净买入额度超限;";
		m_riskRuleDesc[56] = "56.报价单数量下限;";

		m_riskRuleDesc[62]= "62:数据溢出;";
	}

	string GetOrderRejectDesc(int grammarResult, unsigned char* riskResult)
	{
		int reject_count = 0;
		int const_reject_max_count = 5;

		string strReason;

		bool b_first_grammar_rej = true;

		char baseBit = 0x01 ;
		if (0 != grammarResult)
		{
			for (int bitIdx = 1; bitIdx <= 31; ++bitIdx)
			{
				unsigned int curValue = (baseBit << bitIdx);
				if (curValue & grammarResult)
				{
					if (reject_count++ < const_reject_max_count)
					{
						string strCurReason;
						if (b_first_grammar_rej)
						{
							b_first_grammar_rej = false;
							strCurReason = string("违反语法风控:") + m_newOrdergrammarDesc[bitIdx];
						}
						else
						{
							strCurReason = m_newOrdergrammarDesc[bitIdx];
						}
						strReason.append(strCurReason.c_str());
					}
				}
			}
		}

		bool b_first_tu_rej = true;

		int ACC_RISK_LEN = 16;
		for (int ruleIdx = 1; ruleIdx <= 56; ++ruleIdx)
		{
			int chBitLen = 8;
			int chIdx    = (ACC_RISK_LEN - 1) - ((ruleIdx - 1) / chBitLen) ;
			int chBitIdx = (ruleIdx - 1) % chBitLen ; 

			if (riskResult[chIdx] & (baseBit << chBitIdx))
			{
				if (reject_count++ < const_reject_max_count)
				{
					string strCurReason;
					if (b_first_tu_rej)
					{
						strCurReason = "违反交易单元风控:";
						b_first_tu_rej = false;
						strCurReason = strCurReason + m_riskRuleDesc[ruleIdx];
					}
					else
					{
						strCurReason = m_riskRuleDesc[ruleIdx];
					}

					strReason.append(strCurReason.c_str());
				}
			}
		}
		 
		// 判断  62号 RULE
		for (int ruleIdx = 62; ruleIdx <= 62; ++ruleIdx)
		{
			int chBitLen = 8;
			int chIdx    = (ACC_RISK_LEN - 1) - ((ruleIdx - 1) / chBitLen) ;
			int chBitIdx = (ruleIdx - 1) % chBitLen ; 

			if (riskResult[chIdx] & (baseBit << chBitIdx))
			{
				if (reject_count++ < const_reject_max_count)
				{
					string strCurReason;
					if (b_first_tu_rej)
					{
						strCurReason = "违反风控:";
						b_first_tu_rej = false;
						strCurReason = strCurReason + m_riskRuleDesc[ruleIdx];
					}
					strReason.append(strCurReason.c_str());
				}
			}
		}

		return strReason;
	}

	string GetCancelRejectDesc(int grammarResult,  unsigned char* riskResult)
	{
		const int const_reject_max_count = 5;
		int reject_count = 0;

		string strReason;
		bool b_first_grammar_rej = true;

		char baseBit = 0x01 ;
		if (0 != grammarResult)
		{
			for (int bitIdx = 1; bitIdx <= 14; ++bitIdx)
			{
				unsigned int curValue = (baseBit << bitIdx);
				if (curValue & grammarResult)
				{
					if (reject_count++ < const_reject_max_count)
					{
						string strCurReason;
						if (b_first_grammar_rej)
						{
							b_first_grammar_rej = false;
							strCurReason = string("违反语法风控:") + m_cxlOrderGrammarDesc[bitIdx];
						}
						else
						{
							strCurReason = m_cxlOrderGrammarDesc[bitIdx];
						}
						strReason.append(strCurReason.c_str());
					}
				}
			}
		}

		int ACC_RISK_LEN = 16;

		bool b_first_acc_rej = true;
		for (int ruleIdx = 1; ruleIdx <= 46; ++ruleIdx)
		{
			int chBitLen = 8;
			int chIdx    = (ACC_RISK_LEN - 1) - ((ruleIdx - 1) / chBitLen) ;
			int chBitIdx = (ruleIdx - 1) % chBitLen ; 

			if (riskResult[chIdx] & (baseBit << chBitIdx))
			{
				if (reject_count++ < const_reject_max_count)
				{
					string strCurReason;
					if (b_first_acc_rej)
					{
						strCurReason = "违反风控:";
						b_first_acc_rej = false;
						strCurReason = strCurReason + m_riskRuleDesc[ruleIdx];
					}
					else
					{
						strCurReason = m_riskRuleDesc[ruleIdx];
					}
					strReason.append(strCurReason.c_str());
				}
			}
		}

		return strReason;
	}
};

