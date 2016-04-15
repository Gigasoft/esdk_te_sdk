
/** 
* @file call_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP 呼叫子系统基础业务定义头文件。 \n
*/


/**
*
*  @{
*/


#ifndef __CALL_DEF_H__
#define __CALL_DEF_H__


#include "tup_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

#define TUP_CALL_VERSION   "TUP V100R001C50B01b"


#define CALL_D_ACCESSCODE_MAX_LENGTH    (32)   /**< 接入码字符串最大长度*/
#define CALL_D_IP_LENGTH                (16)   /**< IP地址字符串最大长度 */
#define CALL_D_PROTOCOL_LENGTH          (30)   /**< 协议名字字符串最大长度 */
#define MPROC_D_AAC_CONFIG_LEN          (16)   /**< TODO AAC的config码流*/
#define MPROC_D_AUD_RATE_NUM            (16)   /**< 格式音频支持多个码率的个数*/
#define MPROC_D_MAX_AUDIO_OUT_VOLUME    (100)  /**< 音频输出最大音量值*/
#define CALL_D_HMEVERSION_LENGTH        (128)  /**< HME版本字符串最大长度*/ 
#define CALL_D_MAX_AUDIO_CODEC_LEN      (64)   /**< 音频编解码名称最大长度*/
#define CALL_D_MAX_CODEC_LIST_LEN       (127)  /**< 音频编解码名称链最大长度，以逗号分割*/
#define CALL_D_MAX_DEVICE_NUM           (10)   /**< 输入/输出设备最大支持数目*/

#define CALL_MAX_CODEC_NAME_LEN         (31)   /**< 音视频编解码名称长度 */
#define CALL_MAX_FRAMESIZE_LEN          (16)   /**< 视频分辨率长度 */    
#define CALL_MAX_PROFILE_LEN            (8)    /**< 视频编解码格式长度*/

#define CALL_D_MAX_LENGTH_NUM           (256)  /**< 通用字符串最大长度*/
#define CALL_D_MAX_DISPLAY_NAME         (256)  /**< 显示名最大长度*/
#define CALL_D_MAX_USERNAME_LENGTH      (256)  /**< 用户名最大长度*/
#define CALL_D_MAX_PASSWORD_LENGTH      (256)  /**< 密码最大长度*/
#define CALL_D_MAX_URL_LENGTH           (256)  /**< 通用URL最大长度*/
#define CALL_D_MAX_SERVER_LENGTH        (256)  /**< 服务器最大长度*/
#define CALL_D_MAX_TOKEN_LENGTH         (256)  /**< TOKEN最大长度*/
#define CALL_D_MAX_PASSCODE_LENGTH      (256)  /**< 接入码最大长度*/



#define CALL_D_MAX_HTTP_URL_LENGTH      (512)  /**< HTTP URL最大长度*/

#define CALL_D_MAXDEVICENUM             (8)    /**< TODO设备最大数量 */

#define CALL_D_MAX_PRESET_MSG_LENGTH    (100)  /**< 预设消息字符串最大长度 */

#define CALL_D_MAX_MSGSUMMARY_NUM       (10)   /**< UM消息最大个数 */

#define CALL_D_MAX_ACCOUNT_NUM          (24)   /**< 用户账号最大数 */
#define CALL_D_MAX_CALL_NUM             (24)   /**< 并发呼叫最大路数 */
#define CALL_D_MAX_LINE_NUM             (24)   /**< 可用呼叫线路最大路数 */
#define CALL_D_MAX_LINE_KEY_NUM         (24)   /**< 呼叫线路键最大数 */

#define CALL_D_MAX_ACB_NUM              (5)    /**< 回呼最大个数 */

#define CALL_D_MAX_FOWARD_NUM           (24)   /**< 前转控制块处理最大个数*/

#define CALL_D_MAX_INTERCOM_GROUPNUM    (CALL_D_MAX_ACCOUNT_NUM-1)     /**< intercom线路最大数,最多比最大账号数少一路 */

#define CALL_D_PASSCODE_LENGTH          (50)   /**< 会议创建结果中接入码最大长度 */
#define CALL_D_DATACONF_PARAM_LENGTH    (32)   /**< 数据会议参数长度普适值 */
#define CALL_D_DATACONF_CMADDR_LENGTH   (64)   /**< 数据会议参数cm_address长度值 */
#define CALL_D_CONF_CODE_LENGTH         (33)   /**< 会议接入码最大长度 */
#define CALL_D_CONF_LINK_NUM_LENGTH     (32)   /**< 会议列表中成员联动号码最大长度 */
#define CALL_D_CONF_TYPE_MAX_LEN        (21)   /**< 会议类型最大长度 */
#define TUP_CONF_VALID_CONFID_BEG       (1)    /**< TODO */

#define CALL_D_TLSVERSION_V1_0          0x00000001L  /**< TLS v1.0 */
#define CALL_D_TLSVERSION_V1_1          0x00000002L  /**< TLS v1.1 */
#define CALL_D_TLSVERSION_V1_2          0x00000004L  /**< TLS v1.2 */



/** 
 * 呼叫模块ID 
 */
typedef enum tagCALL_E_MOD_ID
{
    CALL_E_MOD_ID_TSP = 0,         /**< 呼叫控制主消息处理模块 */
    CALL_E_MOD_ID_STACK,          /**< SIP协议栈消息处理模块 */

    CALL_E_MOD_ID_SIP = 4096,      /**< SIPC消息处理模块 */
    CALL_E_MOD_ID_HLLM,            /**< HLLM负责DNS查询消息处理模块 */
    CALL_E_MOD_ID_VCOM,            /**< VCOM消息处理模块 */
    CALL_E_MOD_ID_TPTD,            /**< TPTD消息处理模块 */

    CALL_E_MOD_ID_BUTT
} CALL_E_MOD_ID;


/** 
 * ID类型 
 */
typedef enum tagCALL_E_ID_TYPE
{
    CALL_E_IDTYPE_CALL_ID,  /**< 呼叫 */
    CALL_E_IDTYPE_CONF_ID   /**< 会议 */
}CALL_E_ID_TYPE;


/** 
 * 日志级别
 */
enum CALL_E_LOG_LEVEL
{
    CALL_E_LOG_ERROR = 0,    
    CALL_E_LOG_WARNING,     
    CALL_E_LOG_INFO,         
    CALL_E_LOG_DEBUG         
};


/** 
 *系统错误码定义
 */
typedef enum tagCALL_E_ERR_ID
{
    CALL_E_ERR_BEGIN = 0x08002100UL,
    CALL_E_ERR_GENERAL_ERROR,                     /**<1  一般错误 */
    CALL_E_ERR_PARAM_ERROR,                       /**<2  参数错误 */
    CALL_E_ERR_MEM_ERROR,                         /**<3  分配内存错误 */
    CALL_E_ERR_SYSTEM_ERROR,                      /**<4  系统错误 */
    CALL_E_ERR_MSG_ERROR,                         /**<5  发送消息错误 */
    CALL_E_ERR_CFG_ERROR,                         /**<6  获取系统配置错误 */
    CALL_E_ERR_NET_ERROR,                         /**<7  物理网络错误 */
    CALL_E_ERR_ACCESS_ERROR,                      /**<8  网络接入失败错误 */
    CALL_E_ERR_TIMER_ERROR,                       /**<9  创建定时器错误 */
    CALL_E_ERR_STATE_ERROR,                       /**<10 呼叫状态不正确 */
    
    CALL_E_ERR_OPERATE_ERROR,                     /**<11 正在进行其他操作错误 */
    CALL_E_ERR_REQSRV_ERROR,                      /**<12 请求主控进行呼叫开始错误 */
    CALL_E_ERR_REQRES_ERROR,                      /**<13 申请音频资源错误 */
    CALL_E_ERR_SERVICE_DOING,                     /**<14 正在进行其他补充业务 */
    CALL_E_ERR_CALLRECORD_ERROR,                  /**<15 记录通话记录错误 */
    CALL_E_ERR_MPROC_ERROR,                       /**<16 媒体进程返回的错误 */
    CALL_E_ERR_MAX_CALL_ERROR,                    /**<17 超过最大呼叫路数 */
    CALL_E_ERR_SIPID_NOTEXIT_ERROR,               /**<18 SIP账户ID不存在 */
    CALL_E_ERR_CALLID_NOEXIT_ERROR,               /**<19 呼叫ID不存在 */
    CALL_E_ERR_REGISTERING_ERROR,                 /**<20 正在注册中失败*/
    
    CALL_E_ERR_REGIST_FALL_ERROR,                 /**<21 调用sip接口注册失败 */
    CALL_E_ERR_DEREGIST_FALL_ERROR,               /**<22 调用sip接口注销失败 */
    CALL_E_ERR_SET_SIP_INFO_ERROR,                /**<23 设置账户信息错误 */
    CALL_E_ERR_SETACCOUNT_ERROR,                  /**<24 设置SIP模块失败*/
    CALL_E_ERR_NOTIFYSIPACCOUNT_ERROR,            /**<25 上报失败  */
    CALL_E_ERR_SIPSEVER_ERROR,                    /**<26 服务器信息错误*/
    CALL_E_ERR_SIPACCOUNTINFO_ERROR,              /**<27 账户信息错误*/
    CALL_E_ERR_SIPC_ERROR,                        /**<28 SIPC执行错误*/
    CALL_E_ERR_UNREGISTER_ERROR,                  /**<29 未注册错误*/
    CALL_E_ERR_SUB_FALL_ERROR,                    /**<30 调用Sip接口订阅失败 */
    
    CALL_E_ERR_DESUBING_ERROR,                    /**<31 注销订阅中错误 */
    CALL_E_ERR_SUBING_ERROR,                      /**<32 订阅中错误 */
    CALL_E_ERR_LOCAL_MAX_CONFER_ERROR,            /**<33 本地会议已创建，只允许一个会场*/
    CALL_E_ERR_LOCAL_CONFER_NOEXIT_ERROR,         /**<34 本地会议未创建 */
    CALL_E_ERR_LOCAL_CONFER_NOMATCH_ERROR,        /**<35 与会者线路与主席账户不匹配*/
    CALL_E_ERR_CONF_STATE_ERROR,                  /**<36 本地会议状态错误*/
    CALL_E_ERR_JOINTSTATENOTIFY_ERROR,            /**<37 IP Phone端联动状态上报失败*/
    CALL_E_ERR_CONFID_NOTEXIST_ERROR,             /**<38 会议ID不存在 */
    CALL_E_ERR_CONF_VIDEO_HOLD_ERROR,             /**<39 视频保持失败 */
    CALL_E_ERR_CONF_VIDEO_UNHOLD_ERROR,           /**<40 视频恢复失败 */
    
    CALL_E_ERR_MAX_SERVER_CONF_ERROR,             /**<41 服务器会议个数超出 */
    CALL_E_ERR_AA_REQRANDOMNUM_ERROR,             /**<42 AA获取随机数失败 */
    CALL_E_ERR_AA_LOGIN_ERROR,                    /**<43 AA登陆失败 */
    CALL_E_ERR_CONF_VIDEO_TYPE_NO_MATCH,          /**<44 会议类型不匹配*/
    CALL_E_ERR_CONF_VIDEO_START_ERROR,            /**<45 视频会议开启失败*/
    CALL_E_ERR_AA_NOMAINSERVER_ERROR,             /**<46 AA无主服务器 */
    CALL_E_ERR_AA_PASSWORD_ERROR,                 /**<47 密码错误 */
    CALL_E_ERR_AA_USERNAME_ERROR,                 /**<48 用户名错误 */
    CALL_E_ERR_AA_USERLOGINED_ERROR,              /**<49 用户已登录 */
    CALL_E_ERR_AA_ACCOUNTLOCKED_ERROR,            /**<50 账户已锁定 */
    
    CALL_E_ERR_AA_TERMINALTYPE_ERROR,             /**<51 终端类型不匹配 */
    CALL_E_ERR_AA_PARSEXML_ERROR,                 /**<52 解析XML错误 */
    CALL_E_ERR_AA_CONNECT_ERROR,                  /**<53 连接服务器错误 */
    CALL_E_ERR_MEDIA_CFG_ERROR,                   /**<54 获取媒体配置失败 */
    CALL_E_ERR_AA_GETSRINFO_ERROR,                /**<55 获取业务权限失败 */
    CALL_E_ERR_AA_LACKSR_ERROR,                   /**<56 业务权限不足失败 */
    CALL_E_ERR_NETWORKENV_ERROR,                  /**<57 网络环境错误 */
    CALL_E_ERR_SERVICE_CONFLICT_ERROR,            /**<58 业务冲突*/
    CALL_E_ERR_AA_TIMEOUT_ERROR,                  /**<59 连接超时 */
    CALL_E_ERR_AA_UNKOWN_ERROR,                   /**<60 未知错误*/
    
    CALL_E_ERR_PICKUP_ADDTIP_ERROR,               /**<61 添加振铃信息失败 */
    CALL_E_ERR_PICKUP_REMOVETIP_ERROR,            /**<62 删除加振铃信息失败 */
    CALL_E_ERR_PICKUP_CREATERINGNUM_ERROR,        /**<63 创建振铃号码失败 */
    CALL_E_ERR_VVM_PARAM_ERR,                     /**<64 VVM参数错误 */
    CALL_E_ERR_GET_IPT_INFO_ERR,                  /**<65 获取登记业务错误 */
    CALL_E_ERR_VVM_GETVOICEMAIL_ERR,              /**<66 获取语音邮箱 */
    CALL_E_ERR_ATTENDEE_ALREADY_EXIST,            /**<67 与会者已经存在 */
    CALL_E_ERR_ATTENDEE_NOT_EXIST,                /**<68 与会者不存在 */
    CALL_E_ERR_CREATE_CONF_WND_ERROR,             /**<69 创建服务器视频会议窗口失败*/
    CALL_E_ERR_CREATE_CONF_WND_EXIST,             /**<70 视频窗口不存在*/
    
    CALL_E_ERR_GET_CONF_LIST_INFO_ERROR,          /**<71 获取会议列表失败*/
    CALL_E_ERR_NEED_CHAIRMAN_TO_OPERATE,          /**<72 需要主持人权限才能操作*/
    CALL_E_ERR_NO_VIDEO_DEVICE_TO_OPERATE,        /**<73 没有视频设备可以操作*/
	CALL_E_ERR_NOT_STOP_REFRESHREG,               /**<74 没有关闭刷新注册*/
    CALL_E_ERR_NOTIFY_ONLINE_STATE_ERROR,         /**<75 在线状态notify上报失败*/
    CALL_E_ERR_NOTIFY_NETADDR_ERROR,              /**<76 网络地址本订阅notify上报失败*/
    CALL_E_ERR_INFO_FORCEUNREG_ERROR,             /**<77 智真账号被踢info上报失败*/
    CALL_E_ERR_TLSROOTCERT_ERROR,                 /**<78 TLS根证书错误*/
    
    CALL_E_ERR_BUTT,
    CALL_E_ERR_NUM = (CALL_E_ERR_BUTT & 0x00001FFF)
} CALL_E_ERR_ID;

/**
 *信令失败的原因码
 */
typedef enum tagCALL_E_REASON_CODE
{
    CALL_E_REASON_CODE_OK = 0,

    CALL_E_REASON_CODE_BADREQUEST = 400,
    CALL_E_REASON_CODE_PAYMENTREQUIRED = 402,
    CALL_E_REASON_CODE_FORBIDDEN = 403,
    CALL_E_REASON_CODE_NOTFOUND = 404,
    CALL_E_REASON_CODE_METHODNOTALLOWED = 405,
    CALL_E_REASON_CODE_RESNOTACCEPTABLE = 406,
    CALL_E_REASON_CODE_REQUESTTIMEOUT = 408,
    CALL_E_REASON_CODE_GONE = 410,
    CALL_E_REASON_CODE_REQUESTENTITYTOOLARGE = 413,
    CALL_E_REASON_CODE_REQUESTURITOOLONG = 414,
    CALL_E_REASON_CODE_UPSUPPORTEDMEDIATYPE = 415,
    CALL_E_REASON_CODE_UPSUPPORTEDURISCHEME = 416,
    CALL_E_REASON_CODE_BADEXTENSION = 420,
    CALL_E_REASON_CODE_EXTENSIONREQUIRED = 421,
    CALL_E_REASON_CODE_TEMPORARILYUNAVAILABLE = 480,
    CALL_E_REASON_CODE_CALLTRANSACTIONDOESNOTEXIST = 481,
    CALL_E_REASON_CODE_LOOPDETECTED = 482,
    CALL_E_REASON_CODE_TOOMANYHOPS = 483,
    CALL_E_REASON_CODE_ADDRESSINCOMPLETE = 484,
    CALL_E_REASON_CODE_AMBIGUOUS = 485,
    CALL_E_REASON_CODE_BUSYHERE = 486,
    CALL_E_REASON_CODE_REQUESTTEMINATED = 487,
    CALL_E_REASON_CODE_NOTACCEPTABLEHERE = 488,
    CALL_E_REASON_CODE_REQUESTPENDING = 491,
    CALL_E_REASON_CODE_UNDECIPHERABLE = 493,

    CALL_E_REASON_CODE_SERVERINTERNALERROR = 500,
    CALL_E_REASON_CODE_NOTIMPLEMENTED = 501,
    CALL_E_REASON_CODE_BADGATEWAY = 502,
    CALL_E_REASON_CODE_SERVICEUNAVAILABLE = 503,
    CALL_E_REASON_CODE_SERVERTIMEOUT = 504,
    CALL_E_REASON_CODE_VERSIONNOTSUPPORTED = 505,
    CALL_E_REASON_CODE_MESSAGETOOLARGE = 513,

    CALL_E_REASON_CODE_BUSYEVERYWHERE = 600,
    CALL_E_REASON_CODE_DECLINE = 603,
    CALL_E_REASON_CODE_DOESNOTEXISTEVERYWHERE = 604,
    CALL_E_REASON_CODE_NOTACCEPTABLE = 606,

    CALL_E_REASON_CODE_TLS_CERTIFICATE_INVALIDE = 801, //证书错误
    CALL_E_REASON_CODE_TLS_RECV_CERTIFICATE_FAIL = 802,//接收证书失败 
    CALL_E_REASON_CODE_END
} CALL_E_REASON_CODE;



/**
 * 特征码业务类型
 */
typedef enum tagCALL_E_SERVICE_CALL_TYPE
{
    CALL_E_SERVICE_CALL_NORMAL,


    CALL_E_SERVICE_CALL_TYPE_REG_DND,                   /**< 登记DND */
    CALL_E_SERVICE_CALL_TYPE_UNREG_DND,                 /**< 取消登记DND */

    
    CALL_E_SERVICE_CALL_TYPE_CALL_WAIT_ACTIVE,          /**< 呼叫等待开启 */
    CALL_E_SERVICE_CALL_TYPE_CALL_WAIT_DEACTIVE,        /**< 呼叫等待关闭 */

    CALL_E_SERVICE_CALL_TYPE_REG_SCAPRIVATE,            /**< 登记私人呼叫 */
    CALL_E_SERVICE_CALL_TYPE_UNREG_SCAPRIVATE,          /**< 取消登记私人呼叫 */


    CALL_E_SERVICE_CALL_TYPE_REG_ALERT_SILENCE,         /**< 登记共享线来电静音 */
    CALL_E_SERVICE_CALL_TYPE_UNREG_ALERT_SILENCE,       /**< 取消共享线来电静音 */
    CALL_E_SERVICE_CALL_TYPE_REG_PRIVACY,               /**< 登记私人呼叫业务*/
    CALL_E_SERVICE_CALL_TYPE_UNREG_PRIVACY,             /**< 取消私人呼叫业务*/

    CALL_E_SERVICE_CALL_TYPE_SET_CALLPARK,              /**< 设置呼叫驻留 */
    CALL_E_SERVICE_CALL_TYPE_DIRECTCALLPARK,            /**< 直接呼叫驻留 */
    CALL_E_SERVICE_CALL_TYPE_GET_CALLPARK,              /**< 取回呼叫驻留 */

    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION,       /**< 本地无条件前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY,            /**< 本地遇忙前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY,           /**< 本地无应答前转*/

    CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Active,       /**< 无条件转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Deactive,     /**< 无条件转语音邮箱注销*/
    CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Active,       /**< 遇忙 转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Deactive,     /**< 遇忙 转语音邮箱注销*/
    CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Active,       /**< 无应答 转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Deactive,     /**< 无应答 转语音邮箱注销*/
    CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Active,       /**< 离线 转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Deactive,     /**< 离线 转语音邮箱注销*/

    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active,/**< 服务器无条件前转登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive, /**< 服务器无条件前转注销*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active,     /**< 服务器遇忙前转登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive,   /**< 服务器遇忙前转注销*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active,    /**< 服务器无应答前转登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive,  /**< 服务器无应答前转注销*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active,    /**< 服务器离线前转登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive,  /**< 服务器离线前转注销*/

    CALL_E_SERVICE_CALL_TYPE_SCAPRIVATE_ACTIVE,         /**< 共享线路私人呼叫登记*/
    CALL_E_SERVICE_CALL_TYPE_SCAPRIVATE_DEACTIVE,       /**< 共享线路私人呼叫注销*/

    CALL_E_SERVICE_CALL_TYPE_ACBCALL_ACTIVE,            /**< 呼叫回呼登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_ACBCALL_DEACTIVE,          /**< 呼叫回呼注销 */

    CALL_E_SERVICE_CALL_TYPE_GOURPPICKUP,               /**< 群组代答*/
    CALL_E_SERVICE_CALL_TYPE_DESPICKUP,                 /**< 指定代答*/

    CALL_E_SERVICE_CALL_TYPE_DIVERT,                    /**< 偏转*/

    CALL_E_SERVICE_CALL_TYPE_REG_DICF,                  /**< 拒绝前转来电登记 */
    CALL_E_SERVICE_CALL_TYPE_UNREG_DICF,                /**< 拒绝前转来电注销 */

    CALL_E_SERVICE_CALL_TYPE_ABSENT_ON,                 /**< 开启absence */
    CALL_E_SERVICE_CALL_TYPE_ABSENT_OFF,                /**< 关闭absence */

    CALL_E_SERVICE_CALL_TYPE_MCID,                      /**< 恶意呼叫跟踪 */

    CALL_E_SERVICE_CALL_TYPE_CALL_LIMIT_ACTIVE,         /**< 开启密码限呼 */
    CALL_E_SERVICE_CALL_TYPE_CALL_LIMIT_DEACTIVE,       /**< 关闭密码限呼 */

    CALL_E_SERVICE_CALL_TYPE_ATTENDCONF_BY_ONEKEY,      /**< 一键入会**/
    CALL_E_SERVICE_CALL_TYPE_HUNTGROUP_SIGNIN,          /**< huntgroup签入 */
    CALL_E_SERVICE_CALL_TYPE_HUNTGROUP_SIGNOUT,         /**< huntgroup签出 */
    CALL_E_SERVICE_CALL_TYPE_GET_VIRTUALVM,             /**< 获取虚拟语音邮箱 */

    CALL_E_SERVICE_CALL_TYPE_BUIT

} CALL_E_SERVICE_CALL_TYPE;



