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
 * @file  DeviceMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manager Device Class
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#ifndef DEVICE_MGR_H
#define DEVICE_MGR_H

#include "TESDK.h"
#include "stdafx.h"

/***************************************************
 * @class CDeviceMgr
 * @brief Manager Device
 * @details 
***************************************************/
class CDeviceMgr
{
public:
	static inline CDeviceMgr& Instance()
	{
		static CDeviceMgr inst;
		return inst;
	}
public:
    CDeviceMgr(void);
    ~CDeviceMgr(void);

	int SetLocalVideo(TE_UINT32 callId,bool flag);
	int SetLocalSpeaker(TE_UINT32 callId,bool flag);
	int SetLocalMic(TE_UINT32 callId,bool flag);
	int OpenLocalVideoPreview(HWND  localWnd, TE_ULONG devIndex);
	int CloseLocalVideoPreview();
	int GetCamerasInfo(TE_S_CAMERA_INFO *cameraInfoList);
	int GetAudioInInfo(TE_S_AUDIOIN_INFO *audioInInfoList);
	int GetAudioOutInfo(TE_S_AUDIOOUT_INFO *audioOutInfoList);
	int GetCamerasNum();
	int GetAudioInNum();
	int GetAudioOutNum();
	int SetVolume(TE_INT32 volume,TE_E_VOLUME_TYPE type);
	int GetVolume(TE_E_VOLUME_TYPE type);
};
#endif //EVENT_MGR_H