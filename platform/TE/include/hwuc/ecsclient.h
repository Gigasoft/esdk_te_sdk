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
			AbbDial,                 //��λ���� 01 
			PwdCallLimit,
			CallLimit,               //�������� 03
			LostCallNotifySms,       //δ������ת����  04    
			BlackWhiteList,          //�ڰ����� 05   
			Ctd,                     //������� 06
			CallAllNewSev,           //��������ҵ�� 07
			OneNum,                  //һ��ͨ  08
			CallDeflection,          //����ƫת 09
			RemoteReg,               //Զ��ע�� 10
			MainNum,                 //��ҵ�ܻ� 11
			Attendant,               //����Ա  12
			SecretarySev,            //����ҵ��  13
			SecretaryStationSev,     //����̨  14
			Clir,                    //������ʶ������  15
			ClirOverride,            //������ʶ��������Խ  16
			Clip,                    //������ʶ����ʾ  17
			DisplayUsrName,          //������ʾ����  18
			CallerId,                //����������ʾ  19
			AnonymousCallReject,     //�������оܾ�  20
			GroupPickUp,             //ͬ�����  21
			DesignatePick,           //ָ������  22
			AlarmClock,              //����ҵ��  23
			Acb,                     //�Զ��ؽ�ҵ��  24
			TakeNotes,               //  25
			CallTransfer,            //����ת��  26
			CallPark,                //����פ��  27
			CallWait,                //���еȴ�  28
			CallHold,                //���б���  29
			DisRinging,              //��������  30
			BargeInsert,             //ǿ��  31
			BargeDisconnect,         //ǿ��  32
			BargeOverride,           //ǿ��  33
			BargeMonitor,            //  34
			NightService,            //ҹ������  35
			DoNotDisturb,            //�����  36
			ThreePartyConf,          //����ͨ��  37
			CallForwardUnCondi,      //������ת��  38
			CallForwardOnBusy,       //��æת��  39
			CallForwardOnReply,      //��Ӧ��ת��  40
			CallForwardOffline,      //����ת��  41
			ForwarVoimailBoxUnCon,   //������ת��������  42
			ForwarVoimailBoxBusy,    //��æת��������  43
			ForwarVoimailBoxNoReply, //��Ӧ��ת��������  44
			ForwarFaxMailBoxUnCon,   //������ת����  45
			ForwarOnCon,             //����ת��  46
			ForwarVoiMailBoxOffline, //����ת��������  47
			HuntingGroup,            //HuntingѰ��  48
			VipList,                 //˽���б�  49
			FaxMail,                 //��������  50
			DataConf,                //��ý�����  51
			FileTrans,               //�ļ�����  52
			VideoCall,               //��Ƶͨ������  53
			VoiceConf,               //��������  54
			EnterBussBook,           //��ҵ��ַ��   55
			PersonBook,              //���˵�ַ��  56
			Sms,                     //���Ź���  57
			Mms,                     //���Ź���  58
			IM,                      //��ʱ��Ϣ  59
			TurnPhone,               //һ��ת��  60
			VoiceCall,               //��Ƶͨ������  61
			CreateGroup,             //����Ⱥ��  62
			DeptNotificaton,         //����֪ͨ  63
			GroupMessage,            //Ⱥ����Ϣ  64

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
		* \brief   �û��Զ���״̬
		* \note    Ŀǰ֧��æµ���뿪�������࣬С����û��Լ�����
		* \author  liwenwqing 217212 20121226
		* \version 1.0.0  initial version
		*/
		typedef long long UserDefineStateID;
		struct APPCLASSLAYER_API UserDefineStateDateType
		{
			UserDefineStateID userDefineStateId;  //����������
			std::string strParentState;           //�Զ���״̬�����Ĵ��࣬Ŀǰ֧��æµ���뿪�������� liwenwqing 217212 20121226
			std::string strChildStateContent;     //�û��Զ���״̬����
		};

		class APPCLASSLAYER_API UserDefineStateConfig
		{
		public:
			/**
			*
			* �������ã�����һ���û��Զ���״̬
			* ����    ��
			*          [out]UserDefineStateId_ �����ӵ�״̬IDֵ��
			*               �����ݿ���������������
			*          [in ]_strParentState ��״̬
			*          [in ]_strStateContent �û��Զ����״̬
			*
			* ����ֵ�� ture��ʾ����ɹ���false��ʾ����ʧ��
			*
			* ��ע�� ������û�Ҫ�õ��ող�����������Ա�ɾ���ü�¼
			*
			**/
			bool AddOneUserDefineState(int &UserDefineStateId_, const std::string & _strParentState, const std::string & _strStateContent) const;

			/**
			*
			* �������ã�ͨ��������״̬id��ɾ���û��Զ���״̬
			* ����    ��
			*          [in ]_userDefineStateId ״̬id�������ݿ�����������
			*
			* ����ֵ�� ture��ʾɾ���ɹ���false��ʾɾ��ʧ��
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

			//00208227����ϵ�ˡ�Ⱥ������������Ƴ�ʼ���ֱ�Ϊ 1000��100
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

				/* begin:modified by 00208227 2013/07/9 Reason:���ö��ֵ annotate for eSpace for TP */
				SelfName,
				SelfNumber1, 
				SelfNumber2, 
				SelfNumber3, 
				SelfAddress,
				SelfEmail,
				SelfRemark,
				SelfLocalIpAddr,
				SelfPort,
				/* end:modified by 00208227 2013/07/9 Reason:���ö��ֵ annotate for eSpace for TP */
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
			sigslot::te_signal0<> BatchUpdateContact_;  // ldap����ˢ����ϵ��
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