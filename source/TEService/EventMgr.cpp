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
 * @file  EventMgr.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manager Event Class
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#include "stdafx.h"
#include "EventMgr.h"
#include "TERegMgr.h"
#include "Log.h"
#include "AddContacts.h"
#include "TESDK.h"

CEventMgr::CEventMgr(void)
{
	m_EventCallBack = NULL;
	m_EventUserData = NULL;
}

CEventMgr::~CEventMgr(void)
{
   m_EventCallBack = NULL;
   m_EventUserData = NULL;
}

int CEventMgr::SetEventCallBack( EventCallBack fEventCallBack /*= NULL*/, void *pUserData /*= NULL*/ )
{
	DEBUG_TRACE("");
    //记录回调函数;
    m_EventCallBack = fEventCallBack;
    m_EventUserData = pUserData;

    //pUserMgr->SetEventCallBack(EventCallBackFun, (void*)iSessionID);
    //SetLocalFilePlayBackEventCallBack(EventCallBackFun, (void*)iSessionID);

    return TE_SDK_Success;
}

//异步的回调
int CEventMgr::OnEventCallBack(int iEventType, void* pEventData, int iBufSize)
{
	DEBUG_TRACE("type:%d",iEventType);
    switch(iEventType)
    {
		case TE_E_EVT_LOGIN_RESULT:
		{
			if (TE_E_LOGIN_SUCCESS == CTERegMgr::Instance().m_LoginResult.loginState)
			{
				UCClient* clients = UCClient::GetClient();
				int ret;
				if (!clients)
				{
					return TE_SDK_NullPtr;
				}
				ret = clients->DeviceManager->Uninit();
				if ( ret )
				{
					ERROR_LOG("DeviceManager Uninit fail.");
				}
				ret = clients->DeviceManager->Init();
				if( ret )
				{
					ERROR_LOG("DeviceManager Init fail.");
				}
			}
			break;
		}
		case TE_E_EVT_CALL_RESULT:
		{
			TE_S_CALL_STATE_INFO *pCallStateInfo = new TE_S_CALL_STATE_INFO;
			if (pCallStateInfo!=NULL)
			{
				//memcpy(pCallStateInfo, pEventData, sizeof(TE_S_CALL_STATE_INFO));
				hw::memcpy_s(pCallStateInfo,sizeof(TE_S_CALL_STATE_INFO), pEventData, sizeof(TE_S_CALL_STATE_INFO));
				if (TE_E_CALL_EVENT_ANSWERRSP == pCallStateInfo->enCallEvent)
				{
					CIMConversation::Instance().InitVideoParam(true);
				}
				delete pCallStateInfo;
			}
			
			break;
		}
		case TE_E_EVT_DATA_RESULT:
		{
			TE_S_CALL_STATE_INFO *pCallStateInfo = new TE_S_CALL_STATE_INFO;
			if (pCallStateInfo!=NULL)
			{
				//memcpy(pCallStateInfo, pEventData, sizeof(TE_S_CALL_STATE_INFO));
				hw::memcpy_s(pCallStateInfo,sizeof(TE_S_CALL_STATE_INFO), pEventData, sizeof(TE_S_CALL_STATE_INFO));
				if (TE_E_DATA_EVENT_DATARECIEVE == pCallStateInfo->enDataEvent)
				{
					CIMConversation::Instance().InitVideoParam(true);
				}
				delete pCallStateInfo;
			}

			break;
		}
		case TE_E_EVT_ENTERPRISE_RESULT:
		{
			TE_S_CONTACTS_INFO contactsList; 	
			contactsList.contact = NULL;
			contactsList.num = 0;
			TE_UINT32 i=0;
			CAddrContacts::Instance().SearchContactFinish(CTERegMgr::Instance().GetLdapResult()->restInfo.pResult,&contactsList);
			if(contactsList.contact == NULL)
			{
				break;
			}
			CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact = (TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contactsList.num);
			for(i=0;i<contactsList.num;i++)
			{
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].name, contactsList.contact[i].name,TE_D_NAME_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].addresssite , contactsList.contact[i].addresssite,TE_D_ADDRESS_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].deptname , contactsList.contact[i].deptname,TE_D_DEPARTNAME_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].email,contactsList.contact[i].email,TE_D_EMAIL_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].officePhone,contactsList.contact[i].officePhone,TE_D_PHONE_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].mobile,contactsList.contact[i].mobile,TE_D_PHONE_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].ucAcc,contactsList.contact[i].ucAcc,TE_D_NUMBER_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].description,contactsList.contact[i].description,TE_D_DESCRIPTION_LEN);
				strncpy(CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.contact[i].nickname,contactsList.contact[i].nickname,TE_D_NAME_LEN);
			}
			CTERegMgr::Instance().GetLdapResult()->restInfo.enterpriseContacts.num = contactsList.num;
			free(contactsList.contact);
			break;
		}
		case TE_E_EVT_USER_STATUS:
		{
			break;
		}
		default:
		{
			break;
		}
    }
    
    EventCallBack fEventCallBack = m_EventCallBack;
    if (NULL != fEventCallBack)
    {
        fEventCallBack(iEventType, pEventData, static_cast<TE_UINT32>(iBufSize), m_EventUserData);
		//BP_DBG_LOG("fEventCallBack End, EventType: %d, SessionID: %d, EventData: %p, BufSize: %d", 
		//	iEventType, iSessionID, pEventData, iBufSize);
    }
	else
	{
		//fEventCallBack(iEventType, pEventData, static_cast<TE_UINT32>(iBufSize), m_EventUserData);
		//BP_RUN_LOG_ERR(IVS_FAIL, "OnEventCallBack", "fEventCallBack is null.");
	}
    return TE_SDK_Success;
}

#if 0
CEventMgr::~CEventMgr(void)
{
	if(NULL != m_pQueueMutex)
	{
		VOS_DestroyMutex(m_pQueueMutex);
		m_pQueueMutex = NULL;
	}
	if(NULL !=  m_pIsStartMutex)
	{
		VOS_DestroyMutex(m_pIsStartMutex);
		m_pIsStartMutex = NULL;
	}	
}

void *CEventMgr::HandleEventThread(void *argc)
{
	INFO_LOG("HandleEvent Thread Start.");
	CUCEventMgr* pEmgr = (CUCEventMgr*)argc;
	if(NULL == pEmgr)
	{
		return NULL;
	}
	UCEvent* pEvent = NULL;
	bool bIsStart = pEmgr->GetIsStart();
	while(bIsStart)
	{
		pEvent = pEmgr->PopEvent();
		if(NULL != pEvent)
		{
			if(!pEvent->DoHandle())
			{
				ERROR_LOG("Process Event Failed.");
			}
			SAFE_DELETE(pEvent);
		}

		Sleep(200);

		bIsStart = pEmgr->GetIsStart();
		if(!bIsStart)
		{
			break;
		}
	}

	INFO_LOG("HandleEvent Thread End.");
	return NULL;
}
#endif