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
* @file  AddrContacts.cpp
* @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
* @brief address List Class
* @details 
* @author zwx283069
* @version 1.0
* @date 2015-09-18    
* @history  v1.1 2015-09-18 Init TE Desktop SDK Interface
****************************************************/
#include "stdafx.h"
#include "AddContacts.h"
#include "Log.h"
#include "LangResManager.h"
#include "eSDKTool.h"
#include "shlwapi.h"

#ifndef UCCLIENT
#define UCCLIENT() (uc::model::UCClient::GetClient())
#endif


static const  std::string ID_RECENT_CONTACT_GROUP = "1";   // �����ϵ�˷���
static const  std::string ID_MY_CONTACT_GROUP     = "2";   // �ҵ���ϵ�˷���
static const  std::string ID_DEFAULT_GROUP        = "2";   // �ҵ���ϵ�˷���

CAddrContacts::CAddrContacts()
{
	m_netAddressBookType = uc::model::UCClient::NetAddressBook_Invalid;
	m_lastSearchSeqNo = 0;
	m_pLdapSearchResult = NULL;
}

CAddrContacts::~CAddrContacts()
{
	try
	{
		delete m_pLdapSearchResult;
	}
	catch(...)
	{
	}
}

int CAddrContacts::PrepareContactInfo( TE_S_CONTACT_INFO& contact)
{
	std::wstring W_contact;
	CString T_contact;

	T_contact = contact.name;
	if(T_contact.GetLength()>TE_D_NAME_LEN)
	{
		ERROR_LOG("the contact name is too long");
		return  TE_SDK_ExceedNameLength;
	}
	if(CheckNameEmpty(contact.name))
	{
		INFO_LOG("name is empty!");
		return TE_SDK_ContactEmpty;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.name,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_NAME_LEN);

	T_contact = contact.ucAcc;
	if(T_contact.GetLength()>TE_D_NUMBER_LEN)
	{
		ERROR_LOG("the contact account is too long");
		return TE_SDK_ExceedAccountLength;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.ucAcc,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_NUMBER_LEN);

	T_contact = contact.addresssite;
	if(T_contact.GetLength()>TE_D_ADDRESS_LEN)
	{
		ERROR_LOG("the contact address is too long");
		return TE_SDK_ExceedAddressLength;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.addresssite,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_ADDRESS_LEN);

	T_contact = contact.email;
	// �ж�����Ϊ�� �� �ж�����Ƿ� �� �����б�Ϊ��
	if(CheckEmailFormat(contact.email))
	{
		INFO_LOG("Add Contacts Failed!");
		return TE_SDK_illegalEmailFormat;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.email,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_EMAIL_LEN);

	T_contact = contact.deptname;
	if(T_contact.GetLength()>TE_D_DEPARTNAME_LEN)
	{
		ERROR_LOG("the contact deptname is too long");
		return TE_SDK_ExceedDeptnameLength;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.deptname,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_DEPARTNAME_LEN);

	T_contact = contact.mobile;
	if(T_contact.GetLength()>TE_D_PHONE_LEN)
	{
		ERROR_LOG("the contact mobilephone is too long");
		return TE_SDK_ExceedMobileLength;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.mobile,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_PHONE_LEN);

	T_contact = contact.officePhone;
	if(T_contact.GetLength()>TE_D_PHONE_LEN)
	{
		ERROR_LOG("the contact officephone is too long");
		return TE_SDK_ExceedOfficePhoneLength;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.officePhone,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_PHONE_LEN);

	T_contact = contact.nickname;
	if(T_contact.GetLength()>TE_D_NAME_LEN)
	{
		ERROR_LOG("the contact nickname is too long");
		return TE_SDK_ExceedNickNameLength;
	}
	W_contact = eSDKTool::CstringToWstring(T_contact);
	strncpy(contact.nickname,eSDKTool::Unicode2Utf8(W_contact).c_str(),TE_D_NAME_LEN);

	return TE_SDK_Success;

}

int CAddrContacts::AddContact(const TE_S_CONTACT_INFO contact,const TE_CHAR* groupName)
{
	DEBUG_TRACE("");
	TE_S_CONTACT_INFO tempContact;
	//uc::model::ContactAvailability status_ = uc::model::InvalidStatus;
	if(strlen(groupName)>TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}
	tempContact = contact;
	int ret = PrepareContactInfo(tempContact);
	if(0!= ret)
	{
		return ret;
	}
	uc::model::Contact T_contact;
	uc::model::CustomGroup group;
	CString cstrAccount;
	T_contact.name_ =tempContact.name;
	T_contact.address_=tempContact.addresssite;
	T_contact.email_=tempContact.email;
	T_contact.deptName_=tempContact.deptname;
	T_contact.mobile_=tempContact.mobile;
	T_contact.officePhone_=tempContact.officePhone;
	T_contact.nickName_ = tempContact.nickname;
	T_contact.ucAcc_ = tempContact.ucAcc;
	cstrAccount = eSDKTool::utf8_2_unicode(T_contact.ucAcc_);
	CString cstrUri = _T("sip:") + cstrAccount.Trim() +_T("@tedesktop");
	T_contact.uri_ = eSDKTool::unicode_2_utf8(cstrUri.Trim());
	if(T_contact.id_.empty())
	{
		T_contact.gender_ = eSDKTool::num2str(CONTACT_TYPE_SIP);
		if(CheckExceedLimit())
		{
			ERROR_LOG("contact has beyonded the limits");
			return TE_SDK_ExceedMaximumContacts;
		}
		if(!IsLocalContact(T_contact))//�����뱾����ͬ���˺Ų�ͬ����ʾ�Ƿ��滻
		{
			if(UCCLIENT()->ContactManager->HasContactByName(T_contact.name_))
			{
				INFO_LOG("contact whether replace");
				return TE_SDK_ContactWhetherReplace;
			}
			else
			{
				//��ȡ����
				const string strCurrentGtoup =groupName;
				if(!GetCustomGroupByName(eSDKTool::unicode_2_utf8(strCurrentGtoup.c_str()),group))
				{
					return TE_SDK_GetCustomGroupFailed;
				}

				if (!group.AddContact(T_contact))
				{
					ERROR_LOG("Add Failed!");
					return TE_SDK_AddContactFailed;
				}
				else
				{
					INFO_LOG (" You have add a contact! contact id = %s",T_contact.id_.c_str());
				}
			}
		}
		else
		{
			if(CheckHasContactByName(T_contact.name_))
			{
				INFO_LOG("Add Contacts Failed, Already has this contact!");
				return TE_SDK_ContactAlreadyExist;
			}
		}
	}
	else
	{
		return TE_SDK_IDAlreadyExist;
	}
	uc::model::Contact tmpContact;
	//std::vector<uc::model::Contact> ungroup;  // �����ķ����б�
	if(UCCLIENT()->ContactManager->GetContactByName(T_contact.name_, tmpContact))
	{
		T_contact.id_ = tmpContact.id_;
	}
	//status_ = UCCLIENT()->ContactSubManager->GetContactStatus(T_contact.uri_, T_contact.gender_);
	return TE_SDK_Success;
}

/*******************************************************************************
* �������� : CheckInputNameEmpty
* �������� : �ж���������Ϊ�գ�����ʾ��
* ������� : N/A
* ������� : N/A
* �� �� ֵ : 0:        �ɹ�
����:     ʧ��
* ����˵�� : N/A
* �޸���ʷ : 2013-06-21    1.0.0   h00220747
*  1.��    �� : 2013-06-21
*    ��    �� : h00220747
*    �޸����� : ��ʼ�汾
*******************************************************************************/
bool CAddrContacts::CheckNameEmpty(std::string strName)
{
	DEBUG_TRACE("name:%s",strName.c_str());
	// ��������
	if (strName.empty())
	{
		return TRUE;
	}
	return FALSE;
}

/*******************************************************************************
* �������� : CheckEmailFrmInvalid
* �������� : �ж������ʽ�Ƿ�
* ������� : N/A
* ������� : N/A
* �� �� ֵ : 0:        �ɹ�
����:     ʧ��
* ����˵�� : N/A
* �޸���ʷ : 2013-06-21    1.0.0   h00220747
*  1.��    �� : 2013-06-21
*    ��    �� : h00220747
*    �޸����� : ��ʼ�汾
*******************************************************************************/
bool CAddrContacts::CheckEmailFormat(std::string strEmail)
{
	DEBUG_TRACE("email:%s",strEmail.c_str());
	// ������
	if (!eSDKTool::IsValidEmailFormat(strEmail))
	{
		return TRUE;
	}
	return FALSE;
}

int CAddrContacts::RemoveContact(const TE_CHAR* contactName,const TE_CHAR* groupName)
{
	DEBUG_TRACE("name:%s",contactName);
	CString T_contactName;
	string temp;
	int i =0;

	std::wstring TempGroupName;
	T_contactName  = contactName;
	if(T_contactName.GetLength()>TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}
	uc::model::Contact contactInfo;
	uc::model::CustomGroup CurrentGroup;
	//contactInfo.id_ =contact.id;
	if(!UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(contactName),contactInfo))
	{
		return  TE_SDK_GetContactFailed;
	}

	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(groupName), CurrentGroup))
	{
		ERROR_LOG("GetCustomGroupById Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	// ��ȡ��ϵ����������
	std::vector<uc::model::CustomGroup> customGroups;
	if (!contactInfo.GetCustomGroups(customGroups))
	{
		ERROR_LOG("GetCustomGroups Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}

	std::vector<uc::model::CustomGroup>::iterator itor = customGroups.begin();
	while(itor!=customGroups.end())
	{
		temp = eSDKTool::utf8str2unicodestr(itor->name_);
		if(strcmp(groupName,temp.c_str()) == 0)
		{
			break;
		}
		itor++;
		//i++;
	}
	if(itor == customGroups.end())
	{
		return TE_SDK_GetCustomGroupFailed;
	}
	if(1 == customGroups.size())
	{
		if (!UCCLIENT()->ContactManager->RemoveContact(contactInfo))
		{
			ERROR_LOG("RemoveContactById Failed!");
			return TE_SDK_RemoveContactFailed;
		}
	}
	else
	{
		// ��ȡ��ǰ����
		if (!contactInfo.RemoveFromGroup(CurrentGroup))  // �ӷ������Ƴ�
		{
			ERROR_LOG("RemoveFromGroup Failed!");
			return TE_SDK_RemoveContactFailed;
		}
	}
	return TE_SDK_Success;
}

int CAddrContacts::CheckExceedLimit()
{
	DEBUG_TRACE("");
	std::vector<uc::model::Contact> contactlist;
	if (!UCCLIENT()->ContactManager->GetAllContactlist(contactlist))
	{
		ERROR_LOG("GetAllContactlist Failed!");
	}

	if ((unsigned int)contactlist.size() >= MAX_CONTACT_NUM)
	{
		return TRUE;
	}
	return  FALSE;
}

int CAddrContacts::IsLocalContact(uc::model::Contact& pContact)
{
	DEBUG_TRACE("");
	//�ж���ϵ���Ƿ�����ڱ��ص�ַ��
	int bIsLocal = FALSE;
	uc::model::Contact contact;
	if(UCCLIENT()->ContactManager->HasContactByName(pContact.name_))
	{
		if(UCCLIENT()->ContactManager->GetContactByName(pContact.name_, contact))
		{
			if(pContact.ucAcc_ == contact.ucAcc_)
			{
				//������ϵ��
				bIsLocal = TRUE;
			}
		}
		else
		{
			ERROR_LOG("GetContactByName FAILED!");
		}
	}
	return bIsLocal;
}

int CAddrContacts::CheckHasContactByName(std::string strName)
{
	DEBUG_TRACE("%s",strName.c_str());
	// ����
	if (UCCLIENT()->ContactManager->HasContactByName(strName))
	{
		return TRUE;
	}

	return FALSE;
}


bool CAddrContacts::GetCustomGroupByName(const string& name, uc::model::CustomGroup& group) const
{
	DEBUG_TRACE("name:%s",name.c_str());
	uc::model::UCClient *pClient = uc::model::UCClient::GetClient();
	if (NULL == pClient)
	{
		return false;
	}

	std::vector<uc::model::CustomGroup> groupList_;
	(void)pClient->ContactManager->GetCustomGrouplist(groupList_);
	std::vector<uc::model::CustomGroup>::iterator it = groupList_.begin();
	while (it != groupList_.end())
	{
		if (it->name_ == name)
			/*|| (it->name_ == "default group"*/ 
		{
			group = *it;
			return true;
		}

		it++;
	}

	return false;
}

int CAddrContacts::GetAllEnterpriseContacts(TE_S_CONTACTS_INFO* enterpriseContacts)
{
	DEBUG_TRACE("");
	std::vector<uc::model::Contact> contacts;
	std::wstring cstrName;
	std::string contactName;
	int i=0;
	if(!UCCLIENT()->ContactManager->GetAllNetContactslist(contacts))
	{
		return TE_SDK_NOGetAllNetContactsList;
	}
	enterpriseContacts->contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contacts.size());
	std::vector<uc::model::Contact>::iterator cit = contacts.begin();
	while (cit != contacts.end())
	{
		cstrName = eSDKTool::utf82unicode(contacts[i].name_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].name, contactName.c_str(), TE_D_NAME_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].ucAcc_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].ucAcc, contactName.c_str(), TE_D_NUMBER_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].address_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].addresssite, contactName.c_str(), TE_D_ADDRESS_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].mobile_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].mobile, contactName.c_str(), TE_D_PHONE_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].officePhone_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].officePhone,contactName.c_str(), TE_D_PHONE_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].email_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].email, contactName.c_str(), TE_D_EMAIL_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].deptName_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].deptname, contactName.c_str(), TE_D_DEPARTNAME_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].desc_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].description,contactName.c_str(),TE_D_DESCRIPTION_LEN);
		cstrName = eSDKTool::utf82unicode(contacts[i].nickName_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(enterpriseContacts->contact[i].nickname,contactName.c_str(),TE_D_NAME_LEN);
		//	strncpy(contact[i]., contactlist[i].name_.c_str(), TE_D_NAME_LEN);
		cit++;
		i++;
	}
	enterpriseContacts->num = i;
	return TE_SDK_Success;
}

int CAddrContacts::GetContactByName(const TE_CHAR* name,TE_S_CONTACT_INFO* contact)
{
	DEBUG_TRACE("name:%s",name);
	uc::model::Contact tmpContact;
	uc::model::ContactAvailability status_ = uc::model::InvalidStatus;
	std::wstring W_contact;
	std::string T_contact;
	if(strlen(name)>TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}
	if(UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(name), tmpContact))
	{
		ContactsTransCoding(tmpContact,*contact);
		status_ = UCCLIENT()->ContactSubManager->GetContactStatus(tmpContact.uri_, tmpContact.gender_);
		contact->status = SetContactStatus(status_);
		INFO_LOG("TE_GetContactByName success");
		return TE_SDK_Success;
	}
	else
	{
		ERROR_LOG("TE_GetContactByName failed, name:%s",name);
		return TE_SDK_GetContactFailed;
	}
}


