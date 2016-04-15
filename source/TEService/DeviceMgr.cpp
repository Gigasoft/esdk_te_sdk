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
 * @file  DeviceMgr.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manager Device Class
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#include "stdafx.h"
#include "DeviceMgr.h"
#include "IMMgr.h"
#include "Log.h"

CDeviceMgr::CDeviceMgr(void)
{

}

CDeviceMgr::~CDeviceMgr(void)
{
   
}

int CDeviceMgr::SetLocalVideo(TE_UINT32 callId, bool flag )
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,flag:%d",callId,flag);
	DEBUG_TRACE("set local video:%s",strParameter);
	CIMConversation* p_IMConv;
	//int ret;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return TE_SDK_NotFoundCallID;
	}
	AVSession* pSess = IMManager::Instance().GetAVsessByConvId(p_IMConv->m_convID);

	if (pSess)
	{
		if (false == flag)
		{
			if(!pSess->CloseLocalVideo())
			{
				//do nothing
				return TE_SDK_NotInit;
			}
		}
		else if (true == flag)
		{
			if(!pSess->OpenLocalvideo())
			{
				//do nothing
				return TE_SDK_NotInit;
			}
		}
		else
		{
			return TE_SDK_InvalidPara;
		}

	}
	else
	{
		return TE_SDK_NullPtr;

	}

    return TE_SDK_Success;
}



int CDeviceMgr::SetLocalMic(TE_UINT32 callId,bool flag)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,flag:%d",callId,flag);
	DEBUG_TRACE("set local mic:%s",strParameter);
	CIMConversation* p_IMConv;
	//int ret;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return TE_SDK_NotFoundCallID;
	}
	
	AVSession* pSess = IMManager::Instance().GetAVsessByConvId(p_IMConv->m_convID);

	if (pSess)
	{
		if (false == flag)
		{
			if(!pSess->UnMuteMic())
			{
				//do nothing
				return TE_SDK_NotInit;
			}
		}
		else if (true == flag)
		{
			if(!pSess->MuteMic())
			{
				//do nothing
				return TE_SDK_NotInit;
			}
		}
		else
		{
			return TE_SDK_InvalidPara;
		}

	}
	else
	{
		return TE_SDK_NullPtr;

	}

    return TE_SDK_Success;
}


int CDeviceMgr::SetLocalSpeaker(TE_UINT32 callId,bool flag)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,flag:%d",callId,flag);
	DEBUG_TRACE("set local speaker:%s",strParameter);
	CIMConversation* p_IMConv;
	//int ret;
	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		return TE_SDK_NotFoundCallID;
	}
	AVSession* pSess = IMManager::Instance().GetAVsessByConvId(p_IMConv->m_convID);

	if (pSess)
	{
		if (false == flag)
		{
			if(!pSess->UnMuteSpeaker())
			{
				//do nothing
				return TE_SDK_NotInit;
			}
		}
		else if (true == flag)
		{
			if(!pSess->MuteSpeaker())
			{
				//do nothing
				return TE_SDK_NotInit;
			}
		}
		else
		{
			return TE_SDK_InvalidPara;
		}

	}
	else
	{
		return TE_SDK_NullPtr;

	}

    return TE_SDK_Success;

}

int CDeviceMgr::OpenLocalVideoPreview(HWND  localWnd, TE_ULONG devIndex)
{
	DEBUG_TRACE("devIndex:%ld",devIndex);
	uc::model::device::PreviewWndParam wndPara;
	UCClient* clients = UCClient::GetClient();
	bool ret=false;
	wndPara.wndhandle =  HandleToLong(localWnd);  
	if(clients&&clients->DeviceManager&&clients->DeviceManager->activevideodev)
	{
		ret = clients->DeviceManager->activevideodev->BeginPreview(wndPara, devIndex);
	}
	
	return (ret==true?TE_SDK_Success:TE_SDK_Failed);
}


