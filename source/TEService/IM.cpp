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
 * @file  IM.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Handle Callout include video and audio.
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/

#include "stdafx.h"
#include "SignalRecvProcess.h"
#include "IM.h"
#include "IMMgr.h"
#include "TERegMgr.h"
#include "EventMgr.h"
#include "Log.h"


bool PhoneEventHandler::hangup_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv;
	//int ret;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}
	
	p_IMConv->HangUpCall();

	return true;
}

bool PhoneEventHandler::rejectcall_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv;
	//int ret;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}
	
	p_IMConv->RejectCall();

	return true;
}
bool PhoneEventHandler::callout_handle(CallParam* _param)
{
	DEBUG_TRACE("");
	if (_param)
    {
        if (0 == _param->memlist.size())
        {
            return false; //参数不正确
        }
        

        //点对点呼叫时，判断当前是否可发起呼叫
        if (TE_CheckCallParam_Success != CheckCallParam(_param))
        {
			return false;
        }

        IMManager::Instance().FilterInvaildContact(_param->memlist);

		if (0 == _param->memlist.size())
		{
			return false;
		}

		//判断是否有呼叫权限
        if (false == HasCalloutPermission(_param))
        {
            return false;
        }
		CIMConversation *p_IMConv = IMManager::Instance().GetConversationExist(_param);
		if (!p_IMConv)
		{

			p_IMConv = IMManager::Instance().CreateConverSession(_param);
		}

		if (NULL == p_IMConv)
		{
			//create IMConv fail, return
			return false;
		}
		
        //视频呼出
		if (_param->callType)
		{
			conversation::Conversation* pConv = IMManager::Instance().GetCurConv(p_IMConv->m_convID);
			if (pConv)
			{
				if (pConv->propmap_[ConvTempGroupUri].empty()&& pConv->propmap_[ConvConfIdentifier].empty())
				{
					//发起视频呼叫
					BOOL bRet = p_IMConv->VideoCallOut();
					if(FALSE ==bRet)
					{
						p_IMConv->HangUpCall();//无法发起呼叫，以结束通话刷界面
					}
				}
			}
		}
		else//音频呼出
		{
			bool bRet = p_IMConv->AudioCallOut(_param->callType);
			if(FALSE == bRet)
			{
				p_IMConv->HangUpCall();//无法发起呼叫，以结束通话刷界面
			}
		}

		return true;
    }

    return false;
}

//创建当前IM的Conversation对应的历史记录Conversation
void CIMConversation::CreateConvHistory(CallParam* _param, CIMConversation* convHistory)
{
	DEBUG_TRACE("");
	if (NULL == convHistory)
	{
		return;
	}

	if (_param && (IM_EMPTY_DLGKEY != convHistory->GetConvId()))
	{
		//创建当前IM的Conversation对应的历史记录Conversation
		if (!convHistory->IsIMConvExist(convHistory->GetConvId()))
		{ 
			std::string hisconvID = convHistory->CreateIMHistoryConv(convHistory->GetConvId(), convHistory->GetHisConvId());convHistory->AddHistoryConv(convHistory->GetConvId(), hisconvID);
		}

		//创建历史记录ConvID
		if (convHistory->IsIMConvExist(convHistory->GetConvId()))
		{
			std::string historyid = convHistory->GetHistoryConvID(convHistory->GetConvId());
			if (!historyid.empty())
			{
				//
			}
		}
	}

	return;
}

void CIMConversation::AddHistoryConv(const std::string& _imConvID, const std::string& _historyConvID)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"_imConvID:%s,_historyConvID:%s",_imConvID.c_str(),_historyConvID.c_str());
	DEBUG_TRACE("add history convition:%s",strParameter);
	if (_historyConvID.empty() || _imConvID.empty())
	{
		return;
	}

	//由于对话过程中，存在两方转多方等的场景，所以需要实时转换历史记录的ID
	if (m_IMHistoryManageMap.find(_imConvID) != m_IMHistoryManageMap.end())
	{
		m_IMHistoryManageMap[_imConvID] = _historyConvID;
	}
	else
	{
		(void)m_IMHistoryManageMap.insert(_HISTOTY_CONV_MAP::value_type(_imConvID, _historyConvID));
	}
}

std::string CIMConversation::CreateIMHistoryConv(const std::string& _imConvID, const std::string& _hisConvId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"ConvID:%s",_imConvID.c_str());
	DEBUG_TRACE(strParameter);
	std::string historyConvID = "";

	HistoryManager *pHistoryManager = HistoryManager::Instance();
	UCClient *pClient = UCClient::GetClient();
	if (!pHistoryManager || !pClient)
	{
		return historyConvID;
	}

	//获得IM的conversation
	conversation::Conversation *pConv = pClient->ConvManager->GetConversation(_imConvID);
	if (NULL == pConv)
	{
		return historyConvID;
	}

	historydata::Conversation historyConv;

	if (!_hisConvId.empty())
	{
		//加载历史临时群聊天记录
		if (pHistoryManager->GetConversationByConversationId(historyConv, _hisConvId) )
		{
			historyConvID = historyConv.cvsId;
		}

		INFO_LOG("historyid,%s",historyConvID.c_str());
	}
	else if (!pConv->propmap_[uc::model::conversation::ConvIdentifier].empty())//点对点聊天
	{
		std::string currentImDlgUri = "";
		uc::model::conversation::Conversation::MemList_::iterator itor = pConv->members_.begin();
		for (; itor != pConv->members_.end(); itor++)
		{
			//if ((*itor).second->contact_.uri_ != pClient->Self->selfInfo.uri_)
			if ((*itor).first != pClient->Self->selfInfo.uri_)
			{
				//如果uri不为空，则取账号，否则取电话号码
				if (IMManager::Instance().IsValidUri((*itor).first))
				{
					currentImDlgUri = IMManager::Instance().GetNoFromUri((*itor).first);
				}
				else
				{
					uc::model::Contact contactInfo;

					if(!(*itor).second->contact_.id_.empty())
					{
						if(pClient->ContactManager->GetContactById((*itor).second->contact_.id_, contactInfo))
						{
							//呼出历史记录conversation id 设置为mobile，否则导致最近联系人显示为联系人id
							currentImDlgUri = (*itor).first;
							if(IMManager::Instance().IsValidUri(contactInfo.uri_))
							{
								currentImDlgUri = IMManager::Instance().GetNoFromUri(contactInfo.uri_);
							}
						}
					}
					else
					{
						currentImDlgUri = (*itor).first;
					}
				}
				break;
			}
		}

		//插入一条历史记录
	historyConvID = InsertSigleConvHistory(currentImDlgUri);

	INFO_LOG("P2P HistoryID,%s ",historyConvID.c_str());
	}

	return historyConvID;
}