int  CAddrContacts::ReplaceContact(TE_S_CONTACT_INFO   contact)
{
	DEBUG_TRACE("");
	uc::model::Contact tmpContact;
	uc::model::Contact contact_;  
	std::wstring W_contact;
	CString T_contact;
	std::string  name = contact.name;
	CString cstrAccount;
	if(UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(contact.name), tmpContact))
	{
		int ret = PrepareContactInfo(contact);
		if(0!= ret)
		{
			return ret;
		}
		tmpContact.name_=contact.name;
		tmpContact.address_=contact.addresssite;
		tmpContact.email_=contact.email;
		tmpContact.deptName_=contact.deptname;
		tmpContact.mobile_=contact.mobile;
		tmpContact.officePhone_=contact.officePhone;
		tmpContact.nickName_ = contact.nickname;
		tmpContact.desc_ = contact.description;
		tmpContact.ucAcc_ = contact.ucAcc;
		cstrAccount = eSDKTool::utf8_2_unicode(tmpContact.ucAcc_);
		CString cstrUri = _T("sip:") + cstrAccount.Trim() +_T("@tedesktop");
		tmpContact.uri_ = eSDKTool::unicode_2_utf8(cstrUri.Trim());
		//contact_.id_ = tmpContact.id_;
		tmpContact.Modify();

		return TE_SDK_Success;
	}

	return TE_SDK_GetContactFailed;
}

int  CAddrContacts::EditContact(TE_S_CONTACT_INFO contact)
{
	DEBUG_TRACE("");
	std::string T_ContactId;
	uc::model::Contact T_contact;
	uc::model::Contact Prev_contact;
	uc::model::Contact T_Pcontact;
	CString cstrAccount;

	T_contact.id_ = contact.id;
	T_ContactId = contact.id;
	// �༭ʱ�����Ƿ��ظ�
	if(T_ContactId.empty())
	{
		return TE_SDK_NoFindContact;
	}
	int ret = PrepareContactInfo(contact);
	if(0!= ret)
	{
		return ret;
	}

	T_contact.name_=contact.name;
	T_contact.address_=contact.addresssite;
	T_contact.email_=contact.email;
	T_contact.deptName_ = contact.deptname;
	T_contact.mobile_ = contact.mobile;
	T_contact.nickName_ = contact.nickname;
	T_contact.desc_ = contact.description;
	T_contact.officePhone_ = contact.officePhone;
	T_contact.ucAcc_ = contact.ucAcc;
	cstrAccount = eSDKTool::utf8_2_unicode(T_contact.ucAcc_);
	CString cstrUri = _T("sip:") + cstrAccount.Trim() +_T("@tedesktop");
	T_contact.uri_ = eSDKTool::unicode_2_utf8(cstrUri.Trim());
	if(!UCCLIENT()->ContactManager->GetContactById(T_contact.id_,Prev_contact))
	{
		return TE_SDK_GetContactFailed;
	}
	if(Prev_contact.name_!= T_contact.name_)	
	{
		if(!IsLocalContact(T_contact))//�����뱾����ͬ���˺Ų�ͬ����ʾ�Ƿ��滻
		{
			if(UCCLIENT()->ContactManager->HasContactByName(T_contact.name_))
			{
				return TE_SDK_ContactWhetherReplace;
			}
			else
			{
				// �༭��ϵ�ˣ�д�����ݿ�
				if (!T_contact.Modify())
				{
					ERROR_LOG("Modify Failed!");
					return TE_SDK_EditContactFailed;
				}
			}
		}
		else//������ϵ�� ��ʾ�Ѵ���
		{
			if(CheckHasContactByName(contact.name))
			{
				INFO_LOG("the local contact has already exist");
				return TE_SDK_ContactAlreadyExist;
			}
		}
	}
	else
	{
		// �༭��ϵ�ˣ�д�����ݿ�
		if (!T_contact.Modify())
		{
			ERROR_LOG("Modify Failed!");
			return TE_SDK_ModifyFailed;
		}
	}
	INFO_LOG("You have edit a contact!");	
	return TE_SDK_Success;
}

void CAddrContacts::ContactsTransCoding(uc::model::Contact&  contactlist,TE_S_CONTACT_INFO& contactsList)
{
	std::wstring W_contact;
	std::string T_contact;
	W_contact = eSDKTool::utf82unicode(contactlist.id_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.id,T_contact.c_str(),TE_D_ID_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.name_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.name, T_contact.c_str(), TE_D_NAME_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.ucAcc_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.ucAcc, T_contact.c_str(), TE_D_NUMBER_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.address_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.addresssite, T_contact.c_str(), TE_D_ADDRESS_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.mobile_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.mobile, T_contact.c_str(), TE_D_PHONE_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.officePhone_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.officePhone,T_contact.c_str(), TE_D_PHONE_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.email_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.email, T_contact.c_str(), TE_D_EMAIL_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.deptName_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.deptname, T_contact.c_str(), TE_D_DEPARTNAME_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.desc_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.description,T_contact.c_str(),TE_D_DESCRIPTION_LEN);
	W_contact = eSDKTool::utf82unicode(contactlist.nickName_);
	T_contact = eSDKTool::WSToString(W_contact);
	strncpy(contactsList.nickname,T_contact.c_str(),TE_D_NAME_LEN);
}

typedef std::map<UserKey, TE_S_CONTACT_INFO*> container_type;
typedef std::pair<const UserKey, TE_S_CONTACT_INFO* > name2Item_pair_type;

int CAddrContacts::GetContactList(TE_S_CONTACTS_INFO*  contactsList, TE_E_USEKEY_SORT_RULE sortRule)
{
	DEBUG_TRACE("");
	std::vector<uc::model::Contact> contactlist;
	TE_UINT32 i =0;
	CString strTmp;
	uc::model::ContactAvailability status_ = uc::model::InvalidStatus;
	TE_S_CONTACTS_INFO  tempcontactsList;
	std::string id_;
	std::string strName;
	bool isSelfFlag = false;
	container_type arryContainerFTI; //�����û��ļ���״̬�ּ������������user��
	if (!UCCLIENT()->ContactManager->GetAllContactlist(contactlist))
	{
		ERROR_LOG("GetAllContactlist Failed!");
		return TE_SDK_GetContactListFailed;
	}
	tempcontactsList.contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contactlist.size());
	std::vector<uc::model::Contact>::iterator cit = contactlist.begin();
	while (cit != contactlist.end())
	{
		ContactsTransCoding(contactlist[i],tempcontactsList.contact[i]);

		id_ = contactlist[i].id_;
		//��֤��ͬ�᳡����ͬ���Ͳ�ͬ���룬���ֵ�Ψһ��ʶDTS2015101908778

		strName = contactlist[i].nickName_;
		if (strName.empty())
		{
			strName = contactlist[i].name_;

		}

		if (strName.empty())
		{
			strName = contactlist[i].ucAcc_;
		}
		status_ = UCCLIENT()->ContactSubManager->GetContactStatus(cit->uri_, cit->gender_);
		UserKey userKey(sortRule, status_, i, id_, strName, isSelfFlag);
		arryContainerFTI.insert(name2Item_pair_type(userKey, &tempcontactsList.contact[i]));
		cit++;
		i++;
	}
	contactsList->contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contactlist.size());
	container_type::iterator itor = arryContainerFTI.begin();
	i = 0;
	while (itor != arryContainerFTI.end())
	{
		if(itor->second)
		{
			strncpy(contactsList->contact[i].id,itor->second->id,TE_D_ID_LEN);
			strncpy(contactsList->contact[i].name, itor->second->name, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].ucAcc, itor->second->ucAcc, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].addresssite, itor->second->addresssite, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].mobile, itor->second->mobile, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].officePhone, itor->second->officePhone, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].email, itor->second->email, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].deptname, itor->second->deptname, TE_D_NAME_LEN);
			strncpy(contactsList->contact[i].description,itor->second->description,TE_D_DESCRIPTION_LEN);
			strncpy(contactsList->contact[i].nickname,itor->second->nickname,TE_D_NAME_LEN);
			status_ = UCCLIENT()->ContactSubManager->GetContactStatus(contactlist[i].uri_, contactlist[i].gender_);
			contactsList->contact[i].status = SetContactStatus(status_);
			//free(itor->second);
			//	itor->second = NULL;

		}

		i++;
		itor++;
	}

	if(!arryContainerFTI.empty())
	{
		arryContainerFTI.clear();
	}

	contactsList->num = i;
	return TE_SDK_Success;
}


TE_E_CONTACT_AVAIL_ABILITY  CAddrContacts::SetContactStatus(uc::model::ContactAvailability status)
{
	TE_E_CONTACT_AVAIL_ABILITY ret = TE_E_CONTACT_InvalidStatus;
	switch(status)
	{
	case Offline:
		ret = TE_E_CONTACT_Offline;
		break;
	case Online:
		ret = TE_E_CONTACT_Online;
		break;
	case Busy:
		ret = TE_E_CONTACT_Busy;
		break;
	case Hide:
		ret = TE_E_CONTACT_Hide;
		break;
	case Leave:
		ret = TE_E_CONTACT_Leave;
		break;
	case NoDisturb:
		ret = TE_E_CONTACT_NoDisturb;
		break;
	default:
		ret = TE_E_CONTACT_InvalidStatus;
		break;
	}
	return ret;
}

int CAddrContacts::SearchContact(const TE_CHAR* keyword,TE_S_CONTACTS_INFO*   contactsList)
{
	DEBUG_TRACE("keyword:%s",keyword);
	std::vector<uc::model::Contact> contactlist; 
	TE_UINT32 i =0;
	int j = 0;
	std::wstring W_contact;
	std::string T_contact;
	uc::model::ContactAvailability status_ = uc::model::InvalidStatus;
	// ��ȡ����ȫ����ϵ��
	if(strlen(keyword)>=TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}

	if (!UCCLIENT()->ContactManager->GetAllContactlist(contactlist))
	{
		ERROR_LOG("GetAllContactlist Failed!");
		return TE_SDK_GetContactListFailed;
	}

	contactsList->contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contactlist.size());
	// m_strKey��ȡƥ����
	std::string utf8Key = eSDKTool::unicode_2_utf8(keyword);
	std::vector<uc::model::Contact>::iterator cit = contactlist.begin();
	while (cit != contactlist.end())
	{
		if (CAddrContacts::HasRelateInfo(*cit, utf8Key))
		{
			ContactsTransCoding(contactlist[j],contactsList->contact[i]);
			status_ = UCCLIENT()->ContactSubManager->GetContactStatus(contactlist[j].uri_, contactlist[j].gender_);
			contactsList->contact[i].status = SetContactStatus(status_);
			i++;
		}
		cit++;
		j++;
	}
	contactsList->num = i;
	return TE_SDK_Success;
}


bool CAddrContacts::HasRelateInfo(const uc::model::Contact& contact, const std::string& key)
{
	DEBUG_TRACE("");
	// ��ϵ���Լ�
	if (contact.ucAcc_ == UCCLIENT()->Self->selfInfo.ucAcc_)
	{
		return false;
	}

	// ������
	//if (contact.name_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.name_, key))
	{
		return true;
	}

	// ��ȫƴ
	//if (contact.qpinyin_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.qpinyin_, key))
	{
		return true;
	}

	// ��ƴ������ĸ
	//if (contact.spinyin_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.spinyin_, key))
	{
		return true;
	}

	// ���˺�
	//if (contact.ucAcc_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.ucAcc_, key))
	{
		return true;
	}

	// ������1
	//if (contact.mobile_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.mobile_, key))
	{
		return true;
	}

	// ������2
	//if (contact.officePhone_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.officePhone_, key))
	{
		return true;
	}

	// ������3
	//if (contact.otherPhone_.find(key.c_str()) != std::string::npos)
	if(CAddrContacts::FindNoCase(contact.otherPhone_, key))
	{
		return true;
	}

	return false;
}

bool CAddrContacts::FindNoCase(const std::string &strA,const std::string &strB)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"strA:%s,strB:%s",strA.c_str(),strB.c_str());
	DEBUG_TRACE("find no case:%s",strParameter);
	std::string str1 = StrToLower(strA);
	std::string str2 = StrToLower(strB);
	return (str1.find(str2) != string::npos);
}

std::string CAddrContacts::StrToLower(const std::string &str)
{
	DEBUG_TRACE("str:%s",str.c_str());
	std::string strTmp = str;
	(void)std::transform(strTmp.begin(),strTmp.end(),strTmp.begin(),tolower);
	return strTmp;
}

int CAddrContacts::CreateCustomGroup(const std::string& groupName)
{
	DEBUG_TRACE("group name%s",groupName.c_str());
	int iFlagName = groupName.size();
	// �п�
	if (groupName == "")
	{
		return TE_SDK_GroupNameEmpty;
	}

	// ����Ƿ񳬹��������
	if(CheckExceedCustomGroupsLimit())
	{
		return TE_SDK_ExceedGroupSum;
	}

	if(IsExistGroupFlag(eSDKTool::unicode_2_utf8(groupName.c_str())))
	{
		return TE_SDK_GroupAlreadyExist;
	}

	if(iFlagName >= TE_D_NAME_LEN )
	{
		return TE_SDK_ExceedGroupNameLength;
	}

	uc::model::CustomGroup group;

	group.name_ = eSDKTool::unicode_2_utf8(groupName.c_str());
	//	group.name_=	contactName;
	if (UCCLIENT()->ContactManager->AddCustomGroup(group))
	{
		// ��ӳɹ�
		INFO_LOG("You have add a group");

		return TE_SDK_Success;
	}
	else
	{
		ERROR_LOG("AddCustomGroup Failed!");

		return TE_SDK_AddGroupFailed;
	}
}

// �Ƿ���ڵķ���
bool CAddrContacts::IsExistGroupFlag( std::string strFlagName)
{
	DEBUG_TRACE("strFlagName:%s",strFlagName.c_str());
	std::vector<uc::model::CustomGroup> grouplist;
	if (!UCCLIENT()->ContactManager->GetCustomGrouplistByIndex(grouplist))
	{
		ERROR_LOG("GetCustomGrouplistByIndex Failed!");
	}
	std::wstring defaultgroup = LANG(CONTACTCTRL_COMMON_MYCONTACT_GROUP);
	if(eSDKTool::utf82unicode(strFlagName) == defaultgroup)
	{
		return true;
	}
	for(short i = 0 ; i < (short)grouplist.size() ; i++ ) 
	{
		if( 0 == eSDKTool::utf82unicode(grouplist[i].name_).compare(eSDKTool::utf82unicode(strFlagName)))
		{
			return true;
		}
	}
	return false;
}


int CAddrContacts::CheckExceedCustomGroupsLimit()
{
	DEBUG_TRACE("");
	// ���������
	std::vector<uc::model::CustomGroup> grouplist;
	if (!UCCLIENT()->ContactManager->GetCustomGrouplistByIndex(grouplist))
	{
		ERROR_LOG("GetCustomGrouplistByIndex Failed!");
	}
	if ( grouplist.size() >= MAX_CUSTOMGROUP_NUM + 2)
	{
		return TRUE;
	}

	return FALSE;
}

