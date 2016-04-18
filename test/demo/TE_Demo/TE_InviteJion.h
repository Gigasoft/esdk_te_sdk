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
#include "afxwin.h"


// CTE_InviteJion 对话框
#define CONF_ADDHALL_MSG_BEGIN					(WM_APP + 1401) //消息开始ID
#define WM_CONF_ADD_HALL_RESULT			(CONF_ADDHALL_MSG_BEGIN+1)


class CTE_InviteJion : public CDialog
{
	DECLARE_DYNAMIC(CTE_InviteJion)

public:
	CTE_InviteJion(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTE_InviteJion();

	// 对话框数据
	enum { IDD = IDD_DIALOG_INVITETOJION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT AddHallResult(WPARAM wParm, LPARAM Lparam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CCheckListBox m_memLists;
	//CListBox m_memLists;
	afx_msg void OnLbnSelchangeListMembers();
	afx_msg void OnBnClickedBtnInvite();

	TE_S_ADDSITETOCONF_RESULT m_addHallRest;
	afx_msg void OnBnClickedButtonSearch();
	CString m_SearchContact;
};
