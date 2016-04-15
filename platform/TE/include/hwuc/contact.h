/******************************************************************************
* Huawei Enterprise Communication API
* contact.h
* Author :  Huawei
* Description :  Contact and ContactMgr related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma  once

namespace uc
{
	namespace model
	{

		class Group;
		class CustomGroup;

		// ! An enum
		/** \brief  conversation type definition
		*/
		enum APPCLASSLAYER_API SessionType
		{
			InstantMessage = 1,
			AudioVideo,
		};

		// ! An enum
		/** \brief  addressbook search field definition
		*/
		enum SearchFields
		{
			AddrSearch_Uri = 0,
			AddrSearch_Account,
			AddrSearch_StaffNo,
			AddrSearch_Name,
			AddrSearch_NickName,
			AddrSearch_HomePhone,
			AddrSearch_OfficePhone,
			AddrSearch_Mobile,
			AddrSearch_OtherPhone,
			AddrSearch_Address,
			AddrSearch_Email,
			AddrSearch_Duty,
			AddrSearch_Fax,
			AddrSearch_DeptName,
			AddrSearch_All,
		};

		// ! An enum
		/** \brief  addressbook search options
		*/
		enum SearchOptions
		{
			MatchWholeWords,
			FuzzyMatch,
		};

		// ! An enum
		/** \brief  Contact login device type
		*/
		const std::string CONTACT_PC_DEVICE = "p";
		const std::string CONTACT_MOBILE_DEVICE = "m";


		/**
		* \brief Contact
		* \note The Contact class is the detailed user information class
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API Contact
		{
		public:
			Contact():flow_(0){}
			/**
			* \brief Modify contact
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool Modify() const;

			/**
			* \brief Get user self define head image
			* \param[in]  N/A
			* \param[out] N/A
			* \return  head image file path
			*/
			std::string GetHeadImagePath(bool grey = false) const;

			/**
			* \brief Move Contact from one group to another
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool MoveToGroup(const uc::model::Group& _src, const uc::model::Group& _target);

			/**
			* \brief Add Contact to a group
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool AddToGroup(const uc::model::Group& _target) const;

			/**
			* \brief Remove Contact from a group
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool RemoveFromGroup(const uc::model::Group& _target) const;

			/**
			* \brief Judge if we can started related session
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool CanStartSession(SessionType _type);

			/**
			* \brief Judge if we can move Contact from one group to another
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool CanMoveToGroup(const uc::model::Group& _src, const uc::model::Group& _target);

			/**
			* \brief query custom groups that this contact belongs to
			* \param[in]  N/A
			* \param[out] _groups: custom groups
			* \return  number of groups
			*/
			int GetCustomGroups(std::vector<uc::model::CustomGroup>& _groups);


			/*******************************************************************************
			* 函数名称 : GetCustomGroupsByIndex
			* 函数描述 : 根据索引顺序获取一个联系人所属的分组信息
			* 输入参数 : N/A
			* 输出参数 : std::vector<uc::model::CustomGroup>& _groups
			* 返 回 值 : 分组个数
			* 其他说明 : N/A
			* 修改历史 : 2013-09-24    1.0.0   w00221920
			*  1.日    期 : 2013-09-24
			*    作    者 : w00221920
			*    修改内容 : 初始版本
			*******************************************************************************/
			int GetCustomGroupsByIndex(std::vector<uc::model::CustomGroup>& _groups);

		public:
			std::string id_;        //!< id
			std::string uri_;       //!< sip uri
			std::string ucAcc_;     //!< account  
			std::string staffNo_;   //!< staff no

			std::string name_;      //!< name
			std::string nickName_;  //!< nick name

			std::string qpinyin_;   //!< name fullpinyin
			std::string spinyin_;   //!< name simplepinyin

			std::string homePhone_;   //!< home phone
			std::string officePhone_; //!< office phone
			std::string mobile_;      //!< mobile phone
			std::string otherPhone_;  //!< other phone
			std::string address_;     //!< address

			std::string email_;     //!< email
			std::string duty_;      //!< duty
			std::string fax_;       //!< fax
			std::string gender_;    //!< gender

			std::string corpName_;  //!< enterprise name
			std::string deptName_;  //!< dept name
			std::string webSite_;   //!< web site
			std::string desc_;      //!< description
			std::string zip_;       //!< zip

			std::string signature_; //!< signature
			std::string imageID_;   //!< head image id
			std::string position_;  //!<
			std::string location_;  //!<
			std::string tzone_;     //!< contact time zone
			std::string avtool_;    //!< avaliable device (mic/speaker/camera)
			std::string device_;    //!< contact device type
			std::string terminalType_; //!< contact type
			int flow_;              //!< mark contact status in the group
		};

		/**
		* \brief ContactMgr
		* \note The ContactMgr class is the private contact collection manager class.
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API ContactMgr
		{
		public:
			typedef std::vector<Contact> _Contacts;

			virtual ~ContactMgr() {}

			virtual bool Init() = 0;
			virtual bool Uninit() = 0;

			virtual bool AddCustomGroup(CustomGroup& _grp) = 0;

			virtual bool RemoveCustomGroup(const CustomGroup& _grp) = 0;

			virtual bool RefreshContactByUri(const std::string& _uri, Contact& _contact) = 0;
			virtual bool RefreshContactByAccount(const std::string& _acc, Contact& _contact) = 0;
			virtual bool RefreshContactById(const std::string& _id, Contact& _contact) = 0;

			virtual bool RemoveContactById(const std::string& _id) = 0;
			//单个删除联系人，在关系已删除的前提下，只做删除联系人用
			virtual bool RemoveContact(Contact &_contact) = 0;
			//在对应的群组下批量删除选中的联系人关系，不删除联系人
			virtual bool RemoveContactByGroup(std::map<int, std::vector<Contact> > &_contactsMap ) = 0;

			// query local only
			virtual bool HasContact(const std::string& uri) = 0;
			virtual bool HasContactByUri(const std::string& uri) = 0;
			virtual bool HasContactByAccount(const std::string& account) = 0;
            virtual bool HasContactById(const std::string& id) = 0;
			//Begin Added By w00221920 2013/07/03 Reason: 通过名字查询是否有联系人存在 eSpace for TP V100R001C01
			virtual bool HasContactByName(const std::string& name) = 0;
			//End   Added By w00221920 2013/07/03 Reason: 通过名字查询是否有联系人存在 eSpace for TP V100R001C01

			virtual bool HasContactByDN(const std::string& dn) = 0;

			virtual bool HasContactByNameAndDN(const std::string& name,const std::string& dn) = 0;

			virtual bool HasContactByNameAndAccountAndDN(const std::string& name,const std::string& account,const std::string& dn) = 0;

			//Begin Added By w00221920 2013/07/03 Reason: 通过名字查询是否有联系人存在 eSpace for TP V100R001C01
			virtual bool GetContactByName(const std::string& name, Contact& _contact) = 0;
			//End   Added By w00221920 2013/07/03 Reason: 通过名字查询是否有联系人存在 eSpace for TP V100R001C01

			virtual bool GetContactByUri(const std::string& _uri, Contact& _contact, bool refresh = false) = 0;
			virtual bool GetContactByAccount(const std::string& _acc, Contact& _contact) = 0;
			virtual bool GetContactById(const std::string& _id, Contact& _contact) = 0;
			virtual bool GetContactByPhoneNum(const std::string& _phonenum, Contact& _contact) = 0;
            virtual bool GetContactByNameAndAccount(const std::string& _name, std::string& _acc, Contact& _contact) = 0;

			virtual bool GetContactByDN(const std::string& _dn, Contact& _contact) = 0;

			virtual bool GetContactByNameAndDN(const std::string& _name,const std::string& _dn, Contact& _contact) = 0;
			virtual bool GetContactByNameAndAccountAndDN(const std::string& _name,const std::string& _account,const std::string& _dn, Contact& _contact) = 0;

			virtual bool SearchContact(const std::string& _condition, SearchFields _field,
				SearchOptions _options, _Contacts& _contactlist) = 0;
			virtual	bool InitMemUserDB() = 0;

			virtual bool AddBatchContactsAndCustomInfo(const std::string& CustomName, const std::vector<Contact>& Contacts) = 0;

			virtual bool GetAllContactlist(std::vector<Contact>& _contactlist) = 0;

			virtual bool GetCustomGrouplist(std::vector<CustomGroup>& _grouplist) = 0;
            
            virtual int GetAllContactCount() = 0;

			/*******************************************************************************
			* 函数名称 : GetCustomGrouplistByIndex
			* 函数描述 : 根据索引顺序获取分组信息
			* 输入参数 : N/A
			* 输出参数 : std::vector<uc::model::CustomGroup>& _groups
			* 返 回 值 : 分组个数
			* 其他说明 : N/A
			* 修改历史 : 2013-09-24    1.0.0   w00221920
			*  1.日    期 : 2013-09-24
			*    作    者 : w00221920
			*    修改内容 : 初始版本
			*******************************************************************************/
			virtual bool GetCustomGrouplistByIndex(std::vector<CustomGroup>& _grouplist) = 0;

			virtual bool GetCustomGroupById(const std::string& _id, CustomGroup& _group) = 0;

			//Begin Added By w00221920 2013/07/03 Reason: 通过群组名称获取群组信息 eSpace for TP V100R001C01
			virtual bool GetCustomGroupByName(const std::string& _name, CustomGroup& _group) = 0;
			//End   Added By w00221920 2013/07/03 Reason: 通过群组名称获取群组信息 eSpace for TP V100R001C01

			//Begin Added By w00221920 2013/07/04 Reason: 通过群组名查询群组是否存在 eSpace for TP V100R001C01
			virtual bool HasCustomGroupByName(const std::string& _name) = 0;
			//End   Added By w00221920 2013/07/04 Reason: 通过群组名查询群组是否存在 eSpace for TP V100R001C01

			/**
			* \brief 获取网络地址本所有联系人列表 z00220320
			* \param[in]  N/A
			* \param[out] std::vector<Contact>& _contactlist
			* \return  0:  success ; 1: failed; 2: failed
			*/
			virtual bool GetAllNetContactslist(std::vector<Contact>& _contactlist) = 0;
			/**
			* \brief 更新网络地址本联系人列表 z00220320
			* \param[in]  N/A
			* \param[out] std::vector<Contact>& _contactlist
			* \return  0:  success ; 1: failed; 2: failed
			*/
			virtual bool UpdateNetContactlist(std::vector<Contact>& _contactlist) = 0;
			/**
			* \brief 根据姓名判断网络地址本是否包含某联系人 z00220320
			* \param[in]  std::string _name
			* \param[out] N/A
			* \return  0:  success ; 1: failed; 2: failed
			*/
			virtual bool HasNetContactByName(std::string _name) = 0;
			/**
			* \brief 根据姓名获取网络地址本中联系人 z00220320
			* \param[in]  std::string _name
			* \param[out] Contact& _contact
			* \return  0:  success ; 1: failed; 2: failed
			*/
			virtual bool GetNetContactByName(std::string _name, Contact& _contact) = 0;
			/**
			* \brief 根据账号判断网络地址本是否包含某联系人 z00220320
			* \param[in]  std::string _name
			* \param[out] N/A
			* \return  0:  success ; 1: failed; 2: failed
			*/
			virtual bool HasNetContactByAcc(std::string _acc) = 0;
			/**
			* \brief 根据账号获取网络地址本中联系人 z00220320
			* \param[in]  std::string _acc
			* \param[out] Contact& _contact
			* \return  0:  success ; 1: failed; 2: failed
			*/
			virtual bool GetNetContactByAcc(std::string _acc, Contact& _contact) = 0;
            
            virtual bool GetNetContactByNameAndAcc(std::string _name, std::string _acc, Contact& _contact) = 0;

			virtual void ParseVcardFile(std::string filepath, std::vector<uc::model::Contact>& _contacts) = 0;


			virtual void WriteNetContactToDataBase(std::string filePath) = 0;

		public:

			sigslot::te_signal0<> NetAddressBookDownloadedNotify_;
			
			bool netAddressDownloadSucess;
			std::string enterpriseFileFullPath;

		};

		// ! An enum
		/** \brief  online status definition
		*/
		enum ContactAvailability
		{
			Offline = 0,
			Online,
			Busy,
			Hide,
			Leave,
			NoDisturb,
			InvalidStatus,
		};

		typedef std::pair<uc::model::Contact, uc::model::ContactAvailability> ContactStatus;
		/**
		* \brief Dept
		* \note The Dept class is the enterprise department class.
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API Dept
		{
		public:
		  typedef std::vector<ContactStatus> _ContactStatuses;

		  Dept():deptlevel_(0){}

		  /**
		  * \brief Search the contacts in current or its sub-branch
		  * \param[in]  N/A
		  * \param[out] N/A
		  * \return  contact list
		  */
		  bool SearchContact( int deptlevel, int offset, int count, int ordertype
			, int & recamount, _ContactStatuses & _contactlist, bool updateLocalStaffStore = true
			/*, SearchFields _field, SearchOptions _options*/) const;

		  bool SendBroadcastMessage(
			const std::string & subject, const std::string & text) const;

		  std::string deptname_;  /*!< dept name*/
		  std::string deptID_;    /*!< dept ID*/
		  std::string parentID_;  /*!< parent dept ID*/
		  int         deptlevel_; /*!< dept level*/
		};

		/**
		* \brief EntAddrbookMgr
		* \note The EntAddrbookMgr class is basis of the enterprise addressbook manager.
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API EntAddrbookMgr
		{
		public:
		  typedef std::vector<ContactStatus> _ContactStatuses;
		  typedef std::vector<Dept> _Depts;

		  EntAddrbookMgr():lastoffset_(0),recamount_(0){}
		  /**
		  * \brief Search the contacts in current enterprise addressbook
		  * \param[in]  N/A
		  * \param[out] N/A
		  * \return contact list
		  */
		  bool SearchContact(
			std::string _condition, std::string deptid, bool querysubdept
			, int offset, int count, int ordertype, int & recamount, 
			_ContactStatuses & _contactlist, int searchtype = 0, bool updateLocalStaffStore = true
			/*, SearchFields _field, SearchOptions _options*/);

		  bool SearchContactAssist(
			  std::string _condition, std::string deptid, bool querysubdept
			  , int offset, int count, int ordertype, int & recamount, 
			  _ContactStatuses & _contactlist);

		  void GetRootDept(Dept & rootDept) const;

		  /**
		  * \brief Get sub branches of the specified parent branch
		  * \param[in]  N/A
		  * \param[out] N/A
		  * \return department list
		  */
		  bool GetSubDeptList(std::string _parentId, _Depts & depts) const;

			/**
		  * \brief Get status of the enterprise staffs
		  * \param[in]  accountList:the account list
		  * \param[out] N/A
		  * \return department list
		  */
		  void GetEntStaffStatus(const std::list<std::string> &accountList) const;

		  mutable int lastoffset_;      //!< Previous unconditional search offset
		  mutable int recamount_;       //!< Previous unconditional search totalcount
		  mutable _ContactStatuses lastcache_;  //!< Previous unconditional search staff cache

		  typedef ctk::Mutex _Mutex;
		  _Mutex mtx_;
		};

	} // namespace model
} // namespace uc
