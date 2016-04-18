
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

const int TE_D_NAME_LEN = 64;					//���ֳ���
const int TE_D_NUMBER_LEN = 64;			//�˺ų���
const int TE_D_URI_LEN = 128;					//URL����
const int TE_D_PWD_LEN = 32;					//���볤��
const int TE_D_IP_LEN = 64;							//IP����
const int TE_D_TIME_LEN = 64;					//ʱ�䳤��
const int TE_D_MESSAGE_LEN = 100;		//��Ϣ����
const int TE_D_DEVICE_MAX_NUM = 10;	//�豸�����
const int TE_D_DESC_MAX_NUM = 1024;
const int TE_D_CONF_SELECT_SITES_MAX = 400;//���ѡ��400���᳡���
const int TE_D_PROTOCOL_LENGTH=30;  /** Э�����ֳ��� */
const int TE_MAX_CODEC_NAME_LEN = 31; /** ����Ƶ��������Ƴ��� */
const int TE_MAX_FRAMESIZE_LEN =16;  /** ��Ƶ�ֱ��ʳ��� */    
const int TE_MAX_PROFILE_LEN =8;   /** ��Ƶ������ʽ����*/
const int TE_D_PHONE_LEN = 20; // �绰����
const int TE_D_ADDRESS_LEN = 80; //��ַ����
const int TE_D_DEPARTNAME_LEN = 64; // ���ų���
const int TE_D_EMAIL_LEN = 100; //local part ���ֲ��ܳ������ʼ�����
const int TE_D_GROUPNAME_LEN =64; //����������
const int TE_D_DESCRIPTION_LEN = 100;//��������
const int TE_D_ID_LEN = 10; //ID ����
const int TE_D_LDAPTYPE = 1;//ldap ����
const int TE_D_FTPTYPE = 0; //ftp ����
const int TE_D_MAXLOGLENGTH = 1024; //�����־����

const char LOGSWITCH[]="LOGSWITCH";
const char LOGPATH[]="LOGPATH";
//const int TE_D_MAX_CODEC_LIST_LEN=127; /** �����list��󳤶�*/
//const int TE_D_IP_LENGTH = 16;	//IP
//const int TE_D_MAX_LENGTH_NUM = 256;	//����


// ���Ͷ���
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
	TE_E_CFG_CALLENV = 1, /*��������*/
	TE_E_CFG_SERVER,      /*��������ַ*/
	TE_E_CFG_NET,         /*��������ӿڵ�ַ*/
	TE_E_CFG_USERAGENT,
	TE_E_CFG_SERVRIGHT,   /*ҵ��Ȩ��*/
	TE_E_CFG_DSCP,        /*DSCP*/    
	TE_E_CFG_SIP,         /*SIP��������*/
	TE_E_CFG_ACCOUNT,
	TE_E_CFG_COMPATIBLE_PARAM,
	TE_E_CFG_CONF,        /*�����������*/
	TE_E_CFG_MEDIA,       /* ý��ȫ������*/
	TE_E_CFG_AUDIO,       /*��Ƶ����*/
	TE_E_CFG_VIDEO,       /*��Ƶ���� & ��������*/
	TE_E_CFG_BFCP,        /*����BFCP����*/
	TE_E_CFG_MOBILE_VOICEMAIL,   /*�ƶ���������Ȩ��*/
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


// �������
typedef enum tagTE_E_USEKEY_SORT_RULE
{
	group_status_first = 0,        // �����°�״̬������
	group_name_first,              // �����°�����
	do_not_sort                    // ��Ҫ����
}TE_E_USEKEY_SORT_RULE;

#define TE_CFG_ID_DEF(major,datatype,_id,_index)    ((major)<<24|((datatype) << 16)|(_id) <<8|(_index))

/* ��Ƶ���� & ��������(��ͬ�����豣������Ƶ����ǰ3���ֽ�һ�£����һ���ֽ���1)*/
#define TE_D_CFG_VIDEO_FRAMESIZE          TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 0) //�ֱ��� (TE_S_VIDEO_FRAMESIZE
#define TE_D_CFG_DATA_FRAMESIZE           TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 1) //�ֱ��� (TE_S_VIDEO_FRAMESIZE
#define TE_D_CFG_VIDEO_DATARATE           TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 0) //���� (TE_S_VIDEO_DATARATE
#define TE_D_CFG_DATA_DATARATE            TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 1) //���� (TE_S_VIDEO_DATARATE
#define TE_D_CFG_VIDEO_FRAMERATE          TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 0) //֡�� (TE_S_VIDEO_FRAMERATE)
#define TE_D_CFG_DATA_FRAMERATE           TE_CFG_ID_DEF(TE_E_CFG_VIDEO, TE_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 1) //֡�� (TE_S_VIDEO_FRAMERATE)