/**
 * DTMF键值
 */
typedef enum tagCALL_E_DTMF_TONE
{
    CALL_E_DTMF0,       /**< dtmf按键0 */
    CALL_E_DTMF1,       /**< dtmf按键1 */
    CALL_E_DTMF2,       /**< dtmf按键2 */
    CALL_E_DTMF3,       /**< dtmf按键3 */
    CALL_E_DTMF4,       /**< dtmf按键4 */
    CALL_E_DTMF5,       /**< dtmf按键5 */
    CALL_E_DTMF6,       /**< dtmf按键6 */
    CALL_E_DTMF7,       /**< dtmf按键7 */
    CALL_E_DTMF8,       /**< dtmf按键8 */
    CALL_E_DTMF9,       /**< dtmf按键9 */
    CALL_E_DTMFSTAR,    /**< dtmf按键'*' */
    CALL_E_DTMFJIN,     /**< dtmf按键'#' */
    CALL_E_DTMFA,       /**< dtmf按键A */
    CALL_E_DTMFB,       /**< dtmf按键B */
    CALL_E_DTMFC,       /**< dtmf按键C */
    CALL_E_DTMFD,       /**< dtmf按键D */
    CALL_E_DTMFFLASH,   /**< dtmf按键FLASH */
    CALL_E_BUTT
} CALL_E_DTMF_TONE;




/**
 *上报给界面的事件
 */
typedef enum tagCALL_E_CALL_EVENT
{
    CALL_E_EVT_BEGIN = 0,

    CALL_E_EVT_SIPACCOUNT_INFO,             /**< 通知上层应用，SIP账户信息改变
                                                <br>param1：无 
                                                <br>param2：无  
                                                <br>data：  CALL_S_SIP_ACCOUNT_INFO* */    
    CALL_E_EVT_CALL_STARTCALL_RESULT,       /**< 发起呼叫响应，异步
                                                <br>param1：ulCallID 
                                                <br>param2：ulResult  建立呼叫结果
                                                <br>data：无 */
    CALL_E_EVT_CALL_INCOMMING,              /**< 来电事件
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO* */   
    CALL_E_EVT_CALL_OUTGOING,               /**< 呼出事件
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO* */   
    CALL_E_EVT_CALL_RINGBACK,               /**< 回铃音事件 
                                                <br>param1：ulCallID 
                                                <br>param2：无 
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_CONNECTED,              /**< 通话已建立
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_ENDED,                  /**< 呼叫结束
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */  
    CALL_E_EVT_CALL_DESTROY,                /**< 删除呼叫ID
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */  
    CALL_E_EVT_CALL_RTP_CREATED,            /**< RTP通道已建立，可以进行二次拨号
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  无 */   
    CALL_E_EVT_CALL_ADD_VIDEO,              /**< 通话增加视频
                                                <br>param1：ulCallID 
                                                <br>param2：ulOrientType 横竖屏（移动端使用）
                                                <br>data：  无  */  
    CALL_E_EVT_CALL_DEL_VIDEO,              /**< 通话删除视频
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  无 */   
    CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT,    /**< 修改视频结果
                                                <br>param1：ulCallID 
                                                <br>param2：ulResult 0成功 其他失败
                                                <br>data：  CALL_S_MODIFY_VIDEO_RESULT*  */ 
    CALL_E_EVT_REFRESH_VIEW,                /**< 视频view刷新通知
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_REFRESH_VIEW*  */   
    CALL_E_EVT_DECODE_SUCCESS,              /**< 媒体解码成功通知(消息体为CALL_S_DECODE_SUCCESS)
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_DECODE_SUCCESS*  */  
    CALL_E_EVT_MOBILE_ROUTE_CHANGE,         /**< 移动路由变化通知
                                                <br>param1：ulCallID 
                                                <br>param2：ulRoute
                                                <br>data：  无  */   
    CALL_E_EVT_AUDIO_END_FILE,              /**< 音频文件播结束通知
                                                <br>param1：ulHandle 
                                                <br>param2：无
                                                <br>data：  无  */   
    CALL_E_EVT_NET_QUALITY_CHANGE,          /**< 网络质量改变通知
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_NETQUALITY_CHANGE*  */
    CALL_E_EVT_STATISTIC_NETINFO,           /**< 网络质量统计信息
                                                <br>param1：ulCallID 
                                                <br>param2：无
                                                <br>data：  CALL_S_STATISTIC_NETINFO*  */    
    CALL_E_EVT_STATISTIC_MOS,               /**< 话机；视频质量上报ulQualityLevel 0-5 level=0时error值有效网络错误 
                                                <br>0 : 没有错误 1 : 网络发端错误 2 : 网络收端错误 3 : 网络收发均错误     MOS分上报
                                                <br>param1：ulCallID
                                                <br>param2：ulMos
                                                <br>data：  无  */   
    CALL_E_EVT_STATISTIC_QOS,               /**< QOS网络信息上报
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_NOTIFYLOACLQOS_INFO* */   
    CALL_E_EVT_STATISTIC_LOCAL_QOS,         /**< 定时5秒上报QOS网络信息上，用于界面网络状态显示
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_NOTIFYLOACLQOS_INFO* */    
    CALL_E_EVT_SPKDEV_VOLUME_CHANGE,        /**< 扬声器设备音量变化(pc/mac)
                                                <br>param1：uiVolume
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_MICDEV_VOLUME_CHANGE,        /**< 麦克风设备音量变化(pc/mac)
                                                <br>param1：uiVolume
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_AUDIO_UNIT_INIT,             /**< 音频单元初始化完成通知(可用于通知上层设置路由)
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */
    CALL_E_EVT_AUDIO_SET_INDEVICE_ERR,      /**< 音频设置输入设备失败
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */
    CALL_E_EVT_AUDIO_SET_OUTDEVICE_ERR,     /**< 音频设置输出设备失败
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */   
    CALL_E_EVT_VIDEO_OPERATION,             /**< 视频操作
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_VIDEO_OPERATION*  */   
    CALL_E_EVT_VIDEO_STATISTIC_NETINFO,     /**< 视频网络质量统计信息
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_STATISTIC_NETINFO*  */    
    CALL_E_EVT_VIDEO_QUALITY,               /**< 视频质量
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_NETQUALITY_CHANGE*  */
    CALL_E_EVT_VIDEO_FRAMESIZE_CHANGE,      /**< 视频大小变更
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_VIDEO_FRAMESIZE_CHANGE*  */    
    CALL_E_EVT_DATA_FRAMESIZE_CHANGE,       /**< 辅流大小变更
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_VIDEO_FRAMESIZE_CHANGE*  */    
    CALL_E_EVT_DATA_READY,                  /**< 辅流准备好
                                                <br>param1：ulCallID
                                                <br>param2：bIsDataReady
                                                <br>data：  无  */    
    CALL_E_EVT_DATA_SENDING,                /**< 辅流开始发送
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_DATA_RECVING,                /**< 辅流开始接收
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_DATA_START_ERR,              /**< 辅流启动失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_DATA_STOPPED,                /**< 辅流停止
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SESSION_MODIFIED,            /**< 会话修改完成通知
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_SESSION_MODIFIED*  */    
    CALL_E_EVT_SESSION_CODEC,               /**< 会话正在使用的codec通知
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_SESSION_CODEC*  */    
    CALL_E_EVT_CALL_HOLD_SUCCESS,           /**< 保持成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_HOLD_FAILED,            /**< 保持失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_UNHOLD_SUCCESS,         /**< 恢复成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_UNHOLD_FAILED,          /**< 恢复失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_ENDCALL_FAILED,         /**< 结束通话失败
                                                <br>param1：ulCallID
                                                <br>param2：ulResult 错误码
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_DIVERT_FAILED,          /**< 偏转失败
                                                <br>param1：ulCallID
                                                <br>param2：ulResult 错误码
                                                <br>data：  无 */    
	CALL_E_EVT_CALL_BLD_TRANSFER_RECV_SUC_RSP,	/**< 盲转REFER收到成功响应
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */	
    CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS,   /**< 盲转成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_BLD_TRANSFER_FAILED,    /**< 盲转失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS,   /**< 咨询转成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_ATD_TRANSFER_FAILED,    /**< 咨询转失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_SET_IPT_SERVICE_SUCCESS,     /**< 登记业务成功,仅在呼叫控制使用
                                                <br>param1：CALL_E_SERVICE_CALL_TYPE enIPTServiceType
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SET_IPT_SERVICE_FAILED,      /**< 登记业务失败,仅在呼叫控制使用
                                                <br>param1：CALL_E_SERVICE_CALL_TYPE enIPTServiceType
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_SIPACCOUNT_WMI,              /**< 留言通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_MSG_WAIT_INFOS*  */    
    CALL_E_EVT_VVM_DOWNLOAD_SUCCESS_NOTIFY, /**< VVM下载结果成功通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulDataLen
                                                <br>data：  pcData  */    
    CALL_E_EVT_VVM_DOWNLOAD_FAIL_NOTIFY,    /**< VVM下载结果失败通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VVM_FORWARD_SUCCESS_NOTIFY,  /**< VVM转发留言成功通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VVM_FORWARD_FAIL_NOTIFY,     /**< VVM转发留言失败通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VVM_DELETE_SUCCESS_NOTIFY,   /**< VVM删除留言成功通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VVM_DELETE_FAIL_NOTIFY,      /**< VVM删除留言失败通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VVM_DELETEALL_SUCCESS_NOTIFY,/**< VVM删除所有留言成功通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VVM_DELETEALL_FAIL_NOTIFY,   /**< VVM删除所有留言失败通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_VoiceMail_SUB_SUCCESS,  /**< 语言邮箱订阅成功通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_VoiceMail_SUB_FAILED,   /**< 语言邮箱订阅失败通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_TO_UI_JOINT_START,           /**< 联动开启事件
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_CLOSE,           /**< 联动关闭事件
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_ACCEPTCALL,      /**< 联动代接事件
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_STARTCALL,       /**< 联动代拨事件
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_HUNGUP,          /**< 联动代挂事件
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_HOLD,            /**< 联动保持请求
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_UNHOLD,          /**< 联动恢复请求
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*   */    
    CALL_E_EVT_TO_UI_JOINT_DIVERT,          /**< 联动偏转请求
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_BLDTRANSFER,     /**< 联动盲转请求
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UP_JOINT_TO_CONF,         /**< 联动两方转三方
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_DTMF,            /**< 联动发送DTMF消息
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_CONFCREATE,      /**< 联动创建会议
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_ONLINE,          /**< 联动话机上线
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_OFFLINE,         /**< 联动话机下线
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_ONHOOK,          /**< 联动话机已挂机
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_OFFHOOK,         /**< 联动话机已摘机
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_OUTGOING,        /**< 联动话机已呼出
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_ESTABLISHED,     /**< 联动话机进入通话中
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_RINGRING,        /**< 联动话机振铃
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE, /**< 语音切换到话机
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC,    /**< 语音切换到pc
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_CREATE_CONFERENCE,   /**< IPPHONE创会通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*   */    
    CALL_E_EVT_TO_UI_JOINT_REFER_RESULT,    /**< 联动转移结果
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_STARTVIDEOCALL,  /**< 联动视频代拨事件
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_JOINT_CONF_RESULT,     /**< 联动PC建会结果通知话机的返回消息
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINT_CMD_INFOS*  */    
    CALL_E_EVT_TO_UI_CTD_INFO,              /**< CTD info消息
                                                <br>param1：ulCallID
                                                <br>param2：ulServiceType
                                                <br>data：  CALL_S_CTD_INFO_BODY*  */    
    CALL_E_EVT_TO_UI_JOINT_REPLACECALL,	    /**< 联动PC替换呼叫消息
                                                <br>param1：ulCallID
                                                <br>param2：ulServiceType
                                                <br>data：  CALL_S_CTD_INFO_BODY*  */
    CALL_E_EVT_TO_UI_JOINT_JOINMSCONF,      /**< 联动加入融合会议上报
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINMSCONF_INFO*  */    
    CALL_E_EVT_TO_UI_JOINT_PEER_CAPS_REPORT,/**< 联动话机是否具体视频能力上报
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_JOINMSCONF_INFO*  */    
	CALL_E_EVT_SERVER_LINK_OK,              /**< 服务器连接正常，话机自 检
                                                <br>param1：ulCallID
                                                <br>param2：ucCheckingServerIndex
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_RECORD_SUCCESS,         /**< 记录语音开启成功
                                                <br>param1：ulID
                                                <br>param2：ulIDType
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_RECORD_FAILED,          /**< 记录语音开启失败
                                                <br>param1：ulID
                                                <br>param2：ulIDType
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_UNRECORD_SUCCESS,       /**< 记录语音关闭成功
                                                <br>param1：ulID
                                                <br>param2：ulIDType
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_UNRECORD_FAILED,        /**< 记录语音关闭失败
                                                <br>param1：ulID
                                                <br>param2：ulIDType
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_CALLINFO_SUB_FAILED,    /**< 共享线路状态订阅失败
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_CALLINFO_UNSUB_FAILED,  /**< 共享线路状态去订阅失败
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_LINESEIZE_UNSUB_FAILED, /**< 共享摘机去订阅失败
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulLineID
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_LINESEIZE_UNSUB_SUCCESS,/**< 共享摘机去订阅成功
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulLineID
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_LINESEIZE_SUCCESS,      /**< 共享摘机成功
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulLineID
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_LINESEIZE_FAILED,       /**< 共享摘机失败
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulLineID
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_CALLINFO_NOTIFY,        /**< 共享线路状态通知
                                                <br>param1：ulStateCount
                                                <br>param2：无
                                                <br>data：  CALL_S_SCA_CALLINFO*  */    
    CALL_E_EVT_CALL_MODIFY_SUCCESS,         /**< 修改通话成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_MODIFY_FAILED,          /**< 修改通话失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_JOIN_CONF,              /**< 通话加入本地会议，通知通话状态
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_LCONF_JOIN_SUCCESS,          /**< 本地会议加入成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_JOIN_FAILED,           /**< 本地会议加入失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_TALK_STATE_CHANGE,     /**< 与会者发言状态改变
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_CONFEREE_DROPED,       /**< 剔除与会者/与会者退出会场
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_CONFER_ENDED,          /**< 结束会议通知
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_HOLD_SUCESS,           /**< 保持会场成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_HOLD_FAILED,           /**< 保持会场失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_UNHOLD_SUCESS,         /**< 恢复会场成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_LCONF_UNHOLD_FAILED,         /**< 恢复会场失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONFER_LOCAL_INFO*  */    
    CALL_E_EVT_CALL_MOBILE_EXTEND_SUCCESS,  /**< 手机分机切换成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_MOBILE_EXTEND_FAILED,   /**< 手机分机切换失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_ACBCALL_REQ,            /**< ACB请求
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_ACB_REQ_INFO*  */    
    CALL_E_EVT_CALL_ACBCALL_TIMEOUT,        /**< ACB超时
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_IPT_DATA*  */    
    CALL_E_EVT_CALL_CALLPARK_GET_SUCCESS,   /**< 驻留取回成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_CALLPARK_GET_FAILED,    /**< 驻留取回失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_CALLPARK_INVALID,       /**< 驻留超时或者被取回
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CONTACT_STATUS_CHANGE,       /**< 联系人状态上报
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulNum
                                                <br>data：  pcData  */
    CALL_E_EVT_CONTACTINCRE_STATUS_CHANGE,  /**< PGM联系人增量上报
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  pcData  */    
    CALL_E_EVT_CONTACT_INFO,                /**< 联系人信息
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONTACT_INFO*  */    
    CALL_E_EVT_PHONE_SETTING_STATUS_CHANGE, /**< 发布设置状态
                                                <br>param1：ulSipAccountID
                                                <br>param2：CALL_E_CONTACT_STATUS
                                                <br>data：  无 */    
    CALL_E_EVT_ONLINESTATE_NOTIFY_INFO,     /**< 在线状态订阅notify body上报
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulSendNum
                                                <br>data：  pcBodyTmp  */    
    CALL_E_EVT_NETADDR_NOTIFY_INFO,         /**< 网络地址本订阅notify body上报
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_IDO_NETADDRESS*  */    
    CALL_E_EVT_FORCEUNREG_INFO,             /**< 账号被踢info body上报
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_IDO_FORCEUNREG*  */    
    CALL_E_EVT_SUB_ONLINESTATE_RESULT_INFO, /**< 在线状态订阅结果上报
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulResult
                                                <br>data：  无  */    
    CALL_E_EVT_SUB_NETADDR_RESULT_INFO,     /**< 网络地址本订阅结果上报
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_AUTHORIZE_SUCCESS,      /**< 鉴权成功
                                                <br>param1：ulResult
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_AUTHORIZE_FAILED,       /**< 鉴权失败
                                                <br>param1：ulResult
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_NEW_SERVICE_RIGHT,           /**< 业务权限改变，通知界面
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_SERVICERIGHT_CFG*  */    
    CALL_E_EVT_SERVERCONF_INCOMING,         /**< 会议邀请事件
                                                <br>param1：ulConfID
                                                <br>param2：ulCallID
                                                <br>data：  CALL_S_CONF_INFO*  */    
    CALL_E_EVT_SERVERCONF_CREATE_RESULT,    /**< 创建会议结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  pcBody */    
    CALL_E_EVT_SERVERCONF_CONNECT_RESULT,   /**< 加入会议结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  CALL_S_CONF_CONNECT_RESULT*  */    
    CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT,   /**< 添加与会者结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  pcAttendees*  */    
    CALL_E_EVT_SERVERCONF_REFRESHLIST,      /**< 刷新与会者列表
                                                <br>param1：ulConfID
                                                <br>param2：ulAttendeeCount
                                                <br>data：  CALL_S_CONF_MEMBER*  */    
    CALL_E_EVT_SERVERCONF_SUBJECT,          /**< 上报会议主题
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONF_SUBJECT*  */    
    CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM,     /**< 上报主席号码
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pcChairNum */    
    CALL_E_EVT_SERVERCONF_DATACONF_PARAM,   /**< 上报数据会议相关参数
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  CALL_S_DATACONF_PARAM*  */    
    CALL_E_EVT_SERVERCONF_MODIFYATTENDEE_RESULT,   /**< 修改与会者发言权结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  pcAttendeeNumber */    
    CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT,   /**< 踢出与会者结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  pcAttendeeNumber */    
    CALL_E_EVT_SERVERCONF_END_RESULT,       /**< 结束会议结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_ATTENDEEKICKED,   /**< 与会者被踢出
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pcAttendeeNum  */    
    CALL_E_EVT_SERVERCONF_ENDED,            /**< 会议被结束
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS,   /**< 与会者加入成功
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_ACCESSCODEJOINED_SUCCESS,   /**< 接入码呼叫加入，与会者加入成功
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED,   /**< 与会者加入失败
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_ATTENDEEQUIT,     /**< 与会者退出
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_ADDRESSOR,        /**< 显示发言人
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pstSpeakMem  */    
    CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF, /**< 被转会议
                                                <br>param1：ulConfID
                                                <br>param2：ulCallID
                                                <br>data：  CALL_S_CONF_BETRANSFERTOCONF*  */    
    CALL_E_EVT_BETRANSFERTOPRERECECONF,     /**< 被转入融合会议 
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO* */
    CALL_E_EVT_SERVERCONF_TRANSFERTOCONF_SUCCESS,   /**< 转会议成功
                                                <br>param1：ulConfID
                                                <br>param2：ulCallID
                                                <br>data：  CALL_S_CONF_TRANSFERTOCONF_RESULT*  */    
    CALL_E_EVT_SERVERCONF_TRANSFERTOCONF_FAILED,   /**< 转会议失败
                                                <br>param1：ulConfID
                                                <br>param2：ulCallID
                                                <br>data：  CALL_S_CONF_TRANSFERTOCONF_RESULT */    
    CALL_E_EVT_SERVERCONF_HOLD_SUCESS,      /**< 保持会场成功
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_HOLD_FAILED,      /**< 保持会场失败
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  无   */    
    CALL_E_EVT_SERVERCONF_UNHOLD_SUCESS,    /**< 恢复会场成功
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  无   */    
    CALL_E_EVT_SERVERCONF_UNHOLD_FAILED,    /**< 恢复会场失败
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  无   */    
    CALL_E_EVT_SERVERCONF_MUTE_STATUS_CHANGE,   /**< 会场静音状态变更
                                                <br>param1：ulConfID
                                                <br>param2：bMuted
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_SERVERCONF_LOCK_STATUS_CHANGE,   /**< 会场锁定状态变更
                                                <br>param1：ulConfID
                                                <br>param2：bLocked
                                                <br>data：  无  */
    CALL_E_EVT_PICKUP_NOTIFY,               /**< 同组代答通知/取消
                                                <br>param1：bIndicate
                                                <br>param2：ulSipAccoutID
                                                <br>data：  CALL_S_TIPINFO*  */    
    CALL_E_EVT_FORWARD_RESULT,              /**< 前转呼叫的结果
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_FORWARD_SERVICE*  */    
    CALL_E_EVT_IMS_FORWARD_RESULT,          /**< IMS被前转的目的号码结果
                                                <br>param1：ulSipAccountId
                                                <br>param2：ulCallID
                                                <br>data：  CALL_S_HISTORY_INFO*  */    
    CALL_E_EVT_CALL_LOGOUT_NOTIFY,          /**< 通知界面logout
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_TURN_CALL_NOTIFY,            /**< 通知界面，手机分机，分机接听、挂断
                                                <br>param1：bIndicate
                                                <br>param2：ulSipAccoutID
                                                <br>data：  pszNumber  */    
    CALL_E_EVT_SUB_BLF_RESULT_NOTIFY,       /**< BLF订阅结果
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulResult
                                                <br>data：  pvSubData  */    
    CALL_E_EVT_SUB_RLS_RESULT_NOTIFY,       /**< RLS订阅结果
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulResult
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_CALLOUT_TIMEOUT,        /**< 呼出超时
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_REPORTED_CALLINFO,      /**< 语音质量上报
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_CLEAN_SCALINE,          /**< 清除共享线路状态
                                                <br>param1：accountid
                                                <br>param2：appearance_lineIndex
                                                <br>data：  无  */    
    CALL_E_EVT_UM_MSG_NOTIFY,               /**< UM 事件定义
                                                <br>param1：ulSipAccoutID
                                                <br>param2：无
                                                <br>data：  CALL_S_UM_MSG*  */    
    CALL_E_EVT_CALL_INTERCOM_NUMBER,        /**< 上报界面AA推送的intercom号码
                                                <br>param1：ulSipAccoutID
                                                <br>param2：无
                                                <br>data：  pszIntercomNumber*  */    
    CALL_E_EVT_CALL_CALLPARK_SUCCESS,       /**< 呼叫驻留成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_183_BUSY,               /**< 通话收到183busy
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_PICKUP_REMOTE_INFO,     /**< 代答主叫方信息
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_PICKUP_REMOTE_INFO*  */    
    CALL_E_EVT_CALL_ACB_LIST_NOTIFY,        /**< 回呼列表通知
                                                <br>param1：ulSipAccountID
                                                <br>param2：ulACBCount
                                                <br>data：  CALL_S_ACB_INFO*  */    
    CALL_E_EVT_CALL_PICKUP_INTERCOM_SUCCESS,/**< intercom接起成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_PICKUP_INTERCOM_FAILED, /**< intercom接起失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_INTERCOM_BEPICKUP,      /**< intercom 被pick up 事件
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_UPATE_REMOTEINFO,       /**< 更新远端号码信息
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_SRTP_STATE,             /**< SRTP开启或关闭
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_PINCODE_VALID,          /**< 通话中是否启用 PinCode
                                                <br>param1：ulCallID
                                                <br>param2：bPinCodeValid
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_PINCODE_OK,             /**< 密码验证通过
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_PINCODE_ERROR,          /**< 密码验证失败，需重新输入
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_CALLACCEPTED_RMTCTRL,   /**< 对端回复 200 OK 带 P-Notification: Callee Ctrl
                                                <br>param1：ulCallID
                                                <br>param2：ulRmtCtrl
                                                <br>data：  无  */
    CALL_E_EVT_CALL_CALL_REINVITED,         /**< Call接受对端的Reinvite后 向上报告
                                                <br>param1：ulCallID
                                                <br>param2：enHoldType
                                                <br>param3: bIsfocus
                                                <br>data：  无 */    
    CALL_E_EVT_SET_IPT_SERVICE_BATCH_SUCCESS,   /**< 批量登记业务成功
                                                <br>param1：CALL_E_CALL_EVENT enIPTServiceType
                                                <br>param2：ulResultNum
                                                <br>data：  pulResultlist */    
    CALL_E_EVT_SET_IPT_SERVICE_BATCH_FAILED,/**< 批量登记业务失败
                                                <br>param1：CALL_E_CALL_EVENT enIPTServiceType
                                                <br>param2：ulResultNum
                                                <br>data：  pulResultlist  */    
    CALL_E_EVT_SET_CALL_LIMIT_ON_LOCKED,    /**< 登记密码限呼失败(被锁定)
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SET_CALL_LIMIT_OFF_LOCKED,   /**< 取消密码限呼失败(被锁定)
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_MERGER_RESULT,    /**< 合并会议结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  pcBody  */    
    CALL_E_EVT_SERVERCONF_SPLIT_RESULT,     /**< 拆分会议结果
                                                <br>param1：ulConfID
                                                <br>param2：ulResult
                                                <br>data：  pcBody  */    
    CALL_E_EVT_ACCOUNT_STATUS_CHANGE,       /**< 账号状态变更
                                                <br>param1：ulSipAccountID
                                                <br>param2：CALL_E_CONTACT_STATUS enStatus
                                                <br>data：  无  */    
    CALL_E_EVT_MESSAGE_RELOGIN_REQUEST,     /**< 收到relogin的message后通知界面重新AA登录
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_CALL_ONEKEY_TO_WM_ON_CALL_SUCCESS,   /**< 上报一键转VM成功
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_ONEKEY_TO_WM_ON_CALL_FAIL,   /**< 上报一键转VM失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_CALL_CALLPARK_FAILED,        /**< 驻留失败
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_CALL_INFO*  */    
    CALL_E_EVT_SERVERCONF_CONNECT_ONEKEY_TO_CONF_RESULT,   /**< 一键加入会议结果
                                                <br>param1：ulCallID
                                                <br>param2：ulResult
                                                <br>data：  CALL_S_ONEKEY_TO_CONF_RESULT*  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_CREATEWND_RESULT,   /**< 视频会议创建窗口结果
                                                <br>param1：ulConfID
                                                <br>param2：ulCreateResult
                                                <br>data：  CALL_S_VIDEOCONFWND_INFO*  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_CREATEVIDEO_MEETING_FAILED,   /**< 创建视频会议失败
                                                <br>param1：ulConfID
                                                <br>param2：ulReason
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_LEAVECONF_RESULT,   /**< 视频会议主动离开会议结果
                                                <br>param1：ulConfID
                                                <br>param2：ulLeaveResult
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_ATTEND_JOINED_CONF,   /**< 视频会议成员加入会议
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pszAttendNum */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_END_CONF,   /**< 视频会议结束
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_BEKICKOUT_CONF,   /**< 视频会议中被主席踢出
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_LEAVE_CONF,   /**< 视频会议中有与会者退出
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pszAttendNum  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_STATUS_CHANGE,   /**< 视频会议中与会者包含自己的视频状态改变通知
                                                <br>param1：ulConfID
                                                <br>param2：CALL_E_VIDEOCONF_DEVICE_STATUS eVideoConfVideoStatus
                                                <br>data：  pszAttendNum  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_REQUEST_CHANGE,   /**< 视频会议中视频被其他与会者请求开启
                                                <br>param1：ulConfID
                                                <br>param2：bOpenVideo
                                                <br>data：  pszAttendNum  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_DEVICE_STATUS,   /**< 视频会议中与会者包含自己的视频设备状态改变通知: 拔插
                                                <br>param1：ulConfID
                                                <br>param2：CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS eDeviceStatus
                                                <br>data：  pszAttendNum */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_JOINCHANNEL,   /**< 视频加入到高低流时的反馈触发条件：加入到高低流
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  CALL_S_VIDEOCONF_DOUBLESTREAM_STATUS*  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_DISCONNECT,   /**< 视频网络失去连接
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_RECONNECT,   /**< 视频网络重新连上
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_USERDEVICE_STATUSCHANGE,   /**< 视频发送者设备状态改变(暂停或是取消暂停)
                                                <br>param1：ulConfID
                                                <br>param2：CALL_E_VIDEOCONF_DEVICE_STATUS eLocalDeviceStatus
                                                <br>data：  pszAttendNum */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_WARNING_FLOWCONTROL,   /**< 流控告警(当前视频参数下，还需要流控，请关闭视频的提示)
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pszAttendNum  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_NOTIFY_FLOWCONTROL,   /**< 流控视频分辨率更改通知
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pszAttendNum  */    
    CALL_E_EVT_SERVERCONF_VOICECONF_TO_VIDEOCONF_SUCCESS,   /**< 音频会议转视频会议成功
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_SERVERCONF_VOICECONF_TO_VIDEOCONF_FAILED,   /**< 音频会议转视频会议失败
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_SERVERCONF_VIDEO_ON_FIRST_KEYFRAME,   /**< 关键帧通知
                                                <br>param1：ulConfID
                                                <br>param2：无
                                                <br>data：  pszAttendNum  */    
    CALL_E_EVT_SERVERCONF_VIDEOCONF_NET_STATUS,   /**< 网络状态通知
                                                <br>param1：ulNetStatus
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_MEETING_MSG_NOTIFY,          /**< 会议事件定义
                                                <br>param1：ulSipAccoutID
                                                <br>param2：无
                                                <br>data：  CALL_S_UM_MEETING_MSG*  */    
    CALL_E_EVT_GET_MEETING_CONF_RESULT,     /**< 获取会议列表结果
                                                <br>param1：ulResult
                                                <br>param2：ulSipAccount
                                                <br>data：  CALL_S_GETCONF_MEETING_LIST_INFO*  */    
    CALL_E_EVT_GET_MEETING_CONF_XML_RESULT, /**< 获取会议XML 文件结果
                                                <br>param1：ulResult
                                                <br>param2：ulSipAccount
                                                <br>data：  pFileNameList  */    
    CALL_E_EVT_SIP_AUTH_INFO_WRITTEN,       /**< 账户鉴权信息写入配置文件成功后通知UI
                                                <br>param1：ulAccountID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SWITCH_DND_SUCCESS,          /**< 切换DND模式成功
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_SWITCH_DND_FAIL,             /**< 切换DND模式失败
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_CALL_RECORDINFO_NOTIFY,      /**< 通知记录语音结果
                                                <br>param1：ulID
                                                <br>param2：ulIDType
                                                <br>data：  CALL_S_RECORD_INFO*  */    
    CALL_E_EVT_SPKDEV_MUTE_CHANGE,          /**< 扬声器设备静音状态变化 iMute 当前静音状态 0当前状态为非静音  非0 当前状态为静音
                                                <br>param1：iMute
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_MICDEV_MUTE_CHANGE,          /**< 麦克风设备静音状态变化 iMute 当前静音状态 0当前状态为非静音  非0 当前状态为静音
                                                <br>param1：iMute
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VMTC_VERSION_INFO,           /**< VMTC版本信息 uiVerInfo 版本比较结果 0:版本兼容 1:VM版本老 2:TC版本老
                                                <br>param1：uiVerInfo
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VMTC_DISCONNECT,             /**< VMTC断开连接通知 uiInfo 断开连接信息
                                                <br>param1：uiInfo
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VMTC_CONNECTOK,              /**< VMTC连接成功通知 uiInfo 连接成功信息
                                                <br>param1：uiInfo
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SYN_MISSCALL,                /**< 联动通话记录同步
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无 */    
    CALL_E_EVT_HUNTGROUP_STATUS_CHANGE,     /**< 通知huntgroup状态改变
                                                <br>param1：ulSipAccountID
                                                <br>param2：无
                                                <br>data：  CALL_S_CONTACT_STATUS*  */    
    CALL_E_EVT_PAGING_INCOMING,             /**< 通知paging来电
                                                <br>param1：ulGroupID
                                                <br>param2：无
                                                <br>data：  CALL_S_PAGING_GROUP*  */    
    CALL_E_EVT_PAGING_ENDED,                /**< 通知paging结束播
                                                <br>param1：ulGroupID
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_SIPPORT_CHANGE,              /**< sip端口变更通知
                                                <br>param1：ulSipPort
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_AUDIO_DEVICE_CHANGED,        /**< 音频输入/输出设备变更通知
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_AUDIO_DEVICE_INFO*  */    
    CALL_E_EVT_AUDIO_INPUT_DEVICE_CHANGED,  /**< 音频输入设备变更通知
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_AUDIO_OUTPUT_DEVICE_CHANGED, /**< 音频输出设备变更通知
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_VIDEO_DEVICE_CHANGED,        /**< 视频输入设备(Capture)变更通知
                                                <br>param1：ulCallID
                                                <br>param2：bIsDeviceLost, 表示当前摄像头是否丢失, true表示丢失
                                                <br>data：  CALL_S_VIDEO_DEVICE_INFO*  */    
    CALL_E_EVT_MEDIA_ERROR_INFO,            /**< 媒体错误信息通知
                                                <br>param1：ulCallID
                                                <br>param2：无
                                                <br>data：  CALL_S_MEDIA_ERRORINFO*  */    
    CALL_E_EVT_PASSWORD_CHANGEED_RESULT,    /**< 密码修改结果
                                                <br>param1：ulResult
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_GET_LICENSE_TYPE_RESULT,     /**< 获取license类型响应
                                                <br>param1：ulResult TUP_SUCCESS 成功  其他值 失败
                                                <br>param2：ulLicenseType (LOGIN_E_LICENSE_TYPE)
                                                <br>data：  无  */    
    CALL_E_EVT_APPLY_LICENSE_RESULT,        /**< 申请license响应
                                                <br>param1：ulResult TUP_SUCCESS 成功  其他值 失败
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_REFRESH_LICENSE_FAILED,      /**< 保活license失败
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_RELEASE_LICENSE_RESULT,      /**< 释放license响应
                                                <br>param1：ulResult TUP_SUCCESS 成功  其他值 失败
                                                <br>param2：无
                                                <br>data：  无  */    
    CALL_E_EVT_IDO_OVER_BFCP,               /**< id会控使用bfcp方式
                                                <br>param1：ulCallID
                                                <br>param2：bIdoOverBfcp
                                                <br>data：  无  */    
    CALL_E_EVT_DEVICE_STATUS_CHANGE,        /**< 耳机 设备状态变更上报
                                                <br>param1：istatus
                                                <br>data：  无  */    
    CALL_E_EVT_SIP_AUTH_TYPE,               /**< sip认证方式
                                                <br>param1：ulSipAccount
                                                <br>param2：eAuthType （CALL_E_AUTH_TYPE）
                                                <br>data：  无  */    
    CALL_E_EVT_UPORTAL_TOKEN_REFRESH,       /**< uportal token刷新通知
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_UPORTAL_TOKEN_REFRESH_INFO */        
    CALL_E_EVT_COMPLETE_LOAD_SERVIE_RIGHT,  /**< 收到relogin的message后通知界面重新AA登录 
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  CALL_S_UPORTAL_TOKEN_REFRESH_INFO */     
    CALL_E_EVT_REFER_NOTIFY,                /**< 转移通知
                                                <br>param1：ulCallId
                                                <br>param2：无
                                                <br>data：  无 */
    CALL_E_EVT_EXIT_UI_MSGQUEUE,            /**< 退出消息队列特殊消息，置于最后 
                                                <br>param1：无
                                                <br>param2：无
                                                <br>data：  PID名 */    

    CALL_E_EVT_BUTT
} CALL_E_CALL_EVENT;




