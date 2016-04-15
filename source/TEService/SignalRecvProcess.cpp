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
 * @file  SignalRecvProcess.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Handle the signal of UCClient interface.
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/

#include "stdafx.h"
#include "SignalRecvProcess.h"
#include "EventMgr.h"
#include "TESDK.h"
#include "eSDKTool.h"
#include "TERegMgr.h"
#include "IM.h"
#include "IMMgr.h"
#include "log.h"
#include "SettingMgr.h"
#include <string>


static const std::string ID_RECENT_CONTACT_GROUP = "1";   // 最近联系人分组
static const std::string ID_MY_CONTACT_GROUP     = "2";   // 我的联系人分组
static const std::string ID_DEFAULT_GROUP        = "2";   // 我的联系人分组

//typedef  int __declspec(dllimport) (WINAPI *tup_call_get_callstatics)(CALL_S_STREAM_INFO* statics);
//typedef  int (*tup_call_get_callstatics)(CALL_S_STREAM_INFO* statics);

void SignalRecvProcess::OnClientSignInNotify(UCClient::SignInState _state, std::string _param)
{
	DEBUG_TRACE("");
	if (_param == uc::model::SIGNOUT_OK)
	{
		CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_SIGNOUT;
		INFO_LOG("Login signout");
		return;
	}


	switch (_state)
	{
	case uc::model::UCClient::Client_SignedIn:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_SUCCESS;	
			INFO_LOG("Login Success");
			 //SRTP默认最大互通性
			std::string  strSRTPValue = "";
			(void)USERCONFIG().GetUserConfig(SETTING_MEDIA_ENCRYPT_SRTP, strSRTPValue);
			if (strSRTPValue.empty())
			{
				(void)USERCONFIG().SaveUserConfig(SETTING_MEDIA_ENCRYPT_SRTP, "3");
			}
#ifdef RUSSIA
			//俄罗斯定制版本SRTP不加密
			(void)USERCONFIG().SaveUserConfig(SETTING_MEDIA_ENCRYPT_SRTP, "1");
#endif

			// 自动接听默认不启用
			std::string  strAutoReplyValue = ""; 
			(void)USERCONFIG().GetUserConfig(SETTING_MEDIA_AUTO_REPLY, strAutoReplyValue);  //
			if (strAutoReplyValue.empty())
			{
				(void)USERCONFIG().SaveUserConfig(SETTING_MEDIA_AUTO_REPLY, "0");
			} 

			// 辅流能力默认启用
			std::string  strSlideValue = "";
			(void)USERCONFIG().GetUserConfig(SETTING_MEDIA_OPEN_SLIDE, strSlideValue);
			if (strSlideValue.empty())
			{
				(void)USERCONFIG().SaveUserConfig(SETTING_MEDIA_OPEN_SLIDE, "1"); // 默认启用
			} 

			// 呼叫带宽
			std::string  strBandWidth = "";
			(void)USERCONFIG().GetUserConfig(SETTING_MEDIA_BAND_WIDTH, strBandWidth);
			if(strBandWidth.empty())
			{
				// 默认2048
				(void)USERCONFIG().SaveUserConfig(SETTING_MEDIA_BAND_WIDTH, "2048k bit/s");
			}

			//视频质量设置,默认流畅优先
			std::string  strVedioQuality = "";
			(void)USERCONFIG().GetUserConfig(VIDEO_QUALITY, strVedioQuality);
			if(strVedioQuality.empty())
			{
				(void)USERCONFIG().SaveUserConfig(VIDEO_QUALITY, "0");
			}

			// 联系人默认排序，分组下按名称
			std::string  strSortRule = "";
			(void)USERCONFIG().GetUserConfig(SORTRULE_PRIVATECONTACT, strSortRule);
			if(strSortRule.empty())
			{
				(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(SORTRULE_PRIVATECONTACT, "2");
			}

			//通话过程中主画面显示模式 拉伸0 原始1
			std::string strPicMode = "";
			(void)USERCONFIG().GetUserConfig(BIG_WINDOW_PIC_MODE, strPicMode);
			if(strPicMode.empty())
			{
				(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(BIG_WINDOW_PIC_MODE, "1");
			}
			
			historydata::HistoryManager::Instance()->InitializeHistoryData();
			// 初始化DB
			if (!UCCLIENT()->ContactManager->InitMemUserDB())
			{
				ERROR_LOG("InitMemUserDB Failed");
			}

			// 创建两个列表管理（联系人和搜索结果）
			// 获取客户分组列表
			std::vector<uc::model::CustomGroup> grouplist;
			if (!UCCLIENT()->ContactManager->GetCustomGrouplistByIndex(grouplist))
			{
				ERROR_LOG("GetCustomGrouplistByIndex Failed!");
			}
			// 分组为空
			if (grouplist.empty())
			{
				ERROR_LOG( "grouplist.empty()");

				// 插入最近联系人分组和我的联系人分组

				// step1：插入最近联系人分组
				uc::model::CustomGroup RecentContactGroup;
				RecentContactGroup.id_ = ID_RECENT_CONTACT_GROUP;
				RecentContactGroup.name_ = "recent  contact";
				if (!UCCLIENT()->ContactManager->AddCustomGroup(RecentContactGroup))
				{
					ERROR_LOG("AddCustomGroup Failed!");
				}

				// step2：插入我的联系人分组
				uc::model::CustomGroup MyContactGroup;
				MyContactGroup.id_ = ID_MY_CONTACT_GROUP;
				MyContactGroup.name_ = "default group";
				if (!UCCLIENT()->ContactManager->AddCustomGroup(MyContactGroup))
				{
					ERROR_LOG("AddCustomGroup Failed!");
				}
			}
			(void)UCCLIENT()->ContactSubManager->SubSCUserStatus(false);
			break;
		}
	case uc::model::UCClient::Client_SigningIn:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_SIGNING;
			INFO_LOG("Login Signing");
			break;
		}
	case UCClient::Client_KickedOut:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_KICKOUT;
			INFO_LOG("Login KickOut");
			break;
		}
	case UCClient::Client_SignedFailed:
		{

			if (SIGNINFAIL_AUTH == _param)
			{
				CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_AUTH;
				INFO_LOG("Login fail auth");
			}
			else if (SIGNINFAIL_TIMEOUT == _param)
			{
				//PostMessageMark(pdlg->GetSafeHwnd(), WM_LOGIN_FAILED, LOGIN_TIMEOUT, NULL);
				CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_TIMEOUT;
				INFO_LOG("Login Fail TimeOut");
			}
			else if(SIGNINFAIL_CER_VALID_FAILED == _param)
			{
				//PostMessageMark(pdlg->GetSafeHwnd(), WM_LOGIN_FAILED, LOGIN_CERT_VALID_FAILED, NULL);
				CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_CER_INVALID;

				INFO_LOG("Login Fail Cer_Invaild");
			}
			else if(SIGNINFAIL_REGISTER == _param)
			{
				//PostMessageMark(pdlg->GetSafeHwnd(), WM_LOGIN_FAILED, LOGIN_FAILED, NULL);
				CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LGOIN_FAIL_UNREGISTER;

				INFO_LOG("Login_Fail_Unregister");
			}

			break;
		}
	default:
		{
			//INFO_LOG() << "Login result :" << _state << "; _param = " << _param;
			//PostMessageMark(pdlg->GetSafeHwnd(), WM_LOGIN_FAILED, LOGIN_FAILED, NULL);
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_OTHERS;
			strncpy(CTERegMgr::Instance().m_LoginResult.cReserve, _param.c_str(),31);
			INFO_LOG("Login fail others");
			break;
		}
	}
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_LOGIN_RESULT,&CTERegMgr::Instance().m_LoginResult, sizeof(TE_S_LOGIN_RESULT));
}


 void SCStatusNotifySigRev:: OnStatusNotify(string id)
 {
	 DEBUG_TRACE("");
	 status = 1;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_USER_STATUS,&status,sizeof(int));
 }

