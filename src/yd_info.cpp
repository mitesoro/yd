#include <map>
#include "ydExample.h"

/*
±¾Ê¾ÀýÍ¬Ê±Õ¹Ê¾ÏÂÁÐ¹¦ÄÜ
ListOptionExecute:ÁÐ³öËùÓÐÓÐÐ§µÄÆÚÈ¨Ö´ÐÐµ¥
InsertOptionExecute:²åÈëÒ»ÕÅÒ»ÊÖµÄÆÚÈ¨Ö´ÐÐµ¥
CancelAllOptionExecute:É¾³ýËùÓÐÓÐÐ§µÄÆÚÈ¨Ö´ÐÐµ¥
ListOptionAbandonExecute:ÁÐ³öËùÓÐÓÐÐ§µÄÆÚÈ¨·ÅÆúÖ´ÐÐµ¥
InsertOptionAbandonExecute:²åÈëÒ»ÕÅÒ»ÊÖµÄÆÚÈ¨·ÅÆúÖ´ÐÐµ¥
CancelAllOptionAbandonExecute:É¾³ýËùÓÐÓÐÐ§µÄÆÚÈ¨·ÅÆúÖ´ÐÐµ¥
RequestForQuote:·¢³öÒ»ÕÅÑ¯¼Û£¨»ñÈ¡±ðÈËÑ¯¼ÛµÄÀý×Ó¼ûExample6£©
*/

const int ListOptionExecute=0;
const int InsertOptionExecute=1;
const int CancelAllOptionExecute=2;
const int ListOptionAbandonExecute=3;
const int InsertOptionAbandonExecute=4;
const int CancelAllOptionAbandonExecute=5;
const int RequestForQuote=6;
const int PutOrder=7;

class YDExample5Listener: public YDListener
{
private:
    YDApi *m_pApi;
    const char *m_username,*m_password,*m_instrumentID;
    int m_maxOrderRef;
    int m_action;
    bool m_hasCaughtUp;

    // Ö¸ÏòÏ£Íû´¦ÀíµÄÆ·ÖÖ
    const YDInstrument *m_pInstrument;

    // ËùÓÐÓÐÐ§µÄÆÚÈ¨Ö´ÐÐµ¥£¬LongOrderSysID->YDOrder
    std::map<long long,YDOrder> m_optionExecuteMap;

    // ËùÓÐÓÐÐ§µÄÆÚÈ¨·ÅÆúÖ´ÐÐµ¥£¬LongOrderSysID->YDOrder
    std::map<long long,YDOrder> m_optionAbandonExecuteMap;