//添加一条新的历史纪录
std::string CIMConversation::InsertSigleConvHistory(std::string& strCurrentImDlgUri)
{
	DEBUG_TRACE("uri:%s",strCurrentImDlgUri.c_str());
	std::string strHistoryConvID = "";	
	historydata::Conversation historyConv;

	HistoryManager *pHistoryManager = HistoryManager::Instance();
	if (NULL == pHistoryManager)
	{
		return strHistoryConvID;
	}

	//获取当前时间
	historydata::Date curdate;
	historydata::Time curtime;
	CTime times    = CTime::GetCurrentTime();
	curdate.year   = times.GetYear();
	curdate.month  = times.GetMonth();
	curdate.day    = times.GetDay();
	curtime.hour   = times.GetHour();
	curtime.minute = times.GetMinute();
	curtime.second = times.GetSecond();

	//如果conversation记录超过1500条，则删除最旧的那条
	std::string lastHistoryConvID;
	int num = pHistoryManager->GetAllConversation(lastHistoryConvID);
	if (num >= 1500)
	{
		uc::model::historydata::Conversation hisConversation;

		if(pHistoryManager->GetConversationByConversationId(hisConversation, strCurrentImDlgUri))
		{
			if (hisConversation.cvsId.empty())
			{
				(void)pHistoryManager->RemoveConversationByConversationID(lastHistoryConvID);
			}
		}
	}

	bool val = pHistoryManager->CreateSingleConversation(historyConv, strCurrentImDlgUri, curdate, curtime);
	if (val)
	{
		strHistoryConvID = historyConv.cvsId;
	}

	return strHistoryConvID;
}


bool CIMConversation::IsIMConvExist(std::string _imConvID)
{
	DEBUG_TRACE("ID:%s",_imConvID.c_str());
	if (m_IMHistoryManageMap.find(_imConvID) != m_IMHistoryManageMap.end())
	{
		return TRUE;
	}

	return FALSE;
}

bool PhoneEventHandler::answeraudiocall_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}
	
	p_IMConv->AcceptAudioCall();

	return true;
}


bool PhoneEventHandler::answervediocall_handle(TE_UINT32 callId, TE_BOOL isAudioAccept)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,isAudioAccept:%d",callId,isAudioAccept);
	DEBUG_TRACE("answervideo handle:%s",strParameter);
	CIMConversation* p_IMConv;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}
	
	p_IMConv->AcceptVideoCall(isAudioAccept);

	return true;
}

//函数执行完strFormat为空，说明是一路正常的新的呼叫
int PhoneEventHandler::CheckCallParam(CallParam* _param)
{
	DEBUG_TRACE("");
    std::string strSelfUri = UCCLIENT()->Self->selfInfo.uri_;
    uc::model::Contact contact_ = (*(_param->memlist.begin()));
	

    if (eSDKTool::IsValidUri(contact_.uri_))
    {
        if (contact_.uri_ == UCCLIENT()->Self->selfInfo.ucAcc_ || contact_.uri_ == strSelfUri)
        {
            //不能呼叫自己
            return TE_CheckCallParam_FAIL_CallSelf;
        }
    }
    else
    {
        if (contact_.mobile_ ==  UCCLIENT()->Self->selfInfo.ucAcc_ || contact_.mobile_ ==  strSelfUri)
        {
            //不能呼叫自己
            return TE_CheckCallParam_FAIL_CallSelf;
        }

    }

    if (UCCLIENT()->ContactManager->HasContactByName(contact_.name_) && eSDKTool::IsEmptyUri(contact_.uri_))
    {
        //不能呼叫空号码
		return TE_CheckCallParam_FAIL_NulNum;
   
    }
    else if ((!eSDKTool::IsValidUri(contact_.uri_) || eSDKTool::GetNoFromUri(contact_.uri_).empty()) && contact_.mobile_.empty())
    {
         //不能呼叫空号码
		return TE_CheckCallParam_FAIL_NulNum;
    }
    else if (UCCLIENT()->ConvManager->HasConnectingAVSession())
    {
        //当前有来电时，不能发起新的呼叫
		return TE_CheckCallParam_FAIL_HasNewSession;
    }
    else if (IMManager::Instance().HasAudioVideo())
    {
        //不能发起多路通话 by zhuxudong
		return TE_CheckCallParam_FAIL_HasTwoSession;
    }

    if (UCCLIENT()->Self->selfStatus == uc::model::Offline)
    {
        
		return TE_CheckCallParam_FAIL_Offline;
    }
	return TE_CheckCallParam_Success;
}

//判断是否有呼叫权限  w00221920 2015-04-21
bool PhoneEventHandler::HasCalloutPermission(CallParam* _param)
{
	DEBUG_TRACE("");
    if (!PERM(uc::model::VoiceCall))
    {
        return false; //无语音呼叫权限
    }

    if ((true == _param->videocall) && !PERM(uc::model::VideoCall))
    {
        return false; //无视频呼叫权限
    }

    return true;
}


