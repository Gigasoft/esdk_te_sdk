/******************************************************************************
* Huawei Enterprise Communication API
* ecsclient.h
* Author :  Huawei
* Description :  UCSelf and UCClient related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

#include "conversation_match.h"

#define ANONYMITY_LOGIN_USER_NAME "_ANONYMITY_"
#define ANONYMITY_LOGIN_USER_PSW  ""


namespace uc {
	namespace model {

		// ! An enum
		/** \brief  permission field definition
		*/
		enum APPCLASSLAYER_API PermissionType
		{
			AbbDial,                 //缩位拨号 01 
			PwdCallLimit,
			CallLimit,               //呼叫限制 03
			LostCallNotifySms,       //未接来电转短信  04    
			BlackWhiteList,          //黑白名单 05   
			Ctd,                     //点击呼叫 06
			CallAllNewSev,           //撤销所有业务 07
			OneNum,                  //一号通  08
			CallDeflection,          //呼叫偏转 09
			RemoteReg,               //远程注册 10
			MainNum,                 //企业总机 11
			Attendant,               //话务员  12
			SecretarySev,            //秘书业务  13
			SecretaryStationSev,     //秘书台  14
			Clir,                    //主叫线识别限制  15
			ClirOverride,            //主叫线识别限制逾越  16
			Clip,                    //主叫线识别显示  17
			DisplayUsrName,          //主叫显示姓名  18
			CallerId,                //被叫来电显示  19
			AnonymousCallReject,     //匿名呼叫拒绝  20
			GroupPickUp,             //同组代答  21
			DesignatePick,           //指定代答  22
			AlarmClock,              //闹钟业务  23
			Acb,                     //自动回叫业务  24
			TakeNotes,               //  25
			CallTransfer,            //呼叫转接  26
			CallPark,                //呼叫驻留  27
			CallWait,                //呼叫等待  28
			CallHold,                //呼叫保持  29
			DisRinging,              //区别振铃  30
			BargeInsert,             //强插  31
			BargeDisconnect,         //强拆  32
			BargeOverride,           //强替  33
			BargeMonitor,            //  34
			NightService,            //夜服功能  35
			DoNotDisturb,            //免打扰  36
			ThreePartyConf,          //三方通话  37
			CallForwardUnCondi,      //无条件转移  38
			CallForwardOnBusy,       //遇忙转移  39
			CallForwardOnReply,      //无应答转移  40
			CallForwardOffline,      //离线转移  41
			ForwarVoimailBoxUnCon,   //无条件转语音邮箱  42
			ForwarVoimailBoxBusy,    //遇忙转语音邮箱  43
			ForwarVoimailBoxNoReply, //无应答转语音邮箱  44
			ForwarFaxMailBoxUnCon,   //无条件转传真  45
			ForwarOnCon,             //条件转移  46
			ForwarVoiMailBoxOffline, //离线转语音邮箱  47
			HuntingGroup,            //Hunting寻呼  48
			VipList,                 //私人列表  49
			FaxMail,                 //语音传真  50
			DataConf,                //多媒体会议  51
			FileTrans,               //文件传输  52
			VideoCall,               //视频通话功能  53
			VoiceConf,               //语音会议  54
			EnterBussBook,           //企业地址簿   55
			PersonBook,              //个人地址簿  56
			Sms,                     //短信功能  57
			Mms,                     //彩信功能  58
			IM,                      //即时消息  59
			TurnPhone,               //一键转接  60
			VoiceCall,               //音频通话功能  61
			CreateGroup,             //创建群组  62
			DeptNotificaton,         //部门通知  63
			GroupMessage,            //群发消息  64

			UnknownPermission = 200
		};

		// ! An enum
		/** \brief  playing ringtone type definition
		*/
		enum APPCLASSLAYER_API RingType
		{
			ContactRing = 0,
			GroupRing,
			InsideRing,
			OutsideRing,
			CallbackRing,
			SystemRing
		};

		/**
		* \brief OnlineConfig
		* \note The OnlineConfig class is used for reminder when user login
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API OnlineConfig
		{
		public:
			int GetOnlineTipsList(std::vector<std::string>& _list) const;
			int SaveOnlineTipsList(const std::vector<std::string>& _list) const;
		};

		/**
		* \brief RingToneConfig
		* \note The RingToneConfig class is used for playing ringtone when new call arrives
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API RingToneConfig
		{
		public:
			bool SaveContactGroupRing(
				const std::string& _id, const std::string& _ringtone) const;
			bool SaveGlobalRing(const int _type, const std::string& _ringtone) const;
			bool GetContactGroupRing(
				const std::string &_id, std::string& _ringtone) const;
			void GetGlobalRing(const int _type, std::string& _ringtone) const;
			bool RemoveContactGroupRing(const std::string& _id) const;
		};

		/**
		* \brief StringItem
		* \note The StringItem class is used for storing quick (auto) reply messages
		* \author  c00161520
		* \version 1.0.0  initial version
		*/
		typedef long long IDType;
		struct APPCLASSLAYER_API StringItem
		{
			IDType id;
			std::string content;

			StringItem() : id(0) {}
		};

		/**
		* \brief QuickReplyConfig
		* \note The QuickReplyConfig class is used for storing quick reply messages
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API ReplyConfig
		{
		public:
			int SaveQuickReplyList(const std::vector<StringItem> & _list) const;
			bool AddQuickReply(StringItem & strItem) const;
			bool UpdateQuickReply(const StringItem & strItem) const;
			bool RemoveQuickReply(const IDType & id) const;
			int ClearQuickReply() const;
			int GetQuickReplyList(std::vector<StringItem> & strItems) const;

		public:
			int SaveAutoReplyList(const std::vector<StringItem> & _list) const;
			bool AddAutoReply(StringItem & strItem) const;
			bool UpdateAutoReply(const StringItem & strItem) const;
			bool RemoveAutoReply(const IDType & id) const;
			int ClearAutoReply() const;
			int GetAutoReplyList(std::vector<StringItem> & strItems) const;
		};

		/**
		* \brief SimpleConfig
		* \note The SimpleConfig class is used for UI to store simple key/value pair config
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API SimpleConfig
		{
		public:
			bool GetUserConfig(
				const std::string & _strkey, std::string & _strValue) const;
			bool SaveUserConfig(
				const std::string & _strkey, const std::string & _strValue) const;
		};

		/**
		* \brief   用户自定义状态
		* \note    目前支持忙碌和离开两个大类，小类别用户自己定义
		* \author  liwenwqing 217212 20121226
		* \version 1.0.0  initial version
		*/
		typedef long long UserDefineStateID;
		struct APPCLASSLAYER_API UserDefineStateDateType
		{
			UserDefineStateID userDefineStateId;  //主键，递增
			std::string strParentState;           //自定义状态所属的大类，目前支持忙碌和离开两个大类 liwenwqing 217212 20121226
			std::string strChildStateContent;     //用户自定义状态内容
		};

		class APPCLASSLAYER_API UserDefineStateConfig
		{
		public:
			/**
			*
			* 函数作用：增加一个用户自定义状态
			* 参数    ：
			*          [out]UserDefineStateId_ 新增加的状态ID值，
			*               在数据库中是自增的主键
			*          [in ]_strParentState 父状态
			*          [in ]_strStateContent 用户自定义的状态
			*
			* 返回值： ture表示插入成功，false表示插入失败
			*
			* 备注： 插入后，用户要得到刚刚插入的主键，以便删除该记录
			*
			**/
			bool AddOneUserDefineState(int &UserDefineStateId_, const std::string & _strParentState, const std::string & _strStateContent) const;

			/**
			*
			* 函数作用：通过主键（状态id）删除用户自定义状态
			* 参数    ：
			*          [in ]_userDefineStateId 状态id，在数据库中是自增的
			*
			* 返回值： ture表示删除成功，false表示删除失败
			*
			*/
			bool DeleteOneUserDefineState(const UserDefineStateID _userDefineStateId) const;

		};


		/**
		* \brief profile of current user
		* \note get value from ecs::ecsdata::UserProfile
		* \author  c00161520
		* \version 1.0.0  initial version
		*/
		struct APPCLASSLAYER_API SelfProfile
		{
			std::string profilepath_;       //!< data path
			std::string portaladdr;         //!< Personal PORTAL address
			std::string confportal;         //!< Main conf PORTAL address

			std::map<std::string, std::string> pluginconfigs_;  //plugin params fetched from the server

			bool bPhoneJoint;
			bool bInputStatus; //!< Whether you notify your input status

			//00208227：联系人、群组最大数量限制初始化分别为 1000、100
			SelfProfile() 
				: bPhoneJoint(false), bInputStatus(false)
			{}
			~SelfProfile() {}
		};

		/**
		* \brief vip list item
		* \note get value from ecs::ecsdata::UserProfile
		* \author  c00161520
		* \version 1.0.0  initial version
		*/
		struct APPCLASSLAYER_API PrivateListItem
		{
			std::string bindNo;   //<! bind number
			std::string name;     //<! vip name
			std::string reserve;  //<! not used
		};

		/**
		* \brief UCSelf
		* \note The UCSelf class is the Self detailed information manipulation class
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API UCSelf
		{
		public:
			enum PubContactInfoType
			{
				Availability,
				CustomStatusDesc,
				Position, 
				Location, 
				AVTool, 
				Signature,
				HeadImage,
				CallDeviceDesc,
				Invalid,

				/* begin:modified by 00208227 2013/07/9 Reason:添加枚举值 annotate for eSpace for TP */
				SelfName,
				SelfNumber1, 
				SelfNumber2, 
				SelfNumber3, 
				SelfAddress,
				SelfEmail,
				SelfRemark,
				SelfLocalIpAddr,
				SelfPort,
				/* end:modified by 00208227 2013/07/9 Reason:添加枚举值 annotate for eSpace for TP */
			};

			virtual ~UCSelf()
			{
			}

			virtual bool Init() = 0;

			virtual bool Uninit() = 0;

			/**
			* \brief Judge if we have the specified permission
			* \param[in]  permission type
			* \param[out] N/A
			* \return  true:  has permission ; false: Otherwise 
			*/
			virtual bool HasPermission(PermissionType _type) = 0;

			/**
			* \brief Publish self information.
			*        Include status/signature/headimage etc.
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool PublishSelfInformation(const std::map<PubContactInfoType, std::string>& _values) = 0;

			/**
			* \brief Sync Self information from local db.
			*        Include status/signature/head image etc.
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool RefreshSelfInfo() = 0;

			/**
			* \brief Get current user profile value
			* \param[in]  
			* \param[out] _profile: user profile
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool RefreshSelfProfile() = 0;
			virtual const SelfProfile & GetProfile() = 0;
			virtual std::string GetProfilePath() const = 0;  /*< assign user profile storage path*/

		public:
			uc::model::Contact selfInfo;  /*!< Self detailed information*/
			uc::model::ContactAvailability selfStatus;  /*!< Self status */
			std::string selfStatusDesc;   /*!< Self status description */
			std::string localIp;
			std::string localPort;

			OnlineConfig onlinecfg_;     /*!< online tips config*/
			RingToneConfig ringtonecfg_; /*!< ring tone of incoming call config*/
			ReplyConfig quickreplycfg_; /*!< quick reply config*/
			SimpleConfig simplecfg_;     /*< value/pair simple config*/ 
			UserDefineStateConfig userDefineStateConfig_; /**/
		};

		/**
		* \brief LoginListItem
		* \note The LoginListItem struct represents user login information;
		* \author  c00161520
		* \version 1.0.0  initial version
		*/
		struct APPCLASSLAYER_API LoginListItem
		{
			std::string account;  /*< login account */
			std::string password; /*< login password */
			std::string datetime; /*< login date and time */
			bool rememberPwd;
			bool autoLogin;

		};

		/**
		* \brief SystemConfig
		* \note The SystemConfig class is used for UI to store login list
		* \author  c00161520
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API SystemConfig
		{
		public:
			bool Initilize() const;
			bool Finalize() const;

			int GetLoginList(std::vector<LoginListItem> & items) const;
			bool UpdateLoginList(
				const std::string & account, const std::string & password, 
				bool rememberPwd, bool autoLogin) const;
			bool UpdateRememberPwd(const std::string & account, bool rememberPwd) const;
			bool UpdateAutoLogin(const std::string & account, bool autoLogin) const;
			bool DeleteAccount(const std::string & account) const;

			bool GetSysConfig(
				const std::string & _strkey, std::string & _strValue) const;
			bool SaveSysConfig(
				const std::string & _strkey, const std::string & _strValue) const;
		};


		/**
		* \brief UCClient
		* \note The UCClient class is the basis for all Huawei UC2.0 API functionality
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API UCClient
		{
		public:
			enum LicenseState
			{
				LicenseTypeGetFailed,
				LicenseTypeInvalid,
				LicenseApplyFailed,   
				LicenseRefreshFailed
			};
			enum SignInState
			{
				Client_Uninited,
				Client_SignedFailed,
				Client_SigningIn,
				Client_SignedIn,
				Client_KickedOut,
				Client_Invalid
			};

			enum NetAddressBookType
			{
				NetAddressBook_FTPS,
				NetAddressBook_LDAPS,
				NetAddressBook_Invalid
			};

			UCClient();
			virtual ~UCClient();

			/**
			* \brief Initialize the uc system
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool Init() = 0;

			/**
			* \brief Initialize the uc system
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool UnInit() = 0;

			/**
			* \brief Sign in the uc system
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool SignIn() = 0;

			/**
			* \brief Sign Out the uc system
			* \param[in]  cancel login or logout
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool SignOut(bool bCancelLogin = false) = 0;

			virtual bool ChangePassword(const uc::model::PasswordWrapper &oldPassword,
                                        const uc::model::PasswordWrapper &newPassword,
                                        const std::string &server) = 0;

			/**
			* \set the srtp and bfcp values
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  Success ; false: Failed 
			*/
			virtual bool SetProfileParam() = 0;
			virtual bool SetSeesionTimer(bool bSupportTimer) = 0;
			virtual bool SupportSessionTimerConfig() = 0;

			virtual uc::model::UCClient::NetAddressBookType GetCurrentNetAddressBookType() = 0;
			virtual void SetNetAddressBookType(uc::model::UCClient::NetAddressBookType netAddressbookType) = 0;


			virtual void SetBatchUpdateMark(bool bStart) = 0;

			virtual void GetBatchUpdateContact(std::vector<uc::model::Contact> &contactList) = 0;

			virtual void ClearBatchContactCache() = 0;

			virtual void StartBatchUpdate() = 0;
			/**
			* \brief Get the UC client class instance
			* \param[in]  N/A
			* \param[out] N/A
			* \return  UCClient 
			*/
			static UCClient* GetClient();

		public:
			uc::model::UCSelf* Self;     /*!< Self privacy */
			uc::model::ContactMgr* ContactManager;   /*!< Personal addressbook manager*/
			uc::model::ContactSubscription* ContactSubManager;  /*!< Contact presence subscription manager*/

			uc::model::device::DeviceMgr* DeviceManager;   /*!< Audio/Video device manager*/

			uc::model::conversation::ConversationMgr* ConvManager;  /*!< IM/Call/Conference conversation manager*/
			uc::model::conversation::ConversationMatch* ConvMatch;

			uc::model::SignInConfig SignConfig;  /*!< Sign in param configuration*/
			uc::model::SystemConfig SysConfig; /*!< System config interface */

			uc::model::conference::ConferenceMgr* ConfManager; /*!< Conference manager */
			uc::model::EntAddrbookMgr EntAddrbookManager_;  /*!< Enterprise addressbook manager*/
			uc::model::LdapMgr* LdapManager;

			/**
			* \brief client signin result notify Signal
			*        UI need to implement has_slots<> and connect to the signal.
			*        Like this:  void OnStateChanged(uc::model::UCClient::SignInState _state, std::string);
			* \param[in]  N/A
			* \param[out] N/A
			* \return   
			*/

			sigslot::te_signal2<LicenseState,std::string> LicenseStateNotify_;

			sigslot::te_signal2<SignInState, std::string> SignInNotify_;
			sigslot::te_signal1<bool> SessionTimerNotify_;
            
            sigslot::te_signal1<bool> ChangePasswordNotify_;

			sigslot::te_signal1<bool> ADCertificationResultNotify_;

			sigslot::te_signal0<> AudioDeviceChangeNotify_;
			sigslot::te_signal0<> VideoDeviceChangeNotify_;

			sigslot::te_signal1<NetAddressBookType> NetAddressBookTypeNotify_;
			sigslot::te_signal0<> BatchUpdateContact_;  // ldap批量刷新联系人
		};

		static const std::string SIGNINFAIL_AUTH = "signin_fail_auth";
		static const std::string SIGNINFAIL_CER_VALID_FAILED = "signin_fail_cer";
		static const std::string SIGNINFAIL_REGISTER = "register_failed";

		static const std::string SIGNINFAIL_CONTACT = "contact";
		static const std::string SIGNINFAIL_SIP = "sip";
		static const std::string SIGNINFAIL_TIMEOUT = "timeout";

		static const std::string SIGNOUT_OK = "signout";

		static const std::string SIGNINFAIL_NOIP = "noip";
		static const std::string SIGNINFAIL_HASIP = "hasip";


	}//namespace model
}//namespace uc