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
 * @file  addrcontacts.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Address List Class
 * @details 
 * @author zwx283069
 * @version 1.0
 * @date 2015-09-18    
 * @history  v1.1 2015-09-18 Init TE Desktop SDK Interface
****************************************************/
#pragma  once

//#include "stdafx.h"
#include <map>
#include <vector>


const int MAX_CONTACT_NUM = 1000;           // ��ϵ���������
const unsigned int MAX_CUSTOMGROUP_NUM = 100;        // �����������
const int MAXFLAGNAME= 100;


#include "ctk/ctk.h"
#include "hwuc/HWUC.h"
#include "history/history.h"
#include "TESDK.h"
#include "LangResManager.h"

//#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#import "../../../platform/TE/import/Excel/MSO.DLL" rename("RGB", "RGBXL") rename("SearchPath", "SearchPathXL")
#import "../../../platform/TE/import/Excel/VBE6EXT.OLB"
#import "../../../platform/TE/import/Excel/EXCEL.EXE" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") \
	rename("CopyFile", "CopyFileXL") rename("ReplaceText", "ReplaceTextXL") \
	rename("DocumentProperties", "DocumentPropertiesXL") exclude("IFont","IPicture")


#import "../../../platform/TE/import/Excel/MSOUTL.OLB" no_namespace  exclude("_IRecipientControl", "_DRecipientControl")\
	rename("CopyFile", "CopyFileOL")   rename("Folder", "FolderOL") exclude("_OlkTextBox","_OlkLabel","_OlkCommandButton","_OlkCheckBox","_OlkOptionButton","_OlkComboBox","_OlkListBox","_OlkDateControl","_OlkTimeControl" ,"_OlkFrameHeader")


enum emContactInfo
{
	ci_GroupName = 0,  //����
    ci_Name,           //����
	ci_Account,        // �ʺ�
	ci_Email,          //��������
	ci_Addr,
	ci_Desc,           //����
	ci_DepartName,     //��������
	ci_Mobile,         //�ֻ�����
	ci_OfficePhone,    //�칫�绰
	ci_DN,
	ci_Type,
	ci_Nickname,       //�ǳ�
};//00208227  ע�⣬���ö��ÿ����Ա��ֵ����������ģ��������ı䣡

//����ʧ�ܴ�����
typedef enum 
{
	err_None = 0,			//û�д���
    err_NameRepeat,			//�����ظ�
	err_AccountRepeat,	    //�˺��ظ�
	err_Server,				//�������������
	err_Local,				//���������뱾���ظ�
	err_GroupName,			//����������
    err_Name,				//��������
    err_NoName,				//����Ϊ��
	err_Account,            //�˺ų���
	err_NoAccount,          //�˺�Ϊ��
	err_Gender,				//�Ա����
	err_Mobile,				//�ֻ������������1��
	err_OfficePhone,        //�칫���루����2��//00208227:��������
	err_OtherPhone,			//�������루����3��
	err_Email,				//��������
	err_DeptName,			//����������
	err_Address,			//��ַ������
	err_Description,		//����������       //00208227:��������
	err_CreateGroupFailed,	//������ʧ��
	err_AddContactFailed,	//������ϵ��ʧ��
	err_MaxLimit,			//��ϵ���Ѵ�����
	err_Unkown				//δ֪�Ĵ���
}ERROR_TYPE1;


const int	MAXLEN_GROUPNAME	= 100;  //00208227������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_NAME			= 100; //00208227������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_ACCOUNT	    = 100;  //00208227������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_GENDER		= 7;
const int 	MAXLEN_NICKNAME		= 64;
const int 	MAXLEN_CORPNAME		= 64;
const int 	MAXLEN_BUSINESSNAME	= 64;
const int	MAXLEN_DEPTNAME		= 128;
const int	MAXLEN_MOBILE		= 100;  //00208227������1������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_OFFICETEL	= 100;  //00208227������2������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_OTHERTEL		= 100;  //00208227������3������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_HOMETEL		= 16;
const int	MAXLEN_SHORTCODE	= 10;
const int	MAXLEN_FAX			= 16;
const int	MAXLEN_EMAIL		= 100;  //00208227������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_WEBPAGE	    = 256;
const int	MAXLEN_ADDR			= 100;  //00208227������SRS�����ȶ�Ϊ100���ַ�
const int	MAXLEN_DESC			= 100;   //00208227������SRS�����ȶ�Ϊ100���ַ�


