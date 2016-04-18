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
#include "TE_Demo.h"
#include "TE_InviteJion.h"


// CTE_InviteJion 对话框

IMPLEMENT_DYNAMIC(CTE_InviteJion, CDialog)

CTE_InviteJion::CTE_InviteJion(CWnd* pParent /*=NULL*/)
: CDialog(CTE_InviteJion::IDD, pParent)
, m_SearchContact(_T(""))
{

}

CTE_InviteJion::~CTE_InviteJion()
{
}

void CTE_InviteJion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMBERS, m_memLists);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_SearchContact);
}


BEGIN_MESSAGE_MAP(CTE_InviteJion, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_MEMBERS, &CTE_InviteJion::OnLbnSelchangeListMembers)
	ON_BN_CLICKED(IDC_BTN_INVITE, &CTE_InviteJion::OnBnClickedBtnInvite)
	ON_MESSAGE(WM_CONF_ADD_HALL_RESULT, &CTE_InviteJion::AddHallResult)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTE_InviteJion::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CTE_InviteJion 消息处理程序

BOOL CTE_InviteJion::OnInitDialog()
{	


	CDialog::OnInitDialog();
	//::SetWindowPos(m_LocalWindow.GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);
	return TRUE;  // return TRUE unless you set the focus to a control
}
void CTE_InviteJion::OnLbnSelchangeListMembers()
{
	// TODO: 在此添加控件通知处理程序代码
	int curSel = m_memLists.GetCurSel();

	if(m_memLists.GetCheck(curSel))
	{
		m_memLists.SetCheck(curSel,BST_UNCHECKED);
	}
	else
	{
		m_memLists.SetCheck(curSel,BST_CHECKED);
	}

}

void CTE_InviteJion::OnBnClickedBtnInvite()
{
	// TODO: 在此添加控件通知处理程序代码
	TE_S_SITE_INVITEDLIST _contacts;
	_contacts.listCount=0;
	int hasSelected=0;
	int len = 0;

	for(int i = 0 ; i < m_memLists.GetCount() ; i++)
	{
		if(m_memLists.GetCheck(i))
		{
			CString str;
			m_memLists.GetText(i, str);

			len = str.GetLength();

			char * itemstr=new char[len+1];
			memset(itemstr,0,len+1);

			strncpy(itemstr, str.GetBuffer(len), len);
			_contacts.list[hasSelected]=itemstr;
			_contacts.listCount++;

			hasSelected++;

		}
	}    

	if (hasSelected>0)
	{
		if(TE_SDK_OverMax==TE_InviteSiteToConf(&_contacts))
		{
			GetDlgItem(IDD_DIALOG_INVITETOJION)->SetWindowText(_T("失败：超出会议最大人数"));
		}

		for(int i=0;i<_contacts.listCount;i++)
		{
			delete _contacts.list[i];
		}
	}


}


LRESULT CTE_InviteJion::AddHallResult(WPARAM wParm, LPARAM Lparam)
{
	if (!m_addHallRest.result)
	{

		CString cstr;
		cstr.Format("%d个会场添加失败！", m_addHallRest.failedCount); 

		AfxMessageBox(_T(LPCSTR(cstr)));
	}
	this->DestroyWindow();
	return 0L;
}
void CTE_InviteJion::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	int len = 0,ret = 0,i=0;
	char searchkey[512]={0};
	TE_S_CONTACTS_INFO m_getContact;
	m_getContact.contact = NULL;
	m_getContact.num = 0;
	UpdateData(TRUE);
	len = m_SearchContact.GetLength();
	strncpy(searchkey ,m_SearchContact.GetBuffer(len),len);
	ret = TE_SearchContact(searchkey,&m_getContact);
	if(0 == ret)
	{
		m_memLists.ResetContent();
		m_memLists.SetCheckStyle(BS_CHECKBOX);
		for(i=0;i<m_getContact.num;i++)
		{
			m_memLists.AddString(m_getContact.contact[i].ucAcc);
		}
	}
}