int  CDeviceMgr::CloseLocalVideoPreview()
{
	DEBUG_TRACE("");
	UCClient* clients = UCClient::GetClient();
	int ret = 0;
	if(clients&&clients->DeviceManager&&clients->DeviceManager->activevideodev)
	{
		ret = clients->DeviceManager->activevideodev->EndPreview();
	}
	
	if(ret)
	{
		return TE_SDK_Success;
	}
	else
	{
		return TE_SDK_Failed;
	}
}

int  CDeviceMgr::GetCamerasInfo(TE_S_CAMERA_INFO *cameraInfoList)
{
	DEBUG_TRACE("");
	int nCount = 0, i = 0, ret= TE_SDK_Success;
	std::string m_ContactName;
	UCClient* clients = UCClient::GetClient();
	
	if (!cameraInfoList)
	{
		return TE_SDK_InvalidPara;
	}
	
	nCount = GetCamerasNum();
	if (nCount <= 0)
	{
		ret = TE_SDK_NotFoundcamera;
	}
	for(i=0; i < nCount; i++)
	{
		if((cameraInfoList+i) == NULL)
		{
			ret = TE_SDK_NullPtr;
			break;
		}
		m_ContactName = eSDKTool::utf8str2unicodestr(clients->DeviceManager->videodevlist[i]->name.c_str());
		strncpy(cameraInfoList[i].cName, m_ContactName.c_str(), TE_D_NAME_LEN);
		cameraInfoList[i].bIsActive = clients->DeviceManager->videodevlist[i]->isactive;
		cameraInfoList[i].bIsCertified = clients->DeviceManager->videodevlist[i]->iscertified;
		cameraInfoList[i].bType = clients->DeviceManager->videodevlist[i]->type;
		cameraInfoList[i].ulIndex = clients->DeviceManager->videodevlist[i]->index;
	}


	return ret;
}

int CDeviceMgr::GetAudioInInfo(TE_S_AUDIOIN_INFO *audioInInfoList)
{
	DEBUG_TRACE("");
	int nCount = 0, i = 0, ret= TE_SDK_Success;
	std::string m_audioName;
	UCClient* clients = UCClient::GetClient();

	if (!audioInInfoList)
	{
		return TE_SDK_InvalidPara;
	}

	nCount = GetAudioInNum();
	if (nCount <= 0)
	{
		ret = TE_SDK_NotFoundAudioIn;
	}
	for(i=0; i < nCount; i++)
	{
		if((audioInInfoList+i) == NULL)
		{
			ret = TE_SDK_NullPtr;
			break;
		}
		m_audioName = eSDKTool::utf8str2unicodestr(clients->DeviceManager->micdevlist[i]->name);
		strncpy(audioInInfoList[i].cName, m_audioName.c_str(), TE_D_NAME_LEN);
		audioInInfoList[i].bIsActive = clients->DeviceManager->micdevlist[i]->isactive;
		audioInInfoList[i].bIsCertified = clients->DeviceManager->micdevlist[i]->iscertified;
		audioInInfoList[i].bType = clients->DeviceManager->micdevlist[i]->type;
		audioInInfoList[i].ulIndex = clients->DeviceManager->micdevlist[i]->index;
	}
	return ret;
}


int CDeviceMgr::GetAudioOutInfo(TE_S_AUDIOOUT_INFO *audioOutInfoList)
{
	DEBUG_TRACE("");
	int nCount = 0, i = 0, ret= TE_SDK_Success;
	std::string m_audioName;
	UCClient* clients = UCClient::GetClient();

	if (!audioOutInfoList)
	{
		return TE_SDK_InvalidPara;
	}

	nCount = GetAudioOutNum();
	if (nCount <= 0)
	{
		ret = TE_SDK_NotFoundAudioOut;
	}
	for(i=0; i < nCount; i++)
	{
		if((audioOutInfoList+i) == NULL)
		{
			ret = TE_SDK_NullPtr;
			break;
		}
		m_audioName = eSDKTool::utf8str2unicodestr(clients->DeviceManager->speakerdevlist[i]->name);
		strncpy(audioOutInfoList[i].cName, m_audioName.c_str(), TE_D_NAME_LEN);
		audioOutInfoList[i].bIsActive = clients->DeviceManager->speakerdevlist[i]->isactive;
		audioOutInfoList[i].bIsCertified = clients->DeviceManager->speakerdevlist[i]->iscertified;
		audioOutInfoList[i].bType = clients->DeviceManager->speakerdevlist[i]->type;
		audioOutInfoList[i].ulIndex = clients->DeviceManager->speakerdevlist[i]->index;
	}


	return ret;
}


