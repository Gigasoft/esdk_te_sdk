
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
 * @file  TESDK.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief TE Desktop SDK Interface
 * @details declare data struct, enum value and  macro define
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK Interface
****************************************************/

#ifndef _TE_SDK_H_
#define _TE_SDK_H_

//#include "stdafx.h"

#ifdef ESDK_TESERVICE_EXPORTS

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

#define ESDK_TESERVICE_API __declspec(dllexport)
#else
#define ESDK_TESERVICE_API __declspec(dllimport)
#endif

#ifdef WIN32
#define __TE_SDK_CALL __stdcall
#else
#define __TE_SDK_CALL
#endif

const int TE_D_NAME_LEN = 64;					//名字长度
const int TE_D_NUMBER_LEN = 64;			//账号长度
const int TE_D_URI_LEN = 128;					//URL长度
const int TE_D_PWD_LEN = 32;					//密码长度
const int TE_D_IP_LEN = 64;							//IP长度
const int TE_D_TIME_LEN = 64;					//时间长度
const int TE_D_MESSAGE_LEN = 100;		//信息长度
const int TE_D_DEVICE_MAX_NUM = 10;	//设备最大数
const int TE_D_DESC_MAX_NUM = 1024;
const int TE_D_CONF_SELECT_SITES_MAX = 400;//最多选择400个会场入会
const int TE_D_PROTOCOL_LENGTH=30;  /** 协议名字长度 */
const int TE_MAX_CODEC_NAME_LEN = 31; /** 音视频编解码名称长度 */
const int TE_MAX_FRAMESIZE_LEN =16;  /** 视频分辨率长度 */    
const int TE_MAX_PROFILE_LEN =8;   /** 视频编解码格式长度*/
const int TE_D_PHONE_LEN = 20; // 电话长度
const int TE_D_ADDRESS_LEN = 80; //地址长度
const int TE_D_DEPARTNAME_LEN = 64; // 部门长度
const int TE_D_EMAIL_LEN = 100; //local part 部分不能超过的邮件长度
const int TE_D_GROUPNAME_LEN =64; //分组名长度
const int TE_D_DESCRIPTION_LEN = 100;//描述长度
const int TE_D_ID_LEN = 10; //ID 长度
const int TE_D_LDAPTYPE = 1;//ldap 类型
const int TE_D_FTPTYPE = 0; //ftp 类型
const int TE_D_MAXLOGLENGTH = 1024; //最大日志长度

const char LOGSWITCH[]="LOGSWITCH";
const char LOGPATH[]="LOGPATH";
//const int TE_D_MAX_CODEC_LIST_LEN=127; /** 编解码list最大长度*/
//const int TE_D_IP_LENGTH = 16;	//IP
//const int TE_D_MAX_LENGTH_NUM = 256;	//号码


// 类型定义
typedef  int                TE_RESULT;
typedef  char               TE_CHAR;
typedef unsigned int		TE_UINT32;
typedef unsigned short		TE_USHORT;
typedef char				TE_INT8;
typedef unsigned char       TE_UINT8;
typedef bool				TE_BOOL;
typedef unsigned long		TE_ULONG;
typedef void				TE_VOID;
typedef int					TE_INT32;
typedef float				TE_FLOAT;
typedef unsigned short      TE_UINT16;
typedef short				TE_SHORT;


//typedef std::vector<char*>  TE_VEC_PCHAR;
//typedef std::vector<TE_S_SITE_INFO>  TE_VEC_HALL;

typedef enum tagTE_E_CFG_MAJOR_TYPE
{
	TE_E_CFG_CALLENV = 1, /*环境变量*/
	TE_E_CFG_SERVER,      /*服务器地址*/
	TE_E_CFG_NET,         /*本地网络接口地址*/
	TE_E_CFG_USERAGENT,
	TE_E_CFG_SERVRIGHT,   /*业务权限*/
	TE_E_CFG_DSCP,        /*DSCP*/    
	TE_E_CFG_SIP,         /*SIP信令配置*/
	TE_E_CFG_ACCOUNT,
	TE_E_CFG_COMPATIBLE_PARAM,
	TE_E_CFG_CONF,        /*会议相关设置*/
	TE_E_CFG_MEDIA,       /* 媒体全局配置*/
	TE_E_CFG_AUDIO,       /*音频配置*/
	TE_E_CFG_VIDEO,       /*视频配置 & 辅流配置*/
	TE_E_CFG_BFCP,        /*辅流BFCP配置*/
	TE_E_CFG_MOBILE_VOICEMAIL,   /*移动语音邮箱权限*/
	TE_E_CFG_BUTT
}TE_E_CFG_MAJOR_TYPE;



typedef enum tagTE_E_CFG_DATA_TYPE
{
	TE_E_CFG_DATA_TYPE_INT = 0x01,     
	TE_E_CFG_DATA_TYPE_STRING = 0x02,             
	TE_E_CFG_DATA_TYPE_STRUCTURE = 0x04,   
	TE_E_CFG_DATA_TYPE_BOOL = 0x08,
	TE_E_CFG_DATA_TYPE_BUTT,

} TE_E_CFG_DATA_TYPE;


// 排序规则
typedef enum tagTE_E_USEKEY_SORT_RULE
{
	group_status_first = 0,        // 分组下按状态和名称
	group_name_first,              // 分组下按名称
	do_not_sort                    // 不要排序
}TE_E_USEKEY_SORT_RULE;

#define TE_CFG_ID_DEF(major,datatype,_id,_index)    ((major)<<24|((datatype) << 16)|(_id) <<8|(_index))

