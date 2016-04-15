//#ifndef __CONVERSATION_JOINT_TUP_H__
//#define __CONVERSATION_JOINT_TUP_H__
#pragma  once

#ifdef WIN32
#include "PthreadMutex.h"
#else
#include "./../../src/hwuc/PthreadMutex.h"
#endif


namespace ecs
{
    namespace framework
    {
        struct MsgItem;
    }
}

namespace uc {
    namespace model {
        namespace conversation {


#define TE_SUCCESS  (0)
#define TE_ERROR    (-1)

typedef unsigned int Uint32;

//TUP回调消息结构参数
typedef struct TUP_MSG_NOTIFY_PARAM_tag  
{
    unsigned int ulTupMsgId;
    unsigned int ulParam1;
    unsigned int ulParam2; 
    void *pMsgBody;
    
    ~TUP_MSG_NOTIFY_PARAM_tag()
    {
        if (pMsgBody)
        {
            free(pMsgBody);
        }
    }
    
}TUP_MSG_NOTIFY_PARAM;


typedef void (*TupMsgProcFunc)(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

class APPCLASSLAYER_API ConversationMatch : ctk::noncopyable
{
public:
    ConversationMatch(uc::model::UCClient* client);
    ~ConversationMatch();
    
    bool TE_TupFrameInit();
    void TE_TupFrameUnInit();
    static void TE_TupMsgNotifyCB(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody);

	static bool MallocMemForBody( TUP_MSG_NOTIFY_PARAM * pstTupMsgNotifyParamTemp, int dataSize, void * pBody, Uint32 ulMsgId );
	static void ThreadFunc_For_Deal_Tup_Msg();
    static void InitTupMsgInfoBodySize();
    static int  GetMsgInfoBodySizeByMsgId(Uint32 msgId, Uint32 ulParam1, Uint32 ulParam2);
private:
    static void FindTupMsgProcFuncAndExecute(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

    inline void InitTupMsgProcFuncMap();

	static void DoTupMsgProcFuncDispense(unsigned int tupMsgId, ecs::framework::MsgItem& item);

	static void InitHMELog();

	void CleanTupMsgCBParamList();
    static void clientImplHandle(ecs::framework::MsgItem& item);
    static void contactManagerHandle(ecs::framework::MsgItem& item);
	static void ldapManagerHandle(ecs::framework::MsgItem& item);
    static void conferenceHandle(ecs::framework::MsgItem& item);
    static void conversationHandle(ecs::framework::MsgItem& item);
    
    static std::map<Uint32, TupMsgProcFunc> TupMsgProcFuncMap;
    static std::map<Uint32, int> TupMsgInfoBodySizeMap;
public:
    uc::model::UCClient* client_;
    static unsigned int s_callEndReason;
	static unsigned int s_previousAudioDirectionMode; // 前一个媒体码率方向 用于呼叫保持恢复 实际类型为CALL_E_MEDIA_SENDMODE
	static unsigned int s_previoudVideoDirectionMode; // 前一个视频媒体码流方向 用于硬终端对接 直接关闭摄像头发送sendonly问题 
	static unsigned int s_prepareReferCallID;

private:
    static TE_MUTEX_T s_TupThreadDealMutex;
    static bool s_bInitTupThreadFuncFlag;  // TUP上抛消息处理线程初始化标志
    TE_Pthread_T m_TupCbPthreadHandle;  //TUP上抛消息处理线程句柄
    static std::list<TUP_MSG_NOTIFY_PARAM *> s_lstTupMsgNotifyParam;
};
//license相关处理函数
void loginLicenseTypeResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void loginApplyLicenseResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void refreshLicenseResultFailedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void releaseLicenseResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

//呼叫消息处理函数
void sipRegisterResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void authorizeFailedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callIncommingMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callOutgoingMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callRingBackMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callConnectedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callEndedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callDestroyedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

// video
void callVideoAddedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callVideoClosedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callVideoModifyResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

// bfcp
void callDataEnableMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callDataStartSendingMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callDataStartReceivingMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callDataStoppedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);
void callDataStartFailureMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

// kickout
void kickedOutMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

// status subscribe notify
void statusChangedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

void callGetDataFrameSizeMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

void networkAddressBeginDownloadMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);

void callAudioNetQualityMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
void callVideoNetQualityMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);


void callVideoOrDataDecodeSucessMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);

void callPrepareReferMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody, ecs::framework::MsgItem& item);

void audioVideoDeviceChangedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);

void mediaSessionModifiedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);

void callHoldeResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
void callResumeResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
            
// confCreateResult
void confCreateResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
// enable bfcp conference ctrl
void confCtrlEnableMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
//conf ctrl connected
void confCtrlConnectedMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
// refresh all hall list
void confAttendeeListRefreshMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);
// refresh one hall
void confAttendeeRefreshMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);

// enter password to be chairman
void confEnterPasswordMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void *pBody,  ecs::framework::MsgItem& item);

// ConfApplyChairmanResult
void confApplyChairmanResultMI(Uint32 /*ulMsgId*/, Uint32 ulParam1, Uint32 /*ulParam2*/, void * pBody, ecs::framework::MsgItem& item);
            
//ConfReleaseChairmanResult
void confReleaseChairmanResultMI(Uint32 /*ulMsgId*/, Uint32 ulParam1, Uint32 /*ulParam2*/, void * pBody, ecs::framework::MsgItem& item);

void confReleaseChariManNotifyMI(Uint32 /*ulMsgId*/, Uint32 ulParam1, Uint32 /*ulParam2*/, void * pBody, ecs::framework::MsgItem& item);

void confctrlExtendResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
// change password
void changePasswordResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);

// password ADcertification
void passwordADCertificationResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);

//广播指示
void confBroadCastAttendeeIndMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//广播会场结果上抛
void confBroadCastResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//观看会场结果上抛
void confWatchResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//发言指示
void confFloorAttendeeIndMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//会议主席指示
void confChairManIndMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//会议剩余时间
void confTimeRemnantMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//会控添加会场结果上抛
void confAddHallResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//本地被广播状态变更通知
void confLocalBroadCastStatusChangeMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);
//取消广播结果
void confCancelBroadCastResultMI(Uint32 ulMsgId, Uint32 ulParam1, Uint32 ulParam2, void* pBody, ecs::framework::MsgItem& item);

		} //namespace conversation
    } //namespace model
} // uc


//#endif