int CAddrContacts::RenameCustomGroup(const CString& groupName, std::string oldName)
{
	DEBUG_TRACE("oldName:%s",oldName.c_str());
	std::string newgroupname;
	int oldnamesize = oldName.size();
	// �п�
	if (groupName.IsEmpty() || oldName.empty())
	{
		return TE_SDK_GroupNameEmpty;
	}
	if(groupName.GetLength()>TE_D_GROUPNAME_LEN)
	{
		return TE_SDK_ExceedGroupNameLength;
	}
	if(oldnamesize>TE_D_GROUPNAME_LEN)
	{
		return TE_SDK_ExceedGroupNameLength;
	}
	if(IsExistGroupFlag(eSDKTool::unicode_2_utf8(groupName)))
	{
		return TE_SDK_GroupAlreadyExist;
	}
	uc::model::CustomGroup group;
	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(oldName.c_str()), group))
	{
		ERROR_LOG("GetCustomGroupByName Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	if (ID_RECENT_CONTACT_GROUP == group.id_ ||  ID_DEFAULT_GROUP == group.id_)
	{
		// �����ϵ�˺��ҵ���ϵ�˲�����������
		return TE_SDK_SameWithDefaultName;
	}

	if (group.Rename(eSDKTool::unicode_2_utf8(groupName)))
	{
		INFO_LOG(" You have rename a group");
		return TE_SDK_Success;
	}
	else
	{
		ERROR_LOG(" rename a group failed");
	}
	return TE_SDK_RenameCustomGroupFailed;
}

int CAddrContacts::RemoveCustomGroup(std::string strGrpName)
{
	DEBUG_TRACE("name:%s",strGrpName.c_str());
	int i =0;
	uc::model::Contact contactInfo;
	std::vector<uc::model::CustomGroup> grouplist;
	uc::model::CustomGroup ungroup;
	int grpnamesize = strGrpName.size();
	if(grpnamesize>TE_D_GROUPNAME_LEN)
	{
		return TE_SDK_ExceedGroupNameLength;
	}
	// �Ƴ�����������
	uc::model::CustomGroup group;
	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(strGrpName.c_str()), group))
	{
		ERROR_LOG("GetCustomGroupById Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	if (ID_RECENT_CONTACT_GROUP == group.id_ || ID_DEFAULT_GROUP == group.id_)
	{
		// �����ϵ�ˣ��ҵ���ϵ�˲�֧��ɾ��
		return TE_SDK_SameWithDefaultName;
	}

	// ��ȡ��ɾ������ĳ�Ա
	std::vector<uc::model::Contact> contactlist;
	if (!group.GetContactlist(contactlist))
	{
		ERROR_LOG("GetContactlist Failed!");
	}
	//�������������ϵ�ˣ���ֱ��ɾ������
	if (contactlist.size() == 0)
	{
		if (UCCLIENT()->ContactManager->RemoveCustomGroup(group))
		{
			INFO_LOG(" You have delete a group");
		}
		else
		{
			return TE_SDK_RemoveContactFailed;
		}
	}
	else // ����������ϵ�ˣ�ɾ��ʱת��
	{
		std::vector<Contact> selectRemoveContact;
		for(i=0;i<(int)contactlist.size();++i)
		{
			selectRemoveContact.push_back(contactlist[i]);
		}

		// Ĭ�Ϸ���
		if (!UCCLIENT()->ContactManager->GetCustomGroupById(ID_DEFAULT_GROUP, ungroup))
		{
			ERROR_LOG("GetCustomGroupById Failed!");
			return TE_SDK_GetCustomGroupFailed;
		}

		if (!UCCLIENT()->ContactManager->AddBatchContactsAndCustomInfo(ungroup.name_, selectRemoveContact))
		{
			ERROR_LOG("GetCustomGroupById Failed!");
			return TE_SDK_GetCustomGroupFailed;
		}

		if (UCCLIENT()->ContactManager->RemoveCustomGroup(group))
		{
			INFO_LOG(" You have delete a group");
		}
		else
		{
			return TE_SDK_RemoveContactFailed;
		}
	}
	return TE_SDK_Success;
}


void  CAddrContacts::SetImportMapArray(CMapString& mapString)
{
	DEBUG_TRACE("");
	if(!m_multimapContact.empty())
	{
		m_multimapContact.clear();
	}

	CMapString::const_iterator it = mapString.begin();
	for ( ; it != mapString.end(); ++it)
	{
		// �����ϵ�����ݱ�:����+�����ֶ�)
		(void)m_multimapContact.insert(make_pair(it->second[ci_Name], it->second) );
	}
}

int  CAddrContacts::GetCustomGroupList(TE_S_GROUPS_INFO*  groupsList)
{
	DEBUG_TRACE("");
	std::vector<uc::model::CustomGroup> groupList_;
	std::wstring W_contact;
	std::string T_contact;
	TE_UINT32 i = 0;
	if(!UCCLIENT()->ContactManager->GetCustomGrouplist(groupList_))
	{
		ERROR_LOG("GetAllContactlist Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	groupsList->groupInfo = (TE_S_GROUP_INFO*)malloc(sizeof(TE_S_GROUP_INFO)*groupList_.size());
	groupsList->num = 0;

	std::vector<uc::model::CustomGroup>::iterator cit = groupList_.begin();
	while (cit != groupList_.end())
	{
		W_contact = eSDKTool::utf82unicode(cit->name_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(groupsList->groupInfo[i].groupName, T_contact.c_str(), TE_D_NAME_LEN);
		cit++;
		i++;
	}
	groupsList->num = i;
	return TE_SDK_Success;
}

int CAddrContacts::MoveContactToGroup(const TE_CHAR* contactName,const TE_CHAR* newGroupName,const TE_CHAR* oldGroupName)
{
	DEBUG_TRACE("");
	if((strlen(contactName) == 0)||(0 == strlen(newGroupName))||(0 == strlen(oldGroupName)))
	{
		return TE_SDK_NullPtr;
	}
	if((strlen(contactName)>TE_D_NAME_LEN)||(strlen(newGroupName)>TE_D_NAME_LEN)||(strlen(oldGroupName)>TE_D_NAME_LEN))
	{
		return TE_SDK_ExceedNameLength;
	}
	uc::model::CustomGroup destGroup;
	uc::model::Contact tmpContact;
	std::vector<uc::model::Contact> contactList;
	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(newGroupName), destGroup))
	{
		ERROR_LOG("GetCustomGroupByName Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	if(!destGroup.GetContactlist(contactList))
	{
		ERROR_LOG("GetContactlist Failed!");
	}
	std::vector<uc::model::Contact>::iterator cit = contactList.begin();
	while (cit != contactList.end())
	{	
		if(strcmp(cit->name_.c_str(),contactName) == 0)
		{
			return TE_SDK_ContactAlreadyExist;
		}
		cit++;
	}
	if (!UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(contactName), tmpContact))
	{
		ERROR_LOG("GetContactByName Failed!");
		return TE_SDK_GetContactFailed;

	}
	if (!tmpContact.AddToGroup(destGroup))
	{
		ERROR_LOG("AddToGroup Failed!");
		return TE_SDK_AddToGroupFailed;
	}

	// �Ƴ���ϵ��
	uc::model::CustomGroup srcGroup;
	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(oldGroupName), srcGroup))
	{
		ERROR_LOG("GetCustomGroupByName Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	if (!srcGroup.RemoveContact(tmpContact))
	{
		ERROR_LOG("RemoveContact Failed!");
		return TE_SDK_RemoveContactFailed;
	}
	return TE_SDK_Success;
}

int CAddrContacts::CopyContactToGroup(const TE_CHAR* contactName,const TE_CHAR* groupName)
{
	DEBUG_TRACE("");
	if((strlen(contactName) == 0)||(0 == strlen(groupName)))
	{
		return TE_SDK_NullPtr;
	}
	if((strlen(contactName)>TE_D_NAME_LEN)||(strlen(groupName)>TE_D_NAME_LEN))
	{
		return TE_SDK_ExceedNameLength;
	}
	uc::model::CustomGroup destGroup;
	uc::model::Contact tmpContact;
	std::vector<uc::model::Contact> contactList;
	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(groupName), destGroup))
	{
		ERROR_LOG("GetCustomGroupByName Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	if(!destGroup.GetContactlist(contactList))
	{
		ERROR_LOG("GetContactlist Failed!");
	}
	std::vector<uc::model::Contact>::iterator cit = contactList.begin();
	while (cit != contactList.end())
	{	
		if(strcmp(cit->name_.c_str(),contactName) == 0)
		{
			return TE_SDK_ContactAlreadyExist;
		}
		cit++;
	}
	if (!UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(contactName), tmpContact))
	{
		ERROR_LOG("GetContactByName Failed!");
		return TE_SDK_GetContactFailed;
	}
	if (!tmpContact.AddToGroup(destGroup))
	{
		ERROR_LOG("AddToGroup Failed!");
		return TE_SDK_AddToGroupFailed;
	}
	return TE_SDK_Success;
}

typedef std::map<UserKey, TE_S_CONTACT_INFO*> container_type1;
typedef std::pair<const UserKey, TE_S_CONTACT_INFO* > name2Item_pair_type1;

int CAddrContacts::GetContactsInGroup(const TE_CHAR* name,const TE_E_USEKEY_SORT_RULE sortRule,TE_S_CONTACTS_INFO *contacts)
{
	DEBUG_TRACE("");
	uc::model::CustomGroup group;
	int i =0;
	CString strTmp;
	uc::model::ContactAvailability status_ = uc::model::InvalidStatus;
	std::string id_;
	std::string strName;
	bool isSelfFlag = false;
	container_type1 arryContainerFTI; //�����û��ļ���״̬�ּ������������user��
	TE_S_CONTACTS_INFO tempContact;
	if (!UCCLIENT()->ContactManager->GetCustomGroupByName(eSDKTool::unicode_2_utf8(name), group))
	{
		ERROR_LOG("GetCustomGroupByName Failed!");
		return TE_SDK_GetCustomGroupFailed;
	}
	if (ID_RECENT_CONTACT_GROUP == group.id_)
	{
		// �����ϵ�ˣ��ҵ���ϵ�˲�֧��ɾ��
		return TE_SDK_SameWithDefaultName;
	}
	std::vector<Contact> contactlist;
	if (!group.GetContactlist(contactlist))
	{
		ERROR_LOG("GetContactlist Failed!");
		return TE_SDK_GetContactFailed;
	}
	tempContact.contact = (TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contactlist.size());
	std::vector<uc::model::Contact>::iterator itor = contactlist.begin();
	for (;itor != contactlist.end(); ++itor)
	{	
		ContactsTransCoding(contactlist[i],tempContact.contact[i]);

		id_ = contactlist[i].id_;	
		//��֤��ͬ�᳡����ͬ���Ͳ�ͬ���룬���ֵ�Ψһ��ʶDTS2015101908778
		strName = contactlist[i].nickName_;

		if (strName.empty())
		{
			strName = contactlist[i].name_;

		}

		if (strName.empty())
		{
			strName = contactlist[i].ucAcc_;
		}
		status_ = UCCLIENT()->ContactSubManager->GetContactStatus(contactlist[i].uri_, contactlist[i].gender_);
		UserKey userKey(sortRule, status_, i, id_, strName, isSelfFlag);
		arryContainerFTI.insert(name2Item_pair_type1(userKey, &tempContact.contact[i]));
		i++;
	}

	contacts->contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*contactlist.size());
	container_type1::iterator cit = arryContainerFTI.begin();
	i = 0;
	while (cit != arryContainerFTI.end())
	{
		if(cit->second)
		{
			strncpy(contacts->contact[i].name, cit->second->name, TE_D_NAME_LEN);
			strncpy(contacts->contact[i].ucAcc, cit->second->ucAcc, TE_D_NAME_LEN);
			strncpy(contacts->contact[i].addresssite, cit->second->addresssite, TE_D_NAME_LEN);
			strncpy(contacts->contact[i].mobile, cit->second->mobile, TE_D_NAME_LEN);
			strncpy(contacts->contact[i].officePhone, cit->second->officePhone, TE_D_NAME_LEN);
			strncpy(contacts->contact[i].email, cit->second->email, TE_D_NAME_LEN);
			strncpy(contacts->contact[i].deptname, cit->second->deptname, TE_D_NAME_LEN);
			status_ = UCCLIENT()->ContactSubManager->GetContactStatus(contactlist[i].uri_, contactlist[i].gender_);
			contacts->contact[i].status = SetContactStatus(status_);
			/*free(itor->second);
			itor->second = NULL;*/
		}

		i++;
		cit++;
	}

	if(!arryContainerFTI.empty())
	{
		arryContainerFTI.clear();
	}

	contacts->num = i;
	return TE_SDK_Success;
}

int CAddrContacts::GetCustomGroups(const TE_CHAR* name,TE_S_GROUPS_INFO *groups)
{
	DEBUG_TRACE("");
	std::wstring cstrName;
	std::string contactName;
	std::vector<uc::model::CustomGroup> ungroup;  // �����ķ����б�
	uc::model::Contact tmpContact;

	if (!name || !groups)
	{
		return TE_SDK_NullPtr;
	}

	groups->groupInfo = NULL;
	groups->num = 0;
	//uc::model::CustomGroup group;
	int i=0;

	if(strlen(name)>=TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;
	}

	if(UCCLIENT()->ContactManager->GetContactByName(eSDKTool::unicode_2_utf8(name), tmpContact))
	{
		//CustomGroup group;
		if (!tmpContact.GetCustomGroups(ungroup)) // ����ǰ��ȡ��ϵ��ԭ�������ϵ
		{
			ERROR_LOG("GetCustomGroups Failed!");
			return TE_SDK_GetCustomGroupFailed;
		}
	}
	else
	{
		return TE_SDK_NoFindContact;
	}
	groups->groupInfo = (TE_S_GROUP_INFO*)malloc(sizeof(TE_S_GROUP_INFO)*ungroup.size());
	std::vector<uc::model::CustomGroup>::iterator itor = ungroup.begin();
	for (;itor != ungroup.end(); ++itor)
	{	
		// ��ȡ����
		uc::model::CustomGroup T_groups = *itor;
		cstrName = eSDKTool::utf82unicode(itor->name_);
		contactName = eSDKTool::WSToString(cstrName);
		strncpy(groups->groupInfo[i].groupName, contactName.c_str(), TE_D_NAME_LEN);
		i++;
	}
	groups->num = i;
	return TE_SDK_Success;
}


int CAddrContacts::ExportExcelFile(const TE_CHAR* strFilePath,const TE_S_GROUPS_INFO* groupList,const TE_UINT32 type)
{
	DEBUG_TRACE("strFilePath:%s",strFilePath);
	CString strPath;
	CString tempStrPath;
	std::string ack;
	std::string tempack;
	int index = 0;
	strPath = strFilePath;
	//�ж�·���Ƿ�Ϊ��
	if (strPath.IsEmpty())// ·��Ϊ��
	{
		return TE_SDK_illegalFileFormat;
	}
	//�ж�·���Ƿ����
	ack = strFilePath;
	index = ack.find_last_of("\\");
	if(-1 == index)
	{
		return TE_SDK_PathFormatFailed;
	}
	tempack  = ack.substr(0,index);
	tempStrPath = tempack.c_str();
	if(!PathIsDirectory(tempStrPath))
	{
		return TE_SDK_NoFindFile;
	}
	CString strPostFix = strPath.Right(POSTFIX_COUNT);
	if(0 != strPostFix.Compare(_T("lsx"))&&(0 != strPostFix.Compare(_T("xls")))  && ( 0!= strPostFix.Compare(_T("csv"))))
	{
		return TE_SDK_illegalFileFormat;
	}

	unsigned int i=0;
	uc::model::CustomGroup newGroup;
	if(!agentGroupList.empty())
	{
		agentGroupList.clear();
	}
	for(i=0;i<groupList->num;i++)
	{
		if (GetCustomGroupByName(eSDKTool::unicode_2_utf8(groupList->groupInfo[i].groupName), newGroup))
		{
			agentGroupList.push_back(newGroup);
		}
	}
	if((1 == type)&&(0!=strPostFix.Compare(_T("csv"))))
	{
		(void)::CoInitialize(NULL);
		//SendMessageMark(m_hWndParent, WM_CONTACT_EXPORTPROGRESSDLG_INIT, NULL, NULL);

		//����Excel������Excelʵ��������Excel������
		Excel::_ApplicationPtr excelApp;
		HRESULT hr = excelApp.CreateInstance("Excel.Application");//lint !e1033
		if (FAILED(hr))
		{
			// �����־��¼office�ӿڴ���ʧ�ܵĴ����� [3/2/2010 cKF12355]
			//SendMessageMark(m_hWndParent,WM_CONTACT_EXPORTPROGRESSDLG_RUNING, EXPORT_FAILED, NULL);//������ϵ��ʧ��
			return TE_SDK_CreatExcelApplicationFailed;
		}

		//��ȡExcel�������������еı�(����Ϊ*.xls)
		Excel::WorkbooksPtr workbooks = excelApp->GetWorkbooks();


		//���Excel�б�
		Excel::_WorkbookPtr workbook = workbooks->Add();
		if (workbook == NULL)
		{
			//	SendMessageMark(m_hWndParent,WM_CONTACT_EXPORTPROGRESSDLG_RUNING, EXPORT_FAILED, NULL);//������ϵ��ʧ��	
			(void)workbooks->Close();
			(void)excelApp->Quit();
			return TE_SDK_ExcelWorkbookEmpty;
		}

		//��ȡ������
		Excel::_WorksheetPtr worksheet = workbook->Worksheets->Item[1L];
		if (worksheet == NULL)
		{
			//SendMessageMark(m_hWndParent,WM_CONTACT_EXPORTPROGRESSDLG_RUNING, EXPORT_FAILED, NULL);//������ϵ��ʧ��
			CloseWorkbook(workbook, workbooks, excelApp);
			return TE_SDK_ExcelWorksheetEmpty;
		}

		// ָ��������ʽΪ�ı����������ǰ���0��ʧ
		Excel::RangePtr rangeall = worksheet->GetRows();
		rangeall->PutNumberFormatLocal(CComVariant( "@" ));

		Excel::RangePtr range = worksheet->GetCells();

		// ��ӵ�һ��
		InsertExcelHead(worksheet, range);

		// ��ʼ��Excel��д����ϵ����Ϣ
		if (!InsertExcelContactInfo(worksheet,range))
		{
			CloseWorkbook(workbook, workbooks, excelApp);
			return TE_SDK_InsertExcelContactFailed;
		}
		try
		{

			INFO_LOG(" Export contacts path:");
			(void)workbook->SaveAs(_bstr_t(strFilePath),vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, Excel::xlNoChange);
		}
		catch (_com_error& comException) 
		{
			CloseWorkbook(workbook, workbooks, excelApp);
			ERROR_LOG("%s",eSDKTool::unicode_2_utf8(comException.ErrorMessage()).c_str());
			return TE_SDK_ComError;
		}

		CloseWorkbook(workbook, workbooks, excelApp);
		//PostMessageMark(m_hWndParent, WM_CONTACT_EXPORTPROGRESSDLG_RUNING, EXPORT_SUCCESS, NULL);//������ϵ�����
		return TE_SDK_Success;
	}
	else if((2 == type)&&(0== strPostFix.Compare(_T("csv")) ))
	{
		(void)::CoInitialize(NULL);
		//SendMessageMark(m_hWndParent, WM_CONTACT_EXPORTPROGRESSDLG_INIT, NULL, NULL);

		//���ļ�
		//ʹ��STL�е�locale��ľ�̬����ָ��ȫ��locale���������·���´��ļ�ʧ�����⣻
		//ʹ�ø÷����Ժ�,cout���ܲ������趨����������������ģ�ʮ�����Σ�
		//����ķ�������Ҫ�ڻ�ԭ�����趨ǰ��cout��wcout������ģ�     
		//�ο����ϣ�http://www.cnblogs.com/kevinGaoblog/archive/2012/07/20/2601236.html
		(void)locale::global(locale(""));//��ȫ��������Ϊ����ϵͳĬ������
		ofstream saveFile;
		saveFile.open(strFilePath, ofstream::out);
		(void)locale::global(locale("C"));//��ԭȫ�������趨

		if (!saveFile.is_open())
		{
			//SendMessageMark(m_hWndParent, WM_CONTACT_EXPORTPROGRESSDLG_RUNING, EXPORT_FAILED, NULL);
			ERROR_LOG( "Export Open CSV Failed!");

			return TE_SDK_OpenCSVFailed;
		}

		// �������ͷ
		InsertCSVHead(saveFile);

		if (!InsertCSVContactInfo(saveFile))
		{
			return TE_SDK_InsertCSVContactFailed;
		}

		saveFile.close();
		//	PostMessageMark(m_hWndParent,WM_CONTACT_EXPORTPROGRESSDLG_RUNING, EXPORT_SUCCESS, NULL);//������ϵ�����
		return TE_SDK_Success;
	}
	else
	{
		return TE_SDK_ErrorFileType;
	}
}


void CAddrContacts::InsertExcelHead(Excel::_WorksheetPtr worksheet, Excel::RangePtr range)
{
	DEBUG_TRACE("");
	/*lint --e{10,40}*/

	// ��һ�в������ͷ
	const CString head = "Group,Name,Number,Email,Address,Description,Department,MobilePhone,OfficePhone,DN,Type,NickName,";//LANG(CONTACTCTRL_SELECTDLG_STC_EXPORTDLG_STANDARD_HEAD).c_str();
	std::vector<CString> strHead;
	Split(head, strHead);

	int j = 1;
	std::vector<CString>::const_iterator itIndex = strHead.begin();
	for (; itIndex != strHead.end(); ++itIndex)
	{
		worksheet->Cells->Item[1L][j] = COleVariant(*itIndex);
		range = worksheet->Cells->Item[1L][j];

		++j;
	}	
}


/**********************************************************
* description: 
��һ�� CString �ַ����ָ�󣬷���һ�� std::vector<CString> ������
�ַ����ָ������
�����ַ���Ϊ��inString = "������,����,����1,����2,����3,��������,��ַ,����,"
���������Ϊ��splitStr = [8]("������","����","����1","����2","����3","��������","��ַ","����")
* param [in ]: inString ������ַ���
* param [out]: splitStr �ֽ�����������
* return     : Tvoid
* History    :
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::Split(const CString &inString, std::vector<CString>& splitStr) const
{
	DEBUG_TRACE("");
	CString tmpString = inString;
	const int oneCharSize = 1;//һ���ַ��ĳ���

	int pos = tmpString.Find(_T(","));
	while (pos != -1)
	{
		CString str = tmpString.Left(pos);

		if (str.GetLength() > 0)
		{
			if (str[0] == '\"')
			{
				str = str.Right(str.GetLength() - oneCharSize);
			}
		}

		if (str.GetLength() > 0)
		{
			if (str[str.GetLength() - oneCharSize] == '\"')
			{
				str = str.Left(str.GetLength() - oneCharSize);
			}
		}

		tmpString = tmpString.Right(tmpString.GetLength() - (pos + oneCharSize));
		splitStr.push_back(str);

		pos = tmpString.Find(_T(","));
	}
}

/**********************************************************
* description: �ر�excel��Workbook
* param [in ]: workbook  Excel::_WorkbookPt
workbooks Excel::WorkbooksPtr
excelApp  Excel::_ApplicationPtr
* param [out]: ��
* return     : void
* History    :
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::CloseWorkbook(const Excel::_WorkbookPtr &workbook,const Excel::WorkbooksPtr &workbooks, const Excel::_ApplicationPtr &excelApp) const
{ 
	DEBUG_TRACE("");
	(void)workbook->Close();
	(void)workbooks->Close();
	(void)excelApp->Quit();
}



/**********************************************************
* description: ��Excel��д����ϵ����Ϣ
* param [in ]: 
* param [out]: worksheet ��ǰ���ָ��
range     Excel::RangePtr
* return     : TRUE�������ɹ���FALSE������ʧ��
* History    :
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::InsertExcelContactInfo(Excel::_WorksheetPtr worksheet, Excel::RangePtr range)
{
	DEBUG_TRACE("");
	int iCol = 1; //��1�п�ʼ
	int nRow = 2; //�ӵڶ��п�ʼ

	std::vector<uc::model::CustomGroup>::iterator itor = agentGroupList.begin();

	// ѭ����������
	for ( ; itor != agentGroupList.end(); ++itor)
	{
		//�ȴӷ����б��л�ȡ��ϵ���б�
		std::vector<uc::model::Contact> contactlist;
		if (!itor->GetContactlist(contactlist)) // ��ȡ���³�Ա
		{
			ERROR_LOG("GetContactlist Failed!");
		}

		//�÷���������ϵ��,�����ѭ��
		if (0 == contactlist.size())
		{
			continue;
		}

		//��Ŀ���ļ��з���д������
		std::vector<uc::model::Contact>::const_iterator contactListItor = contactlist.begin();
		for ( ; contactListItor != contactlist.end(); ++contactListItor)
		{	
			iCol = 1;//��1�п�ʼ

			std::vector<CString> contaceInfo;
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(itor->name_));                    //GroupName
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->name_));         //Name
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->ucAcc_));         //Name
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->email_));        //Email
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->address_));      //Address
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->desc_));         //Description
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->deptName_));  //officePhone
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->mobile_));       //Mobile
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->officePhone_));  //officePhone
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->webSite_));   //DN�ֶ�
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->gender_));  //���� 0,1,2
			contaceInfo.push_back(eSDKTool::utf8_2_unicode(contactListItor->nickName_));   //�����ǳ�

			//contaceInfo.push_back(StringUtility::utf8_2_unicode(contactListItor->otherPhone_));   //OtherPhone
			std::vector<CString>::const_iterator it = contaceInfo.begin();
			for (; it != contaceInfo.end(); ++it)
			{
				worksheet->Cells->Item[nRow][iCol] = COleVariant(*it);
				range = worksheet->Cells->Item[nRow][iCol];
				++iCol;
			}

			++nRow;

			// ����һ�����ȴ���
			//SendMessageMark(m_hWndParent, WM_CONTACT_EXPORTPROGRESSDLG_STEPIT, NULL, NULL);
		}
	}

	return TRUE;
}


/**********************************************************
* description: ����CSV�ļ��ĵ�һ��
* param [in ]: saveFile ������ļ�
* param [out]: ��
* return     : void
* History    :
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::InsertCSVHead(ofstream &saveFile) const
{
	DEBUG_TRACE("");
	/*lint --e{533,18}*/

	CString sHead = "Group,Name,Number,Email,Address,Description,Department,MobilePhone,OfficePhone,DN,Type,NickName,";

	sHead += _T("\n");

	const std::string head = ctk::to_str(sHead.GetString());//lint !e64

	(void)saveFile.write(head.c_str(), (streamsize)head.size());
}

