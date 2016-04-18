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
#include "afxcmn.h"
#include "resource.h"

#include "ConfChairManApplyDlg.h"
#include "TE_InviteJion.h"
#include "TE_ExtendTime.h"

// CTE_ConfCtrl 对话框
#define CONF_CTRL_MSG_BEGIN					(WM_APP + 1201) //消息开始ID
#define WM_CONF_FRESH_MEMLIST			(CONF_CTRL_MSG_BEGIN+1)
#define WM_CONF_RELEASE_CHAIRMAN_RESULT	(CONF_CTRL_MSG_BEGIN+2)
#define WM_CONF_APPLY_SUCCEED			(CONF_CTRL_MSG_BEGIN+3)
#define WM_CONF_EXTEND_TIME_REST		(CONF_CTRL_MSG_BEGIN+4)
#define WM_CONF_EXTEND_REMAIN_TIME		(CONF_CTRL_MSG_BEGIN+5)
#define WM_CONF_BROADCAST_REST			(CONF_CTRL_MSG_BEGIN+6)
#define WM_CONF_WATCH_REST				(CONF_CTRL_MSG_BEGIN+7)


class CTE_ConfCtrl : public CDialog
{
	DECLARE_DYNAMIC(CTE_ConfCtrl)

public:
	CTE_ConfCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTE_ConfCtrl();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONF };

protected:
	afx_msg void OnPaint();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT ToRefreshAttendeeList(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT ToReleaseChairmanRst(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT AfterApplySucceed(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT ExtendTimeResult(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT ExtendTimeRemain(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT BroadcastResult(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT WatchResult(WPARAM wParm, LPARAM Lparam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	void RefreshAttendeeList();

	CToolTipCtrl m_ToolTip;
	CButton m_extendTimeBtn;
	CButton m_applyChairMan;
	CButton m_addMember;
	//CListCtrl m_confMemList;
	afx_msg void OnNMRClickListJionedMem(NMHDR *pNMHDR, LRESULT *pResult);

	CImageList myimage;

	CBitmap bitmapMuti;
	CBitmap bitmapUnmute;
	CBitmap bitmapMute;
	CBitmap bitmapMan;
	CBitmap bitmapOut;
	CBitmap bitmapBroad;

	CListCtrl m_confMemList;
	afx_msg void OnBnClickedBtnExtendTime();
	afx_msg void OnBnClickedBtnApplyChairman();

	ConfChairManApplyDlg *m_applyChairmanDlg;
	CTE_InviteJion *m_inviteDlg;
	CTE_ExtendTime *m_extendTime;

	afx_msg void OnBnClickedBtnReleaseChairman();
	CButton m_releaseChairMan;

	bool result;
	bool extendRest;
	int remainTime;
	int broadcastRest;
	int watchRest;


	afx_msg void OnBnClickedBtnAddMem();
	afx_msg void OnMenuMute();


	TE_S_SITE_JIONEDLIST _confHallList;
	TE_S_SITE_INFO localHall;

	int curHall;
	afx_msg void OnMenuUnmute();
	afx_msg void OnMenuApplyChairman();
	afx_msg void OnMenuReleaseChairman();
	afx_msg void OnMenuBroadcast();
	afx_msg void OnMenuStopBroadcast();
	afx_msg void OnMenuCallupHall();
	afx_msg void OnMenuDeleteHall();
	afx_msg void OnMenuHandup();
	afx_msg void OnMenuWatch();
};