#define EXCEL_POSTFIX               _T("xls")         // Excel�ļ���׺
#define EXCEL2007_POSTFIX           _T("xlsx")        // EXCEL2007�ļ���׺
#define EXCEL2010_POSTFIX           _T("xlsx")        // EXCEL2010�ļ���׺
#define EXCEL2012_POSTFIX           _T("xlsx")        // EXCEL2012�ļ���׺
#define CSV_POSTFIX                 _T("csv")         // csv�ļ���׺
#define POSTFIX_COUNT               3			      // ��׺���ĸ���
#define VNET_KEY_ROW_POS            1                 // V�������ļ��ؼ������ڵ���,������ؼ���
const static int STADNTILENUM       = 13;              // ��׼����ͷ�ֶ���,���һ���ֶ�Ϊ��
const static int STADNTILENUM_OLD   = 7;              // ��׼����ͷ�ֶ���,���һ���ֶ�Ϊ��(��ǰ���ֶ���)

typedef struct tagTE_S_VIDEO_FRAMESIZE
{
	TE_UINT32 uiFramesize;         //����ֱ���
	TE_UINT32 uiMinFramesize;      //��С����ֱ���
	TE_UINT32 uiDecodeFrameSize;   //�������ֱ���
} TE_S_VIDEO_FRAMESIZE;

typedef struct tagTE_S_VIDEO_DATARATE
{
	TE_UINT32 ulDataRate;     //����
	TE_UINT32 ulMinDataRate;  //��С����
	TE_UINT32 ulMaxDataRate;  //�������
	TE_UINT32 ulMaxBw;        //������
} TE_S_VIDEO_DATARATE;

typedef struct tagTE_S_VIDEO_FRAMERATE
{
	TE_UINT32 uiFrameRate;   //֡��
	TE_UINT32 uiMinFrameRate; //��С֡��
} TE_S_VIDEO_FRAMERATE;

typedef struct tagTE_S_SITE_INFO
{
	unsigned int index_;                    //���
	TE_CHAR  name_[TE_D_NAME_LEN+1];	//�᳡��
	TE_CHAR  number_[TE_D_NUMBER_LEN+1];			//����
	short T_;				//�᳡T��
	short M_;				//�᳡M��
	bool isBroadcast_;				//�Ƿ��ڹ㲥��
	bool isMute_;					//�Ƿ����״̬
	bool isChairMan_;				//�Ƿ�����ϯ
	bool isJoined_;					//�Ƿ����
	bool isWatching_;

}TE_S_SITE_INFO;

typedef struct tagTE_S_PERSON_INFO 
{
	long itemID;
	TE_CHAR cvsID[TE_D_ID_LEN];					//��¼�Ļ���ID
	long long recordID;							//��¼ID
	int		nUserId;							//�û�ID
	TE_CHAR strAcc[TE_D_NUMBER_LEN+1];			//�˺�
	TE_CHAR strName[TE_D_NAME_LEN+1];			//����
	TE_CHAR strPhone[TE_D_PHONE_LEN+1];			//�绰����
	TE_CHAR strMessage[TE_D_MESSAGE_LEN+1];	    //��Ϣ
	TE_CHAR strTime[TE_D_TIME_LEN+1];			//ʱ��
	TE_CHAR strDuration[TE_D_TIME_LEN+1];		//����ʱ��
	int		nPersonStatus;						//�û�״̬
	int		nPhoneStatus;				    	//	�绰״̬
	TE_CHAR strPersonIcon[TE_D_NAME_LEN+1];		//����ͷ��
	int nCalltype;                              //��������
}TE_S_PERSON_INFO;

typedef struct tagTE_S_PERSONS_INFO
{
	TE_S_PERSON_INFO* historyRecords;
	TE_INT32 num;                      

}TE_S_PERSONS_INFO;

typedef struct tagTE_S_SITE_INVITEDLIST
{

	TE_CHAR* list[TE_D_CONF_SELECT_SITES_MAX+1];  //Ҫ�����Ա�б�
	TE_INT32 listCount;                              //Ҫ�������
	
}TE_S_SITE_INVITEDLIST;


typedef struct tagTE_S_SITE_JIONEDLIST
{

	TE_S_SITE_INFO list[TE_D_CONF_SELECT_SITES_MAX];     //�������Ա��Ϣ�б�
	TE_INT32 listCount;                                //���������

}TE_S_SITE_JIONEDLIST;


/** SIP�˻�ע��״̬*/
typedef enum tagTE_E_REG_STATE
{
    TE_E_REG_STATE_UNREGISTER,     /**< SIP�˻�δע��*/
    TE_E_REG_STATE_REGISTERING,    /**< SIP�˻�ע����*/
    TE_E_REG_STATE_DEREGISTERING,  /**< SIP�˻�ע����*/
    TE_E_REG_STATE_REGISTERED,     /**< SIP�˻���ע��*/
    TE_E_REG_STATE_BUTT            /**< SIP�˻���Ч״̬*/
} TE_E_REG_STATE;

/*��������*/
typedef enum tagTE_E_CALL_TYPE
{
    TE_E_CALL_TYPE_IPAUDIO,					//IP��������
    TE_E_CALL_TYPE_IPVIDEO,					//IP��Ƶ����
    TE_E_CALL_TYPE_BUTT						//��Ч���ͺ���
} TE_E_CALL_TYPE;