void ConversationChangedSigRev::OnAVSessAdded(conversation::Conversation* _con, conversation::sAudioVideoParam _param)
{
	if (_con != NULL)
	{
		EventParam* param = new EventParam;
		memset(&CallStateInfo, 0, sizeof(TE_S_CALL_STATE_INFO));
		param->convId_ = _con->propmap_[conversation::ConvIdentifier];
		param->src_ = eSDKTool::ParsePhoneNo(_param.caller_);
		
		if (!PERM(uc::model::ClirOverride) && _param.caller_.compare("Anonymous") == 0)
		{
			_param.callername_ = "Anonymous";
		}

		ctk::xml::XMLOutStream xos;
		xos["callername"] << _param.callername_;
		xos["callalertinfo"] << _param.callalertinfo_;
		xos["lineindex"] << _param.lineindex_;
		xos["isvideo"] << _param.isvideo_;
		xos["callmode"] << _param.callmode_;
		param->xmlbody_  = xos.str();
		
		CallStateInfo.enCallEvent = TE_E_CALL_EVENT_AUDIOVIDEOINCOMING;
		CallStateInfo.bIsIn = 1;
		CallStateInfo.enCallState = TE_E_CALL_STATE_IN;
		strcpy(CallStateInfo.acDisplayName,_param.callername_.c_str());
		DEBUG_LOG("isvideo_ :%d",_param.isvideo_);
		if(_param.isvideo_)
		{
			CallStateInfo.enCallType = TE_E_CALL_TYPE_IPVIDEO;
			
			INFO_LOG("Call Type Ip Video");
		}
		else
		{
			CallStateInfo.enCallType = TE_E_CALL_TYPE_IPAUDIO;
			INFO_LOG("Call Type Ip Audio");
		}
		
		CIMConversation* pIMConv = new CIMConversation;
		pIMConv->SetConvId(param->convId_);
		CallStateInfo.ulCallID = GetCallID(_con);
		//IMManager::Instance().m_convID = param->convId_;

		TE_S_STREAM_INFO callStreamInfo;
		memset(&callStreamInfo,0,sizeof(TE_S_STREAM_INFO));
		int result = CSettingMgr::Instance().GetNetworkConfig(_con,&callStreamInfo);

		if (TE_SDK_Success == result)
		{
			string strAudioCodec = callStreamInfo.stAudioStreamInfo.acEncodeProtocol;
			strncpy(CallStateInfo.acEncodeProtocol,strAudioCodec.c_str(),TE_D_PROTOCOL_LENGTH-1);
			
		}

		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		//yw need implement function.
		//CEventMgr::Instance().OnEventCallBack(AudioVideoIncomingNotifyMsg, param, sizeof(EventParam));
		//fEventCallBack(AudioVideoIncomingNotifyMsg, param, sizeof(UIEventParam), );

		IMManager::Instance().convmap_.put(param->convId_, pIMConv);
		//delete pIMConv;
		delete param;
	}

}
TE_UINT32 ConversationChangedSigRev::GetCallID(conversation::Conversation* _con)
{
	DEBUG_TRACE("");
	conversation::AVSession* pSess = NULL;
	if(_con)
	{
		pSess = dynamic_cast<conversation::AVSession*>(_con->GetSession(AudioVideo));
	}
	if (NULL == pSess)
	{
		return 0L;
	}
	std::string strCallid = pSess->propmap_[AVSessionIdentifier];
	TE_UINT32 callid = eSDKTool::str2num<TE_UINT32>(strCallid);
	return callid;

}
void ConversationChangedSigRev::AVSessionClosed(conversation::Conversation* _con, std::string _avid, std::string _reason)
{
	DEBUG_TRACE("");
	if (_con != NULL)
	{
		
		EventParam* param = new EventParam;
		memset(&CallStateInfo, 0, sizeof(TE_S_CALL_STATE_INFO));
		param->convId_ = _con->propmap_[conversation::ConvConfIdentifier];
		ctk::xml::XMLOutStream xos;
		xos["avid"] << _avid;
		xos["reason"] << _reason;
		param->xmlbody_ = xos.str(true);
		//CEventMgr::Instance().OnEventCallBack(AudioVideoCallAnswerRspMsg, param, sizeof(UIEventParam));
		CallStateInfo.enCallEvent = TE_E_CALL_EVENT_CLOSE;
		//CallOutMenuHandler::CallStateInfo.bIsIn = 1;
		CallStateInfo.enCallState = TE_E_CALL_STATE_END;
		switch(atoi(_reason.c_str()))
		{
			case 603:
			{
				CallStateInfo.ulReasonCode = TE_E_CALL_END_REASON_CANNOT_CONNECT;
				break;
			}
			case 486:
			{
				CallStateInfo.ulReasonCode = TE_E_CALL_END_REASON_BUSYING;
				break;
			}
			case 1000:
			{
				CallStateInfo.ulReasonCode = TE_E_CALL_END_REASON_CANNOT_CONNECT_OFFLINE;
				break;
			}
			default:
			{
				CallStateInfo.ulReasonCode = TE_E_CALL_END_REASON_NORMAL;
				break;
			}
		}
		//if(_param.isvideo_)
		//{
		//	CallOutMenuHandler::CallStateInfo.enCallType = TE_E_CALL_TYPE_IPVIDEO;
		//}
		//else
		//{
		//	CallOutMenuHandler::CallStateInfo.enCallType = TE_E_CALL_TYPE_IPAUDIO;
		//}
		CallStateInfo.ulCallID = GetCallID(_con);
		IMManager::Instance().convmap_.erase(_con->propmap_[conversation::ConvConfIdentifier]);
		
		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		delete param;
	}
}

