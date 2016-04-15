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
 * @file  TERegMgr.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Handle TE Init/Uninit, Login/Logout 
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#include "stdafx.h"
#include "SignalRecvProcess.h"
#include "TERegMgr.h"
#include "EventMgr.h"
#include "eSDKTool.h"
#include "Log.h"
#include "aes128_cbc_base64_gly.h"
#include "LangResManager.h"
#include <afx.h>
#include "TESDK.h"

CTERegMgr::CTERegMgr(void):m_pUCClient(uc::model::UCClient::GetClient())
{
	m_netAddressBookType = UCClient::NetAddressBook_Invalid;
}

CTERegMgr::~CTERegMgr(void)
{
	//Uninit();
	m_pUCClient = NULL;
}

void CTERegMgr::Init(void)
{
	DEBUG_TRACE("");
	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return;
		}
	}

	m_pUCClient->Init();
	m_pUCClient->SysConfig.Initilize();
	//login
	m_pUCClient->SignInNotify_.connect(&CEventMgr::Instance().m_Signalslot, &SignalRecvProcess::OnClientSignInNotify);
	//status changed
	//m_pUCClient->ContactSubManager->UserAvailabilityChanged_.connect(&statuschangeslot_, &UserStatusChangeSigRev::OnStatusChanged);
	m_pUCClient->ContactSubManager->SCStatusNotify_.connect(&scsatusnotifyslot_, &SCStatusNotifySigRev::OnStatusNotify);
	//Init Call and Hang up signal
	m_pUCClient->ConvManager->AVSessAdded.connect(&conversationchangedslot_, &ConversationChangedSigRev::OnAVSessAdded);
	m_pUCClient->ConvManager->AVSessionRinged.connect(&conversationchangedslot_, &ConversationChangedSigRev::AVSessionRinged);
	m_pUCClient->ConvManager->AVSessionClosed.connect(&conversationchangedslot_, &ConversationChangedSigRev::AVSessionClosed);
	m_pUCClient->ConvManager->AVSessionConnected.connect(&conversationchangedslot_, &ConversationChangedSigRev::AVSessionConnected);
	
	m_pUCClient->ConvManager->AVSessionBFCPModified.connect(&avSessionBFCPModifiedslot,&AvSessionBFCPModifiedSigRev::OnAvSessionBFCPModifiedSigRes);

	m_pUCClient->ConfManager->ConfCreateStateSignal.connect(&confCreateStateChangeslot_, &ConfCreateStateChangeSigRev::OnConfCreateStateChangeSigRes);
	
	m_pUCClient->ConfManager->ApplyChairmanSignal.connect(&confChairManApplyResultslot_,&ConfChairManApplyResultSigRev::OnConfChairManApplyResultSigRes);
	m_pUCClient->ConfManager->ReleaseChairmanSignal.connect(&m_confChairManReleaseSlot_, &ConfChairManReleaseSigRev::OnConfChairManReleaseResultSigRes);


	m_pUCClient->ConfManager->ConfAddHallResultSignal.connect(&confCtrlNotifySigRev_, &ConfCtrlNotifySigRev::OnAddHallResult);
	m_pUCClient->ConfManager->ConfBroadCastResultSignal.connect(&confCtrlNotifySigRev_, &ConfCtrlNotifySigRev::OnConfCtrlBroadCastResult);
	m_pUCClient->ConfManager->ConfWatchResultSignal.connect(&confCtrlNotifySigRev_, &ConfCtrlNotifySigRev::OnConfCtrlWatchResult);
	m_pUCClient->ConfManager->ConfCtrlTimeRemnantSignal.connect(&confCtrlNotifySigRev_, &ConfCtrlNotifySigRev::OnConfCtrlTimeRemnant);
	m_pUCClient->ConfManager->ExtendTimeSignal.connect(&confCtrlNotifySigRev_, &ConfCtrlNotifySigRev::OnConfExtendResult);

	m_pUCClient->ConfManager->ConfCtrlAttendeeListRefreshSignal.connect(&m_confCtrlAttendeeListRefreshSlot,&ConfAttendeeListRefreshSigRev::OnConfAttendeeListRefreshSigRes);
	m_pUCClient->ConfManager->ConfBroadCastIndSignal.connect(&m_confCtrlAttendeeListRefreshSlot,&ConfAttendeeListRefreshSigRev::OnConfCtrlBroadCastInd);
	m_pUCClient->ConfManager->ConfChairmanIndSignal.connect(&m_confCtrlAttendeeListRefreshSlot,&ConfAttendeeListRefreshSigRev::OnConfCtrlChairManInd);

	m_pUCClient->ContactManager->NetAddressBookDownloadedNotify_.connect(&m_netAddrDownloadSlot,&NetAddrDownloadedSigRecvInEnterprise::OnNetAddrDownloaded);

	m_pUCClient->LdapManager->ldapSearchResultSignal.connect(&m_ldapSearchResultSlot,&LdapSearchResultRevInEnterprise::OnLdapSearchResultRev);
	
	m_pUCClient->LicenseStateNotify_.connect(&m_licenseStateSlot, &LicenseStateProcessSigRev::OnClientLicenseStateNotify);
	//Init observer
	m_pUCClient->ConvManager->observer = (ConversationUiObserver *)this;
	m_pUCClient->ConfManager->observer = (ConferenceUiObserver *)this;
    m_pUCClient->LdapManager->observer=(LdapUiObserver*)this;

	LoadLangCode();
	
}


