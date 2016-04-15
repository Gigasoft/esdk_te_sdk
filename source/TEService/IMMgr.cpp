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
 * @file  IMMgr.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manage conversation session
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/

#include "stdafx.h"
#include "IMMgr.h"
#include "TERegMgr.h"
#include "Log.h"

conversation::Conversation* IMManager::GetCurConv(const std::string& _convId) const
{
	DEBUG_TRACE("convid:%s",_convId.c_str());
	conversation::Conversation* pConv=NULL;
	UCClient* clients = UCClient::GetClient();

	if(clients && clients->ConvManager)
	{
		pConv = clients->ConvManager->GetConversation(_convId);
	}
	
	return pConv;
}


conversation::AVSession* IMManager::GetAVsessByConvId(const std::string& _convId) const
{
	DEBUG_TRACE("convid:%s",_convId.c_str());
	conversation::Conversation* pConv = GetCurConv(_convId);
	if (!pConv || !pConv->HasSession(AudioVideo) )
	{
		//找不到对应的会话或是语音session不能存在
		return NULL;
	}

	conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));

	return pSess;
}



void IMManager::FilterInvaildContact(std::vector<uc::model::Contact>& _clist) const
{
	DEBUG_TRACE("");
	std::vector<uc::model::Contact>::iterator itor = _clist.begin();
	while (itor != _clist.end())
	{
		if (!eSDKTool::IsValidUri(itor->uri_) && itor->mobile_.empty())
		{
			itor = _clist.erase(itor);
			continue;
		}

		++itor;
	}
}

CIMConversation* IMManager::GetNewConversation(CallParam* _param, HWND _parent, BOOL _popup)
{
	DEBUG_TRACE("");
	CIMConversation* pIMConv=NULL ;
#if 0
	CIMConversation* pDlg = new CIMConversation;
	if (NULL == pDlg)
	{
		return NULL;
	}

	if (!_param)
	{
		//标明是空窗口
		//pDlg->m_bEmptyWnd = TRUE;
	}

	if (_param)
	{
		if (!_param->convId.empty())
		{
			pDlg->SetConvId(_param->convId);
		}

		if (!_param->history_convId.empty())
		{
			pDlg->SetHisConvId(_param->history_convId);  //设置关联历史会话ID
		}
	}

	INFO_LOG("Created CIMDlg...");
#endif
	if (_param && _param->convId.empty())
	{
		pIMConv = IMManager::Instance().CreateConverSession(_param);
	}

	//convmap_.put(pDlg->GetConvId(), pDlg);

	//包文祥添加，解决按conversationid打开IM时，名称显示不对的问题
	if (_param && !_param->convId.empty())
	{
		if (pIMConv)
		{
			pIMConv->UpdateDlg();
		}
	}
	return pIMConv;
}


void CIMConversation::UpdateDlg()
{
	DEBUG_TRACE("");
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	if (!pConv)
	{
		WARN_LOG("Conv is NULL, can't update dlg");
		return;
	}
	if (pConv->propmap_[conversation::ConvTempGroupUri].empty()&& pConv->propmap_[conversation::ConvConfIdentifier].empty()&&m_hisConvID .empty())
	{
		UpdateIMDlgSingleChat();
	}

}

void CIMConversation::UpdateIMDlgSingleChat()
{
	DEBUG_TRACE("");
	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(m_convID);
	UCClient *pClient = UCClient::GetClient();

	if (pConv && pClient)
	{
		Contact contact_;
		GetP2PContact(contact_);
		
		if (!contact_.uri_.empty())
		{
			Contact tempContactInfo;
			if(UCCLIENT()->ContactManager->GetContactByUri(contact_.uri_, tempContactInfo))
			{
				CString strSig = eSDKTool::utf8_2_unicode(tempContactInfo.signature_);
			}
		}
	}
}

CIMConversation* IMManager::GetConversationExist(CallParam* _param)
{
	DEBUG_TRACE("");
	CIMConversation*  p_IMConv = NULL;
	if (_param)
	{
		//增加判断已有会话窗口是否打开
		if (!_param->convId.empty())
		{
			p_IMConv = IMManager::Instance().GetIMConvByConvId(_param->convId);
			if (p_IMConv)
			{
				return p_IMConv;
			}
		}

		if (1 == _param->memlist.size())
		{
			//检查当前是否已经存在此点对点聊天的窗口
			p_IMConv = GetIMConvByP2PContact(*(_param->memlist.begin()));
			if (p_IMConv)
			{
				return p_IMConv;
			}
		}
		
		if (!_param->history_convId.empty())
		{
			p_IMConv = GetIMConvByHistoryID(_param->history_convId);
			if (p_IMConv)
			{
				return p_IMConv;
			}
		}

	}
	p_IMConv = GetNewConversation(_param,  NULL, false);
	CIMConversation::CreateConvHistory(_param, p_IMConv);
	
	return p_IMConv;

}