void ConversationChangedSigRev::AVSessionConnected(conversation::Conversation* _con, int sessiontype_)
{
	DEBUG_TRACE("");
	if (_con != NULL)
	{
		EventParam* param = new EventParam;
		memset(&CallStateInfo, 0, sizeof(TE_S_CALL_STATE_INFO));
		param->convId_ = _con->propmap_[conversation::ConvConfIdentifier];
		ctk::xml::XMLOutStream xos;
		xos["sessiontype"] << sessiontype_;
		param->xmlbody_ = xos.str(true);
		//CEventMgr::Instance().OnEventCallBack(AudioVideoCallAnswerRspMsg, param, sizeof(UIEventParam));
		CallStateInfo.enCallEvent = TE_E_CALL_EVENT_ANSWERRSP;
		//CallOutMenuHandler::CallStateInfo.bIsIn = 1;
		CallStateInfo.enCallState = TE_E_CALL_STATE_LIVE;
		//if(_param.isvideo_)
		//{
		//	CallOutMenuHandler::CallStateInfo.enCallType = TE_E_CALL_TYPE_IPVIDEO;
		//}
		//else
		//{
		//	CallOutMenuHandler::CallStateInfo.enCallType = TE_E_CALL_TYPE_IPAUDIO;
		//}
		CallStateInfo.ulCallID = GetCallID(_con);

		if (_con->sessiontype_ & MEDIA_SESSION_VIDEO )
		{
			CallStateInfo.enCallType = TE_E_CALL_TYPE_IPVIDEO;
		}
		else if (_con->sessiontype_  & MEDIA_SESSION_AUDIO)
		{
			CallStateInfo.enCallType = TE_E_CALL_TYPE_IPAUDIO;
		}
		else
		{
			CallStateInfo.enCallType = TE_E_CALL_TYPE_BUTT;
		}
	

		TE_S_STREAM_INFO callStreamInfo;
		memset(&callStreamInfo,0,sizeof(TE_S_STREAM_INFO));
		int result = CSettingMgr::Instance().GetNetworkConfig(_con,&callStreamInfo);

		if (TE_SDK_Success == result)
		{
			string strAudioCodec = callStreamInfo.stAudioStreamInfo.acEncodeProtocol;
			strncpy(CallStateInfo.acEncodeProtocol,strAudioCodec.c_str(),TE_D_PROTOCOL_LENGTH-1);

		}


		IMManager::Instance().GetIMConvByCallID(CallStateInfo.ulCallID)->OnCallConnect(0);

		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));

		delete param;
	}
}