/*���л���״̬*/
typedef enum tagTE_E_CALL_STATE
{
    TE_E_CALL_STATE_IDLE,					//���п���̬
    TE_E_CALL_STATE_IN,						//���к���̬
    TE_E_CALL_STATE_OUT,					//���к���̬
    TE_E_CALL_STATE_LIVE,					//����ͨ��̬
    TE_E_CALL_STATE_HOLD,					//���б���̬
    TE_E_CALL_STATE_END,					//���н���̬
    TE_E_CALL_STATE_BUTT					//������Ч̬
} TE_E_CALL_STATE;

typedef enum tagTE_E_LOGIN_STATE
{
	TE_E_LOGIN_SUCCESS						=	0,//��½�ɹ�
	TE_E_LOGIN_FAIL_AUTH					=	1,//��֤ʧ��
	TE_E_LOGIN_SIGNING						=	2,//��¼
	TE_E_LOGIN_FAIL_CER_INVALID				=	3,//�Ƿ�ƾ֤
	TE_E_LGOIN_FAIL_UNREGISTER				=	4,//δע��
	TE_E_LOGIN_FAIL_CONTACT					=	5,//CONTACT ʧ��
	TE_E_LOGIN_FAIL_SIP						=	6,//SIPʧ��
	TE_E_LOGIN_FAIL_TIMEOUT					=	7,//��ʱ
	TE_E_LOGIN_SIGNOUT						=	8,//ע��
	TE_E_LOGIN_FAIL_NOIP					=	9,//��IP����
	TE_E_LOGIN_FAIL_HASIP					=	10,//������IP����
	TE_E_LOGIN_KICKOUT						=	11,//����
	TE_E_LOGIN_FAIL_LICENSE_TYPE_FAILED		=	12,//��ȡLicense����ʧ��
	TE_E_LOGIN_FAIL_LICENSE_TYPE_INVALID	=	13,//License������Ч
	TE_E_LOGIN_FAIL_LICENSE_APPLY_FAILED	=	14,//����Licenseʧ��
	TE_E_LOGIN_FAIL_LICENSE_REFRESH_FAILED	=	15,//����Licenseʧ��
	TE_E_LOGIN_FAIL_OTHERS					=	16//����
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
	CALL_TYPE_DIAL,     //�Ѳ�
	CALL_TYPE_NOANSWER, //δ��
	CALL_TYPE_ANSWER,   //�ѽ�
	CALL_TYPE_ACB       //�غ�
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
	TE_E_CALL_EVENT_CALLOUT				=0,   //����ʱ��
	TE_E_CALL_EVENT_AUDIOVIDEOINCOMING	=1,   //�����¼�
	TE_E_CALL_EVENT_CALLRING				=2,   //���ں���
	TE_E_CALL_EVENT_ANSWERRSP				=3,   //��Ӧ����
	TE_E_CALL_EVENT_CLOSE					=4,   //ͨ������
	TE_E_CALL_EVENT_OPEN_VEDIO			=5,	   //������Ƶ
	TE_E_CALL_EVENT_CLOSE_VEDIO			=6,   //�ر���Ƶ
	TE_E_CALL_EVENT_ANSWER_VEDIO		=7,   //��Ӧ��Ƶ����
}TE_E_CALL_EVENT;

typedef enum tagTE_E_DATA_EVENT
{
	TE_E_DATA_EVENT_DATASEND				=0,   //���͸����¼�
	TE_E_DATA_EVENT_DATARECIEVE				=1,   //���ո����¼�
	TE_E_DATA_EVENT_DATASTOPED				=2,   //ͣ�������¼�
	TE_E_DATA_EVENT_DATASENDFAILURE			=3,   //��������ʧ���¼�
	TE_E_DATA_BFCPMODIFIED_RESULT			=4,   //�����仯����¼�
}TE_E_DATA_EVENT;

typedef enum tagTE_E_CALL_END_REASON
{
	TE_E_CALL_END_REASON_NORMAL							=	0,	// normal call end
	TE_E_CALL_END_REASON_CANNOT_CONNECT					=	1,	// can not connect with other;
	TE_E_CALL_END_REASON_BUSYING						=	2,	// other is busying now;
	TE_E_CALL_END_REASON_CANNOT_CONNECT_OFFLINE			=	3,	// other is offline now;
	TE_E_CALL_END_REASON_BUTT							=	4	// call end reason number;
}TE_CALL_END_REASON;

/*��������*/
typedef enum tagTE_E_VOLUME_TYPE
{
	TE_E_VOLUME_TYPE_MIC,					//��˷�����
	TE_E_VOLUME_TYPE_SPEAK,					//����������
	TE_E_VOLUME_TYPE_BUTT						//��Ч����
} TE_E_VOLUME_TYPE;

typedef struct tagTE_S_NETWORK_CONIFG
{
	TE_E_SETTING_SRTP_MODE srtp_mode;
	TE_E_SETTING_MEDIA_BANDWIDTH media_bandwidth;
	TE_E_SETTING_MEDIA_OPEN_SLIDE media_open_slide;
	TE_E_SETTING_MEDIA_AUTO_REPLY media_auto_reply;
	TE_S_VIDEO_FRAMESIZE dataFrameSize;// ���÷ֱ���
	TE_S_VIDEO_DATARATE stDataRate;// ���ø�������
	TE_S_VIDEO_DATARATE sVideoDataRate;// ������������
	TE_S_VIDEO_FRAMERATE stDataFrameRate;//����֡��

	TE_BOOL setFrameSize;//�Ƿ�Ҫ���÷ֱ���
	TE_BOOL setDataRate;//�Ƿ�Ҫ��������
	TE_BOOL setFrameRate;//�Ƿ�Ҫ����֡��

}TE_S_NETWORK_CONFIG;