CIMConversation* IMManager::GetIMConvByHistoryID(const std::string& _historyid)const
{
	DEBUG_TRACE("historyid:%s",_historyid.c_str());
	//TRACE_FUNC1(_historyid);
	std::list<CIMConversation*> imconvlist;
	convmap_.getValueList(imconvlist);
	std::list<CIMConversation*>::iterator itor = imconvlist.begin();
	while (itor != imconvlist.end())
	{
		if ((*itor)->GetHisConvId() == _historyid)
		{
			return (*itor);
		}

		itor++;
	}

	return NULL;
}

CIMConversation* IMManager::GetIMConvByConvId(const std::string& _convId)const
{
	DEBUG_TRACE("convid:%s",_convId.c_str());
	if (_convId != "")
	{
		if (convmap_.has(_convId))
		{
			//INFO_LOG()<<"find a IMDlg。";
			CIMConversation* pIMConv = NULL;
			(void)convmap_.get(_convId, pIMConv);
			return pIMConv;
		}
	}

	return NULL;
}


CIMConversation* IMManager::GetIMConvByP2PContact(const uc::model::Contact& _contact)const
{
	DEBUG_TRACE("");
	std::list<CIMConversation*> imconvlist;
	convmap_.getValueList(imconvlist);
	std::list<CIMConversation*>::iterator itor = imconvlist.begin();
	while (itor != imconvlist.end())
	{
		conversation::Conversation* pConv = IMManager::Instance().GetCurConv((*itor)->GetConvId());
		if (pConv && pConv->propmap_[conversation::ConvTempGroupUri] == "" 
			&& pConv->propmap_[conversation::ConvConfIdentifier] == ""
			&& pConv->propmap_[conversation::ConvHistoryGroupUri] == ""
			&& pConv->HasParticipant(_contact))
		{
			return (*itor);
		}
		itor++;
	}
	return NULL;
}

bool IMManager::HasAudioOrVideoInUse(std::string strDlgKey)
{
	DEBUG_TRACE("key:%s",strDlgKey.c_str());
	std::list<CIMConversation*> convlist_;
	convmap_.getValueList(convlist_);
	std::string dlgKey = "";

	std::list<CIMConversation*>::iterator itor = convlist_.begin();
	for (;itor != convlist_.end(); ++itor)
	{
		if ((*itor))
		{
			dlgKey = (*itor)->GetConvId();

			//不判断发起的对话框
			if ( strDlgKey == dlgKey )
			{
				continue;
			}

			conversation::Conversation* pConv = GetCurConv(dlgKey);
			if (pConv && pConv->HasSession(AudioVideo))
			{
				SessionState enState = pConv->GetSession(AudioVideo)->state_;
				//除了挂起以外的其他状态都返回true
				if ( enState != SessionOnHold && enState != SessionDisconnected)
				{
					return true;
				}
			}
		}
	}
	return false;	
}

std::string IMManager::GetNoFromUri(const std::string & uri)
{
	DEBUG_TRACE("uri:%s",uri.c_str());
	//从uri解析号码，若非uri返回号码
	std::string::size_type pos1 = uri.find("sip:");

	if(pos1!= std::string::npos)
	{
		//对于"号码@ip地址"的场景之前不兼容
		std::string::size_type pos2 = uri.rfind("@");
		//std::string::size_type pos2 = uri.find("@");
		if(pos2 != std::string::npos)
		{
			if(4 == pos2)
			{
				return "";
			}
			else
			{
				return uri.substr(pos1+4, pos2-pos1-4);
			}
		}
		else
		{
			return uri.substr(pos1+4);
		}
	}
	else
	{
		return uri;
	}
}



bool  IMManager::GetPeerInfo(const std::string &csvId, uc::model::Contact& contact)const
{
	DEBUG_TRACE("csvid:%s",csvId.c_str());
	uc::model::UCClient* pClient =uc::model::UCClient::GetClient();
	uc::model::conversation::Conversation* pConv = 
		IMManager::Instance().GetCurConv(csvId);
	if(!pConv)
	{
		return FALSE;
	}

	uc::model::historydata::HistoryManager *pHistoryManager = uc::model::historydata::HistoryManager::Instance();
	uc::model::historydata::Conversation Conversations;		//lint !e1075

	if(!pConv->propmap_[conversation::ConvTempGroupUri].empty())
	{
		return FALSE;
	}
	std::map<std::string, Participant*>& memberlist = pConv->members_;
	std::map<std::string, Participant*>::iterator itor = memberlist.begin();

	for(; itor!= memberlist.end(); ++itor)
	{
		//遍历成员列表第一个与本端不同的uri作为对方的uri_
		if((*itor).first != pClient->Self->selfInfo.uri_)
		{
			bool bRet;
			std::string strContactUri = (*itor).second->contact_.uri_;

			if (IMManager::Instance().IsValidUri(strContactUri))
			{
				bRet = pClient->ContactManager->GetContactByUri(strContactUri, contact);
			}
			else
			{
				if(strContactUri.empty())
				{
					bRet = pClient->ContactManager->GetContactByAccount((*itor).second->contact_.mobile_, contact);
				}
				else
				{
					bRet = pClient->ContactManager->GetContactByAccount(strContactUri, contact);
				}

				contact.uri_ = (*itor).first;
			}

			if(!bRet)
			{
				contact.uri_ = (*itor).first;
				contact.mobile_ = contact.uri_;

				if(pHistoryManager->GetConversationByConversationId(Conversations, contact.uri_))
				{
					contact.name_ = Conversations.participants;
				}

			}
			break;
		}
	}
	return TRUE;
}

