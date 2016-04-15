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
 * @file  SettingMgr.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Manager Setting Class
 * @details 
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/
#include "stdafx.h"
#include "SettingMgr.h"
#include "Log.h"
//typedef  int __declspec(dllimport) (WINAPI *tup_call_set_cfg)(unsigned int cfgid, void * val);
//typedef  int __declspec(dllimport) (WINAPI *tup_call_get_callstatics)(CALL_S_STREAM_INFO* statics);
typedef  int ( *tup_call_get_callstatics)(CALL_S_STREAM_INFO* statics);

typedef  int ( *tup_call_set_cfg)(unsigned int cfgid, void * val);

CSettingMgr::CSettingMgr(void)
{

}

CSettingMgr::~CSettingMgr(void)
{
   
}

int CSettingMgr::SetNetworkConfig(TE_S_NETWORK_CONFIG networkConfig)
{
	DEBUG_TRACE("");
	std::string strValue = "";
	if ((networkConfig.media_auto_reply>=TE_E_SETTING_MEDIA_AUTO_REPLY_BUTT) && (networkConfig.media_auto_reply < TE_E_SETTING_MEDIA_AUTO_REPLY_DISABLE))
	{
		return TE_SDK_InvalidPara;
	}

	if ((networkConfig.media_bandwidth>=TE_E_SETTING_MEDIA_BANDWIDTH_BUTT) && (networkConfig.media_bandwidth < TE_E_SETTING_MEDIA_BANDWIDTH_64))
	{
		return TE_SDK_InvalidPara;
	}

	if ((networkConfig.srtp_mode>=TE_E_SETTING_SRTP_MODE_BUTT) && (networkConfig.srtp_mode < TE_E_SETTING_SRTP_MODE_DISABLE))
	{
		return TE_SDK_InvalidPara;
	}
	
	if ((networkConfig.media_open_slide>=TE_E_SETTING_MEDIA_OPEN_SLIDE_BUTT) && (networkConfig.media_open_slide < TE_E_SETTING_MEDIA_OPEN_SLIDE_DISABLE))
	{
		return TE_SDK_InvalidPara;
	}
	
	switch (networkConfig.srtp_mode)
	{
		case TE_E_SETTING_SRTP_MODE_DISABLE:
		{
			strValue = "1"; //disable encryption
			break;
		}
		case TE_E_SETTING_SRTP_MODE_FORCE:
		{

			strValue = "2"; //enable encryption
			break;
		}
		case TE_E_SETTING_SRTP_MODE_OPTION:
		{
			strValue = "3";
			break;
		}
		default:
		{
			//it should not be in here;
		}
	}
	//setup Encrypt SRTP 
	(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(SETTING_MEDIA_ENCRYPT_SRTP, strValue);

	unsigned int ulBandwidth = 0;
	
	switch (networkConfig.media_bandwidth)
	{
		case TE_E_SETTING_MEDIA_BANDWIDTH_64:
		{
			strValue = "64";
			ulBandwidth=64;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_128:
		{
			strValue = "128";
			ulBandwidth=128;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_256:
		{
			strValue = "256";
			ulBandwidth=256;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_384:
		{
			strValue = "384";
			ulBandwidth=384;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_512:
		{
			strValue = "512";
			ulBandwidth=512;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_768:
		{
			strValue = "768";
			ulBandwidth=768;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_1024:
		{
			strValue = "1024";
			ulBandwidth=1024;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_1472:
		{
			strValue = "1472";
			ulBandwidth=1472;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_1536:
		{
			strValue = "1536";
			ulBandwidth=1536;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_1920:
		{
			strValue = "1920";
			ulBandwidth=1920;
			break;
		}
		case TE_E_SETTING_MEDIA_BANDWIDTH_2048:
		{
			strValue = "2048";
			ulBandwidth=2048;
			break;
		}
		default:
		{
			////it should not be in here;
		}

	}
	//setup BandWidth
	(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(SETTING_MEDIA_BAND_WIDTH, strValue);

	if(TE_E_SETTING_MEDIA_BANDWIDTH_64 == networkConfig.media_bandwidth)
	{
		if(networkConfig.media_open_slide)
		{
			strValue = "1";
		}
		else
		{
			strValue = "0";
		}
		(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(SETTING_MEDIA_SLIDE_ABILITY_CACHE, strValue);
		networkConfig.media_open_slide = TE_E_SETTING_MEDIA_OPEN_SLIDE_DISABLE;
	}

	if (networkConfig.media_auto_reply)
	{
		strValue = "1";
	}
	else
	{
		strValue = "0";
	}
	(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(SETTING_MEDIA_AUTO_REPLY, strValue);



	if (networkConfig.media_open_slide)
	{
		strValue = "1";
	}
	else
	{	
		strValue = "0";
	}
	(void)UCCLIENT()->Self->simplecfg_.SaveUserConfig(SETTING_MEDIA_OPEN_SLIDE, strValue);


	if (!(UCCLIENT()->SetProfileParam())) //设置界面配置 srtp、辅流、带宽、清晰流畅策略
	{
		return TE_SDK_SetParamFailed;
	}


	tup_call_set_cfg tup_set_cfg;

	HINSTANCE hDll; //DLL句柄

	//..\\..\\..\\platform\\TE\\lib\\windows\\Debug\\tup_callservice.dll
	hDll = LoadLibrary(L"tup_callservice.dll");
	tup_set_cfg = (tup_call_set_cfg)GetProcAddress(hDll,"tup_call_set_cfg");



	if(tup_set_cfg == NULL)
	{
		FreeLibrary(hDll);
	}
	else
	{
		int ret =0;
		if(networkConfig.setFrameSize)
		{
			TE_S_VIDEO_FRAMESIZE dataFrameSize;
			memset(&dataFrameSize, 0, sizeof(TE_S_VIDEO_FRAMESIZE));
			dataFrameSize.uiFramesize = networkConfig.dataFrameSize.uiFramesize;
			dataFrameSize.uiMinFramesize = networkConfig.dataFrameSize.uiMinFramesize;
			dataFrameSize.uiDecodeFrameSize = networkConfig.dataFrameSize.uiDecodeFrameSize;
			ret=tup_set_cfg(TE_D_CFG_DATA_FRAMESIZE, (void *)&dataFrameSize);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_DATA_FRAMESIZE error:%d",ret);
			}
		}
		else
		{
			TE_S_VIDEO_FRAMESIZE dataFrameSize;
			memset(&dataFrameSize, 0, sizeof(TE_S_VIDEO_FRAMESIZE));
			dataFrameSize.uiFramesize = 9;
			dataFrameSize.uiMinFramesize = 4;
			dataFrameSize.uiDecodeFrameSize = 11;
			ret=tup_set_cfg(TE_D_CFG_DATA_FRAMESIZE, (void *)&dataFrameSize);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_DATA_FRAMESIZE error:%d",ret);
			}
		}
		if (networkConfig.setDataRate)
		{
			// 设置辅流码率
			TE_S_VIDEO_DATARATE stDataRate;
			memset(&stDataRate, 0, sizeof(TE_S_VIDEO_DATARATE));
			stDataRate.ulDataRate    = networkConfig.stDataRate.ulDataRate;
			stDataRate.ulMaxDataRate = networkConfig.stDataRate.ulMaxDataRate;
			stDataRate.ulMaxBw       = networkConfig.stDataRate.ulMaxBw;
			stDataRate.ulMinDataRate = networkConfig.stDataRate.ulMinDataRate;

			ret=tup_set_cfg(TE_D_CFG_DATA_DATARATE, (void *)&stDataRate);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_DATA_DATARATE error:%d",ret);
			}

			// 设置主流码率
			TE_S_VIDEO_DATARATE sVideoDataRate;
			memset(&sVideoDataRate, 0, sizeof(TE_S_VIDEO_DATARATE));
			sVideoDataRate.ulDataRate =  networkConfig.sVideoDataRate.ulDataRate;
			sVideoDataRate.ulMaxBw    = networkConfig.sVideoDataRate.ulMaxBw;
			sVideoDataRate.ulMinDataRate =networkConfig.sVideoDataRate.ulMinDataRate;
			sVideoDataRate.ulMaxDataRate = networkConfig.sVideoDataRate.ulMaxDataRate;
			ret=tup_set_cfg(TE_D_CFG_VIDEO_DATARATE, (void *)&sVideoDataRate);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_VIDEO_DATARATE error:%d",ret);
			}

		}
		else
		{
			int iDataBandwidth = 0;;
			if (ulBandwidth <= 64)
			{
				iDataBandwidth = 0;
			}
			else if (ulBandwidth < 128)
			{
				iDataBandwidth = 64;
			}
			else if (ulBandwidth < 256)
			{
				iDataBandwidth = 64;
			}
			else if (ulBandwidth < 384)
			{
				iDataBandwidth = 128;
			}
			else if (ulBandwidth < 512)
			{
				iDataBandwidth = 192;
			}
			else if (ulBandwidth < 768)
			{
				iDataBandwidth = 192;
			}
			else if (ulBandwidth < 1024)
			{
				iDataBandwidth = 256;
			}
			else if (ulBandwidth < 1152)
			{
				iDataBandwidth = 384;
			}
			else if (ulBandwidth < 1472)
			{
				iDataBandwidth = 384;
			}
			else if (ulBandwidth < 1536)
			{
				iDataBandwidth = 512;
			}
			else if (ulBandwidth <= 2560)
			{
				iDataBandwidth = 512;
			}
			else
			{
				iDataBandwidth= -1;
			}
		
			// 设置辅流码率
			TE_S_VIDEO_DATARATE stDataRate;
			memset(&stDataRate, 0, sizeof(TE_S_VIDEO_DATARATE));
			stDataRate.ulDataRate    = iDataBandwidth;
			stDataRate.ulMaxDataRate = iDataBandwidth * 4 / 3;
			stDataRate.ulMaxBw       = iDataBandwidth;
			stDataRate.ulMinDataRate = iDataBandwidth;

			ret=tup_set_cfg(TE_D_CFG_DATA_DATARATE, (void *)&stDataRate);

			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_DATA_DATARATE error:%d",ret);
			}

			// 设置主流码率
			TE_S_VIDEO_DATARATE sVideoDataRate;
			memset(&sVideoDataRate, 0, sizeof(TE_S_VIDEO_DATARATE));
			sVideoDataRate.ulDataRate = ulBandwidth; // - iDataBandwidth;
			sVideoDataRate.ulMaxBw    = ulBandwidth;
			sVideoDataRate.ulMinDataRate = ulBandwidth;
			sVideoDataRate.ulMaxDataRate = ulBandwidth;
			ret=tup_set_cfg(TE_D_CFG_VIDEO_DATARATE, (void *)&sVideoDataRate);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_VIDEO_DATARATE error:%d",ret);
			}


		}
		if (networkConfig.setFrameRate)
		{
			TE_S_VIDEO_FRAMERATE stDataFrameRate;
			memset(&stDataFrameRate, 0, sizeof(TE_S_VIDEO_FRAMERATE));
			stDataFrameRate.uiFrameRate = networkConfig.stDataFrameRate.uiFrameRate; //STR_TO_UINT32(gProfile.getDataPicFramerate());
			ret=tup_set_cfg(TE_D_CFG_DATA_FRAMERATE, (void *)&stDataFrameRate);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_DATA_FRAMERATE error:%d",ret);
			}
		}
		else
		{
			TE_S_VIDEO_FRAMERATE stDataFrameRate;
			memset(&stDataFrameRate, 0, sizeof(TE_S_VIDEO_FRAMERATE));
			stDataFrameRate.uiFrameRate = 5; //STR_TO_UINT32(gProfile.getDataPicFramerate());
			ret=tup_set_cfg(TE_D_CFG_DATA_FRAMERATE, (void *)&stDataFrameRate);
			if(ret)
			{
				ERROR_LOG("tup_call_set_cfg TE_D_CFG_DATA_FRAMERATE error:%d",ret);
			}

		}

		/*std::string txt = UCCLIENT()->DeviceManager->videodevlist[_index]->name.c_str();
		std::string dec="VideoDevice";
		(void)USERCONFIG().SaveUserConfig(dec, txt);
		INFO_LOG("SETTING_MEDIA_VIDEODEVICE=[ %s", txt.c_str());
		if (TUP_SUCCESS != iResult)\
		{\
		ERROR_LOG() << "[" << __FUNCTION__ << "  " << __LINE__ << "] Set " #errorInfo " failed.  " #iResult " = " << iResult;\
		return checkResult;\
		}\
		ERROR_LOG*/

		FreeLibrary(hDll);
	}


	return TE_SDK_Success;
}


//int CSettingMgr::GetNetworkConfig(TE_S_NETWORK_CONFIG &networkConfig)
//{
//	std::string  strValue = ""; 
//	TE_E_SETTING_MEDIA_BANDWIDTH nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_64;
//	(void)UCCLIENT()->Self->simplecfg_.GetUserConfig(SETTING_MEDIA_ENCRYPT_SRTP, strValue);
//	if (strValue == "1")
//	{
//		networkConfig.srtp_mode = TE_E_SETTING_SRTP_MODE_DISABLE;
//
//	}
//	else if(strValue == "2")
//	{
//		networkConfig.srtp_mode = TE_E_SETTING_SRTP_MODE_FORCE;
//	}
//	else
//	{
//		networkConfig.srtp_mode = TE_E_SETTING_SRTP_MODE_OPTION;
//	}
//
//
//	(void)UCCLIENT()->Self->simplecfg_.GetUserConfig(SETTING_MEDIA_AUTO_REPLY, strValue);
//	if (strValue == "1")
//	{
//		networkConfig.media_auto_reply = TE_E_SETTING_MEDIA_AUTO_REPLY_ENABLE;
//
//	}
//	else
//	{
//		networkConfig.media_auto_reply = TE_E_SETTING_MEDIA_AUTO_REPLY_DISABLE;
//	}
//
//	(void)UCCLIENT()->Self->simplecfg_.GetUserConfig(SETTING_MEDIA_OPEN_SLIDE, strValue);
//
//	if (strValue == "1")
//	{
//
//		networkConfig.media_open_slide = TE_E_SETTING_MEDIA_OPEN_SLIDE_ENABLE;
//	}
//	else
//	{
//		networkConfig.media_open_slide = TE_E_SETTING_MEDIA_OPEN_SLIDE_DISABLE;
//	}
//
//	(void)UCCLIENT()->Self->simplecfg_.GetUserConfig(SETTING_MEDIA_BAND_WIDTH, strValue);
//	
//	if("64" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_64;
//	}
//	else if("128" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_128;
//	}
//	else if("256" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_256;
//	}
//	else if("384" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_384;
//
//	}
//	else if("512" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_512;
//
//	}
//	else if("768" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_768;
//	}
//	else if("1024" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_1024;
//
//	}
//	else if("1472" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_1472;
//	}
//	else if("1536" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_1536;
//	}
//	else if("1920" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_1920;
//	}
//	else if("2048" == strValue)
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_2048;
//	}
//	else
//	{
//		nbandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_512;
//	}
//
//	networkConfig.media_bandwidth = nbandwidth;
//	return TE_SDK_Success;
//}


int CSettingMgr::GetNetworkConfig(conversation::Conversation* pConv,TE_S_STREAM_INFO* callStreamInfo)
{
	DEBUG_TRACE("");
	conversation::AVSession* pSess = NULL;

	if (pConv && pConv->HasSession(AudioVideo) )
	{
		pSess = dynamic_cast<conversation::AVSession*>(pConv->GetSession(AudioVideo));
	}
	if(pSess)
	{
		tup_call_get_callstatics get_callstatics;

		HINSTANCE hDll; //DLL句柄

		//..\\..\\..\\platform\\TE\\lib\\windows\\Debug\\tup_callservice.dll
		hDll = LoadLibrary(L"tup_callservice.dll");
		get_callstatics = (tup_call_get_callstatics)GetProcAddress(hDll,"tup_call_get_callstatics");


		CALL_S_STREAM_INFO stStreamInfos = {0};
		if(get_callstatics == NULL)
		{
			FreeLibrary(hDll);
			return TE_SDK_GetMediaInfoFailed;
		}
		else
		{
			int result =get_callstatics(&stStreamInfos);
			FreeLibrary(hDll);
			if (0 == result)
			{
				strncpy(callStreamInfo->stAudioStreamInfo.acDecodeProtocol,stStreamInfos.stAudioStreamInfo.acDecodeProtocol,TE_D_PROTOCOL_LENGTH);
				strncpy(callStreamInfo->stAudioStreamInfo.acEncodeProtocol,stStreamInfos.stAudioStreamInfo.acEncodeProtocol,TE_D_PROTOCOL_LENGTH);
                callStreamInfo->stAudioStreamInfo.bIsCalling=stStreamInfos.stAudioStreamInfo.bIsCalling;
				callStreamInfo->stAudioStreamInfo.bIsSRTP=stStreamInfos.stAudioStreamInfo.bIsSRTP;
				callStreamInfo->stAudioStreamInfo.fRecvDelay=stStreamInfos.stAudioStreamInfo.fRecvDelay;
				callStreamInfo->stAudioStreamInfo.fRecvJitter=stStreamInfos.stAudioStreamInfo.fRecvJitter;
				callStreamInfo->stAudioStreamInfo.fRecvLossFraction=stStreamInfos.stAudioStreamInfo.fRecvLossFraction;
				callStreamInfo->stAudioStreamInfo.fSendDelay=stStreamInfos.stAudioStreamInfo.fSendDelay;
				callStreamInfo->stAudioStreamInfo.fSendJitter=stStreamInfos.stAudioStreamInfo.fSendJitter;
				callStreamInfo->stAudioStreamInfo.fSendLossFraction=stStreamInfos.stAudioStreamInfo.fSendLossFraction;
				callStreamInfo->stAudioStreamInfo.ulChannelID=stStreamInfos.stAudioStreamInfo.ulChannelID;
				callStreamInfo->stAudioStreamInfo.ulRecvBitRate=stStreamInfos.stAudioStreamInfo.ulRecvBitRate;
				callStreamInfo->stAudioStreamInfo.ulRecvTotalLostPacket=stStreamInfos.stAudioStreamInfo.ulRecvTotalLostPacket;
				callStreamInfo->stAudioStreamInfo.ulSendBitRate=stStreamInfos.stAudioStreamInfo.ulSendBitRate;
				callStreamInfo->stAudioStreamInfo.ulSendTotalLostPacket=stStreamInfos.stAudioStreamInfo.ulSendTotalLostPacket;

				strncpy(callStreamInfo->stDataStreamInfo.acDecodeName,stStreamInfos.stDataStreamInfo.acDecodeName,TE_MAX_CODEC_NAME_LEN);
				strncpy(callStreamInfo->stDataStreamInfo.acDecoderProfile,stStreamInfos.stDataStreamInfo.acDecoderProfile,TE_MAX_PROFILE_LEN);
				strncpy(callStreamInfo->stDataStreamInfo.acDecoderSize,stStreamInfos.stDataStreamInfo.acDecoderSize,TE_MAX_FRAMESIZE_LEN);
				strncpy(callStreamInfo->stDataStreamInfo.acEncodeName,stStreamInfos.stDataStreamInfo.acEncodeName,TE_MAX_CODEC_NAME_LEN);
				strncpy(callStreamInfo->stDataStreamInfo.acEncoderProfile,stStreamInfos.stDataStreamInfo.acEncoderProfile,TE_MAX_PROFILE_LEN);
				strncpy(callStreamInfo->stDataStreamInfo.acEncoderSize,stStreamInfos.stDataStreamInfo.acEncoderSize,TE_MAX_FRAMESIZE_LEN);
				callStreamInfo->stDataStreamInfo.bIsSRTP = stStreamInfos.stDataStreamInfo.bIsSRTP;
				callStreamInfo->stDataStreamInfo.fVideoRecvDelay = stStreamInfos.stDataStreamInfo.fVideoRecvDelay;
				callStreamInfo->stDataStreamInfo.fVideoRecvJitter = stStreamInfos.stDataStreamInfo.fVideoRecvJitter;
				callStreamInfo->stDataStreamInfo.fVideoRecvLossFraction = stStreamInfos.stDataStreamInfo.fVideoRecvLossFraction;
				callStreamInfo->stDataStreamInfo.fVideoSendDelay = stStreamInfos.stDataStreamInfo.fVideoSendDelay;
				callStreamInfo->stDataStreamInfo.fVideoSendJitter = stStreamInfos.stDataStreamInfo.fVideoSendJitter;
				callStreamInfo->stDataStreamInfo.fVideoSendLossFraction = stStreamInfos.stDataStreamInfo.fVideoSendLossFraction;
				callStreamInfo->stDataStreamInfo.ulHeight = stStreamInfos.stDataStreamInfo.ulHeight;
				callStreamInfo->stDataStreamInfo.ulRecvFrameRate = stStreamInfos.stDataStreamInfo.ulRecvFrameRate;
				callStreamInfo->stDataStreamInfo.ulSendFrameRate = stStreamInfos.stDataStreamInfo.ulSendFrameRate;
				callStreamInfo->stDataStreamInfo.ulVideoRecvBitRate = stStreamInfos.stDataStreamInfo.ulVideoRecvBitRate/1024;
				callStreamInfo->stDataStreamInfo.ulVideoSendBitRate = stStreamInfos.stDataStreamInfo.ulVideoSendBitRate/1024;
				callStreamInfo->stDataStreamInfo.ulWidth = stStreamInfos.stDataStreamInfo.ulWidth;


				strncpy(callStreamInfo->stVideoStreamInfo.acDecodeName,stStreamInfos.stVideoStreamInfo.acDecodeName,TE_MAX_CODEC_NAME_LEN);
				strncpy(callStreamInfo->stVideoStreamInfo.acDecoderProfile,stStreamInfos.stVideoStreamInfo.acDecoderProfile,TE_MAX_PROFILE_LEN);
				strncpy(callStreamInfo->stVideoStreamInfo.acDecoderSize,stStreamInfos.stVideoStreamInfo.acDecoderSize,TE_MAX_FRAMESIZE_LEN);
				strncpy(callStreamInfo->stVideoStreamInfo.acEncodeName,stStreamInfos.stVideoStreamInfo.acEncodeName,TE_MAX_CODEC_NAME_LEN);
				strncpy(callStreamInfo->stVideoStreamInfo.acEncoderProfile,stStreamInfos.stVideoStreamInfo.acEncoderProfile,TE_MAX_PROFILE_LEN);
				strncpy(callStreamInfo->stVideoStreamInfo.acEncoderSize,stStreamInfos.stVideoStreamInfo.acEncoderSize,TE_MAX_FRAMESIZE_LEN);
				callStreamInfo->stVideoStreamInfo.bIsSRTP = stStreamInfos.stVideoStreamInfo.bIsSRTP;
				callStreamInfo->stVideoStreamInfo.fVideoRecvDelay = stStreamInfos.stVideoStreamInfo.fVideoRecvDelay;
				callStreamInfo->stVideoStreamInfo.fVideoRecvJitter = stStreamInfos.stVideoStreamInfo.fVideoRecvJitter;
				callStreamInfo->stVideoStreamInfo.fVideoRecvLossFraction = stStreamInfos.stVideoStreamInfo.fVideoRecvLossFraction;
				callStreamInfo->stVideoStreamInfo.fVideoSendDelay = stStreamInfos.stVideoStreamInfo.fVideoSendDelay;
				callStreamInfo->stVideoStreamInfo.fVideoSendJitter = stStreamInfos.stVideoStreamInfo.fVideoSendJitter;
				callStreamInfo->stVideoStreamInfo.fVideoSendLossFraction = stStreamInfos.stVideoStreamInfo.fVideoSendLossFraction;
				callStreamInfo->stVideoStreamInfo.ulHeight = stStreamInfos.stVideoStreamInfo.ulHeight;
				callStreamInfo->stVideoStreamInfo.ulRecvFrameRate = stStreamInfos.stVideoStreamInfo.ulRecvFrameRate;
				callStreamInfo->stVideoStreamInfo.ulSendFrameRate = stStreamInfos.stVideoStreamInfo.ulSendFrameRate;
				callStreamInfo->stVideoStreamInfo.ulVideoRecvBitRate = stStreamInfos.stVideoStreamInfo.ulVideoRecvBitRate/1024;
				callStreamInfo->stVideoStreamInfo.ulVideoSendBitRate = stStreamInfos.stVideoStreamInfo.ulVideoSendBitRate/1024;
				callStreamInfo->stVideoStreamInfo.ulWidth = stStreamInfos.stVideoStreamInfo.ulWidth;

				std::string strAudioCodec;
				strAudioCodec = stStreamInfos.stAudioStreamInfo.acEncodeProtocol;

				if (strAudioCodec=="PCMU")
				{
					strAudioCodec = "G711U";
				}
				else if (strAudioCodec=="PCMA")
				{
					strAudioCodec = "G711A";
				}
				strncpy(callStreamInfo->stAudioStreamInfo.acEncodeProtocol,strAudioCodec.c_str(),TE_D_PROTOCOL_LENGTH);


			}
			else
			{
				return TE_SDK_GetMediaInfoFailed;
			}
		}
	}
	else
	{
		return TE_SDK_GetMediaInfoFailed;
	}

	return TE_SDK_Success;
}