//��¼�û���Ϣ
typedef struct tagTE_S_LOGIN_INFO
{
   TE_CHAR		cUserName[TE_D_NAME_LEN+1];			// �û���
   TE_CHAR		cPWD[TE_D_PWD_LEN+1];				// �������ģ�����Ϊ�գ�
   TE_CHAR		cSipUri[TE_D_URI_LEN+1];
   TE_CHAR		stIP[TE_D_IP_LEN+1];				// ��¼������IP
   TE_UINT32	uiPort;								// ��¼�������˿ڣ�TLSĬ�϶˿�Ϊ5061,UDPĬ�϶˿�5060
   TE_CHAR		cTransMode[4];						// �ͻ�����SIP�������䴫��ģʽ TLS/UDP
   TE_CHAR		licenseServer[TE_D_IP_LEN];			// ֤�������
   TE_CHAR		cReserve[32];						//�����ֶ�
}TE_S_LOGIN_INFO;


/*��¼���*/
typedef struct tagTE_S_LOGIN_RESULT
{
    TE_UINT32 ulSipAccountID;					//SIP�˻�ID
    TE_E_REG_STATE enRegState;					//SIP�˻�ע��״̬
    TE_UINT32 ulReasonCode;						//ע��ʧ�ܵ�ԭ����
    TE_INT8 acTelNum[TE_D_URI_LEN+1];				//SIP�᳡����
    TE_INT8 acDisplayName[TE_D_NAME_LEN+1];		//SIP�᳡����
	TE_E_LOGIN_STATE loginState;
	TE_CHAR     cReserve[32];					//�����ֶ�
} TE_S_LOGIN_RESULT;

/*������Ϣ*/
typedef struct tagTE_S_CALL_STATE_INFO
{
    TE_UINT32 ulSipAccountID;					//SIP�˻�ID
    TE_UINT32 ulCallID;							//ͨ��ID
    TE_E_CALL_TYPE enCallType;					//��������
    TE_E_CALL_STATE enCallState;				//ͨ��״̬
    TE_INT8 acTelNum[TE_D_URI_LEN+1];				//SIP�᳡����
    TE_INT8 acDisplayName[TE_D_NAME_LEN+1];		//SIP�᳡����
    TE_UINT32 ulReasonCode;						//ʧ��ԭ����endcall
    TE_BOOL bIsIn;								//��ʶ��·ͨ���Ƿ�Ϊ����
    TE_BOOL bIsPassiveEnd;						//��ʶ��·�����Ƿ�Զ�˹Ҷ�
	TE_E_CALL_EVENT	enCallEvent;				//�ϱ��绰�¼�
	TE_E_DATA_EVENT	enDataEvent;				//�ϱ������¼�
	TE_UINT32 sessionType;
	TE_INT8 acEncodeProtocol[TE_D_PROTOCOL_LENGTH];               /**< ��Ƶ����Э��*/
} TE_S_CALL_STATE_INFO;

//��Ƶ����Ϣ
typedef struct tagTE_S_AUDIO_STREAM_INFO
{
	TE_UINT32 bIsCalling;                        /**< �Ƿ���ͨ����*/
	TE_INT8 bIsSRTP;                           /**< �Ƿ�����SRTP MEDIASERVICE_TRANS_SRTP*/
	TE_INT8 acEncodeProtocol[TE_D_PROTOCOL_LENGTH];               /**< ����Э��*/
	TE_INT8 acDecodeProtocol[TE_D_PROTOCOL_LENGTH];               /**< ����Э��*/
	TE_UINT32 ulChannelID;                     /**< ͨ��ID */
	TE_UINT32 ulSendBitRate;                   /**< ���ͱ����� */
	TE_UINT32 ulRecvBitRate;                   /**< ���ձ����� */
	TE_UINT32 ulSendTotalLostPacket;           /**< ���ͷ��ۼư��� */
	TE_FLOAT fSendLossFraction;                /**< ���ͷ�������(%) */
	TE_FLOAT fSendJitter;                      /**< ���ͷ�ƽ������(ms) */
	TE_FLOAT fSendDelay;                       /**< ���ͷ�ƽ��ʱ��(ms) */
	TE_UINT32 ulRecvTotalLostPacket;           /**< ���շ��ۼư��� */
	TE_FLOAT fRecvLossFraction;                /**< ���շ�������(%) */
	TE_FLOAT fRecvJitter;                      /**< ���շ�ƽ������(ms) */
	TE_FLOAT fRecvDelay;                       /**< ���շ�ƽ��ʱ��(ms) */
} TE_S_AUDIO_STREAM_INFO, *TE_S_AUDIO_STREAM_INFO_PTR;

