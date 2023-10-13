#include <map>
#include<ydExample.h>
#include <iostream>

const int ListOptionExecute=0;
const int InsertOptionExecute=1;
const int CancelAllOptionExecute=2;
const int ListOptionAbandonExecute=3;
const int InsertOptionAbandonExecute=4;
const int CancelAllOptionAbandonExecute=5;
const int RequestForQuote=6;
const int InsertOrder=7;

static const int s_orderGroupID=0;

class MyYDListener: public YDListener{
private:
    YDApi *m_pApi;
    const char *m_username,*m_password,*m_instrumentID;
    int m_maxOrderRef;
    int m_action;
    bool m_hasCaughtUp;

    const YDInstrument *m_pInstrument{};

    std::map<long long,YDOrder> m_optionExecuteMap;

    std::map<long long,YDOrder> m_optionAbandonExecuteMap;

public:
    MyYDListener(YDApi *pApi,const char *username,const char *password,const char *instrumentID,int action){
        m_pApi=pApi;
        m_username=username;
        m_password=password;
        m_instrumentID=instrumentID;
        m_maxOrderRef=0;
        m_action=action;
        m_hasCaughtUp=false;
    }

    virtual void notifyReadyForLogin(bool hasLoginFailed){
        if (!m_pApi->login(m_username,m_password,NULL,NULL))
        {
            printf("can not login\n");
            exit(1);
        }
        m_hasCaughtUp=false;
    }

    virtual void notifyLogin(int errorNo, int maxOrderRef, bool isMonitor){
        if (errorNo==0){
            m_maxOrderRef=maxOrderRef;
            printf("login successfully\n");
        }else{
            printf("login failed, errorNo=%d\n",errorNo);
            exit(1);
        }
    }

    virtual void notifyFinishInit(void){
        m_pInstrument=m_pApi->getInstrumentByID(m_instrumentID);
        if (m_pInstrument==NULL)
        {
            printf("can not find instrument %s\n",m_instrumentID);
            exit(1);
        }
    }