/**********************************************************
* description: ��Excel��CSV�ļ��е�����ϵ����Ϣ
* param [in ]: ��
* param [out]: saveFile ������ļ�
* return     : TRUE�������ɹ���FALSE������ʧ��
* History    :
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::InsertCSVContactInfo(ofstream &saveFile)
{
	DEBUG_TRACE("");
	std::vector<uc::model::CustomGroup>::iterator GroupListItor = agentGroupList.begin();

	for (; GroupListItor != agentGroupList.end(); ++GroupListItor)
	{

		//�ȴӷ����б��л�ȡ��ϵ���б�
		std::vector<uc::model::Contact> contactlist;
		if (!GroupListItor->GetContactlist(contactlist))
		{
			ERROR_LOG("GetContactlist Failed!");
		}

		//�÷���������ϵ��
		if (0 == contactlist.size())
		{
			continue;
		}

		std::vector<uc::model::Contact>::const_iterator contactListItor = contactlist.begin();
		for ( ; contactListItor != contactlist.end(); ++contactListItor)
		{	

			/*lint -e64*/
			std::string strGroupName = ctk::to_str(eSDKTool::utf8_2_unicode(GroupListItor->name_));
			std::string strName = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->name_));
			std::string strAccount = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->ucAcc_));
			std::string strEmail = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->email_));
			std::string strAddress = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->address_));
			std::string strDescription = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->desc_));

			std::string strDeptName = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->deptName_));
			std::string strMobilePhone = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->mobile_));
			std::string strOfficePhone = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->officePhone_));
			std::string strDN= ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->webSite_));
			std::string strType = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->gender_));
			std::string strNickName = ctk::to_str(eSDKTool::utf8_2_unicode(contactListItor->nickName_));			

			std::string contentInfo = "";
			(void)(contentInfo.append("\"").append(strGroupName).append("\","));
			(void)(contentInfo.append("\"").append(strName).append("\","));
			(void)(contentInfo.append("\"").append(strAccount).append("\","));
			(void)(contentInfo.append("\"").append(strEmail).append("\","));
			(void)(contentInfo.append("\"").append(strAddress).append("\","));
			(void)(contentInfo.append("\"").append(strDescription).append("\","));

			(void)(contentInfo.append("\"").append(strDeptName).append("\","));
			(void)(contentInfo.append("\"").append(strMobilePhone).append("\","));
			(void)(contentInfo.append("\"").append(strOfficePhone).append("\","));
			(void)(contentInfo.append("\"").append(strDN).append("\","));
			(void)(contentInfo.append("\"").append(strType).append("\","));
			(void)(contentInfo.append("\"").append(strNickName).append("\","));

			(void)contentInfo.append("\n");

			(void)saveFile.write(contentInfo.c_str(), (int)contentInfo.size());

			// ����һ�����ȴ���
			//SendMessageMark(m_hWndParent, WM_CONTACT_EXPORTPROGRESSDLG_STEPIT, NULL, NULL);
		}
	}

	return TRUE;
}



