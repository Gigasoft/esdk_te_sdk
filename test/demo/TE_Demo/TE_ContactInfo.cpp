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
#include "TE_ContactInfo.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_ContactInfo,CDialog)

CTE_ContactInfo::CTE_ContactInfo(CWnd* pParent /*NULL*/)
:CDialog(CTE_ContactInfo::IDD,pParent)
, m_ContactName(_T(""))
, m_ContactNumber(_T(""))
, m_ContactDepartment(_T(""))
, m_ContactMobilephone(_T(""))
, m_ContactOfficephone(_T(""))
, m_ContactEmail(_T(""))
, m_ContactAddress(_T(""))
, m_NickName(_T(""))
{
		m_iLogItem = 0;
		//m_demodlg = NULL;
		m_demodlg =  (CTE_DemoDlg *)pParent;
}

CTE_ContactInfo::~CTE_ContactInfo()
{

}

void CTE_ContactInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_ContactName);	
	DDX_Text(pDX, IDC_EDIT1, m_ContactNumber);
	DDX_Text(pDX, IDC_EDIT2, m_ContactDepartment);
	DDX_Text(pDX, IDC_EDIT3, m_ContactMobilephone);
	DDX_Text(pDX, IDC_EDIT4, m_ContactOfficephone);
	DDX_Text(pDX, IDC_EDIT5, m_ContactEmail);
	DDX_Text(pDX, IDC_EDIT6, m_ContactAddress);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_ComboGroup);
	DDX_Text(pDX, IDC_EDIT7, m_NickName);
}

BEGIN_MESSAGE_MAP(CTE_ContactInfo,CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CTE_ContactInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTE_ContactInfo::OnBnClickedButton1)
END_MESSAGE_MAP()



