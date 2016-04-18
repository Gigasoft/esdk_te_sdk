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
#include "TE_NickName.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_Nickname,CDialog)

CTE_Nickname::CTE_Nickname(CWnd* pParent /*NULL*/)
:CDialog(CTE_Nickname::IDD,pParent)
, m_NickName(_T(""))
{
	m_setNickName = (CTE_Contact*)pParent;
}

CTE_Nickname::~CTE_Nickname()
{

}

void CTE_Nickname::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_NickName);
}

BEGIN_MESSAGE_MAP(CTE_Nickname,CDialog)
	ON_BN_CLICKED(IDOK, &CTE_Nickname::OnBnClickedOk)
END_MESSAGE_MAP()




void CTE_Nickname::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret =0,i=0;
	char NickName[512]={0};
	char OldNickName[512]={0};
	UpdateData(TRUE);
	int len = m_NickName.GetLength();
	strncpy(NickName,m_NickName.GetBuffer(len),len);
	TE_S_CONTACT_INFO SetNickName;
	if(!m_setNickName)
	{
		return;
	}
	strncpy(OldNickName,m_setNickName->m_contactName.c_str(),sizeof(OldNickName));
	TE_GetContactByName(OldNickName,&SetNickName);
	ret = TE_SetDisplayName(SetNickName.name,NickName);
	if(0==ret)
	{
		AfxMessageBox(_T("set NickName success"));
	}
	else
	{
		AfxMessageBox(_T("set NickName failed"));
	}
	OnOK();
}
