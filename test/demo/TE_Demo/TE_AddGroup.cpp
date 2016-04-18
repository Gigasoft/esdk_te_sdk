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
#include "TE_AddGroup.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "TE_Contact.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_Group,CDialog)

CTE_Group::CTE_Group(CWnd* pParent /*NULL*/)
:CDialog(CTE_Group::IDD,pParent)
, m_addgroup(_T(""))
{
	m_demoLg =  (CTE_DemoDlg *)pParent;
}

CTE_Group::~CTE_Group()
{
	
}

void CTE_Group::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_addgroup);
}

BEGIN_MESSAGE_MAP(CTE_Group,CDialog)
	ON_BN_CLICKED(IDOK, &CTE_Group::OnBnClickedOk)
END_MESSAGE_MAP()
void CTE_Group::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();

	int ret =0;
	char GroupName[512]={0};
	std::wstring cstrName;
	UpdateData(TRUE);
	int len = m_addgroup.GetLength();
	strncpy(GroupName,m_addgroup.GetBuffer(len),len);
	/*cstrName = m_demoLg->CstringToWstring(m_addgroup);
	strncpy(GroupName,m_demoLg->Unicode2Utf8(cstrName).c_str(),65);*/
	
	ret = TE_CreateCustomGroup(GroupName);
	if(0 == ret)
	{
		MessageBox("add group success");
		m_contactdlg->OnUpdateRecordList();
	}
	else
	{
		MessageBox(("add group failed"));
	}
}
