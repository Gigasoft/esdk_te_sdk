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
#include "TE_RenameGroup.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_RenameGroup,CDialog)

CTE_RenameGroup::CTE_RenameGroup(CWnd* pParent /*NULL*/)
:CDialog(CTE_RenameGroup::IDD,pParent)
, m_RenameGroup(_T(""))
{
	m_ContactPoint = (CTE_Contact*)pParent;
}

CTE_RenameGroup::~CTE_RenameGroup()
{
		
}

void CTE_RenameGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_RenameGroup);
}

BEGIN_MESSAGE_MAP(CTE_RenameGroup,CDialog)
	ON_BN_CLICKED(IDOK, &CTE_RenameGroup::OnBnClickedOk)
END_MESSAGE_MAP()


void CTE_RenameGroup::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret =0,i=0;
	char GroupName[512]={0};
	UpdateData(TRUE);
	char OldGroupName [512] = {0};
	int len = m_RenameGroup.GetLength();
	strncpy(GroupName,m_RenameGroup.GetBuffer(len),len);

	strncpy(OldGroupName,m_reName.c_str(),65);
	ret = TE_RenameCustomGroup(GroupName,OldGroupName);
	if(0 == ret)
	{
		MessageBox("rename group success");
		m_ContactPoint->OnUpdateRecordList();
	}
	else
	{
		MessageBox(("rename group failed"));
	}
	OnOK();
}