void ConversationChangedSigRev::AVSessionRinged(conversation::Conversation* _con)
{
	DEBUG_TRACE("");
	if (_con != NULL)
	{
		EventParam* param = new EventParam;
		memset(&CallStateInfo, 0, sizeof(TE_S_CALL_STATE_INFO));
		param->convId_ = _con->propmap_[conversation::ConvConfIdentifier];
		//CEventMgr::Instance().OnEventCallBack(AudioVideoCallRingNotifyMsg, param, sizeof(UIEventParam));
		CallStateInfo.enCallEvent = TE_E_CALL_EVENT_CALLRING;
		//CallOutMenuHandler::CallStateInfo.bIsIn = 1;
		//CallOutMenuHandler::CallStateInfo.enCallState = TE_E_CALL_STATE_LIVE;
		//if(_param.isvideo_)
		//{
		//	CallOutMenuHandler::CallStateInfo.enCallType = TE_E_CALL_TYPE_IPVIDEO;
		//}
		//else
		//{
		//	CallOutMenuHandler::CallStateInfo.enCallType = TE_E_CALL_TYPE_IPAUDIO;
		//}
		CallStateInfo.ulCallID = GetCallID(_con);

		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		delete param;
	}
}

/*******************************************************************************

*******************************************************************************/

TE_UINT32 AvSessionBFCPModifiedSigRev::GetCallID(conversation::Conversation* _con)
{
	DEBUG_TRACE("");
	conversation::AVSession* pSess = NULL;
	if(_con)
	{
		pSess = dynamic_cast<conversation::AVSession*>(_con->GetSession(AudioVideo));
	}
	if (NULL == pSess)
	{
		return 0L;
	}
	std::string strCallid = pSess->propmap_[AVSessionIdentifier];
	TE_UINT32 callid = eSDKTool::str2num<TE_UINT32>(strCallid);
	return callid;

}