/* 视频配置 & 辅流配置(相同功能需保持与视频配置前3个字节一致，最后一个字节是1)*/
#define TE_D_CFG_VIDEO_FRAMESIZE          TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 0) //分辨率 (TE_S_VIDEO_FRAMESIZE
#define TE_D_CFG_DATA_FRAMESIZE           TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 1) //分辨率 (TE_S_VIDEO_FRAMESIZE
#define TE_D_CFG_VIDEO_DATARATE           TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 0) //码率 (TE_S_VIDEO_DATARATE
#define TE_D_CFG_DATA_DATARATE            TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 1) //码率 (TE_S_VIDEO_DATARATE
#define TE_D_CFG_VIDEO_FRAMERATE          TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 0) //帧率 (TE_S_VIDEO_FRAMERATE)
#define TE_D_CFG_DATA_FRAMERATE           TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 1) //帧率 (TE_S_VIDEO_FRAMERATE)


#define EXCEL_POSTFIX               _T("xls")         // Excel文件后缀
#define EXCEL2007_POSTFIX           _T("xlsx")        // EXCEL2007文件后缀
#define EXCEL2010_POSTFIX           _T("xlsx")        // EXCEL2010文件后缀
#define EXCEL2012_POSTFIX           _T("xlsx")        // EXCEL2012文件后缀
#define CSV_POSTFIX                 _T("csv")         // csv文件后缀
#define POSTFIX_COUNT               3			      // 后缀名的个数
#define VNET_KEY_ROW_POS            1                 // V网伴侣文件关键字所在的行,即标题关键字
const static int STADNTILENUM       = 13;              // 标准标题头字段数,最后一个字段为空
const static int STADNTILENUM_OLD   = 7;              // 标准标题头字段数,最后一个字段为空(以前的字段数)

typedef struct tagTE_S_VIDEO_FRAMESIZE
{
	TE_UINT32 uiFramesize;         //编码分辨率
	TE_UINT32 uiMinFramesize;      //最小编码分辨率
	TE_UINT32 uiDecodeFrameSize;   //解码最大分辨率
} TE_S_VIDEO_FRAMESIZE;

typedef struct tagTE_S_VIDEO_DATARATE
{
	TE_UINT32 ulDataRate;     //码率
	TE_UINT32 ulMinDataRate;  //最小码率
	TE_UINT32 ulMaxDataRate;  //最大码率
	TE_UINT32 ulMaxBw;        //最大带宽
} TE_S_VIDEO_DATARATE;

typedef struct tagTE_S_VIDEO_FRAMERATE
{
	TE_UINT32 uiFrameRate;   //帧率
	TE_UINT32 uiMinFrameRate; //最小帧率
} TE_S_VIDEO_FRAMERATE;

typedef struct tagTE_S_SITE_INFO
{
	unsigned int index_;                    //序号
	TE_CHAR  name_[TE_D_NAME_LEN+1];	//会场名
	TE_CHAR  number_[TE_D_NUMBER_LEN+1];			//号码
	short T_;				//会场T号
	short M_;				//会场M号
	bool isBroadcast_;				//是否在广播中
	bool isMute_;					//是否闭音状态
	bool isChairMan_;				//是否是主席
	bool isJoined_;					//是否入会
	bool isWatching_;

}TE_S_SITE_INFO;

typedef struct tagTE_S_PERSON_INFO 
{
	long itemID;
	TE_CHAR cvsID[TE_D_ID_LEN];					//记录的会议ID
	long long recordID;							//记录ID
	int		nUserId;							//用户ID
	TE_CHAR strAcc[TE_D_NUMBER_LEN+1];			//账号
	TE_CHAR strName[TE_D_NAME_LEN+1];			//名字
	TE_CHAR strPhone[TE_D_PHONE_LEN+1];			//电话号码
	TE_CHAR strMessage[TE_D_MESSAGE_LEN+1];	    //信息
	TE_CHAR strTime[TE_D_TIME_LEN+1];			//时间
	TE_CHAR strDuration[TE_D_TIME_LEN+1];		//持续时间
	int		nPersonStatus;						//用户状态
	int		nPhoneStatus;				    	//	电话状态
	TE_CHAR strPersonIcon[TE_D_NAME_LEN+1];		//个人头像
	int nCalltype;                              //呼叫类型
}TE_S_PERSON_INFO;

typedef struct tagTE_S_PERSONS_INFO
{
	TE_S_PERSON_INFO* historyRecords;
	TE_INT32 num;                      

}TE_S_PERSONS_INFO;

typedef struct tagTE_S_SITE_INVITEDLIST
{

	TE_CHAR* list[TE_D_CONF_SELECT_SITES_MAX+1];  //要入会人员列表
	TE_INT32 listCount;                              //要入会人数
	
}TE_S_SITE_INVITEDLIST;


typedef struct tagTE_S_SITE_JIONEDLIST
{

	TE_S_SITE_INFO list[TE_D_CONF_SELECT_SITES_MAX];     //已入会人员信息列表
	TE_INT32 listCount;                                //已入会人数

}TE_S_SITE_JIONEDLIST;


/** SIP账户注册状态*/
typedef enum tagTE_E_REG_STATE
{
    TE_E_REG_STATE_UNREGISTER,     /**< SIP账户未注册*/
    TE_E_REG_STATE_REGISTERING,    /**< SIP账户注册中*/
    TE_E_REG_STATE_DEREGISTERING,  /**< SIP账户注销中*/
    TE_E_REG_STATE_REGISTERED,     /**< SIP账户已注册*/
    TE_E_REG_STATE_BUTT            /**< SIP账户无效状态*/
} TE_E_REG_STATE;

/*呼叫类型*/
typedef enum tagTE_E_CALL_TYPE
{
    TE_E_CALL_TYPE_IPAUDIO,					//IP语音呼叫
    TE_E_CALL_TYPE_IPVIDEO,					//IP视频呼叫
    TE_E_CALL_TYPE_BUTT						//无效类型呼叫
} TE_E_CALL_TYPE;

