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
 * @file  EventMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manager Event Class
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#ifndef EVENT_MGR_H
#define EVENT_MGR_H

#include "SignalRecvProcess.h"
#include "IM.h"

#include "stdafx.h"
/***************************************************
 * @class CEventMgr
 * @brief Handle Event for callback
 * @details 
***************************************************/
class CEventMgr
{
public:
	static inline CEventMgr& Instance()
	{
		static CEventMgr inst;
		return inst;
	}
public:
    CEventMgr(void);
    ~CEventMgr(void);

    int SetEventCallBack( EventCallBack fEventCallBack = NULL, void *pUserData = NULL );
	int OnEventCallBack(int iEventType, void* pEventData, int iBufSize);
	//static void *HandleEventThread(void *argc);

private:
	EventCallBack  m_EventCallBack;
	void*          m_EventUserData;
public:
	SignalRecvProcess m_Signalslot;
	

};
#endif //EVENT_MGR_H