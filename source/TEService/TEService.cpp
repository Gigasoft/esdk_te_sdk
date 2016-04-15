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
 * @file  TEService.cpp   
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief TE Desktop SDK Interface
 * @details TE SDK Interface:TE_SDK_Init,TE_SDK_Release,
 *			TE_SDK_SetEventCallBack TE_SDK_Logout,TE_MakeCall
 *			TE_DropCall,TE_AnswerCall
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/

#include "stdafx.h"
#include "TEService.h"
#include "TESDK.h"
#include "Log.h"
#include "TERegMgr.h"
#include "EventMgr.h"
#include "eSDKTool.h"
#include "IM.h"
#include "IMMgr.h"
#include "DeviceMgr.h"
#include "SettingMgr.h"
#include "AddContacts.h"
#include "HistoryRecord.h"

//#pragma comment(linker, "/EXPORT:TE_SDK_Init=_TE_SDK_Init@0")

bool isInit = false;

#define CHECK_INIT_RETURN(isFlag,ret) if(!isFlag)\
{\
	ERROR_LOG("not init");\
	return ret;\
}

/**************************************************
 * @fn         TE_SDK_Init
 * @brief      Init TE SDK Resource
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  Before logining,please use this interface
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SDK_Init(void)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	if(isInit)
	{
		INFO_LOG("already init");
		return ret;
	}

	CTERegMgr::Instance().Init();

	SetUnhandledExceptionFilter(GPTUnhandledExceptionFilter);
	//IMManager::Instance().m_HasAudioVideo = 0;
	//初始化日志
	std::string path;
	eSDKTool::getCurrentPath(path);
	std::string strLogCfgFile = path+"\\eSDKClientLogCfg.ini";

	std::string iniValue;
	const int LENGTH = 1024;
	wchar_t* tchValue = new wchar_t[LENGTH];
	if(tchValue==NULL)
	{
		ret = TE_SDK_INIT_FAILED;
		return ret;
	}
	memset(tchValue, 0, LENGTH*sizeof(wchar_t));
	(void)::GetPrivateProfileString(eSDKTool::utf82unicode(LOGSWITCH).c_str(), eSDKTool::utf82unicode("switchflag").c_str(), eSDKTool::utf82unicode("").c_str(), tchValue, LENGTH-1,eSDKTool::utf82unicode(strLogCfgFile.c_str()).c_str());
	iniValue = eSDKTool::unicode_w_2_utf8(tchValue);
	if (iniValue=="" || iniValue=="1")
	{
		SET_LOG_SWITCH(1);
	} 
	else
	{
		SET_LOG_SWITCH(0);
	}

	memset(tchValue, 0, LENGTH*sizeof(wchar_t));
	(void)::GetPrivateProfileString(eSDKTool::utf82unicode(LOGPATH).c_str(), eSDKTool::utf82unicode("path").c_str(), eSDKTool::utf82unicode("").c_str(), tchValue, LENGTH-1, eSDKTool::utf82unicode(strLogCfgFile.c_str()).c_str());
	iniValue = eSDKTool::unicode_w_2_utf8(tchValue);

	unsigned int logLevel[LOG_CATEGORY] = {INVALID_LOG_LEVEL,INVALID_LOG_LEVEL,INVALID_LOG_LEVEL};

	if (iniValue=="" && CLogTrace::logSwitch==1)
	{
		std::string strLogStorePath = path+"\\eSDKLog";
		LogInit(PRODUCT_NAME,strLogCfgFile.c_str(),logLevel,strLogStorePath.c_str());
	} 
	else
	{
		if (CLogTrace::logSwitch==1)
		{
			std::string strLogStorePath = iniValue+"\\eSDKLog";
			LogInit(PRODUCT_NAME,strLogCfgFile.c_str(),logLevel,strLogStorePath.c_str());
		}
	}
	INFO_LOG("SDK Compile Time:%s %s",__DATE__,__TIME__);
	INFO_TRACE(strParameter,&ret,"");
	delete[] tchValue;
	//tchValue = NULL;

	isInit = true;
	ret = TE_SDK_Success;
	return ret;
}


/**************************************************
 * @fn         TE_SDK_Release
 * @brief      Release TE SDK Resource
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  Before end programing,please use this interface
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SDK_Release(void)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	CHECK_INIT_RETURN(isInit,TE_SDK_NotInit);
	{	
		CTERegMgr::Instance().Uninit();
	}
	
	LogFini(PRODUCT_NAME);

	isInit = false;
	ret = TE_SDK_Success;
	return ret;
}

/**************************************************
 * @fn         TE_SDK_Login
 * @brief      Login TE SDK Server
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  pLoginReqInfo	Login TE Server Request Information
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SDK_Login(const TE_S_LOGIN_INFO *pLoginReqInfo)
{
	
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = TE_SDK_InvalidPara;
	INFO_TRACE(strParameter,&ret,"");
	if (NULL == pLoginReqInfo)
	{
		ERROR_LOG("pLoginReqInfo  is null pointer.");
		ret = TE_SDK_NullPtr;
		return ret;
	}
	if ( pLoginReqInfo->uiPort>65535)
	{
		ERROR_LOG("pLoginReqInfo uiPort is invalid value.");
		return ret;
	}
	if(strlen(pLoginReqInfo->cPWD) > TE_D_PWD_LEN)
	{
		ERROR_LOG("password is too long");
	}
	if(strlen(pLoginReqInfo->cUserName) > TE_D_NAME_LEN)
	{
		ERROR_LOG("usename is too long");
	}
	ret = CTERegMgr::Instance().SignIn(pLoginReqInfo);
	sprintf_s(strParameter,sizeof(strParameter),"%s,%d,%s,%s,%s,%s",pLoginReqInfo->stIP,pLoginReqInfo->uiPort,pLoginReqInfo->cTransMode,pLoginReqInfo->licenseServer,pLoginReqInfo->cSipUri,pLoginReqInfo->cUserName);
	return ret;
}

/**************************************************
 * @fn         TE_SDK_SetEventCallBack
 * @brief      Login TE SDK Server
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  fEventCallBack	ISV provides callback function
 * @param[in]  pUserData		ISV provides user data space
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SDK_SetEventCallBack(EventCallBack fEventCallBack /*= NULL*/, TE_VOID *pUserData /*= NULL*/)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = TE_SDK_NullPtr;
	INFO_TRACE(strParameter,&ret,"");
	CHECK_INIT_RETURN(isInit,TE_SDK_NotInit);

	if (NULL == fEventCallBack)
	{
		ERROR_LOG("fEventCallBack  is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	
	if (NULL == pUserData)
	{
		ERROR_LOG("pUserData  is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	ret = CEventMgr::Instance().SetEventCallBack(fEventCallBack, pUserData);
	return ret;
}

/**************************************************
 * @fn         TE_SDK_Logout
 * @brief      Login out TE SDK Server
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SDK_Logout()
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	CHECK_INIT_RETURN(isInit,TE_SDK_NotInit);
	INFO_LOG("TE LogOut");
	ret = CTERegMgr::Instance().SignOut();
	return ret;
}

/**************************************************
 * @fn         TE_MakeCall
 * @brief      Start to call somebody by SIP number 
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  number		SIP number
 * @param[in]  callType	Call type
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_MakeCall (TE_CHAR* number, TE_E_CALL_TYPE callType)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = TE_SDK_NullPtr;
	INFO_TRACE(strParameter,&ret,"");
	CString  cstrInputNum;
	std::string inputnum ;
	uc::model::Contact contact_;
	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;

	if (!number)
	{
		ERROR_LOG("number  is null pointer.");
		return ret;
	}
	if ((callType < TE_E_CALL_TYPE_IPAUDIO) || (callType >= TE_E_CALL_TYPE_BUTT))
	{
		ERROR_LOG("call type is invalid value.");
		ret = TE_SDK_InvalidPara;
		return ret;	
	}

	//cstrInputNum.Format(_T("%s"),eSDKTool::utf8_2_unicode(number));
	inputnum = number;//eSDKTool::unicode_2_utf8(cstrInputNum.Trim());

	if (!inputnum.empty())
	{
		if (!ucclient->ContactManager->GetContactByAccount(eSDKTool::unicode_2_utf8(inputnum.c_str()),contact_))
		{
			//if it could not get contacts by local, it will search from net address book.
			if (!ucclient->ContactManager->GetNetContactByAcc(inputnum, contact_))  
			{
				contact_.name_ = contact_.mobile_ = eSDKTool::unicode_2_utf8(inputnum.c_str());
			}
			else 
			{
				contact_.mobile_ = eSDKTool::unicode_2_utf8(inputnum.c_str());
			}
		}
		else //when got it, it will assign value to mobile.
		{
			contact_.ucAcc_ = eSDKTool::unicode_2_utf8(inputnum.c_str());
		}

		CallParam param;
		param.callType = callType;

		param.memlist.push_back(contact_);
		//CIMConversation *p_IMConv = new CIMConversation; 			
		//ret = p_IMConv->handle(&param);
		ret = PhoneEventHandler::callout_handle(&param);
		ret = TE_SDK_Success;
	}
	else
	{
		ERROR_LOG("input number is empty!");
		ret = TE_SDK_InvalidPara;
	}
	
	sprintf_s(strParameter,sizeof(strParameter),"%s,%d",number,callType);
	return ret;

	

}

/**************************************************
 * @fn         TE_DropCall
 * @brief      End somebody phone
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		Call ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_DropCall(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	ret =(int)PhoneEventHandler::hangup_handle(callId);
	if(1 == ret)
	{
		ret = TE_SDK_Success;
	}
	else
	{
		ret = TE_SDK_Failed;
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",callId);
	return ret;
}

/**************************************************
 * @fn         TE_RejectCall
 * @brief      Reject somebody's comming call
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		Call ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_RejectCall(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret = (int)PhoneEventHandler::rejectcall_handle(callId);
	//CallOutMenuHandler::RejectCall();
	if(1 == ret)
	{
		ret = TE_SDK_Success;
	}
	else
	{
		ret = TE_SDK_Failed;
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",callId);
	return ret;
}

/**************************************************
 * @fn         TE_AnswerAudioCall
 * @brief      Answer Audio call
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		Call ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_AnswerAudioCall(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret = (int)PhoneEventHandler::answeraudiocall_handle(callId);
	if(1 == ret)
	{
		ret = TE_SDK_Success;
	}
	else
	{
		ret = TE_SDK_Failed;
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",callId);
	return ret;
}



/**************************************************
 * @fn         TE_AnswerVideoCall
 * @brief      Answer Video call
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		Call ID
 * @param[in]  isAudioAccept		Audio Accept flag
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_AnswerVideoCall(TE_UINT32 callId, TE_BOOL isAudioAccept)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret =(int)PhoneEventHandler::answervediocall_handle(callId, isAudioAccept);	
	if(1 == ret)
	{
		ret = TE_SDK_Success;
	}
	else
	{
		ret = TE_SDK_Failed;
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d,%d",callId,isAudioAccept);
	return ret;
}

/**************************************************
 * @fn         TE_SetLocalSpeaker
 * @brief      Set speaker mute or unmute
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId	Call ID
 * @param[in]  flag		0:unmute	1:mute
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SetLocalSpeaker(TE_UINT32 callId,TE_BOOL flag)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	ret = CDeviceMgr::Instance().SetLocalSpeaker(callId, flag);

	if (ret != TE_SDK_Success)
	{
		ERROR_LOG("SetLocalSpeaker fail. flag:%d ret:%d",flag,ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d,%d",callId,flag);
	return ret;
}



/**************************************************
 * @fn         TE_SetLocalVideo
 * @brief      Set local camera disable or enable
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId	Call ID
 * @param[in]  flag		0:disable	1:enable
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SetLocalVideo(TE_UINT32 callId,TE_BOOL flag)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CDeviceMgr::Instance().SetLocalVideo(callId, flag );
	if (ret != TE_SDK_Success)
	{
		ERROR_LOG("SetLocalVideo fail. flag:%d ret:%d",flag,ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d,%d",callId,flag);
	return ret;

}

/**************************************************
 * @fn         TE_SetLocalMic
 * @brief      Set mic mute or unmute
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId	Call ID
 * @param[in]  flag		0:unmute	1:mute
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SetLocalMic(TE_UINT32 callId,TE_BOOL flag)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	ret = CDeviceMgr::Instance().SetLocalMic(callId, flag);

	if (ret != TE_SDK_Success)
	{
		ERROR_LOG("SetLocalMic fail. flag:%d ret:%d",flag,ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d,%d",callId,flag);
	return ret;
}

/**************************************************
 * @fn         TE_SetDisplayHandle
 * @brief      Set local and remote display window
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  localWnd	Local window handle
 * @param[in]  remote_wnd	Remote window handle
 * @param[in]  hwndData	   display share window handle
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetDisplayHandle(HWND  localWnd, HWND  remote_wnd,HWND hwndData)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	IMManager::Instance().setDisplayHandle(localWnd,remote_wnd,hwndData);
	return ret;
}


/**************************************************
 * @fn         TE_OpenPreview
 * @brief      Test local specify camera video
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  localWnd	Local window handle
 * @param[in]  devIndex	specify camera
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_OpenPreview(HWND  localWnd, TE_ULONG devIndex)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if (IMManager::Instance().HasAudioOrVideoInUse())
	{
		ERROR_LOG("Audio or Video is in use,Can not Open Preview.");
		ret = TE_SDK_OpenPreviewFailed;
		return ret;
	}
	ret = CDeviceMgr::Instance().OpenLocalVideoPreview(localWnd, devIndex);

	if (ret != TE_SDK_Success)
	{
		ERROR_LOG("TE_OpenPreview fail. ret:%d localWnd:%p devIndex:%d",ret,localWnd,devIndex);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%ld",devIndex);
	return ret;

}



/**************************************************
 * @fn         TE_ClosePreview
 * @brief      Close local specify camera video preview window
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_ClosePreview()
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CDeviceMgr::Instance().CloseLocalVideoPreview();

	if (ret != TE_SDK_Success)
	{
		ERROR_LOG("TE_ClosePreview fail. ret:%d",ret);
	}
	return ret;
}


/**************************************************
 * @fn         TE_GetCamerasInfo
 * @brief      Get Cameras Information 
 * @param[in]  cameraNum	Camera Number
 * @param[in]  cameraInfoList	Cameras Information
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_GetCamerasInfo(TE_UINT32 *cameraNum, TE_S_CAMERA_INFO *cameraInfoList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	int num = 0;
	ret = CDeviceMgr::Instance().GetCamerasInfo(cameraInfoList);
	num = CDeviceMgr::Instance().GetCamerasNum();
	*cameraNum = num;

	if (num < 0)
	{
		ret =  TE_SDK_NotFoundcamera;
	}
	else if (ret != TE_SDK_Success)
	{
		ERROR_LOG("TE_GetCamerasInfo fail. ret:%d cameraNum:%d",ret, *cameraNum);
	}
	sprintf_s(strParameter,sizeof(strParameter),"camerNum:%d,index:%d",cameraNum,cameraInfoList->ulIndex);
	return ret;
}


/**************************************************
 * @fn         TE_GetAudioInInfo
 * @brief      Get Audio input device Information
 * @param[out]  audioInNum	Audio input device Number
 * @param[out]  audioInInfoList	Audio input device Information
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetAudioInInfo(TE_UINT32 *audioInNum, TE_S_AUDIOIN_INFO *audioInInfoList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =TE_SDK_NullPtr;
	INFO_TRACE(strParameter,&ret,"");
	int Num = 0;

	if (audioInNum==NULL)
	{
		ERROR_LOG("audioInNum is null.");
		return ret;
	}
	if(audioInInfoList==NULL) 
	{
		ERROR_LOG("audioInInfoList is null.");
		return ret;
	}

	ret = CDeviceMgr::Instance().GetAudioInInfo(audioInInfoList);
	Num = CDeviceMgr::Instance().GetAudioInNum();

	if (Num< 0)
	{
		ret =  TE_SDK_NotFoundAudioIn;
	}
	else if (ret != TE_SDK_Success)
	{
		ERROR_LOG("TE_GetAudioInInfo fail. ret:%d audioInNum:%d",ret, *audioInNum);
	}
	*audioInNum = Num;
	sprintf_s(strParameter,sizeof(strParameter),"audionum:%d,name:%s,device type:%d,device no:%d,deviceifverified:%d,deviceifactive:%d",audioInNum,audioInInfoList->cName,audioInInfoList->bType,audioInInfoList->ulIndex,audioInInfoList->bIsCertified,audioInInfoList->bIsActive);
	return ret;
}


/**************************************************
 * @fn         TE_GetAudioOutInfo
 * @brief      Get Audio output device Information
 * @param[out]  audioOutNum	Audio output device Number
 * @param[out]  audioOutInfoList	Audio output device Information
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetAudioOutInfo(TE_UINT32 *audioOutNum, TE_S_AUDIOOUT_INFO *audioOutInfoList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =TE_SDK_NullPtr;
	INFO_TRACE(strParameter,&ret,"");
	int Num = 0;

	if (audioOutNum==NULL)
	{
		ERROR_LOG("audioInNum is null.");
		return ret;
	}
	if(audioOutInfoList==NULL) 
	{
		ERROR_LOG("audioInInfoList is null.");
		return ret;
	}

	ret = CDeviceMgr::Instance().GetAudioOutInfo(audioOutInfoList);
	Num = CDeviceMgr::Instance().GetAudioOutNum();

	if (Num < 0)
	{
		ret =  TE_SDK_NotFoundAudioOut;
	}
	else if (ret != TE_SDK_Success)
	{
		ERROR_LOG("TE_GetAudioOutInfo fail. ret:%d audioOutNum:%d",ret, *audioOutNum);
	}
	*audioOutNum = Num;
	sprintf_s(strParameter,sizeof(strParameter),"audioOutNum:%d,name:%s,device type:%d,device no:%d,deviceifverified:%d,deviceifactive:%d",audioOutNum,audioOutInfoList->cName,audioOutInfoList->bType,audioOutInfoList->ulIndex,audioOutInfoList->bIsCertified,audioOutInfoList->bIsActive);
	return ret;
}


/**************************************************
 * @fn         TE_SetAudioInDevice
 * @brief      Set Audio Input Device
 * @param[in]  index	Audio input index
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetAudioInDevice(TE_UINT32 index)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if(IMManager::Instance().HasAudioOrVideoInUse())
	{
		ret = TE_SDK_AudioVideoInUsedFailed;
		return ret;
	}

	if (!UCCLIENT()->DeviceManager->SetAudioCaptureDev(index))
	{
		ERROR_LOG("SetAudioCaptureDev failed !!");
		ret = TE_SDK_SetAudioCaptureDevFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d",index);
	return ret;
}



/**************************************************
 * @fn         TE_SetAudioOutDevice
 * @brief      Set Audio Output Device
 * @param[in]  index	Audio Output index
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetAudioOutDevice(TE_UINT32 index)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if(IMManager::Instance().HasAudioOrVideoInUse())
	{
		ret = TE_SDK_AudioVideoInUsedFailed;
		return ret;
	}

	if (!UCCLIENT()->DeviceManager->SetAudioPlayDev(index))
	{
		ERROR_LOG("SetAudioPlayDev failed !!");
		ret =  TE_SDK_SetAudioPlayDevFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d",index);
	return ret;
}


/**************************************************
 * @fn         TE_StartLecture
 * @brief      Start to share desktop/app
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @param[in]  shareWnd	Share window handle
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_StartLecture(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	if (!ShareEventHandler::requestsend_handle(callId))
	{
		ERROR_LOG("request send data failed!");
		ret = TE_SDK_SenddataFailed;	
	}
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d",callId);
	return ret;
}


/**************************************************
 * @fn         TE_StopLecture
 * @brief      Stop to share desktop/app
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StopLecture(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	if (!ShareEventHandler::stopsend_handle(callId))
	{
		ERROR_LOG("stop send data failed!");
		ret = TE_SDK_SenddataFailed;	
	}
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d",callId);
	return ret;
}


/**************************************************
 * @fn         TE_StartRecvLecture
 * @brief      Start to recieve data
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StartRecvLecture(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	if (!ShareEventHandler::startrecvdata_handle(callId))
	{
		ERROR_LOG("start recieve data failed!");
		ret = TE_SDK_RecvdataFailed;	
	}
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d",callId);
	return ret;
}


/**************************************************
 * @fn         TE_StopRecvLecture
 * @brief      stop to recieve data
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StopRecvLecture(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	if (!ShareEventHandler::stoprecvdata_handle(callId))
	{
		ERROR_LOG("stop recieve data failed!");
		ret = TE_SDK_RecvdataFailed;	
	}
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d",callId);
	return ret;
}


/**************************************************
 * @fn         TE_RejectRecvLecture
 * @brief      reject to recieve data
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RejectRecvLecture(TE_UINT32 callId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if (!ShareEventHandler::rejectrecvdata_handle(callId))
	{
		ERROR_LOG("reject recieve data failed!");
		ret = TE_SDK_RecvdataFailed;	
	}
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d",callId);
	return ret;
}


/**************************************************
 * @fn         TE_SetShareWindHandle
 * @brief      Set share window
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		sCall ID
 * @param[in]  shareWnd	share window handle
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetShareWindHandle(TE_UINT32 callId,HWND  shareWnd)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	CIMConversation* imConversation = NULL;
	imConversation = IMManager::Instance().GetIMConvByCallID(callId);

	if(!imConversation)
	{
		ret = TE_SDK_NotFoundCallID;
		return ret;
	}

	imConversation->m_hwndShared= shareWnd;
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d",callId);
	return ret;

}


/**************************************************
 * @fn         TE_SetUserConfig
 * @brief      Set user config
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
int __TE_SDK_CALL TE_SetNetworkConfig(TE_S_NETWORK_CONFIG networkConfig)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CSettingMgr::Instance().SetNetworkConfig(networkConfig);
	sprintf_s(strParameter,sizeof(strParameter),"mode:%d,auto reply:%d,bandwidth:%d,open_slide:%d,setFrameSize:%d,setDataRate:%d,setFrameRate:%d"
		,networkConfig.srtp_mode,networkConfig.media_auto_reply,networkConfig.media_bandwidth,networkConfig.media_open_slide,networkConfig.setFrameSize,
		networkConfig.setDataRate,networkConfig.setFrameRate);

	return ret; 
}


/**************************************************
 * @fn         TE_GetNetworkConfig
 * @brief      get network Configuration
 * @param[out]  network Configuration;
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetNetworkConfig(TE_UINT32 callId,TE_S_STREAM_INFO* callStreamInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	CIMConversation* imConversation = NULL;
	imConversation = IMManager::Instance().GetIMConvByCallID(callId);

	if(!imConversation)
	{
		ret = TE_SDK_NotFoundCallID;
		return ret;
	}

	conversation::Conversation* pConv = IMManager::Instance().GetCurConv(imConversation->m_convID);

	ret = CSettingMgr::Instance().GetNetworkConfig(pConv,callStreamInfo);
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,",callId);
	return ret; 
}


/**************************************************
 * @fn         TE_BFCPModifiedResult
 * @brief      deal with bfcp result
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  callId		Call ID
 * @param[in]  sessionType	result sessiontype
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_BFCPModifiedResult(TE_UINT32 callId,TE_UINT32 sessionType)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	CIMConversation* imConversation = NULL;
	imConversation = IMManager::Instance().GetIMConvByCallID(callId);

	if(!imConversation)
	{
		ret = TE_SDK_NotFoundCallID;
		return ret;
	}

	imConversation->OnCallConnect(sessionType);
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,sessionType:%d",callId,sessionType);
	return ret;
}

/**************************************************
 * @fn         TE_MBVoipLogForDLL
 * @brief      record log
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  type		log type
 * @param[in]  content	log content
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MBVoipLogForDLL(LOGTYPE type,TE_CHAR* content)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	switch(type)
	{
	case DEBUG_TYPE:
		{
		    DEBUG_LOG(content);
			break;
		}
	case ERROR_TYPE:
		{
			ERROR_LOG(content);
			break;
		}
	case WARN_TYPE:
		{
			WARN_LOG(content);
			break;
		}
	case INFO_TYPE:
		{
			INFO_LOG(content);
			break;
		}
	default:
		{
			break;
		}
	}
	sprintf_s(strParameter,sizeof(strParameter),"Log Type:%d,content:%d",type,content);
	return ret;
}

/**************************************************
 * @fn         TE_CreateConf
 * @brief      create conference
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  _contacts		vector of contacts' number 
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CreateConf(TE_S_SITE_INVITEDLIST * contacts)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if (NULL == contacts)
	{
		ERROR_LOG("TE_CreateConf(TE_S_SITE_INVITEDLIST * contacts)  parameter _contacts is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	if (contacts->listCount<0 || contacts->listCount>TE_D_CONF_SELECT_SITES_MAX)
	{
		ERROR_LOG("_contacts listCount is invalid value.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	if (0==contacts->listCount)
	{
		ERROR_LOG("no contacts to jion conference.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	
	std::vector<uc::model::Contact> m_vecConfSelectedList;
	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;

	
	for (int i=0;i<contacts->listCount;i++)
	{
		std::string inputnum ;
		uc::model::Contact contact_;

		inputnum=contacts->list[i];


		if (!inputnum.empty())
		{
			if (!ucclient->ContactManager->GetContactByAccount(inputnum,contact_))
			{
				//if it could not get contacts by local, it will search from net address book.
				if (!ucclient->ContactManager->GetNetContactByAcc(inputnum, contact_))  
				{
					contact_.name_ = contact_.mobile_ = inputnum;
				}
				else 
				{
					contact_.mobile_ = inputnum;
				}
			}
			else //when got it, it will assign value to mobile.
			{
				contact_.mobile_ = inputnum;
			}
			
			m_vecConfSelectedList.push_back(contact_);
		}

	}

	
	if(!UCCLIENT()->ConfManager->ConfCreate(m_vecConfSelectedList))
	{
		ret=TE_SDK_ConfCreateFailed;
	}
	sprintf_s(strParameter,sizeof(strParameter),"Enter Conference person numbers:%d",contacts->listCount);
	return ret;
}


/**************************************************
 * @fn         TE_GetLocalSite
 * @brief      get local hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[out]  localHall		local hall information 
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetLocalSite(TE_S_SITE_INFO * localHall)
{	
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	uc::model::Hall localH;
	(void)UCCLIENT()->ConfManager->GetLocalHall(localH);

	localHall->index_=localH.index_; 
	strncpy(localHall->name_,localH.name_.c_str(),TE_D_NUMBER_LEN);
	strncpy(localHall->number_,localH.number_.c_str(),TE_D_NUMBER_LEN);			
	localHall->T_=localH.T_;				
	localHall->M_=localH.M_;				
	localHall->isBroadcast_=localH.isBroadcast_;				
	localHall->isMute_=localH.isMute_;					
	localHall->isChairMan_=localH.isChairMan_;				
	localHall->isJoined_=localH.isJoined_;					
	localHall->isWatching_=localH.isWatching_;
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		localHall->index_,localHall->name_,localHall->number_,localHall->isBroadcast_,localHall->isMute_,localHall->isChairMan_,localHall->isJoined_,localHall->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_GetConfMemberSites
 * @brief      get members of conference
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[out]  _confHallList		information of members
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetConfMemberSites(TE_S_SITE_JIONEDLIST * confHallList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = TE_SDK_NullPtr;
	INFO_TRACE(strParameter,&ret,"");

	if (!confHallList)
	{
		return ret;
	}

	std::vector<uc::model::Hall> m_ConfListItemInfo;
	if(!UCCLIENT()->ConfManager->GetConfAttendeeList(m_ConfListItemInfo))
	{
		INFO_LOG("GetConfAttendeeList failed, vector is empty");
		ret = TE_SDK_GetConfMemberFailed;
		return ret;
	}

	int nCount=0;
	if (m_ConfListItemInfo.size()>TE_D_CONF_SELECT_SITES_MAX)
	{
		nCount=400;
	}
	else
	{
		nCount=m_ConfListItemInfo.size();
	}

	for (int i=0;i<nCount;i++)
	{
		confHallList->list[i].index_=m_ConfListItemInfo[i].index_;
		strncpy(confHallList->list[i].name_,m_ConfListItemInfo[i].name_.c_str(),TE_D_NAME_LEN);
		strncpy(confHallList->list[i].number_,m_ConfListItemInfo[i].number_.c_str(),TE_D_NUMBER_LEN);
		confHallList->list[i].T_=m_ConfListItemInfo[i].T_;				
		confHallList->list[i].M_=m_ConfListItemInfo[i].M_;				
		confHallList->list[i].isBroadcast_=m_ConfListItemInfo[i].isBroadcast_;				
		confHallList->list[i].isMute_=m_ConfListItemInfo[i].isMute_;					
		confHallList->list[i].isChairMan_=m_ConfListItemInfo[i].isChairMan_;				
		confHallList->list[i].isJoined_=m_ConfListItemInfo[i].isJoined_;					
		confHallList->list[i].isWatching_=m_ConfListItemInfo[i].isWatching_;

	}
	confHallList->listCount=nCount;
	sprintf_s(strParameter,sizeof(strParameter),"Enter conference person num:%d",confHallList->listCount);
	return ret;
}


/**************************************************
 * @fn         TE_IsConfChairMan
 * @brief      is the chairman of conference or not 
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode 
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_IsConfChairMan()
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}
	return ret;
}


/**************************************************
 * @fn         TE_SendDTMF
 * @brief      send DTMF
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @param[in]  _signal		the dtmf to send
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SendDTMF( TE_UINT32 callId,TE_CHAR* signal)
{	
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	std::string strSignal ;

	if (!signal)
	{
		ERROR_LOG("_signal  is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}

	DEBUG_LOG("signal :%s",signal);

	//cstrInputNum.Format(_T("%s"),eSDKTool::utf8_2_unicode(number));
	strSignal = signal;//eSDKTool::unicode_2_utf8(cstrInputNum.Trim());

	if (!strSignal.empty())
	{
		CIMConversation* p_IMConv=NULL;

		p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

		if (!p_IMConv)
		{
			ret = TE_SDK_NotFoundCallID;
			return ret;
		}
		AVSession* pSess = IMManager::Instance().GetAVsessByConvId(p_IMConv->m_convID);

		if (pSess)
		{

			int flag=0;

			for (unsigned int i=0;i<strlen(signal);i++)
			{
				strSignal=signal[i];
				if(!pSess->audiochannel_.SendDTMF(strSignal))
				{
					flag=1;
				}
			}
            if (flag == 1)
            {
				ret = TE_SDK_SendDTMFFailed;
				return ret;
            }
			
		}
		else
		{
			ret = TE_SDK_GetAVsessByConvIdFailed;
			return ret;
		}
	}
	else
	{
		ERROR_LOG("_signal is empty!");
		ret = TE_SDK_InvalidPara;
	}

	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,signal:%s",callId,signal);
	return ret;
}


/**************************************************
 * @fn         TE_UpdateCall
 * @brief      switch between audio and video
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		Call ID
 * @param[in]  callType	Call type
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_UpdateCall( TE_UINT32 callId, TE_E_CALL_TYPE callType)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ((callType < TE_E_CALL_TYPE_IPAUDIO) || (callType >= TE_E_CALL_TYPE_BUTT))
	{
		ERROR_LOG("call type is invalid value.");
		ret = TE_SDK_InvalidPara;
		return ret;	
	}

	CIMConversation* p_IMConv=NULL;

	p_IMConv = IMManager::Instance().GetIMConvByCallID(callId);

	if (!p_IMConv)
	{
		ret = TE_SDK_NotFoundCallID;
		return ret;
	}
	

	if (callType==TE_E_CALL_TYPE_IPAUDIO)
	{
		AVSession* pSess = IMManager::Instance().GetAVsessByConvId(p_IMConv->m_convID);

		if (!pSess)
		{
			ret = TE_SDK_GetAVsessByConvIdFailed;
			return ret ;
		}
		if (!pSess->videochannel_.Stop())
		{
			ret = TE_SDK_VideoChannelStopFailed;
			return ret;
		}		

	}
	else
	{
		if (FALSE == p_IMConv->AudioToVideoCall(TRUE))
		{
			ret = TE_SDK_AudioToVideoFailed;
			return ret;
		}

	}
	sprintf_s(strParameter,sizeof(strParameter),"callId:%d,call Type:%d",callId,callType);
	return ret;
}

/**************************************************
 * @fn         TE_SwitchCamera
 * @brief      switch camera
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		Call ID
 * @param[in]  _index	    camera index
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SwitchCamera(const TE_UINT32 index)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	//CIMConversation* p_IMConv=NULL;

	if(IMManager::Instance().HasAudioOrVideoInUse())
	{
		ret = TE_SDK_AudioVideoInUsedFailed;
		return ret;
	}

	if (UCCLIENT()->DeviceManager->SetVideoCaptureDev(index))
	{
		std::string txt = UCCLIENT()->DeviceManager->videodevlist[index]->name.c_str();
		std::string dec="VideoDevice";
		(void)USERCONFIG().SaveUserConfig(dec, txt);
		INFO_LOG("SETTING_MEDIA_VIDEODEVICE=[ %s", txt.c_str());
	}
	else
	{	
		ret = TE_SDK_SetVideoCaptureDevFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d",index);
	return ret;
}

 


/**************************************************
 * @fn         TE_SetDisplayName
 * @brief      set contact's nickname
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  _contactId		contact id
 * @param[in]  _contactName	    nickname that changed to be
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetDisplayName( TE_CHAR* contactNameOld, TE_CHAR* contactNameNew)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if (!contactNameOld)
	{
		ERROR_LOG("contactNameOld  is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}

	if (!contactNameNew)
	{
		ERROR_LOG("contactNameNew  is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}


	uc::model::Contact tmpContact;

	if(!UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(contactNameOld), tmpContact))
	{
		ERROR_LOG("contactNameOld not exist, name:%s",contactNameOld);
		ret = TE_SDK_GetContactFailed;
		return ret;
	}
	
	std::string  contactNames;
	contactNames=contactNameNew;

	if (contactNames.empty())
	{
		ERROR_LOG("contactName is empty!");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
    DEBUG_LOG("contactNameOld :%s,contactNameNew :%s",contactNameOld,contactNameNew);
	tmpContact.nickName_=eSDKTool::unicode_2_utf8(contactNames.c_str());
	tmpContact.Modify();
	sprintf_s(strParameter,sizeof(strParameter),"contactNameOld:%s,contactNameNew:%s",contactNameOld,contactNameNew);
	return ret;
}


/**************************************************
 * @fn         TE_ApplyConfChairman
 * @brief      apply to be the chairman 
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode 
 * @param[in]  _password		password to apply to be the chairman
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ApplyConfChairman(TE_CHAR* password)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	std::string  passWord;

	if (!password)
	{
		passWord="";
	}
	else
	{
		passWord=password;
	}

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("[ConfApplyChairManDlg]ConfApplyChairman failed not in conference");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if ( !UCCLIENT()->ConfManager->ConfApplyChairman(passWord) )
	{
		ERROR_LOG("[ConfApplyChairManDlg]ConfApplyChairman failed");
		ret = TE_SDK_ConfApplyChairManFailed;
		return ret;
	}
	return ret;
}



/**************************************************
 * @fn         TE_ReleaseConfChairman
 * @brief      give up the chairman 
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode 
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ReleaseConfChairman()
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}


	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if ( !UCCLIENT()->ConfManager->ConfReleaseChairman() )
	{
		INFO_LOG("ConfReleaseChairman failed");
		ret = TE_SDK_ConfReleaseChairManFailed;
		return ret;
	}
	return ret;
}


/**************************************************
 * @fn         TE_InviteSiteToConf
 * @brief      invite to jion conference
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  _contacts		people to be invited
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_InviteSiteToConf(TE_S_SITE_INVITEDLIST * contacts)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");


	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (NULL == contacts)
	{
		ERROR_LOG("TE_InviteSiteToConf(TE_S_SITE_INVITEDLIST * contacts)  parameter contacts is null pointer.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	if (contacts->listCount<0 || contacts->listCount>TE_D_CONF_SELECT_SITES_MAX)
	{
		ERROR_LOG("contacts listCount is invalid value.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}
	if (0==contacts->listCount)
	{
		ERROR_LOG("no contacts to be invited.");
		ret = TE_SDK_InvalidPara;
		return ret;
	}

	TE_S_SITE_JIONEDLIST _confHallList;
	memset(&_confHallList, 0, sizeof(TE_S_SITE_JIONEDLIST));
	TE_GetConfMemberSites(&_confHallList);
	if ( (_confHallList.listCount + contacts->listCount) > TE_D_CONF_SELECT_SITES_MAX)
	{
		ERROR_LOG("over maxmun can not be added to conference.");
		ret = TE_SDK_OverMax;
		return ret;
	}

	std::vector<uc::model::Contact> m_vecConfSelectedList;
	UCClient* ucclient = CTERegMgr::Instance().m_pUCClient;


	for (int i=0;i<contacts->listCount;i++)
	{
		std::string inputnum ;
		uc::model::Contact contact_;

		inputnum=contacts->list[i];


		if (!inputnum.empty())
		{
			if (!ucclient->ContactManager->GetContactByAccount(inputnum,contact_))
			{
				//if it could not get contacts by local, it will search from net address book.
				if (!ucclient->ContactManager->GetNetContactByAcc(inputnum, contact_))  
				{
					contact_.name_ = contact_.mobile_ = inputnum;
				}
				else 
				{
					contact_.mobile_ = inputnum;
				}
			}
			else //when got it, it will assign value to mobile.
			{
				contact_.mobile_ = inputnum;
			}

			m_vecConfSelectedList.push_back(contact_);

		}

	}

	if(!UCCLIENT()->ConfManager->ConfAddThisHall(m_vecConfSelectedList))
	{
		ERROR_LOG("invite to jion failed.");
		ret=TE_SDK_jionConfFailed;
	}
	sprintf_s(strParameter,sizeof(strParameter),"site Invite person num:%d",contacts->listCount);
	return ret;
}


/**************************************************
 * @fn         TE_ExtendConfTime
 * @brief      extend the time of conference
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  _time		minute to extend
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ExtendConfTime(TE_USHORT time)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}


	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!UCCLIENT()->ConfManager->ConfExtend(time))
	{
		ERROR_LOG("[ConfExtendTimeDlg]Extend time failed");
		ret = TE_SDK_ExtandConfFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"time:%d",time);
	return ret;
}


/**************************************************
 * @fn         TE_CallSiteToConf
 * @brief      call someone to jion the conference
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be called
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CallSiteToConf(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	} 

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}

	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;

	if(!UCCLIENT()->ConfManager->ConfCallOutHall(_confHall))
	{
		ERROR_LOG("call someone to jion conference failed");
		ret = TE_SDK_ConfCallOutHallFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_HandUpSite
 * @brief      handup one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be handup
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_HandUpSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");


	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}


	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;

	if(!UCCLIENT()->ConfManager->ConfHangUpHall(_confHall))
	{
		ERROR_LOG("hand up hall failed");
		ret = TE_SDK_ConfHangUpHallFailed;
		return ret ;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_DeleteSite
 * @brief      delete one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be deleted
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_DeleteSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");


	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}


	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;

	
	if(!UCCLIENT()->ConfManager->ConfDeleteHall(_confHall))
	{
		ERROR_LOG("delete hall failed");
		ret = TE_SDK_DeleteHallFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_MuteSite
 * @brief      mute one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be muted
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MuteSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");


	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}


	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;

	if(!UCCLIENT()->ConfManager->ConfMutehall(_confHall))
	{
		ERROR_LOG("mute hall failed");
		ret = TE_SDK_ConfMuteHallFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_UnMuteSite
 * @brief      unmute one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be unmuted
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_UnMuteSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}

	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;


	if(!UCCLIENT()->ConfManager->ConfUnMuteHall(_confHall))
	{
		ERROR_LOG("unmute hall failed");
		ret = TE_SDK_ConfUnMuteHallFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;

}


/**************************************************
 * @fn         TE_BroadCastSite
 * @brief      broadcast one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be broadcast
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_BroadCastSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}

	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;

	if(!UCCLIENT()->ConfManager->ConfBroadCastHall(_confHall))
	{
		ERROR_LOG("broadcast hall failed");
		ret = TE_SDK_ConfBroadCastHallFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;

}


/**************************************************
 * @fn         TE_UnBroadCastSite
 * @brief      stop broadcast one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be stoped broadcast
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_UnBroadCastSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}

	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;

	if(!UCCLIENT()->ConfManager->ConfUnBroadCastHall(_confHall))
	{
		ERROR_LOG("stop broadcast hall failed");
		ret = TE_SDK_ConfStopBroadFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_WatchSite
 * @brief      watch one hall
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  siteInfo		who to be watched
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_WatchSite(TE_S_SITE_INFO* siteInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH]={0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}

	if (!siteInfo)
	{
		ret = TE_SDK_NullPtr;
		return ret;
	}

	uc::model::Hall _confHall;
	_confHall.index_=siteInfo->index_;
	_confHall.name_=siteInfo->name_;
	_confHall.number_=siteInfo->number_;
	_confHall.T_=siteInfo->T_;
	_confHall.M_=siteInfo->M_;
	_confHall.isBroadcast_=siteInfo->isBroadcast_;
	_confHall.isMute_=siteInfo->isMute_;
	_confHall.isChairMan_=siteInfo->isChairMan_;
	_confHall.isJoined_=siteInfo->isJoined_;
	_confHall.isWatching_=siteInfo->isWatching_;


	if(!UCCLIENT()->ConfManager->ConfWatchHall(_confHall))
	{
		ERROR_LOG("watch hall failed");
		ret = TE_SDK_ConfWatchHallFailed;
		return ret;
	}
	sprintf_s(strParameter,sizeof(strParameter),"index:%d,name:%s,number:%s,isBroadcast:%d,isMute:%d,isChairMan:%d,isJoined:%d,isWatching:%d",
		siteInfo->index_,siteInfo->name_,siteInfo->number_,siteInfo->isBroadcast_,siteInfo->isMute_,siteInfo->isChairMan_,siteInfo->isJoined_,siteInfo->isWatching_);
	return ret;
}


/**************************************************
 * @fn         TE_EndConf
 * @brief      end the conference
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_EndConf()
{
	char strParameter[TE_D_MAXLOGLENGTH]={0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");

	if ( !UCCLIENT()->ConfManager->IsInConference())
	{
		ERROR_LOG("Not in conference.");
		ret = TE_SDK_NotInConference;
		return ret;
	}


	if(!UCCLIENT()->ConfManager->IsLocalChairMan())
	{
		ERROR_LOG("not conference chairman , no right to operate this function.");
		ret = TE_SDK_NotConfChairMan;
		return ret;
	}

	if ( !UCCLIENT()->ConfManager->ConfEnd() ) 
	{
		ERROR_LOG("ConfEnd failed!");
		ret = TE_SDK_ConfEndFailed;
		return ret;
	}
	return ret;
}



/**************************************************
 * @fn         TE_AddContact
 * @brief      Add Contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contact  information
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_AddContact(const TE_S_CONTACT_INFO   contact,const TE_CHAR* groupName)
{
	char strParameter[TE_D_MAXLOGLENGTH]={0};
	int ret =0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CAddrContacts::Instance().AddContact(contact,groupName);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_AddContact success");
	}
	else
	{
		ERROR_LOG("TE_AddContact failed,return value = %d",ret);
	}	
	sprintf_s(strParameter,sizeof(strParameter),"%s,%s,%s,%s",contact.addresssite,contact.deptname,contact.email,contact.mobile);
	return ret;
}

/**************************************************
 * @fn         TE_RemoveContact
 * @brief	 Remove Contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contact  information
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
 ESDK_TESERVICE_API int __TE_SDK_CALL TE_RemoveContact(const TE_CHAR* contactName,const TE_CHAR* groupName)
{
	char strParameter[TE_D_MAXLOGLENGTH]={0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == contactName)
	{
		ERROR_LOG("the pointer is empty");
		return ret;
	}
	if(NULL == groupName)
	{
		ERROR_LOG("the pointer is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().RemoveContact(contactName,groupName);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_RemoveContact success");
	}
	else
	{
		ERROR_LOG("TE_RemoveContact failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",contactName);
	return ret;
}

 /**************************************************
 * @fn         TE_EditContact
 * @brief	 Edit  Contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contact  information
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
 ESDK_TESERVICE_API int __TE_SDK_CALL TE_EditContact(const TE_S_CONTACT_INFO   contact)
 {
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
 	INFO_TRACE(strParameter,&ret,"");
	ret = CAddrContacts::Instance().EditContact(contact);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_EditContact success");
	}
	else
	{
		ERROR_LOG("TE_EditContact failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s,%s,%s,%s",contact.addresssite,contact.deptname,contact.email,contact.mobile);
	return ret;
 }

  /**************************************************
 * @fn         TE_ReplaceContact
 * @brief	 replace contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contact  information
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
 ESDK_TESERVICE_API int __TE_SDK_CALL TE_ReplaceContact(const TE_S_CONTACT_INFO   contact)
 {
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
 	INFO_TRACE(strParameter,&ret,"");
	ret = CAddrContacts::Instance().ReplaceContact(contact);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_ReplaceContact success");
	}
	else
	{
		ERROR_LOG("remove contact failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s,%s,%s,%s",contact.addresssite,contact.deptname,contact.email,contact.mobile);
	return ret;
 }

  /**************************************************
 * @fn         TE_GetContactList
 * @brief	 get  ContactList
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contact  information
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
 ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetContactList(const TE_E_USEKEY_SORT_RULE sortRule,TE_S_CONTACTS_INFO*   contactList )
 {
	 char strParameter[TE_D_MAXLOGLENGTH] = {0};
	 int ret = 0;
 	 INFO_TRACE(strParameter,&ret,"");
	 ret = TE_SDK_NullPtr;
	 if(NULL == contactList)
	 {
		 ERROR_LOG("the point is empty");
		 return ret ;
	 }
	 ret = CAddrContacts::Instance().GetContactList(contactList,sortRule);
	 if(TE_SDK_Success == ret )
	 { 
		 INFO_LOG("TE_GetContactList  success");
	 }
	 else
	 {
		ERROR_LOG("TE_GetContactList failed,return value = %d",ret);
	 }
	 sprintf_s(strParameter,sizeof(strParameter),"%d",contactList->num);
	 return ret;
 }

  /**************************************************
 * @fn         TE_SearchContact
 * @brief	 search contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchContact(const TE_CHAR*   keyword,TE_S_CONTACTS_INFO* contactsList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == keyword)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	if(NULL == contactsList)
	{
		DEBUG_LOG("the second point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().SearchContact(keyword,contactsList);
	if(TE_SDK_Success == ret)
	{
		 INFO_LOG("TE_SearchContact success");
	}
	else
	{
		ERROR_LOG("TE_SearchContact failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",keyword);
	return ret;
}

/**************************************************
 * @fn         TE_CreateCustomGroup
 * @brief      create customgroup
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CreateCustomGroup(const TE_CHAR* groupName)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == groupName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().CreateCustomGroup(groupName);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_CreateCustomGroup  success.");
	}
	else
	{	
		ERROR_LOG("TE_CreateCustomGroup failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",groupName);
	return ret;
}

/**************************************************
 * @fn         TE_RenameCustomGroup
 * @brief      rename customgroup
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RenameCustomGroup(const TE_CHAR* newName,const TE_CHAR* oldName)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == newName)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	if(NULL == oldName)
	{
		ERROR_LOG("the second point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().RenameCustomGroup(newName,oldName);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_RenameCustomGroup  success.");
	}
	else
	{
		ERROR_LOG("TE_RenameCustomGroup failed, return value :%d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s,%s",newName,oldName);
	return ret;
}

/**************************************************
 * @fn         TE_RemoveCustomGroup
 * @brief      remove customgroup
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RemoveCustomGroup(const TE_CHAR* strGrpName)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	if(NULL == strGrpName)
	{
		ERROR_LOG("the point is empty");
		ret = TE_SDK_NullPtr;
		return ret;
	}
	ret = CAddrContacts::Instance().RemoveCustomGroup(strGrpName);
	if(TE_SDK_Success ==ret)
	{
			INFO_LOG("TE_RemoveCustomGroup  success.");
	}
	else
	{
		ERROR_LOG("TE_RemoveCustomGroup failed,strGrpName = %s,return value = %d",strGrpName,ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",strGrpName);
	return ret;
}


/**************************************************
 * @fn         TE_GetCustomGroupList
 * @brief      get custom group list
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetCustomGroupList(TE_S_GROUPS_INFO*  groupsList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == groupsList)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().GetCustomGroupList(groupsList);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_GetCustomGroupList success");
	}
	else
	{
		ERROR_LOG("TE_GetCustomGroupList failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",groupsList->num);
	return ret;
}


/**************************************************
 * @fn         TE_GetCustomGroups
 * @brief      get custom groups
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetCustomGroups(const TE_CHAR* contactName,TE_S_GROUPS_INFO *groups)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == contactName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().GetCustomGroups(contactName,groups);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_GetCustomGroups success");
	}
	else
	{
		ERROR_LOG("TE_GetCustomGroups failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",contactName);
	return ret;
}

/**************************************************
 * @fn         TE_GetContactsInGroup
 * @brief      get contacts in group
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetContactsInGroup(const TE_CHAR* groupName,const TE_E_USEKEY_SORT_RULE sortRule,TE_S_CONTACTS_INFO *contacts)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == groupName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().GetContactsInGroup(groupName,sortRule,contacts);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_GetContactsInGroup success");
	}
	else
	{
		ERROR_LOG("TE_GetContactsInGroup failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",groupName);
	return ret;
}

/**************************************************
 * @fn         TE_CopyContactToGroup
* @brief      copy contact to group
* @return     Success return 0,
*			   Failure return errCode,see EM_TEServiceRetvCode
* @attention  you can operate address list when init.
 * @par 示例
* @code
* @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CopyContactToGroup(const TE_CHAR* contactName,const TE_CHAR* groupName)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == contactName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	if(NULL == groupName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().CopyContactToGroup(contactName,groupName);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_CopyContactToGroup success");
	}
	else
	{
		ERROR_LOG("TE_CopyContactToGroup failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",contactName);
	return ret;
}

/**************************************************
 * @fn         TE_MoveContactToGroup
* @brief      move contact to group
* @return     Success return 0,
*			   Failure return errCode,see EM_TEServiceRetvCode
* @attention  you can operate address list when init.
 * @par 示例
* @code
* @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MoveContactToGroup(const TE_CHAR* contactName,const TE_CHAR* newGroupName,const TE_CHAR* oldGroupName)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == contactName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	if(NULL == newGroupName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	if(NULL == oldGroupName)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().MoveContactToGroup(contactName,newGroupName,oldGroupName);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_MoveContactToGroup success");
	}
	else
	{
		ERROR_LOG("TE_MoveContactToGroup failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",contactName);
	return ret;
}

/**************************************************
 * @fn         TE_GetContactByName
* @brief      get contact by name
* @return     Success return 0,
*			   Failure return errCode,see EM_TEServiceRetvCode
* @attention  you can operate address list when init.
 * @par 示例
* @code
* @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetContactByName(const TE_CHAR* contactName,TE_S_CONTACT_INFO* contact)
{	
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == contactName)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	if(NULL == contact)
	{
		ERROR_LOG("the second point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().GetContactByName(contactName,contact);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_GetContactByName success");
	}
	else
	{
		ERROR_LOG("TE_GetContactByName failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",contactName);
	return ret;
}


/**************************************************
 * @fn         TE_ExportExcelFile
* @brief     ExportExcelFile
* @return     Success return 0,
*			   Failure return errCode,see EM_TEServiceRetvCode
* @attention  you can operate address list when init.
 * @par 示例
* @code
* @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ExportExcelFile(const TE_CHAR* strFilePath,const TE_S_GROUPS_INFO* groupList,const TE_UINT32 type)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == strFilePath)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().ExportExcelFile(strFilePath,groupList,type);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_ExportExcelFile success");
	}
	else
	{
		ERROR_LOG("TE_ExportExcelFile, strFilePath value = %s,return value = %d",strFilePath,ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s,%d",strFilePath,type);
	return ret;
}


/**************************************************
 * @fn         ImportFile
* @brief     import excel file
* @return     Success return 0,
*			   Failure return errCode,see EM_TEServiceRetvCode
* @attention  you can operate address list when init.
 * @par 示例
* @code
* @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ImportFile(const  TE_S_GROUPS_CHAIN* groupsList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == groupsList)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().ImportFile(groupsList);
	if(TE_SDK_Success == ret)
	{ 
		INFO_LOG("TE_ImportFile success");
	}
	else
	{
		ERROR_LOG("TE_ImportFile failed,return value = %d",ret);
	}
	return ret;
}

  /**************************************************
 * @fn         TE_ParseExcelFile
 * @brief		excel file
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ParseExcelFile(const TE_CHAR* strPath,TE_S_GROUPS_CHAIN**  groupChain)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == strPath)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().ParseExcelFile(strPath,groupChain);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_ParseExcelFile success");
	}
	else
	{
		ERROR_LOG("TE_ParseExcelFile failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",strPath);
	return ret;
}	

  /**************************************************
 * @fn         TE_ParseCSVFile
 * @brief		csv file
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ParseCSVFile(const TE_CHAR* strPath,TE_S_GROUPS_CHAIN**  groupChain)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == strPath)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}

	ret = CAddrContacts::Instance().ParseCSVFile(strPath,groupChain);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_ParseCSVFile success");
	}
	else
	{
		ERROR_LOG("TE_ParseExcelFile failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",strPath);
	return ret;
}

 /**************************************************
 * @fn         TE_SetVolume
 * @brief	   set mic or speak volume
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  volume		the size to set
 * @param[in]  type		    mic or speak
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetVolume(TE_INT32 volume,TE_E_VOLUME_TYPE type)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CDeviceMgr::Instance().SetVolume(volume,type);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_SetVolume success");
	}
	else
	{
		ERROR_LOG("TE_SetVolume failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d,%d",volume,type);
	return ret;
}

 /**************************************************
 * @fn         TE_GetVolume
 * @brief	   get mic or speak volume
 * @return     the volume of mic or speak  
 * @param[in]  type		    mic or speak
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetVolume(TE_E_VOLUME_TYPE type)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CDeviceMgr::Instance().GetVolume(type);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_GetVolume success");
	}
	else
	{
		ERROR_LOG("TE_GetVolume failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",type);
	return ret;
}

 /**************************************************
 * @fn         TE_SetLogSwitch
 * @brief	   set log switch
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  logSwitch		    flag to log switch
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLogSwitch(TE_INT32 logSwitch)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	SET_LOG_SWITCH(logSwitch);


	string ivalue="";
	if (logSwitch==0)
	{
		ivalue="0";
	} 
	else
	{
		ivalue="1";
	}

	std::string path;
	eSDKTool::getCurrentPath(path);
	std::string strLogCfgFile = path+"\\eSDKClientLogCfg.ini";
	(void)::WritePrivateProfileString(eSDKTool::utf82unicode(LOGSWITCH).c_str(), eSDKTool::utf82unicode("switchflag").c_str(), eSDKTool::utf82unicode(ivalue).c_str(), eSDKTool::utf82unicode(strLogCfgFile).c_str());  
	sprintf_s(strParameter,sizeof(strParameter),"%d",logSwitch);
	return TE_SDK_Success;
}



/**************************************************
 * @fn         TE_SetLogPath
 * @brief	   set log path
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  logPath		    log path
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLogPath(TE_CHAR* logPath)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_InvalidPara;
	if (!logPath)
	{
		ERROR_LOG("logPath  is null pointer.");
		return ret;
	}
	std::string path;
	eSDKTool::getCurrentPath(path);
	std::string strLogCfgFile = path+"\\eSDKClientLogCfg.ini";
	(void)::WritePrivateProfileString(eSDKTool::utf82unicode(LOGPATH).c_str(), eSDKTool::utf82unicode("path").c_str(), eSDKTool::utf82unicode(logPath).c_str(), eSDKTool::utf82unicode(strLogCfgFile).c_str());  
	sprintf_s(strParameter,sizeof(strParameter),"%s",logPath);
	ret = TE_SDK_Success;
	return ret;
}

 /**************************************************
 * @fn         TE_GetEnterpriseBookType
 * @brief		get enterprise book type
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetEnterpriseBookType(TE_UINT32* enterpriseType)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == enterpriseType)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	uc::model::UCClient::NetAddressBookType type = UCCLIENT()->GetCurrentNetAddressBookType();
	
	if (type == uc::model::UCClient::NetAddressBook_FTPS)
	{
		*enterpriseType = TE_D_FTPTYPE;
	}
	else if (type == uc::model::UCClient::NetAddressBook_LDAPS)
	{
		*enterpriseType = TE_D_LDAPTYPE;
	}
	else
	{
		ret = TE_SDK_GetEnterpriseContactsFailed;
		return ret;
	}
	ret = TE_SDK_Success;
	sprintf_s(strParameter,sizeof(strParameter),"%d",*enterpriseType);
	return ret;
}

  /**************************************************
 * @fn         TE_SearchLdap
 * @brief	 start search ldap
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchLdap(const TE_CHAR*   keyword)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == keyword)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().StartSearchByKey(keyword);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_SearchLdap success");
	}
	else
	{
		ERROR_LOG("TE_SearchLdap failed,return value = %d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",keyword);
	return ret;
}

 /**************************************************
 * @fn         TE_SearchFtp
 * @brief	 start search ftp
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchFtp(const TE_CHAR*   keyword,TE_S_CONTACTS_INFO* contactsList)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == keyword)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	if(NULL == contactsList)
	{
		ERROR_LOG("the second point is empty");
		sprintf_s(strParameter,sizeof(strParameter),"%s",keyword);
		return ret;
	}
	if(strlen(keyword)>TE_D_NAME_LEN)
	{
		sprintf_s(strParameter,sizeof(strParameter),"%s",keyword);
		return TE_SDK_ExceedNameLength;
	}
	uc::model::UCClient::NetAddressBookType type = UCCLIENT()->GetCurrentNetAddressBookType();
	if (type == uc::model::UCClient::NetAddressBook_FTPS)
	{
		if(TE_SDK_Success == CAddrContacts::Instance().StartSearchFtp(keyword,contactsList))
		{
			INFO_LOG("TE_SearchFtp  success");
			ret = TE_SDK_Success;
			sprintf_s(strParameter,sizeof(strParameter),"%s,%d",keyword,contactsList->num);
			return ret;
		}
		else
		{
			ERROR_LOG("TE_SearchFtp,keyword = %s",keyword);
			ret = TE_SDK_SearchFtpFailed;
			sprintf_s(strParameter,sizeof(strParameter),"%s,%d",keyword,contactsList->num);
			return ret;
		}
	}
	else
	{
		ret = TE_SDK_SearchFtpFailed;
		sprintf_s(strParameter,sizeof(strParameter),"%s,%d",keyword,contactsList->num);
		return ret;
	}
	
}

  /**************************************************
 * @fn         TE_GetAllEnterpriseContacts
 * @brief		get all enterprise contacts
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetAllEnterpriseContacts(TE_S_CONTACTS_INFO* enterpriseContacts)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == enterpriseContacts)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	ret = CAddrContacts::Instance().GetAllEnterpriseContacts(enterpriseContacts);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_GetAllEnterpriseContacts success");
	}
	else
	{
		ERROR_LOG("TE_GetAllEnterpriseContacts failed,%d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",enterpriseContacts->num);
	return ret;
}

  /**************************************************
 * @fn         TE_ClearAllCallRecord
 * @brief		clear all record
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ClearAllCallRecord()
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = CHistroyRecord::Instance().OnRMenuClearAllRecord();
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_ClearAllCallRecord success");
	}
	else
	{
		ERROR_LOG("TE_ClearAllCallRecord failed,%d",ret);
	}
	return ret;
}

  /**************************************************
 * @fn         TE_DeleteOneCallRecord
 * @brief		clear one record
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_DeleteOneCallRecord(const TE_CHAR* histroyRecordId)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == histroyRecordId)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	if(strlen(histroyRecordId)>TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}
	std::string pstrRecordID = histroyRecordId;
	
	long RcdId  = eSDKTool::str2num<long>(pstrRecordID);
	ret = CHistroyRecord::Instance().OnRMenuClearOneRecord(RcdId);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_DeleteOneCallRecord success");
	}
	else
	{
		ERROR_LOG("TE_DeleteOneCallRecord failed,%d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s",histroyRecordId);
	return ret;
}

  /**************************************************
 * @fn         TE_SearchHistoryRecords
 * @brief		search history records
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchHistoryRecords(const TE_CHAR* historyKey,TE_S_PERSONS_INFO* historyRecords)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == historyKey)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	if(NULL == historyRecords)
	{
		ERROR_LOG("the second point is empty");
		return ret;
	}
	if(strlen(historyKey)>TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}
	/* begin:modified by l00220604 2013/09/26 Reason: annotate for DTS2013092302176 */
	std::string key;
	key = historyKey;
	ret = CHistroyRecord::Instance().InsertResultIntoCurRecordList(key,historyRecords);  //搜索更
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_SearchHistoryRecords success");
	}
	else
	{
		ERROR_LOG("TE_SearchHistoryRecords failed,%d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%s,%d",historyKey,historyRecords->num);
	return ret;
}

  /**************************************************
 * @fn         TE_GetRecentCallRecords
 * @brief		get recent call records
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetRecentCallRecords(TE_S_PERSONS_INFO* historyInfo)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	ret = TE_SDK_NullPtr;
	if(NULL == historyInfo)
	{
		ERROR_LOG("the first point is empty");
		return ret;
	}
	CHistroyRecord::Instance().InitRecentCallList();
	ret = CHistroyRecord::Instance().GetAllHistoryCallRecords(historyInfo);
	if(TE_SDK_Success == ret)
	{
		INFO_LOG("TE_GetRecentCallRecords success");
	}
	else
	{
		ERROR_LOG("TE_GetRecentCallRecords failed,%d",ret);
	}
	sprintf_s(strParameter,sizeof(strParameter),"%d",historyInfo->num);
	return ret;
}

  /**************************************************
 * @fn         TE_FreeMemory
 * @brief		free memory
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_FreeMemory(TE_VOID* point)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	int ret = 0;
	INFO_TRACE(strParameter,&ret,"");
	sprintf_s(strParameter,sizeof(strParameter),"%p",point);
	ret = TE_SDK_NullPtr;
	if(NULL == point)
	{
		ERROR_LOG("the point is empty");
		return ret;
	}
	free(point);
	ret = TE_SDK_Success;
	return ret;
}