int CDeviceMgr::GetCamerasNum()
{
	DEBUG_TRACE("");
	int nCount = 0;
	UCClient* clients = UCClient::GetClient();
	if(clients&&clients->DeviceManager)
	{
		nCount = clients->DeviceManager->videodevlist.size();
	}
	
	
	if (nCount > TE_D_DEVICE_MAX_NUM)
	{
		nCount = TE_D_DEVICE_MAX_NUM;
	}


	return nCount;

}

int CDeviceMgr::GetAudioInNum()
{
	DEBUG_TRACE("");
	int nCount = 0;
	UCClient* clients = UCClient::GetClient();
	if(clients&&clients->DeviceManager)
	{
		nCount = clients->DeviceManager->micdevlist.size();
	}

	if (nCount > TE_D_DEVICE_MAX_NUM)
	{
		nCount = TE_D_DEVICE_MAX_NUM;
	}


	return nCount;

}


int CDeviceMgr::GetAudioOutNum()
{
	DEBUG_TRACE("");
	int nCount = 0;
	UCClient* clients = UCClient::GetClient();
	if(clients&&clients->DeviceManager)
	{
		nCount = clients->DeviceManager->speakerdevlist.size();
	}

	if (nCount > TE_D_DEVICE_MAX_NUM)
	{
		nCount = TE_D_DEVICE_MAX_NUM;
	}


	return nCount;

}

int CDeviceMgr::SetVolume(TE_INT32 volume,TE_E_VOLUME_TYPE type)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"volume:%d,type:%d",volume,type);
	DEBUG_TRACE("setvolume:%s",strParameter);
	if (volume<0)
	{
		return TE_SDK_VOLUME_TO_SET_LESS_THAN_ZERO;
	}

	if (type == TE_E_VOLUME_TYPE_MIC)
	{
		//设置MIC音量
		if (UCCLIENT()->DeviceManager && UCCLIENT()->DeviceManager->activemicdev)
		{
			if(!UCCLIENT()->DeviceManager->activemicdev->SetVolume(volume))
			{
				return TE_SDK_SET_MIC_VOLUME_FAILED;
			}
		}
		else
		{
			return TE_SDK_SET_MIC_VOLUME_FAILED;
		}
	}
	else if(type == TE_E_VOLUME_TYPE_SPEAK)
	{
		//设置SPK音量
		if (UCCLIENT()->DeviceManager && UCCLIENT()->DeviceManager->activespkerdev)
		{
			if(!UCCLIENT()->DeviceManager->activespkerdev->SetVolume(volume))
			{
				return TE_SDK_SET_SPEAK_VOLUME_FAILED;
			}

		}
		else
		{
			return TE_SDK_SET_SPEAK_VOLUME_FAILED;
		}
	}
	else
	{
		return TE_SDK_INVALID_VOLUME_TYPE;
	}

	return TE_SDK_Success;
}

int CDeviceMgr::GetVolume(TE_E_VOLUME_TYPE type)
{
	DEBUG_TRACE("type:%d",type);
	if (type == TE_E_VOLUME_TYPE_MIC)
	{
		if (UCCLIENT()->DeviceManager && UCCLIENT()->DeviceManager->activemicdev)
		{
			return UCCLIENT()->DeviceManager->activemicdev->GetVolume();
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (UCCLIENT()->DeviceManager && UCCLIENT()->DeviceManager->activespkerdev)
		{
			return UCCLIENT()->DeviceManager->activespkerdev->GetVolume();
		}
		else
		{
			return 0;
		}
	}
}