    virtual void notifyCaughtUp(void){
        m_hasCaughtUp=true;
        switch (m_action){
            case ListOptionExecute:
                listOptionExecute();
                break;
            case InsertOptionExecute:
                insertOptionExecute();
                break;
            case InsertOrder:
                insertOrder();
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

    void showFailedOptionExecute(const YDOrder *pFailedOrder){
        printf("OptionExecuteFailed:Volume=%d ErrorNo=%d\n",pFailedOrder->OrderVolume,pFailedOrder->ErrorNo);
    }
    void showOptionExecute(const YDOrder *pOrder){
        printf("OptionExecute:LongOrderSysID=%lld Volume=%d OrderStatus=%d\n",pOrder->LongOrderSysID,pOrder->OrderVolume,pOrder->OrderStatus);
    }
    void showFailedOptionAbandonExecute(const YDOrder *pFailedOrder){
        printf("OptionAbandonExecuteFailed:Volume=%d ErrorNo=%d\n",pFailedOrder->OrderVolume,pFailedOrder->ErrorNo);
    }
    void showOptionAbandonExecute(const YDOrder *pOrder){
        printf("OptionAbandonExecute:LongOrderSysID=%lld Volume=%d OrderStatus=%d\n",pOrder->LongOrderSysID,pOrder->OrderVolume,pOrder->OrderStatus);
    }

    virtual void notifyOrder(const YDOrder *pOrder,const YDInstrument *pInstrument,const YDAccount *pAccount){
        if (pInstrument!=m_pInstrument){
            return;
        }
        if (pOrder->ErrorNo == 0)
        {
            std::cout << "\tnotifyOrder::交易所接受报单/撤单" << std::endl;
            std::cout << "\tOrderRef: " << pOrder->OrderRef << "\tOrderLocalID: " << pOrder->OrderLocalID;
            std::cout << "\tOrderSysID: " << pOrder->OrderSysID;
            std::cout << "\t报单状态：";
            switch (pOrder->OrderStatus)
            {
                case YD_OS_Queuing:
                    std::cout << "交易所确认报单(部成或未成)";
                    break;
                case YD_OS_Canceled:
                    std::cout << "报单已被撤销";
                    break;
                case YD_OS_AllTraded:
                    std::cout << "全部成交";
                    break;
                default:
                    std::cout << "未知";
            }
            std::cout << "\t报单已成交量：" << pOrder->TradeVolume;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\tnotifyOrder::交易所拒绝报单";
            std::cout << "\tOrderRef: " << pOrder->OrderRef;
            std::cout << "\t错误码：" << pOrder->ErrorNo;
            std::cout << std::endl;
        }
    }

    void listOptionExecute(void){
        for (std::map<long long,YDOrder>::iterator it=m_optionExecuteMap.begin();it!=m_optionExecuteMap.end();it++){
            showOptionExecute(&(it->second));
        }
    }

    void insertOptionExecute(void){
        YDInputOrder inputOrder;
        memset(&inputOrder,0,sizeof(inputOrder));
        inputOrder.YDOrderFlag=YD_YOF_OptionExecute;
        inputOrder.OrderType=YD_ODT_Limit;
        inputOrder.Direction=YD_D_Sell;
        inputOrder.OffsetFlag=YD_OF_Close;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.Price=0;
        inputOrder.OrderVolume=1;
        inputOrder.OrderRef=++m_maxOrderRef;
        m_pApi->insertOrder(&inputOrder,m_pInstrument);
    }

    void insertOrder(void){
        YDInputOrder inputOrder;
        memset(&inputOrder,0,sizeof(inputOrder));
        inputOrder.OffsetFlag=YD_OF_Open;
//        inputOrder.Price=m_pInstrument->m_pMarketData->AskPrice;
        inputOrder.Direction=0;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.OrderVolume=1;
        inputOrder.OrderGroupID=s_orderGroupID;
        inputOrder.OrderRef=++m_maxOrderRef;
        inputOrder.GroupOrderRefControl=YD_GORF_Increase;
        inputOrder.OrderType=YD_ODT_Market; // 市场价格
        inputOrder.YDOrderFlag=YD_YOF_Normal;
        inputOrder.ConnectionSelectionType=YD_CS_Any;
        inputOrder.ConnectionID=0;
        if (m_pApi->insertOrder(&inputOrder,m_pInstrument)){
            std::cout << "\t insertOrder success" << std::endl;
        }
    }

    void cancelAllOptionExecute(void){
        for (std::map<long long,YDOrder>::iterator it=m_optionExecuteMap.begin();it!=m_optionExecuteMap.end();it++)
        {
            YDCancelOrder cancelOrder;
            memset(&cancelOrder,0,sizeof(cancelOrder));
            cancelOrder.YDOrderFlag=it->second.YDOrderFlag;
            cancelOrder.LongOrderSysID=it->second.LongOrderSysID;
            m_pApi->cancelOrder(&cancelOrder,m_pInstrument->m_pExchange);
        }
    }
    void listOptionAbandonExecute(void){
        for (std::map<long long,YDOrder>::iterator it=m_optionAbandonExecuteMap.begin();it!=m_optionAbandonExecuteMap.end();it++)
        {
            showOptionAbandonExecute(&(it->second));
        }
    }
    void insertOptionAbandonExecute(void){
        YDInputOrder inputOrder;
        memset(&inputOrder,0,sizeof(inputOrder));
        inputOrder.YDOrderFlag=YD_YOF_OptionAbandonExecute;
        inputOrder.OrderType=YD_ODT_Limit;
        inputOrder.Direction=YD_D_Sell;
        inputOrder.OffsetFlag=YD_OF_Close;
        inputOrder.HedgeFlag=YD_HF_Speculation;
        inputOrder.Price=0;
        inputOrder.OrderVolume=1;
        inputOrder.OrderRef=++m_maxOrderRef;
        m_pApi->insertOrder(&inputOrder,m_pInstrument);
    }

    void cancelAllOptionAbandonExecute(void){
        for (std::map<long long,YDOrder>::iterator it=m_optionAbandonExecuteMap.begin();it!=m_optionAbandonExecuteMap.end();it++)
        {
            YDCancelOrder cancelOrder;
            memset(&cancelOrder,0,sizeof(cancelOrder));
            cancelOrder.YDOrderFlag=it->second.YDOrderFlag;
            cancelOrder.LongOrderSysID=it->second.LongOrderSysID;
            m_pApi->cancelOrder(&cancelOrder,m_pInstrument->m_pExchange);
        }
    }

    void insertRequestForQuote(void){
        YDInputOrder inputOrder;
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

void startExample5(const char *configFilename,const char *username,const char *password,const char *instrumentID){
    YDApi *pApi=makeYDApi(configFilename);
    if (pApi==NULL)
    {
        printf("can not create API\n");
        exit(1);
    }
    int action=InsertOrder;

    MyYDListener *pListener=new MyYDListener(pApi,username,password,instrumentID,action);
    if (!pApi->start(pListener))
    {
        printf("can not start API\n");
        exit(1);
    }
}