/**********************************************************
* description: �߳��У������ļ�
* param [in ]: ��
* param [out]: ��
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::ImportFile(const TE_S_GROUPS_CHAIN* groupsList)
{
	DEBUG_TRACE("");
	std::vector<CString> contactMapCstring;
	std::map<long, std::vector<CString>> cmapString;
	unsigned int i=0;

	uc::model::CustomGroup newGroup;
	//	if (!GetCustomGroupByName(strLabel, newGroup))
	// ��ʼ��DB
	while(groupsList)
	{
		while(groupsList->group->contactsChain)
		{
			contactMapCstring.push_back(groupsList->group->groupName);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.name);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.ucAcc);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.email);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.addresssite);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.description);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.deptname);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.mobile);
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.officePhone);
			contactMapCstring.push_back("");
			contactMapCstring.push_back("6");
			contactMapCstring.push_back(groupsList->group->contactsChain->contactInfo.nickname);
			cmapString.insert(pair<long,std::vector<CString>>(i,contactMapCstring));
			contactMapCstring.erase(contactMapCstring.begin(), contactMapCstring.end());
			groupsList->group->contactsChain = groupsList->group->contactsChain->next;
			i++;
		}
		groupsList = groupsList->next;
	}

	SetImportMapArray(cmapString);
	//�ж�Ԥ������ļ������Ƿ����ظ����ݣ�ɾ����ϵ�����ݣ�ͬʱ�߽�����
	this->DelRepeatContactFile();

	//��ȡ�������з��ظ���ϵ�������б�����
	vector<string> localContactAcclist;
	int localContantNum = this->GetContactAcclist(localContactAcclist);

	//map<string,vector<string>> : <������������ϵ�������б�>
	map<string,vector<string>> localContactWhitGroup;
	this->GetlocalContactWithGroup(localContactWhitGroup);
	if(!m_localContactMap.empty())
	{
		m_localContactMap.clear();//����м仺�����
	}
	CMultimapContact::iterator itor = m_multimapContact.begin();
	for ( ; itor != m_multimapContact.end(); ++itor)
	{

		if ((itor->second[ci_GroupName]).IsEmpty())
		{
			itor->second[ci_GroupName] = "Unnamed Group"; // ������Ϊ��-��δ�������
		}

		// �뱾��ʱ���ظ�
		if (!this->IsFileRepeatWithlocal(itor->second, localContactWhitGroup))
		{
			vector<string>::iterator findResult = find( localContactAcclist.begin(),localContactAcclist.end(), eSDKTool::unicode_2_utf8((itor->second)[ci_Name]) );
			if ( findResult == localContactAcclist.end()) //û�ҵ�
			{
				++localContantNum;
				localContactAcclist.push_back(eSDKTool::unicode_2_utf8((itor->second)[ci_Name]));
			}

			if (IsContactOrGroupNumBeyondLimit(localContantNum, localContactWhitGroup))
			{
				//��ʾ����ǰ������ϵ�˻�Ⱥ�������������������
				const CString strDetailInfo ="Maximum number of contacts or groups reached.";
				//	this->SendMsgStepShowImportInfo(eSDKTool::unicode_2_utf8(itor->first), strDetailInfo);

				MoveContactDataMemoryToDb();     //��������Ҫд�����ݿ����ϵ�˱��������ݿ�
				return TE_SDK_ContactOrGroupSumBeyondLimit;
			}

			this->ImportContactNormally(itor);
		}
		else //��⵽һ���ظ�����ϵ�ˣ����������һ������ϵ�˵���ʧ�ܲ���ʾ�ظ�(�˺��ظ�)
		{
			CString strDetailInfo =  _T("");
			this->ImportProgressSetDetailInfo(err_Local, strDetailInfo);	
			const string contactName = eSDKTool::unicode_2_utf8(itor->first);
			//this->SendMsgStepShowImportInfo(contactName, strDetailInfo);
			WARN_LOG("contact  repeat:%s",contactName.c_str());
		}

	}

	MoveContactDataMemoryToDb();     //��������Ҫд�����ݿ����ϵ�˱��������ݿ�
	return TE_SDK_Success;
}


/**********************************************************
* description: �ж�Ԥ������ļ������Ƿ����ظ����ݣ�ɾ���ظ���ϵ�����ݣ�ͬʱ�߽�����
* param [in ]: ��
* param [out]: ��
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::DelRepeatContactFile()
{
	DEBUG_TRACE("");
	// ����ȷ�ϵ����� �����ڴ洢δ�ظ�����ϵ��
	CMultimapContact m_mapCheckContactResult;

	CMultimapContact::const_iterator itor = m_multimapContact.begin();
	for (; itor != m_multimapContact.end(); ++itor)
	{
		bool errFlag = false;
		CMultimapContact::const_iterator TempItor = itor; 
		for (++TempItor; TempItor != m_multimapContact.end(); ++TempItor)
		{
			// �����ȱ�ʾ�ظ�
			//��⵽һ���ظ�����ϵ��(ָ��ͬһ���飬���֣��˺ţ���ͬ����ϵ��)�����������һ������ϵ�˵���ʧ��
			if (IsRepeatContactInFile(itor->second, TempItor->second))
			{ 
				//�������ϵ���ظ���ʾ
				CString strDetailInfo =  _T("");
				ImportProgressSetDetailInfo(err_NameRepeat, strDetailInfo);	
				const string contactName = eSDKTool::unicode_2_utf8(itor->first);
				//SendMsgStepShowImportInfo(contactName, strDetailInfo);

				errFlag = true;

				break;
			}
		}

		if (!errFlag)
		{
			// ���ظ������
			(void)m_mapCheckContactResult.insert(*itor);
		}
	}
	if(!m_multimapContact.empty())
	{
		m_multimapContact.clear();
	}
	m_multimapContact = m_mapCheckContactResult;//ȥ���������ظ������ϵ��
}

/**********************************************************
* description: �ж�������ϵ�����ļ����Ƿ��ظ�������(�˺�)���鶼��ͬ�ļ�Ϊ�ظ�
* param [in ]: contact       ��ϵ�ˣ�����һ�����������ϵ�˱Ƚ�
contactBehind ��ϵ�ˣ�����һ�����������ϵ�˱Ƚ�
* param [out]: ��
* return     : TRUE,���ظ��ģ�FALSE�������ظ���
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::IsRepeatContactInFile(const std::vector<CString> &contact, const std::vector<CString> &contactBehind) const
{
	DEBUG_TRACE("");
	if ((contact[ci_GroupName] == contactBehind[ci_GroupName])&& (contact[ci_Name] == contactBehind[ci_Name]))
	{
		return TRUE;
	}

	return FALSE;
}

/**********************************************************
* description: ���ݴ������ͣ����õ�����ϵ�˵���ϸ��Ϣ�����ڽ���չʾ
* param [in ]: errType       �������ͣ�
* param [out]: strDetailInfo �������ϸ��Ϣ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::ImportProgressSetDetailInfo(const ERROR_TYPE1 errType,CString &strDetailInfo) const
{
	DEBUG_TRACE("type:%d",errType);
	strDetailInfo.Empty();

	//�����ɹ�
	if (0 == errType)
	{
		strDetailInfo="Contacts imported.";
		return;

	}

	//����ʧ�ܣ���ʾ��Ϣ
	CString strErrInfo = _T("");
	InitErrInfoByErrType(errType, strErrInfo);

	//strDetailInfo.Format("Importing failure : %s", strErrInfo.GetBuffer());
}


/**********************************************************
* description: ���ݴ������ͳ�ʼ��������Ϣ
* param [in ]: errType       ��������
* param [out]: strErrInfo    ����ľ�����Ϣ�ַ���
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::InitErrInfoByErrType(const ERROR_TYPE1 &errType, CString &strErrInfo) const
{
	DEBUG_TRACE("type:%d",errType);
	switch(errType)
	{
	case err_NameRepeat:         //��ϵ���ظ�
		{
			strErrInfo = "Duplicate contact name in the file to import.";
			break;
		}
	case err_AccountRepeat:      //��ϵ���˺��ظ�
		{
			strErrInfo = "Duplicate numbers in the file to import";
			break;
		}
	case err_Local:	             //������ϵ���뱾���ظ�
		{
			strErrInfo = "Contact already exists";
			break;
		}
	case err_GroupName:	         //����������
		{
			strErrInfo = "Group name is too long or illegal";
			break;
		}
	case err_Name:		         //��������
		{
			strErrInfo = "too long";
			break;
		} 
	case err_NoName:            //û������
		{
			strErrInfo = "The name cannot be left empty.";
			break;
		}
	case err_Account:		    //�˺ų���
		{
			strErrInfo = "Number too long or invalid format.";
			break;
		} 
	case err_NoAccount:         //�˺�Ϊ��
		{
			strErrInfo ="The number cannot be left empty.";
			break;
		}
	case err_Mobile:	        //�ֻ��������
		{
			strErrInfo = "Number 1 too long or invalid.";
			break;
		}
	case err_OfficePhone:       //�칫�������
		{
			strErrInfo = "Number 2 too long or invalid.";
			break;
		}
	case err_OtherPhone:        //��������
		{
			strErrInfo = "Number 3 too long or invalid.";
			break;
		}
	case err_Email:		        //��������
		{
			strErrInfo = "Email address too long or invalid format.";
			break;
		}
	case err_Address:           //��ַ����
		{
			strErrInfo = "Address too long.";
			break;
		}
	case err_Description:       //��������
		{
			strErrInfo = "Description too long.";
			break;
		}
	case err_CreateGroupFailed:	//������ʧ��
		{
			strErrInfo = "Failed to create the group.";
			break;
		}
	case err_AddContactFailed:	//������ϵ��ʧ��
		{
			strErrInfo = "Failed to add the contact.";
			break;
		}
	default:                    //δ֪����
		{
			strErrInfo = "Unknown error.";
			break;
		}
	}
}

/**********************************************************
* description: ��ȡ��ϵ���ʺţ��������б�
* param [in ]: ��
* param [out]: vector<string> : <�������з��ظ���ϵ�������б�>
* return     : ���ط��ظ���ϵ�˵�����
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::GetContactAcclist(vector<string> &localContactNamelist) const
{
	DEBUG_TRACE("");
	//��ȡ��ǰ��ϵ���б�
	vector<uc::model::Contact> localContactlist;
	if (!UCCLIENT()->ContactManager->GetAllContactlist(localContactlist))
	{
		ERROR_LOG("GetAllContactlist Failed!");
	}

	//��ȡ����������ϵ������
	vector<uc::model::Contact>::const_iterator Itor = localContactlist.begin();
	for (; Itor != localContactlist.end(); ++Itor)
	{
		localContactNamelist.push_back(Itor->name_);
	}

	return (int)localContactlist.size();
}

/**********************************************************
* description: �������ȡ������ϵ��
* param [in ]: ��
* param [out]: map<string,vector<string>> : <������������ϵ������(�˺�)�б�>
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::GetlocalContactWithGroup(map<string,vector<string>> &localContactWhitGroup) const
{
	DEBUG_TRACE("");
	vector<uc::model::CustomGroup> grouplist;
	if (!UCCLIENT()->ContactManager->GetCustomGrouplistByIndex(grouplist))
	{
		ERROR_LOG("GetCustomGrouplistByIndex Failed!");
	}

	vector<uc::model::CustomGroup>::iterator grouplistItor = grouplist.begin();
	for (; grouplistItor != grouplist.end(); ++grouplistItor)
	{
		vector<uc::model::Contact> contactlist;
		if (!grouplistItor->GetContactlist(contactlist))
		{
			ERROR_LOG("GetContactlist Failed!");
			//continue;
		}

		vector<string> contactNamelist;
		vector<uc::model::Contact>::const_iterator tmpItor = contactlist.begin();
		for (; tmpItor != contactlist.end(); ++tmpItor)
		{
			contactNamelist.push_back(tmpItor->name_);
		}

		localContactWhitGroup[grouplistItor->name_] = contactNamelist;
	}
}

/**********************************************************
* description: �ж��ļ�����ϵ���뱾���ظ�
* param [in ]: contactFile  Ԥ�����ļ��У���һ����ϵ��
* param [out]: map<string,vector<string>> : <Ⱥ��������������ϵ�������б�>
* return     : TRUE,����ϵ���뱾���ظ���FALSE������ϵ�˲��뱾���ظ�
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::IsFileRepeatWithlocal(const vector<CString> &contactFile, map<string,vector<string>> &localContactWhitGroup) const
{
	DEBUG_TRACE("");
	const string groupName = eSDKTool::unicode_2_utf8(contactFile[ci_GroupName]);
	const string contactName = eSDKTool::unicode_2_utf8(contactFile[ci_Name]);
	//const string contactAccount = StringUtility::unicode_2_utf8(contactFile[ci_Account]);

	/*- ����1����鱾���Ƿ��и���ϵ�˵ķ��� */
	map<string,vector<string>>::iterator itor = localContactWhitGroup.find(groupName);
	if (itor != localContactWhitGroup.end())
	{
		/*- ����2������и���ϵ�˵ķ��飬�鿴���ظ÷������Ƿ���������ϵ�� */
		vector<string>::const_iterator contactListItor = (itor->second).begin();
		while (contactListItor != (itor->second).end())
		{
			if (contactName == *contactListItor)
			{
				/*- �������1������2�����㣬����һ���ظ���ϵ�ˣ�����TRUE */
				return TRUE;
			}

			++contactListItor;
		}

		(itor->second).push_back(contactName);
	}
	else
	{
		localContactWhitGroup[groupName].push_back(contactName);
	}

	return FALSE;
}

/**********************************************************
* description: ��ϵ�˻�Ⱥ�������������������
* param [in ]: localContantNum ������ϵ������
localContactWhitGroup ���з�����Ϣ�ı�����ϵ��
* param [out]: ��
* return     : true���������ƣ�false��û�г�������
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
bool CAddrContacts::IsContactOrGroupNumBeyondLimit(const int localContantNum,const map<string,vector<string>> &localContactWhitGroup) const
{
	DEBUG_TRACE("num:%d",localContantNum);
	if (localContantNum > MAX_CONTACT_NUM)
	{
		return true;
	}

	const unsigned int maxGroupNum = 100;
	unsigned int validGroupNum = localContactWhitGroup.size();
	if (validGroupNum > maxGroupNum)
	{
		/*֮���԰���δ���������ŵ��ϲ�if֮�У���Ϊ�����Ч�ʣ�
		ֻ�е�Ⱥ��������100��ʱ�ż����Ƿ���Ҫ��ȥ���ҵ���ϵ�ˡ����������ϵ�ˡ�*/

		unsigned int invalidGroupNum = 0;
		const string strMyContactGroup = eSDKTool::unicode_w_2_utf8(LANG(CONTACTCTRL_COMMON_MYCONTACT_GROUP));
		const string strRecContactGroup = eSDKTool::unicode_w_2_utf8(LANG(CONTACTCTRL_COMMON_RECENTCONTACT_GROUP));
		if (localContactWhitGroup.end() != localContactWhitGroup.find(strMyContactGroup))
		{
			++invalidGroupNum;
		}
		if (localContactWhitGroup.end() != localContactWhitGroup.find(strRecContactGroup))
		{
			++invalidGroupNum;
		}

		validGroupNum -= invalidGroupNum;

		if (validGroupNum > maxGroupNum)
		{
			return true;
		}
	}

	return false;
}

