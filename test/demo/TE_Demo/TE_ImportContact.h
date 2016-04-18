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
#pragma  once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "TE_Contact.h"
#include "string"

class CTE_DemoDlg;
class CTE_Contact;

#define WM_CONTACT_SHOW				(WM_APP + 1501) //��Ϣ��ʼID
#define WM_CONTACT_SHOW_IMPORT_SELECTDLG				(WM_CONTACT_SHOW+1)

class CTE_ImportContact : public CDialog
{
	DECLARE_DYNAMIC(CTE_ImportContact)

public:
	CTE_ImportContact(CWnd* pParent = NULL);
	virtual ~CTE_ImportContact();

	enum { IDD = IDD_DIALOG_IMPORT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg LRESULT ShowContactList(WPARAM wParm, LPARAM Lparam);
	DECLARE_MESSAGE_MAP()
public:
	CTE_DemoDlg* contact;
	CTE_Contact* m_contacts_;
	typedef std::multimap<CString, std::vector<CString> > CMultimapContact;  // ��ϵ�����ݱ�
	CMultimapContact m_multimapContact;  // ��ϵ�����ݱ�
	CListCtrl m_ContacList;
	afx_msg void OnBnClickedOk();
	int InsertContactInGroup(TE_S_GROUP_INFO *groupNode, TE_S_CONTACTS_CHAIN *contactNode);
	TE_S_GROUP_INFO* findGroupInChain(TE_CHAR *groupName, TE_S_GROUPS_CHAIN *groupChainHead);
	TE_S_GROUPS_CHAIN* AddGroupChain(TE_S_GROUPS_CHAIN *groupChainHead,TE_S_GROUP_INFO *groupInfo);
};