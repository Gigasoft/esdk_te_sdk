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
// TE_DIAL_PLATE.cpp : 实现文件
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "TE_DIAL_PLATE.h"


// CTE_DIAL_PLATE 对话框

IMPLEMENT_DYNAMIC(CTE_DIAL_PLATE, CDialog)

CTE_DIAL_PLATE::CTE_DIAL_PLATE(CWnd* pParent /*=NULL*/)
	: CDialog(CTE_DIAL_PLATE::IDD, pParent)
	, m_dialNums(_T(""))
{

}

CTE_DIAL_PLATE::~CTE_DIAL_PLATE()
{
}

void CTE_DIAL_PLATE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dialNums);
}


BEGIN_MESSAGE_MAP(CTE_DIAL_PLATE, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CTE_DIAL_PLATE::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTE_DIAL_PLATE::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTE_DIAL_PLATE::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTE_DIAL_PLATE::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTE_DIAL_PLATE::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTE_DIAL_PLATE::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTE_DIAL_PLATE::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTE_DIAL_PLATE::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTE_DIAL_PLATE::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTE_DIAL_PLATE::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTE_DIAL_PLATE::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CTE_DIAL_PLATE::OnBnClickedButton12)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CTE_DIAL_PLATE 消息处理程序

void CTE_DIAL_PLATE::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"1";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"1");
}

void CTE_DIAL_PLATE::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"2";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"2");
}

void CTE_DIAL_PLATE::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"3";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"3");
}

void CTE_DIAL_PLATE::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"4";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"4");
}

void CTE_DIAL_PLATE::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"5";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"5");
}

void CTE_DIAL_PLATE::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"6";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"6");
}

void CTE_DIAL_PLATE::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"7";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"7");
}

void CTE_DIAL_PLATE::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"8";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"8");
}

void CTE_DIAL_PLATE::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"9";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"9");
}

void CTE_DIAL_PLATE::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"*";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"*");
}

void CTE_DIAL_PLATE::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"0";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"0");
}

void CTE_DIAL_PLATE::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dialNums=m_dialNums+"#";
	UpdateData(FALSE);
	TE_SendDTMF(m_callId,"#");
}


void CTE_DIAL_PLATE::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	if ( WA_INACTIVE == nState) 
	{
		m_dialNums="";
		UpdateData(FALSE);
		//this->DestroyWindow();
		ShowWindow(SW_HIDE);
	}
}