//发起发送辅流申请
bool ShareEventHandler::requestsend_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}

	if(!p_IMConv->StartSendData())
	{
		return false;
	}


	return true;
}

bool ShareEventHandler::stopsend_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}

	if(!p_IMConv->StopSendData())
	{
		return false;
	}


	return true;
}


bool ShareEventHandler::startrecvdata_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}

	if(!p_IMConv->StartRecvData())
	{
		return false;
	}

	return true;
}


bool ShareEventHandler::stoprecvdata_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}

	if(!p_IMConv->StopRecvData())
	{
		return false;
	}

	return true;
}


bool ShareEventHandler::rejectrecvdata_handle(TE_UINT32 callId)
{
	DEBUG_TRACE("callId:%d",callId);
	CIMConversation* p_IMConv;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return false;
	}

	if(!p_IMConv->RejectRecvData())
	{
		return false;
	}

	return true;
}


CIMConversation::CIMConversation()
:m_convID(IM_EMPTY_DLGKEY)
,m_strSubject(_T("Default Chat"))
,m_bAcceptedOwer(FALSE)
,m_bHasAccepted(FALSE)
,m_bIsDataReceiving(FALSE)
,m_hwndShared(NULL)
,m_CallRcdID(0)
{
}

CIMConversation::~CIMConversation()
{
	m_hwndShared = NULL;

}


#if 0
CIMConversation* IMManager::CreateConverSession(CallParam* _param)//const std::vector<uc::model::Contact>& _list, const std::string& _fixgrpId)
{
	CIMConversation *pIMConv = new CIMConversation;
	
	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;
	
	if (NULL == pIMConv)
	{
		return NULL;
	}

	if (!ucclient || (_param->memlist.size() == 0 && _param->fixgrpId == ""))
	{
		return NULL;
	}
	
	if (_param)
	{
		if (!_param->convId.empty())
		{
			pIMConv->SetConvId(_param->convId);
		}

		if (!_param->history_convId.empty())
		{
			pIMConv->SetHisConvId(_param->history_convId);
		}
	}

	conversation::Conversation* pConv = NULL;
	if (_param->memlist.size() == 1)
	{
		pConv = ucclient->ConvManager->GetConversationByContact(*(_param->memlist.begin()));
	}

	if (!pConv)
	{
		//INFO_LOG()<<" create a new conversation";
		pConv = ucclient->ConvManager->AddConversation();
		if(!pConv)
		{
			delete pIMConv;
			return NULL;
		}
	}

	std::string hisconvid = pIMConv->GetHisConvId();
	pConv->propmap_[conversation::ConvHistoryGroupUri] = hisconvid;

	if (_param->fixgrpId == "")
	{
		std::string strAccount = "";
		std::vector<uc::model::Contact>::const_iterator citb = _param->memlist.begin();
		while (citb != _param->memlist.end())
		{
			uc::model::Contact contact_ = (*citb);
			if(eSDKTool::IsValidUri(contact_.uri_))
			{
				strAccount = eSDKTool::GetNoFromUri(contact_.uri_);
			}
			else
			{
				if(!contact_.mobile_.empty())
				{
					strAccount = contact_.mobile_;
				}
			}
			contact_.ucAcc_ = strAccount;
			if(ucclient->ContactManager->HasContactByAccount(contact_.ucAcc_))
			{
				(void)ucclient->ContactManager->GetContactByAccount(contact_.ucAcc_, contact_);
			}

			if (contact_.name_.empty())
			{
				contact_.name_ = contact_.ucAcc_;
			}

			(void)pConv->AddParticipant(contact_);

			++citb;
		}
	}

	pConv->propmap_[conversation::ConvSubject] = eSDKTool::unicode_2_utf8(pIMConv->m_strSubject);
	pIMConv->m_convID = pConv->propmap_[conversation::ConvIdentifier];
	convmap_.put(pIMConv->m_convID,pIMConv);
	return pIMConv;
}
#endif
bool CIMConversation::AudioCallOut(int iCallType)
{
	DEBUG_TRACE("callId:%d",iCallType);
	//TRACE_FUNC();
	//m_VoiceStateDlg.SetUIMode(CIMVoiceMainWnd::VOICEMAIN_AUDIO_MODE);
	return CallOut(FALSE,iCallType);
}

bool CIMConversation::VideoCallOut()
{
	DEBUG_TRACE("");
	return CallOut(TRUE);
}

bool CIMConversation::CallOut(bool bVideoCall, int iCallType)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"bVideoCall:%d",bVideoCall);
	DEBUG_TRACE("call out %s",strParameter);
	//TRACE_FUNC1(bVideoCall);

	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (!pConv)
	{
		return FALSE;
	}
	//检查是否能发起新的呼叫
	if( IMManager::Instance().HasAudioOrVideoInUse(m_convID)|| ucclient->ConvManager->HasConnectingAVSession())
	{
		return FALSE;
	}

	//已存在语音会话，不再发起
	conversation::AVSession* pSess = NULL;
	if (pConv->HasSession(AudioVideo) )
	{
        //发起音频转视频操作
		if (FALSE == AudioToVideoCall(bVideoCall))
        {
			return FALSE;
        }


		return TRUE;
	}

	//不存在会话，为发起新呼叫操作
	pSess = dynamic_cast<conversation::AVSession*>(pConv->AddSession(AudioVideo));

	if (pSess)
	{
		//m_bSelfStart = TRUE; //标识语音发起方为自己

		//呼出时记录一条呼出记录Record

		Contact contact;
		std::string peerID;

		(void)IMManager::Instance().GetPeerInfo(m_convID, contact);

		peerID = contact.uri_.empty() ? contact.mobile_ : IMManager::Instance().GetNoFromUri(contact.uri_);

		m_CallRcdID = InsertCallHistory(m_convID, peerID, contact.name_, TRUE, bVideoCall);
		//UpdateRecentSingleCall(m_CallRcdID, peerID, contact.name_);

		if (bVideoCall)
		{
			//INFO_LOG()<<"SetUIMode CIMVoiceMainWnd::VOICEMAIN_VIDEO_MODE";
			//m_VoiceStateDlg.SetUIMode(CIMVoiceMainWnd::VOICEMAIN_VIDEO_MODE);
			
			//设置视频通道参数信息
			InitVideoParam();
		}

		//判断呼叫终端类型，默认呼叫PC客户端
		if (!pSess->Connect())//发起AudioVideo Session
		{
			//发起失败，挂断呼叫
			(void)pSess->Disconnect();

			HangUpCall();
		}

		return TRUE;
	}

	return FALSE;
}