/*呼叫基本状态*/
typedef enum tagTE_E_CALL_STATE
{
    TE_E_CALL_STATE_IDLE,					//呼叫空闲态
    TE_E_CALL_STATE_IN,						//呼叫呼入态
    TE_E_CALL_STATE_OUT,					//呼叫呼出态
    TE_E_CALL_STATE_LIVE,					//呼叫通话态
    TE_E_CALL_STATE_HOLD,					//呼叫保持态
    TE_E_CALL_STATE_END,					//呼叫结束态
    TE_E_CALL_STATE_BUTT					//呼叫无效态
} TE_E_CALL_STATE;

typedef enum tagTE_E_LOGIN_STATE
{
	TE_E_LOGIN_SUCCESS						=	0,//登陆成功
	TE_E_LOGIN_FAIL_AUTH					=	1,//认证失败
	TE_E_LOGIN_SIGNING						=	2,//登录
	TE_E_LOGIN_FAIL_CER_INVALID				=	3,//非法凭证
	TE_E_LGOIN_FAIL_UNREGISTER				=	4,//未注册
	TE_E_LOGIN_FAIL_CONTACT					=	5,//CONTACT 失败
	TE_E_LOGIN_FAIL_SIP						=	6,//SIP失败
	TE_E_LOGIN_FAIL_TIMEOUT					=	7,//超时
	TE_E_LOGIN_SIGNOUT						=	8,//注销
	TE_E_LOGIN_FAIL_NOIP					=	9,//无IP可用
	TE_E_LOGIN_FAIL_HASIP					=	10,//有其他IP可用
	TE_E_LOGIN_KICKOUT						=	11,//被踢
	TE_E_LOGIN_FAIL_LICENSE_TYPE_FAILED		=	12,//获取License类型失败
	TE_E_LOGIN_FAIL_LICENSE_TYPE_INVALID	=	13,//License类型无效
	TE_E_LOGIN_FAIL_LICENSE_APPLY_FAILED	=	14,//申请License失败
	TE_E_LOGIN_FAIL_LICENSE_REFRESH_FAILED	=	15,//保活License失败
	TE_E_LOGIN_FAIL_OTHERS					=	16//其他
}TE_E_LOGIN_STATE;

//SRTP encrytion setting
typedef enum tagTE_E_SETTING_SRTP_MODE
{
	TE_E_SETTING_SRTP_MODE_DISABLE			=	1,
	TE_E_SETTING_SRTP_MODE_FORCE			=	2,
	TE_E_SETTING_SRTP_MODE_OPTION			=	3,
	TE_E_SETTING_SRTP_MODE_BUTT
}TE_E_SETTING_SRTP_MODE;

//media bandwidth setting
typedef enum tagTE_E_SETTING_MEDIA_BANDWIDTH
{
	TE_E_SETTING_MEDIA_BANDWIDTH_64			=	0,
	TE_E_SETTING_MEDIA_BANDWIDTH_128		=	1,
	TE_E_SETTING_MEDIA_BANDWIDTH_256		=	2,
	TE_E_SETTING_MEDIA_BANDWIDTH_384		=	3,
	TE_E_SETTING_MEDIA_BANDWIDTH_512		=	4,
	TE_E_SETTING_MEDIA_BANDWIDTH_768		=	5,
	TE_E_SETTING_MEDIA_BANDWIDTH_1024		=	6,
	TE_E_SETTING_MEDIA_BANDWIDTH_1472		=	7,
	TE_E_SETTING_MEDIA_BANDWIDTH_1536		=	8,
	TE_E_SETTING_MEDIA_BANDWIDTH_1920		=	9,
	TE_E_SETTING_MEDIA_BANDWIDTH_2048		=	10,
	TE_E_SETTING_MEDIA_BANDWIDTH_BUTT		

}TE_E_SETTING_MEDIA_BANDWIDTH;

typedef enum tagENUM_CALL_TYPE
{
	CALL_TYPE_DIAL,     //已拨
	CALL_TYPE_NOANSWER, //未接
	CALL_TYPE_ANSWER,   //已接
	CALL_TYPE_ACB       //回呼
}ENUM_CALL_TYPE;  

//data share cache setting
typedef enum tagTE_E_SETTING_MEDIA_SLIDE_ABILITY_CACHE
{
	TE_E_SETTING_MEDIA_SLIDE_ABILITY_CACHE_DISABLE	=	0,
	TE_E_SETTING_MEDIA_SLIDE_ABILITY_CACHE_ENABLE	=	1,
	TE_E_SETTING_MEDIA_SLIDE_ABILITY_CACHE_BUTT
}TE_E_SETTING_MEDIA_SLIDE_ABILITY_CACHE;

//date share setting
typedef enum tagTE_E_SETTING_MEDIA_OPEN_SLIDE
{
	TE_E_SETTING_MEDIA_OPEN_SLIDE_DISABLE			=	0,
	TE_E_SETTING_MEDIA_OPEN_SLIDE_ENABLE			=	1,
	TE_E_SETTING_MEDIA_OPEN_SLIDE_BUTT
}TE_E_SETTING_MEDIA_OPEN_SLIDE;

typedef enum tagTE_E_SETTING_MEDIA_AUTO_REPLY
{
	TE_E_SETTING_MEDIA_AUTO_REPLY_DISABLE			=	0,
	TE_E_SETTING_MEDIA_AUTO_REPLY_ENABLE			=	1,
	TE_E_SETTING_MEDIA_AUTO_REPLY_BUTT
}TE_E_SETTING_MEDIA_AUTO_REPLY;



typedef enum tagTE_E_CALL_EVENT
{
// call related notification
	TE_E_CALL_EVENT_CALLOUT				=0,   //呼出时间
	TE_E_CALL_EVENT_AUDIOVIDEOINCOMING	=1,   //呼入事件
	TE_E_CALL_EVENT_CALLRING				=2,   //正在呼叫
	TE_E_CALL_EVENT_ANSWERRSP				=3,   //响应呼叫
	TE_E_CALL_EVENT_CLOSE					=4,   //通话结束
	TE_E_CALL_EVENT_OPEN_VEDIO			=5,	   //开启视频
	TE_E_CALL_EVENT_CLOSE_VEDIO			=6,   //关闭视频
	TE_E_CALL_EVENT_ANSWER_VEDIO		=7,   //响应视频请求
}TE_E_CALL_EVENT;

