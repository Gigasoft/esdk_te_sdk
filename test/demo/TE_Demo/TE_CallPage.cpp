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
// TE_CallPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "TE_Demo.h"
#include "TE_CallPage.h"
//#include "TESDK.h"

// CTE_CallPage �Ի���

IMPLEMENT_DYNAMIC(CTE_CallPage, CPropertyPage)

CTE_CallPage::CTE_CallPage()
	: CPropertyPage(CTE_CallPage::IDD)
{

}

CTE_CallPage::~CTE_CallPage()
{
}

void CTE_CallPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTE_CallPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CALL_BUTTON, &CTE_CallPage::OnBnClickedCallButton)
END_MESSAGE_MAP()


// CTE_CallPage ��Ϣ�������

void CTE_CallPage::OnBnClickedCallButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
