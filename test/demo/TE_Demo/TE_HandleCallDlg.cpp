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
// TE_HandleCallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "TE_HandleCallDlg.h"
#include "TE_IncomingCall.h"



// CTE_HandleCallDlg 对话框

IMPLEMENT_DYNAMIC(CTE_HandleCallDlg, CDialog)

CTE_HandleCallDlg::CTE_HandleCallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTE_HandleCallDlg::IDD, pParent)
{
	m_callIncome=NULL;
}

CTE_HandleCallDlg::~CTE_HandleCallDlg()
{
}

void CTE_HandleCallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTE_HandleCallDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CTE_HandleCallDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTE_HandleCallDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTE_HandleCallDlg 消息处理程序

void CTE_HandleCallDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TE_AnswerVideoCall(m_callInfo.ulCallID,0);

	m_callIncome->m_isCheckVedio=TRUE;
	m_callIncome->m_isCheckAudio=FALSE;
	m_callIncome->m_isVideo = TRUE;
	m_callIncome->m_btnShare.EnableWindow(TRUE);
	m_callIncome->m_btnStopShare.EnableWindow(TRUE);
	m_callIncome->exeShareBtn.EnableWindow(TRUE);
	m_callIncome->m_LocalWindow.ShowWindow(SW_SHOW);
	m_callIncome->m_RemoteWindow.ShowWindow(SW_SHOW);
	m_callIncome->m_btnVtoa.EnableWindow(TRUE);
	m_callIncome->m_btnVtoa.ShowWindow(SW_SHOW);
    m_callIncome->m_btnAtov.EnableWindow(FALSE);
	m_callIncome->m_btnAtov.ShowWindow(SW_HIDE);
	m_callIncome->m_btnVideo.EnableWindow(TRUE);

	::SetWindowPos(m_callIncome->GetSafeHwnd(),NULL,0,0,m_callIncome->rectLarge.Width(),m_callIncome->rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);


	this->DestroyWindow();

}

void CTE_HandleCallDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//TE_RejectCall(m_callInfo.ulCallID);

	TE_UpdateCall(m_callInfo.ulCallID,TE_E_CALL_TYPE_IPAUDIO);

	this->DestroyWindow();
}