//��Ƶ����Ϣ
typedef struct tagTE_S_VIDEO_STREAM_INFO
{
	TE_INT8 acEncodeName[TE_MAX_CODEC_NAME_LEN];        /**< ��������*/
	TE_INT8 acDecodeName[TE_MAX_CODEC_NAME_LEN];        /**< ��������*/
	TE_INT8 acEncoderSize[TE_MAX_FRAMESIZE_LEN];        /**< ͼ��ֱ���(����)*/
	TE_INT8 acDecoderSize[TE_MAX_FRAMESIZE_LEN];        /**< ͼ��ֱ���(����)*/
	TE_INT8 bIsSRTP;                           /**< �Ƿ�����SRTP,��ӦMEDIASERVICE_TRANS_SRTP*/
	TE_UINT32  ulSendFrameRate;                            /**< ��Ƶ֡��(����)*/
	TE_UINT32  ulRecvFrameRate;                            /**< ��Ƶ֡��(����)*/
	TE_UINT32  ulVideoSendBitRate;                        /**< ��������*/
	TE_UINT32  ulVideoRecvBitRate;                        /**< ��������*/
	TE_INT8 acEncoderProfile[TE_MAX_PROFILE_LEN];        /**< ��Ƶ�����ʽ*/
	TE_INT8 acDecoderProfile[TE_MAX_PROFILE_LEN];        /**< ��Ƶ�����ʽ*/
	TE_FLOAT fVideoSendLossFraction;                    /**< ���ͷ�������(%) */
	TE_FLOAT fVideoSendJitter;                          /**< ���ͷ�ƽ������(ms) */
	TE_FLOAT fVideoSendDelay;                           /**< ���ͷ�ƽ��ʱ��(ms) */
	TE_FLOAT fVideoRecvLossFraction;                    /**< ���շ�������(%) */
	TE_FLOAT fVideoRecvJitter;                          /**< ���շ�ƽ������(ms) */
	TE_FLOAT fVideoRecvDelay;                           /**< ���շ�ƽ��ʱ��(ms) */
	TE_UINT32 ulWidth;                                    /**< ��Ƶ�ֱ���-��*/
	TE_UINT32 ulHeight;                                   /**< ��Ƶ�ֱ���-��*/
} TE_S_VIDEO_STREAM_INFO, *TE_S_VIDEO_STREAM_INFO_PTR;


typedef struct tagTE_S_STREAM_INFO
{
	TE_S_AUDIO_STREAM_INFO stAudioStreamInfo;         /*��Ƶ����Ϣ*/
	TE_S_VIDEO_STREAM_INFO stVideoStreamInfo;         /*��Ƶ����Ϣ*/
	TE_S_VIDEO_STREAM_INFO stDataStreamInfo;          /*������Ϣ*/
} TE_S_STREAM_INFO, *TE_S_STREAM_INFO_PTR;


/*��������״̬*/
typedef struct tagTE_S_CREATECONF_STATE_INFO
{
	TE_CHAR _reason[TE_D_DESC_MAX_NUM+1];       //״̬�������
	TE_INT32 _result;               //״̬���ֵ
} TE_S_CREATECONF_STATE_INFO;


/*���������*/
typedef struct tagTE_S_ADDSITETOCONF_RESULT
{
	TE_SHORT failedCount;     //��������¼��ص��������ʾ�м��������ʧ��
	TE_BOOL  result;           //��������¼��ص�������ɹ���ʧ�� 
} TE_S_ADDSITETOCONF_RESULT;


typedef enum tagTE_E_CONF_RESULT
{
	TE_E_EVT_CREATE_CONF_STATE_CHANGE  =	0,  //���������¼�
	TE_E_EVT_APPLY_CONF_CHAIRMAN  =1,   //������ϯ�¼�
	TE_E_EVT_RELEASE_CONF_CHAIRMAN  =	2,  //�ͷ���ϯ�¼�
	TE_E_EVT_ADDSITETOCONF_RESULT		=  3,  //��������¼�
	TE_E_EVT_CONF_BROADCAST_RESULT  =  4,   //����㲥�¼�
	TE_E_EVT_SITE_WATCH_RESULT    =    5,   //�ۿ������¼�
	TE_E_EVT_CONF_EXTENDTIME_NOTE =   6,   //��ʾ�ӳ�����ʱ���¼�
	TE_E_EVT_CONF_EXTEND_RESULT   =   7,   //�ӳ������¼�
	TE_E_EVT_CONF_MEMLISTREFRESH	=  8,  //ˢ�»�����Ա�б��¼�
	TE_E_EVT_CONF_BROADCAST_MEMLISTREFRESH	= 9,  //�㲥��ˢ�»�����Ա�б��¼�
	TE_E_EVT_CONF_CHAIRMAN_THENDO	=  10,	  //������ϯָʾ
}TE_E_CONF_RESULT;

typedef enum tagTE_E_ENTERPRISE_RESULT
{
	TE_E_EVT_LDAP_CONTACTS_ADDRESS = 0 // ldap ��ҵͨѶ¼
}TE_E_ENTERPRISE_RESULT;

typedef struct tagTE_S_LDAP_D_Search_Result
{
	bool bSucess; // �Ƿ�ɹ�
	unsigned int	ulCode; // ������
	unsigned int ulSeqNo; // ������ŵķ���
	unsigned int ulCookieLen; // ����������cookie����
	char *pcPageCookie; // cookie����
}TE_S_LDAP_D_Search_Result;