std::string CIMConversation::GetHistoryConvID(std::string _imConvID)
{
	DEBUG_TRACE("convId:%s",_imConvID.c_str());
	std::string hisConvId = "";
	_HISTOTY_CONV_MAP::iterator itor = m_IMHistoryManageMap.find(_imConvID);
	if (itor != m_IMHistoryManageMap.end())
	{
		hisConvId = (*itor).second;
	}

	return hisConvId;
}


long long CIMConversation::InsertCallHistory(std::string _imConvID, std::string src, std::string srcname, BOOL bIsSend, BOOL bIsVideoCall)
{
	DEBUG_TRACE("convId:%s",_imConvID.c_str());
	long long rcdID = -1;

	std::string historyConvID = GetHistoryConvID(_imConvID);

	//写入历史记录
	uc::model::historydata::HistoryManager *pHistoryManager = uc::model::historydata::HistoryManager::Instance();
	if (NULL == pHistoryManager)
	{
		return rcdID;
	}

	uc::model::UCClient* pClient = uc::model::UCClient::GetClient();
	ASSERT(pClient);

	//获得当前的conversation
	uc::model::conversation::Conversation* _conv = pClient->ConvManager->GetConversation(_imConvID );
	if(!_conv)
	{
		return rcdID;
	}

	uc::model::historydata::Conversation hisConversation;
	CTime times = CTime::GetCurrentTime();
	Date curDate;
	Time curTime;
	curDate.year = times.GetYear();
	curDate.month = times.GetMonth();
	curDate.day = times.GetDay();
	curTime.hour = times.GetHour();
	curTime.minute = times.GetMinute();
	curTime.second = times.GetSecond();

	bool val = pHistoryManager->GetConversationByConversationId(hisConversation, historyConvID);
	if (!val)
	{
		return -1L;
	}

	//如果是临时群，则设置参加人员列表
	if (_conv->propmap_[uc::model::conversation::ConvTempGroupUri] != "")//
	{
		std::map<std::string, uc::model::conversation::Participant*>& memberlist = _conv->members_;
		std::map<std::string, uc::model::conversation::Participant*>::iterator itor = memberlist.begin();
		ctk::xml::XMLOutStream xmlbody("temp");
		std::string uri;
		std::string name;
		for( ; itor!= memberlist.end(); ++itor )
		{
			if(itor != memberlist.begin())
			{
				uri += ",";
				name += ",";
			}
			uri += (*itor).second->contact_.uri_;
			name += (*itor).second->contact_.name_;
		}
		xmlbody["urilist"] << uri;
		xmlbody["namelist"] << name;
		std::string strParticipants = xmlbody.str();

		(void)hisConversation.SetParticipants(strParticipants);
	}

	uc::model::historydata::Record rcd;
	bool rcdVal = false;

	//如果条数达到1500条，则删除最旧的那条
	long long lastRcdID;
	int num = pHistoryManager->GetAllRecord(&lastRcdID);
	if (num >= 1500) //最大记录1500条
	{
		(void)pHistoryManager->RemoveRecordsByRecordId(lastRcdID);
	}

	if (bIsSend)
	{
		rcdVal = hisConversation.CreateOutgoingCallRecord(rcd, curDate, curTime, src, srcname);
	}
	else
	{
		rcdVal = hisConversation.CreateIncommingCallRecord(rcd, curDate, curTime, src, srcname);
	}

	if (rcdVal)
	{
		(void)rcd.ClearRead();

		//复用body字段，保存通话类型
		std::string rcdTypeStr = num2str<int>(bIsVideoCall);
		(void)rcd.ModifyBody(rcdTypeStr);

		return rcd.recordId;
	}
	return rcdID;
}

//音频转视频，具体操作  w00221920 2015-04-23
bool CIMConversation::AudioToVideoCall(bool bVideoCall)
{
	DEBUG_TRACE("convId:%d",bVideoCall);
    //音频呼叫，直接退出
    if (true != bVideoCall)
    {
		return false;
    }
    
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (NULL == pConv)
	{
		return false;
	}

	//已存在语音会话，判断视频状态，决定是否发起转视频操作
	if (false == pConv->HasSession(AudioVideo))
    {
		return false;
    }

	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));	
    if (NULL == pSess)
    {
		return false;
    }

    if (conversation::avchannel::ChannelInActive != pSess->videochannel_.GetChannelState())
	{
		return false;
    }

	//设置视频通道参数信息
	InitVideoParam();
	if (pSess->videochannel_.Start())
	{
		//m_VoiceStateDlg.SetUIMode(CIMVoiceMainWnd::VOICEMAIN_VIDEO_MODE);
		//m_VoiceStateDlg.UpdateCallState(CALL_WAIT_FOR_VIDEO_REQUEST_STATE);
#if 0
		//开启音频转视频超时定时器
		if(m_pTimerAudio2VideoTimer)
		{
			(void)KillTimer(IM_VIDEO_REQUEST_OVER_TIMER);
			m_pTimerAudio2VideoTimer = NULL;
		}


		if(NULL == m_pTimerAudio2VideoTimer)
		{
			m_pTimerAudio2VideoTimer = SetTimer(IM_VIDEO_REQUEST_OVER_TIMER, IM_VIDEO_REQUEST_OVER_TIME, NULL);
		}
#endif

	}
	else
	{
		//申请视频start返回失败，重设转视频按钮可用
		;
#if 0
		if(m_VoiceStateDlg.m_pVideoVoiceToolBarWnd &&
			m_VoiceStateDlg.m_pVideoVoiceToolBarWnd->m_pBtnAudio2Video)
		{
			(void)m_VoiceStateDlg.m_pVideoVoiceToolBarWnd->m_pBtnAudio2Video->EnableObject(TRUE, TRUE);
		}
#endif
	}

    return true;
}

