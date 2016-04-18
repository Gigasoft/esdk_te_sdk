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
#pragma once

class CTE_IncomingCall;

// CTE_HandleCallDlg 对话框

class CTE_HandleCallDlg : public CDialog
{
	DECLARE_DYNAMIC(CTE_HandleCallDlg)

public:
	CTE_HandleCallDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTE_HandleCallDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ANSWER_REJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	TE_S_CALL_STATE_INFO m_callInfo;
	CTE_IncomingCall * m_callIncome;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
