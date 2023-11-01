#include "ydExample.h"

// ±¾Ê¾ÀýÕ¹ÏÖÁËÈçºÎÊ¹ÓÃ±¨µ¥×éµÄ¸ÅÄî
// ±¨µ¥×éÓÐ¶àÖÖÓÃÍ¾
// 1) ¶ÔÓÚÒ»¸ö±¨µ¥×éµÄ±¨µ¥µÄOrderRef½øÐÐÑÏ¸ñµÄ¹ÜÀí£¬È·±£OrderRefµÄµÝÔöÐÔºÍÎ¨Ò»ÐÔ£¬ÒÔ±ãÓ¦¶ÔÔÚUDP±¨µ¥Ê±¿ÉÄÜ³öÏÖµÄ¶ªµ¥»òÕßÖØ¸´·¢ËÍµÄÎÊÌâ
// 2) ¶ÔÓÚ±¨µ¥×éÄÚµÄ±¨µ¥£¬¿ÉÒÔÊ¹ÓÃOrderRef³·µ¥£¬²»ÐèÒªOrderSysID£¬Ò²¾ÍÊÇ¿ÉÒÔÔÚÊÕµ½±¨µ¥»Ø±¨Ç°³·µ¥
// 3) ¸÷¸ö±¨µ¥×éµÄOrderRef¶¼¶À×Ô¹ÜÀí£¬µ±Ò»¸öÕËºÅÐèÒª¶à¸ö³ÌÐòÍ¬Ê±µÇÂ¼ºÍ½»Ò×Ê±£¬¿ÉÒÔ»¥²»Ó°Ïì

// ÒªÊ¹ÓÃ±¨µ¥×é£¬ÐèÒªÓÐÒ»¸ö±¨µ¥×éºÅ¡£Ä¿Ç°Ò×´ïÖ§³ÖµÄ±¨µ¥×éºÅµÄ·¶Î§ÊÇ[1,63]¡£Èç¹û±¨µ¥×éºÅÎª0£¬±íÊ¾²»Ê¹ÓÃ±¨µ¥×é£¬OrderRef¾ÍÃ»ÓÐ±ØÒªµÝÔöºÍÎ¨Ò»ÁË£¬Ò²²»¿ÉÒÔÓÃOrderRef³·µ¥
// Çë²»ÒªÊ¹ÓÃÆäËû±¨µ¥×éºÅ£¬Æä½á¹ûÊÇ²»È·¶¨µÄ
static const int s_orderGroupID=5;

class YDExample9Listener: public YDListener
{
private:
    YDApi *m_pApi;
    const char *m_username,*m_password,*m_instrumentID;
    int m_maxPosition;
    int m_maxOrderRef;

    // Ö¸ÏòÏ£Íû½»Ò×µÄÆ·ÖÖ
    const YDInstrument *m_pInstrument;

    // Ö¸ÏòÏ£Íû½»Ò×µÄÆ·ÖÖµÄÕË»§Æ·ÖÖÐÅÏ¢
    const YDAccountInstrumentInfo *m_pAccountInstrumentInfo;