enum DUICHECKBOX_VALUE
{ 
	DUICHECKBOX_CHECKED = 1,
	DUICHECKBOX_HALFCHECKED = 2,
	DUICHECKBOX_UNCHECKED = 0 
};


typedef std::map<long, DUICHECKBOX_VALUE > CMapEmun;      // ӳ�� װö������
typedef std::map<long, std::vector<CString>> CMapString;  // ӳ�� װ�ַ�������
typedef std::multimap<CString, std::vector<CString> > CMultimapContact;  // ��ϵ�����ݱ�

struct UserKey
{
	// ���Խṹ����
	UserKey(TE_E_USEKEY_SORT_RULE sort_rule, uc::model::ContactAvailability state, int lsort, const std::string& id, const std::string& name, bool isMyself = false) 
	{
		state_ = state;
		sort_ = lsort;
		id_ = id;
		name_ = name;
		isMyself_ =isMyself;
		sort_rule_ = sort_rule;
	}

	// ��ȡ�û�ID
	std::string getID() const
	{
		return id_;
	}

	// �ؼ���
	int state_;
	int sort_;
	std::string id_;
	std::string name_;
	bool isMyself_;
	TE_E_USEKEY_SORT_RULE sort_rule_;


	//������ϵ�������㷨ʵ��  HJJ===
	bool operator< (const UserKey& _v) const
	{
		if (isMyself_)
		{
			return true;
		}
		if (_v.isMyself_)
		{
			return false;
		}
		if (group_status_first == sort_rule_)
		{
			// �����°�״̬
			return state_sort(_v);
		}
		else if(group_name_first == sort_rule_)
		{
			// �����°�����
			return name_sort(_v);
		}
		else
		{
			return this->sort_<_v.sort_;
		}
	}

