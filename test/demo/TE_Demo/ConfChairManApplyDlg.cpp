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
// ConfChairManApplyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "ConfChairManApplyDlg.h"
#include "TE_ConfCtrl.h"

// ConfChairManApplyDlg �Ի���

IMPLEMENT_DYNAMIC(ConfChairManApplyDlg, CDialog)

ConfChairManApplyDlg::ConfChairManApplyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ConfChairManApplyDlg::IDD, pParent)
	, m_edtPassWord(_T(""))
{
	m_FromDlg=NULL;
}

ConfChairManApplyDlg::~ConfChairManApplyDlg()
{
	m_FromDlg=NULL;
}

void ConfChairManApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_edtPassWord);
}


BEGIN_MESSAGE_MAP(ConfChairManApplyDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &ConfChairManApplyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &ConfChairManApplyDlg::OnBnClickedButtonApply)
	ON_MESSAGE(WM_CONF_APPLY_CHAIRMAN_RESULT, &ConfChairManApplyDlg::ApplyChairmanResult)
END_MESSAGE_MAP()


// ConfChairManApplyDlg ��Ϣ�������

HBRUSH ConfChairManApplyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1 || pWnd->GetDlgCtrlID() == IDC_STATIC2)
	{
		pDC->SetTextColor(RGB(190, 190, 190));
	} 

	return hbr;
}

void ConfChairManApplyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void ConfChairManApplyDlg::OnBnClickedButtonApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int len = 0;
	char passWD[20]={0};

	UpdateData(TRUE);

	len = m_edtPassWord.GetLength();
	if(len>19)
	{
		AfxMessageBox("the password too long,please enter again!");
		return;
	}

	strncpy(passWD, m_edtPassWord.GetBuffer(len), len);

	if(TE_SDK_Failed==TE_ApplyConfChairman(passWD))
	{
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("ʧ�ܣ�������ϯ�Ѵ���"));
	}
}


LRESULT ConfChairManApplyDlg::ApplyChairmanResult(WPARAM wParm, LPARAM Lparam)
{
	if (TE_E_OPERATION_SUCCESS == result)
	{
		/*if (m_FromDlg!=NULL)
		{
			m_FromDlg->RefreshAttendeeList();
		}*/
		if (m_FromDlg!=NULL)
		{
			::PostMessage(m_FromDlg->GetSafeHwnd(), WM_CONF_APPLY_SUCCEED, NULL, NULL);
		}

		CloseConfApplyChairMan();
	}
	else
	{
		//GetDlgItem(IDC_STATIC3)->SetWindowText(dlg.m_nvalue);
		
		switch (result)
		{
		case TE_E_OPERATION_NO_CAP_TO_BE_CHAIR:
			GetDlgItem(IDC_STATIC3)->SetWindowText(_T("ʧ�ܣ��ն�����ϯ����"));
			break;
		case TE_E_OPERATION_NO_CHAIR_FUNC:
			GetDlgItem(IDC_STATIC3)->SetWindowText(_T("ʧ�ܣ���������ϯ����"));
			break;
		case TE_E_OPERATION_CHAIR_EXIST:
			GetDlgItem(IDC_STATIC3)->SetWindowText(_T("ʧ�ܣ�������ϯ�Ѵ���"));
			break;
		case TE_E_OPERATION_CHAIR_PWD_ERR:
			GetDlgItem(IDC_STATIC3)->SetWindowText(_T("ʧ�ܣ���ϯ�������"));
			break;
		default:
			GetDlgItem(IDC_STATIC3)->SetWindowText(_T("ʧ�ܣ�����δ֪����"));
		}
		UpdateData(FALSE);
	}

	
	return 0L;
}


void ConfChairManApplyDlg::CloseConfApplyChairMan()
{
	if (m_FromDlg!=NULL)
	{
		m_FromDlg->m_applyChairmanDlg=NULL;
	}
	this->DestroyWindow();
}