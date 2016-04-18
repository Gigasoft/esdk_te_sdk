
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
 * @file  TEService.h   
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


#ifndef _CESDK_TESERVICE_H
#define _CESDK_TESERVICE_H
#include "TESDK.h"
#include "stdafx.h"
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ESDK_TESERVICE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ESDK_TESERVICE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。




#ifdef __cplusplus
extern "C"
{
#endif



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SDK_Init(void);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SDK_Release(void);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SDK_Login(const TE_S_LOGIN_INFO *pLoginReqInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SDK_SetEventCallBack(EventCallBack fEventCallBack = NULL, TE_VOID *pUserData = NULL);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SDK_Logout();

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MakeCall(TE_CHAR* number, TE_E_CALL_TYPE callType);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_DropCall(TE_UINT32 callId);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RejectCall(TE_UINT32 callId);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_AnswerAudioCall(TE_UINT32 callId);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_AnswerVideoCall(TE_UINT32 callId, TE_BOOL isAudioAccept);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLocalSpeaker(TE_UINT32 callId,TE_BOOL flag);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLocalMic(TE_UINT32 callId,TE_BOOL flag);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLocalVideo(TE_UINT32 callId,TE_BOOL flag);


//noused
/**************************************************
 * @fn         TE_SetDisplayHandle
 * @brief      Set local and remote display window
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		sCall ID
 * @param[in]  localWnd	Local window handle
 * @param[in]  remote_wnd	Remote window handle
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
//ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetDisplayHandle(TE_UINT32 callId,HWND  localWnd, HWND  remote_wnd);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetDisplayHandle(HWND  localWnd, HWND  remote_wnd,HWND hwndData);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_OpenPreview(HWND  localWnd, TE_ULONG devIndex);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ClosePreview();



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetCamerasInfo(TE_UINT32 *cameraNum, TE_S_CAMERA_INFO *cameraInfoList);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetAudioInInfo(TE_UINT32 *audioInNum, TE_S_AUDIOIN_INFO *audioInInfoList);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetAudioOutInfo(TE_UINT32 *audioOutNum, TE_S_AUDIOOUT_INFO *audioOutInfoList);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetAudioInDevice(TE_UINT32 index);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetAudioOutDevice(TE_UINT32 index);


/**************************************************
 * @fn         TE_SetNetworkConfig
 * @brief      Set TE Configuration
 * @param[in]  networkConfig	network config include srtp mode;media bandwidth;open slide;auto reply;
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetNetworkConfig(TE_S_NETWORK_CONFIG networkConfig);



/**************************************************
 * @fn         TE_GetNetworkConfig
 * @brief      get network Configuration
 * @param[in]  callId     Call ID
 * @param[out]  network Configuration;
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetNetworkConfig(TE_UINT32 callId,TE_S_STREAM_INFO* callStreamInfo);



/**************************************************
 * @fn         TE_StartLecture
 * @brief      Start to share desktop/app
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @param[in]  shareWnd	Share window handle
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StartLecture(TE_UINT32 callId);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StopLecture(TE_UINT32 callId);


/**************************************************
 * @fn         TE_StartRecvLecture
 * @brief      Start to recieve data
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StartRecvLecture(TE_UINT32 callId);


/**************************************************
 * @fn         TE_StopRecvLecture
 * @brief      stop to recieve data
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_StopRecvLecture(TE_UINT32 callId);


/**************************************************
 * @fn         TE_RejectRecvLecture
 * @brief      reject to recieve data
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		CALL ID
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RejectRecvLecture(TE_UINT32 callId);


/**************************************************
 * @fn         TE_SetShareWindHandle
 * @brief      Set share window
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		sCall ID
 * @param[in]  shareWnd	share window handle
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetShareWindHandle(TE_UINT32 callId,HWND  shareWnd);


//noused
/**************************************************
 * @fn         TE_SetDisplayShareHandle
 * @brief      Set to display share window
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  callId		sCall ID
 * @param[in]  diaplayshare_wnd	 handle to display share window
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
//ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetDisplayShareHandle(TE_UINT32 callId,HWND  displayShareWnd);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_BFCPModifiedResult(TE_UINT32 callId,TE_UINT32 sessionType);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MBVoipLogForDLL(LOGTYPE type,TE_CHAR* content);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CreateConf(TE_S_SITE_INVITEDLIST * contacts);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetLocalSite(TE_S_SITE_INFO * localHall);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetConfMemberSites(TE_S_SITE_JIONEDLIST * confHallList);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_IsConfChairMan();



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ApplyConfChairman(TE_CHAR* password);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ReleaseConfChairman();



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SendDTMF( TE_UINT32 callId,TE_CHAR* signal);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_UpdateCall( TE_UINT32 callId, TE_E_CALL_TYPE callType);
 
/**************************************************
 * @fn         TE_SwitchCamera
 * @brief      switch camera
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  _index	    camera index
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SwitchCamera(const TE_UINT32 index);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetDisplayName( TE_CHAR* contactNameOld, TE_CHAR* contactNameNew);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_InviteSiteToConf(TE_S_SITE_INVITEDLIST * contacts);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ExtendConfTime(TE_USHORT time);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CallSiteToConf(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_HandUpSite(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_DeleteSite(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MuteSite(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_UnMuteSite(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_BroadCastSite(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_UnBroadCastSite(TE_S_SITE_INFO* siteInfo);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_WatchSite(TE_S_SITE_INFO* siteInfo);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_EndConf();



/**************************************************
 * @fn         TE_AddContact
 * @brief      add new contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contacter
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_AddContact(const TE_S_CONTACT_INFO   contact,const TE_CHAR* groupName);


/**************************************************
 * @fn         TE_ RemoveContact
 * @brief      remove  contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contacter
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RemoveContact(const TE_CHAR*   contactName,const TE_CHAR* groupName);

/**************************************************
 * @fn         TE_EditContact
 * @brief      edit  contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contacter
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_EditContact(const TE_S_CONTACT_INFO   contact);


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
 ESDK_TESERVICE_API int __TE_SDK_CALL TE_ReplaceContact(const TE_S_CONTACT_INFO   contact);

/**************************************************
 * @fn         TE_GetContactList
 * @brief      get  contactlist
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  contact		contacter
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetContactList(const TE_E_USEKEY_SORT_RULE sortRule,TE_S_CONTACTS_INFO*  contactsList);


/**************************************************
 * @fn         TE_SearchContact
 * @brief     search contact
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchContact(const TE_CHAR*   keyword,TE_S_CONTACTS_INFO*  contactsList);



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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CreateCustomGroup(const TE_CHAR* groupName);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RenameCustomGroup(const TE_CHAR* newName,const TE_CHAR* oldName);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_RemoveCustomGroup(const TE_CHAR* strGrpName);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetCustomGroupList(TE_S_GROUPS_INFO*  groupsList);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetCustomGroups(const TE_CHAR* contactName,TE_S_GROUPS_INFO *groups);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetContactsInGroup(const TE_CHAR* groupName,const TE_E_USEKEY_SORT_RULE sortRule,TE_S_CONTACTS_INFO *contacts);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetContactByName(const TE_CHAR* contactName,TE_S_CONTACT_INFO* contact);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_CopyContactToGroup(const TE_CHAR* contactName,const TE_CHAR* groupName);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_MoveContactToGroup(const TE_CHAR* contactName,const TE_CHAR* newGroupName,const TE_CHAR* oldGroupName);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ExportExcelFile(const TE_CHAR* strFilePath,const TE_S_GROUPS_INFO* groupList,const TE_UINT32 type);

/**************************************************
 * @fn         TE_ImportFile
* @brief     import  file
* @return     Success return 0,
*			   Failure return errCode,see EM_TEServiceRetvCode
* @attention  you can operate address list when init.
 * @par 示例
* @code
* @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ImportFile(const TE_S_GROUPS_CHAIN* groupsList);


  /**************************************************
 * @fn         TE_ParseExcelFile
 * @brief		parse excel file
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode   
 * @param[in]  keyword		search word
 * @attention  
 * @par 
 * @code
 * @endcode
****************************************************/
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ParseExcelFile(const TE_CHAR* strPath,TE_S_GROUPS_CHAIN**  groupChain);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ParseCSVFile(const TE_CHAR* strPath,TE_S_GROUPS_CHAIN**  groupChain);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetVolume(TE_INT32 volume,TE_E_VOLUME_TYPE type);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetVolume(TE_E_VOLUME_TYPE type);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLogSwitch(TE_INT32 logSwitch);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SetLogPath(TE_CHAR* logPath);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetAllEnterpriseContacts(TE_S_CONTACTS_INFO* enterpriseContacts);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetEnterpriseBookType( TE_UINT32* enterpriseType);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchLdap(const TE_CHAR*   keyword);


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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchFtp(const TE_CHAR*   keyword,TE_S_CONTACTS_INFO* contactsList);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_ClearAllCallRecord();

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_DeleteOneCallRecord(const TE_CHAR* histroyRecordId);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_SearchHistoryRecords(const TE_CHAR* historyKey,TE_S_PERSONS_INFO* historyRecords);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_GetRecentCallRecords(TE_S_PERSONS_INFO* historyInfo);

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
ESDK_TESERVICE_API int __TE_SDK_CALL TE_FreeMemory(TE_VOID* point);


#ifdef __cplusplus
}
#endif 
#endif