    // ×¢Òâ£¬ÉÏÊöÁ½¸ömap±ØÐë·Ö¿ª£¬ÒòÎª¸÷¸ö½»Ò×ËùÄÚµÄLongOrderSysID²¢²»ÊÇÖ÷Âë£¬(LongOrderSysID,YDOrderFlag)²ÅÄÜ¹¹³ÉÖ÷Âë

public:
    YDExample5Listener(YDApi *pApi,const char *username,const char *password,const char *instrumentID,int action)
    {
        m_pApi=pApi;
        m_username=username;
        m_password=password;
        m_instrumentID=instrumentID;
        m_maxOrderRef=0;
        m_action=action;
        m_hasCaughtUp=false;
    }
    virtual void notifyReadyForLogin(bool hasLoginFailed)
    {
        // µ±API×¼±¸µÇÂ¼Ê±£¬·¢³ö´ËÏûÏ¢£¬ÓÃ»§ÐèÒªÔÚ´ËÊ±·¢³öµÇÂ¼Ö¸Áî
        // Èç¹û·¢ÉúÁË¶ÏÏßÖØÁ¬£¬Ò²»á·¢³ö´ËÏûÏ¢£¬ÈÃÓÃ»§ÖØÐÂ·¢³öµÇÂ¼Ö¸Áî£¬µ«ÊÇ´ËÊ±²»ÔÊÐí»»³ÉÁíÍâµÄÓÃ»§µÇÂ¼
        if (!m_pApi->login(m_username,m_password,NULL,NULL))
        {
            printf("can not login\n");
            exit(1);
        }
        m_hasCaughtUp=false;
    }
    virtual void notifyLogin(int errorNo, int maxOrderRef, bool isMonitor)
    {
        // Ã¿´ÎµÇÂ¼ÏìÓ¦£¬¶¼»á»ñµÃ´ËÏûÏ¢£¬ÓÃ»§Ó¦µ±¸ù¾ÝerrorNoÀ´ÅÐ¶ÏÊÇ·ñµÇÂ¼³É¹¦
        if (errorNo==0)
        {
            // µÇÂ¼³É¹¦ºó£¬Ó¦µ±¼ÇÂ¼µ±Ç°µÄ×î´ó±¨µ¥ÒýÓÃ£¬ÔÚ±¨µ¥Ê±ÓÃ¸ü´óµÄÊý×÷Îª±¨µ¥ÒýÓÃ£¬ÒÔ±ã³ÌÐòÍ¨¹ý±¨µ¥ÒýÓÃÀ´Ê¶±ð±¨µ¥
            m_maxOrderRef=maxOrderRef;
            printf("login successfully\n");
        }
        else
        {
            // Èç¹ûµÇÂ¼Ê§°Ü£¬ÓÐ¿ÉÄÜÊÇ·þÎñÆ÷¶ËÉÐÎ´Æô¶¯£¬ËùÒÔ¿ÉÒÔÑ¡Ôñ²»ÖÕÖ¹³ÌÐò£¬µ«ÊÇ²»ÐèÒªÔÚÕâÀïÔÙ´Î·¢³öµÇÂ¼ÇëÇó¡£
            // Api»áÉÔ¹ýÒ»»á¶ùÔÙ´Î¸ø³önotifyReadyForLoginÏûÏ¢£¬Ó¦µ±ÔÚÄÇÊ±·¢³öµÇÂ¼ÇëÇó
            printf("login failed, errorNo=%d\n",errorNo);
            exit(1);
        }
    }
    virtual void notifyFinishInit(void)
    {
        // notifyFinishInitÊÇÔÚµÚÒ»´ÎµÇÂ¼³É¹¦ºóÒ»Ð¡¶ÎÊ±¼ä·¢³öµÄÏûÏ¢£¬±íÊ¾APIÒÑ¾­ÊÕµ½ÁË½ñÌìµÄËùÓÐ³õÊ¼»¯ÐÅÏ¢£¬
        // °üÀ¨ËùÓÐµÄ²úÆ·ºÏÔ¼ÐÅÏ¢£¬×òÐÐÇéºÍ½ñÈÕµÄ¹Ì¶¨ÐÐÇé£¨ÀýÈçÕÇµøÍ£°å£©ÐÅÏ¢£¬ÕËºÅµÄÈÕ³õÐÅÏ¢£¬±£Ö¤½ðÂÊÐÅÏ¢£¬
        // ÊÖÐø·ÑÂÊÐÅÏ¢£¬×ò³Ö²ÖÐÅÏ¢£¬µ«ÊÇ»¹Ã»ÓÐ»ñµÃµÇÂ¼Ç°ÒÑ¾­·¢ÉúµÄ±¨µ¥ºÍ³É½»ÐÅÏ¢£¬ÈÕÄÚµÄ³öÈë½ðÐÅÏ¢
        // Õâ¸öÊ±ºò£¬ÓÃ»§³ÌÐòÒÑ¾­¿ÉÒÔ°²È«µØ·ÃÎÊËùÓÐAPI¹ÜÀíµÄÊý¾Ý½á¹¹ÁË
        // ÓÃ»§³ÌÐò»ñµÃËùÓÐYDSystemParam£¬YDExchange£¬YDProduct£¬YDInstrument£¬YDCombPositionDef£¬YDAccount£¬
        // YDPrePosition£¬YDMarginRate£¬YDCommissionRate£¬YDAccountExchangeInfo£¬YDAccountProductInfo£¬
        // YDAccountInstrumentInfoºÍYDMarketDataµÄÖ¸Õë£¬¶¼¿ÉÒÔÔÚÎ´À´³¤ÆÚ°²È«Ê¹ÓÃ£¬API²»»á¸Ä±äÆäµØÖ·
        // µ«ÊÇAPIÏûÏ¢ÖÐµÄYDOrder¡¢YDTrade¡¢YDInputOrder¡¢YDQuote¡¢YDInputQuoteºÍYDCombPositionµÄµØÖ·¶¼ÊÇ
        // ÁÙÊ±µÄ£¬ÔÚ¸ÃÏûÏ¢´¦ÀíÍê³Éºó½«²»ÔÙÓÐÐ§
        m_pInstrument=m_pApi->getInstrumentByID(m_instrumentID);
        if (m_pInstrument==NULL)
        {
            printf("can not find instrument %s\n",m_instrumentID);
            exit(1);
        }
    }
    virtual void notifyCaughtUp(void)
    {
        m_hasCaughtUp=true;
        switch (m_action)
        {
            case ListOptionExecute:
                listOptionExecute();
                break;
            case InsertOptionExecute:
                insertOptionExecute();
                break;
            case PutOrder:
                putOrder();
                break;
            case CancelAllOptionExecute:
                cancelAllOptionExecute();
                break;
            case ListOptionAbandonExecute:
                listOptionAbandonExecute();
                break;
            case InsertOptionAbandonExecute:
                insertOptionAbandonExecute();
                break;
            case CancelAllOptionAbandonExecute:
                cancelAllOptionAbandonExecute();
                break;
            case RequestForQuote:
                insertRequestForQuote();
                break;
            default:
                break;
        }
    }
    void showFailedOptionExecute(const YDOrder *pFailedOrder)
    {
        printf("OptionExecuteFailed:Volume=%d ErrorNo=%d\n",pFailedOrder->OrderVolume,pFailedOrder->ErrorNo);
    }
    void showOptionExecute(const YDOrder *pOrder)
    {
        printf("OptionExecute:LongOrderSysID=%lld Volume=%d OrderStatus=%d\n",pOrder->LongOrderSysID,pOrder->OrderVolume,pOrder->OrderStatus);
    }
    void showFailedOptionAbandonExecute(const YDOrder *pFailedOrder)
    {
        printf("OptionAbandonExecuteFailed:Volume=%d ErrorNo=%d\n",pFailedOrder->OrderVolume,pFailedOrder->ErrorNo);
    }
    void showOptionAbandonExecute(const YDOrder *pOrder)
    {
        printf("OptionAbandonExecute:LongOrderSysID=%lld Volume=%d OrderStatus=%d\n",pOrder->LongOrderSysID,pOrder->OrderVolume,pOrder->OrderStatus);
    }
    virtual void notifyOrder(const YDOrder *pOrder,const YDInstrument *pInstrument,const YDAccount *pAccount)
    {
        if (pOrder->ErrorNo == 0)
        {
            printf("\tnotifyOrder::交易所接受报单/撤单\n");
            printf("\tOrderRef: %d OrderLocalID: %d\n",pOrder->OrderRef ,pOrder->OrderLocalID);
            printf("\tOrderSysID %d\n",pOrder->OrderSysID);
            printf("\t报单状态\n");

            switch (pOrder->OrderStatus)
            {
                case YD_OS_Queuing:
                    printf("交易所确认报单(部成或未成)");
                    break;
                case YD_OS_Canceled:
                    printf( "报单已被撤销");
                    break;
                case YD_OS_AllTraded:
                    printf("全部成交");
                    break;
                default:
                    printf( "未知");
            }
            printf("\t报单已成交量：%d", pOrder->TradeVolume);
        }
        else
        {
            printf( "\tnotifyOrder::交易所拒绝报单\n");
            printf(  "\tOrderRef: %d\n" ,pOrder->OrderRef);
            printf(   "\t错误码：%d\n", pOrder->ErrorNo);
        }

        return;
        if (pInstrument!=m_pInstrument)
        {
            return;
        }
        if (pOrder->YDOrderFlag==YD_YOF_OptionExecute)
        {
            // ÊÇÆÚÈ¨Ö´ÐÐ
            if (m_hasCaughtUp)
            {
                // ÔÚÒÑ¾­×·ÉÏµÄÇé¿öÏÂ£¬Á¢¼´½«¸Ã±¨µ¥µÄÐÅÏ¢Êä³ö
                if (pOrder->OrderStatus==YD_OS_Rejected)
                {
                    showFailedOptionExecute(pOrder);
                }
                else
                {
                    showOptionExecute(pOrder);
                }
            }
            else
            {
                // Ã»ÓÐ×·ÉÏµÄÇé¿öÏÂ£¬½«ÐÅÏ¢±£´æ
                if (pOrder->OrderStatus==YD_OS_Queuing)
                {
                    // ¸Ã±¨µ¥×´Ì¬ËµÃ÷¸Ã±¨µ¥±»½»Ò×Ëù½ÓÊÜ
                    m_optionExecuteMap[pOrder->LongOrderSysID]=*pOrder;
                }
                else
                {
                    // ÆäËû×´Ì¬£¨Ö»¿ÉÄÜÊÇYD_OS_Canceled»òÕßYD_OS_Rejected£©ËµÃ÷¸Ã±¨µ¥Ò»¶¨ÎÞÐ§
                    m_optionExecuteMap.erase(pOrder->LongOrderSysID);
                }
            }
        }
        else if (pOrder->YDOrderFlag==YD_YOF_OptionAbandonExecute)
        {
            // ÊÇÆÚÈ¨·ÅÆúÖ´ÐÐ
            if (m_hasCaughtUp)
            {
                // ÔÚÒÑ¾­×·ÉÏµÄÇé¿öÏÂ£¬Á¢¼´½«¸Ã±¨µ¥µÄÐÅÏ¢Êä³ö
                if (pOrder->OrderStatus==YD_OS_Rejected)
                {
                    showFailedOptionAbandonExecute(pOrder);
                }
                else
                {
                    showOptionAbandonExecute(pOrder);
                }
            }
            else
            {
                // Ã»ÓÐ×·ÉÏµÄÇé¿öÏÂ£¬½«ÐÅÏ¢±£´æ
                if (pOrder->OrderStatus==YD_OS_Queuing)
                {
                    // ¸Ã±¨µ¥×´Ì¬ËµÃ÷¸Ã±¨µ¥±»½»Ò×Ëù½ÓÊÜ
                    m_optionAbandonExecuteMap[pOrder->LongOrderSysID]=*pOrder;
                }
                else
                {
                    // ÆäËû×´Ì¬£¨Ö»¿ÉÄÜÊÇYD_OS_Canceled»òÕßYD_OS_Rejected£©ËµÃ÷¸Ã±¨µ¥Ò»¶¨ÎÞÐ§
                    m_optionAbandonExecuteMap.erase(pOrder->LongOrderSysID);
                }
            }
        }
    }
    void listOptionExecute(void)
    {
        for (std::map<long long,YDOrder>::iterator it=m_optionExecuteMap.begin();it!=m_optionExecuteMap.end();it++)
        {
            showOptionExecute(&(it->second));
        }
    }
    void insertOptionExecute(void)
    {
        YDInputOrder inputOrder;
        // inputOrderÖÐµÄËùÓÐ²»ÓÃµÄ×Ö¶Î£¬Ó¦µ±Í³Ò»Çå0
        memset(&inputOrder,0,sizeof(inputOrder));
        inputOrder.YDOrderFlag=YD_YOF_OptionExecute;
        inputOrder.OrderType=YD_ODT_Limit;
        inputOrder.Direction=YD_D_Sell;
        // ¿ªÆ½±êÖ¾Ò²¿ÉÄÜÊÇÆäËûÆ½²ÖÀàµÄ±êÖ¾
        inputOrder.OffsetFlag=YD_OF_Close;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.Price=0;
        // ±¨µ¥ÊýÁ¿ÌîÐ´Êµ¼ÊÆÚÍûÖ´ÐÐµÄÆÚÈ¨ÊýÁ¿
        inputOrder.OrderVolume=1;
        inputOrder.OrderRef=++m_maxOrderRef;
        m_pApi->insertOrder(&inputOrder,m_pInstrument);
    }