void CTERegMgr::LoadLangCode()
{
	DEBUG_TRACE("");
// ¼ÓÔØÓïÑÔÎÄ¼þ
	std::wstring langCode = LANGRESMGR()->ReadLangCode();
	//INFO_PARAM1(langCode);
	if (langCode.empty())
	{
		LANGID langid = GetSystemDefaultLangID();
		
		wostringstream oss;
		oss << langid;

		langCode = oss.str();
		//INFO_PARAM1(langCode);
		/*1033 Ó¢ÎÄ
		1036 ·¨Óï
		1046 ÆÏÌÑÑÀÓï£¨°ÍÎ÷£©
		2052 ÖÐÎÄ¼òÌå
		2070 ÆÏÌÑÑÀÓï
		3082 Î÷°àÑÀÓï
		1028 ÖÐÎÄ·±Ìå
		1049 ¶íÓï
		*/
		if(!langCode.empty()
			&&(langCode.compare(L"1033") 
			|| langCode.compare(L"1036")
			|| langCode.compare(L"1046")
			|| langCode.compare(L"2052")
			|| langCode.compare(L"2070")
			|| langCode.compare(L"3082")
			|| langCode.compare(L"1028")
			|| langCode.compare(L"1049")
			))
		{
			LANGRESMGR()->WriteLangCode(langCode);
		}
		else
		{
			langCode = L"1033"; // Ä¬ÈÏÓ¢ÎÄ
			LANGRESMGR()->WriteLangCode(langCode);
		}
	}
	else
	{
		
	}
	LANGRESMGR()->SetLangCode(langCode);
	LANGRESMGR()->ReloadLangRes();
}




void CTERegMgr::Uninit(void)
{	
	DEBUG_TRACE("");
	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return;
		}
	}

	
	
//		m_pUCClient->ContactSubManager->UserAvailabilityChanged_.disconnect_all();
//		m_pUCClient->ContactSubManager->SCStatusNotify_.disconnect_all();
		//UCClient* clients = UCClient::GetClient();
	m_pUCClient->DeviceManager->Uninit();
	m_pUCClient->SignInNotify_.disconnect_all();
	m_pUCClient->LicenseStateNotify_.disconnect_all();
	m_pUCClient->ConvManager->AVSessAdded.disconnect_all();
	m_pUCClient->ConvManager->AVSessionRinged.disconnect_all();
	m_pUCClient->ConvManager->AVSessionClosed.disconnect_all();
	m_pUCClient->ConvManager->AVSessionConnected.disconnect_all();
	m_pUCClient->ConvManager->DisconObserver();
	m_pUCClient->ConfManager->DisconObserver();
	m_pUCClient->UnInit();

	
}