/**
 * SIP账户注册状态
 */
typedef enum tagCALL_E_REG_STATE
{
    CALL_E_REG_STATE_UNREGISTER,     /**< SIP账户未注册 */
    CALL_E_REG_STATE_REGISTERING,    /**< SIP账户注册中 */
    CALL_E_REG_STATE_DEREGISTERING,  /**< SIP账户注销中 */
    CALL_E_REG_STATE_REGISTERED,     /**< SIP账户已注册 */
    CALL_E_REG_STATE_BUTT            /**< SIP账户无效状态 */
} CALL_E_REG_STATE;

/**
 * 呼叫类型
 */
typedef enum tagCALL_E_CALL_TYPE
{
    CALL_E_CALL_TYPE_IPAUDIO,        /**< IP语音呼叫 */
    CALL_E_CALL_TYPE_IPVIDEO,        /**< IP视频呼叫 */
    CALL_E_CALL_TYPE_BUTT            /**< 无效类型呼叫 */
} CALL_E_CALL_TYPE;


/** 
 * 呼叫基本状态
 */
typedef enum tagCALL_E_CALL_STATE
{
    CALL_E_CALL_STATE_IDLE,         /**< 呼叫空闲态 */
    CALL_E_CALL_STATE_IN,           /**< 呼叫呼入态 */
    CALL_E_CALL_STATE_OUT,          /**< 呼叫呼出态 */
    CALL_E_CALL_STATE_LIVE,         /**< 呼叫通话态 */
    CALL_E_CALL_STATE_HOLD,         /**< 呼叫保持态 */
    CALL_E_CALL_STATE_END,          /**< 呼叫结束态 */
    
    CALL_E_CALL_STATE_BUTT          /**< 呼叫无效态 */
} CALL_E_CALL_STATE;


/** 
 * 设备类型
 */
typedef enum tagCALL_E_DEVICE_TYPE
{
    CALL_E_CALL_DEVICE_MIC,         /**< 麦克风设备 */
    CALL_E_CALL_DEVICE_SPEAK,       /**< 扬声器设备 */
    CALL_E_CALL_DEVICE_VIDEO,       /**< 视频设备 */
    CALL_E_CALL_DEVICE_BUTT         /**< 无效设备 */
} CALL_E_DEVICE_TYPE;


/**
 * 振铃类型
 */
typedef enum tagCALL_E_CALL_ALERTTYPE
{
    CALL_E_CALL_ALERTTYPE_COMMON = 0x1,     /**< 普通振铃 */
    CALL_E_CALL_ALERTTYPE_INTERNAL,         /**< 局内振铃 */
    CALL_E_CALL_ALERTTYPE_EXTERNAL,         /**< 局外振铃 */
    CALL_E_CALL_ALERTTYPE_NETWORK,          /**< 网络彩铃 */
    CALL_E_CALL_ALERTTYPE_SILENCE,          /**< 来电静铃 */
    CALL_E_CALL_ALERTTYPE_WAKEUP,           /**< 闹醒振铃 */
    CALL_E_CALL_ALERTYPE_HUNTGROUP,         /**< HUNTGROUP来电振铃 */

    CALL_E_CALL_ALERTTYPE_BUTT = 0x0
} CALL_E_CALL_ALERTTYPE;


/** 
 * 上报给界面的语言留言类型
 */
typedef enum tagCALL_E_MSG_WAIT_TYPE
{
    CALL_E_MSG_WAIT_TYPE_VOICE = 0,     /**< 语音消息 */
    CALL_E_MSG_WAIT_TYPE_VIDEO,         /**< 视频消息 */
    CALL_E_MSG_WAIT_TYPE_FAX,           /**< 传真消息 */
    CALL_E_MSG_WAIT_TYPE_PAGER,         /**< 页面信息 */
    CALL_E_MSG_WAIT_TYPE_MULTIMEDIA,    /**< 媒体消息 */
    CALL_E_MSG_WAIT_TYPE_TEXT,          /**< 文本消息 */
    CALL_E_MSG_WAIT_TYPE_VITRUALVM,     /**< 虚拟语音留言消息 */
    CALL_E_MSG_WAIT_TYPE_BUTT           /**< 未知消息 */
} CALL_E_MSG_WAIT_TYPE;


/**
 * 会议角色
 */