typedef enum tagTE_E_DATA_EVENT
{
	TE_E_DATA_EVENT_DATASEND				=0,   //发送辅流事件
	TE_E_DATA_EVENT_DATARECIEVE				=1,   //接收辅流事件
	TE_E_DATA_EVENT_DATASTOPED				=2,   //停发辅流事件
	TE_E_DATA_EVENT_DATASENDFAILURE			=3,   //辅流发送失败事件
	TE_E_DATA_BFCPMODIFIED_RESULT			=4,   //辅流变化结果事件
}TE_E_DATA_EVENT;

typedef enum tagTE_E_CALL_END_REASON
{
	TE_E_CALL_END_REASON_NORMAL							=	0,	// normal call end
	TE_E_CALL_END_REASON_CANNOT_CONNECT					=	1,	// can not connect with other;
	TE_E_CALL_END_REASON_BUSYING						=	2,	// other is busying now;
	TE_E_CALL_END_REASON_CANNOT_CONNECT_OFFLINE			=	3,	// other is offline now;
	TE_E_CALL_END_REASON_BUTT							=	4	// call end reason number;
}TE_CALL_END_REASON;

/*音量类型*/
typedef enum tagTE_E_VOLUME_TYPE
{
	TE_E_VOLUME_TYPE_MIC,					//麦克风音量
	TE_E_VOLUME_TYPE_SPEAK,					//扬声器音量
	TE_E_VOLUME_TYPE_BUTT						//无效类型
} TE_E_VOLUME_TYPE;

typedef struct tagTE_S_NETWORK_CONIFG
{
	TE_E_SETTING_SRTP_MODE srtp_mode;
	TE_E_SETTING_MEDIA_BANDWIDTH media_bandwidth;
	TE_E_SETTING_MEDIA_OPEN_SLIDE media_open_slide;
	TE_E_SETTING_MEDIA_AUTO_REPLY media_auto_reply;
	TE_S_VIDEO_FRAMESIZE dataFrameSize;// 设置分辨率
	TE_S_VIDEO_DATARATE stDataRate;// 设置辅流码率
	TE_S_VIDEO_DATARATE sVideoDataRate;// 设置主流码率
	TE_S_VIDEO_FRAMERATE stDataFrameRate;//设置帧率

	TE_BOOL setFrameSize;//是否要设置分辨率
	TE_BOOL setDataRate;//是否要设置码率
	TE_BOOL setFrameRate;//是否要设置帧率

}TE_S_NETWORK_CONFIG;

//登录用户信息
typedef struct tagTE_S_LOGIN_INFO
{
   TE_CHAR		cUserName[TE_D_NAME_LEN+1];			// 用户名
   TE_CHAR		cPWD[TE_D_PWD_LEN+1];				// 密码明文（不能为空）
   TE_CHAR		cSipUri[TE_D_URI_LEN+1];
   TE_CHAR		stIP[TE_D_IP_LEN+1];				// 登录服务器IP
   TE_UINT32	uiPort;								// 登录服务器端口，TLS默认端口为5061,UDP默认端口5060
   TE_CHAR		cTransMode[4];						// 客户端与SIP服务器间传输模式 TLS/UDP
   TE_CHAR		licenseServer[TE_D_IP_LEN];			// 证书服务器
   TE_CHAR		cReserve[32];						//保留字段
}TE_S_LOGIN_INFO;


/*登录结果*/
typedef struct tagTE_S_LOGIN_RESULT
{
    TE_UINT32 ulSipAccountID;					//SIP账户ID
    TE_E_REG_STATE enRegState;					//SIP账户注册状态
    TE_UINT32 ulReasonCode;						//注册失败的原因码
    TE_INT8 acTelNum[TE_D_URI_LEN+1];				//SIP会场号码
    TE_INT8 acDisplayName[TE_D_NAME_LEN+1];		//SIP会场名称
	TE_E_LOGIN_STATE loginState;
	TE_CHAR     cReserve[32];					//保留字段
} TE_S_LOGIN_RESULT;

/*呼叫信息*/
typedef struct tagTE_S_CALL_STATE_INFO
{
    TE_UINT32 ulSipAccountID;					//SIP账户ID
    TE_UINT32 ulCallID;							//通话ID
    TE_E_CALL_TYPE enCallType;					//呼叫类型
    TE_E_CALL_STATE enCallState;				//通话状态
    TE_INT8 acTelNum[TE_D_URI_LEN+1];				//SIP会场号码
    TE_INT8 acDisplayName[TE_D_NAME_LEN+1];		//SIP会场名称
    TE_UINT32 ulReasonCode;						//失败原因码endcall
    TE_BOOL bIsIn;								//标识该路通话是否为呼入
    TE_BOOL bIsPassiveEnd;						//标识该路呼叫是否远端挂断
	TE_E_CALL_EVENT	enCallEvent;				//上报电话事件
	TE_E_DATA_EVENT	enDataEvent;				//上报辅流事件
	TE_UINT32 sessionType;
	TE_INT8 acEncodeProtocol[TE_D_PROTOCOL_LENGTH];               /**< 音频编码协议*/
} TE_S_CALL_STATE_INFO;

