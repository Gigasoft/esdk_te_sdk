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
#include "TE_EnterpriseAddr.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_Enterprise,CDialog)

CTE_Enterprise::CTE_Enterprise(CWnd* pParent /*NULL*/)
:CDialog(CTE_Enterprise::IDD,pParent)
, m_search(_T(""))
{
	m_EnterpriseContacts = (CTE_DemoDlg*)pParent;
}

CTE_Enterprise::~CTE_Enterprise()
{
	
}

void CTE_Enterprise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_EnterpriseList);
	DDX_Text(pDX, IDC_EDIT_SEARCH_ADDR, m_search);
}

BEGIN_MESSAGE_MAP(CTE_Enterprise,CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CTE_Enterprise::OnBnClickedButton1)
END_MESSAGE_MAP()



void CTE_Enterprise::OnBnClickedButton1()
{
	//TE_InitNetBookType();
	// TODO: 在此添加控件通知处理程序代码
	char keyword[512]={""};
	int len = 0;
	UpdateData(TRUE);
	len = m_search.GetLength();
	strncpy(keyword,m_search.GetBuffer(len),len);
	TE_S_CONTACTS_INFO contactsList;
	contactsList.contact = NULL;
	contactsList.num = 0;
	TE_UINT32 enterpriseType =1;
	TE_GetEnterpriseBookType(&enterpriseType);
	if(1 == enterpriseType)
	{
		TE_SearchLdap( keyword);
	}
	else
	{
		int ret = TE_SearchFtp(keyword,&contactsList);
		m_EnterpriseContacts->OnShowEnterpriseResult(&contactsList);
	}

	TE_FreeMemory(contactsList.contact);
	
}