typedef enum tagCALL_E_CONF_ROLE
{
    CALL_E_CONF_ROLE_ATTENDEE,          /**< 与会者 */
    CALL_E_CONF_ROLE_CHAIRMAN,          /**< 主席方 */
    CALL_E_CONF_ROLE_CONFCHAIN,         /**< 会议(合并会议业务) */
    CALL_E_CONF_ROLE_CHAIRMAN_DN,       /**< 主席的DN */
    CALL_E_CONF_ROLE_BUTT
} CALL_E_CONF_ROLE;


/**
 * 服务器会议与会者状态
 */
typedef enum tagCALL_E_CONF_STATE
{
    CALL_E_CONF_ATTENDEE_INVITING,      /**< 邀请中  */
    CALL_E_CONF_ATTENDEE_INVITE_FAIL,   /**< 邀请失败  */
    CALL_E_CONF_ATTENDEE_ADD_FAIL,      /**< 添加失败  */
    CALL_E_CONF_ATTENDEE_INCONF,        /**< 会议中  */
    CALL_E_CONF_ATTENDEE_OUT,           /**< 退出会议 */
    CALL_E_CONF_ATTENDEE_STATE_BUTT
} CALL_E_CONF_ATTENDEE_STATE;


/**
 * 服务器会议退出会议类型
 */
typedef enum tagCALL_E_CONF_END_TYPE
{
    CALL_E_CONF_END_TYPE_END,           /**< 结束会议,释放会场 */
    CALL_E_CONF_END_TYPE_LEAVE          /**< 离会,不释放会场 */
} CALL_E_CONF_END_TYPE;


/**
 * 业务权限类型，对应数据结构CALL_S_SERVICERIGHT_CFG
 * @see tagCALL_S_SERVICERIGHT_CFG
 */
typedef enum tagCALL_E_SERVICE_RIGHT_TYPE
{
    CALL_E_SERVICE_RIGHT_TYPE_NULL = -1,                        /**< 空类型，无效类型 */ 
        
    CALL_E_SERVICE_RIGHT_TYPE_ABBRDIAL = 0,                     /**< 缩位拨号 */
    CALL_E_SERVICE_RIGHT_TYPE_CTD,                              /**< 点击呼叫 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLDEFLECTION,                   /**< 呼叫偏转业务 */
    CALL_E_SERVICE_RIGHT_TYPE_ATTENDANT,                        /**< 话务员  */
    CALL_E_SERVICE_RIGHT_TYPE_SECRETARYSERVICE,                 /**< 秘书业务 */
    CALL_E_SERVICE_RIGHT_TYPE_SECRETARYSTATIONSERVICE,          /**< 秘书台 */
    CALL_E_SERVICE_RIGHT_TYPE_GROUPPICKUP,                      /**< 同组代答 */
    CALL_E_SERVICE_RIGHT_TYPE_DESIGNATEPICKUP,                  /**< 指定代答 */
    CALL_E_SERVICE_RIGHT_TYPE_ACB,                              /**< 自动回叫业务 */
    CALL_E_SERVICE_RIGHT_TYPE_RECORDING,                        /**< 记录语音 */
    
    CALL_E_SERVICE_RIGHT_TYPE_CALLTRANSFER,                     /**< 呼叫转接 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLPARK,                         /**< 呼叫预留 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLHOLD,                         /**< 呼叫保持 */
    CALL_E_SERVICE_RIGHT_TYPE_DONOTDISTURB,                     /**< 免打扰 */
    CALL_E_SERVICE_RIGHT_TYPE_THREEPARTYCONFERENCE,             /**< 三方通话 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL,     /**< 无条件转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY,            /**< 遇忙转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY,           /**< 无应答转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_OFFLINE,           /**< 离线转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_UNCONDITIONAL, /**< 无条件转语音邮箱 */
    
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_ONBUSY, /**< 遇忙转语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_NOREPLY,/**< 无应答转语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_OFFLINE,/**< 离线转语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_VOICECONFERENCE,                  /**< 语音会议 */
    CALL_E_SERVICE_RIGHT_TYPE_CORPORATEDIRECTORY,               /**< 企业通讯录 */
    CALL_E_SERVICE_RIGHT_TYPE_INDIVIDUALDIRECTORY,              /**< 个人通讯录 */
    CALL_E_SERVICE_RIGHT_TYPE_TURNPHONE,                        /**< 一键转接 */
    CALL_E_SERVICE_RIGHT_TYPE_VOICECALL,                        /**< 音频通话功能 */
    CALL_E_SERVICE_RIGHT_TYPE_EXTENSIONMOBILITY,                /**< 分机携带,AA不推送，WEB上修改 */
    CALL_E_SERVICE_RIGHT_TYPE_SUBREGSTATE,                      /**< 分机携带时订阅业务权限,AA不推送，WEB上修改 */
    
    CALL_E_SERVICE_RIGHT_TYPE_BLF,                              /**< BLF, AA不推送，WEB上修改 */
    CALL_E_SERVICE_RIGHT_TYPE_PRESENCE,                         /**< 状态呈现 */
    CALL_E_SERVICE_RIGHT_TYPE_INTERCOM,                         /**< intercom业务 */
    CALL_E_SERVICE_RIGHT_TYPE_DICF,                             /**< 拒绝前转来电 */
    CALL_E_SERVICE_RIGHT_TYPE_ABSENT,                           /**< 缺席业务 */
    CALL_E_SERVICE_RIGHT_TYPE_TURN_VM,                          /**< 一键转语音邮箱*/
    CALL_E_SERVICE_RIGHT_TYPE_HOT_LINE,                         /**< 热线业务 */
    CALL_E_SERVICE_RIGHT_TYPE_MCID,                             /**< 恶意呼叫跟 */
    CALL_E_SERVICE_RIGHT_TYPE_CALL_LIMIT,                       /**< 密码限呼 */
    CALL_E_SERVICE_RIGHT_TYPE_CALL_WAIT,                        /**< 呼叫等待 */

    CALL_E_SERVICE_RIGHT_TYPE_VVM,                              /**< 可视化语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_BARGE,                            /**< 强插*/
    CALL_E_SERVICE_RIGHT_TYPE_LBS,                              /**< LBS*/
    CALL_E_SERVICE_RIGHT_TYPE_PRIVACY,                          /**< privacy业务 */
    CALL_E_SERVICE_RIGHT_TYPE_HOLD_PRIVATE,                     /**< 私人保持业务 */
    CALL_E_SERVICE_RIGHT_TYPE_BRIDGE,                           /**< bridge业务 */
    CALL_E_SERVICE_RIGHT_TYPE_RESUME,                           /**< resume业务 */
    CALL_E_SERVICE_RIGHT_TYPE_VOICE_MAIL,                       /**< 语言邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_HUNTGROUP,                        /**< huntgroup权限 */
    CALL_E_SERVICE_RIGHT_TYPE_VIRTUALVM,                        /**< 虚拟语音邮箱 */
    
    CALL_E_SERVICE_RIGHT_TYPE_UC2X_VOICECONFERENCE,             /**< UC2.X立即会议 */
    CALL_E_SERVICE_RIGHT_TYPE_ONENUMBER,                        /**< 一号通 */
    CALL_E_SERVICE_RIGHT_TYPE_ARLERT_SILCNCE,                   /**< 来电静铃 */
    CALL_E_SERVICE_RIGHT_TYPE_ANONYMOUS,                        /**< 匿名呼叫 */
    CALL_E_SERVICE_RIGHT_TYPE_MULTIPLEAPPEARANCESERVICE,        /**< 共享线 */

    CALL_E_SERVICE_RIGHT_TYPE_BUTT
} CALL_E_SERVICE_RIGHT_TYPE;


/**
 * 本地信号音枚举
 */
typedef enum  enumAUDIO_CompoundVoice
{
    COMPOUND_E_NONE   = 0,  /**< 无信号音 */
    COMPOUND_E_BUSY,        /**< 忙音 */    
    COMPOUND_E_BACK,        /**< 回铃音 */
    COMPOUND_E_DIAL,        /**< 拨号音 */
    COMPOUND_E_WAIT,        /**< 呼等音 */
    COMPOUND_E_TIP,         /**< 提示音 */
    COMPOUND_E_WARN,        /**< 警告音 */
    COMPOUND_E_LEAVE,       /**< 会场离开音 */
    COMPOUND_E_UFWD,        /**< 无条件前转特殊拨号音 */

    COMPOUND_E_DTMF0,       /**< dtmf按键0 */
    COMPOUND_E_DTMF1,       /**< dtmf按键1 */
    COMPOUND_E_DTMF2,       /**< dtmf按键2 */
    COMPOUND_E_DTMF3,       /**< dtmf按键3 */
    COMPOUND_E_DTMF4,       /**< dtmf按键4 */
    COMPOUND_E_DTMF5,       /**< dtmf按键5 */
    COMPOUND_E_DTMF6,       /**< dtmf按键6 */
    COMPOUND_E_DTMF7,       /**< dtmf按键7 */
    COMPOUND_E_DTMF8,       /**< dtmf按键8 */
    COMPOUND_E_DTMF9,       /**< dtmf按键9 */ 
    COMPOUND_E_DTMFSTAR,    /**< dtmf按键'*' */
    COMPOUND_E_DTMFJIN,     /**< dtmf按键'#' */
    COMPOUND_E_DTMFA,       /**< dtmf按键A */
    COMPOUND_E_DTMFB,       /**< dtmf按键B */
    COMPOUND_E_DTMFC,       /**< dtmf按键C */
    COMPOUND_E_DTMFD,       /**< dtmf按键D */
    COMPOUND_E_DTMFFLASH,   /**< dtmf按键FLASH */
    
    COMPOUND_E_BUTT
}AUDIO_E_COMPOUNT_VOICE;


/**
 * 音频能力类型
 */
typedef enum tagCALL_E_AUDIO_CAP
{
    CALL_E_AUDIO_CAP_AACLD = 0,  /**< AAC-LD  */
    CALL_E_AUDIO_CAP_G722,       /**< G722  */
    CALL_E_AUDIO_CAP_G7221,      /**< G722.1  */
    CALL_E_AUDIO_CAP_G7222,      /**< G722.2  */
    CALL_E_AUDIO_CAP_G711A,      /**< G711A  */
    CALL_E_AUDIO_CAP_G711U,      /**< G711U  */
    CALL_E_AUDIO_CAP_G729AB,     /**< G729AB  */
    CALL_E_AUDIO_CAP_G726,       /**< G726  */
    CALL_E_AUDIO_CAP_ILBC,       /**< ILBC  */
    CALL_E_AUDIO_CAP_OPUS,       /**< OPUS  */
    CALL_E_AUDIO_CAP_DTMF,       /**< DTMF  */
    
    CALL_E_AUDIO_CAP_BUTT
}CALL_E_AUDIO_CAP;


/** 
 * 视频协议类型
 */
typedef enum tagCALL_E_VIDEO_CAP
{
    CALL_E_VIDEO_CAP_H264 = 0,   /**< H264 */
    CALL_E_VIDEO_CAP_H263,       /**< H264 */
    
    CALL_E_VIDEO_CAP_BUTT
}CALL_E_VIDEO_CAP;


/** 
 * DTMF 传输模式
 */
typedef enum
{
    CALL_E_DTMF_MODE_TRANSPARENT = 0,   /**< 透传模式 */
    CALL_E_DTMF_MODE_RFC2833,           /**< RFC2833模式(自动协商) */
    CALL_E_DTMF_MODE_CONST2833,         /**< 强制2833模式 */
    CALL_E_DTMF_MODE_INFO,              /**< INFO模式 */  
    
    CALL_E_DTMF_MODE_BUTT
}CALL_E_DTMF_MODE;


/** 
 * 网络事件类型
 */
typedef enum tagCALL_E_NET_EVT_TYPE
{
    CALL_E_NET_EVENT_CONNECTED,         /**< 连接成功 */
    CALL_E_NET_EVENT_CONNECTFAIL,       /**< 连接失败 */
    CALL_E_NET_EVENT_LINKUP,            /**< 网卡 UP */
    CALL_E_NET_EVENT_LINKDOWN,          /**< 网卡 DOWN */

    CALL_E_NET_EVENT_BUTT
}CALL_E_NET_EVT_TYPE;


/** 
 * 产品类型
 */
typedef enum tagCALL_E_PRODUCT_TYPE
{
    CALL_E_PRODUCT_TYPE_PHONE = 0,      /**< IP Phone */
    CALL_E_PRODUCT_TYPE_PC,             /**< PC */
    CALL_E_PRODUCT_TYPE_MOBILE,         /**< Mobile */
    
    CALL_E_PRODUCT_TYPE_BUTT
}CALL_E_PRODUCT_TYPE;


/**
 * 音频输入输出设备类型(软终端使用)
 */
typedef enum tagCALL_E_AO_DEV
{
    CALL_E_AO_DEV_SPEAKER = 0,          /**< 扬声器 */
    CALL_E_AO_DEV_BLUETOOTH,            /**< 蓝牙输出 */
    CALL_E_AO_DEV_EARPIECE,             /**< 手柄输出 */
    CALL_E_AO_DEV_HEADSET,              /**< 3.5mm耳机输出 */
    CALL_E_AO_DEV_HDMI,                 /**< HDMI输出 */
    CALL_E_AO_DEV_USB,                  /**< USB输出 */
    CALL_E_AO_DEV_SPEAKERRING,          /**< 扬声器铃音(获取音量值时候用到) */
    CALL_E_AO_DEV_BLUETOOTHRING,        /**< 蓝牙输出铃音(获取音量值时候用到) */
    CALL_E_AO_DEV_HDMIRING,             /**< 手柄输出 */
    CALL_E_AO_DEV_USBRING,              /**< USB输出铃音(获取音量值时候用到) */
    
    CALL_E_AO_DEV_BUTT                  /**< 无效值 */
} CALL_E_AO_DEV;


/**
 * 音频输入输出设备类型(硬终端使用)
 */
typedef enum tagCALL_E_AUDDEV_ROUTE
{
    CALL_E_AUD_DEV_ROUTE_DEFAULT     = 0x0,  /**< 保留值，设置不生效 */
    CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER = 0x1,  /**< 扬声器 ，支持输入输出 */
    CALL_E_AUD_DEV_ROUTE_BLUETOOTH   = 0x2,  /**< 蓝牙耳机 ，支持输入输出 */
    CALL_E_AUD_DEV_ROUTE_EARPIECE    = 0x3,  /**< 听筒 手柄设备，支持输入输出 */
    CALL_E_AUD_DEV_ROUTE_HEADSET     = 0x4,  /**< 3.5毫米耳机 ，支持输入输出 */
    CALL_E_AUD_DEV_ROUTE_SUBDEFAULT  = 0x5,  /**< 保留值，设置不生效 */
    CALL_E_AUD_DEV_ROUTE_HDMI        = 0x6,  /**< HDMI,支持输出 */
    CALL_E_AUD_DEV_ROUTE_USB         = 0x7,  /**< USB耳机 ，支持输入输出 */
    CALL_E_AUD_DEV_ROUTE_MAX         = 0X8   /**< 无效值 */
} CALL_E_AUDDEV_ROUTE;


/**
 * 容灾模式
 */
typedef enum tagCALL_E_REG_FAILOVER_MODE{
    CALL_E_REG_FAILOVER_MODE_REGMASTER,     /**< 主、备先后注册，A-S */
    CALL_E_REG_FAILOVER_MODE_REGALL,        /**< 主、备同时注册, A-A */
    
    CALL_E_REG_FAILOVER_MODE_BUTT
}CALL_E_REG_FAILOVER_MODE;


/**
 * 组网环境类型
 */
typedef enum tagCALL_E_NET_ENVIRONMENT
{
    CALL_E_NET_UC1X = 0,        /**< UC1.0环境*/
    CALL_E_NET_UC2X,            /**< UC2.0环境*/
    CALL_E_NET_OTHERS,          /**< 其他环境，兼容老版本设为2 */
    CALL_E_NET_ASTERISK,        /**< Asterisk环境*/
    CALL_E_NET_BROADSOFT,       /**< Broadsoft环境*/
    CALL_E_NET_IPCC,            /**< IPCC环境  */
    CALL_E_NET_IMSUC_MIX,       /**< IMS+UC */
    CALL_E_NET_TE,              /**< 智真 */
    CALL_E_NETWORK_HUAWEIUC,    /**< 华为UC*/
    CALL_E_NET_IMS,             /**< IMS环境 */
    
    CALL_E_NET_BUTT
} CALL_E_NET_ENVIRONMENT;


/**
 * IP协议类型
 */
typedef enum tagCALL_E_IP_PROTOCOL_TYPE
{
    CALL_E_IP_V4 = 0,          /**< IP V4 */
    CALL_E_IP_V6,              /**< IP V6 */
}CALL_E_IP_PROTOCOL_TYPE;


/**
 * 业务权限状态
 */
typedef enum tagCALL_E_SEVICERIGHT_STATUS
{
    CALL_E_SEVICERIGHT_LACK = 0,  /**< 没权限 */
    CALL_E_SEVICERIGHT_HAVE       /**< 有权限 */
} CALL_E_SEVICERIGHT_STATUS;


/**
 * 服务器会议类型
 */
typedef enum tagCALL_E_SERVERCONF_TYPE
{
    CALL_E_SERVERCONF_AUDIO = 1,  /**< 会场类型：语音 */
    CALL_E_SERVERCONF_DATA  = 3   /**< 会场类型：数据+语音 */
} CALL_E_SERVERCONF_TYPE;


/**
 * 服务器会议模式
 */
typedef enum tagCALL_E_CONF_MODE
{
    CALL_E_CONF_MODE_NOMAL = 0,         /**< 立即会议 */
    CALL_E_CONF_MODE_VIDEO,             /**< 视频会议*/
    CALL_E_CONF_MODE_PRESECE_VOICE,     /**< 智真语音会议*/
    CALL_E_CONF_MODE_PRESECE_VIDEO,     /**< 智真视频会议*/
    CALL_E_CONF_MODE_LINKAGE,           /**< 联动会议 */
    
    CALL_E_CONF_MODE_BUTT
}CALL_E_CONF_MODE;


/**
 * 视频预览媒体类型
 */
typedef enum tagCALL_E_REFRESHVIEW_MIDEATYPE
{
    CALL_E_REFRESHVIEW_VIDEO_PREVIEW = 1,   /**< 本地视频预览 */
    CALL_E_REFRESHVIEW_VIDEO = 2,           /**< 普通视频 */
    CALL_E_REFRESHVIEW_DATA = 3             /**< 辅流 */
} CALL_E_REFRESHVIEW_MIDEATYPE;


/**
 * 解码成功的视频媒体类型
 */
typedef enum tagCALL_E_DECODE_SUCCESS_MIDEATYPE
{
    CALL_E_DECODE_SUCCESS_VIDEO = 2,        /**< 普通视频 */
    CALL_E_DECODE_SUCCESS_DATA = 3          /**< 辅流 */
} CALL_E_DECODE_SUCCESS_MIDEATYPE;


/**
 * 媒体类型
 */
typedef enum tagCALL_E_MEDIATYPE
{
    CALL_E_MEDIATYPE_AUDIO, /**< 音频 */
    CALL_E_MEDIATYPE_VIDEO, /**< 普通视频 */
    CALL_E_MEDIATYPE_DATA   /**< 辅流 */
} CALL_E_MEDIATYPE;


/**
 * 视频刷新事件
 */
typedef enum tagCALL_E_REFRESHVIEW_EVENT
{
    CALL_E_LOCALVIEW_ADD = 1,     /**< 本地view添加 */
    CALL_E_LOCALVIEW_REMOVE       /**< 本地view删除 */
} CALL_E_REFRESHVIEW_EVENT;


/**
 * 来电类型
 */
typedef enum tagCALL_E_URI_PARAMTYPE
{
    CALL_E_URI_PARAM_NORAML,                /**< 普通来电 */
    CALL_E_URI_PARAM_INTERCOM,              /**< 对讲机来电 */
    CALL_E_URI_PARAM_PAGING,                /**< Paging来电 */
    CALL_E_URI_PARAM_APPEARANCE_PRIVATE,    /**< 私人呼叫来电 */
    CALL_E_URI_PARAM_BUTT
}CALL_E_URI_PARAMTYPE;


/**
 * 视频窗口类型
 */
typedef enum tagCALL_E_VIDEOWND_TYPE
{
    CALL_E_VIDEOWND_CALLREMOTE = 0,         /**< 通话远端窗口 */
    CALL_E_VIDEOWND_CALLLOCAL,              /**< 通话本地窗口 */
    CALL_E_VIDEOWND_PREVIEW,                /**< 预览窗口 */
    CALL_E_VIDEOWND_CALLDATA,               /**< 辅流窗口 */
    CALL_E_VIDEOWND_BUTT
} CALL_E_VIDEOWND_TYPE;


/**
 * 坐标类型
 */
typedef enum tagCALL_E_COORDINATE_TYPE
{
    CALL_E_COORDINATE_X = 0,               /**< X 轴 */
    CALL_E_COORDINATE_Y,                   /**< Y 轴 */
    CALL_E_COORDINATE_W,                   /**< 宽 */
    CALL_E_COORDINATE_H,                   /**< 高 */
    CALL_E_COORDINATE_Z,                   /**< Z 轴 */  
    CALL_E_COORDINATE_BUTT
} CALL_E_COORDINATE_TYPE;