int CTERegMgr::SignIn(const TE_S_LOGIN_INFO *pLoginReqInfo)
{
	DEBUG_TRACE("");
	bool ret;
	CString ll;
	CString InternalUrl;
	CString account,pwd;
	wstring wstrPassword;
	std::string strInternalUrl = "";
	std::string strDestIp  = "";
	std::string strLocalIP = "";

	if (NULL == pLoginReqInfo)
	{
		return TE_SDK_InvalidPara;
	}
	
	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return TE_SDK_Failed;
		}
	}
		
	ll = _T("2052");
	
	InternalUrl.Format(_T("%s:%d"),eSDKTool::utf8_2_unicode(pLoginReqInfo->stIP).GetBuffer(),pLoginReqInfo->uiPort);
	account.Format(_T("%s"),eSDKTool::utf8_2_unicode(pLoginReqInfo->cUserName).GetBuffer());
	if (strlen(pLoginReqInfo->cPWD))
	{
		//AES+BASE64¼ÓÃÜÃÜÂë
		unsigned int cryptlen = 512;
		char szCrypt[512] = {0};
		const std::string aeskey_ = "jkfdkfcxzlwxcjkh";
		//¼ÓÃÜÄÚÈÝÌí¼ÓÑÎÖµ
		std::string real_password = pLoginReqInfo->cPWD;
		std::string real_account = pLoginReqInfo->cUserName;//StringUtility::unicode_w_2_utf8(m_UserName);
		std::string password = real_password + "$%" + real_account + "$%";
		(void)AES128_CBC_BASE64_Encode_GLY(szCrypt, &cryptlen, password.c_str(), 0, aeskey_.c_str(), 0, aeskey_.c_str(), 0);
		if (cryptlen < 512)
		{
			szCrypt[cryptlen] = '\0';
		}
		wstrPassword = eSDKTool::utf82unicode(std::string(szCrypt));
		//memset(szCrypt, 0, 512);
		//hwsecure
		//hw::memset_s(szCrypt, 512, 0, 512);
	}
	pwd =wstrPassword.c_str();// .Format(_T("%s"),eSDKTool::utf8_2_unicode(pLoginReqInfo->cPWD));
	
	m_pUCClient->SignConfig.autosign = TE_D_BISAUTOLOGIN_VALUE;
	m_pUCClient->SignConfig.savepwd = TE_D_BISREMEMBERPSW_VALUE;
	//m_pUCClient->SignConfig.account = eSDKTool::unicode_2_utf8(account);
	m_pUCClient->SignConfig.SetUserName(std::string(pLoginReqInfo->cUserName));
	m_pUCClient->SignConfig.pwd = eSDKTool::unicode_2_utf8(pwd);
	m_pUCClient->SignConfig.lang =  eSDKTool::unicode_2_utf8(ll);//ÓïÑÔ
	m_pUCClient->SignConfig.SetClientVersion(TE_DESKTOP_VERSION);
	m_pUCClient->SignConfig.SetInternalUrl(eSDKTool::unicode_2_utf8(InternalUrl));
	strInternalUrl = m_pUCClient->SignConfig.GetInternalUrl();
	size_t pos = strInternalUrl.find(":");
	if (std::string::npos != pos)
	{
		strDestIp = strInternalUrl.substr(0, pos);
	}
	
	if(strlen(pLoginReqInfo->cSipUri))
	{
		m_pUCClient->SignConfig.SetSipUri(eSDKTool::unicode_2_utf8(pLoginReqInfo->cSipUri));
	}
	else
	{
		m_pUCClient->SignConfig.SetSipUri("");
	}
	m_pUCClient->SignConfig.strSipRegisterMode = eSDKTool::unicode_2_utf8(pLoginReqInfo->cTransMode);
	m_pUCClient->SignConfig.initStatus = uc::model::Online;
	m_pUCClient->Self->selfInfo.ucAcc_ =  eSDKTool::unicode_2_utf8(account);
	m_pUCClient->SignConfig.SetBeAnonymityLogin(false);
	if(strlen(pLoginReqInfo->licenseServer))
	{
		m_pUCClient->SignConfig.SetLicenseServer(std::string(pLoginReqInfo->licenseServer));
	}
	
	ret = m_pUCClient->SignIn();
	std::string path;
	eSDKTool::getCurrentPath(path);
	std::string strLogCfgFile = path+"\\cert\\root_cert_huawei.pem";
	SetCurrentDirectoryA(strLogCfgFile.c_str());
	return (ret==true?TE_SDK_Success:TE_SDK_Failed);
}

int CTERegMgr::SignOut(void)
{
	DEBUG_TRACE("");
	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return TE_SDK_Failed;
		}
	}
	m_pUCClient->SignConfig.SetLicenseServer(std::string(""));
	m_pUCClient->SignOut();
	return TE_SDK_Success;
}

bool CTERegMgr::OnConfNotification(void* _item)
{
	DEBUG_TRACE("");
	bool bRet = false;

	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return bRet;
		}
	}

	if (_item)
	{
		bRet = m_pUCClient->ConfManager->HandleConferenceNotify(_item);
		if (!bRet)
		{
			ERROR_LOG("HandleConferenceNotify failed");
		}
	}

	return bRet;
}

bool CTERegMgr::OnConvNotification(void* _item)
{
	DEBUG_TRACE("");
	bool bRet = false;
	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return bRet;
		}
	}

	if (_item)
	{
		//uc::model::UCClient* pClient = uc::model::UCClient::GetClient();
		if(!m_pUCClient)
		{
			return bRet;
		}
		bRet = m_pUCClient->ConvManager->HandleConversationNotify(_item);
		if (!bRet)
		{
			ERROR_LOG("HandleConversationNotify failed");
		}
	}

	return bRet;
}

bool CTERegMgr::OnLdapNotification(void* _item)
{
	DEBUG_TRACE("");
	bool bRet = false;
	if(!m_pUCClient)
	{
		m_pUCClient = uc::model::UCClient::GetClient();
		if (!m_pUCClient)
		{
			return bRet;
		}
	}

	if (_item)
	{
		bRet = m_pUCClient->LdapManager->HandleLdapNotify(_item);
		if (!bRet)
		{
			ERROR_LOG( "HandleLdapNotify  failed !!");
		}
	}

	return bRet;
}


const TE_S_CALL_STATE_INFO *CTERegMgr::GetCallStateInfo()
{
	DEBUG_TRACE("");
	return &conversationchangedslot_.CallStateInfo;
}