void CIMConversation::GetP2PContact(uc::model::Contact& _contact)const
{
	DEBUG_TRACE("");
	UCClient* pClient = UCClient::GetClient();
	std::string selfuri = pClient->Self->selfInfo.uri_;

	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);

	if (!pConv || pConv->propmap_[conversation::ConvTempGroupUri] != "")
	{
		return;  //非P2P的会话,不提供此功能
	}

	conversation::Conversation::MemList_::iterator itor = pConv->members_.begin();
	while (itor != pConv->members_.end())
	{
		if (itor->second->contact_.uri_ != selfuri)
		{
			_contact = itor->second->contact_;
			if(_contact.uri_.empty())
			{
				_contact.uri_ = _contact.mobile_;
			}
			break;
		}
		++itor;
	}
}


void CIMConversation::InitVideoParam(bool b_needUpdata,bool b_AudioAccept)
{
	DEBUG_TRACE("");
	//TRACE_FUNC();
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if(!pConv)
	{
		return;
	}
	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

	if (pConv && pSess && pConv->propmap_[conversation::ConvConfIdentifier] == "")
	{
		//INFO_LOG()<<"InitVideoParam P2P Video";

		//HWND hwndBig = m_VoiceStateDlg.GetBigVideoWnd();
		//HWND hwndContact = m_VoiceStateDlg.GetContactVideoWnd(UCCLIENT()->Self->selfInfo.uri_);

		if (b_AudioAccept)
		{
			pSess->videochannel_.setVideoLocalWnd(NULL);//hwndContact;
			pSess->videochannel_.setVideoRemoteWnd(NULL);//hwndBig;
			pSess->datachannel_.setDataRemoteWnd(NULL);
		}
		else
		{
			pSess->videochannel_.setVideoLocalWnd(IMManager::Instance().m_hwndLocal);//hwndContact;
			pSess->videochannel_.setVideoRemoteWnd(IMManager::Instance().m_hwndRemote);//hwndBig;
			pSess->datachannel_.setDataRemoteWnd(IMManager::Instance().m_hwndData);
		}

		if(b_needUpdata)
		{
			if(!pSess->videochannel_.Update())
			{
				//do nothing
			}
			if(!pSess->datachannel_.Update())
			{
				//do nothing
			}
		}

		return;
	}

}



void CIMConversation::HangUpCall()
{
	DEBUG_TRACE("");
	//TRACE_FUNC();
	//INFO_LOG() << " hang up!";

	//if (m_VoiceStateDlg.IsConfCtrlEnable())
	//{
	//	HangUpConf();
	//}
	//插入一条历史记录
	//InsertCallHistory();

	
	//m_bSelfStart = FALSE;

	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (NULL == pConv)
	{
		//MANAGEIMDLG_INSTANCE().CloseDlg(m_dlgKey);
		return;
	}

	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

	if (pSess)
	{
		if(!pSess->videochannel_.Update())
		{
			//do nothing
		}
		if(!pSess->datachannel_.Update())
		{
			//do nothing
		}
		//disconnect channel state change signal
		pSess->videochannel_.ChannelStateChanged.disconnect_all();
		pSess->datachannel_.ChannelEventChanged.disconnect_all();

		pSess->StreamHolded_.disconnect_all();
		pSess->StreamConnected_.disconnect_all();
		//如果当前仍在振铃，先停止振铃
		//callid_ = StringUtility::str2num<long>(pSess->propmap_[conversation::AVSessionIdentifier]);
		//CPlayLocalWav::Instance().StopPlayCallRing(callid_);

		(void)pSess->Disconnect(); //挂断呼叫

		(void)pConv->RemoveSession(AudioVideo);

		//INFO_LOG() << "AudioVideo Disconnect";
	}


}

void CIMConversation::RejectCall()
{
	DEBUG_TRACE("");
	//TRACE_FUNC();
	//INFO_LOG() << " hang up!";

	//if (m_VoiceStateDlg.IsConfCtrlEnable())
	//{
	//	HangUpConf();
	//}
	//插入一条历史记录
	//InsertCallHistory();

	
	//m_bSelfStart = FALSE;

	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (NULL == pConv)
	{
		//MANAGEIMDLG_INSTANCE().CloseDlg(m_dlgKey);
		return;
	}

	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

	if (pSess && pSess->Reject())
	{
		//disconnect channel state change signal
		


		//如果当前仍在振铃，先停止振铃
		//callid_ = StringUtility::str2num<long>(pSess->propmap_[conversation::AVSessionIdentifier]);
		//CPlayLocalWav::Instance().StopPlayCallRing(callid_);

		//(void)pSess->Disconnect(); //挂断呼叫

		(void)pConv->RemoveSession(AudioVideo);

		//INFO_LOG() << "AudioVideo Disconnect";
	}


}