/**
 * 视频窗口显示类型，eSpace 8950使用
 */
typedef enum tagCALL_E_VIDEOWND_DISPLAY_TYPE
{
    CALL_E_VIDEOWND_DISPLAY_ZOOM = 0,       /**< 0:保持比例不变,加黑边,默认为此值 */
    CALL_E_VIDEOWND_DISPLAY_CUT,            /**< 1:保持比例不变,拉伸裁剪   */
    CALL_E_VIDEOWND_DISPLAY_FULL,           /**< 2:全部填满,不加黑边，不做裁剪   */
    CALL_E_VIDEOWND_DISPLAY_BUTT
} CALL_E_VIDEOWND_DISPLAY_TYPE;


/**
 * 媒体发送模式
 */
typedef enum tagCALL_E_MEDIA_SENDMODE
{
    CALL_E_MEDIA_SENDMODE_INACTIVE = 0x00,  /**< 不收不发 */
    CALL_E_MEDIA_SENDMODE_SENDONLY = 0x01,  /**< 只发 */
    CALL_E_MEDIA_SENDMODE_RECVONLY = 0x02,  /**< 只收 */
    CALL_E_MEDIA_SENDMODE_SENDRECV = 0x04,  /**< 收发 */

    CALL_E_MEDIA_SENDMODE_INVALID  = 0x08   /**< 无效 */
}CALL_E_MEDIA_SENDMODE;


/**
 * 视频变更
 */
typedef enum tagCALL_E_VIDEO_MOD_RESULT
{
    CALL_E_VIDEO_MOD_NORMAL = 0,            /**< 视频正常打开/关闭 */
    CALL_E_VIDEO_MOD_LOW_BW,                /**< 由低带宽造成的视频切换到音频 */ 
    CALL_E_VIDEO_MOD_BUTT
}CALL_E_VIDEO_MOD_RESULT;


/**
 * 带宽级别
 */
typedef enum tagCALL_E_BANDWIDTH_LEVER
{
    CALL_E_BANDWIDTH_NORMAL,                /**< 正常带宽 */
    CALL_E_BANDWIDTH_LOWER,                 /**< 低带宽 */
    CALL_E_BANDWIDTH_LOWEST
}CALL_E_BANDWIDTH_LEVER;


/** 
 * 装备测试，用于IPPhone
 */
typedef struct tagMPROC_S_AUDIO_EQPTTEST
{
    TUP_UINT32 ulVolume;                    /**< 音量大小 */
    TUP_UINT32 ulSampleFreq;                /**< 采样频率 */
    TUP_UINT32 ulBitWide;                   /**< 位宽 */
    TUP_UINT32 em7950AMPType;               /**< TODO */
} MPROC_S_AUDIO_EQPTTEST;


/** 
 * 账号注册结果
 */
typedef struct tagCALL_S_SIP_ACCOUNT_INFO
{
    TUP_UINT32 ulSipAccountID;                      /**< SIP账户ID */
    CALL_E_REG_STATE enRegState;                    /**< SIP账户注册状态 */
    TUP_UINT32 ulReasonCode;                        /**< 注册失败的原因码 */
    TUP_INT8 acUserNum[CALL_D_MAX_USERNAME_LENGTH]; /**< SIP账户用户名 */
    TUP_INT8 acTelNum[CALL_D_MAX_LENGTH_NUM];       /**< SIP账户号码 */
	TUP_INT8 acServer[CALL_D_MAX_SERVER_LENGTH];    /**< SIP服务器信息*/
} CALL_S_SIP_ACCOUNT_INFO;


/** 
 * 呼叫参数
 */
typedef struct tagCALL_S_CALL_PARAMS
{
    TUP_UINT32 ulLineId;                        /**< 线路ID */
    TUP_UINT32 ulCallType;                      /**< 呼叫类型 */
    TUP_UINT32 ulAccountId;                     /**< 账号ID */
    TUP_UINT32 ulReserved;                      /**< 保留字段 */
    TUP_UINT32 ulCallId;                        /**< 呼叫ID, 可做输入输出参数 */
    TUP_INT8 acTelNum1[CALL_D_MAX_LENGTH_NUM];  /**< 电话号码 TODO */
    TUP_INT8 acTelNum2[CALL_D_MAX_LENGTH_NUM];  /**< 电话号码 TODO */
    TUP_VOID* pReserved;                        /**< 保留字段 */
}CALL_S_CALL_PARAMS;


/** 
 * 通话状态信息
 */
typedef struct tagCALL_S_CALL_STATE_INFO
{
    TUP_UINT32 ulSipAccountID;                          /**< 通话所属线路ID */
    TUP_UINT32 ulCallID;                                /**< 通话ID */
    CALL_E_CALL_TYPE enCallType;                        /**< 呼叫类型 */
    CALL_E_CALL_STATE enCallState;                      /**< 通话状态 */
    TUP_INT8 acTelNum[CALL_D_MAX_LENGTH_NUM];           /**< 来电号码 和 作为主叫时的呼出号码 */
    TUP_INT8 acDisplayName[CALL_D_MAX_DISPLAY_NAME];    /**< 来电姓名 */
    TUP_INT8 acDomainIp[CALL_D_MAX_DISPLAY_NAME];       /**< 来电域名 or ip */
    TUP_UINT32 ulReasonCode;                            /**< 失败原因码，@see tagCALL_E_REASON_CODE */ 
    TUP_BOOL bIsIn;                                     /**< 标识该路通话是否为呼入 */
    TUP_BOOL bIsPassiveEnd;                             /**< 标识该路呼叫是否远端挂断 */
    CALL_E_CALL_ALERTTYPE enAlertType;                  /**< 新增振铃类型 */
    TUP_BOOL bIsAccept;                                 /**< 呼叫是否已经接听标志 */
    TUP_BOOL bIsTimeout;                                /**< 呼叫超时标志，用例记录来电超时未接记录 */
    TUP_BOOL bIsInLocalConf;                            /**< 标志是否加入本地会议 */
    TUP_BOOL bIsInBridgeConf;                           /**< 标识是否是进入bridge会议状态 */
    TUP_BOOL bCompletedElsewhere;                       /**< 标识是否是不用计入未接来电的被结束来电 */
    TUP_BOOL bIsAutoAnswer;                             /**< 呼叫是否自动接听标志  */
    TUP_UINT32 ulAutoAnswerTime;                        /**< 呼叫自动接听时间 */
    TUP_UINT32 ulCause;                                 /**< sip呼叫cause码 */
    TUP_CHAR szPresetMsg[CALL_D_MAX_PRESET_MSG_LENGTH]; /**< 预设消息 */
    TUP_BOOL bIsPaging;                                 /**< 是否Paging */
    TUP_BOOL bHaveSDP;                                  /**< 是否带有SDP */
}CALL_S_CALL_STATE_INFO;


/** 
 * 呼叫信息
 */
typedef struct tagCALL_S_CALL_INFO
{
    CALL_S_CALL_STATE_INFO stCallStateInfo;         /**< 通话状态信息 */

    CALL_E_URI_PARAMTYPE enUriType;                 /**< URI 类型 */
    
    TUP_BOOL bIsFwdCallForbidden;                   /**< 服务器指示禁止本地前传,用于对接BROADSOFT服务器 */
    TUP_BOOL bIsFwdCall;                            /**< 是否前转呼叫 */
    TUP_INT8 acFwdFromNum[CALL_D_MAX_LENGTH_NUM];   /**< 前转者号码 */
    TUP_INT8 acFwdFromName[CALL_D_MAX_DISPLAY_NAME];/**< 前转者姓名 */

    TUP_INT8 acTelNumTel[CALL_D_MAX_LENGTH_NUM];    /**< 来电号码 */
    TUP_INT8 acDisplayNameTel[CALL_D_MAX_LENGTH_NUM];/**< 来电姓名 */

    TUP_BOOL bIsShareLine;                          /**< 是否共享线 */
    TUP_UINT32 ulSCALineID;                         /**< 共享线线路ID */
    TUP_UINT32 ulBossLineID;                        /**< 共享线经理线路ID */
    TUP_BOOL   bIsReplace;                          /**< 是否替换线路 */
    TUP_UINT32 ulReplaceID;                         /**< 咨询转，被 替换的原呼叫ID */
    TUP_CHAR acBossNum[CALL_D_MAX_LENGTH_NUM];      /**< 共享线经理号码 */
    TUP_UINT32 ulRmtCtrl;                           /**< 是否对端控 */
    TUP_UINT32 ulSwitchId;                          /**< PC联动一键切换 TODO */

    TUP_BOOL bIsFocus;                              /**< 是否带isfoucs标识，移动会议场景使用*/  
    TUP_INT8 acServerConfType[CALL_D_MAX_LENGTH_NUM];/**< 会议类型，移动会议场景使用*/  
    TUP_INT8 acServerConfID[CALL_D_MAX_LENGTH_NUM]; /**< 会议ID, 移动会议场景使用*/
    TUP_UINT32 ulOrientType;                        /**< 移动视频横竖屏情况*/
    TUP_INT8 acLocalAddr[CALL_D_IP_LENGTH];         /**< 移动上报本地地址*/
    TUP_INT8 acRemoteAddr[CALL_D_IP_LENGTH];        /**< 移动上报远端地址*/
    TUP_INT8 acUserAgent[CALL_D_MAX_LENGTH_NUM];    /**< 对端的UserAgent */
    CALL_E_MEDIA_SENDMODE enAudioSendMode;          /**< 音频媒体方向 */
    CALL_E_MEDIA_SENDMODE enVideoSendMode;          /**< 视频媒体方向 */
    CALL_E_MEDIA_SENDMODE enDataSendMode;           /**< 辅流媒体方向 */

} CALL_S_CALL_INFO;


/** 
 * 语音邮箱通知消息 TODO
 */
typedef struct tagCALL_S_MSG_INFO
{
    CALL_E_MSG_WAIT_TYPE enMsgType;                 /**< 留言灯类型 */
    TUP_UINT32 ulNewMsgNum;                         /**< 新消息个数 */
    TUP_UINT32 ulOldMsgNum;                         /**< 旧消息个数 */
    TUP_UINT32 ulNewEmgMsgNum;                      /**< 新紧急消息个数 */
    TUP_UINT32 ulOldEmgMsgNum;                      /**< 旧紧急消息个数 */
    TUP_CHAR   aszSubscriber[CALL_D_MAX_LENGTH_NUM];/**< 隶属的号码 */
} CALL_S_MSG_INFO;


/** 
 * 语音邮箱通知 TODO
 */
typedef struct tagCALL_S_MSG_WAIT_INFOS
{
    TUP_UINT32 ulMsgCnt;                                    /**< 消息个数 */
    CALL_S_MSG_INFO astMsgInfos[CALL_D_MAX_MSGSUMMARY_NUM]; /**< 消息信息内容 */
} CALL_S_MSG_WAIT_INFOS;


/** 
 * 语音通道MOS信息
 */
typedef struct tagCALL_CHANNEL_EMODEL_RESULT_STRU
{
    TUP_UINT8  ucSendMOSValidFlag;  /**< 发送方向MOS分有效标志,当通道未收到RTCP RR报文时，如下4个发送方向的MOS分参数都无效 */
    TUP_UINT8  ucRecvMOSValidFlag;  /**< 接收方向MOS分有效标志,当通道未收到任何报文或未达到计算周期(RTCP发送周期，5s)时，如下4个接收方向的MOS分参数都无效 */
    TUP_UINT16 uwResv;              /**< 保留位，保证4字节对齐 */

    TUP_FLOAT fSendAverageMosQ;     /**< 发送方向MOS分平均值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
    TUP_FLOAT fSendMaxMosQ;         /**< 发送方向MOS分最大值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
    TUP_FLOAT fSendMinMosQ;         /**< 发送方向MOS分最小值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
    TUP_FLOAT fSendCurMosQ;         /**< 发送方向MOS分当前值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */

    TUP_FLOAT fRecvAverageMosQ;     /**< 接收方向MOS分平均值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
    TUP_FLOAT fRecvMaxMosQ;         /**< 接收方向MOS分最大值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
    TUP_FLOAT fRecvMinMosQ;         /**< 接收方向MOS分最小值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
    TUP_FLOAT fRecvCurMosQ;         /**< 接收方向MOS分当前值,用浮点数表示:取值范围(0, 5], 0xFFFFFFFF表示该参数无效 */
} CALL_CHANNEL_EMODEL_RESULT_STRU;


/** 
 * 音频通道信息
 */
typedef struct tagCALL_S_AUDIO_STREAM_INFO
{
    TUP_BOOL bIsCalling;                                /**< 是否在通话中*/
    TUP_INT8 bIsSRTP;                                   /**< 是否启用SRTP MEDIASERVICE_TRANS_SRTP*/
    TUP_INT8 acEncodeProtocol[CALL_D_PROTOCOL_LENGTH];  /**< 编码协议*/
    TUP_INT8 acDecodeProtocol[CALL_D_PROTOCOL_LENGTH];  /**< 解码协议*/
    TUP_UINT32 ulChannelID;                             /**< 通道ID */
    TUP_UINT32 ulSendBitRate;                           /**< 发送比特率 */
    TUP_UINT32 ulRecvBitRate;                           /**< 接收比特率 */
    TUP_UINT32 ulSendTotalLostPacket;                   /**< 发送方累计包损 */
    TUP_FLOAT fSendLossFraction;                        /**< 发送方丢包率(%) */
    TUP_FLOAT fSendNetLossFraction;                     /**< 发送方网络丢包率(%) */
    TUP_FLOAT fSendJitter;                              /**< 发送方平均抖动(ms) */
    TUP_FLOAT fSendDelay;                               /**< 发送方平均时延(ms) */
    TUP_UINT32 ulRecvTotalLostPacket;                   /**< 接收方累计包损 */
    TUP_FLOAT fRecvLossFraction;                        /**< 接收方丢包率(%) */
    TUP_FLOAT fRecvNetLossFraction;                     /**< 接收方丢包率(%) */
    TUP_FLOAT fRecvJitter;                              /**< 接收方平均抖动(ms) */
    TUP_FLOAT fRecvDelay;                               /**< 接收方平均时延(ms) */
    CALL_CHANNEL_EMODEL_RESULT_STRU stMosResult;        /**< 语音mos值 */
} CALL_S_AUDIO_STREAM_INFO, *CALL_S_AUDIO_STREAM_INFO_PTR;


/** 
 * 视频通道信息
 */
typedef struct tagCALL_S_VIDEO_STREAM_INFO
{
    TUP_INT8 acEncodeName[CALL_MAX_CODEC_NAME_LEN];     /**< 编码名称*/
    TUP_INT8 acDecodeName[CALL_MAX_CODEC_NAME_LEN];     /**< 解码名称*/
    TUP_INT8 acEncoderSize[CALL_MAX_FRAMESIZE_LEN];     /**< 图像分辨率(编码)*/
    TUP_INT8 acDecoderSize[CALL_MAX_FRAMESIZE_LEN];     /**< 图像分辨率(解码)*/
    TUP_INT8 bIsSRTP;                                   /**< 是否启用SRTP,对应MEDIASERVICE_TRANS_SRTP*/
    TUP_UINT32 ulSendFrameRate;                         /**< 视频帧率(编码)*/
    TUP_UINT32 ulRecvFrameRate;                         /**< 视频帧率(解码)*/
    TUP_UINT32 ulVideoSendBitRate;                      /**< 编码码率*/
    TUP_UINT32 ulVideoRecvBitRate;                      /**< 解码码率*/
    TUP_INT8 acEncoderProfile[CALL_MAX_PROFILE_LEN];    /**< 视频编码格式*/
    TUP_INT8 acDecoderProfile[CALL_MAX_PROFILE_LEN];    /**< 视频解码格式*/
    TUP_FLOAT fVideoSendLossFraction;                   /**< 发送方丢包率(%) */
    TUP_FLOAT fVideoSendJitter;                         /**< 发送方平均抖动(ms) */
    TUP_FLOAT fVideoSendDelay;                          /**< 发送方平均时延(ms) */
    TUP_FLOAT fVideoRecvLossFraction;                   /**< 接收方丢包率(%) */
    TUP_FLOAT fVideoRecvJitter;                         /**< 接收方平均抖动(ms) */
    TUP_FLOAT fVideoRecvDelay;                          /**< 接收方平均时延(ms) */
    TUP_UINT32 ulWidth;                                 /**< 视频分辨率-宽*/
    TUP_UINT32 ulHeight;                                /**< 视频分辨率-高*/
    
} CALL_S_VIDEO_STREAM_INFO, *CALL_S_VIDEO_STREAM_INFO_PTR;


/** 
 * 会话媒体通道(视频+视频)信息 TODO
 */
typedef struct tagCALL_S_MEDIA_STREAM_INFO
{
    TUP_UINT32 uiCt;                                    /**< 会话级带宽 ct */
    TUP_CHAR szAudioCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /**< 会话协商出的所支持的音频编解码列表 "G722,PCMA,PCMU,G729,iLBC,telephone-event,red"*/
    TUP_CHAR szVideoCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /**< 会话协商出的所支持的视频编解码列表 预留*/
}CALL_S_MEDIA_STREAM_INFO, *CALL_S_MEDIA_STREAM_INFO_PTR;


/**
* 会话信息 TODO
*/
typedef struct tagCALL_S_STREAM_INFO
{
    CALL_S_MEDIA_STREAM_INFO stMediaStreamInfo;         /**< 会话级信息*/
    CALL_S_AUDIO_STREAM_INFO stAudioStreamInfo;         /**< 音频流信息*/
    CALL_S_VIDEO_STREAM_INFO stVideoStreamInfo;         /**< 视频流信息*/
    CALL_S_VIDEO_STREAM_INFO stDataStreamInfo;          /**< 辅流信息*/
    TUP_BOOL bIsIn;                                     /**< 标识该路通话是否为呼入 */
    TUP_BOOL bIsEndCall;                                /**< 标识是否为结束上报 */
    TUP_CHAR acLocalIP[CALL_D_IP_LENGTH];               /**< 本端IP*/
    TUP_CHAR acRemoteNum[CALL_D_MAX_LENGTH_NUM];        /**< 远端号码*/
    TUP_CHAR acLocalNum[CALL_D_MAX_LENGTH_NUM];         /**< 本端号码*/
} CALL_S_STREAM_INFO, *CALL_S_STREAM_INFO_PTR;


/**
* 共享线呼叫信息
*/
typedef struct tagCALL_S_SCA_CALL_INFO
{
    TUP_BOOL bIsShareLine;                              /**< 是否共享线 */
    TUP_UINT32 ulSCALineID;                             /**< 共享线线路ID */
    TUP_UINT32 ulBossLineID;                            /**< 共享线经理线路ID */
    TUP_CHAR acBossNum[CALL_D_MAX_LENGTH_NUM];          /**< 共享线经理号码 */
} CALL_S_SCA_CALL_INFO;


/**
* 会议信息
*/
typedef struct tagCALL_S_CONF_INFO
{
    TUP_UINT32 ulConfID;                                /**< 会议控制块ID  */               
    CALL_E_SERVERCONF_TYPE eConfType;                   /**< 服务器会场类型 */
    TUP_UINT32 ulCallID;                                /**< 呼叫控制块ID */  
    TUP_UINT32 ulSipAccountID;                          /**< 用户账号ID  */
    
	/** 远端用户信息 */
    TUP_INT8 acUserNumber[CALL_D_MAX_LENGTH_NUM];       /**< TODO 用户号码 */
    TUP_INT8 aszRemoteDisplayName[CALL_D_MAX_LENGTH_NUM ]; /**< TODO 显示昵称 */
    
    /*为匹配沙特ATS服务器局内号码显示，解析PAI中的第二个URI（默认为TEL） */
    TUP_INT8 aszRemoteUserIDTel[CALL_D_MAX_LENGTH_NUM]; /**< TODO 用户号码 */
	TUP_INT8 aszRemoteDisplayNameTel[CALL_D_MAX_LENGTH_NUM ]; /**< TODO 显示昵称 */
	
    TUP_INT8 acGroupUri[CALL_D_MAX_LENGTH_NUM];         /**< 群组URI */
    TUP_INT8 acConfIndex[CALL_D_MAX_LENGTH_NUM];        /**< 会议索引 */
    TUP_UINT32 ulSvrAutoAnswer;                         /**< 服务器是否指示自动接听 */
    TUP_UINT32 ulSvrAutoAnswerTime;
    CALL_S_SCA_CALL_INFO stScaCallInfo;                 /**< 经理秘书信息，用于在会议来电的时候上报 */
    CALL_E_CONF_MODE eConfMode;                         /**< 会议模式:融合会议、UC会议 */
    CALL_E_CALL_TYPE eCallType;                         /**< 呼叫类型:音频、视频 */
} CALL_S_CONF_INFO;


/**
 * 会场创建结果
 */
typedef struct tagCALL_S_CONF_CREATE_RESULT
{
    TUP_UINT32 ulConfID;                                /**< 会议控制块ID */
    TUP_UINT32 ulResult;                                /**< 创会结果 */
    CALL_E_SERVERCONF_TYPE eConfType;                   /**< 服务器会场类型 */
    TUP_CHAR acPasscode[CALL_D_PASSCODE_LENGTH];        /**< 会议接入码 */
} CALL_S_CONF_CREATE_RESULT;