//音频流信息
typedef struct tagTE_S_AUDIO_STREAM_INFO
{
	TE_UINT32 bIsCalling;                        /**< 是否在通话中*/
	TE_INT8 bIsSRTP;                           /**< 是否启用SRTP MEDIASERVICE_TRANS_SRTP*/
	TE_INT8 acEncodeProtocol[TE_D_PROTOCOL_LENGTH];               /**< 编码协议*/
	TE_INT8 acDecodeProtocol[TE_D_PROTOCOL_LENGTH];               /**< 解码协议*/
	TE_UINT32 ulChannelID;                     /**< 通道ID */
	TE_UINT32 ulSendBitRate;                   /**< 发送比特率 */
	TE_UINT32 ulRecvBitRate;                   /**< 接收比特率 */
	TE_UINT32 ulSendTotalLostPacket;           /**< 发送方累计包损 */
	TE_FLOAT fSendLossFraction;                /**< 发送方丢包率(%) */
	TE_FLOAT fSendJitter;                      /**< 发送方平均抖动(ms) */
	TE_FLOAT fSendDelay;                       /**< 发送方平均时延(ms) */
	TE_UINT32 ulRecvTotalLostPacket;           /**< 接收方累计包损 */
	TE_FLOAT fRecvLossFraction;                /**< 接收方丢包率(%) */
	TE_FLOAT fRecvJitter;                      /**< 接收方平均抖动(ms) */
	TE_FLOAT fRecvDelay;                       /**< 接收方平均时延(ms) */
} TE_S_AUDIO_STREAM_INFO, *TE_S_AUDIO_STREAM_INFO_PTR;

//视频流信息
typedef struct tagTE_S_VIDEO_STREAM_INFO
{
	TE_INT8 acEncodeName[TE_MAX_CODEC_NAME_LEN];        /**< 编码名称*/
	TE_INT8 acDecodeName[TE_MAX_CODEC_NAME_LEN];        /**< 解码名称*/
	TE_INT8 acEncoderSize[TE_MAX_FRAMESIZE_LEN];        /**< 图像分辨率(编码)*/
	TE_INT8 acDecoderSize[TE_MAX_FRAMESIZE_LEN];        /**< 图像分辨率(解码)*/
	TE_INT8 bIsSRTP;                           /**< 是否启用SRTP,对应MEDIASERVICE_TRANS_SRTP*/
	TE_UINT32  ulSendFrameRate;                            /**< 视频帧率(编码)*/
	TE_UINT32  ulRecvFrameRate;                            /**< 视频帧率(解码)*/
	TE_UINT32  ulVideoSendBitRate;                        /**< 编码码率*/
	TE_UINT32  ulVideoRecvBitRate;                        /**< 解码码率*/
	TE_INT8 acEncoderProfile[TE_MAX_PROFILE_LEN];        /**< 视频编码格式*/
	TE_INT8 acDecoderProfile[TE_MAX_PROFILE_LEN];        /**< 视频解码格式*/
	TE_FLOAT fVideoSendLossFraction;                    /**< 发送方丢包率(%) */
	TE_FLOAT fVideoSendJitter;                          /**< 发送方平均抖动(ms) */
	TE_FLOAT fVideoSendDelay;                           /**< 发送方平均时延(ms) */
	TE_FLOAT fVideoRecvLossFraction;                    /**< 接收方丢包率(%) */
	TE_FLOAT fVideoRecvJitter;                          /**< 接收方平均抖动(ms) */
	TE_FLOAT fVideoRecvDelay;                           /**< 接收方平均时延(ms) */
	TE_UINT32 ulWidth;                                    /**< 视频分辨率-宽*/
	TE_UINT32 ulHeight;                                   /**< 视频分辨率-高*/
} TE_S_VIDEO_STREAM_INFO, *TE_S_VIDEO_STREAM_INFO_PTR;


typedef struct tagTE_S_STREAM_INFO
{
	TE_S_AUDIO_STREAM_INFO stAudioStreamInfo;         /*音频流信息*/
	TE_S_VIDEO_STREAM_INFO stVideoStreamInfo;         /*视频流信息*/
	TE_S_VIDEO_STREAM_INFO stDataStreamInfo;          /*辅流信息*/
} TE_S_STREAM_INFO, *TE_S_STREAM_INFO_PTR;


/*创建会议状态*/
typedef struct tagTE_S_CREATECONF_STATE_INFO
{
	TE_CHAR _reason[TE_D_DESC_MAX_NUM+1];       //状态结果描述
	TE_INT32 _result;               //状态结果值
} TE_S_CREATECONF_STATE_INFO;


/*邀人入会结果*/
typedef struct tagTE_S_ADDSITETOCONF_RESULT
{
	TE_SHORT failedCount;     //会议加人事件回调结果，表示有几个人添加失败
	TE_BOOL  result;           //会议加人事件回调结果，成功或失败 
} TE_S_ADDSITETOCONF_RESULT;


typedef enum tagTE_E_CONF_RESULT
{
	TE_E_EVT_CREATE_CONF_STATE_CHANGE  =	0,  //创建会议事件
	TE_E_EVT_APPLY_CONF_CHAIRMAN  =1,   //申请主席事件
	TE_E_EVT_RELEASE_CONF_CHAIRMAN  =	2,  //释放主席事件
	TE_E_EVT_ADDSITETOCONF_RESULT		=  3,  //会议加人事件
	TE_E_EVT_CONF_BROADCAST_RESULT  =  4,   //会议广播事件
	TE_E_EVT_SITE_WATCH_RESULT    =    5,   //观看会议事件
	TE_E_EVT_CONF_EXTENDTIME_NOTE =   6,   //提示延长会议时间事件
	TE_E_EVT_CONF_EXTEND_RESULT   =   7,   //延长会议事件
	TE_E_EVT_CONF_MEMLISTREFRESH	=  8,  //刷新会议人员列表事件
	TE_E_EVT_CONF_BROADCAST_MEMLISTREFRESH	= 9,  //广播后刷新会议人员列表事件
	TE_E_EVT_CONF_CHAIRMAN_THENDO	=  10,	  //会议主席指示
}TE_E_CONF_RESULT;