/**********************************************************
* description: ����ϵ�������������ݿ�
* param [in ]: ��
* param [out]: ��
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::MoveContactDataMemoryToDb()
{
	DEBUG_TRACE("");
	if(!m_multimapContact.empty())
	{
		m_multimapContact.clear();//��մ��ļ��ж�ȡ����������
	}

	map<string,vector<uc::model::Contact>>::const_iterator tmpItor = m_localContactMap.begin();
	for (;tmpItor != m_localContactMap.end(); ++tmpItor)
	{
		if (!UCCLIENT()->ContactManager->AddBatchContactsAndCustomInfo(tmpItor->first, tmpItor->second))
		{
			ERROR_LOG( "AddBatchContactsAndCustomInfo Failed!!!");
		}
	}

	m_localContactMap.clear(); //����м仺�����

	// ����Ϣ���������б�
	//PostMessageMark(ContactsCtrlModel::instance()->view_->getSafeHwnd(), WM_CONTACT_UPDATE_CONTACT_TREE, NULL, NULL);
}


/**********************************************************
* description: ����������ϵ�ˣ�ͬʱ�߽�����
* param [in ]: it ��ϵ����Ϣ����
* param [out]: ��
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::ImportContactNormally(const CMultimapContact::const_iterator &it)
{
	DEBUG_TRACE("");
	//ȡ��һ����ϵ�˵���Ϣ�����ڷָ��
	const vector<CString> splitTemp = it->second;

	vector<std::string> splitStr;
	for (size_t index = 0; index < splitTemp.size(); ++index)
	{
		const CString strInfo = splitTemp[index];
		splitStr.push_back(eSDKTool::unicode_2_utf8(strInfo));
	}

	uc::model::Contact contact;  // ��װ��ϵ�˽ṹ
	ERROR_TYPE1 errType = err_None;

	InitSetFunctionMap(); //��ʼ�� m_SetFunctionMap

	map<enum emContactInfo, SetFunction>::const_iterator itor = m_SetFunctionMap.begin();
	for ( ; itor != m_SetFunctionMap.end(); ++itor)
	{
		if (err_None == errType && itor->first < (int)splitStr.size())
		{
			errType = (this->*CAddrContacts::m_SetFunctionMap[itor->first])(contact, splitStr[itor->first]);
		}
	}

	if (err_None == errType)
	{
		errType = CheckGroupName(splitStr[ci_GroupName]);
	}

	if (err_None == errType)
	{
		m_localContactMap[splitStr[ci_GroupName]].push_back(contact);
	}

	vector<CString> DetailInfo(1, eSDKTool::utf8_2_unicode(contact.name_));
	CString strErrInfo = _T("");
	ImportProgressSetDetailInfo(errType, strErrInfo);
	DetailInfo.push_back(strErrInfo.GetString());

	// ֪ͨ�������ƶ�
	//const int isImportSuc = (errType == err_None) ? TRUE : FALSE;
	//SendMessageMark(m_hWndParent,WM_CONTACT_IMPORTPROGRESSDLG_STEPIT, (WPARAM)&DetailInfo, isImportSuc);//info,true/false
}


void CAddrContacts::InitSetFunctionMap()
{
	DEBUG_TRACE("");
	m_SetFunctionMap[ci_Name] = &CAddrContacts::ImportProgressSetName;
	m_SetFunctionMap[ci_Account] = &CAddrContacts::ImportProgressSetAccount;
	m_SetFunctionMap[ci_Email] = &CAddrContacts::ImportProgressSetEmail;
	m_SetFunctionMap[ci_Addr] = &CAddrContacts::ImportProgressSetAddress;
	m_SetFunctionMap[ci_Desc] = &CAddrContacts::ImportProgressSetDescription;
	m_SetFunctionMap[ci_DepartName] = &CAddrContacts::ImportProgressSetDeptName;
	m_SetFunctionMap[ci_Mobile] = &CAddrContacts::ImportProgressSetMobile;
	m_SetFunctionMap[ci_OfficePhone] = &CAddrContacts::ImportProgressSetOfficePhone;
	m_SetFunctionMap[ci_DN] = &CAddrContacts::ImportProgressSetDN;
	m_SetFunctionMap[ci_Type] = &CAddrContacts::ImportProgressSetType;
	m_SetFunctionMap[ci_Nickname] = &CAddrContacts::ImportProgressSetNickName;

}

/**********************************************************
* description: ��������,�����ֶβ���Ϊ��
* param [in ]: strName ����
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetName(uc::model::Contact &contact, const std::string &strName) const
{
	DEBUG_TRACE("name:%s",strName.c_str());
	if (strName.empty())
	{
		return err_NoName;
	}

	const wstring tstrName = eSDKTool::utf8_2_unicode_w(strName);
	if (tstrName.size() > MAXLEN_NAME)
	{
		contact.name_ = strName;
		return err_Name;
	}

	contact.name_ = strName;

	return err_None;
}

/**********************************************************
* description: �����˺�,�˺��ֶβ���Ϊ��
* param [in ]: strAccount �ʺ�
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetAccount(uc::model::Contact &contact, const std::string &strAccount) const
{
	DEBUG_TRACE("");
	//if (strAccount.empty())
	//{
	//	return err_NoAccount;
	//}

	const wstring tstrAccount = eSDKTool::utf8_2_unicode_w(strAccount);
	if (tstrAccount.size() > MAXLEN_ACCOUNT)
	{
		return err_Account;
	}

	contact.ucAcc_ = strAccount;
	contact.uri_ = "sip:" + strAccount + "@tedesktop";

	return err_None;
}

/**********************************************************
* description: ����Mobile
* param [in ]: strMobile Mobile
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetMobile(uc::model::Contact &contact, const std::string &strMobile) const
{
	DEBUG_TRACE("mobile:%s",strMobile.c_str());
	const wstring tstrMobile = eSDKTool::utf8_2_unicode_w(strMobile);
	if (tstrMobile.size() > MAXLEN_MOBILE)
	{
		return err_Mobile;
	}

	contact.mobile_ = strMobile;

	return err_None;
}

/**********************************************************
* description: ���ð칫����
* param [in ]: strOfficePhone
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetOfficePhone(uc::model::Contact &contact,const std::string &strOfficePhone) const
{
	DEBUG_TRACE("officephone:%s",strOfficePhone.c_str());
	const wstring tstrOfficePhone = eSDKTool::utf8_2_unicode_w(strOfficePhone);
	if (tstrOfficePhone.size() > MAXLEN_OFFICETEL)
	{
		return err_OfficePhone;
	}

	contact.officePhone_ = strOfficePhone;

	return err_None;
}

ERROR_TYPE1 CAddrContacts::ImportProgressSetDN(uc::model::Contact &contact,  const std::string &strDN) const
{
	DEBUG_TRACE("dn:%s",strDN.c_str());
	const wstring tstrDN = eSDKTool::utf8_2_unicode_w(strDN);
	if (tstrDN.size() > MAXLEN_OFFICETEL)
	{
		return err_Unkown;
	}

	contact.webSite_ = strDN;

	return err_None;
}

ERROR_TYPE1 CAddrContacts::ImportProgressSetType(uc::model::Contact &contact,  const std::string &strType) const
{
	DEBUG_TRACE("type:%s",strType.c_str());
	const wstring tstrType = eSDKTool::utf8_2_unicode_w(strType);
	if (tstrType.size() > MAXLEN_OFFICETEL)
	{
		return err_Unkown;
	}

	contact.gender_ = strType;

	return err_None;
}


ERROR_TYPE1 CAddrContacts::ImportProgressSetNickName(uc::model::Contact &contact,  const std::string &strNickName) const
{
	DEBUG_TRACE("strNickName:%s",strNickName.c_str());
	const wstring tstrNickName = eSDKTool::utf8_2_unicode_w(strNickName);
	if (tstrNickName.size() > MAXLEN_OFFICETEL)
	{
		return err_Unkown;
	}

	contact.nickName_ = strNickName;

	return err_None;
}


/**********************************************************
* description: ����OtherPhone
* param [in ]: strOtherPhone
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetOtherPhone(uc::model::Contact &contact, const std::string &strOtherPhone) const
{
	DEBUG_TRACE("otherphone:%s",strOtherPhone.c_str());
	const wstring tstrOtherPhone = eSDKTool::utf8_2_unicode_w(strOtherPhone);
	if (tstrOtherPhone.size() > MAXLEN_OTHERTEL)
	{
		return err_OtherPhone;
	}

	contact.otherPhone_ = strOtherPhone;

	return err_None;
}

/**********************************************************
* description: ����Email
* param [in ]: strEmail
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetEmail(uc::model::Contact &contact, const std::string &strEmail) const
{
	DEBUG_TRACE("email:%s",strEmail.c_str());
	const int bRet = eSDKTool::IsValidEmailFormat(strEmail);

	if (!bRet)
	{
		return err_Email;
	}

	contact.email_ = strEmail;

	return err_None;	
}

/**********************************************************
* description: ���õ�ַ
* param [in ]: strAddress
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetAddress(uc::model::Contact &contact,const std::string &strAddress) const
{
	DEBUG_TRACE("address:%s",strAddress.c_str());
	const wstring tstrAddress = eSDKTool::utf8_2_unicode_w(strAddress);
	if (tstrAddress.size() > MAXLEN_ADDR)
	{
		return err_Address;
	}

	contact.address_ = strAddress;

	return err_None;
}

/**********************************************************
* description: ��������
* param [in ]: strDescription
* param [out]: contact ��ǰ��ϵ�˽ṹ��ָ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::ImportProgressSetDescription(uc::model::Contact &contact,const std::string &strDescription) const
{
	DEBUG_TRACE("description:%s",strDescription.c_str());
	const wstring tstrDescription = eSDKTool::utf8_2_unicode_w(strDescription);
	if (tstrDescription.size() > MAXLEN_DESC)
	{
		return err_Description;
	}

	contact.desc_ = strDescription;

	return err_None;
}
ERROR_TYPE1 CAddrContacts::ImportProgressSetDeptName(uc::model::Contact &contact,const std::string &strDeptName) const
{
	DEBUG_TRACE("deptname:%s",strDeptName.c_str());
	const wstring tstrDeptName = eSDKTool::utf8_2_unicode_w(strDeptName);
	if (tstrDeptName.size() > MAXLEN_DESC)
	{
		return err_DeptName;
	}

	contact.deptName_ = strDeptName;

	return err_None;
}


/**********************************************************
* description: ���������Ƿ�������ȷ
* param [in ]: strGroupName �����ķ�����
* param [out]: ��
* return     : ERROR_TYPE
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
ERROR_TYPE1 CAddrContacts::CheckGroupName(const std::string &strGroupName) const
{
	DEBUG_TRACE("group name:%s",strGroupName.c_str());
	const wstring tstrGroupName = eSDKTool::utf8_2_unicode_w(strGroupName);
	if (tstrGroupName.size() > MAXLEN_GROUPNAME)
	{
		return err_GroupName;
	}

	// ������ϵ�˷������Ʋ�����"�����ϵ��"
	//std::wstring  contactName= "Recent Contacts";
	const string strRecContactGroup = eSDKTool::unicode_w_2_utf8(LANG(CONTACTCTRL_COMMON_RECENTCONTACT_GROUP));
	if (strRecContactGroup == strGroupName)
	{
		return err_GroupName;
	}

	return err_None;
}

TE_S_GROUPS_CHAIN* CAddrContacts::AddGroupChain(TE_S_GROUPS_CHAIN *groupChainHead,TE_S_GROUP_INFO *groupInfo)
{
	TE_S_GROUPS_CHAIN *groupChain = groupChainHead;
	TE_S_GROUPS_CHAIN *tmpGroupChain = NULL;
	if(!groupChain)
	{
		groupChain =  (TE_S_GROUPS_CHAIN*)malloc(sizeof(TE_S_GROUPS_CHAIN));
		memset(groupChain, 0, sizeof(TE_S_GROUPS_CHAIN));
		groupChain->group = groupInfo;
		return groupChain;
	}

	while(groupChain)
	{
		if(!groupChain->next)
		{
			tmpGroupChain =  (TE_S_GROUPS_CHAIN*)malloc(sizeof(TE_S_GROUPS_CHAIN));
			memset(tmpGroupChain, 0, sizeof(TE_S_GROUPS_CHAIN));
			groupChain->next = tmpGroupChain;
			tmpGroupChain->group = groupInfo;
			return tmpGroupChain;
		}
		groupChain = groupChain->next;
	}
	return NULL;
}

TE_S_GROUP_INFO* CAddrContacts::findGroupInChain(TE_CHAR *groupName, TE_S_GROUPS_CHAIN *groupChainHead)
{
	TE_S_GROUPS_CHAIN *groupChain = groupChainHead;
	if (!groupName || !groupChainHead)
	{
		return NULL;
	}

	while(groupChain)
	{
		if (strncmp(groupName, groupChain->group->groupName,strlen(groupName)) == 0)
		{
			return groupChain->group;
		}
		groupChain = groupChain->next;
	}
	return NULL;
}

int CAddrContacts::InsertContactInGroup(TE_S_GROUP_INFO *groupNode, TE_S_CONTACTS_CHAIN *contactNode)
{
	TE_S_CONTACTS_CHAIN *contactChain = NULL;

	if(!groupNode || !contactNode)
	{
		return TE_SDK_NullPtr;
	}

	contactChain = groupNode->contactsChain;

	if(!contactChain)
	{
		groupNode->contactsChain = contactNode;
		return TE_SDK_Success;
	}

	while(contactChain)
	{
		if(!contactChain->next)
		{
			contactChain->next = contactNode;
			break;
		}
		contactChain=contactChain->next;
	}
	return TE_SDK_Success;
}


int CAddrContacts::ParseExcelFile(const TE_CHAR* strFile,TE_S_GROUPS_CHAIN**  groupChain)
{
	DEBUG_TRACE("strFile:%s",strFile);
	CString T_strFile;
	CMapString mapArray;
	T_strFile = strFile;
	//�ж�·���Ƿ�Ϊ��
	if (T_strFile.IsEmpty())// ·��Ϊ��
	{
		return TE_SDK_illegalFileFormat;
	}
	//�ж��ܲ����ҵ����ļ�
	const DWORD dwAttributes = GetFileAttributes( T_strFile );
	if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		// ��ʾ:��ʾδ�ҵ����ļ�
		return TE_SDK_NoFindFile ;
	}
	// ȡ�ļ��ĺ�׺��
	CString filePostfix = _T("");
	const int postFixSize = T_strFile.GetLength() - (T_strFile.ReverseFind(_T('.')) + 1);
	if ((POSTFIX_COUNT == postFixSize) || (POSTFIX_COUNT + 1 ==postFixSize))
	{
		filePostfix = T_strFile.Right(postFixSize);
	}

	if(0 != filePostfix.Compare(_T("xlsx"))&&(0 != filePostfix.Compare(_T("xls"))))
	{
		return TE_SDK_illegalFileFormat;
	}
	// �����еط��ȵ�����CoUnInitilize [3/2/2010 cKF12355]
	//(void)::CoInitialize(NULL);
	Excel::_ApplicationPtr excelApp;
	HRESULT hr = excelApp.CreateInstance("Excel.Application");//����Excelʵ��������Excel������(4�˻����Ϻ�ʱ1s������)
	if (FAILED(hr))
	{
		ERROR_LOG( "excelApp.CreateInstance can not create instance !");
		return TE_SDK_CreatExcelApplicationFailed;
	}

	Excel::WorkbooksPtr workbooks = excelApp->GetWorkbooks();  //��ȡExcel�������������еı�(����Ϊ*.xls)
	Excel::_WorkbookPtr workbook = NULL;//���ļ���ȡ��Ҫ�ı�

	try
	{
		workbook = workbooks->Open(_bstr_t(strFile), vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);
		if (NULL == workbook)
		{
			(void)workbooks->Close();
			(void)excelApp->Quit();

			// ��ʾ:�ļ��޷�ʶ��
			CString m_strTipInfo = LANG(CONTACTCTRL_SELECTDLG_TXT_IMPORTDLG_ERR_INVALID_FAILE).c_str();
			//SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_MSGBOX, (WPARAM)&m_strTipInfo, NO_CLOSE_PARENT_DLG);
			ERROR_LOG( "Open Excel Failed!");
			return TE_SDK_ExcelWorkbookEmpty;
		}

		Excel::_WorksheetPtr worksheet = workbook->GetActiveSheet();//��ȡ��Ĺ�����
		Excel::RangePtr usedRange = worksheet->GetUsedRange();//��ȡ�Ѿ���ʹ�õķ�Χ

		//�ж��ļ�ͷ���Ƿ���Ϲ淶
		Excel::RangePtr colRange = usedRange->GetColumns(); //��ʹ�õ��������
		const int nCols = colRange->GetCount();
		std::vector<CString> splitHead;  //������ļ��ı���ͷ
		for (int nCol = 1; nCol <= nCols; ++nCol)
		{
			Excel::RangePtr range = worksheet->Cells->Item[VNET_KEY_ROW_POS][nCol]; //��ȡ����

			CString str = range->GetValue();//lint !e64

			splitHead.push_back(str);
		}

		if (!CheckHeadLine(splitHead))
		{
			CloseWorkbook(workbook, workbooks, excelApp);
			return TE_SDK_ErrorHeadLineFormat;
		}

		//�����ϵ�˺ܶ࣬��ѭ������ѭ���ܶ�Σ�Ҫ�ǳ�ע������Ҫ��
		//��һ�еı������ݲ���Ҫ,����,�ӵڶ��п�ʼ��
		//��ʹ�õ��������
		Excel::RangePtr rowRange = usedRange->GetRows();
		const int nRows = rowRange->GetCount() > 65535 ? 65535 : rowRange->GetCount();
		unsigned int nIndex = 0;
		for (int nRow = VNET_KEY_ROW_POS + 1; nRow <= nRows; ++nRow)
		{

			//Begin: 4�˻�����ÿ�κ�ʱ4.3ms����
			std::vector<CString> splitStr;
			for (int nCol = 1; nCol <= nCols; ++nCol)
			{
				Excel::RangePtr range = worksheet->Cells->Item[nRow][nCol];//��ȡ����

				CString strTmp = range->GetValue();//lint !e64
				(void)strTmp.Trim();//ȥ���ַ����еĿո�
				splitStr.push_back(strTmp);
			}
			//End  :4�˻�����ÿ�κ�ʱ4.3ms����

			if (!AssemblyMapArray(splitStr, nIndex, mapArray))
			{
				CloseWorkbook(workbook, workbooks, excelApp);
				return TE_SDK_AssemblyContactFailed;
			}
		}

		if (0 == nIndex)
		{
			// ��ʾ:�ļ�������ϵ
			CString m_strTipInfo = LANG(CONTACTCTRL_SELECTDLG_STC_IMPORTDLG_NO_CONTACT).c_str();
			//	SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_MSGBOX, (WPARAM)&m_strTipInfo, NO_CLOSE_PARENT_DLG);

			CloseWorkbook(workbook, workbooks, excelApp);
			return TE_SDK_FileNoContact;
		}

		//	SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_SET_CONTACT_SIZE, NULL, NULL);
		//	SendMessageMark(m_hWndOwner,WM_CONTACT_IMPORTFRAME_USER_SELECTCONTACT, SELECT_ALL, NULL);

		CloseWorkbook(workbook, workbooks, excelApp);

		std::map<long, std::vector<CString>>::const_iterator itr=mapArray.begin();
		//std::vector<CString>  m_contact;
		//int i=0;
		CString str;
		std::wstring str1;
		TE_S_GROUPS_CHAIN *groupChainHead= NULL;
		TE_S_GROUPS_CHAIN *groupChainTail= NULL;
		//groupList->groupInfo = (TE_S_GROUP_INFO*)malloc(sizeof(TE_S_GROUP_INFO));
		for(;itr!=mapArray.end();itr++)
		{

			TE_S_GROUP_INFO *tmpgroupInfo = (TE_S_GROUP_INFO *)malloc(sizeof(TE_S_GROUP_INFO));
			TE_S_GROUP_INFO *groupInfo = NULL ;
			if(!tmpgroupInfo)
			{
				return TE_SDK_Failed;
			}
			memset(tmpgroupInfo,0,sizeof(TE_S_GROUP_INFO));
			str =  itr->second.at(0);
			if(str.GetLength()>=TE_D_NAME_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the group name is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(tmpgroupInfo->groupName, eSDKTool::WSToString(str1).c_str(),TE_D_GROUPNAME_LEN);

			TE_S_CONTACTS_CHAIN *contactsChain = (TE_S_CONTACTS_CHAIN *)malloc(sizeof(TE_S_CONTACTS_CHAIN));
			memset(contactsChain, 0, sizeof(TE_S_CONTACTS_CHAIN));
			str =  itr->second.at(1);
			if(str.GetLength()>=TE_D_NAME_LEN)
			{	
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the name is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.name, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);
			str =  itr->second.at(2);
			if(str.GetLength()>=TE_D_NUMBER_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the account is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.ucAcc, eSDKTool::WSToString(str1).c_str(),TE_D_NUMBER_LEN);
			str =  itr->second.at(3);
			if(str.GetLength()>=TE_D_EMAIL_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the email is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.email, eSDKTool::WSToString(str1).c_str(),TE_D_EMAIL_LEN);
			str =  itr->second.at(4);
			if(str.GetLength()>=TE_D_ADDRESS_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the address is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.addresssite, eSDKTool::WSToString(str1).c_str(),TE_D_ADDRESS_LEN);
			str =  itr->second.at(5);
			if(str.GetLength()>=TE_D_DESCRIPTION_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the description is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.description, eSDKTool::WSToString(str1).c_str(),TE_D_DESCRIPTION_LEN);
			str =  itr->second.at(6);
			if(str.GetLength()>=TE_D_DEPARTNAME_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the departname is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.deptname, eSDKTool::WSToString(str1).c_str(),TE_D_DEPARTNAME_LEN);
			str =  itr->second.at(7);
			if(str.GetLength()>=TE_D_PHONE_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the mobile phone is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.mobile, eSDKTool::WSToString(str1).c_str(),TE_D_PHONE_LEN);
			str =  itr->second.at(8);
			if(str.GetLength()>=TE_D_PHONE_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the office phone is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.officePhone, eSDKTool::WSToString(str1).c_str(),TE_D_PHONE_LEN);
			str =  itr->second.at(11);
			if(str.GetLength()>=TE_D_NAME_LEN)
			{
				if (tmpgroupInfo)
				{
					free(tmpgroupInfo);
				}
				ERROR_LOG("the nickname is too long");
				continue;
			}
			str1 = eSDKTool::CstringToWstring(str);
			strncpy(contactsChain->contactInfo.nickname, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);

			if(groupInfo = findGroupInChain(tmpgroupInfo->groupName,groupChainHead))
			{
				if (TE_SDK_Success != InsertContactInGroup(groupInfo, contactsChain))
				{
					ERROR_LOG("InsertContactInGroup Fail!");
				}
				if(tmpgroupInfo)
				{
					free(tmpgroupInfo);
					tmpgroupInfo = NULL;
				}
			}
			else
			{
				groupChainTail = AddGroupChain(groupChainHead,tmpgroupInfo);
				if(!groupChainHead)
				{
					groupChainHead = groupChainTail;
				}
				if (TE_SDK_Success != InsertContactInGroup(groupChainTail->group, contactsChain))
				{
					ERROR_LOG("InsertContactInGroup Fail!");
				}
			}

			//i++;
		}
		*groupChain = groupChainHead;
		return TE_SDK_Success;

	}
	catch (const _com_error& comErr)
	{
		ERROR_LOG("catch exception : 0x%08lx; Error:%s,",comErr.Error(),eSDKTool::unicode_2_utf8(comErr.ErrorMessage()).c_str());

		CloseWorkbook(workbook, workbooks, excelApp);

		// ��ʾ:�ļ��޷�ʶ��
		//const CString strTipInfo = LANG(CONTACTCTRL_SELECTDLG_TXT_IMPORTDLG_ERR_INVALID_FAILE).c_str();
		//SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_MSGBOX, (WPARAM)&strTipInfo, NO_CLOSE_PARENT_DLG);

		return TE_SDK_ComError;
	}
}


/**********************************************************
* description: �ж��ļ�ͷ���Ƿ���Ϲ淶
* param [in ]: splitHead  �ļ�ͷ�ֶ��б�
* param [out]: ��
* return     : TRUE���ļ�ͷ���Ϲ淶��FALSE���ļ�ͷ�����Ϲ淶
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
int CAddrContacts::CheckHeadLine(std::vector<CString> &splitHead)
{
	DEBUG_TRACE("");
	InitStandardHeaders();
	std::vector<CString>::iterator itor = m_vecStandardHeaders.begin();
	for ( ; itor != m_vecStandardHeaders.end(); itor++)
	{
		if (CheckHeadLine(splitHead, *itor))
		{
			return TRUE;
		}
	}

	// ��ʾ:�����ļ�����ͷ�����ϱ�׼����ͷ�ĸ�ʽ
	return FALSE;
}

void CAddrContacts::InitStandardHeaders()
{
	DEBUG_TRACE("");
	if (m_vecStandardHeaders.size() > 0)
	{
		return;
	}

	CString header = LANG(CONTACTCTRL_SELECTDLG_STC_EXPORTDLG_STANDARD_HEAD).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_ENGLISH).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_SMPLECHINESE).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_FRENCH).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_SPANISH).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_PORTUGUESE).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_PROTUGAL_BRAZIL).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_JAPAN).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_TRADITIONAL_CHINESE).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_RUSSIAN_IOS).c_str();
	m_vecStandardHeaders.push_back(header);

	header = LANG(STANDARDHEADER_RUSSIAN_OSX).c_str();
	m_vecStandardHeaders.push_back(header);
}


/**********************************************************
* description: ��װ m_mapArray ��ֻ�����ֲ�Ϊ�յ����������װ��ȥ������ϵ���������ܳ���2000��
* param [in ]: splitStr ��ϵ����Ϣ�ֶ�
nIndex   ��ǰ������ϵ������ֵ
* param [out]: ��
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
bool CAddrContacts::AssemblyMapArray(const std::vector<CString> &splitStr, unsigned int &nIndex, CMapString &mapArray)
{
	DEBUG_TRACE("");
	//�������Ϊ��,����Ϊ��������
	if (!splitStr[ci_Name].IsEmpty() /*&& !splitStr[ci_Account].IsEmpty()*/)
	{
		mapArray[(long)nIndex] = splitStr;
		//mapArraySelectFlag[(long)nIndex] = DUICHECKBOX_CHECKED;

		++nIndex;

		const ctk::size_type MaxImportNum = 2000;//������ϵ����������2000���������Ƿ��ظ���
		if (nIndex > MaxImportNum)
		{
			// ��ʾ��Ϣ��������ϵ����������2000��
			CString strText;
			strText.Format(LANG(CONTACTCTRL_IMPORTPROGRESSDLG_TXT_IMPORTDLG_ERR_LIMIT).c_str(), MaxImportNum);
			//	SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_MSGBOX, (WPARAM)&strText, NO_CLOSE_PARENT_DLG);

			return false;
		}
	}

	return true;
}

