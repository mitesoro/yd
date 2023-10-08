/*!****************************************************************************
 @note   Copyright (coffee), 2005-2014, Shengli Tech. Co., Ltd.
 @file   EESQuoteDemo.h
 @date   2014/4/27   12:31
 @author zhou.hu
 
 \brief  ������ʾ��EES����API��ʹ��ʾ����

 @note 
******************************************************************************/

#pragma once

#ifdef WIN32
/// add by zhou.hu review 2014/4/22 Windwosƽ̨���õ�ͷ�ļ�
#include <Windows.h>

typedef HMODULE		T_DLL_HANDLE;

#else
/// add by zhou.hu review 2014/4/22 linuxƽ̨���õ�ͷ�ļ�
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

typedef void*		T_DLL_HANDLE;

#endif

#include <string>
#include "./quote/C++/EESQuoteApi.h"

using std::string;

class QuoteDemo : public EESQuoteEvent
{
public:
	QuoteDemo(void);
	virtual ~QuoteDemo(void);
	
	/// \brief ������ں���
	void Run();

private:
	/// \brief ��ʼ��
	bool Init();
	/// \brief �ر�
	void Close();

	/// \brief ��ͣ
	void Pause();

private:
	/// \brief ����EES����API�Ķ�̬��
	bool LoadEESQuote();
	/// \brief �ͷ�EES����API�Ķ�̬��
	void UnloadEESQuote();

	/// \brief Windows���������API�Ķ�̬��
	bool Windows_LoadEESQuote();
	/// \brief Windows���ͷ�����API�Ķ�̬��
	void Windows_UnloadEESQuote();

	/// \brief Linux�汾��������API�Ķ�̬��
	bool Linux_LoadEESQuote();
	/// \brief Linux�汾�ͷ�����API�Ķ�̬��
	void Linux_UnloadEESQuote();

	/// \brief ��ʼ��������������
	void InputParam();

	/// \brief ��¼
	void Logon();
	/// \brief ��ѯ���к�Լ
	void QueryAllSymbol();
	/// \brief ��ʾ������Ϣ
	void ShowQuote(EESMarketDepthQuoteData* pQuote);
	
private:

	/// \brief �����������ӳɹ�����¼ǰ����, ������鲥ģʽ���ᷢ��, ֻ���ж�InitMulticast����ֵ����
	virtual void OnEqsConnected();
	/// \brief ���������������ӳɹ������Ͽ�ʱ���ã��鲥ģʽ���ᷢ�����¼�
	virtual void OnEqsDisconnected();
	/// \brief ����¼�ɹ�����ʧ��ʱ���ã��鲥ģʽ���ᷢ��
	virtual void OnLoginResponse(const char* eqsId, bool bSuccess, const char* pReason);
	/// \brief �յ�����ʱ����,�����ʽ����instrument_type��ͬ����ͬ
	virtual void OnQuoteUpdated(EqsExchangeId exchangeId, EESMarketDepthQuoteData* pDepthQuoteData);
	/// \brief ��־�ӿڣ���ʹ���߰���д��־��
	virtual void OnWriteTextLog(EesEqsLogLevel nlevel, const char* pLogText, int nLogLen);
	/// \brief ע��symbol��Ӧ��Ϣ��ʱ���ã��鲥ģʽ��֧������ע��
	virtual void OnSymbolRegisterResponse(EqsExchangeId exchangeId, const char* pSymbol, bool bSuccess);
	/// \brief  ע��symbol��Ӧ��Ϣ��ʱ���ã��鲥ģʽ��֧������ע��
	virtual void OnSymbolUnregisterResponse(EqsExchangeId exchangeId, const char* pSymbol, bool bSuccess);
	/// \brief ��ѯsymbol�б���Ӧ��Ϣ��ʱ���ã��鲥ģʽ��֧�ֺ�Լ�б��ѯ
	virtual void OnSymbolListResponse(const char* eqsId, EqsExchangeId exchangeId, const char* pSymbol, bool bLast);
	/// \brief ��ѯ��������Ӧ�ĺ�Լ��Ϣ
	virtual void OnQuerySymbolQuoteResponse(EqsExchangeId exchangeId, const char* pSymbol, EESMarketDepthQuoteData* pDepthQuoteData);


private:
	EESQuoteApi*				m_eesApi;				///< EES����API�ӿ�
	T_DLL_HANDLE				m_handle;				///< EES����API���
	funcDestroyEESQuoteApi		m_distoryFun;			///< EES����API�������ٺ���

	string						m_quoteServerIp;		///< ���������IP
	int							m_quotePort;			///< ����������˿�
	vector<EqsTcpInfo>			m_vec_ServerInfo;		///< ��Ҫ���ӵ����������Ϣ
	string						m_logonId;				///< ��¼���
	string						m_logonPwd;				///< ��¼����


	int                         m_regSymCount;
	char						m_c_need_quote_type;	///< ��Ҫ������������

	bool 						m_b_logoned;			///< �Ƿ��¼
};

