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
 * @file  SignalRecvProcess.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Handle the signal of UCClient interface.
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#pragma once
#include <string>
#include "stdafx.h"
#include "hwuc/HWUC.h"


class CIMConversation;
typedef struct EventParam
{
	std::string src_;
	std::string target_;
	std::string convId_;
	std::string xmlbody_;
}EventParam;


//登录、状态、IM、呼叫、固定群等信号的通知
class SignalRecvProcess: public has_slots<sigslot::te_multi_thread_mutex>
{
public:
	//Sign In Signal
	void OnClientSignInNotify(UCClient::SignInState _state, std::string _reason);

};

// client state changed notify
class UserStatusChangeSigRev : public has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnStatusChanged(uc::model::ContactAvailability _state, std::string _desc, Contact& _contact);

};

class SCStatusNotifySigRev : public has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnStatusNotify(string id);
	 int status ;
};

//handle conversation signal
class ConversationChangedSigRev: public has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnAVSessAdded(conversation::Conversation* _con, conversation::sAudioVideoParam _param);
	void AVSessionRinged(conversation::Conversation* _con);
	void AVSessionClosed(conversation::Conversation* _con, std::string _avid, std::string _reason);
	void AVSessionConnected(conversation::Conversation* _con, int sessiontype_);
	TE_UINT32 GetCallID(conversation::Conversation* _con);
	TE_S_CALL_STATE_INFO CallStateInfo;
};


class AvSessionBFCPModifiedSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnAvSessionBFCPModifiedSigRes(std::string _convid, int _sessionType, bool _bDataReady);

	TE_UINT32 GetCallID(conversation::Conversation* _con);
private:
	TE_S_CALL_STATE_INFO CallStateInfo;
};


class ConfCreateStateChangeSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnConfCreateStateChangeSigRes(std::string _reason, int _result);

	TE_S_CONF_RESULT restInfo;
	//CWnd *m_wnd;
};


class ConfChairManApplyResultSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnConfChairManApplyResultSigRes(int _result);

	TE_S_CONF_RESULT restInfo;
	//CWnd *m_wnd;
};


class ConfChairManReleaseSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnConfChairManReleaseResultSigRes(bool _result);

	TE_S_CONF_RESULT restInfo;
	//CWnd *m_wnd;
};


class ConfCtrlNotifySigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	//void OnConfCtrlFLoorAttendeeInd(uc::model::Hall _hall);

	void OnAddHallResult(short failedCount, bool result);

	void OnConfCtrlBroadCastResult(int result);

	void OnConfCtrlWatchResult(int result);

	void OnConfCtrlTimeRemnant(short time);

	void OnConfExtendResult(bool _result);


	TE_S_CONF_RESULT restInfo;
	//CWnd *m_wnd;
};


class ConfAttendeeListRefreshSigRev: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	//与会者列表刷新上抛
	void OnConfAttendeeListRefreshSigRes(std::vector<uc::model::Hall> _vecConfHalls);
	//广播会场指示上抛
	void OnConfCtrlBroadCastInd(short M, short T);
	//会议主席指示上抛
	void OnConfCtrlChairManInd(bool isChairMan);

	TE_S_CONF_RESULT restInfo;
	//CWnd *m_wnd;
};

class NetAddrDownloadedSigRecvInEnterprise :  public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnNetAddrDownloaded();

	TE_S_ENTERPRISE_RESULT restInfo;

	//CWnd* m_wnd;
};

class LdapSearchResultRevInEnterprise: public sigslot::has_slots<sigslot::te_multi_thread_mutex>
{
public:
	void OnLdapSearchResultRev(uc::model::LDAP_D_Search_Result* result);

	TE_S_ENTERPRISE_RESULT restInfo;

	//CWnd* m_pWnd;
};


//登录、状态、IM、呼叫、固定群等信号的通知
class LicenseStateProcessSigRev: public has_slots<sigslot::te_multi_thread_mutex>
{
public:
	//Sign In Signal
	void OnClientLicenseStateNotify(UCClient::LicenseState _state, std::string _reason);

};