typedef enum tagTE_E_ENTERPRISE_RESULT
{
	TE_E_EVT_LDAP_CONTACTS_ADDRESS = 0 // ldap 企业通讯录
}TE_E_ENTERPRISE_RESULT;

typedef struct tagTE_S_LDAP_D_Search_Result
{
	bool bSucess; // 是否成功
	unsigned int	ulCode; // 返回码
	unsigned int ulSeqNo; // 搜索序号的返回
	unsigned int ulCookieLen; // 本次搜索的cookie长度
	char *pcPageCookie; // cookie内容
}TE_S_LDAP_D_Search_Result;

typedef struct tagTE_S_CONF_RESULT
{
	TE_E_CONF_RESULT	eventType;	//会议上报的事件类型
	union
	{
		TE_BOOL	isChairman;          
		TE_INT32 result;            //其他会议相关事件的返回结果
		TE_S_CREATECONF_STATE_INFO createConfInfo;  //创建会议事件的返回结果
		TE_S_ADDSITETOCONF_RESULT addHallRest;   //会议加人事件的返回结果
	}uResult;  //不同事件类型对应不同结果
}TE_S_CONF_RESULT;

// ! An enum
		/** \brief  online status definition
		*/
typedef enum tagTE_E_CONTACT_AVAIL_ABILITY
{
	TE_E_CONTACT_Offline = 0,  //离线
	TE_E_CONTACT_Online,       //在线
	TE_E_CONTACT_Busy,         //忙碌
	TE_E_CONTACT_Hide,         //隐身
	TE_E_CONTACT_Leave,        //离开
	TE_E_CONTACT_NoDisturb,    //勿扰
	TE_E_CONTACT_InvalidStatus, //非法状态
}TE_E_CONTACT_AVAIL_ABILITY;


//联系人信息 
typedef struct tagTE_S_CONTACT_INFO
{
	TE_CHAR id[TE_D_ID_LEN+1];							// ID
	TE_CHAR name[TE_D_NAME_LEN+1];				//	名字
	TE_CHAR ucAcc[TE_D_NUMBER_LEN+1];			// 账号
	TE_CHAR nickname[TE_D_NAME_LEN+1];			// 昵称
	TE_CHAR mobile[TE_D_PHONE_LEN+1];			// 手机号
	TE_CHAR officePhone[TE_D_PHONE_LEN+1];	//	办公电话	
	TE_CHAR addresssite[TE_D_ADDRESS_LEN+1];	// 地址
	TE_CHAR email[TE_D_EMAIL_LEN+1];				// 邮箱
	TE_CHAR deptname[TE_D_DEPARTNAME_LEN+1];	//	部门
	TE_CHAR description[TE_D_DESCRIPTION_LEN+1];	//	描述
	TE_E_CONTACT_AVAIL_ABILITY status;          // 联系人状态
}TE_S_CONTACT_INFO;

typedef struct tagTE_S_CONTACTS_CHAIN
{
	TE_S_CONTACT_INFO  contactInfo;
	struct tagTE_S_CONTACTS_CHAIN*  next;
}TE_S_CONTACTS_CHAIN;

typedef struct tagTE_S_CONTACTS_INFO
{
	TE_S_CONTACT_INFO*   contact;
	TE_UINT32 num;
}TE_S_CONTACTS_INFO;



typedef struct tagTE_S_ENTERPRISE_RESULT
{
	TE_E_ENTERPRISE_RESULT  eventType;   //企业通讯录上报事件类型
	TE_S_LDAP_D_Search_Result* pResult;
	TE_S_CONTACTS_INFO enterpriseContacts;
}TE_S_ENTERPRISE_RESULT;

/// 会控操作结果值, copy自TUP头文件
typedef enum tagTE_E_OPERATION_RSP_REASON_CONF
{
	TE_E_OPERATION_SUCCESS = 0,           //!< 会控操作成功

	TE_E_OPERATION_NO_EXIST_USER,         //!< 操作的终端不存在（remove、broadcast）
	TE_E_OPERATION_NO_PRIVILEGE,          //!< 没有操作权限（不是主席）

	TE_E_OPERATION_NO_CHAIR_FUNC,         //!< 会议没有主席功能
	TE_E_OPERATION_NO_CAP_TO_BE_CHAIR,    //!< 所操纵的终端没有主席功能
	TE_E_OPERATION_CHAIR_EXIST,           //!< 会议中已有主席
	TE_E_OPERATION_CHAIR_PWD_ERR,         //!< 主席密码错误

	TE_E_OPERATION_FAIL_UNKNOW = 0xFF     //!< 其他失败原因
}TE_E_OPERATION_RSP_REASON_CONF;


typedef struct tagTE_S_CAMERA_INFO
{
	TE_CHAR cName[TE_D_NAME_LEN+1];				//device name
	TE_UINT32 ulIndex;							//device no
	TE_BOOL bIsCertified;						//if device is verified by Huawei Corp.
	TE_BOOL bIsActive;							//if device is active
	TE_BOOL bType;								//device type

}TE_S_CAMERA_INFO;


typedef struct tagTE_S_AUDIOIN_INFO
{
	TE_CHAR cName[TE_D_NAME_LEN+1];				//device name
	TE_UINT32 ulIndex;							//device no
	TE_BOOL bIsCertified;						//if device is verified by Huawei Corp.
	TE_BOOL bIsActive;							//if device is active
	TE_BOOL bType;								//device type

}TE_S_AUDIOIN_INFO;


typedef struct tagTE_S_AUDIOOUT_INFO
{
	TE_CHAR cName[TE_D_NAME_LEN+1];				//device name
	TE_UINT32 ulIndex;							//device no
	TE_BOOL bIsCertified;						//if device is verified by Huawei Corp.
	TE_BOOL bIsActive;							//if device is active
	TE_BOOL bType;								//device type

}TE_S_AUDIOOUT_INFO;


