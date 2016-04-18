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
#include "TE_ConfereceContacts.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_ConfContacts,CDialog)

CTE_ConfContacts::CTE_ConfContacts(CWnd* pParent /*NULL*/)
:CDialog(CTE_ConfContacts::IDD,pParent)
{
	demodlg = NULL;

	
}

CTE_ConfContacts::~CTE_ConfContacts()
{

}

void CTE_ConfContacts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ConfContactsList);
}

BEGIN_MESSAGE_MAP(CTE_ConfContacts,CDialog)
	ON_BN_CLICKED(IDOK, &CTE_ConfContacts::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL CTE_ConfContacts::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	LONG lStyle;
	lStyle = GetWindowLong(m_ConfContactsList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_ConfContactsList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_ConfContactsList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件

	m_ConfContactsList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_ConfContactsList.InsertColumn( 1, "NAME", LVCFMT_LEFT, 240 );
	m_ConfContactsList.InsertColumn( 2, "NUMBER", LVCFMT_LEFT, 240 );
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTE_ConfContacts::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
	int i=0;
	TE_S_SITE_INVITEDLIST _contacts;
	
	int rowEnd = m_ConfContactsList.GetItemCount();
	_contacts.listCount = 0;
	for(i=0;i<rowEnd;i++)
	{
		if(m_ConfContactsList.GetCheck(i))
		{
			CString exportGroup= m_ConfContactsList.GetItemText(i,1);
			int len = exportGroup.GetLength();
			TE_CHAR* ConfContacts=new TE_CHAR[len+1];
			memset(ConfContacts,0,len+1);
			strncpy(ConfContacts,exportGroup.GetBuffer(len),len);
			_contacts.list[_contacts.listCount] = ConfContacts;
		
			_contacts.listCount++;
		}
	}
	//_contacts.list[0]="01052418";
	//_contacts.list[1]="01052419";
	//_contacts.listCount=1;

	TE_CreateConf(&_contacts);
	demodlg->m_confInfo.SetWindowText(_T("等待服务响应，请稍后..."));

}