void CIMConversation::AcceptAudioCall()
{
	DEBUG_TRACE("");
	//TRACE_FUNC();
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	// 有出现pConv为空的情况
	if (NULL == pConv)
	{
		return;
	}

	std::map<std::string, Participant*>::iterator itor = pConv->members_.begin();
	UCClient* pClient = UCClient::GetClient();
	while(itor != pConv->members_.end() )
	{
		if ((0 == (*itor).first.compare("Anonymous")) && ((*itor).second->contact_.uri_ != pClient->Self->selfInfo.uri_) && (!PERM(uc::model::ClirOverride)))
		{
			(*itor).second->contact_.name_ = "Anonymous";
		}
		++itor;
	}

	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo) );
	if(pSess)
	{
		std::string strCallid = pSess->propmap_[AVSessionIdentifier];
		//CPlayLocalWav::Instance().StopPlayCallIncoming(callid);
	}

	//第三栏显示IMDlg, 当前提示窗口自动隐藏
	//CIMDlg* convHistory = MANAGEIMDLG_INSTANCE().GetIMDlgByConvIdentifier(convId);

	//发出信号先让当前呼叫进行保持操作
	//MANAGEIMDLG_INSTANCE().SendMsgToAllWnd(WM_IMDLG_HOLDCALL, uc::model::AudioVideo, convHistory);
	//Sleep(1000);

	AcceptIncomingAudioCall(pSess);
}

void CIMConversation::AcceptIncomingAudioCall(conversation::AVSession* pSess)
{
	DEBUG_TRACE("");
	if (pSess && (m_bAcceptedOwer ? TRUE : pSess->Accept()))
	{
		m_bHasAccepted = TRUE;
	}
}

void CIMConversation::AcceptVideoCall(bool isAudioAccet  /* = false */)
{
	DEBUG_TRACE("isAudioAccept:%d",isAudioAccet);
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if(!pConv)
	{
		return;
	}

	//INFO_LOG() << "AcceptCall: " << convId << " pConv: " << (LONG)pConv;

	std::map<std::string, Participant*>::iterator itor = pConv->members_.begin();
	UCClient* pClient = UCClient::GetClient();
	while(itor != pConv->members_.end() )
	{
		if ((0 == (*itor).first.compare("Anonymous")) && ((*itor).second->contact_.uri_ != pClient->Self->selfInfo.uri_) && (!PERM(uc::model::ClirOverride)))
		{
			(*itor).second->contact_.name_ = "Anonymous";
		}
		++itor;
	}

	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

	//区分语音转视频和直接收到视频呼叫两种场景
	if (pSess && (conversation::SessionConnected == pSess->state_) && !m_bAcceptedOwer/*非话机侧接起[---by k00191387---]*/)
	{
		AcceptVideoOffer();
	}
	else
	{
		AcceptIncomingVideoCall(pSess, isAudioAccet);
	}	
	
	m_bHasAccepted = TRUE;


}

void CIMConversation::AcceptVideoOffer()
{
	DEBUG_TRACE("");
	conversation::AVSession* pSess = IMManager::Instance().GetAVsessByConvId(m_convID);
	if (pSess)
	{
		InitVideoParam();
		if (pSess->videochannel_.Start())
		{
			OnCallConnect(0);

		}
	}
}

void CIMConversation::OnCallConnect(int sessiontype)
{

	DEBUG_TRACE("sessiontype:%d",sessiontype);
	//如果当前仍在放回铃音，先停止回铃音
	//StopPlayingCallRing();

	//int sessiontype = (int)lParam;
	//if (::IsWindow(m_VoiceStateDlg.GetSafeHwnd()))
	{
		//connect channel state signal
		//conversation::Conversation *pConv = MANAGEIMDLG_INSTANCE().GetCurConv(m_dlgKey);
		//sessiontype = pConv->sessiontype_;
		AVSession* pSess = IMManager::Instance().GetAVsessByConvId(m_convID);
		if (pSess)
		{
			m_VChanlStateChgSlot.m_IMConv = this;
			pSess->videochannel_.ChannelStateChanged.disconnect_all();
			if (!pSess->videochannel_.ChannelStateChanged.isconnected(&m_VChanlStateChgSlot) )
			{
				pSess->videochannel_.ChannelStateChanged.connect(&m_VChanlStateChgSlot, &VideoChnStateChgSigRev::OnChannelStateChanged);
			}
			/*添加辅流状态变化sigslot事件   z00220320*/
			m_DataChannelChgSlot.m_IMConv = this;
			if(!pSess->datachannel_.ChannelEventChanged.isconnected(&m_DataChannelChgSlot))
			{
				pSess->datachannel_.ChannelEventChanged.connect(&m_DataChannelChgSlot, &DataChnStateChgSigRev::OnDataChannelEvent);
			}
			/*被保持与恢复处理*/
			avSessionResumeslot_.m_IMConv = this;
			if(!pSess->StreamHolded_.isconnected(&avSessionBeHoldslot_))
			{
				pSess->StreamHolded_.connect(&avSessionBeHoldslot_,&AvSessionBeHoldSigRev::OnAvSessionBeHoldSigRes);
			}
			avSessionBeHoldslot_.m_IMConv = this;
			if (!pSess->StreamConnected_.isconnected(&avSessionResumeslot_))
			{
				pSess->StreamConnected_.connect(&avSessionResumeslot_,&AvSessionBeHoldSigRev::OnAvSessionResumeSigRes);
			}

		}
#if 0
		if( ((sessiontype & uc::model::conversation::MEDIA_SESSION_AUDIO) != 0) && ( 0 == (sessiontype & uc::model::conversation::MEDIA_SESSION_VIDEO)))
		{
			//only auido
			m_VoiceStateDlg.SetUIMode(CIMVoiceMainWnd::VOICEMAIN_AUDIO_MODE);

			//音频转视频图标，在上报video close消息时设置为可用
			if(m_VoiceStateDlg.m_pVideoVoiceToolBarWnd && m_VoiceStateDlg.m_pVideoVoiceToolBarWnd->m_pBtnAudio2Video)
			{
				(void)m_VoiceStateDlg.m_pVideoVoiceToolBarWnd->m_pBtnAudio2Video->EnableObject(TRUE,TRUE);
			}

		}
		else if( 0 != (sessiontype & uc::model::conversation::MEDIA_SESSION_VIDEO) && (0 == (sessiontype & uc::model::conversation::MEDIA_SESSION_AUDIO)))
		{
			//only video
			m_VoiceStateDlg.SetUIMode(CIMVoiceMainWnd::VOICEMAIN_VIDEO_MODE);
		}
		else if( (0 != (sessiontype & uc::model::conversation::MEDIA_SESSION_AUDIO)) && (0 != (sessiontype & uc::model::conversation::MEDIA_SESSION_VIDEO)))
		{
			//audio & video
			m_VoiceStateDlg.SetUIMode(CIMVoiceMainWnd::VOICEMAIN_VIDEO_MODE);
		}

		m_VoiceStateDlg.UpdateCallState(CALL_CONNECTED_STATE);
#endif	
	}

	return ;
}
#if 0
void CIMConversation::CreateConverSession(const std::vector<uc::model::Contact>& _list, const std::string& _fixgrpId)
{
	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;
	
	if(!ucclient || (_list.size()==0 && _fixgrpId == ""))
	{
		return;
	}

	conversation::Conversation* pConv = NULL;

	if(_list.size() == 1)
	{
		pConv = ucclient->ConvManager->GetConversationByContact(*(_list.begin()));
	}

	if (!pConv)
	{
		pConv = ucclient->ConvManager->AddConversation();
		
		if(!pConv)
		{
			return;
		}
	}

	std::string hisconvid = GetHisConvId();
	pConv->propmap_[conversation::ConvHistoryGroupUri] = hisconvid;

	if (_fixgrpId == "")
	{
		std::string strAccount = "";
		std::vector<uc::model::Contact>::const_iterator citb = _list.begin();

		while(citb != _list.end())
		{
			uc::model::Contact contact_ = (*citb);
			if (eSDKTool::IsValidUri(contact_.uri_))
			{
				strAccount = eSDKTool::GetNoFromUri(contact_.uri_);

			}
			else if( !contact_.mobile_.empty())
			{
				strAccount = contact_.mobile_;
			}
			contact_.ucAcc_ = strAccount;

			if (ucclient->ContactManager->HasContactByAccount(contact_.ucAcc_))
			{
				(void)ucclient->ContactManager->GetContactByAccount(contact_.ucAcc_, contact_);
			}

			if (contact_.name_.empty())
			{
				contact_.name_ = contact_.ucAcc_;
			}

			(void)pConv->AddParticipant(contact_);
			++citb;
		}

	}
	pConv->propmap_[conversation::ConvSubject] = eSDKTool::unicode_2_utf8(m_strSubject);
	m_convID = pConv->propmap_[conversation::ConvIdentifier];
}
#endif