bool IMManager::IsValidUri(const std::string& uri)
{
	DEBUG_TRACE("uri:%s",uri.c_str());
	size_t nSip = uri.find("sip:");
	if (nSip != 0) //必须以sip:开头
	{
		return false;
	}
	return true;
}

bool IMManager::HasAudioOrVideoInUse()
{
	DEBUG_TRACE("");
	std::list<CIMConversation*> convlist_;
	convmap_.getValueList(convlist_);
	std::string dlgKey = "";

	std::list<CIMConversation*>::iterator itor = convlist_.begin();
	for (;itor != convlist_.end(); ++itor)
	{
		if ((*itor))
		{
			dlgKey = (*itor)->GetConvId();

			conversation::Conversation* pConv = GetCurConv(dlgKey);
			if (pConv && pConv->HasSession(AudioVideo))
			{
				SessionState enState = pConv->GetSession(AudioVideo)->state_;
				if ( enState != SessionOnHold && enState != SessionDisconnected)
				{
					return true;
				}
			}
		}
	}
	return false;	
}


bool IMManager::HasAudioVideo()
{
	DEBUG_TRACE("");
	std::list<CIMConversation*> convlist_;
	convmap_.getValueList(convlist_);
	std::string convID = "";

	std::list<CIMConversation*>::iterator itor = convlist_.begin();
	while (itor != convlist_.end())
	{
		if ((*itor) )
		{
			convID = (*itor)->GetConvId();
			conversation::Conversation* pConv = GetCurConv(convID);
			if (pConv && pConv->HasSession(AudioVideo))
			{
				return true;
			}
		}
		++itor;
	}

	return false;
}

CIMConversation* IMManager::GetIMConvByCallID(TE_UINT32 callId) const
{
	DEBUG_TRACE("callid:%d",callId);
	std::list<CIMConversation*> imconvlist;
	convmap_.getValueList(imconvlist);
	std::list<CIMConversation*>::iterator itor = imconvlist.begin();
	while (itor != imconvlist.end())
	{
		conversation::Conversation* pConv = IMManager::Instance().GetCurConv((*itor)->GetConvId());
		if (pConv &&  pConv->HasSession(AudioVideo))	
		{
			conversation::AVSession* pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo)); 
			if (pSess && eSDKTool::str2num<TE_UINT32>(pSess->propmap_[conversation::AVSessionIdentifier]) == callId)
				return (*itor);
		
		}
		itor++;
	}
	return NULL;
}


CIMConversation* IMManager::CreateConverSession(CallParam* _param)//const std::vector<uc::model::Contact>& _list, const std::string& _fixgrpId)
{
	DEBUG_TRACE("");
	CIMConversation *pIMConv = new CIMConversation;
	
	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;
	
	if (NULL == pIMConv)
	{
		return NULL;
	}

	if (!ucclient || (_param->memlist.size() == 0 && _param->fixgrpId == ""))
	{
		delete pIMConv;
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
	else
	{
		delete pIMConv;
		return NULL;
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
	pIMConv->m_hisConvID = _param->history_convId;
	convmap_.put(pIMConv->m_convID,pIMConv);
	return pIMConv;
}


void IMManager::setDisplayHandle(HWND  localWnd, HWND  remote_wnd,HWND hwndData)
{
	DEBUG_TRACE("");
	m_hwndLocal=localWnd;
	m_hwndRemote=remote_wnd;
	m_hwndData=hwndData;
}

IMManager::IMManager()
:m_hwndLocal(NULL)
,m_hwndRemote(NULL)
,m_hwndData(NULL)
{
	
}

IMManager::~IMManager()
{
	try
	{
		m_hwndLocal = NULL;
		m_hwndRemote = NULL;
		m_hwndData = NULL;
		convmap_.clear();
	}
	catch (...)
	{
		
	}
	
}