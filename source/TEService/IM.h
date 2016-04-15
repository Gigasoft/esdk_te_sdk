/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0


Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/
/****************************************************   
 * @file  IM.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Handle Callout include video and audio.
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#pragma  once

#include "stdafx.h"

typedef struct CallParam
{
	std::vector<uc::model::Contact> memlist;
//	std::vector<uc::model::Hall> confHalllist;
	std::string fixgrpId;
	std::string convId;
	std::string history_convId;
	bool videocall;
	int callType;
}CallParam;

// 对外接口返回码
enum EM_TECheckCallParamCode
{
	TE_CheckCallParam_Success				=	0,			//Success
	TE_CheckCallParam_FAIL_CallSelf			=	1,			//Call Self
	TE_CheckCallParam_FAIL_NulNum			=	2,			//Null Number
	TE_CheckCallParam_FAIL_HasNewSession	=	3,			//Coming Call
	TE_CheckCallParam_FAIL_HasTwoSession	=	4,			//Call mutil channel
	TE_CheckCallParam_FAIL_Offline			=	5			//Status Offline
};

class PhoneEventHandler
{
public:
	static bool callout_handle(CallParam* _param);
	static bool hangup_handle(TE_UINT32 callId);
	static bool answervediocall_handle(TE_UINT32 callId, TE_BOOL isAudioAccept);
	static bool answeraudiocall_handle(TE_UINT32 callId);
	static bool rejectcall_handle(TE_UINT32 callId);
	static int CheckCallParam(CallParam *_param);
	static bool HasCalloutPermission(CallParam* _param);
};

class ShareEventHandler
{
public:
	static bool requestsend_handle(TE_UINT32 callId);
	static bool stopsend_handle(TE_UINT32 callId);
	static bool startrecvdata_handle(TE_UINT32 callId);
	static bool stoprecvdata_handle(TE_UINT32 callId);
	static bool rejectrecvdata_handle(TE_UINT32 callId);
};


class CIMConversation;

//handle video channel state change signal
class VideoChnStateChgSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnChannelStateChanged(uc::model::conversation::avchannel::ChannelState _state, 
		uc::model::conversation::Session* _pSess);

	CIMConversation* m_IMConv;
	TE_S_CALL_STATE_INFO CallStateInfo;
};



class DataChnStateChgSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnDataChannelEvent(uc::model::conversation::avchannel::DataChannelEvent _state, uc::model::conversation::Session* _pSess,int iRspCode);

	TE_UINT32 GetCallID(conversation::Conversation* _con);
	CIMConversation* m_IMConv;
	TE_S_CALL_STATE_INFO CallStateInfo;
};


//被保持和恢复
class AvSessionBeHoldSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnAvSessionBeHoldSigRes(uc::model::conversation::AVSession * pAVSession);
	void OnAvSessionResumeSigRes(uc::model::conversation::AVSession* pAVSession);

	CIMConversation* m_IMConv;
	TE_S_CALL_STATE_INFO CallStateInfo;
};



class CIMConversation
{
public:
	static inline CIMConversation& Instance()
	{
		static CIMConversation inst;
		return inst;
	}
public:
	CIMConversation();
	~CIMConversation();
	//void CreateConverSession(CallParam *_param);
	bool CallOut(bool bVideoCall, int iCallType = conversation::SessionConnUri);
	void AcceptAudioCall();
	void AcceptVideoCall(bool isAudioAccet= false );
	void AcceptVideoOffer();
	bool VideoCallOut();
	bool AudioCallOut(int iCallType);
	void GetP2PContact(uc::model::Contact& _contact)const;
	void OnCallConnect(int sessiontype);
	long long InsertCallHistory(std::string _imConvID, std::string src, std::string srcname, BOOL bIsSend, BOOL bIsVideoCall);
	std::string InsertSigleConvHistory(std::string& strCurrentImDlgUri);
	std::string CreateIMHistoryConv(const std::string& _imConvID, const std::string& _hisConvId);
	bool IsIMConvExist(std::string _imConvID);
	void AddHistoryConv(const std::string& _imConvID, const std::string& _historyConvID);
	typedef std::map<std::string, std::string> _HISTOTY_CONV_MAP;
	_HISTOTY_CONV_MAP m_IMHistoryManageMap;
	std::string GetHistoryConvID(std::string _imConvID);
	static void CreateConvHistory(CallParam* _param, CIMConversation* convHistory);
	void UpdateIMDlgSingleChat();
	void UpdateDlg();
	long long m_CallRcdID;

	//数字转化为字符串，第二个参数指定进制（默认十进制）
	//使用时可以不指定模板参数类型；转换失败抛出runtime_error异常
	template<class T> inline static std::string num2str(
		const T & num, std::ios_base &(*f)(std::ios_base&) = std::dec)
	{
		std::ostringstream oss; 
		if ((oss << f << num).fail())
		{
			//throw std::runtime_error("invalid conversion : num = " + num);
		}
		return oss.str();
	}
	//whether this menu can be enabled
	//virtual bool isEnabled();
	

	void AcceptIncomingAudioCall(conversation::AVSession* pSess);
	void AcceptIncomingVideoCall(conversation::AVSession* pSess, bool isAudioAccept=false);
	void HangUpCall();
	bool AudioToVideoCall(bool bVideoCall);
	void InitVideoParam(bool b_needUpdata=false, bool b_AudioAccept=false);
	void RejectCall();


	bool StartSendData();
	bool StopSendData();
	bool StartRecvData();
	bool StopRecvData();
	bool RejectRecvData();

	void SetConvId(const std::string& _convId)
	{
		m_convID = _convId;
	}
	void SetHisConvId(const std::string& _convId)
	{
		m_hisConvID = _convId;
	}
	std::string GetConvId()const
	{
		return m_convID;
	}
	std::string GetHisConvId()const
	{
		return m_hisConvID;
	}
	//void CreateConverSession(const std::vector<uc::model::Contact>& _list, const std::string& _fixgrpId);
	std::string m_convID;   //Conversion ID
	std::string m_hisConvID;   //Conversion ID
	CString m_strSubject;	//Chat Subject
	bool m_bHasAccepted;
	bool m_bAcceptedOwer;
	bool m_bIsDataReceiving;

	//HWND m_hwndLocal;
	//HWND m_hwndRemote;
	//HWND m_hwndData;

	HWND m_hwndShared;
private:
	
	VideoChnStateChgSigRev   m_VChanlStateChgSlot;

	DataChnStateChgSigRev    m_DataChannelChgSlot;

	//被保持
	AvSessionBeHoldSigRev avSessionBeHoldslot_;
	AvSessionBeHoldSigRev avSessionResumeslot_;
   // bool CheckCallParam(CreateDlgParam dlgparam);
   // bool HasCalloutPermission(CallParam* _param);
	

};