int CAddrContacts::ParseCSVFile(const TE_CHAR* strFile,TE_S_GROUPS_CHAIN**  groupChain)
{	
	DEBUG_TRACE("strFile:%s",strFile);
	CString m_strFile;
	CMapString mapArray;
	m_strFile = strFile;
	//�ж�·���Ƿ�Ϊ��
	if (m_strFile.IsEmpty())// ·��Ϊ��
	{
		return TE_SDK_illegalFileFormat;
	}
	//�ж��ܲ����ҵ����ļ�
	const DWORD dwAttributes = GetFileAttributes( m_strFile );
	if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		// ��ʾ:��ʾδ�ҵ����ļ�
		return TE_SDK_NoFindFile ;
	}
	// ȡ�ļ��ĺ�׺��
	CString filePostfix = _T("");
	const int postFixSize = m_strFile.GetLength() - (m_strFile.ReverseFind(_T('.')) + 1);
	if ((POSTFIX_COUNT == postFixSize) || (POSTFIX_COUNT + 1 ==postFixSize))
	{
		filePostfix = m_strFile.Right(postFixSize);
	}

	if( 0!= filePostfix.Compare(_T("csv")))
	{
		return TE_SDK_illegalFileFormat;
	}
	std::string filePath = ctk::to_str(strFile);//lint !e1037 !e64

	//ʹ��STL�е�locale��ľ�̬����ָ��ȫ��locale���������·���´��ļ�ʧ�����⣻
	//ʹ�ø÷����Ժ�,cout���ܲ������趨����������������ģ�ʮ�����Σ�
	//����ķ�������Ҫ�ڻ�ԭ�����趨ǰ��cout��wcout������ģ�     
	//�ο����ϣ�http://www.cnblogs.com/kevinGaoblog/archive/2012/07/20/2601236.html
	(void)locale::global(locale(""));//��ȫ��������Ϊ����ϵͳĬ������
	ifstream readFile;
	readFile.open(filePath.c_str(), ifstream::in);
	(void)locale::global(locale("C"));//��ԭȫ�������趨

	if (!readFile.rdbuf()->is_open())
	{
		//��ʾ���޷�ʶ����ļ�
		const CString m_strTipInfo = LANG(CONTACTCTRL_SELECTDLG_TXT_IMPORTDLG_ERR_INVALID_FAILE).c_str();
		//SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_MSGBOX, (WPARAM)&m_strTipInfo, NO_CLOSE_PARENT_DLG);
		ERROR_LOG("Import Open CSV Failed!");

		return TE_SDK_UnRegonizeFile;
	}

	std::string line;
	(void)getline(readFile, line); //��ȡ��һ�е�����,������Ӧ���ǵ�����Ϣ�ı���

	CString strHead = CString(line.c_str());
	const std::string head = eSDKTool::unicode_2_utf8(strHead.GetBuffer(strHead.GetLength()));

	//�жϱ���ͷ���ֶθ�ʽ�Ƿ�ƥ���׼����ͷ
	std::vector<CString> splitHead;
	Split(head, splitHead);

	if (!CheckHeadLine(splitHead))
	{
		return TE_SDK_ErrorHeadLineFormat;
	}

	//�����ϵ�˺ܶ࣬��ѭ������ѭ���ܶ�Σ�Ҫ�ǳ�ע������Ҫ��
	//�ӵ����ļ��ĵڶ��п�ʼ��ȡ����
	unsigned int nIndex = 0;
	while (getline(readFile, line)) 
	{

		CString strLine = CString(line.c_str());
		line = eSDKTool::unicode_2_utf8(strLine.GetBuffer(strLine.GetLength()));

		std::vector<CString> splitStr;
		Split(line, splitStr);
		if (0 == splitStr.size())
		{
			continue;
		}

		//ȥ����ϵ�������ֶε�ǰ��ո�
		for (std::vector<CString>::size_type i = 0; i < splitStr.size(); ++i)
		{
			(void)splitStr[i].Trim();
		}

		if (!AssemblyMapArray(splitStr, nIndex, mapArray))
		{
			return TE_SDK_AssemblyContactFailed;
		}
	}

	if (0 == nIndex)
	{
		// ��ʾ:�ļ�������ϵ
		CString m_strTipInfo = LANG(CONTACTCTRL_SELECTDLG_STC_IMPORTDLG_NO_CONTACT).c_str();
		//SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_MSGBOX, (WPARAM)&m_strTipInfo, NO_CLOSE_PARENT_DLG);
		return TE_SDK_FileNoContact;
	}

	//	SendMessageMark(m_hWndOwner, WM_CONTACT_IMPORTSELECTDLG_SET_CONTACT_SIZE, NULL, NULL);
	//SendMessageMark(m_hWndOwner,WM_CONTACT_IMPORTFRAME_USER_SELECTCONTACT,SELECT_ALL, NULL);

	std::map<long, std::vector<CString>>::const_iterator itr=mapArray.begin();
	//std::vector<CString>  m_contact;
	//int i=0;
	CString str;
	std::wstring str1;
	TE_S_GROUPS_CHAIN *groupChainHead= NULL;
	TE_S_GROUPS_CHAIN *groupChainTail= NULL;
	//groupList->groupInfo = (TE_S_GROUP_INFO*)malloc(sizeof(TE_S_GROUP_INFO));
	for(;itr!=mapArray.end();itr++)
	{
		TE_S_GROUP_INFO *tmpgroupInfo = (TE_S_GROUP_INFO *)malloc(sizeof(TE_S_GROUP_INFO));
		if (!tmpgroupInfo)
		{
			ERROR_LOG("malloc fail!");
			continue;
		}
		memset(tmpgroupInfo, 0, sizeof(TE_S_GROUP_INFO));
		TE_S_GROUP_INFO *groupInfo = NULL;
		str =  itr->second.at(0);
		if(str.GetLength()>=TE_D_GROUPNAME_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the group name is too long");
			
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(tmpgroupInfo->groupName, eSDKTool::WSToString(str1).c_str(),TE_D_GROUPNAME_LEN);
		TE_S_CONTACTS_CHAIN *contactsChain = (TE_S_CONTACTS_CHAIN *)malloc(sizeof(TE_S_CONTACTS_CHAIN));
		memset(contactsChain,0,sizeof(TE_S_CONTACTS_CHAIN));
		str =  itr->second.at(1);
		if(str.GetLength()>=TE_D_NAME_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the name is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.name, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);
		str =  itr->second.at(2);
		if(str.GetLength()>=TE_D_NUMBER_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the account is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.ucAcc, eSDKTool::WSToString(str1).c_str(),TE_D_NUMBER_LEN);
		str =  itr->second.at(3);
		if(str.GetLength()>=TE_D_EMAIL_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the email is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.email, eSDKTool::WSToString(str1).c_str(),TE_D_EMAIL_LEN);
		str =  itr->second.at(4);
		if(str.GetLength()>=TE_D_ADDRESS_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the address is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.addresssite, eSDKTool::WSToString(str1).c_str(),TE_D_ADDRESS_LEN);
		str =  itr->second.at(5);
		if(str.GetLength()>=TE_D_DESCRIPTION_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the description is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.description, eSDKTool::WSToString(str1).c_str(),TE_D_DESCRIPTION_LEN);
		str =  itr->second.at(6);
		if(str.GetLength()>=TE_D_DEPARTNAME_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the departname is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.deptname, eSDKTool::WSToString(str1).c_str(),TE_D_DEPARTNAME_LEN);
		str =  itr->second.at(7);
		if(str.GetLength()>=TE_D_PHONE_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the mobile phone is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.mobile, eSDKTool::WSToString(str1).c_str(),TE_D_PHONE_LEN);
		str =  itr->second.at(8);
		if(str.GetLength()>=TE_D_PHONE_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the office phone is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.officePhone, eSDKTool::WSToString(str1).c_str(),TE_D_PHONE_LEN);
		str =  itr->second.at(11);
		if(str.GetLength()>=TE_D_NAME_LEN)
		{
			if (tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
			ERROR_LOG("the nickname is too long");
			continue;
		}
		str1 = eSDKTool::CstringToWstring(str);
		strncpy(contactsChain->contactInfo.nickname, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);

		if(groupInfo = findGroupInChain(tmpgroupInfo->groupName,groupChainHead))
		{
			
			if (TE_SDK_Success != InsertContactInGroup(groupInfo, contactsChain))
			{
				ERROR_LOG("InsertContactInGroup Fail!");
			}
			if(tmpgroupInfo)
			{
				free(tmpgroupInfo);
			}
		}
		else
		{
			groupChainTail = AddGroupChain(groupChainHead,tmpgroupInfo);
			if(!groupChainHead)
			{
				groupChainHead = groupChainTail;
			}
			if (TE_SDK_Success != InsertContactInGroup(groupChainTail->group, contactsChain))
			{
				ERROR_LOG("InsertContactInGroup Fail!");
			}
		}

		//i++;
	}
	*groupChain = groupChainHead;
	return TE_SDK_Success;
}

void CAddrContacts::Split(std::string inString, std::vector<CString>& splitStr) const
{
	DEBUG_TRACE("inString:%s",inString.c_str());
	const int oneCharSize = 1;//һ���ַ��ĳ���

	ctk::size_type pos = inString.find(",");
	ctk::size_type cur = 0;
	while (pos != ctk::npos)//lint !e650
	{
		std::string str = inString.substr(0, pos);

		if (str.length() > 0)
		{
			if (str[0] == '\"')
			{
				str = str.substr(1);
			}
		}
		if (str.length() > 0)
		{
			if (str[str.length() - oneCharSize] == '\"')
			{
				str = str.substr(0, str.length() - oneCharSize);
			}
		}

		cur = pos + oneCharSize;
		inString = inString.substr(cur);

		const CString strInfo = eSDKTool::utf8_2_unicode(str);
		splitStr.push_back(strInfo);

		pos = inString.find(",");

		//�������һ��
		if (pos == ctk::npos)//lint !e650
		{
			if (inString.length() > 0)
			{
				if (inString[0] == '\"')
				{
					inString = inString.substr(oneCharSize);
				}
			}
			if (inString.length() > 0)
			{
				if (inString[inString.length() - oneCharSize] == '\"')
				{
					inString = inString.substr(0, inString.length() - oneCharSize);
				}
			}

			CString cstrInfo = eSDKTool::utf8_2_unicode(inString);
			splitStr.push_back(cstrInfo);
		}
	}
}


int CAddrContacts::CheckHeadLine(std::vector<CString> &splitHead, const CString& standardHeader)
{
	DEBUG_TRACE("");
	std::vector<CString> standardHead;
	CString strStandardHead = standardHeader;
	const std::string head = ctk::to_utf8str(strStandardHead.GetBuffer(strStandardHead.GetLength()));//lint !e64
	Split(head, standardHead);

	//��֤����ͷ����ֻ��һ��""���ַ�
	RestrictFileHead(splitHead, standardHead.size() - 1);

	if(splitHead.size() != standardHead.size())
	{
		return FALSE;
	}

	std::vector<CString>::iterator itor = splitHead.begin();
	std::vector<CString>::iterator stdItor = standardHead.begin();
	int nPos = 0;
	// �������Ƿ�ƥ��
	for (; itor != splitHead.end(); ++itor)
	{
		(void)itor->Trim();//ȥ�����ֶ�ǰ��ո�
		(void)stdItor->Trim();

		if (*itor == *stdItor)
		{
			++nPos;
		}

		++stdItor;
	}

	if (nPos != STADNTILENUM && nPos != STADNTILENUM_OLD)
	{
		return FALSE;
	}

	return TRUE;
}

/**********************************************************
* description: �淶���ļ�ͷ����֤����ͷ����ֻ��һ��""���ַ�,
* param [in ]: splitHead  �ļ�ͷ�ֶ��б�
standardHeadLen ��׼����ͷ����
* param [out]: ��
* return     : void
* History    : 
1. 2013-07-01,w00208227 creat this file.
**********************************************************/
void CAddrContacts::RestrictFileHead(std::vector<CString> &splitHead, const ctk::size_type standardHeadLen) const
{
	DEBUG_TRACE("");
	if (splitHead.size() < standardHeadLen)
	{
		return;
	}

	std::vector<CString> tmpHead;

	for (ctk::size_type i = 0; i < standardHeadLen; ++i)
	{
		tmpHead.push_back(splitHead[i]);
	}

	//���׼����ͷ�ֶζ�Ӧ,���һ���ֶμӿ��ֶ�
	tmpHead.push_back(_T(""));
	if(!splitHead.empty())
	{
		splitHead.clear();
	}
	splitHead = tmpHead;
}

int  CAddrContacts::StartSearchFtp(const TE_CHAR* keyword,TE_S_CONTACTS_INFO*   contactsList)
{
	DEBUG_TRACE("keyword:%s",keyword);
	std::wstring W_contact;
	std::string T_contact;
	std::vector<uc::model::Contact> m_ftpContacts;
	int i=0;
	if(!UCCLIENT()->ContactManager->GetAllNetContactslist(m_ftpContacts))
	{
		ERROR_LOG("get all net contactlist failed");
		return TE_SDK_GetEnterpriseContactsFailed;
	}
	contactsList->contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*m_ftpContacts.size());
	// m_strKey��ȡƥ����
	std::string utf8Key = eSDKTool::unicode_2_utf8(keyword);
	std::vector<uc::model::Contact> contacts;
	std::vector<uc::model::Contact>::iterator cit = m_ftpContacts.begin();
	std::vector<uc::model::Contact>::iterator end = m_ftpContacts.end();
	if (!utf8Key.empty())
	{
		while (cit != end)
		{
			if (CAddrContacts::HasRelateInfo(*cit, utf8Key))
			{
				contacts.push_back(*cit);
				W_contact = eSDKTool::utf82unicode(cit->name_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].name,T_contact.c_str(),TE_D_NAME_LEN);
				W_contact = eSDKTool::utf82unicode(cit->mobile_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].mobile,T_contact.c_str(),TE_D_PHONE_LEN);
				W_contact = eSDKTool::utf82unicode(cit->officePhone_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].officePhone,T_contact.c_str(),TE_D_PHONE_LEN);
				W_contact = eSDKTool::utf82unicode(cit->ucAcc_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].ucAcc,T_contact.c_str(),TE_D_NUMBER_LEN);
				W_contact = eSDKTool::utf82unicode(cit->deptName_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].deptname,T_contact.c_str(),TE_D_DEPARTNAME_LEN);
				W_contact = eSDKTool::utf82unicode(cit->email_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].email,T_contact.c_str(),TE_D_EMAIL_LEN);
				W_contact = eSDKTool::utf82unicode(cit->address_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].addresssite,T_contact.c_str(),TE_D_ADDRESS_LEN);
				W_contact = eSDKTool::utf82unicode(cit->nickName_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].nickname,T_contact.c_str(),TE_D_NAME_LEN);
				W_contact = eSDKTool::utf82unicode(cit->desc_);
				T_contact = eSDKTool::WSToString(W_contact);
				strncpy(contactsList->contact[i].description,T_contact.c_str(),TE_D_DESCRIPTION_LEN);
				i++;
			}
			cit++;
		}
		contactsList->num = i;
	}
	else
	{
		while (cit != end)
		{
			contacts.push_back(*cit);
			W_contact = eSDKTool::utf82unicode(cit->name_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].name,T_contact.c_str(),TE_D_NAME_LEN);
			W_contact = eSDKTool::utf82unicode(cit->mobile_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].mobile,T_contact.c_str(),TE_D_PHONE_LEN);
			W_contact = eSDKTool::utf82unicode(cit->officePhone_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].officePhone,T_contact.c_str(),TE_D_PHONE_LEN);
			W_contact = eSDKTool::utf82unicode(cit->ucAcc_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].ucAcc,T_contact.c_str(),TE_D_NUMBER_LEN);
			W_contact = eSDKTool::utf82unicode(cit->deptName_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].deptname,T_contact.c_str(),TE_D_DEPARTNAME_LEN);
			W_contact = eSDKTool::utf82unicode(cit->email_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].email,T_contact.c_str(),TE_D_EMAIL_LEN);
			W_contact = eSDKTool::utf82unicode(cit->address_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].addresssite,T_contact.c_str(),TE_D_ADDRESS_LEN);
			W_contact = eSDKTool::utf82unicode(cit->nickName_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].nickname,T_contact.c_str(),TE_D_NAME_LEN);
			W_contact = eSDKTool::utf82unicode(cit->desc_);
			T_contact = eSDKTool::WSToString(W_contact);
			strncpy(contactsList->contact[i].description,T_contact.c_str(),TE_D_DESCRIPTION_LEN);
			i++;
			cit++;
		}
		contactsList->num = i;
	}
	return TE_SDK_Success;
}