	// ״̬����
	bool state_sort(const UserKey& _v) const
	{
		if (compareState(state_, _v.state_) < 0)
		{
			return false;
		}
		else if (compareState(state_, _v.state_) == 0)
		{
			return name_sort(_v);
		}
		else 
		{
			return true;
		}
	}
	// ��������
	bool name_sort(const UserKey& _v) const
	{
		//�����ַ���Ҫת����UNICODE�Ƚϣ������std::string��compare��������ƴ������Ͳ�׼ȷ��
		CString nameStr = eSDKTool::utf8_2_unicode(name_);
		CString nameStr2 = eSDKTool::utf8_2_unicode(_v.name_);
		setlocale( LC_ALL, NULL );

		CString cstrLang = LANGRESMGR()->GetLangCode().c_str();
		string str = eSDKTool::unicode_2_utf8(cstrLang);//ctk::to_str(cstrLang.GetString());

		int iLangCode = atoi(str.c_str());

		int ret = CompareString(iLangCode, NULL, nameStr, -1, nameStr2, -1);
		if(ret < CSTR_EQUAL)
		{
			return true;
		}
		else if (ret == CSTR_EQUAL)
		{
			if (id_ < _v.id_)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	// ״̬�Ƚ�
	int compareState(int state1, int state2) const
	{
		if (state1 == state2)
		{
			return 0;
		}

		//����״̬����δ֪״̬ǰ
		if (state1 == uc::model::Offline )
		{
			if ( state2 == uc::model::InvalidStatus)
			{
				return 1;
			}
			else
				return -1;     
		}
		if (state2 == uc::model::Offline )
		{
			if ( state1 == uc::model::InvalidStatus)
			{
				return -1;
			}
			else
				return 1;     
		}
		else if (state1 > state2)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
};
/***************************************************
 * @class CAddrContacts
 * @brief Contacts List
 * @details 
***************************************************/

class CAddrContacts
{
public:
	static inline CAddrContacts& Instance()
	{
		static CAddrContacts inst;
		return inst;
	}
public:
	CAddrContacts(void);
	~CAddrContacts(void);
	std::vector<CString> m_vecStandardHeaders;
	std::vector<uc::model::CustomGroup> agentGroupList;    
	std::map<std::string,std::vector<uc::model::Contact>> m_localContactMap;         // ������ϵ���б�
	CMultimapContact m_multimapContact;
	unsigned int m_lastSearchSeqNo;
	int m_netAddressBookType; //uc::model::UCClient::NetAddressBookType
	uc::model::LDAP_D_Search_Result* m_pLdapSearchResult;
	int AddContact(const TE_S_CONTACT_INFO contact,const TE_CHAR* groupName);
	int RemoveContact(const TE_CHAR*  contactName,const TE_CHAR* groupName);
	bool CheckNameEmpty(std::string strName);
	int CheckAccountEmpty(std::string strAccount);
	bool CheckEmailFormat(std::string strEmail);
	int CheckHasContactByName(std::string strName);
	int CheckHasContactByUri(std::string strUri);
	int CheckHasContactByAccount(std::string strAccount);
	int CheckExceedLimit();
	int IsLocalContact(uc::model::Contact& pContact);
	bool GetCustomGroupByName(const std::string& name, uc::model::CustomGroup& group) const;
	int EditContact(TE_S_CONTACT_INFO contact);
	int GetContactList(TE_S_CONTACTS_INFO* contactList, TE_E_USEKEY_SORT_RULE sortRule);
	int SearchContact(const TE_CHAR* keyword,TE_S_CONTACTS_INFO*   contactsList);
	bool HasRelateInfo(const uc::model::Contact& contact, const std::string& key);
	int CreateCustomGroup(const std::string& groupName);
	int RenameCustomGroup(const CString& groupName, std::string oldName);
	int RemoveCustomGroup(std::string strGrpName);
	void SetImportMapArray(CMapString& mapString);
	int GetCustomGroupList(TE_S_GROUPS_INFO*  groupsList);
	int GetCustomGroups(const TE_CHAR* name,TE_S_GROUPS_INFO *groups);
	int CheckExceedCustomGroupsLimit();
	//add by z00220320 �ַ���תΪСд
	std::string StrToLower(const std::string &str);
	//add by z00220320 �Ƚ��Ƿ�A����B ���Դ�Сд
	bool FindNoCase(const std::string &strA,const std::string &strB);

	int ExportExcelFile(const TE_CHAR* strFilePath,const TE_S_GROUPS_INFO* groupList,const TE_UINT32 type);
	void InsertExcelHead(Excel::_WorksheetPtr worksheet, Excel::RangePtr range);
	void Split(const CString &inString, std::vector<CString>& splitStr) const;
	void Split(std::string inString, std::vector<CString>& splitStr) const;
	void CloseWorkbook(const Excel::_WorkbookPtr &workbook,const Excel::WorkbooksPtr &workbooks,const Excel::_ApplicationPtr &excelApp) const;
	int InsertExcelContactInfo(Excel::_WorksheetPtr worksheet, Excel::RangePtr range);
	void InsertCSVHead(ofstream &saveFile) const;
	int InsertCSVContactInfo(ofstream &saveFile);
	void InitErrInfoByErrType(const ERROR_TYPE1 &errType, CString &strErrInfo) const;
	int IsRepeatContactInFile(const std::vector<CString> &contact, const std::vector<CString> &contactBehind) const;
	void DelRepeatContactFile();
	int GetContactAcclist(std::vector<std::string> &localContactNamelist) const;
	void GetlocalContactWithGroup(std::map<std::string,std::vector<std::string>> &localContactWhitGroup) const;
	int IsFileRepeatWithlocal(const std::vector<CString> &contactFile,std::map<std::string,std::vector<std::string>> &localContactWhitGroup) const;
	bool IsContactOrGroupNumBeyondLimit(const int localContantNum,const std::map<std::string,std::vector<std::string>> &localContactWhitGroup) const;
	ERROR_TYPE1 CheckGroupName(const std::string &strGroupName) const;
	void ImportContactNormally(const CMultimapContact::const_iterator &it);
	int ImportFile(const TE_S_GROUPS_CHAIN* groupsList);
	void MoveContactDataMemoryToDb();
	void ImportProgressSetDetailInfo(const ERROR_TYPE1 errType,CString &strDetailInfo) const;
	int  ParseExcelFile(const TE_CHAR* strFile,TE_S_GROUPS_CHAIN**  groupChain);
	int ParseCSVFile(const TE_CHAR* strFile,TE_S_GROUPS_CHAIN**  groupChain);
	int CheckHeadLine(std::vector<CString> &splitHead);
	void InitStandardHeaders();
	bool AssemblyMapArray(const std::vector<CString> &splitStr, unsigned int &nIndex, CMapString &mapArray);
	void RestrictFileHead(std::vector<CString> &splitHead, const ctk::size_type standardHeadLen) const;
	int CheckHeadLine(std::vector<CString> &splitHead, const CString& standardHeader);
	bool IsExistGroupFlag( std::string strFlagName);
	TE_S_GROUPS_CHAIN* AddGroupChain(TE_S_GROUPS_CHAIN *groupChainHead,TE_S_GROUP_INFO *groupInfo);
	TE_S_GROUP_INFO* findGroupInChain(TE_CHAR *groupName,TE_S_GROUPS_CHAIN *groupChainHead);
	int InsertContactInGroup(TE_S_GROUP_INFO *groupNode, TE_S_CONTACTS_CHAIN *contactNode);

	/* begin:������ϵ����Ϣ���� */
	ERROR_TYPE1 ImportProgressSetName(uc::model::Contact &contact, const std::string &strName) const;
	ERROR_TYPE1 ImportProgressSetAccount(uc::model::Contact &contact, const std::string &strAccount) const;
	ERROR_TYPE1 ImportProgressSetEmail(uc::model::Contact &contact, const std::string &strEmail) const;
	ERROR_TYPE1 ImportProgressSetAddress(uc::model::Contact &contact, const std::string &strAddress) const;
	ERROR_TYPE1 ImportProgressSetDescription(uc::model::Contact &contact, const std::string &strDescription) const;
	ERROR_TYPE1 ImportProgressSetDeptName(uc::model::Contact &contact, const std::string &strDeptName) const;
	ERROR_TYPE1 ImportProgressSetMobile(uc::model::Contact &contact, const std::string &strMobile) const;
	ERROR_TYPE1 ImportProgressSetOfficePhone(uc::model::Contact &contact, const std::string &strOfficePhone) const;
	ERROR_TYPE1 ImportProgressSetDN(uc::model::Contact &contact, const std::string &strDN) const;
	ERROR_TYPE1 ImportProgressSetType(uc::model::Contact &contact, const std::string &strType) const;
	ERROR_TYPE1 ImportProgressSetNickName(uc::model::Contact &contact, const std::string &strNickName) const;
	ERROR_TYPE1 ImportProgressSetOtherPhone(uc::model::Contact &contact, const std::string &strOtherPhone) const;
	typedef ERROR_TYPE1 (CAddrContacts::*SetFunction)(uc::model::Contact &contact, const std::string &strDescription) const;
	std::map<enum emContactInfo, SetFunction> m_SetFunctionMap;
	void InitSetFunctionMap();
	int StartSearchFtp(const TE_CHAR* keyword,TE_S_CONTACTS_INFO*   contactsList);
	int StartSearchLdap(const TE_CHAR* keyword);
	int StartSearchByKey(const TE_CHAR*   keyword);
	void	SearchContactFinish(TE_S_LDAP_D_Search_Result* wParam,TE_S_CONTACTS_INFO* contactsList);
	int  ReplaceContact(TE_S_CONTACT_INFO   contact);
	int GetContactByName(const TE_CHAR* name,TE_S_CONTACT_INFO* contact);
	int GetAllEnterpriseContacts(TE_S_CONTACTS_INFO* enterpriseContacts);
	int PrepareContactInfo(TE_S_CONTACT_INFO& contact);
	void ContactsTransCoding(uc::model::Contact&  contactlist,TE_S_CONTACT_INFO& contactsList);
	int GetContactsInGroup(const TE_CHAR* name,const TE_E_USEKEY_SORT_RULE sortRule,TE_S_CONTACTS_INFO *contacts);
	int CopyContactToGroup(const TE_CHAR* contactName,const TE_CHAR* groupName);
	int MoveContactToGroup(const TE_CHAR* contactName,const TE_CHAR* groupName,const TE_CHAR* oldGroupName);
	TE_E_CONTACT_AVAIL_ABILITY SetContactStatus(uc::model::ContactAvailability status);
};

