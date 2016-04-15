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
 * @file  IMMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manage conversation session
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#ifndef _TE_IM_MGR_H_
#define _TE_IM_MGR_H_
#include "IM.h"
#include "stdafx.h"

#define IM_EMPTY_DLGKEY  "empty"
class CIMConversation;
typedef ctk::mt::map<std::string, CIMConversation*> _IMConversations;
class IMManager
{
public:
	IMManager();
	~IMManager();
	static IMManager& Instance()
	{
		return *ctk::Singleton_T<IMManager>::instance(CTK_CURRENT);
	}
public:
	conversation::Conversation* GetCurConv(const std::string& _convId)const;
	//conversation::AVSession* GetAVsessByConvId(void) const;
	//conversation::AVSession* GetAVsessByConvId(const std::string& _convId)const;
	void FilterInvaildContact(std::vector<uc::model::Contact>& _clist) const;


	void setDisplayHandle(HWND  localWnd, HWND  remote_wnd,HWND hwndData);
	
	//bool m_HasAudioVideo;
	bool HasAudioVideo();
	bool HasAudioOrVideoInUse(std::string strConvID);
	bool IsValidUri(const std::string& uri);
	bool HasAudioOrVideoInUse();
	bool GetPeerInfo(const std::string &csvId, uc::model::Contact& contact)const;
	std::string GetNoFromUri(const std::string & uri);
	CIMConversation* CreateConverSession(CallParam* _param);
	CIMConversation* GetConversationExist(CallParam* _param);
	CIMConversation* GetIMConvByHistoryID(const std::string& _historyid)const;
	CIMConversation* GetIMConvByConvId(const std::string& _convid)const;
	CIMConversation* GetIMConvByP2PContact(const uc::model::Contact& _contact)const;
	conversation::AVSession* GetAVsessByConvId(const std::string& _convId) const;
	CIMConversation* GetIMConvByCallID(TE_UINT32 callId) const;
	CIMConversation* GetNewConversation(CallParam* _param, HWND _parent, BOOL _popup);
	//bool m_bAcceptedOwer;//话机联动场景，1:话机接听 0:PC接听
	//bool m_bHasAccepted;//是否已经处理
	_IMConversations convmap_;


	HWND m_hwndLocal;
	HWND m_hwndRemote;
	HWND m_hwndData;


};


#endif