/*预览窗口信息*/
typedef struct tagTE_S_PREVIEWWND_INFO
{
    TE_ULONG ulWndHandle;						//窗口句柄
	TE_ULONG ulWndLeft;							//X坐标
    TE_ULONG ulWndwidth;						//窗口宽度
	TE_ULONG ulWndTop;							//Y坐标
	TE_ULONG ulWndHeight;						//窗口高度
} TE_S_PREVIEWWND_INFO;



//群组信息
typedef struct tagTE_S_GROUP_INFO
{
	TE_CHAR groupName[TE_D_NAME_LEN+1];			//分组名
	TE_S_CONTACTS_CHAIN *contactsChain;

}TE_S_GROUP_INFO;

typedef  struct tagTE_S_GROUPS_CHAIN
{
	TE_S_GROUP_INFO* group;
	struct tagTE_S_GROUPS_CHAIN *next;
}TE_S_GROUPS_CHAIN;

typedef struct tagTE_S_GROUPS_INFO
{	
	TE_S_GROUP_INFO* groupInfo;					
	TE_UINT32 num;
}TE_S_GROUPS_INFO;

// 对外接口返回码
enum EM_TEServiceRetvCode
{
	TE_SDK_Success				=	0,			//成功
	TE_SDK_InvalidPara			=	1,			//不合法的参数
	TE_SDK_Failed				=	2,			//失败
	TE_SDK_NotInit				=	3,			//未初始化
	TE_SDK_NullPtr				=	4,			//空指针
	TE_SDK_FindUriErr			=	5,			//查找用户uri错误
	TE_SDK_NotHaveCallTarget	=	6,			//没有呼叫对象
	TE_SDK_InTempGroupNow		=	7,			//已经在TempGroup内
	TE_SDK_NotFoundCallID				=	8,			//没有找到Call ID
	TE_SDK_NoRight				=	9,			//没有权限
	TE_SDK_NotLogin				=	10,			//未成功登录
	TE_SDK_SetParamFailed	= 11 ,          //设置界面配置 srtp、辅流、带宽、清晰流畅策略失败
	TE_SDK_OpenPreviewFailed =12,			//打开视频预览失败
	 TE_SDK_NotFoundcamera  = 13,       // 没有找到摄像机
	 TE_SDK_SenddataFailed    = 14,			//发送共享桌面数据失败
	 TE_SDK_RecvdataFailed    = 15,			//接收共享桌面数据失败
	 TE_SDK_AddContactFailed =16,			//添加本地联系人失败
	 TE_SDK_RemoveContactFailed = 17,  //移除本地联系人失败
	 TE_SDK_EditContactFailed  =18,		//编辑本地联系人失败
	 TE_SDK_GetContactListFailed =19,	//获取联系人列表失败
	 TE_SDK_SearchContactFailed = 20,	//搜索联系人失败
	 TE_SDK_OverMax				=	21,			//超过最大限制
	 TE_SDK_NotFound                   =22,
	 TE_SDK_GetMediaInfoFailed  =23, //获取媒体信息失败
	 TE_SDK_ConfCreateFailed =24,   //会议创建失败
	 TE_SDK_GetConfMemberFailed =25, //获取会议成员列表失败
	 TE_SDK_NotConfChairMan  =26,  //不是会议主席
	 TE_SDK_SendDTMFFailed =27,  //发送DTMF失败
	 TE_SDK_GetAVsessByConvIdFailed =28,  //通过ID获取AVsession失败
	 TE_SDK_AudioToVideoFailed  =29,  // 音频转视频失败
	 TE_SDK_VideoChannelStopFailed =30,//视频流信道停止失败
	 TE_SDK_SetVideoCaptureDevFailed =31,//视频抓取设备失败
	 TE_SDK_ConfApplyChairManFailed =32,//申请会议主席失败
	 TE_SDK_ConfReleaseChairManFailed =33,//主席释放失败
	 TE_SDK_jionConfFailed   =34,              //加入会议失败
	 TE_SDK_ExtandConfFailed =35,          //扩大会议时间失败
	 TE_SDK_ConfCallOutHallFailed =36, //会议呼叫会场失败
	 TE_SDK_ConfHangUpHallFailed =37, //会议挂断会场失败
	 TE_SDK_DeleteHallFailed =38,  //会议删除会场失败
	 TE_SDK_ConfMuteHallFailed =39, //会议静音会场失败
	 TE_SDK_ConfUnMuteHallFailed =40, //会议停止静音失败
	 TE_SDK_ConfBroadCastHallFailed =41,//会议广播会场失败
	 TE_SDK_ConfStopBroadFailed =42, //会议停止广播失败
	 TE_SDK_ConfWatchHallFailed =43, //会议观看会场失败
	 TE_SDK_ConfEndFailed =44, //结束会场失败
	 TE_SDK_GetContactByIdFailed =45 ,// 通过ID获取联系人失败
	 TE_SDK_CreateCustomGroupFailed =46 ,// 新建群组失败
	 TE_SDK_RenameCustomGroupFailed =47, //重命名群组失败
	 TE_SDK_RemoveCustomGroupFailed =48, //移除群组失败
	 TE_SDK_GetCustomGroupListFailed =49, //获取联系人分组失败
	 TE_SDK_AudioVideoInUsedFailed=50,   //正在通话中，不能进行媒体设备信息设置
     TE_SDK_VOLUME_TO_SET_LESS_THAN_ZERO=51,//要设置的音量小于0
     TE_SDK_SET_MIC_VOLUME_FAILED=52,//设置麦克音量失败
     TE_SDK_SET_SPEAK_VOLUME_FAILED=53,//设置扬声器音量失败
	 TE_SDK_INVALID_VOLUME_TYPE=54,//非法的音量类型
	 TE_SDK_NotFoundAudioIn=55,//未找到音频输入设备
	 TE_SDK_NotFoundAudioOut=56,//未找到音频输出设备
	 TE_SDK_SetAudioCaptureDevFailed =57,//音频输入设备设置失败
	 TE_SDK_SetAudioPlayDevFailed =58,//音频输出设备设置失败
	 TE_SDK_GetContactFailed =59,	//获取联系人失败
	 TE_SDK_INIT_FAILED=60,			//初始化失败
	 TE_SDK_ContactEmpty = 61,     //联系人为空
	 TE_SDK_GetEnterpriseContactsFailed = 62,//获取企业联系人失败
	 TE_SDK_SearchFtpFailed = 63, //ftp搜索失败
	 TE_SDK_NOGetAllNetContactsList = 64,//没有获得企业通讯录联系人
	 TE_SDK_ExceedNameLength = 65, //超过名字最大长度
	 TE_SDK_ExceedAccountLength = 66,//超过账号最大长度
	 TE_SDK_ExceedAddressLength = 67,//超过地址最大长度
	
