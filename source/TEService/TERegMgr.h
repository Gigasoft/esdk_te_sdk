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
 * @file  TERegMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Handle TE Init/Uninit, Login/Logout 
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#ifndef _TE_REG_MGR_H_
#define _TE_REG_MGR_H_

#include "stdafx.h"
#include "SignalRecvProcess.h"

const int TE_D_BISAUTOLOGIN_VALUE = false;
const int TE_D_BISREMEMBERPSW_VALUE = false;

//×¢²á¹ÜÀí
class CTERegMgr:public ConferenceUiObserver, public uc::model::conversation::ConversationUiObserver, public uc::model::LdapUiObserver
{

public:
	static inline CTERegMgr& Instance()
	{
		static CTERegMgr inst;
		return inst;
	}
public:
	void Init(void);
	void Uninit(void);
	int SignIn(const TE_S_LOGIN_INFO *pLoginReqInfo);
	int SignOut(void);
	void LoadLangCode();
	const TE_S_CALL_STATE_INFO *GetCallStateInfo();
public:
	virtual bool OnConfNotification(void* _item);
	virtual bool OnConvNotification(void* _item);
	virtual bool OnLdapNotification(void* _item);
private:
	CTERegMgr(void);
	~CTERegMgr(void);
public:
	TE_S_LOGIN_RESULT m_LoginResult;
	UCClient* m_pUCClient;
	LdapSearchResultRevInEnterprise m_ldapSearchResultSlot;
	LdapSearchResultRevInEnterprise *GetLdapResult( )
	{
		return &m_ldapSearchResultSlot;
	}
	
private:
	UserStatusChangeSigRev statuschangeslot_;
	SCStatusNotifySigRev scsatusnotifyslot_;
	ConversationChangedSigRev conversationchangedslot_;
	AvSessionBFCPModifiedSigRev avSessionBFCPModifiedslot;
	ConfCreateStateChangeSigRev confCreateStateChangeslot_;
	ConfChairManApplyResultSigRev confChairManApplyResultslot_;
	ConfChairManReleaseSigRev m_confChairManReleaseSlot_;
	ConfCtrlNotifySigRev confCtrlNotifySigRev_;
	ConfAttendeeListRefreshSigRev m_confCtrlAttendeeListRefreshSlot;
	NetAddrDownloadedSigRecvInEnterprise m_netAddrDownloadSlot;
	
	uc::model::UCClient::NetAddressBookType m_netAddressBookType;
	LicenseStateProcessSigRev m_licenseStateSlot;
};

#endif