    void putOrder(void)
    {
        YDInputOrder inputOrder;
        memset(&inputOrder, 0, sizeof(inputOrder));
        // 默认市价(FAK)、投机
        inputOrder.OrderType = YD_ODT_Market;
        inputOrder.HedgeFlag = YD_HF_Speculation;
        inputOrder.YDOrderFlag = YD_YOF_Normal;
        inputOrder.ConnectionSelectionType = YD_CS_Any;
        inputOrder.OrderRef = ++m_maxOrderRef;
        const YDInstrument *pInstrument = nullptr;
        m_pApi->insertOrder(&inputOrder,m_pInstrument);
        pInstrument = m_pApi->getInstrumentByID("fu2401");
        inputOrder.Direction = YD_D_Buy;
        inputOrder.OffsetFlag = YD_OF_Open;
        inputOrder.OrderVolume =1;
        if (m_pApi->insertOrder(&inputOrder, pInstrument))
        {
            printf("\t【报单发送成功】\n");
            printf("%d\n", inputOrder.OrderRef);
        }
        else
            printf("报单发送失败，错误码： %d\n", inputOrder.ErrorNo);
    }

    void cancelAllOptionExecute(void)
    {
        for (std::map<long long,YDOrder>::iterator it=m_optionExecuteMap.begin();it!=m_optionExecuteMap.end();it++)
        {
            YDCancelOrder cancelOrder;
            memset(&cancelOrder,0,sizeof(cancelOrder));
            cancelOrder.YDOrderFlag=it->second.YDOrderFlag;
            cancelOrder.LongOrderSysID=it->second.LongOrderSysID;
            m_pApi->cancelOrder(&cancelOrder,m_pInstrument->m_pExchange);
        }
    }
    void listOptionAbandonExecute(void)
    {
        for (std::map<long long,YDOrder>::iterator it=m_optionAbandonExecuteMap.begin();it!=m_optionAbandonExecuteMap.end();it++)
        {
            showOptionAbandonExecute(&(it->second));
        }
    }
    void insertOptionAbandonExecute(void)
    {
        YDInputOrder inputOrder;
        // inputOrderÖÐµÄËùÓÐ²»ÓÃµÄ×Ö¶Î£¬Ó¦µ±Í³Ò»Çå0
        memset(&inputOrder,0,sizeof(inputOrder));
        inputOrder.YDOrderFlag=YD_YOF_OptionAbandonExecute;
        inputOrder.OrderType=YD_ODT_Limit;
        inputOrder.Direction=YD_D_Sell;
        // ¿ªÆ½±êÖ¾Ò²¿ÉÄÜÊÇÆäËûÆ½²ÖÀàµÄ±êÖ¾
        inputOrder.OffsetFlag=YD_OF_Close;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.Price=0;
        // ±¨µ¥ÊýÁ¿ÌîÐ´Êµ¼ÊÆÚÍûÖ´ÐÐµÄÆÚÈ¨ÊýÁ¿
        inputOrder.OrderVolume=1;
        inputOrder.OrderRef=++m_maxOrderRef;
        m_pApi->insertOrder(&inputOrder,m_pInstrument);
    }
    void cancelAllOptionAbandonExecute(void)
    {
        for (std::map<long long,YDOrder>::iterator it=m_optionAbandonExecuteMap.begin();it!=m_optionAbandonExecuteMap.end();it++)
        {
            YDCancelOrder cancelOrder;
            memset(&cancelOrder,0,sizeof(cancelOrder));
            cancelOrder.YDOrderFlag=it->second.YDOrderFlag;
            cancelOrder.LongOrderSysID=it->second.LongOrderSysID;
            m_pApi->cancelOrder(&cancelOrder,m_pInstrument->m_pExchange);
        }
    }
    void insertRequestForQuote(void)
    {
        YDInputOrder inputOrder;
        // inputOrderÖÐµÄËùÓÐ²»ÓÃµÄ×Ö¶Î£¬Ó¦µ±Í³Ò»Çå0
        memset(&inputOrder,0,sizeof(inputOrder));
        inputOrder.YDOrderFlag=YD_YOF_RequestForQuote;
        inputOrder.OrderType=YD_ODT_Limit;
        inputOrder.Direction=YD_D_Buy;
        inputOrder.OffsetFlag=YD_OF_Open;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.Price=0;
        inputOrder.OrderVolume=0;
        inputOrder.OrderRef=++m_maxOrderRef;
        m_pApi->insertOrder(&inputOrder,m_pInstrument);
    }
};

void startExample5(const char *configFilename,const char *username,const char *password,const char *instrumentID)
{
    /// ËùÓÐYDApiµÄÆô¶¯¶¼ÓÉÏÂÁÐÈý²½¹¹³É

    // ´´½¨YDApi
    YDApi *pApi=makeYDApi(configFilename);
    if (pApi==NULL)
    {
        printf("can not create API\n");
        exit(1);
    }
    // ´´½¨ApiµÄ¼àÌýÆ÷
    int action=PutOrder;		// ¿ÉÒÔ¸ü»»ÎªÆäËûÏ£Íû½øÐÐµÄ²Ù×÷¡£×¢Òâ£¬²»ÊÇÃ¿¼Ò½»Ò×Ëù¶¼Ö§³ÖÕâÐ©ÒµÎñ
    YDExample5Listener *pListener=new YDExample5Listener(pApi,username,password,instrumentID,action);
    /// Æô¶¯Api
    if (!pApi->start(pListener))
    {
        printf("can not start API\n");
        exit(1);
    }
}
