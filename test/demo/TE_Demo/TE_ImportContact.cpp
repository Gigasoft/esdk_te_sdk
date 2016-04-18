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
#include "stdafx.h"
#include "TE_ImportContact.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_ImportContact,CDialog)

CTE_ImportContact::CTE_ImportContact(CWnd* pParent /*NULL*/)
:CDialog(CTE_ImportContact::IDD,pParent)
{
	contact =  (CTE_DemoDlg *)pParent;
}

CTE_ImportContact::~CTE_ImportContact()
{

}

void CTE_ImportContact::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ContacList);
}

BEGIN_MESSAGE_MAP(CTE_ImportContact,CDialog)
	
	ON_BN_CLICKED(IDOK, &CTE_ImportContact::OnBnClickedOk)
	ON_MESSAGE(WM_CONTACT_SHOW_IMPORT_SELECTDLG, &CTE_ImportContact::ShowContactList)
END_MESSAGE_MAP()




void CTE_ImportContact::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	TE_S_GROUPS_CHAIN*  groupsList = NULL;
	std::wstring cstrName;
	TE_S_GROUPS_CHAIN *groupChainHead= NULL;
	TE_S_GROUPS_CHAIN *groupChainTail= NULL;

	//TE_S_CONTACTS_INFO getContacts;
	int i=0,len = 0;
	int rowEnd = m_ContacList.GetItemCount();
	//int ret = TE_GetContactList(getContacts);
	for(i=0;i<rowEnd;i++)
	{
		if(m_ContacList.GetCheck(i))
		{
			TE_S_GROUP_INFO *tmpgroupInfo = (TE_S_GROUP_INFO *)malloc(sizeof(TE_S_GROUP_INFO));
			memset(tmpgroupInfo, 0, sizeof(TE_S_GROUP_INFO));
			TE_S_GROUP_INFO *groupInfo = NULL;
			CString exportGroup= m_ContacList.GetItemText(i,0);
			int len = exportGroup.GetLength();
			strncpy(tmpgroupInfo->groupName,exportGroup.GetBuffer(len),len);

			TE_S_CONTACTS_CHAIN *contactsChain = (TE_S_CONTACTS_CHAIN *)malloc(sizeof(TE_S_CONTACTS_CHAIN));
			memset(contactsChain,0,sizeof(TE_S_CONTACTS_CHAIN));
			CString exportName = m_ContacList.GetItemText(i,1);
			len = exportName.GetLength();
			strncpy(contactsChain->contactInfo.name,exportName.GetBuffer(len),len);
			CString exportNumber = m_ContacList.GetItemText(i,2);
			len = exportNumber.GetLength();
			strncpy(contactsChain->contactInfo.ucAcc,exportNumber.GetBuffer(len),len);
			CString exportEmail = m_ContacList.GetItemText(i,3);
			len = exportEmail.GetLength();
			strncpy(contactsChain->contactInfo.email,exportEmail.GetBuffer(len),len);
			CString exportAddress = m_ContacList.GetItemText(i,4);
			len = exportAddress.GetLength();
			strncpy(contactsChain->contactInfo.addresssite,exportAddress.GetBuffer(len),len);
			CString exportDescription = m_ContacList.GetItemText(i,5);
			len = exportDescription.GetLength();
			strncpy(contactsChain->contactInfo.description,exportDescription.GetBuffer(len),len);
			CString exportDepartment = m_ContacList.GetItemText(i,6);
			len = exportDepartment.GetLength();
			strncpy(contactsChain->contactInfo.deptname,exportDepartment.GetBuffer(len),len);
			CString exportMobilephone = m_ContacList.GetItemText(i,7);
			len = exportMobilephone.GetLength();
			strncpy(contactsChain->contactInfo.mobile,exportMobilephone.GetBuffer(len),len);
			CString exportOfficephone = m_ContacList.GetItemText(i,8);
			len = exportOfficephone.GetLength();
			strncpy(contactsChain->contactInfo.officePhone,exportOfficephone.GetBuffer(len),len);
			CString exportNickname = m_ContacList.GetItemText(i,11);
			len = exportNickname.GetLength();
			strncpy(contactsChain->contactInfo.nickname,exportNickname.GetBuffer(len),len);

			if(groupInfo = findGroupInChain(tmpgroupInfo->groupName,groupChainHead))
			{
				InsertContactInGroup(groupInfo, contactsChain);
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
				InsertContactInGroup(groupChainTail->group, contactsChain);
			}
		}
	}
	groupsList = groupChainHead;
	int ret = TE_ImportFile( groupsList);
	if(0 == ret)
	{
		AfxMessageBox(_T("Import file success"));
		m_contacts_->OnUpdateRecordList();
	}
	else
	{
		AfxMessageBox(_T("Import file filed"));
	}
	while(groupsList)
	{
		while(groupsList->group->contactsChain)
		{
			TE_S_CONTACTS_CHAIN* tempContactsChain = groupsList->group->contactsChain;
			groupsList->group->contactsChain = groupsList->group->contactsChain->next;
			TE_FreeMemory(tempContactsChain);
		}
		TE_S_GROUPS_CHAIN* tempGroupsChain = groupsList;
		groupsList = groupsList->next;
		TE_FreeMemory(tempGroupsChain);
	}
    OnOK();
}

LRESULT CTE_ImportContact::ShowContactList(WPARAM wParm, LPARAM Lparam)
{
	

	return true;
}

TE_S_GROUPS_CHAIN* CTE_ImportContact::AddGroupChain(TE_S_GROUPS_CHAIN *groupChainHead,TE_S_GROUP_INFO *groupInfo)
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

TE_S_GROUP_INFO* CTE_ImportContact::findGroupInChain(TE_CHAR *groupName, TE_S_GROUPS_CHAIN *groupChainHead)
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

int CTE_ImportContact::InsertContactInGroup(TE_S_GROUP_INFO *groupNode, TE_S_CONTACTS_CHAIN *contactNode)
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