/**
 * 数据会议入会相关参数
 */
typedef struct tagCALL_S_DATACONF_PARAM
{
    TUP_UINT32          ulConfID;                                   /**< 会议本地控制id*/
    TUP_UINT32          ulCallID;                                   /**< 对应的呼叫ID */
    CALL_E_CONF_ROLE    enRole;                                     /**< 本地用户会议中角色*/
    TUP_CHAR            acDataConfID[CALL_D_DATACONF_PARAM_LENGTH]; /**< 服务器会场id */
    TUP_CHAR            acAuthKey[CALL_D_DATACONF_PARAM_LENGTH];    /**< 会场鉴权码 */
    TUP_CHAR            acPassCode[CALL_D_MAX_LENGTH_NUM];          /**< 会议接入码 */
    TUP_CHAR            acCmAddr[CALL_D_DATACONF_CMADDR_LENGTH];    /**< 网管地址及端口*/
    TUP_CHAR            acGroupUri[CALL_D_MAX_LENGTH_NUM];          /**< 群组URI */    
    TUP_CHAR            acExtConfType[CALL_D_CONF_TYPE_MAX_LEN];    /**< 会议类型, 最大长度20 */
    TUP_CHAR            acCharman[CALL_D_DATACONF_PARAM_LENGTH];    /**< 主持人UC号码*/
    TUP_CHAR            bP2PDataConf;                               /**< 是否点对点数据会议 */
} CALL_S_DATACONF_PARAM;


/**
 * 与会者信息
 */
typedef struct tagCALL_S_CONF_MEMBER
{
    TUP_CHAR acAttendeeNumber[CALL_D_MAX_LENGTH_NUM];               /**< 号码 */
    TUP_CHAR acAttendeeFullNumber[CALL_D_MAX_LENGTH_NUM];           /**< 与会者长 号码 */
    CALL_E_CONF_ROLE enRole;                                        /**< 角色 */
    CALL_E_CONF_ATTENDEE_STATE enState;                             /**< 状态 */
    TUP_UINT32 ulRight;                                             /**< 发言权  1有  0无  */
    TUP_UINT32 ulAttendeeID;                                        /**< 与会者ID , 用于指明使用哪个会议 */
    TUP_CHAR acLinkDesktop[CALL_D_CONF_LINK_NUM_LENGTH];            /**< USM下，联动PC号码 */
    TUP_CHAR acLinkIPPhone[CALL_D_CONF_LINK_NUM_LENGTH];            /**< USM下，联动话机号码 */
} CALL_S_CONF_MEMBER;


/**
 * 发言人信息 
 */
typedef struct tagCALL_S_CONF_SPEAKER
{
    TUP_CHAR acFirstSpeakMem[CALL_D_MAX_LENGTH_NUM];        /**< TODO 第一发言人号码 */
    TUP_CHAR acSecondSpeakMem[CALL_D_MAX_LENGTH_NUM];       /**< TODO 第二发言人号码 */
} CALL_S_CONF_SPEAKER;


/**
 * 视频修改结果 
 */
typedef struct tagCALL_S_MODIFY_VIDEO_RESULT
{
    TUP_UINT32 ulCallID;                          /**< 呼叫ID */
    TUP_UINT32 ulResult;                          /**< 结果 */
    TUP_BOOL  bIsVideo;                           /**< 是否视频 */
    TUP_UINT32 ulOrientType;                      /**< TODO */
    CALL_E_VIDEO_MOD_RESULT enVideoModRes;        /**< 视频变更动作 */
}CALL_S_MODIFY_VIDEO_RESULT;


/**
 * 视频窗口信息
 */
typedef struct tagCALL_S_VIDEOWND_INFO
{
    TUP_UINT32 ulVideoWndType;                      /**< 视频窗口类型:CALL_E_VIDEOWND_TYPE */
    TUP_INT32 ucCoordinate[CALL_E_COORDINATE_BUTT]; /**< 坐标信息 X1,Y1,w,h,Z*/
    TUP_UPTR ulRender;                              /**< 窗口句柄*/
    TUP_INT32 ulIndex;                              /**< 窗口序号*/
    TUP_UINT32 ulSessionID;                         /**< 本地预览session值*/
    TUP_UINT32 ulRefCount;                          /**< 使用引用计数*/
    TUP_UINT32 ulDisplayType;                       /**< 显示模式(8950用枚举类型CALL_E_VIDEOWND_DISPLAY_TYPE，其他产品用直接赋值 0:拉伸模式 1:(不拉伸)黑边模式 2:(不拉伸)裁剪模式)*/
    TUP_CHAR  acStartImage[CALL_D_MAX_LENGTH_NUM];  /**< 视频显示初始图像，必须为jpeg图像，且长宽都是8的倍数*/
} CALL_S_VIDEOWND_INFO, CALL_S_VIDEOCONFWND_INFO;


/**
 * UPORTAL TOKEN 刷新信息，硬终端使用
 */
typedef struct tagCALL_S_UPORTAL_TOKEN_REFRESH_INFO
{
    TUP_CHAR acToken[CALL_D_MAX_TOKEN_LENGTH];          /**< token值 */
    TUP_CHAR acEabServer[CALL_D_MAX_SERVER_LENGTH];     /**< 企业通讯录server */
    TUP_CHAR acGroupServer[CALL_D_MAX_SERVER_LENGTH];   /**< 头像服务器 */
    TUP_CHAR acUsername[CALL_D_MAX_USERNAME_LENGTH];    /**< 用户名 */
    TUP_UINT32 ulExpire;                                /**< 老化时间 */
}CALL_S_UPORTAL_TOKEN_REFRESH_INFO;


/**
 * 视频窗口控制类型
 */
typedef enum tagCALL_E_VIDEOWND_CTRL_TYPE
{
    CALL_E_VIDEOWND_MOVE,           /**< 窗口移动包括Z序改变隐藏通过改变Z序 */
    CALL_E_VIDEOWND_CLOSE,          /**< 窗口关闭  */
    CALL_E_VIDEOWND_ZOOM,           /**< 窗口缩放  */
    CALL_E_VIDEOWND_DISPLAYTYPE,    /**< 显示模式  */
    CALL_E_VIDEOWND_CTRL_BUTT
} CALL_E_VIDEOWND_CTRL_TYPE;


/**
 * 配置大类
 */
typedef enum tagCALL_E_CFG_MAJOR_TYPE
{
    CALL_E_CFG_CALLENV = 1,     /**< 环境变量 */
    CALL_E_CFG_SERVER,          /**< 服务器地址 */
    CALL_E_CFG_NET,             /**< 本地网络接口地址 */
    CALL_E_CFG_USERAGENT,       /**< 用户代理 */
    CALL_E_CFG_SERVRIGHT,       /**< 业务权限 */
    CALL_E_CFG_DSCP,            /**< DSCP */    
    CALL_E_CFG_SIP,             /**< SIP信令配置 */
    CALL_E_CFG_ACCOUNT,         /**< 账号 */
    CALL_E_CFG_COMPATIBLE_PARAM,/**< 账号 */
    CALL_E_CFG_CONF,            /**< 会议相关设置*/
    CALL_E_CFG_MEDIA,           /**< 媒体全局配置*/
    CALL_E_CFG_AUDIO,           /**< 音频配置*/
    CALL_E_CFG_VIDEO,           /**< 视频配置 & 辅流配置*/
    CALL_E_CFG_BFCP,            /**< 辅流BFCP配置*/
    CALL_E_CFG_MOBILE_VOICEMAIL,/**< 移动语音邮箱权限*/
    CALL_E_CFG_BUTT
}CALL_E_CFG_MAJOR_TYPE;


/**
 * 配置项对应的数据类型
 */
typedef enum tagCALL_E_CFG_DATA_TYPE
{
    CALL_E_CFG_DATA_TYPE_INT = 0x01,       /**< 整形 */
    CALL_E_CFG_DATA_TYPE_STRING = 0x02,    /**< 字符串 */         
    CALL_E_CFG_DATA_TYPE_STRUCTURE = 0x04, /**< 结构 */    
    CALL_E_CFG_DATA_TYPE_BOOL = 0x08,      /**< BOOL */  
    CALL_E_CFG_DATA_TYPE_PTR = 0x10,       /**< 指针 */  
    CALL_E_CFG_DATA_TYPE_BUTT,

} CALL_E_CFG_DATA_TYPE;


#define CFG_ID_DEF(major,data_type,id,index)    ((major)<<24|((data_type) << 16)|(id) <<8|(index))

#define GET_CFG_DATA_TYPE(cfgid)            ((cfgid>>16)&0x000000FF)
#define GET_CFG_MAJOR_TYPE(cfgid)           ((cfgid>>24)&0x000000FF)
#define GET_CFG_ID(cfgid)                   ((cfgid>>8)&0x000000FF)
#define GET_CFG_INDEX(cfgid)                ((cfgid)&0x000000FF)


/**
 * 配置项说明
 * <br>1.CALL_D_CFG_NET_NETADDRESS 这个设置项需要放到最后，由于这个项会去创建socket，
 * <br>建议第一次调用后，除非后续网络地址变更，否则不再调用。
 * <br>2.使用默认值的选项，最好不调用，减少运行开销。
 * <br>3.调用配置接口的顺序，一般是把sip相关的配置项放到后面，相同的功能项放一起。
 * <br>4.软件要正常运行，需要配置的选项
 * <br>  CALL_D_CFG_SERVER_REG_PRIMARY  设置sip注册服务器地址
 * <br>  CALL_D_CFG_ENV_USEAGENT        软件对应的useragent，例如"Huawei TE Desktop"
 * <br>  CALL_D_CFG_ENV_PRODUCT_TYPE    产品类型
 * <br>  CALL_D_CFG_NET_NETADDRESS      本地网络地址
 * <br>  CALL_D_CFG_MEDIA_SDP_CT        TE产品必须设置
 * <br>  CALL_D_CFG_COMPATIBLE_PARAM_OUTGOINGCODE       华为UC必须设置
 * <br>  CALL_D_CFG_COMPATIBLE_PARAM_SELFNUM            华为UC必须设置
 * <br>5.CALL_D_CFG_SIP_USE_VPP_CALLID  使用vpp的callid，会带上网络地址，有一些中间网元会把网络地址替换掉，这时候可以考虑把这个选项设为false
 * <br>6.CALL_D_CFG_SIP_SESSIONTIMER_LENIENT 其他厂商的产品，会话心跳的协议没有严格遵守，为了能够对接起来，可以设为ture
 * <br>7.CALL_D_CFG_SIP_STRICT_CHECK_CSEQ 使用UDP方式时，有时候会收到的包是乱序的，为了是vpp能够兼容，可以设为false，不严格检查
 * <br>8.CALL_D_CFG_SIP_TLS_VERSION 这个必须在CALL_D_CFG_NET_NETADDRESS前
*/
#define CALL_D_CFG_NOTE "call config note"


#define CALL_D_CFG_SERVER_REG_PRIMARY     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x01,0) /**< 呼叫注册主服务器，对应结构体为CALL_S_SERVER_CFG，默认值为空。@see CALL_D_CFG_NOTE*/
#define CALL_D_CFG_SERVER_REG_BACKUP1     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x02,0) /**< 呼叫注册备份服务器1，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_REG_BACKUP2     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x03,0) /**< 呼叫注册备份服务器3，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_REG_BACKUP3     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x04,0) /**< 呼叫注册备份服务器3，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_REG_LOCAL       CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x05,0) /**< 呼叫注册本地服务器，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_PROXY_PRIMARY   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x11,0) /**< 呼叫注册主代理服务器，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_PROXY_BACKUP1   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x12,0) /**< 呼叫注册备份代理服务器1，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/   
#define CALL_D_CFG_SERVER_PROXY_BACKUP2   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x13,0) /**< 呼叫注册备份代理服务器2，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/    
#define CALL_D_CFG_SERVER_PROXY_BACKUP3   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x14,0) /**< 呼叫注册备份代理服务器3，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/ 
#define CALL_D_CFG_SERVER_PROXY_LOCAL     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x15,0) /**< 呼叫注册本地代理服务器，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_UMS_PRIMARY     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x21,0) /**< UMS主服务器，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/
#define CALL_D_CFG_SERVER_UMS_BACKUP      CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x22,0) /**< UMS备份服务器，对应结构体为CALL_S_SERVER_CFG，默认值为空。*/

#define CALL_D_CFG_ENV_SOLUTION                  CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x01,0) /**< 解决方案(组网)环境，对应枚举为CALL_E_NET_ENVIRONMENT，默认值为CALL_E_NET_UC1X。*/ 
#define CALL_D_CFG_ENV_DISASTER_RECOVERY_MODE    CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x02,0) /**< 容灾模式，对应枚举为CALL_E_REG_FAILOVER_MODE，默认值为CALL_E_REG_FAILOVER_MODE_REGMASTER。*/ 
#define CALL_D_CFG_ENV_PRODUCT_TYPE              CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x03,0) /**< 产品类型，对应枚举为CALL_E_PRODUCT_TYPE，默认值为CALL_E_PRODUCT_TYPE_PHONE。@see CALL_D_CFG_NOTE*/
#define CALL_D_CFG_ENV_USEAGENT                  CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_STRING,0x04,0)  /**< 用户代理，字符串，默认为空。@see CALL_D_CFG_NOTE*/  

#define CALL_D_CFG_SERVRIGHT_DND        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_DONOTDISTURB,0) /**< 业务权限配置:DND，对应结构体为CALL_S_SERVICE_RIGHT_CFG，默认值为空。*/
#define CALL_D_CFG_SERVRIGHT_CFU        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL,0) /**< 业务权限配置:CFU，对应结构体为CALL_S_SERVICE_RIGHT_CFG，默认值为空。*/ 
#define CALL_D_CFG_SERVRIGHT_CFB        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY,0) /**< 业务权限配置:CFB，对应结构体为CALL_S_SERVICE_RIGHT_CFG，默认值为空。*/
#define CALL_D_CFG_SERVRIGHT_CFNR       CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_OFFLINE,0) /**< 业务权限配置:CFNR，对应结构体为CALL_S_SERVICE_RIGHT_CFG，默认值为空。*/
#define CALL_D_CFG_SERVRIGHT_CFNA       CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY,0) /**< 业务权限配置:CFNA，对应结构体为CALL_S_SERVICE_RIGHT_CFG，默认值为空。*/
#define CALL_D_CFG_SERVRIGHT_CALLWAIT   CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALL_WAIT,0) /**< 业务权限配置:CALLWAIT，对应结构体为CALL_S_SERVICE_RIGHT_CFG，默认值为空。*/

#define CALL_D_CFG_DSCP_ENABLE   CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_BOOL,0x1,0)  /**< DSCP使能配置，取值true/false，默认值为false。*/
#define CALL_D_CFG_DSCP_AUDIO    CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x2,0)   /**< 音频通道DSCP配置，取值[0,64)，默认值为0。*/
#define CALL_D_CFG_DSCP_VIDEO    CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x3,0)   /**< 视频通道DSCP配置，取值[0,64)，默认值为0。*/
#define CALL_D_CFG_DSCP_SIP      CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x4,0)   /**< SIP信令通道DSCP配置，取值[0,64)，默认值为0。*/
#define CALL_D_CFG_DSCP_DATA     CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x5,0)   /**< 数据通道DSCP配置，取值[0,64)，默认值为0。*/

#define CALL_E_CFG_CONF_ENABLE_INTERCONF            CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_BOOL, 0x1, 0)   /**< 会议配置:TODO。*/
#define CALL_E_CFG_CONF_MS_ADDR                     CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_STRING, 0x4, 0) /**< 会议配置:MS地址，字符串，默认为空。*/ 
#define CALL_E_CFG_CONF_APPAGENT_ADDR               CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_STRING, 0x5, 0) /**< 会议配置:TODO，字符串，默认为空。*/ 
#define CALL_D_CFG_COMPATIBLE_PARAM_SELFNUM         CFG_ID_DEF(CALL_E_CFG_COMPATIBLE_PARAM,CALL_E_CFG_DATA_TYPE_STRING,0x2,0)   /**< 会议配置:TODO 本端号码，字符串，默认为空。*/ 
#define CALL_D_CFG_COMPATIBLE_PARAM_OUTGOINGCODE    CFG_ID_DEF(CALL_E_CFG_COMPATIBLE_PARAM,CALL_E_CFG_DATA_TYPE_STRING,0x3,0)   /**< 会议配置:TODO OUTGOING码，字符串，默认为空。*/ 

#define CALL_D_CFG_SIP_PORT                 CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x1, 0)  /**< SIP端口，取值[TODO]，默认值为5060。*/
#define CALL_D_CFG_SIP_REGIST_TIMEOUT       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x2, 0)  /**< 注册心跳超时时间，取值[TODO]，默认值为300s。*/
#define CALL_D_CFG_SIP_SUBSCRIBE_TIMEOUT    CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x3, 0)  /**< 订阅心跳超时时间，取值[TODO]，默认值为300s。*/
#define CALL_D_CFG_SIP_REREGISTER_TIMEOUT   CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x4, 0)  /**< 注册失败后，重新注册的超时时间，取值[TODO]，默认值为150s。*/
#define CALL_D_CFG_SIP_SWITCHCALL_TIMEOUT   CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x5, 0)  /**< 多注册Invite切换时长，取值[TODO]，默认值为0。*/
#define CALL_D_CFG_SIP_SESSIONTIMER_ENABLE  CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x6, 0)  /**< 会话心跳开关，默认关闭。*/
#define CALL_D_CFG_SIP_SESSIONTIME          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x7, 0)  /**< 会话心跳，取值[TODO]，默认值为0s。*/
#define CALL_D_CFG_SIP_REJECT_TYPE          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x8, 0)  /**< 拒接呼叫回复信令，对应枚举为CALL_E_REJECTCALL_TYPE，默认值为CALL_D_REJECTTYPE_486。*/ 
#define CALL_D_CFG_SIP_TRANS_MODE           CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x9, 0)  /**< 信令传输模式，对应枚举为CALL_E_TRANSPORTMODE，默认值为CALL_E_TRANSPORTMODE_UDP。*/ 
#define CALL_D_CFG_SIP_TLS_ROOTCERTPATH     CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_STRING, 0xA, 0)  /**< TLS根证书路径，字符串，默认为空。*/
#define CALL_D_CFG_SIP_SUPPORT_100REL       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0xB, 0)  /**< 支持100Rel，默认关闭。*/
#define CALL_D_CFG_SIP_ENABLE_REG_SUB       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0xC, 0)  /**< 是否开启订阅注册，默认关闭。*/
#define CALL_D_CFG_SIP_ENABLE_CORPORATE_DIRECTORY CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL, 0xD, 0) /**< 是否开启订阅网络地址本（终端向智真SC订阅）,默认关闭。*/
#define CALL_D_CFG_SIP_ENABLE_PRESENCE_TE   CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0xE, 0)  /**< 是否开启智真在线状态订阅（终端向智真SC订阅）,默认关闭。*/
#define CALL_D_CFG_SIP_REJECT_VIDEO_TYPE    CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0xF, 0)  /**< 拒接视频回复信令，对应枚举为CALL_E_REJECTCALL_TYPE，默认值为CALL_D_REJECTVIDEOTYPE_200。*/
#define CALL_D_CFG_SIP_USE_VPP_CALLID       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x10, 0) /**< 是否默认使用vpp生成的callid，默认是。*/
#define CALL_D_CFG_SIP_SOCKET_USE_All_ZERO_IP  CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,0x11, 0) /**< 是否使用全零IP创建socket，默认否。*/
#define CALL_D_CFG_SIP_SESSION_UPDATEMODE   CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x12, 0) /**< 会话心跳的refresh模式，对应枚举为CALL_E_SESSION_REFRESHER，默认值为CALL_E_REFRESHER_UAC。*/
#define CALL_D_CFG_SIP_SESSIONTIMER_LENIENT CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x13, 0) /**< session timer是否兼容非标准方式，默认否。*/
#define CALL_D_CFG_SIP_SUB_AUTH_TYPE        CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x14, 0) /**< 是否订阅认证方式，默认不订阅。*/
#define CALL_D_CFG_SIP_STRICT_CHECK_CSEQ    CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x15, 0) /**< 是否严格检查CSEQ，默认严格检测。*/
#define CALL_D_CFG_SIP_ANONYMOUSNUM         CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_STRING, 0x16, 0) /**< 匿名呼叫号码，字符串，默认为空。*/ 
#define CALL_D_CFG_SIP_TLS_NOSTANDARD       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x17, 0) /**< 是否添加TLS非标字段,false为不添加,true为添加(默认为false)。*/
#define CALL_D_CFG_SIP_REFER_AUDVIE_MODE    CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x18, 0) /**< 收到REFER后发送invite带视频/音频的模式，0表示根据被转移通话选择，1表示根据是否协商过视频选择。*/
#define CALL_D_CFG_SIP_ALLOWMESSAGE         CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x19, 0) /**< 是否支持MESSAGE方法，默认是。*/
#define CALL_D_CFG_SIP_ALLOWPRACK           CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x20, 0) /**< 是否支持PRACK方法，默认是。*/
#define CALL_D_CFG_SIP_ALLOWUPDATE          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x21, 0) /**< 是否支持UPDATE方法，默认是。*/
#define CALL_D_CFG_SIP_ALLOWSUBSCRIBE       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x22, 0) /**< 是否支持SUBSCRIBE方法，默认是。*/
#define CALL_D_CFG_SIP_ALLOWINFO            CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x23, 0) /**< 是否支持INFO方法，默认是。*/
#define CALL_D_CFG_SIP_ALLOWREFER           CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x24, 0) /**< 是否支持REFER方法，默认是。*/
#define CALL_D_CFG_SIP_ALLOWNOTIFY          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x25, 0) /**< 是否支持NOTIFY方法，默认是。*/
#define CALL_D_CFG_SIP_SUB_SERVICE_RIGHT    CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x26, 0) /**< 订阅 as-feature-event，默认关闭。*/