/*******************************************************************************

*******************************************************************************/
void AvSessionBFCPModifiedSigRev::OnAvSessionBFCPModifiedSigRes(std::string _convid, int _sessionType, bool _bDataReady)
{
	DEBUG_TRACE("");
	if (_convid.empty())
	{
		return;
	}

	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(_convid);

	if (pConv!=NULL)
	{

		EventParam* param = new EventParam;
		if (!param)
		{
			return;
		}

		param->convId_ = _convid;
		ctk::xml::XMLOutStream xos("avSessionBFCPModifiedResult");

		xos["result"] << _sessionType;
		xos["DataReady"] << _bDataReady;
		param->xmlbody_ = xos.str();

		
		CallStateInfo.sessionType=_sessionType;
		CallStateInfo.ulCallID = GetCallID(pConv);
		CallStateInfo.enDataEvent=TE_E_DATA_BFCPMODIFIED_RESULT;


		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		delete param;
		//UIFRAME_EVENTDISPATCH_INSTANCE()->pushEvent(IM_AVSESSION_BFCP_MODIFIED_RESULT, param);

	}

}


void ConfCreateStateChangeSigRev::OnConfCreateStateChangeSigRes(std::string _reason, int _result)
{
	DEBUG_TRACE("");
	restInfo.eventType=TE_E_EVT_CREATE_CONF_STATE_CHANGE;

	strncpy(restInfo.uResult.createConfInfo._reason,_reason.c_str()+3,TE_D_DESC_MAX_NUM);
	restInfo.uResult.createConfInfo._result=_result;

	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));

	/*ConfCreateDlg* pdlg = dynamic_cast<ConfCreateDlg*>(m_wnd);
	if (NULL == pdlg)   
	{
		return;
	}
	pdlg->SetDescribtion(_reason);
	::PostMessage(pdlg->GetSafeHwnd(), WM_CONFERENCE_CREATE_CONF_STATE_CHANGE, NULL, (LPARAM)_result);*/
}


void ConfChairManApplyResultSigRev::OnConfChairManApplyResultSigRes(int _result)
{
	DEBUG_TRACE("");
	restInfo.eventType=TE_E_EVT_APPLY_CONF_CHAIRMAN;
	restInfo.uResult.result=_result;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}


void ConfChairManReleaseSigRev::OnConfChairManReleaseResultSigRes(bool _result)
{
	DEBUG_TRACE("");
	restInfo.eventType=TE_E_EVT_RELEASE_CONF_CHAIRMAN;
	restInfo.uResult.result=(int)_result;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}


//void ConfCtrlNotifySigRev::OnConfCtrlFLoorAttendeeInd(uc::model::Hall _hall)
//{
//	CIMConfList* pdlg = dynamic_cast<CIMConfList*>(m_wnd);
//	if (NULL == pdlg)   
//	{
//		return;
//	}
//	pdlg->SetFloorAttendee(_hall);
//}

void ConfCtrlNotifySigRev::OnAddHallResult(short failedCount, bool result)
{
	DEBUG_TRACE("result:%d",result);
	restInfo.eventType=TE_E_EVT_ADDSITETOCONF_RESULT;
	restInfo.uResult.addHallRest.failedCount=failedCount;
	restInfo.uResult.addHallRest.result=result;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}

void ConfCtrlNotifySigRev::OnConfCtrlBroadCastResult(int result)
{
	DEBUG_TRACE("result:%d",result);
	restInfo.eventType=TE_E_EVT_CONF_BROADCAST_RESULT;
	restInfo.uResult.result=result;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}

void ConfCtrlNotifySigRev::OnConfCtrlWatchResult(int result)
{
	DEBUG_TRACE("result:%d",result);
	restInfo.eventType=TE_E_EVT_SITE_WATCH_RESULT;
	restInfo.uResult.result=result;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}