typedef struct tagTE_S_CONF_RESULT
{
	TE_E_CONF_RESULT	eventType;	//�����ϱ����¼�����
	union
	{
		TE_BOOL	isChairman;          
		TE_INT32 result;            //������������¼��ķ��ؽ��
		TE_S_CREATECONF_STATE_INFO createConfInfo;  //���������¼��ķ��ؽ��
		TE_S_ADDSITETOCONF_RESULT addHallRest;   //��������¼��ķ��ؽ��
	}uResult;  //��ͬ�¼����Ͷ�Ӧ��ͬ���
}TE_S_CONF_RESULT;

// ! An enum
		/** \brief  online status definition
		*/
typedef enum tagTE_E_CONTACT_AVAIL_ABILITY
{
	TE_E_CONTACT_Offline = 0,  //����
	TE_E_CONTACT_Online,       //����
	TE_E_CONTACT_Busy,         //æµ
	TE_E_CONTACT_Hide,         //����
	TE_E_CONTACT_Leave,        //�뿪
	TE_E_CONTACT_NoDisturb,    //����
	TE_E_CONTACT_InvalidStatus, //�Ƿ�״̬
}TE_E_CONTACT_AVAIL_ABILITY;


//��ϵ����Ϣ 
typedef struct tagTE_S_CONTACT_INFO
{
	TE_CHAR id[TE_D_ID_LEN+1];							// ID
	TE_CHAR name[TE_D_NAME_LEN+1];				//	����
	TE_CHAR ucAcc[TE_D_NUMBER_LEN+1];			// �˺�
	TE_CHAR nickname[TE_D_NAME_LEN+1];			// �ǳ�
	TE_CHAR mobile[TE_D_PHONE_LEN+1];			// �ֻ���
	TE_CHAR officePhone[TE_D_PHONE_LEN+1];	//	�칫�绰	
	TE_CHAR addresssite[TE_D_ADDRESS_LEN+1];	// ��ַ
	TE_CHAR email[TE_D_EMAIL_LEN+1];				// ����
	TE_CHAR deptname[TE_D_DEPARTNAME_LEN+1];	//	����
	TE_CHAR description[TE_D_DESCRIPTION_LEN+1];	//	����
	TE_E_CONTACT_AVAIL_ABILITY status;          // ��ϵ��״̬
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
	TE_E_ENTERPRISE_RESULT  eventType;   //��ҵͨѶ¼�ϱ��¼�����
	TE_S_LDAP_D_Search_Result* pResult;
	TE_S_CONTACTS_INFO enterpriseContacts;
}TE_S_ENTERPRISE_RESULT;