void CIMConversation::AcceptIncomingVideoCall(conversation::AVSession* pSess, bool isAudioAccept/*=false*/)
{
	DEBUG_TRACE("");
	if (pSess)
	{     
		//设置视频通道参数信息
		m_VChanlStateChgSlot.m_IMConv = this;
		pSess->videochannel_.ChannelStateChanged.disconnect_all();
		if (!pSess->videochannel_.ChannelStateChanged.isconnected(&m_VChanlStateChgSlot) )
		{
			pSess->videochannel_.ChannelStateChanged.connect(&m_VChanlStateChgSlot, &VideoChnStateChgSigRev::OnChannelStateChanged);
		}

		InitVideoParam(FALSE, isAudioAccept);

		if (!pSess->Accept() && !m_bAcceptedOwer)
		{
			//接听失败，挂断呼叫
			(void)pSess->Disconnect();
			HangUpCall();
		}
	}

}


bool CIMConversation::StartSendData()
{
	DEBUG_TRACE("");
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (pConv && pConv->HasSession(AudioVideo) )
	{
		conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

		if (pSess && pConv->propmap_[conversation::ConvTempGroupUri] == "")
		{
			pSess->datachannel_.setDataCaptureWnd(m_hwndShared);
			if(pSess->datachannel_.Start())
			{
				return true;
			}
		}
	}

	return false;
}

bool CIMConversation::StopSendData()
{
	DEBUG_TRACE("");
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (pConv && pConv->HasSession(AudioVideo) )
	{
		conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

		if (pSess && pConv->propmap_[conversation::ConvTempGroupUri] == "")
		{
			if(pSess->datachannel_.Stop())
			{
				return true;
			}
		}
	}

	return false;
}

bool CIMConversation::StartRecvData()
{
	DEBUG_TRACE("");
	conversation::AVSession* pSess = IMManager::Instance().GetAVsessByConvId(m_convID);
	if (pSess)
	{
		OnCallConnect(0);
		InitVideoParam();
		if(!pSess->videochannel_.Update())
		{
			//do nothing
		}
		if(pSess->datachannel_.StartRecv())
		{
			m_bIsDataReceiving=true;
			return true;
		}
	}

	return false;
}


bool CIMConversation::StopRecvData()
{
	DEBUG_TRACE("");
	InitVideoParam(TRUE);
	conversation::AVSession* pSess = IMManager::Instance().GetAVsessByConvId(m_convID);
	if (pSess)
	{

		if(m_bIsDataReceiving)//正在接收
		{
			m_bIsDataReceiving=false;
			OnCallConnect(0);
			InitVideoParam(TRUE);
			return true;
		}
	}

	return false;
}


bool CIMConversation::RejectRecvData()
{
	DEBUG_TRACE("");
	return StopSendData();
}