void CTE_ContactInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
	int len =0,ret=0,m_num = 0,i=0;
	char TempContact[64] = {0};
	char TempGroup[64] = {0};
	TE_UINT32 num = 0;
	CString m_strGroup;
	std::wstring cstrName;
	TE_S_CONTACT_INFO contact;
   TE_S_CONTACT_INFO  T_contact;
   	memset(&T_contact, 0, sizeof(TE_S_CONTACT_INFO));
	if(m_info->contacttype == 1)
	{
		strncpy(TempContact , m_info->m_contactName.c_str(),TE_D_NAME_LEN);
		ret = TE_GetContactByName(TempContact,&contact);
		{
			if(0 == ret)
			{
				//cstrName = m_demodlg->Utf82Unicode(contact.id);
				strncpy(T_contact.id , contact.id,TE_D_ID_LEN);
			}
		}
	}
	UpdateData(TRUE);
	len = m_ContactName.GetLength();
	if(len>=TE_D_NAME_LEN)
	{
		AfxMessageBox("the name is too long");
	}
	strncpy(T_contact.name,m_ContactName.GetBuffer(len),len);
	len = m_ContactNumber.GetLength();
	if(len>= TE_D_NUMBER_LEN)
	{
		AfxMessageBox("the account is too long");
	}
	strncpy(T_contact.ucAcc,m_ContactNumber.GetBuffer(len),len);
	len = m_NickName.GetLength();
	if(len >= TE_D_NAME_LEN)
	{
		AfxMessageBox("the nickname is too long");
	}
	strncpy(T_contact.nickname,m_NickName.GetBuffer(len),len);
	len = m_ContactDepartment.GetLength();
	if(len >= TE_D_DEPARTNAME_LEN)
	{
		AfxMessageBox("the departname is too long");
	}
	strncpy(T_contact.deptname,m_ContactDepartment.GetBuffer(len),len);
	len = m_ContactEmail.GetLength();
	if(len>TE_D_EMAIL_LEN)
	{
		AfxMessageBox("the email is too long");
	}
	strncpy(T_contact.email,m_ContactEmail.GetBuffer(len),len);
	len = m_ContactMobilephone.GetLength();
	if(len>=TE_D_PHONE_LEN)
	{
		AfxMessageBox("the mobilephone is  too long");
	}
	strncpy(T_contact.mobile,m_ContactMobilephone.GetBuffer(len),len);
	len = m_ContactOfficephone.GetLength();
	if(len >=TE_D_PHONE_LEN)
	{
		AfxMessageBox("the officephone is too long");
	}
	strncpy(T_contact.officePhone,m_ContactOfficephone.GetBuffer(len),len);
	len = m_ContactAddress.GetLength();
	if(len >=TE_D_ADDRESS_LEN)
	{
		AfxMessageBox("the address is too long");
	}
	strncpy(T_contact.addresssite,m_ContactAddress.GetBuffer(len),len);
	int nIndex = m_ComboGroup.GetCurSel();
	if(nIndex !=CB_ERR)
	{
		m_ComboGroup.GetLBText(nIndex , m_strGroup);
		int len = m_strGroup.GetLength();
		if(len >= TE_D_GROUPNAME_LEN)
		{
			AfxMessageBox("the groupname is too long");
		}
		strncpy(TempGroup,m_strGroup.GetBuffer(len),len);
	}
	if(m_ContactName == "")
	{
		AfxMessageBox(_T("please input contacter name"));
		return;
	}
	if(m_info->contacttype == 0)
	{

		ret = TE_AddContact(T_contact,TempGroup);
		if(0 == ret)
		{
			AfxMessageBox("add contact success");
			m_info->OnUpdateRecordList();
		}
		else if(TE_SDK_ContactWhetherReplace == ret)
		{
			if(MessageBox("contact already exist,if replace","system hint",MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			ret = TE_ReplaceContact(T_contact);
			if(0 == ret)
			{
				AfxMessageBox(_T("replace success"));
				m_info->OnUpdateRecordList();
			}
			else
			{
				AfxMessageBox(_T("replace failed"));
			}
		}
		else
		{
				AfxMessageBox("add contact failed");
		}
	
	}
	if(m_info->contacttype == 1)
	{

		
			 ret = TE_EditContact(T_contact);
		if(0 == ret)
		{

			AfxMessageBox("edit contact success");
			m_info->OnUpdateRecordList();
		}
		else if(TE_SDK_ContactWhetherReplace == ret)
		{
			if(MessageBox("contact already exist,if replace","system hint",MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			ret = TE_ReplaceContact(T_contact);
			if(0 == ret)
			{
				AfxMessageBox(_T("replace success"));
				m_info->OnUpdateRecordList();
			}
			else
			{
				AfxMessageBox(_T("replace failed"));
			}

		}
		else
		{
			AfxMessageBox("edit contact failed");
		}
	}
	OnOK();
}

void CTE_ContactInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TE_S_CONTACT_INFO  m_contact;
	int len =0,ret=0;
	memset(&m_contact, 0, sizeof(TE_S_CONTACT_INFO));
	len = m_ContactName.GetLength();
	strncpy(m_contact.name ,m_ContactName.GetBuffer(len),len);
	len = m_ContactNumber.GetLength();
	strncpy(m_contact.ucAcc ,m_ContactNumber.GetBuffer(len),len);
	len = m_ContactDepartment.GetLength();
	strncpy(m_contact.deptname ,m_ContactDepartment.GetBuffer(len),len);
	len = m_ContactAddress.GetLength();
	strncpy(m_contact.addresssite,m_ContactAddress.GetBuffer(len),len);
	len = m_ContactEmail.GetLength();
	strncpy(m_contact.email ,m_ContactEmail.GetBuffer(len),len);
	len = m_ContactMobilephone.GetLength();
	strncpy(m_contact.mobile ,m_ContactMobilephone.GetBuffer(len),len);
	len = m_ContactOfficephone.GetLength();
	strncpy(m_contact.officePhone ,m_ContactOfficephone.GetBuffer(len),len);
		 ret = TE_EditContact(m_contact);
}