#define CALL_D_CFG_SIP_TLS_VERSION          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x27, 0) /**< TLS支持的版本，允许设置tls1.0 tls1.1 tls1.2的任意组合，
																												* <br> 使用CALL_D_TLSVERSION_V1_0、CALL_D_TLSVERSION_V1_1、CALL_D_TLSVERSION_V1_2，
																												* <br> 大于等于两个使用‘|’操作符，默认是 tls1.1 和 tls1.2 */

#define CALL_D_CFG_SIP_REFER_AUTO_BYE       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x28, 0)/**< 收到refer后自动bye掉第一路,默认不开启 */

#define CALL_D_CFG_MEDIA_SRTPMKI            CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x1,0)  /**< 全局媒体配置:SRTP是否打开mki方式，默认否 */
#define CALL_D_CFG_MEDIA_SRTP_MODE          CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x2,0)  /**< 全局媒体配置:SRTP模式，对应枚举为CALL_E_SRTP_MODE，默认值为CALL_E_SRTP_MODE_DISABLE。*/ 
#define CALL_D_CFG_MEDIA_MERGE_SRTP_RTP     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x3,0)  /**< 全局媒体配置:是否合并SRTP和RTP的m行，默认否 */
#define CALL_D_CFG_MEDIA_RTP_PRIORITY       CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x4,0)  /**< 全局媒体配置:媒体行中rtp、srtp优先顺序，对应枚举为SIPC_TUP_SRTP_PRI_E，默认值为SIPC_TUP_SRTP_PRI。*/ 
#define CALL_D_CFG_MEDIA_CRYPTOSUITE        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRING,    0x5,0)  /**< 全局媒体配置:SRTP加密套，字符串，默认TODO。*/ 
#define CALL_D_CFG_MEDIA_SDP_OLINE_INFO     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x6,0)  /**< 全局媒体配置:设置SDP，对应结构体CALL_S_SDP_OLINE_INFO，默认{“huawei”,"23293","1"} */
#define CALL_D_CFG_MEDIA_MOS_TIME           CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x7,0)  /**< 全局媒体配置:MOS值上报间隔时间，单位:秒钟，取值[TODO]，默认5秒 */
#define CALL_D_CFG_MEDIA_MOS_THRESHOLD      CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x8,0)  /**< 全局媒体配置:MOS值上报阀值，取值[0，5]，默认3.6 */
#define CALL_D_CFG_MEDIA_MOS_SENDINFOSWITCH CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x9,0)  /**< 全局媒体配置:MOS值上报通过INFOSIP服务器开关，默认否 */
#define CALL_D_CFG_MEDIA_SENDONLYFREE       CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xA,0)  /**< 全局媒体配置:媒体方向为sendonly，是否释放资源，软终端默认否，硬终端默认是 */
#define CALL_D_CFG_MEDIA_USEPACKMODE        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xB,0)  /**< 全局媒体配置:H264视频协商时，是否判断打包模式，软终端默认是，硬终端默认否 */
#define CALL_D_CFG_MEDIA_RECORDFILE_INFO    CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0xC,0)  /**< 全局媒体配置:设置文件附加信息，对应结构体CALL_S_RECORDFILE_INFO，默认{0,100,8000,0} */
#define CALL_D_CFG_MEDIA_SETQOS_INFO        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0xD,0)  /**< 全局媒体配置:设置qos上报，对应结构体CALL_S_SETQOS_INFO，默认空 */
#define CALL_D_CFG_MEDIA_ENABLE_DATA        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xD,0)  /**< 全局媒体配置:辅流开关，默认否 */
#define CALL_D_CFG_MEDIA_FORCE_IDR_INFO     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xE,0)  /**< 全局媒体配置:是否强制打开info idr请求的收发，默认否 */
#define CALL_D_CFG_MEDIA_SDP_CT             CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0xF,0)  /**< 全局媒体配置:sdp CT 张震 TODO  */
#define CALL_D_CFG_MEDIA_LOOSE_PORT_NEGO    CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x10,0) /**< 全局媒体配置:是否支持loose-port-nego（非严格端口协商），默认否 */
#define CALL_D_CFG_MEDIA_WND_PARAM          CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x11, 0)/**< 全局媒体配置:视频显示窗口属性（拉伸/镜像/旋转），对应结构体CALL_S_VIDEO_RENDER_INFO，默认{1,1,1} */
#define CALL_D_CFG_MEDIA_IFRAME_METHOD      CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x12,0) /**< 全局媒体配置:I帧控制，TODO 默认否 */
#define CALL_D_CFG_MEDIA_FLUID_CONTROL      CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x13,0) /**< 全局媒体配置:流控，TODO 默认否 */
#define CALL_D_CFG_MEDIA_DEL_PORT0_LINE     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x14,0) /**< 全局媒体配置:删除无效媒体行，默认否 */
#define CALL_D_CFG_VIDEOSESSION_PREVIEWTYPE CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x15, 0)/**< 全局媒体配置:视频预览类型，0：不带任何预览，设置为2则为视频预览，默认为0， */
#define CALL_D_CFG_MEDIA_ENABLE_BFCP        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x17,0) /**< 全局媒体配置:BFCP开关，需在CALL_D_CFG_NET_NETADDRESS之前配置，默认否 */

#define CALL_D_CFG_AUDIO_CODEC              CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRING,     0x1, 0) /**< 音频配置:音频编解码优先级，取值[TODO]，默认值TODO。*/
#define CALL_D_CFG_AUDIO_ANR                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x2, 0) /**< 音频配置:噪音抑制，取值[TODO]，默认值TODO。*/
#define CALL_D_CFG_AUDIO_AEC                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x3, 0) /**< 音频配置:回声消除，取值[TODO]，默认值TODO。*/
#define CALL_D_CFG_AUDIO_AGC                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 0) /**< 音频配置:自动增益，取值[TODO]，默认值TODO。*/
#define CALL_D_CFG_AUDIO_DTMF_MODE          CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x5, 0) /**< 音频配置:DTMF模式，对应枚举为CALL_E_DTMF_MODE，默认值为CALL_E_DTMF_MODE_RFC2833。*/ 
#define CALL_D_CFG_AUDIO_DTMF_PT            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x6, 0) /**< 音频配置:DTMF PT值，取值[0,127]，默认值97。*/
#define CALL_D_CFG_AUDIO_ILBCMODE           CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x7, 0) /**< 音频配置:ILBC打包时长，取值20 或 30，默认值20 */    
#define CALL_D_CFG_AUDIO_PACKETTIME         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x8, 0) /**< 音频配置:打包时长,除ILBC外有效，取值20、30、40，默认值20 */
#define CALL_D_CFG_AUDIO_NETATELEVEL        CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x9, 0) /**< 音频配置:是否打开NET-ATE，默认是。*/
#define CALL_D_CFG_AUDIO_VADFLAG            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_BOOL,       0xA, 0) /**< 音频配置:Vad启用标志位，0关闭 1开启，默认关闭。*/
#define CALL_D_CFG_AUDIO_CLOCKRATE          CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xB, 0) /**< 音频配置:采样频率，根据编解码不同，采用业界通用的默认值 */
#define CALL_D_CFG_AUDIO_CHANNELS           CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 0) /**< 音频配置:声道个数，取值[TODO]，默认值1。*/
#define CALL_D_CFG_AUDIO_BITS               CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xD, 0) /**< 音频配置:样本位数，根据编解码不同，采用业界通用的默认值 */
#define CALL_D_CFG_AUDIO_PORT_RANGE         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xE, 0) /**< 音频配置:音频端口范围，对应结构体CALL_S_RTP_PORT_RANGE，默认{10500,10519} */
#define CALL_D_CFG_AUDIO_PLAYFILE_ADDITIONINFO         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF, 0) /**< 音频配置:播放音频文件附加信息，对应结构体CALL_S_AUDIO_PLAYFILE_ADDITIONINFO，默认{CALL_FILE_FORMAT_WAV} */
#define CALL_D_CFG_AUDIO_RFC2198            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x10, 0) /**< 音频配置:音频冗余设置，对应结构体CALL_S_AUDIO_RFC2198，默认为空 */
#define CALL_D_CFG_AUDIO_BAND_LIMIT         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x11, 0) /**< 音频配置:低带宽设置，对应结构体CALL_S_AUDIO_BAND_LIMIT，默认为空 */

#define CALL_D_CFG_VIDEO_LEVEL              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x1, 0) /**< 视频配置:解码级别以及具体限制，对应结构体CALL_S_VIDEO_LEVEL，默认{0,0,0,0} */
#define CALL_D_CFG_DATA_LEVEL               CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x1, 1) /**< 数据配置:解码级别以及具体限制，对应结构体CALL_S_VIDEO_LEVEL，默认{0,0,0,0} */
#define CALL_D_CFG_VIDEO_DEFAULT_IMAGE      CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x2, 0) /**< 视频配置:无视频时使用的图片，图片必须是bmp格式的，默认空*/
#define CALL_D_CFG_VIDEO_ARQ                CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x3, 0) /**< 视频配置:是否开启丢包重传，0关闭 1开启，默认关闭。*/
#define CALL_D_CFG_DATA_ARQ                 CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x3, 1) /**< 数据配置:是否开启丢包重传，0关闭 1开启，默认关闭。*/
#define CALL_D_CFG_VIDEO_TACTIC             CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 0) /**< 视频配置:策略 0 图像质量优先  1 流畅优先，默认图像质量优先。*/
#define CALL_D_CFG_DATA_TACTIC              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 1) /**< 数据配置:策略 0 图像质量优先  1 流畅优先，默认图像质量优先。*/
#define CALL_D_CFG_VIDEO_CODEC              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x5, 0) /**< 视频配置:编解码优先级，当前仅支持H263&H264，TODO */
#define CALL_D_CFG_DATA_CODEC               CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x5, 1) /**< 数据配置:编解码优先级，当前仅支持H263&H264，TODO */
#define CALL_D_CFG_VIDEO_ERRORCORRECTING    CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x6, 0) /**< 视频配置:是否开启错误校验功能，0关闭 1开启，默认关闭。*/
#define CALL_D_CFG_DATA_ERRORCORRECTING     CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x6, 1) /**< 数据配置:是否开启错误校验功能，0关闭 1开启，默认关闭。*/
#define CALL_D_CFG_VIDEO_FRAMESIZE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 0) /**< 视频配置:分辨率，对应结构体CALL_S_VIDEO_FRAMESIZE，默认{11,0,11} TODO*/
#define CALL_D_CFG_DATA_FRAMESIZE           CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 1) /**< 数据配置:分辨率，对应结构体CALL_S_VIDEO_FRAMESIZE，默认{11,0,11} TODO*/
#define CALL_D_CFG_VIDEO_DATARATE           CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 0) /**< 视频配置:码率，对应结构体CALL_S_VIDEO_DATARATE，默认{4096,0,0,1920} TODO*/
#define CALL_D_CFG_DATA_DATARATE            CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 1) /**< 数据配置:码率，对应结构体CALL_S_VIDEO_DATARATE，默认{4096,0,0,1920} TODO*/
#define CALL_D_CFG_VIDEO_HDACCELERATE       CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x9, 0) /**< 视频配置:硬件加速，对应结构体CALL_S_VIDEO_HDACCELERATE，默认{VOS_TRUE,VOS_TRUE} */
#define CALL_D_CFG_DATA_HDACCELERATE        CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x9, 1) /**< 数据配置:硬件加速，对应结构体CALL_S_VIDEO_HDACCELERATE，默认{VOS_TRUE,VOS_TRUE} */
#define CALL_D_CFG_VIDEO_FRAMERATE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 0) /**< 视频配置:帧率，对应结构体CALL_S_VIDEO_FRAMERATE，默认{30,15} */
#define CALL_D_CFG_DATA_FRAMERATE           CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 1) /**< 数据配置:帧率，对应结构体CALL_S_VIDEO_FRAMERATE，默认{30,15} */
#define CALL_D_CFG_VIDEO_KEYFRAMEINTERVAL   CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 0) /**< 视频配置:关键帧间隔 取值[0,30] 单位为s，默认10。*/
#define CALL_D_CFG_DATA_KEYFRAMEINTERVAL    CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 1) /**< 数据配置:关键帧间隔 取值[0,30] 单位为s，默认10。*/
#define CALL_D_CFG_VIDEO_ARS                CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xD, 0) /**< 视频配置:Ars功能设置，对应结构体CALL_S_VIDEO_ARS，默认{VOS_TRUE,VOS_TRUE,255,VOS_TRUE,VOS_TRUE,VOS_FALSE} */
#define CALL_D_CFG_DATA_ARS                 CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xD, 1) /**< 数据配置:Ars功能设置，对应结构体CALL_S_VIDEO_ARS，默认{VOS_TRUE,VOS_TRUE,255,VOS_TRUE,VOS_TRUE,VOS_FALSE} */
#define CALL_D_CFG_VIDEO_CAPTURE_ROTATION   CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xE, 0) /**< 视频配置:摄像头采集角度，取值[TODO]，默认0。*/
#define CALL_D_CFG_VIDEO_PORT_RANGE         CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF, 0) /**< 视频配置:端口范围，对应结构体CALL_S_RTP_PORT_RANGE，默认{10520,10539} */
#define CALL_D_CFG_DATA_PORT_RANGE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF, 1) /**< 数据配置:端口范围，对应结构体CALL_S_RTP_PORT_RANGE，默认{10540,10569} */
#define CALL_D_CFG_DATA_CAPTURE_FUNC        CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_PTR,        0x10,1) /**< 数据配置:抓屏函数指针，对应函数类型定义TODO，默认空 */
#define CALL_D_CFG_VIDEO_NETLOSSRATE        CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0x11,0) /**< 视频配置:初始网络丢包百分率，用于设置给HME控制fec初始冗余，取值[0,100]，默认20。*/
#define CALL_D_CFG_DATA_NETLOSSRATE         CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0x11,1) /**< 数据配置:初始网络丢包百分率，用于设置给HME控制fec初始冗余，取值[0,100]，默认20。*/
#define CALL_D_CFG_VIDEO_PARAM_TABLE        CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x12,0) /**< 视频配置:配置视频清晰、流畅表格，对应结构体CALL_S_VIDEO_PARAM_TABLE，默认空 */
#define CALL_D_CFG_VIDEO_LOWBANDWIDTH_ABILITY   CFG_ID_DEF(CALL_E_CFG_VIDEO,  CALL_E_CFG_DATA_TYPE_BOOL,  0x13,0) /**< 视频配置:是否拥有低带宽功能，智真业务需要(0:不使能-UC,1:使能-TE,默认为0) */
#define CALL_D_CFG_VIDEO_H264_QUALITY_LEVEL CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x14,0) /**< 视频配置:视频H264 BP/HP配置，对应结构体CALL_S_VIDEO_H264_QUALITY_LEVEL_TABLE，默认TODO */
#define CALL_D_CFG_DATA_H264_QUALITY_LEVEL  CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x14,1) /**< 数据配置:辅流H264 BP/HP配置，对应结构体CALL_S_VIDEO_H264_QUALITY_LEVEL_TABLE，默认TODO */
#define CALL_D_CFG_VIDEO_CT_LEVEL_TABLE     CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x15,0) /**< 视频配置:配置ct(该配置项必须在CALL_D_CFG_MEDIA_SDP_CT之前配置)，对应结构体CALL_S_VIDEO_CT_LEVEL_TABLE，默认TODO */
#define CALL_D_CFG_VIDEO_CAP_ROTATE_CTRL_MODE CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,     0x16,0) /**< 视频配置:摄像头角度控制模式(0:SDP协商模式-UC,1:接口控制模式-TE,默认为0) */
#define CALL_D_CFG_VIDEO_CLARITY_FLUENCY_ENABLE  CFG_ID_DEF(CALL_E_CFG_VIDEO,  CALL_E_CFG_DATA_TYPE_BOOL,  0x17,0)/**< 视频配置:是否使能清晰流畅策略表 智真业务需要(0:不使能-UC,1:使能-TE,默认为0) */

#define CALL_D_CFG_BFCP_PARAM          CFG_ID_DEF(CALL_E_CFG_BFCP, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x1,0) /**< 辅流sdp协商参数，对应结构体CALL_S_BFCP_PARAM，默认{1,1,1} */
#define CALL_D_CFG_BFCP_PORT_RANGE     CFG_ID_DEF(CALL_E_CFG_BFCP, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x2,0) /**< BFCP端口范围(CALL_S_BFCP_PORT_RANGE)需要在设置本地地址前配置，默认{10560} */

#define CALL_D_CFG_NET_NETADDRESS           CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x1, 0) /**< 本地地址：sip使用，在媒体没有单独设置时，则媒体也用这个地址，对应结构体CALL_S_IF_INFO，默认TODO */
#define CALL_D_CFG_AUDIO_NETADDRESS         CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRING,    0x2, 0) /**< 设置音频使用地址，IP地址字符串，默认空 */
#define CALL_D_CFG_VDIEO_NETADDRESS         CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRING,    0x3, 0) /**< 设置视频使用地址，当前暂不支持，IP地址字符串，默认空 */

#define CALL_D_CFG_ACCOUNT_AUTH             CFG_ID_DEF(CALL_E_CFG_ACCOUNT, CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x1, 0)/**< 账号配置，对应结构体CALL_S_SIP_AUTH_CFG，默认空 */


/**移动语音邮箱权限配置*/
#define CALL_D_CFG_MOBILE_VVM_RIGHT         CFG_ID_DEF(CALL_E_CFG_MOBILE_VOICEMAIL, CALL_E_CFG_DATA_TYPE_BOOL, 0x1, 0) /**< 是否支持移动语音邮箱权限，默认否 */


/**
 * 服务器配置
 */
typedef struct tagCALL_S_SERVER_CFG
{
     TUP_CHAR server_address[CALL_D_MAX_URL_LENGTH];   /**< 服务器地址，IP地址字串或域名地址 */
     TUP_UINT32 server_port;                           /**< 服务器端口 */
} CALL_S_SERVER_CFG;


/**
 * 业务权限配置
 */
typedef struct tagCALL_S_SERVICE_RIGHT_CFG
{
    TUP_UINT32   ulRight;                                                  /**< 是否有权限:0 无，1 有 */
    TUP_CHAR     acActiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];         /**< 登记特征码 */
    TUP_CHAR     acDeactiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];       /**< 取消登记特征码*/
}CALL_S_SERVICE_RIGHT_CFG;


/**
 * AAC媒体能力集，暂未使用
 */
typedef struct tagMPROC_S_AAC_CAP_SPECIAL
{
     TUP_INT32     bProfileLevel;                       /**< 是否有　profile-level 值　*/
     TUP_INT32     lProfileLevel;                       /**< profile-level 值　*/
     TUP_UINT32    bMaxBitRate;                         /**< 是否有带宽值 */
     TUP_UINT32    ulMaxBitRate;                        /**< 带宽值:单位: 1bps*/
     TUP_UINT8     bAudioObjectType;                    /**< 是否设置了音频对象类型*/
     TUP_UINT8     ucAudioObjectType;                   /**< 音频对象类型 AAC-LC:2,AAC-LD:23 */
     TUP_UINT8     ucAACFormatType;                     /**< 增加formattype 区分rawdata和latm:1:raw，2:支持latm，3:既支持raw又支持latm*/
     TUP_UINT8     bConfigPresent;                      /**< 音频配置是否带内传送,0为带外传送，1为带内传送*/
     TUP_UINT8     bConfig;                             /**< 是否设置了配置字符串 */
     TUP_UINT8     aucReserve[3];                       /**< 保留位,用于字节对齐*/
     TUP_UINT32    ulConfig;                            /**< 配置字符串的长度 */
     TUP_UINT8     pcMuxConfig[MPROC_D_AAC_CONFIG_LEN]; /**< 配置字符串 */
}MPROC_S_AAC_CAP_SPECIAL, *MPROC_S_AAC_CAP_SPECIAL_PTR;


/**
 * DTMF媒体能力集
 */
typedef struct tagMPROC_S_DTMF_CAP_SPECIAL
{
     TUP_UINT32 ulDTMFTransferMode;      /**< 0带内 or 1带外　*/
}MPROC_S_DTMF_CAP_SPECIAL;


/**
 * TODO，真心看不懂
 */ 