/// ��ز������ֵ, copy��TUPͷ�ļ�
typedef enum tagTE_E_OPERATION_RSP_REASON_CONF
{
	TE_E_OPERATION_SUCCESS = 0,           //!< ��ز����ɹ�

	TE_E_OPERATION_NO_EXIST_USER,         //!< �������ն˲����ڣ�remove��broadcast��
	TE_E_OPERATION_NO_PRIVILEGE,          //!< û�в���Ȩ�ޣ�������ϯ��

	TE_E_OPERATION_NO_CHAIR_FUNC,         //!< ����û����ϯ����
	TE_E_OPERATION_NO_CAP_TO_BE_CHAIR,    //!< �����ݵ��ն�û����ϯ����
	TE_E_OPERATION_CHAIR_EXIST,           //!< ������������ϯ
	TE_E_OPERATION_CHAIR_PWD_ERR,         //!< ��ϯ�������

	TE_E_OPERATION_FAIL_UNKNOW = 0xFF     //!< ����ʧ��ԭ��
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


/*Ԥ��������Ϣ*/
typedef struct tagTE_S_PREVIEWWND_INFO
{
    TE_ULONG ulWndHandle;						//���ھ��
	TE_ULONG ulWndLeft;							//X����
    TE_ULONG ulWndwidth;						//���ڿ��
	TE_ULONG ulWndTop;							//Y����
	TE_ULONG ulWndHeight;						//���ڸ߶�
} TE_S_PREVIEWWND_INFO;



//Ⱥ����Ϣ
typedef struct tagTE_S_GROUP_INFO
{
	TE_CHAR groupName[TE_D_NAME_LEN+1];			//������
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

// ����ӿڷ�����
enum EM_TEServiceRetvCode
{
	TE_SDK_Success				=	0,			//�ɹ�
	TE_SDK_InvalidPara			=	1,			//���Ϸ��Ĳ���
	TE_SDK_Failed				=	2,			//ʧ��
	TE_SDK_NotInit				=	3,			//δ��ʼ��
	TE_SDK_NullPtr				=	4,			//��ָ��
	TE_SDK_FindUriErr			=	5,			//�����û�uri����
	TE_SDK_NotHaveCallTarget	=	6,			//û�к��ж���
	TE_SDK_InTempGroupNow		=	7,			//�Ѿ���TempGroup��
	TE_SDK_NotFoundCallID				=	8,			//û���ҵ�Call ID
	TE_SDK_NoRight				=	9,			//û��Ȩ��
	TE_SDK_NotLogin				=	10,			//δ�ɹ���¼
	TE_SDK_SetParamFailed	= 11 ,          //���ý������� srtp������������������������ʧ��
	TE_SDK_OpenPreviewFailed =12,			//����ƵԤ��ʧ��
	 TE_SDK_NotFoundcamera  = 13,       // û���ҵ������
	 TE_SDK_SenddataFailed    = 14,			//���͹�����������ʧ��
	 TE_SDK_RecvdataFailed    = 15,			//���չ�����������ʧ��
	 TE_SDK_AddContactFailed =16,			//��ӱ�����ϵ��ʧ��
	 TE_SDK_RemoveContactFailed = 17,  //�Ƴ�������ϵ��ʧ��
	 TE_SDK_EditContactFailed  =18,		//�༭������ϵ��ʧ��
	 TE_SDK_GetContactListFailed =19,	//��ȡ��ϵ���б�ʧ��
	 TE_SDK_SearchContactFailed = 20,	//������ϵ��ʧ��
	 TE_SDK_OverMax				=	21,			//�����������
	 TE_SDK_NotFound                   =22,
	 TE_SDK_GetMediaInfoFailed  =23, //��ȡý����Ϣʧ��
	 TE_SDK_ConfCreateFailed =24,   //���鴴��ʧ��
	 TE_SDK_GetConfMemberFailed =25, //��ȡ�����Ա�б�ʧ��
	 TE_SDK_NotConfChairMan  =26,  //���ǻ�����ϯ
	 TE_SDK_SendDTMFFailed =27,  //����DTMFʧ��
	 TE_SDK_GetAVsessByConvIdFailed =28,  //ͨ��ID��ȡAVsessionʧ��
	 TE_SDK_AudioToVideoFailed  =29,  // ��Ƶת��Ƶʧ��
	 TE_SDK_VideoChannelStopFailed =30,//��Ƶ���ŵ�ֹͣʧ��
	 TE_SDK_SetVideoCaptureDevFailed =31,//��Ƶץȡ�豸ʧ��
	 TE_SDK_ConfApplyChairManFailed =32,//���������ϯʧ��
	 TE_SDK_ConfReleaseChairManFailed =33,//��ϯ�ͷ�ʧ��
	 TE_SDK_jionConfFailed   =34,              //�������ʧ��
	 TE_SDK_ExtandConfFailed =35,          //�������ʱ��ʧ��
	 TE_SDK_ConfCallOutHallFailed =36, //������л᳡ʧ��
	 TE_SDK_ConfHangUpHallFailed =37, //����Ҷϻ᳡ʧ��
	 TE_SDK_DeleteHallFailed =38,  //����ɾ���᳡ʧ��
	 TE_SDK_ConfMuteHallFailed =39, //���龲���᳡ʧ��
	 TE_SDK_ConfUnMuteHallFailed =40, //����ֹͣ����ʧ��
	 TE_SDK_ConfBroadCastHallFailed =41,//����㲥�᳡ʧ��
	 TE_SDK_ConfStopBroadFailed =42, //����ֹͣ�㲥ʧ��
	 TE_SDK_ConfWatchHallFailed =43, //����ۿ��᳡ʧ��
	 TE_SDK_ConfEndFailed =44, //�����᳡ʧ��
	 TE_SDK_GetContactByIdFailed =45 ,// ͨ��ID��ȡ��ϵ��ʧ��
	 TE_SDK_CreateCustomGroupFailed =46 ,// �½�Ⱥ��ʧ��
	 TE_SDK_RenameCustomGroupFailed =47, //������Ⱥ��ʧ��
	 TE_SDK_RemoveCustomGroupFailed =48, //�Ƴ�Ⱥ��ʧ��
	 TE_SDK_GetCustomGroupListFailed =49, //��ȡ��ϵ�˷���ʧ��
	 TE_SDK_AudioVideoInUsedFailed=50,   //����ͨ���У����ܽ���ý���豸��Ϣ����
     TE_SDK_VOLUME_TO_SET_LESS_THAN_ZERO=51,//Ҫ���õ�����С��0
     TE_SDK_SET_MIC_VOLUME_FAILED=52,//�����������ʧ��
     TE_SDK_SET_SPEAK_VOLUME_FAILED=53,//��������������ʧ��
	 TE_SDK_INVALID_VOLUME_TYPE=54,//�Ƿ�����������
	 TE_SDK_NotFoundAudioIn=55,//δ�ҵ���Ƶ�����豸
	 TE_SDK_NotFoundAudioOut=56,//δ�ҵ���Ƶ����豸
	 TE_SDK_SetAudioCaptureDevFailed =57,//��Ƶ�����豸����ʧ��
	 TE_SDK_SetAudioPlayDevFailed =58,//��Ƶ����豸����ʧ��
	 TE_SDK_GetContactFailed =59,	//��ȡ��ϵ��ʧ��
	 TE_SDK_INIT_FAILED=60,			//��ʼ��ʧ��
	 TE_SDK_ContactEmpty = 61,     //��ϵ��Ϊ��
	 TE_SDK_GetEnterpriseContactsFailed = 62,//��ȡ��ҵ��ϵ��ʧ��
	 TE_SDK_SearchFtpFailed = 63, //ftp����ʧ��
	 TE_SDK_NOGetAllNetContactsList = 64,//û�л����ҵͨѶ¼��ϵ��
	 TE_SDK_ExceedNameLength = 65, //����������󳤶�
	 TE_SDK_ExceedAccountLength = 66,//�����˺���󳤶�
	 TE_SDK_ExceedAddressLength = 67,//������ַ��󳤶�
	
	 TE_SDK_illegalEmailFormat = 69,//�����ʽ�Ƿ�
	 TE_SDK_ExceedDeptnameLength = 70,//����������󳤶�
	 TE_SDK_ExceedMobileLength = 71,//�����ֻ��绰��󳤶�
	 TE_SDK_ExceedOfficePhoneLength = 72,//�����칫�绰��󳤶�
	 TE_SDK_ExceedNickNameLength = 73,//�����ǳ���󳤶�
	 TE_SDK_ExceedMaximumContacts = 74,//���������ϵ�˸���
	 TE_SDK_GetCustomGroupFailed = 75,//��ȡ����ʧ��
	 TE_SDK_ContactAlreadyExist = 76,//��ϵ���Ѿ�����
	 TE_SDK_ContactWhetherReplace = 77,//��ϵ���Ƿ��滻
	 TE_SDK_NoFindContact = 78,//û���ҵ���ϵ��
	 TE_SDK_ModifyFailed =79,//�޸�ʧ��
	 TE_SDK_GroupNameEmpty = 80,//��������Ϊ��
	 TE_SDK_ExceedGroupSum = 81,//�������������Ŀ
	 TE_SDK_GroupAlreadyExist = 82,//�����Ѿ�����
	 TE_SDK_ExceedGroupNameLength = 83,//����������󳤶�
	 TE_SDK_AddGroupFailed = 84,//��ӷ���ʧ��
	 TE_SDK_SameWithDefaultName = 85,//��Ĭ�Ϸ�������
	 TE_SDK_illegalFileFormat = 86, //�Ƿ����ļ���ʽ
	 TE_SDK_CreatExcelApplicationFailed = 87,//����excelʧ��
	 TE_SDK_ExcelWorkbookEmpty = 88,//excel bookΪ��
	 TE_SDK_ExcelWorksheetEmpty = 89, //excel ��Ϊ��
	 TE_SDK_InsertExcelContactFailed = 90,//��excel������ϵ��ʧ��
	 TE_SDK_ComError = 91, //�쳣����
	 TE_SDK_OpenCSVFailed = 92,//��csv�ļ�ʧ��
	 TE_SDK_InsertCSVContactFailed = 93,//��csv������ϵ��ʧ��
	 TE_SDK_ErrorFileType = 94,//������ļ�����
	 TE_SDK_ContactOrGroupSumBeyondLimit = 95,//������ϵ�˻��߷��������Ŀ
	 TE_SDK_ErrorHeadLineFormat =96,//�����ͷ�ļ��и�ʽ
	 TE_SDK_AssemblyContactFailed = 97,//��װ��ϵ��ʧ��
	 TE_SDK_FileNoContact = 98,//�ļ���û����ϵ��
	 TE_SDK_UnRegonizeFile = 99,//�޷�ʶ���ļ�
	 TE_SDK_NoLdapSearchFailed = 100,//û��������ldap����
	 TE_SDK_RemoveRecordsByRecordIdFailed = 101,//ͨ����¼id�Ƴ���¼ʧ��
	 TE_SDK_GetCallRecordsFailed = 102,//��ȡͨ����¼ʧ��
	 TE_SDK_ExceedDescriptionLength = 103,//�����������ĳ���
	 TE_SDK_NoFindFile = 104, // û���ҵ��ļ�
	 TE_SDK_IDAlreadyExist = 105, //id �Ѿ�����
	 TE_SDK_AddToGroupFailed = 106,//���Ƶ�����ʧ��
	 TE_SDK_NotInConference = 107,  //���ڻ�����
	 TE_SDK_PathFormatFailed = 108, //·����ʽ����

	 TE_SDK_MAX_COUNT_FAILED


};


typedef enum tagTE_E_EVENT_CODE
{
	TE_E_EVT_LOGIN_RESULT			=	0,	/**< ��¼�¼�*/
	TE_E_EVT_CALL_RESULT			=	1,	/**< ͨ���¼�*/
	TE_E_EVT_DATA_RESULT			=	2,	/**< �����¼�*/
	TE_E_EVT_CONF_RESULT			=3,		/**< �����¼�*/
	TE_E_EVT_ENTERPRISE_RESULT  =4,  /*��ҵͨѶ¼�¼�*/
	TE_E_EVT_USER_STATUS            =5    /*�û�״̬�ı��¼�*/
}TE_E_EVENT_CODE;


typedef  TE_VOID (CALLBACK* EventCallBack)(
    TE_INT32   iEventType,    //�¼�����
    TE_VOID*   pEventBuf,     //�¼�����
    TE_UINT32  uiBufSize,      //buf����
    TE_VOID*   pUserData     //�û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
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


// ��־����
enum LOGTYPE
{
	DEBUG_TYPE				=	0, //������Ϣ
	INFO_TYPE				=	1, //һ����Ϣ
	WARN_TYPE				=	2, //����
	ERROR_TYPE				=	3  //����
};


#endif