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
			//Begin Added By w00221920 2013/09/24 Reason: ��ȡ��ϵ��������ʱ������index������� eSpace for TP V100R001C00B011
			Group()
				: name_(""), id_(""), index_(0), type_(-1), readonly_(false)
				//End   Added By w00221920 2013/09/24 Reason: ��ȡ��ϵ��������ʱ������index������� eSpace for TP V100R001C00B011

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

			//Begin Added By w00221920 2013/09/24 Reason: ���Ⱥ����������߲���Ⱥ���Ч�� eSpace for TP V100R001C00B011
			unsigned int index_;
			//End   Added By w00221920 2013/09/24 Reason: ���Ⱥ����������߲���Ⱥ���Ч�� eSpace for TP V100R001C00B011

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
			* �������� : GetContactNumber
			* �������� : ��ȡһ��Ⱥ���ڵ���ϵ�˸���
			* ������� : N/A
			* ������� : N/A
			* �� �� ֵ : 0:        ����ϵ��
			����:     ��ϵ�˸���
			* ����˵�� : N/A
			* �޸���ʷ : 2013-08-13    1.0.0   w00221920
			*  1.��    �� : 2013-08-13
			*    ��    �� : w00221920
			*    �޸����� : ��ʼ�汾
			*******************************************************************************/
			int GetContactNumber();

			/*******************************************************************************
			* �������� : GroupHasContactById
			* �������� : ������ϵ��id�жϷ������Ƿ���ڸ���ϵ��
			* ������� : const std::string &cid
			* ������� : N/A
			* �� �� ֵ : 0:        �ɹ�
			����:     ʧ��
			* ����˵�� : N/A
			* �޸���ʷ : 2013-07-09    1.0.0   w00221920
			*  1.��    �� : 2013-07-09
			*    ��    �� : w00221920
			*    �޸����� : ��ʼ�汾
			*******************************************************************************/
			bool GroupHasContactById(const std::string& cid);

			/*******************************************************************************
			* �������� : GetContactListFromDBFile
			* �������� : �ӱ���user.db��ȡȺ���ڵ���ϵ��
			* ������� : N/A
			* ������� : std::vector<Contact>& _contactlist
			* �� �� ֵ : 0:        �ɹ�
			����:     ʧ��
			* ����˵�� : N/A
			* �޸���ʷ : 2013-07-09    1.0.0   w00221920
			*  1.��    �� : 2013-07-09
			*    ��    �� : w00221920
			*    �޸����� : ��ʼ�汾
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