    // ËµÃ÷µ±Ç°ÊÇ·ñÓÐ¹Òµ¥
    bool m_hasOrder;
public:
    YDExample9Listener(YDApi *pApi,const char *username,const char *password,const char *instrumentID,int maxPosition)
    {
        m_pApi=pApi;
        m_username=username;
        m_password=password;
        m_instrumentID=instrumentID;
        m_maxPosition=maxPosition;
        m_maxOrderRef=0;
        m_hasOrder=false;
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
    }
    virtual void notifyLogin(int errorNo,int maxOrderRef,bool isMonitor)
    {
        // Ã¿´ÎµÇÂ¼ÏìÓ¦£¬¶¼»á»ñµÃ´ËÏûÏ¢£¬ÓÃ»§Ó¦µ±¸ù¾ÝerrorNoÀ´ÅÐ¶ÏÊÇ·ñµÇÂ¼³É¹¦
        if (errorNo==0)
        {
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
    virtual void notifyGroupMaxOrderRef(const int groupMaxOrderRef[])
    {
        // Ã¿´ÎµÇÂ¼³É¹¦ºó£¬¶¼»á»Øµ÷´Ë·½·¨£¬Ó¦µ±¼ÇÂ¼µ±Ç°µÄÒªÊ¹ÓÃµÄ±¨µ¥×éµÄ×î´ó±¨µ¥ÒýÓÃ£¬ÔÚ±¨µ¥Ê±ÓÃ¸ü´óµÄÊý×÷Îª±¨µ¥ÒýÓÃ£¬ÒÔ±ã³ÌÐòÍ¨¹ý±¨µ¥ÒýÓÃÀ´Ê¶±ð±¨µ¥
        m_maxOrderRef=groupMaxOrderRef[s_orderGroupID];
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
        m_pAccountInstrumentInfo=m_pApi->getAccountInstrumentInfo(m_pInstrument);
        // ÏÂÃæÕâ¸öÑ­»·Õ¹Ê¾ÁËÈçºÎ¸ù¾ÝÀúÊ·³Ö²ÖÐÅÏ¢£¬¼ÆËã¸ÃÆ·ÖÖµÄµ±Ç°³Ö²Ö¡£Èç¹ûÓÃ»§·ç¿ØºöÂÔÀúÊ·³Ö²Ö£¬¿ÉÒÔ²»Ê¹ÓÃ
        for (int i=0;i<m_pApi->getPrePositionCount();i++)
        {
            const YDPrePosition *pPrePosition=m_pApi->getPrePosition(i);
            if (pPrePosition->m_pInstrument==m_pInstrument)
            {
                if (pPrePosition->PositionDirection==YD_PD_Long)
                {
                    // ËùÓÐ¸÷¸ö½á¹¹ÖÐµÄUserInt1£¬UserInt2£¬UserFloat£¬pUser¶¼ÊÇ¹©ÓÃ»§×ÔÓÉÊ¹ÓÃµÄ£¬Æä³õÖµ¶¼ÊÇ0
                    // ÔÚ±¾Àý×ÓÖÐ£¬ÎÒÃÇÊ¹ÓÃÕË»§ºÏÔ¼ÐÅÏ¢ÖÐµÄUserInt1±£´æµ±Ç°µÄ³Ö²ÖÐÅÏ¢
                    m_pAccountInstrumentInfo->UserInt1+=pPrePosition->PrePosition;
                }
                else
                {
                    m_pAccountInstrumentInfo->UserInt1-=pPrePosition->PrePosition;
                }
            }
        }
        printf("Position=%d\n",m_pAccountInstrumentInfo->UserInt1);
        m_pApi->subscribe(m_pInstrument);
    }
    virtual void notifyMarketData(const YDMarketData *pMarketData)
    {
        if (m_pInstrument->m_pMarketData!=pMarketData)
        {
            // ÓÉÓÚ¸÷¸öÆ·ÖÖµÄpMarketDataµÄµØÖ·ÊÇ¹Ì¶¨µÄ£¬ËùÒÔ¿ÉÒÔÓÃ´Ë·½·¨ºöÂÔ·Ç±¾Æ·ÖÖµÄÐÐÇé
            return;
        }
        printf("notifyMarketData-------------------------\n");
        printf("pMarketData->AskVolume=%d\n", pMarketData->AskVolume);
        printf("pMarketData->BidVolume=%d\n", pMarketData->BidVolume);
        if ((pMarketData->AskVolume==0)||(pMarketData->BidVolume==0))
        {
            // ºöÂÔÍ£°åÐÐÇé
            return;
        }
        if (pMarketData->BidVolume-pMarketData->AskVolume>100)
        {
            // ¸ù¾Ý²ßÂÔÌõ¼þ£¬ÐèÒªÂòÈë
            tryTrade(YD_D_Buy);
        }
        else if (pMarketData->AskVolume-pMarketData->BidVolume>100)
        {
            // ¸ù¾Ý²ßÂÔÌõ¼þ£¬ÐèÒªÂô³ö
            tryTrade(YD_D_Sell);
        }
    }
    void tryTrade(int direction)
    {
        if (m_hasOrder)
        {
            // Èç¹ûÓÐ¹Òµ¥£¬¾Í²»×öÁË
            return;
        }
        YDInputOrder inputOrder;
        // inputOrderÖÐµÄËùÓÐ²»ÓÃµÄ×Ö¶Î£¬Ó¦µ±Í³Ò»Çå0
        memset(&inputOrder,0,sizeof(inputOrder));
        if (direction==YD_D_Buy)
        {
            if (m_pAccountInstrumentInfo->UserInt1>=m_maxPosition)
            {
                // ¿ØÖÆÊÇ·ñ´ïµ½ÁËÏÞ²Ö
                return;
            }
            if (m_pAccountInstrumentInfo->UserInt1>=0)
            {
                // ¿ØÖÆ¿ªÆ½²Ö£¬Õâ¸öÀý×ÓÖÐÃ»ÓÐ´¦ÀíSHFEºÍINEµÄÇø·Ö½ñ×ò²ÖµÄÇé¿ö
                inputOrder.OffsetFlag=YD_OF_Open;
            }
            else
            {
                inputOrder.OffsetFlag=YD_OF_Close;
            }
            // ÓÉÓÚ±¾Àý×ÓÊ¹ÓÃµÄ²»ÊÇÊÐ¼Ûµ¥£¬ËùÒÔÐèÒªÖ¸¶¨¼Û¸ñ
            inputOrder.Price=m_pInstrument->m_pMarketData->AskPrice;
        }
        else
        {
            if (m_pAccountInstrumentInfo->UserInt1<=-m_maxPosition)
            {
                return;
            }
            if (m_pAccountInstrumentInfo->UserInt1<=0)
            {
                inputOrder.OffsetFlag=YD_OF_Open;
            }
            else
            {
                inputOrder.OffsetFlag=YD_OF_Close;
            }
            inputOrder.Price=m_pInstrument->m_pMarketData->BidPrice;
        }
        inputOrder.Direction=direction;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.OrderVolume=1;

        // Ê¹ÓÃ±¾±¨µ¥×éµÄÏÂÒ»¸ö±¨µ¥ÒýÓÃ
        inputOrder.OrderGroupID=s_orderGroupID;
        inputOrder.OrderRef=++m_maxOrderRef;
        // Èç¹ûGroupOrderRefControlÊÇYD_GORF_Increase£¬±íÊ¾Ï£ÍûydServer¼ì²éOrderRefµÄµÝÔöÐÔ
        // Èç¹ûGroupOrderRefControlÊÇYD_GORF_IncreaseOne£¬±íÊ¾Ï£ÍûydServer¼ì²éOrderRef±ØÐèÊÇÇ°Ò»¸ö¼ÓÒ»
        // ÕâÁ½ÖÖ·½Ê½¶¼¿ÉÒÔ·ÀÖ¹UDPÖØ¸´£¬Çø±ðÊÇÈçºÎÓ¦¶ÔUDP¶ªµ¥£º
        //    YD_GORF_Increase±íÊ¾Ï£ÍûydServer¾¡Á¦´¦ÀíºóÃæµÄ±¨µ¥
        //    YD_GORF_IncreaseOne±íÊ¾Ï£ÍûydServerÍ£Ö¹´¦Àí±¾±¨µ¥×éµÄ±¨µ¥£¬´ýÈË¹¤´¦ÀíºóÔÙ¼ÌÐø
        inputOrder.GroupOrderRefControl=YD_GORF_Increase;

        // Õâ¸öÀý×ÓÊ¹ÓÃÏÞ¼Ûµ¥
        inputOrder.OrderType=YD_ODT_Limit;
        // ËµÃ÷ÊÇÆÕÍ¨±¨µ¥
        inputOrder.YDOrderFlag=YD_YOF_Normal;
        // ËµÃ÷ÈçºÎÑ¡ÔñÁ¬½Ó
        inputOrder.ConnectionSelectionType=YD_CS_Any;
        // Èç¹ûConnectionSelectionType²»ÊÇYD_CS_Any£¬ÐèÒªÖ¸¶¨ConnectionID£¬·¶Î§ÊÇ0µ½¶ÔÓ¦µÄYDExchangeÖÐµÄConnectionCount-1
        inputOrder.ConnectionID=0;
        // inputOrderÖÐµÄRealConnectionIDºÍErrorNoÊÇÔÚ·µ»ØÊ±ÓÉ·þÎñÆ÷ÌîÐ´µÄ
        if (m_pApi->insertOrder(&inputOrder,m_pInstrument))
        {
            m_hasOrder=true;

            // ÔÚÊ¹ÓÃ±¨µ¥×éÊ±£¬¿ÉÒÔ²»µÈ±¨µ¥»Ø±¨£¬Ö±½Ó³·µ¥¡£²»¹ýÈç¹û´ËÊ±ydServer»¹Ã»ÓÐÊÕµ½½»Ò×ËùµÄ±¨µ¥»Ø±¨£¬ÄÜ¹»³·µ¥È¡¾öÓÚ½»Ò×ËùÊÇ·ñÖ§³ÖÊ¹ÓÃ±¾µØºÅ³·µ¥
            YDCancelOrder cancelOrder;
            memset(&cancelOrder,0,sizeof(cancelOrder));
            cancelOrder.OrderGroupID=s_orderGroupID;
            cancelOrder.OrderRef=inputOrder.OrderRef;
            m_pApi->cancelOrder(&cancelOrder,m_pInstrument->m_pExchange);
        }
    }
    virtual void notifyOrder(const YDOrder *pOrder,const YDInstrument *pInstrument,const YDAccount *pAccount)
    {
        if ((pOrder->OrderGroupID==s_orderGroupID) && (pOrder->OrderStatus!=YD_OS_Queuing))
        {
            m_hasOrder=false;
        }
    }
    virtual void notifyTrade(const YDTrade *pTrade,const YDInstrument *pInstrument,const YDAccount *pAccount)
    {
        if (pTrade->OrderGroupID!=s_orderGroupID)
        {
            return;
        }
        if (pTrade->Direction==YD_D_Buy)
        {
            // ¸ù¾Ý³É½»£¬µ÷Õû³Ö²Ö
            m_pAccountInstrumentInfo->UserInt1+=pTrade->Volume;
        }
        else
        {
            m_pAccountInstrumentInfo->UserInt1-=pTrade->Volume;
        }
        printf("%s %s %d at %g\n",(pTrade->Direction==YD_D_Buy?"buy":"sell"),(pTrade->OffsetFlag==YD_OF_Open?"open":"close"),pTrade->Volume,pTrade->Price);
        printf("Position=%d\n",m_pAccountInstrumentInfo->UserInt1);
    }
};

void startExample9(const char *configFilename,const char *username,const char *password,const char *instrumentID)
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
    YDExample9Listener *pListener=new YDExample9Listener(pApi,username,password,instrumentID,3);
    /// Æô¶¯Api
    if (!pApi->start(pListener))
    {
        printf("can not start API\n");
        exit(1);
    }
}