	 TE_SDK_illegalEmailFormat = 69,//邮箱格式非法
	 TE_SDK_ExceedDeptnameLength = 70,//超过部门最大长度
	 TE_SDK_ExceedMobileLength = 71,//超过手机电话最大长度
	 TE_SDK_ExceedOfficePhoneLength = 72,//超过办公电话最大长度
	 TE_SDK_ExceedNickNameLength = 73,//超过昵称最大长度
	 TE_SDK_ExceedMaximumContacts = 74,//超过最大联系人个数
	 TE_SDK_GetCustomGroupFailed = 75,//获取分组失败
	 TE_SDK_ContactAlreadyExist = 76,//联系人已经存在
	 TE_SDK_ContactWhetherReplace = 77,//联系人是否替换
	 TE_SDK_NoFindContact = 78,//没有找到联系人
	 TE_SDK_ModifyFailed =79,//修改失败
	 TE_SDK_GroupNameEmpty = 80,//分组名字为空
	 TE_SDK_ExceedGroupSum = 81,//超过分组最大数目
	 TE_SDK_GroupAlreadyExist = 82,//分组已经存在
	 TE_SDK_ExceedGroupNameLength = 83,//超过分组最大长度
	 TE_SDK_AddGroupFailed = 84,//添加分组失败
	 TE_SDK_SameWithDefaultName = 85,//和默认分组重名
	 TE_SDK_illegalFileFormat = 86, //非法的文件格式
	 TE_SDK_CreatExcelApplicationFailed = 87,//创建excel失败
	 TE_SDK_ExcelWorkbookEmpty = 88,//excel book为空
	 TE_SDK_ExcelWorksheetEmpty = 89, //excel 表为空
	 TE_SDK_InsertExcelContactFailed = 90,//向excel插入联系人失败
	 TE_SDK_ComError = 91, //异常错误
	 TE_SDK_OpenCSVFailed = 92,//打开csv文件失败
	 TE_SDK_InsertCSVContactFailed = 93,//向csv插入联系人失败
	 TE_SDK_ErrorFileType = 94,//错误的文件类型
	 TE_SDK_ContactOrGroupSumBeyondLimit = 95,//超出联系人或者分组最大数目
	 TE_SDK_ErrorHeadLineFormat =96,//错误的头文件行格式
	 TE_SDK_AssemblyContactFailed = 97,//组装联系人失败
	 TE_SDK_FileNoContact = 98,//文件中没有联系人
	 TE_SDK_UnRegonizeFile = 99,//无法识别文件
	 TE_SDK_NoLdapSearchFailed = 100,//没有搜索到ldap类型
	 TE_SDK_RemoveRecordsByRecordIdFailed = 101,//通过记录id移除记录失败
	 TE_SDK_GetCallRecordsFailed = 102,//获取通话记录失败
	 TE_SDK_ExceedDescriptionLength = 103,//超出了描述的长度
	 TE_SDK_NoFindFile = 104, // 没有找到文件
	 TE_SDK_IDAlreadyExist = 105, //id 已经存在
	 TE_SDK_AddToGroupFailed = 106,//复制到分组失败
	 TE_SDK_NotInConference = 107,  //不在会议中
	 TE_SDK_PathFormatFailed = 108, //路径格式错误

	 TE_SDK_MAX_COUNT_FAILED


};


typedef enum tagTE_E_EVENT_CODE
{
	TE_E_EVT_LOGIN_RESULT			=	0,	/**< 登录事件*/
	TE_E_EVT_CALL_RESULT			=	1,	/**< 通话事件*/
	TE_E_EVT_DATA_RESULT			=	2,	/**< 辅流事件*/
	TE_E_EVT_CONF_RESULT			=3,		/**< 会议事件*/
	TE_E_EVT_ENTERPRISE_RESULT  =4,  /*企业通讯录事件*/
	TE_E_EVT_USER_STATUS            =5    /*用户状态改变事件*/
}TE_E_EVENT_CODE;


typedef  TE_VOID (CALLBACK* EventCallBack)(
    TE_INT32   iEventType,    //事件类型
    TE_VOID*   pEventBuf,     //事件数据
    TE_UINT32  uiBufSize,      //buf长度
    TE_VOID*   pUserData     //用户数据，自定义，相应回调函数被调用时返回该参数
);

#define TE_DESKTOP_VERSION						"V3.2.0.013"



enum msgtype
{
	DataScreenSizeNotifyMsg,
	DataScreenSizeNotifyAckMsg,

	//login,logout related operations
	SignInMsg,
	SignInNotifyMsg,
	SignOutMsg,
	SignOutNotifyMsg,
	SipRegNotifyMsg,

};


// 日志类型
enum LOGTYPE
{
	DEBUG_TYPE				=	0, //调试信息
	INFO_TYPE				=	1, //一般信息
	WARN_TYPE				=	2, //警告
	ERROR_TYPE				=	3  //错误
};


#endif