int CAddrContacts::StartSearchLdap(const TE_CHAR* keyword)
{
	DEBUG_TRACE("keyword;%s",keyword);
	uc::model::UCClient *pclient = uc::model::UCClient::GetClient();
	unsigned int seqNum = 0;

	if (pclient == NULL)
	{
		return seqNum;
	}

	uc::model::LDAP_D_Search_Condition condition;
	condition.keywords = keyword;
	condition.bPageSize = true;
	if (m_pLdapSearchResult && m_pLdapSearchResult->ulCookieLen != 0)
	{
		condition.ulCookieLen = m_pLdapSearchResult->ulCookieLen;
		condition.pcPageCookie = (char*)malloc(condition.ulCookieLen);
		if (condition.pcPageCookie == NULL)
		{
			ERROR_LOG("alloc memory for pcPageCookie failed.");
			return seqNum;
		}
		hw::memcpy_s(condition.pcPageCookie, condition.ulCookieLen,m_pLdapSearchResult->pcPageCookie, condition.ulCookieLen); 
	}

	bool ret = pclient->LdapManager->Search(condition, &seqNum);
	if (!ret)
	{
		seqNum = 0;
	}

	if (condition.pcPageCookie)
	{
		free(condition.pcPageCookie);
	}

	return seqNum;

}

int CAddrContacts::StartSearchByKey( const TE_CHAR*   keyword)
{
	DEBUG_TRACE("keyword:%s",keyword);
	if(strlen(keyword)>TE_D_NAME_LEN)
	{
		return TE_SDK_ExceedNameLength;	
	}
	uc::model::UCClient::NetAddressBookType type = UCCLIENT()->GetCurrentNetAddressBookType();
	m_netAddressBookType = type;
	if (m_netAddressBookType == uc::model::UCClient::NetAddressBook_FTPS)
	{
		// nothing
		return TE_SDK_NoLdapSearchFailed;
	}
	else if (m_netAddressBookType == uc::model::UCClient::NetAddressBook_LDAPS)
	{
		m_lastSearchSeqNo = CAddrContacts::Instance().StartSearchLdap(keyword);
		if(0 != m_lastSearchSeqNo)
		{
			return TE_SDK_Success;
		}
		else
		{
			return TE_SDK_NoLdapSearchFailed;
		}
	}
	else
	{
		return TE_SDK_NoLdapSearchFailed;
	}
}

void	CAddrContacts::SearchContactFinish(TE_S_LDAP_D_Search_Result* callBackResult,TE_S_CONTACTS_INFO* contactsList)
{
	DEBUG_TRACE("");
	std::wstring W_contact;
	std::string T_contact;
	int i=0;
	if(!callBackResult)
	{
		return;
	}
	LDAP_D_Search_Result* pResult = new LDAP_D_Search_Result;
	if (!pResult)
	{
		return;
	}
	pResult->bSucess = callBackResult->bSucess;
	pResult->pcPageCookie = callBackResult->pcPageCookie;
	pResult->ulCode = callBackResult->ulCode;
	pResult->ulCookieLen = callBackResult->ulCookieLen;
	pResult->ulSeqNo = callBackResult->ulSeqNo;
	/*if (!pResult || pResult->ulSeqNo != m_lastSearchSeqNo)
	{
	return;
	}*/

	INFO_LOG("pResult cookie len:,%d" , pResult->ulCookieLen);  

	SAFE_DELETE(m_pLdapSearchResult);
	if (pResult->ulCookieLen != 0)
	{
		m_pLdapSearchResult = new LDAP_D_Search_Result(*pResult);
	}	
	//delete pResult;

	/*if (NULL == m_pSearchResultDlg)
	{
	return 0L;
	}*/

	uc::model::UCClient *pclient = uc::model::UCClient::GetClient();

	std::vector<uc::model::Contact> searchResultVec;
	if(!pclient->LdapManager->GetSearchResult(m_lastSearchSeqNo,searchResultVec))
	{
		delete pResult;
		return ;
	}

	contactsList->contact =(TE_S_CONTACT_INFO*)malloc(sizeof(TE_S_CONTACT_INFO)*searchResultVec.size());
	std::vector<uc::model::Contact>::iterator cit = searchResultVec.begin();
	while (cit != searchResultVec.end())
	{
		W_contact = eSDKTool::utf82unicode(cit->name_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].name, T_contact.c_str(), TE_D_NAME_LEN);
		W_contact = eSDKTool::utf82unicode(cit->ucAcc_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].ucAcc,T_contact.c_str(), TE_D_NUMBER_LEN);
		W_contact = eSDKTool::utf82unicode(cit->address_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].addresssite, T_contact.c_str(), TE_D_ADDRESS_LEN);
		W_contact = eSDKTool::utf82unicode(cit->mobile_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].mobile, T_contact.c_str(), TE_D_PHONE_LEN);
		W_contact = eSDKTool::utf82unicode(cit->officePhone_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].officePhone, T_contact.c_str(), TE_D_PHONE_LEN);
		W_contact = eSDKTool::utf82unicode(cit->email_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].email, T_contact.c_str(), TE_D_EMAIL_LEN);
		W_contact = eSDKTool::utf82unicode(cit->deptName_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].deptname, T_contact.c_str(), TE_D_DEPARTNAME_LEN);
		W_contact = eSDKTool::utf82unicode(cit->desc_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].description,T_contact.c_str(),TE_D_DESCRIPTION_LEN);
		W_contact = eSDKTool::utf82unicode(cit->nickName_);
		T_contact = eSDKTool::WSToString(W_contact);
		strncpy(contactsList->contact[i].nickname,T_contact.c_str(),TE_D_NAME_LEN);
		//	strncpy(contact[i]., contactlist[i].name_.c_str(), TE_D_NAME_LEN);
		cit++;
		i++;
	}
	contactsList->num = i;

	INFO_LOG("get SearchResult,%d",searchResultVec.size());
	delete pResult;
}