void ConfCtrlNotifySigRev::OnConfCtrlTimeRemnant(short time)
{
	DEBUG_TRACE("");
	restInfo.eventType=TE_E_EVT_CONF_EXTENDTIME_NOTE;
	restInfo.uResult.result=time;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}
// CIMConfList 消息处理程序

void ConfCtrlNotifySigRev::OnConfExtendResult(bool _result)
{
	DEBUG_TRACE("result:%d",_result);
	restInfo.eventType=TE_E_EVT_CONF_EXTEND_RESULT;
	restInfo.uResult.result=(int)_result;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}


void ConfAttendeeListRefreshSigRev::OnConfAttendeeListRefreshSigRes(std::vector<uc::model::Hall> /*_vecConfHalls*/)
{
	DEBUG_TRACE("");
	restInfo.eventType=TE_E_EVT_CONF_MEMLISTREFRESH;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}

void ConfAttendeeListRefreshSigRev::OnConfCtrlBroadCastInd(short M, short T)
{
	DEBUG_TRACE("");
	restInfo.eventType=TE_E_EVT_CONF_BROADCAST_MEMLISTREFRESH;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}

void ConfAttendeeListRefreshSigRev::OnConfCtrlChairManInd(bool isChairMan)
{
	DEBUG_TRACE("result:%d",isChairMan);
	restInfo.eventType=TE_E_EVT_CONF_CHAIRMAN_THENDO;
	restInfo.uResult.isChairman=isChairMan;
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CONF_RESULT,&restInfo, sizeof(TE_S_CONF_RESULT));
}

void NetAddrDownloadedSigRecvInEnterprise::OnNetAddrDownloaded()
{
	DEBUG_TRACE("");
	//	restInfo.eventType = TE_E_EVT_NET_CONTACTS_ADDRESS;
	//	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_ENTERPRISE_RESULT,&restInfo,sizeof(TE_S_ENTERPRISE_RESULT));
}

void LdapSearchResultRevInEnterprise::OnLdapSearchResultRev(LDAP_D_Search_Result* result)
{
	DEBUG_TRACE("");
	restInfo.eventType = TE_E_EVT_LDAP_CONTACTS_ADDRESS;
	if (result)
	{
		LDAP_D_Search_Result* pResult = new LDAP_D_Search_Result(*result);
		restInfo.pResult = new TE_S_LDAP_D_Search_Result;
		restInfo.pResult->bSucess = pResult->bSucess;
		restInfo.pResult->pcPageCookie = pResult->pcPageCookie;
		restInfo.pResult->ulCode = pResult->ulCode;
		restInfo.pResult->ulCookieLen = pResult->ulCookieLen;
		restInfo.pResult->ulSeqNo = pResult->ulSeqNo;
		if(pResult)
		{
			delete pResult;
		}
		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_ENTERPRISE_RESULT,&restInfo,sizeof(TE_S_ENTERPRISE_RESULT));
	}
}


void LicenseStateProcessSigRev::OnClientLicenseStateNotify(UCClient::LicenseState _state, std::string _reason)
{
	DEBUG_TRACE("");
	DEBUG_LOG("Login state:%d",_state);
	switch (_state)
	{
	case uc::model::UCClient::LicenseTypeGetFailed:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_LICENSE_TYPE_FAILED;	
			INFO_LOG("Get license type  failed.");
			break;
		}
	case uc::model::UCClient::LicenseTypeInvalid:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_LICENSE_TYPE_INVALID;
			INFO_LOG("License type  invalid.");
			break;
		}
	case UCClient::LicenseApplyFailed:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_LICENSE_APPLY_FAILED;
			INFO_LOG("Apply license failed");
			break;
		}
	case UCClient::LicenseRefreshFailed:
		{
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_LICENSE_REFRESH_FAILED;
			INFO_LOG("Login KickOut");
			break;
		}
	default:
		{
			//INFO_LOG() << "Login result :" << _state << "; _param = " << _param;
			//PostMessageMark(pdlg->GetSafeHwnd(), WM_LOGIN_FAILED, LOGIN_FAILED, NULL);
			CTERegMgr::Instance().m_LoginResult.loginState = TE_E_LOGIN_FAIL_OTHERS;
			INFO_LOG("Login fail others");
			break;
		}
	}
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_LOGIN_RESULT,&CTERegMgr::Instance().m_LoginResult, sizeof(TE_S_LOGIN_RESULT));
}