typedef struct tagMPROC_S_FORMAT_CAP
{
    TUP_BOOL   bEnable;                             /**< TUP_TRUE:支持 */
    TUP_UINT32  ulPktLen;                           /**< 打包时长ms */
    TUP_UINT32  ulFrameLen;                         /**< 帧长ms, iLBC mode */
    TUP_UINT32   ulSampleRate;                      /**< 采样率 */
    TUP_UINT8   ucPayLoad;                          /**< 该format对应的pt值 */
    TUP_UINT8   ulBitNum;                           /**< 支持的码率个数 */
    TUP_UINT8   ulBitRate[MPROC_D_AUD_RATE_NUM];    /**< 码率和枚举值对应::AUDIO_E_DECODERATE */
    TUP_UINT8   ulPadding[1];                       /**< 字节对齐 */
    union{
        MPROC_S_AAC_CAP_SPECIAL stAacSpecial;       /**< aac 能力集 */
        MPROC_S_DTMF_CAP_SPECIAL stDTMFSpecial;     /**< DTMF 能力集 */
    }uMedSpecialCap;
}MPROC_S_FORMAT_CAP, *MPROC_S_FORMAT_CAP_PTR;



/**
 * 统一网络地址网络接口信息数据结构
 */
typedef struct tagCALL_S_IF_INFO 
{
    CALL_E_IP_PROTOCOL_TYPE  ulType;                /**< 网络地址类型 */
    union
    {
        TUP_UINT32 ulIPv4;                          /**< IPv4地址 */
        TUP_UINT8  aucIPv6[CALL_D_IP_LENGTH];       /**< IPv6地址，长度16字节 */
    }uAddress;
    union
    {
        TUP_UINT32 ulNetMask;                       /**< IPv4子网掩码 */
        TUP_UINT8  ulPrefixLen;                     /**< IPv6地址前缀长度 */
    }uMask;
    union
    {
        TUP_UINT32 ulIPv4;                          /**< 网关IPv4地址 */
        TUP_UINT8  aucIPv6[CALL_D_IP_LENGTH];       /**< 网关IPv6地址，长度16字节 */
    }uGateWay;
} CALL_S_IF_INFO;


/**
 * 设备信息
 */
typedef struct tagCALL_S_DEVICEINFO
{
    TUP_UINT32 ulIndex;                             /**< 设备对应的index */
    TUP_CHAR   strName[CALL_D_MAX_DISPLAY_NAME];    /**< 设备名称 */
} CALL_S_DEVICEINFO;


/**
 * 视频刷新事件信息
 */
typedef struct tagCALL_S_REFRESH_VIEW
{
    TUP_UINT32 ulCallID;                            /**< 通话ID */
    CALL_E_REFRESHVIEW_MIDEATYPE enMeidaType;       /**< view刷新媒体类型 */
    CALL_E_REFRESHVIEW_EVENT enEvent;               /**< view刷新事件 */
} CALL_S_REFRESH_VIEW;


 
/**
 * 解码成功事件信息
 */
typedef struct tagCALL_S_DECODE_SUCCESS
{
    TUP_UINT32 ulCallID;                            /**< 通话ID */
    CALL_E_DECODE_SUCCESS_MIDEATYPE enMeidaType;    /**< 媒体类型 */
} CALL_S_DECODE_SUCCESS;


/**
 * 视频LEVEL
 */
typedef struct tagCALL_S_VIDEO_LEVEL
{
    TUP_UINT32 ulLevel;         /**< H264的level {10,11,12,13,20,21,22,30,31,32,40,41,42,50,51}  */
    TUP_UINT32 ulMaxMBPS;       /**< H264的max-bmps  0表示使用对应级别的默认值 */
    TUP_UINT32 ulMaxFS;         /**< H264的max-fs    0表示使用对应级别的默认值 */
    TUP_UINT32 ulMaxBR;         /**< H264的max-br    0表示使用对应级别的默认值 */
} CALL_S_VIDEO_LEVEL;


/**
 * SDP O行信息
 */
typedef struct tagCALL_S_SDP_OLINE_INFO
{
    TUP_CHAR acUserName[CALL_D_MAX_LENGTH_NUM];        /**< 用户名          eg. "huawei" */
    TUP_CHAR acSessionId[CALL_D_MAX_LENGTH_NUM];       /**< SessionID       eg. "23293" */
    TUP_CHAR acSessionVersion[CALL_D_MAX_LENGTH_NUM];  /**< Session version eg. "1" */
} CALL_S_SDP_OLINE_INFO;


/**
 * SRTP信息
 */
typedef struct tagCALL_S_SRTP_INFO
{
    TUP_BOOL bMkiMode;                                /**< 是否支持MKI，默认关闭 */
    TUP_CHAR acCryptoSuite[CALL_D_MAX_LENGTH_NUM];    /**< 加密套，TODO */
} CALL_S_SRTP_INFO;


/**
 * 视频码率
 */
typedef struct tagCALL_S_VIDEO_DATARATE
{
    TUP_UINT32 ulDataRate;              /**< 平均码率，单位:bps，取值[MinDataRate, MaxDataRate]，默认值4096 */
    TUP_UINT32 ulMinDataRate;           /**< 最小码率(可选)，单位:bps，取值[10, DataRate]，默认值10  */
    TUP_UINT32 ulMaxDataRate;           /**< 最大码率(可选)，单位:bps，取值[DataRate, 30000]，默认值30000  */
    TUP_UINT32 ulMaxBw;                 /**< 最大带宽，对应SDP的AS字段，单位:kbps，取值[64, 2048]，默认值1920  */
} CALL_S_VIDEO_DATARATE;


/**
 * 视频帧率
 */
typedef struct tagCALL_S_VIDEO_FRAMERATE
{
    TUP_UINT32 uiFrameRate;             /**< 帧率，单位:fps，取值[1, 30]，默认值30  */
    TUP_UINT32 uiMinFrameRate;          /**< 最小帧率，单位:fps，取值[1, FrameRate]，默认值15  */
} CALL_S_VIDEO_FRAMERATE;


/**
 * 视频分辨率
 */
typedef struct tagCALL_S_VIDEO_FRAMESIZE
{
    TUP_UINT32 uiFramesize;             /**< 编码分辨率 */
    TUP_UINT32 uiMinFramesize;          /**< 最小编码分辨率 */
    TUP_UINT32 uiDecodeFrameSize;       /**< 解码最大分辨率 */
} CALL_S_VIDEO_FRAMESIZE;


/**
 * 视频编解码器加速信息
 */
typedef struct tagCALL_S_VIDEO_HDACCELERATE
{
    TUP_UINT32 ulHdEncoder;             /**< 编码器加速 0:非硬件加速 1:硬件加速 */
    TUP_UINT32 ulHdDecoder;             /**< 解码器加速 0:非硬件加速 1:硬件加速 */
} CALL_S_VIDEO_HDACCELERATE;


/**
 * 视频ARS信息
 */
typedef struct tagCALL_S_VIDEO_ARS
{
    TUP_BOOL bArs;                      /**< 是否支持ARS，默认TURE */
    TUP_BOOL bArsCtrlFec;               /**< 是否支持TODO，默认TURE */
    TUP_UINT32 ulMaxFecProFac;          /**< TODO，取值[TODO]，默认值255 */
    TUP_BOOL  bArsCtrlBitRate;          /**< 是否支持TODO，默认TURE */
    TUP_BOOL  bArsCtrlFrameRate;        /**< 是否支持TODO，默认TURE */
    TUP_BOOL  bArsCtrlFrameSize;        /**< 是否支持TODO，默认FALSE */
} CALL_S_VIDEO_ARS;


/**
 * 视频显示窗口属性
 */
typedef struct tagCALL_S_VIDEO_RENDER_INFO
{
    CALL_E_VIDEOWND_TYPE enRenderType;  /**< 窗口类型枚举值 */ 
    TUP_UINT32 ulDisplaytype;           /**< 窗口显示模式 0:拉伸模式 1:(不拉伸)黑边模式 2:(不拉伸)裁剪模式 3:(需保证窗口尺寸 >= 图像尺寸)按原始分辨率显示 */
    TUP_UINT32 ulMirrortype;            /**< 窗口镜像模式 0:不做镜像(默认值) 1:上下镜像(目前未支持) 2:左右镜像 */
}CALL_S_VIDEO_RENDER_INFO;



/**
 * 视频方向
 */
typedef struct tagCALL_S_VIDEO_ORIENT
{
    TUP_UINT32 ulChoice;         /**< 视频横竖屏情况 1：竖屏；2：横屏；3：反向横屏  */ 
    TUP_UINT32 ulPortrait;       /**< 竖屏视频捕获（逆时针旋转）角度 0：0度；1：90度；2：180度；3：270度；*/ 
    TUP_UINT32 ulLandscape;      /**< 横屏视频捕获（逆时针旋转）角度 0：0度；1：90度；2：180度；3：270度；*/ 
    TUP_UINT32 ulSeascape;       /**< 反向横屏视频捕获（逆时针旋转）角度 0：0度；1：90度；2：180度；3：270度；*/ 
}CALL_S_VIDEO_ORIENT; //4


/**
 * RTP端口范围
 */
typedef struct tagCALL_S_RTP_PORT_RANGE
{
    TUP_UINT32 ulMinPort;       /**< 最小端口 */ 
    TUP_UINT32 ulMaxPort;       /**< 最大端口 */ 
} CALL_S_RTP_PORT_RANGE;


/**
 * BFCP端口范围
 */
typedef struct tagCALL_S_BFCP_PORT_RANGE
{
    TUP_UINT32 ulMinPort;       /**< 最小端口 */ 
    TUP_UINT32 ulMaxPort;       /**< 最大端口，目前无用，后续扩展 */
} CALL_S_BFCP_PORT_RANGE;


/**
 * 音频冗余(RFC2198)设置
 */
typedef struct tagCALL_S_AUDIO_RFC2198
{
    TUP_BOOL bSwitch;               /**< 是否启用2198手动冗余。 0：不启用 1：启用 */
    TUP_UINT32 uiRedPT;             /**< 需要手动冗余的pt，范围[98,127] */
    TUP_UINT32 uiRedLevel;          /**< 冗余级别 [0,3] */
} CALL_S_AUDIO_RFC2198;


/**
 * 低带宽设置
 */
typedef struct tagCALL_S_AUDIO_BAND_LIMIT
{
    TUP_UINT32 uiLowestBandWidth;                               /**< 音频低带宽限制，总带宽最大值  */
    TUP_CHAR   szLowestAudioCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /**< 音频低带宽编解码列表  */

    TUP_UINT32 uiLowerBandWidth;                                /**< 小于这个带宽的视频呼叫，使用低编解码列表  */
    TUP_CHAR   szLowerAudioCodec[CALL_D_MAX_CODEC_LIST_LEN+1];  /**< 较低带宽编解码列表 */
} CALL_S_AUDIO_BAND_LIMIT;


/**
 * SRTP模式
 */
typedef enum tagCALL_E_SRTP_MODE
{
    CALL_E_SRTP_MODE_DISABLE,       /**< 不启用 */
    CALL_E_SRTP_MODE_OPTION,        /**< 可选 */
    CALL_E_SRTP_MODE_FORCE,         /**< 强制 */
    CALL_E_SRTP_MODE_BUTT
} CALL_E_SRTP_MODE;


/**
 * 信令传输模式
 */
typedef enum tagCALL_E_TRANSPORTMODE
{
    CALL_E_TRANSPORTMODE_UDP,       /**< UDP */
    CALL_E_TRANSPORTMODE_TLS,       /**< TLS */
    CALL_E_TRANSPORTMODE_TCP,       /**< TCP */
    CALL_E_TRANSPORTMODE_DEFAULT,   /**< 默认使用公用传输方式 */
    CALL_E_TRANSPORTMODE_SVN,       /**< UDP */
    CALL_E_TRANSPORTMODE_BUTT
} CALL_E_TRANSPORTMODE;


/**
 * 视频参数集
 */
typedef struct tagCALL_S_VIDEO_PARAM_SET
{
	TUP_UINT32 ulBps;               /**< 视频码率 */
	TUP_UINT32 ulWidth;             /**< 图像宽度 */
	TUP_UINT32 ulHeight;            /**< 图像高度 */
	TUP_UINT32 ulFps;               /**< 最大帧率 */
	TUP_UINT32 uiMaxBitrate;        /**< 最大码率 */
} CALL_S_VIDEO_PARAM_SET;


/**
 * 视频清晰、流畅表
 */
typedef struct tagCALL_S_VIDEO_PARAM_TABLE
{
    CALL_S_VIDEO_PARAM_SET *pstVideoParamSet;   /**< 视频参数集链表 */
    TUP_UINT32 ulTableLineNum;                  /**< 表行数 */
    TUP_BOOL bVideoSmoother;                    /**< true表示流畅表、false表示清晰表 */
    TUP_BOOL bLowerLevel;                       /**< 是否降级表 */
} CALL_S_VIDEO_PARAM_TABLE;


/**
 * 视频CT(TODO)级别
 */
typedef struct tagCALL_S_VIDEO_CT_LEVEL_SET
{
    TUP_UINT32 ulCT;                /**< CT值 */
    CALL_S_VIDEO_LEVEL stLevel;     /**< 对应参数 */
} CALL_S_VIDEO_CT_LEVEL_SET;


/**
 * 视频CT(TODO)级别表
 */
typedef struct tagCALL_S_VIDEO_CT_LEVEL_TABLE
{
    TUP_UINT32 ulLen;                       /**< 表格长度 */
    CALL_S_VIDEO_CT_LEVEL_SET *pstLevelSet; /**< 视频CT(TODO)级别表 */
} CALL_S_VIDEO_CT_LEVEL_TABLE;


/**
 * BFCP开启错误码
 */
typedef enum tagCALL_E_BFCP_START_ERROR
{
    CALL_E_BFCP_START_ERROR_NO_ERROR             = 0,   /**< 启动成功 */
    CALL_E_BFCP_START_ERROR_REQUEST_FLOOR_DENIED = 1,   /**< 服务端拒绝令牌授予 */ 
    CALL_E_BFCP_START_ERROR_UDP_NETWORK_ERROR    = 2,   /**< udp心跳超时 */
    CALL_E_BFCP_START_ERROR_TCP_NETWORK_ERROR    = 3,   /**< TCP链路异常，如断网等 */
    CALL_E_BFCP_START_ERROR_NO_RESPOND_FROM_PEER = 4,   /**< 本端发送报文(重发)后，没有收到对方响应 */
    CALL_E_BFCP_START_ERROR_REQUEST_FLOOR_FAILED = 5,   /**< 令牌请求失败,目前由于重协商角色变换导致 */
    CALL_E_BFCP_START_ERROR_FORCE_REQUEST_FAILED = 6,   /**< 作为c，抢发辅流失败 */
}CALL_E_BFCP_START_ERROR;



#define TUP_MAX_CODEC_NAME_LEN 31   /**< 编解码名称长度 */
#define CODEC_NAME_H264           "H264"


/**
 * H264视频质量级别参数
 */
typedef struct tagCALL_S_VIDEO_H264_QUALITY_LEVEL_PARAM_SET
{
    char       codecName[TUP_MAX_CODEC_NAME_LEN]; /**< 已经注册的名称 */
    TUP_UINT8      uiPt;        /**< 默认的负载类型值 */
    TUP_UINT16 uiProfileIdc;    /**< 视频显示级别，HP:100 MP77 BP:66。默认为BP */
    TUP_UINT8  uiPacketMode;    /**< 打包模式,H264有用.取值范围[0,1,2],硬终端目前没用 */
    TUP_BOOL blevelAsymmetry;   /**< 不对称协商标志位。true为不对称协商，false为对称协商，默认为不对称协商 */ 
    TUP_UINT32 uiPriority;      /**< 编码优先级。从1开始（例如有3个codec，则优先级必须分别为1，2，3），数字越小优先级越高 */

}CALL_S_VIDEO_H264_QUALITY_LEVEL_PARAM_SET;


/**
 * H264视频质量级别参数表
 */
typedef struct tagCALL_S_VIDEO_H264_QUALITY_LEVEL_TABLE
{
    TUP_UINT32 uiParamSetNumber;  /**< 表格长度 */
    CALL_S_VIDEO_H264_QUALITY_LEVEL_PARAM_SET *pstVideoH264QualityLevelParamSet; /**< H264视频质量级别参数表 */
}CALL_S_VIDEO_H264_QUALITY_LEVEL_TABLE;


/**
 * @brief 呼叫业务事件通知回调函数定义
 * 
 * @param [in] TUP_UINT32 msgid   <b>:</b> 事件ID @see tagCALL_E_CALL_EVENT
 * @param [in] TUP_UINT32 param1  <b>:</b> 参数1，具体参见不同事件ID的说明
 * @param [in] TUP_UINT32 param2  <b>:</b> 参数2，具体参见不同事件ID的说明
 * @param [in] TUP_VOID *data     <b>:</b> 消息附加数据，具体参见不同事件ID的说明
 * @retval typedef TUP_VOID (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 初始化成功后调用，开发者要实现回调函数，回调消息指针参数必须在内部深拷贝，否则底层可能会释放，导致程序崩溃
 * @see tup_call_register_process_notifiy
 **/
typedef TUP_VOID (*CALL_FN_CALLBACK_PTR)(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *data);

/**
 * @brief 开发者自定义日志函数
 * 
 * @param [in] const TUP_INT8 *app_name  <b>:</b> 模块名
 * @param [in] TUP_UINT32 level          <b>:</b> 日志级别
 * @param [in] const TUP_INT8* function  <b>:</b> 函数名
 * @param [in] const TUP_INT8* filename  <b>:</b> 文件名
 * @param [in] TUP_UINT32 line_num       <b>:</b> 行号
 * @param [in] const TUP_INT8 *format    <b>:</b> 格式
 * @param [in] ...                       <b>:</b> 可变参数
 * @retval typedef TUP_VOID (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此函数对外暂无作用，作为预留接口
 * @see tup_call_register_logfun
 **/
typedef TUP_VOID (*CALL_FN_DEBUG_CALLBACK_PTR)(const TUP_INT8 *app_name, TUP_UINT32 level,
                            const TUP_INT8* function, const TUP_INT8* filename, TUP_UINT32 line_num, const TUP_INT8 *format, ...);


#define CALL_NTF_TEST_BASE     CALL_E_EVT_BUTT                      /**< 自动化测试通知事件起始ID */
#define CALL_NTF_VIDEO_FIRST_PACKET_TEST    (CALL_NTF_TEST_BASE+1)  /**< 收到第一个视频包信息 */
#define CALL_NTF_AUDIO_FIRST_PACKET_TEST    (CALL_NTF_TEST_BASE+2)  /**< 收到第一个音频包信息 */

#define CALL_DEC_PT_NUM_MAX 18      /**< 解码PT值最大个数 */


/**
 * 视频基本信息
 */
typedef struct tagCALL_VIDEO_BASE_INFO
{
    TUP_UINT32  uiCallID;                                   /**< 呼叫ID */    
    TUP_CHAR    acCodecName[CALL_MAX_CODEC_NAME_LEN+1];     /**< 编解码名 */ 
    TUP_UINT16  usEncPt;                                    /**< 编码PT值 */ 
    TUP_UINT16  ausDecPt[CALL_DEC_PT_NUM_MAX];              /**< 解码PT值列表 */ 
    TUP_UINT16  usDecPtNum;                                 /**< 解码PT值列表个数 */ 
}CALL_VIDEO_BASE_INFO;


/**
 * 音频基本信息
 */
typedef struct tagCALL_AUDIO_BASE_INFO
{
    TUP_UINT32  uiCallID;                                   /**< 呼叫ID */    
    TUP_CHAR    acCodecName[CALL_MAX_CODEC_NAME_LEN+1];     /**< 编解码名 */ 
    TUP_UINT16  usEncPt;                                    /**< 编码PT值 */
    TUP_UINT16  usDecPt;                                    /**< 解码PT值 */
}CALL_AUDIO_BASE_INFO;


/**
 * 呼叫自动化测试基本信息
 */
typedef union tagCALL_U_TEST_INFO
{
    CALL_AUDIO_BASE_INFO stAudioBaseInfo;                   /**< 音频基本信息 */    
    CALL_VIDEO_BASE_INFO stVideoBaseInfo;                   /**< 视频基本信息 */   
}CALL_U_TEST_INFO;


/**
 * 呼叫自动化测试基本信息通知
 */
typedef struct tagCALL_S_TEST_NOTIFY
{
    TUP_UINT32 uiNotifyType;
    CALL_U_TEST_INFO unInfo;
} CALL_S_TEST_NOTIFY;


/**
 * @brief 自动化测试回调函数，不应该开放
 * 
 * @param [in] TUP_VOID* pUserContext         <b>:</b> 用户信息
 * @param [in] CALL_S_TEST_NOTIFY* punNotify  <b>:</b> 呼叫自动化测试基本信息通知结构
 * @param [out] NA
 * @retval typedef TUP_VOID (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 怀疑这个函数没有用
 * @see TODO
 **/
typedef TUP_VOID (*TEST_CALL_BACK)(TUP_VOID* pUserContext, CALL_S_TEST_NOTIFY* punNotify); 

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_DEF_H__ */

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/