/*******************************************************************************
* 函数名称 : OnChannelStateChanged
* 函数描述 : 视频ChannelState变化上报处理
* 输入参数 : conversation::avchannel::ChannelState _state, conversation::Session* _pSess
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
void VideoChnStateChgSigRev::OnChannelStateChanged(conversation::avchannel::ChannelState _state, conversation::Session* _pSess)
{
	DEBUG_TRACE("");
	const TE_S_CALL_STATE_INFO *p_CallStateInfo = CTERegMgr::Instance().GetCallStateInfo();
	
	if(p_CallStateInfo)
	{
		//memcpy(&CallStateInfo,p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
		hw::memcpy_s(&CallStateInfo,sizeof(TE_S_CALL_STATE_INFO),p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
	}

	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_IMConv->GetConvId());


	if ( 0 != (pConv->sessiontype_ & MEDIA_SESSION_VIDEO))
	{
		CallStateInfo.enCallType =  TE_E_CALL_TYPE_IPVIDEO;
	}
	else
	{
		CallStateInfo.enCallType =  TE_E_CALL_TYPE_IPAUDIO;				

	}


	if (conversation::avchannel::ChannelConnecting == _state)
	{
		//对方请求开启视频

		//CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		CallStateInfo.enCallEvent=TE_E_CALL_EVENT_OPEN_VEDIO;
		CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));

	}

	if (conversation::avchannel::ChannelSendReceive == _state)
	{
		if(pConv)
		{
				//对端关闭摄像头
			conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));
			if(pSess && 2 == pSess->videochannel_.iVideoClosedReason)
			{
				//::PostMessage(convHistory->GetSafeHwnd(), WM_IM_P2P_CAMERA_CLOSED, NULL, NULL);
				//CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
				CallStateInfo.enCallEvent=TE_E_CALL_EVENT_ANSWER_VEDIO;
				CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
			}
			else
			{
				CallStateInfo.enCallEvent=TE_E_CALL_EVENT_ANSWER_VEDIO;
				CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
			}
		}
	}

	if (conversation::avchannel::ChannelInActive == _state)
	{
		if(pConv)
		{
			CallStateInfo.enCallEvent=TE_E_CALL_EVENT_CLOSE_VEDIO;
			CEventMgr::Instance().OnEventCallBack(TE_E_EVT_CALL_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		}
	}
}

TE_UINT32 DataChnStateChgSigRev::GetCallID(conversation::Conversation* _con)
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
* 函数名称 : OnDataChannelEvent
* 函数描述 : 辅流ChannelEvent事件上报处理
* 输入参数 : conversation::avchannel::DataChannelEvent _state, conversation::Session* _pSess,int iRspCode
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
void DataChnStateChgSigRev::OnDataChannelEvent(conversation::avchannel::DataChannelEvent _state, conversation::Session* _pSess,int iRspCode)
{
	DEBUG_TRACE("");
	//TRACE_FUNC1(_state);

	//CIMDlg* convHistory = dynamic_cast<CIMDlg*>(m_wnd);
	const TE_S_CALL_STATE_INFO *p_CallStateInfo = CTERegMgr::Instance().GetCallStateInfo();

	if(p_CallStateInfo)
	{
		//memcpy(&CallStateInfo,p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
		hw::memcpy_s(&CallStateInfo,sizeof(TE_S_CALL_STATE_INFO),p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
	}
	
	conversation::Conversation* pConv = _pSess->pConv_;

	if(NULL!=pConv)
	{
		if(conversation::avchannel::DataSending == _state)
		{
			//发送辅流申请成功

			CallStateInfo.enDataEvent = TE_E_DATA_EVENT_DATASEND;
			CallStateInfo.ulCallID = GetCallID(pConv);

			CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		}

		if(conversation::avchannel::DataRecving == _state)
		{
			//对方发送辅流请求

			CallStateInfo.enDataEvent = TE_E_DATA_EVENT_DATARECIEVE;
			CallStateInfo.ulCallID = GetCallID(pConv);

			CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		}

		if(conversation::avchannel::DataStoped == _state)
		{
			//辅流停止请求

			CallStateInfo.enDataEvent = TE_E_DATA_EVENT_DATASTOPED;
			CallStateInfo.ulCallID = GetCallID(pConv);

			CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		}

		if(conversation::avchannel::DataStartFailure == _state)
		{
			//发送辅流请求失败

			CallStateInfo.enDataEvent = TE_E_DATA_EVENT_DATASENDFAILURE;
			CallStateInfo.ulCallID = GetCallID(pConv);
			
			CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
		}
	}
}


//被保持和恢复 事件上报
void AvSessionBeHoldSigRev::OnAvSessionBeHoldSigRes(uc::model::conversation::AVSession * pAVSession)
{
	DEBUG_TRACE("");
	//CIMDlg* convHistory = dynamic_cast<CIMDlg*>(m_wnd);
	//::PostMessage(convHistory->GetSafeHwnd(), WM_IM_BEHOLD_RESULT, NULL,
	//	(LPARAM)(CIMDlg::CALL_HOLDED_STATE));
	const TE_S_CALL_STATE_INFO *p_CallStateInfo = CTERegMgr::Instance().GetCallStateInfo();

	if(p_CallStateInfo)
	{
		//memcpy(&CallStateInfo,p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
		hw::memcpy_s(&CallStateInfo,sizeof(TE_S_CALL_STATE_INFO),p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
	}
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
}

void AvSessionBeHoldSigRev::OnAvSessionResumeSigRes(uc::model::conversation::AVSession* pAVSession)
{
	DEBUG_TRACE("");
	//CIMDlg* convHistory = dynamic_cast<CIMDlg*>(m_wnd);
	//::PostMessage(convHistory->GetSafeHwnd(), WM_IM_BEHOLD_RESULT, NULL,
	//	(LPARAM)(CIMDlg::CALL_CONNECTED_STATE));
	const TE_S_CALL_STATE_INFO *p_CallStateInfo = CTERegMgr::Instance().GetCallStateInfo();

	if(p_CallStateInfo)
	{
		//memcpy(&CallStateInfo,p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
		hw::memcpy_s(&CallStateInfo,sizeof(TE_S_CALL_STATE_INFO),p_CallStateInfo,sizeof(TE_S_CALL_STATE_INFO));
	}
	CEventMgr::Instance().OnEventCallBack(TE_E_EVT_DATA_RESULT,&CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));
}
