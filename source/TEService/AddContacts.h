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


const int MAX_CONTACT_NUM = 1000;           // 联系人最大限制
const unsigned int MAX_CUSTOMGROUP_NUM = 100;        // 分组最大限制
const int MAXFLAGNAME= 100;


#include "ctk/ctk.h"
#include "hwuc/HWUC.h"
#include "history/history.h"
#include "TESDK.h"
#include "LangResManager.h"

//#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
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
	ci_GroupName = 0,  //分组
    ci_Name,           //姓名
	ci_Account,        // 帐号
	ci_Email,          //电子邮箱
	ci_Addr,
	ci_Desc,           //描述
	ci_DepartName,     //部门名称
	ci_Mobile,         //手机号码
	ci_OfficePhone,    //办公电话
	ci_DN,
	ci_Type,
	ci_Nickname,       //昵称
};//00208227  注意，这个枚举每个成员的值都是有意义的，不能随便改变！

//导入失败错误码
typedef enum 
{
	err_None = 0,			//没有错误
    err_NameRepeat,			//姓名重复
	err_AccountRepeat,	    //账号重复
	err_Server,				//导入服务器出错
	err_Local,				//导入数据与本地重复
	err_GroupName,			//分组名出错
    err_Name,				//姓名出错
    err_NoName,				//姓名为空
	err_Account,            //账号出错
	err_NoAccount,          //账号为空
	err_Gender,				//性别出错
	err_Mobile,				//手机号码出错（号码1）
	err_OfficePhone,        //办公号码（号码2）//00208227:新增定义
	err_OtherPhone,			//其他号码（号码3）
	err_Email,				//电子邮箱
	err_DeptName,			//部门名出错
	err_Address,			//地址名出错
	err_Description,		//描述名出错       //00208227:新增定义
	err_CreateGroupFailed,	//创建组失败
	err_AddContactFailed,	//增加联系人失败
	err_MaxLimit,			//联系人已达上限
	err_Unkown				//未知的错误
}ERROR_TYPE1;


const int	MAXLEN_GROUPNAME	= 100;  //00208227：根据SRS，长度定为100个字符
const int	MAXLEN_NAME			= 100; //00208227：根据SRS，长度定为100个字符
const int	MAXLEN_ACCOUNT	    = 100;  //00208227：根据SRS，长度定为100个字符
const int	MAXLEN_GENDER		= 7;
const int 	MAXLEN_NICKNAME		= 64;
const int 	MAXLEN_CORPNAME		= 64;
const int 	MAXLEN_BUSINESSNAME	= 64;
const int	MAXLEN_DEPTNAME		= 128;
const int	MAXLEN_MOBILE		= 100;  //00208227：号码1，根据SRS，长度定为100个字符
const int	MAXLEN_OFFICETEL	= 100;  //00208227：号码2，根据SRS，长度定为100个字符
const int	MAXLEN_OTHERTEL		= 100;  //00208227：号码3，根据SRS，长度定为100个字符
const int	MAXLEN_HOMETEL		= 16;
const int	MAXLEN_SHORTCODE	= 10;
const int	MAXLEN_FAX			= 16;
const int	MAXLEN_EMAIL		= 100;  //00208227：根据SRS，长度定为100个字符
const int	MAXLEN_WEBPAGE	    = 256;
const int	MAXLEN_ADDR			= 100;  //00208227：根据SRS，长度定为100个字符
const int	MAXLEN_DESC			= 100;   //00208227：根据SRS，长度定为100个字符


enum DUICHECKBOX_VALUE
{ 
	DUICHECKBOX_CHECKED = 1,
	DUICHECKBOX_HALFCHECKED = 2,
	DUICHECKBOX_UNCHECKED = 0 
};


typedef std::map<long, DUICHECKBOX_VALUE > CMapEmun;      // 映射 装枚举序列
typedef std::map<long, std::vector<CString>> CMapString;  // 映射 装字符串序列
typedef std::multimap<CString, std::vector<CString> > CMultimapContact;  // 联系人数据表

struct UserKey
{
	// 可以结构构造
	UserKey(TE_E_USEKEY_SORT_RULE sort_rule, uc::model::ContactAvailability state, int lsort, const std::string& id, const std::string& name, bool isMyself = false) 
	{
		state_ = state;
		sort_ = lsort;
		id_ = id;
		name_ = name;
		isMyself_ =isMyself;
		sort_rule_ = sort_rule;
	}

	// 获取用户ID
	std::string getID() const
	{
		return id_;
	}

	// 关键字
	int state_;
	int sort_;
	std::string id_;
	std::string name_;
	bool isMyself_;
	TE_E_USEKEY_SORT_RULE sort_rule_;


	//个人联系人排序算法实现  HJJ===
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
			// 分组下按状态
			return state_sort(_v);
		}
		else if(group_name_first == sort_rule_)
		{
			// 分组下按名字
			return name_sort(_v);
		}
		else
		{
			return this->sort_<_v.sort_;
		}
	}

	// 状态排序
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
	// 姓名排序
	bool name_sort(const UserKey& _v) const
	{
		//这里字符串要转换成UNICODE比较，如果用std::string的compare方法按照拼音排序就不准确。
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
	// 状态比较
	int compareState(int state1, int state2) const
	{
		if (state1 == state2)
		{
			return 0;
		}

		//离线状态排在未知状态前
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
	std::map<std::string,std::vector<uc::model::Contact>> m_localContactMap;         // 本地联系人列表
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
	//add by z00220320 字符串转为小写
	std::string StrToLower(const std::string &str);
	//add by z00220320 比较是否A包含B 忽略大小写
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

	/* begin:导入联系人信息处理 */
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

