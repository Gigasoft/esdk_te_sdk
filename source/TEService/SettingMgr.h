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
 * @file  SettingMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manager Setting Class
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#ifndef SETTING_MGR_H
#define SETTING_MGR_H
#include "stdafx.h"

const std::string SETTING_MEDIA_ENCRYPT_SRTP = "EncryptSRTP";  
const std::string SETTING_MEDIA_OPEN_SLIDE = "OpenSlide";  
const std::string SETTING_MEDIA_BAND_WIDTH = "BandWidth";  
const std::string VIDEO_QUALITY = "VideoQuality";  
const std::string SETTING_MEDIA_SLIDE_ABILITY_CACHE = "SlideCache";
//开启自动接听：表示启用，表示不开启
const std::string SETTING_MEDIA_AUTO_REPLY = "AutoReply"; 
const std::string SORTRULE_PRIVATECONTACT = "PrivateContactSortRule";
const std::string BIG_WINDOW_PIC_MODE = "BigWindowPicMode";

/***************************************************
 * @class CSettingMgr
 * @brief Manager Setting
 * @details 
***************************************************/
class CSettingMgr
{
public:
	static inline CSettingMgr& Instance()
	{
		static CSettingMgr inst;
		return inst;
	}
public:
    CSettingMgr(void);
    ~CSettingMgr(void);
	int SetNetworkConfig(TE_S_NETWORK_CONFIG networkConfig);
	//int GetNetworkConfig(TE_S_NETWORK_CONFIG &networkConfig);
	int GetNetworkConfig(conversation::Conversation* pConv,TE_S_STREAM_INFO* callStreamInfo);

};
#endif //SETTING_MGR_H