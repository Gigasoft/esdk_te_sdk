/******************************************************************************
* Huawei Enterprise Communication API
* group.h
* Author :  Huawei
* Description :  Group related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

#include "SdkDataType.h"


namespace uc
{
	namespace model
	{

		class Contact;

		// ! An enum
		/** \brief  group type definition
		*/
		enum APPCLASSLAYER_API GroupType
		{
			CustomGroupType,
		};

		/**
		* \brief Group
		* \note The Group class is the basis of different group.
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API Group
		{
		public:
			//Begin Added By w00221920 2013/09/24 Reason: 获取联系人所属组时，根据index排序分组 eSpace for TP V100R001C00B011
			Group()
				: name_(""), id_(""), index_(0), type_(-1), readonly_(false)
				//End   Added By w00221920 2013/09/24 Reason: 获取联系人所属组时，根据index排序分组 eSpace for TP V100R001C00B011

			{
			}

			virtual ~Group()
			{
			}

			/**
			* \brief Remove contact from current group(custom group/fixed group)
			* \param[in]  Contact
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			virtual bool RemoveContact(const Contact& _contact) const = 0;

			virtual bool RemoveContacts(const std::vector<uc::model::Contact>& _contacts) const = 0;
			/**
			* \brief Modify group(custom group/fixed group) name
			* \param[in]  Contact
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			virtual bool Rename(const std::string& _name) = 0;

			/**
			* \brief Get group(custom group/fixed group) member list
			* \param[in]  N/A
			* \param[out] Contact list
			* \return  true:  success ; false: failed
			*/
			virtual bool GetContactlist(std::vector<Contact>& _contactlist) = 0;

		public:
			std::string name_;  /*!< group name*/
			std::string id_;    /*!< group id*/

			//Begin Added By w00221920 2013/09/24 Reason: 添加群组索引，提高查找群组的效率 eSpace for TP V100R001C00B011
			unsigned int index_;
			//End   Added By w00221920 2013/09/24 Reason: 添加群组索引，提高查找群组的效率 eSpace for TP V100R001C00B011

			int type_;          /*!< group type*/
			bool readonly_;     /*!< if group is readonly*/
		};

		/**
		* \brief CustomGroup
		* \note The CustomGroup class is private group create by user.
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API CustomGroup: public Group
		{
		public:
			CustomGroup()
			{
				type_ = CustomGroupType;
				indexno_ = -1;
			}

			virtual bool AddContact(uc::model::Contact& _contact);

			virtual bool RemoveContact(const uc::model::Contact& _contact) const;

			virtual bool RemoveContacts(const std::vector<uc::model::Contact>& _contacts) const;
			virtual bool Rename(const std::string& _name);
			virtual bool GetContactlist(std::vector<Contact>& _contactlist);

			/*******************************************************************************
			* 函数名称 : GetContactNumber
			* 函数描述 : 获取一个群组内的联系人个数
			* 输入参数 : N/A
			* 输出参数 : N/A
			* 返 回 值 : 0:        无联系人
			其他:     联系人个数
			* 其他说明 : N/A
			* 修改历史 : 2013-08-13    1.0.0   w00221920
			*  1.日    期 : 2013-08-13
			*    作    者 : w00221920
			*    修改内容 : 初始版本
			*******************************************************************************/
			int GetContactNumber();

			/*******************************************************************************
			* 函数名称 : GroupHasContactById
			* 函数描述 : 根据联系人id判断分组中是否存在该联系人
			* 输入参数 : const std::string &cid
			* 输出参数 : N/A
			* 返 回 值 : 0:        成功
			其他:     失败
			* 其他说明 : N/A
			* 修改历史 : 2013-07-09    1.0.0   w00221920
			*  1.日    期 : 2013-07-09
			*    作    者 : w00221920
			*    修改内容 : 初始版本
			*******************************************************************************/
			bool GroupHasContactById(const std::string& cid);

			/*******************************************************************************
			* 函数名称 : GetContactListFromDBFile
			* 函数描述 : 从本地user.db获取群组内的联系人
			* 输入参数 : N/A
			* 输出参数 : std::vector<Contact>& _contactlist
			* 返 回 值 : 0:        成功
			其他:     失败
			* 其他说明 : N/A
			* 修改历史 : 2013-07-09    1.0.0   w00221920
			*  1.日    期 : 2013-07-09
			*    作    者 : w00221920
			*    修改内容 : 初始版本
			*******************************************************************************/
			bool GetContactListFromDBFile(std::vector<Contact>& _contactlist);

			/**
			* \brief Move Up the CustomGroup
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool MoveUp();

			/**
			* \brief Move Down the CustomGroup
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			bool MoveDown();

		public:
			int indexno_;    /*!< group index no*/
		};
	}
}
