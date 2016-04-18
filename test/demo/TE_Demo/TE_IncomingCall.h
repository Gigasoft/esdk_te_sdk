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
#include "resource.h"
#include "afxcmn.h"
#include <vector>
#include <map>

#include "TE_ConfCtrl.h"
#include "TE_DIAL_PLATE.h"

#define SECOND (1*1000)
const int TIME_ID = 2000;
const int CLOSE_ID = 2001;

// CTE_IncomingCall 对话框

#define CALL_MSG_BEGIN					(WM_APP + 1101) //消息开始ID
#define WM_CALL_AVSESSION_CONNECTED		(CALL_MSG_BEGIN+2)
#define WM_CALL_AVSESSION_CLOSED		(CALL_MSG_BEGIN+3)
#define WM_CALL_AVSESSION_ADDED			(CALL_MSG_BEGIN+4)
#define WM_CALL_UPDATE_STATE			(CALL_MSG_BEGIN+5)

typedef struct tagWndInfo{
	void*			hWnd;
	CString         csWndTitle;
	HICON			hSmallIcon;
	BOOL			bChecked;
}ST_WndInfo;


class CTE_IncomingCall : public CDialog
{
	DECLARE_DYNAMIC(CTE_IncomingCall)

public:
	CTE_IncomingCall(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTE_IncomingCall();

// 对话框数据
	enum { IDD = IDD_COMMINGCALL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	afx_msg LRESULT UpdateCallState(WPARAM wParm, LPARAM Lparam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

public:
	TE_S_CALL_STATE_INFO m_CallStateInfo;
	bool m_isMicMute;
	bool m_isSpeakerMute;
	bool m_isVideo;
	bool m_isCheckVedio;
	bool m_isCheckAudio;
	bool m_bIsHangup;
	bool m_isSharingWnd;
	afx_msg void OnBnClickedSpeakerButton2();
	afx_msg void OnBnClickedMicButton2();
	CButton m_bSpeaker;
	CButton m_bMIC;
	long m_lDuration;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedHangupButton();
	CString m_CallState;
	
	CButton m_btnAnswer;
	CButton m_btnReject;
	CButton m_btnHangup;
	CStatic m_RemoteWindow;
	CStatic m_LocalWindow;

    
	HWND m_dataShareWind;

	CButton m_btnVideo;
	afx_msg void OnBnClickedVideoButton();
	afx_msg void OnBnClickedStartshareBtn();
	afx_msg void OnBnClickedStopshareBtn();
	static BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam);
	CButton m_btnShare;
	CStatic m_displayShareWind;
	CButton m_btnStopShare;
	CListCtrl m_listApps;
	char callername[TE_D_NAME_LEN+1];
	afx_msg void OnBnClickedShareexeBtn();
	BOOL GetAppList();
	afx_msg void OnNMClickListApps(NMHDR *pNMHDR, LRESULT *pResult);

	bool isEXEshare;
	CButton exeShareBtn;
	CRect rectLarge;
	CRect rectSmall;
	CStatic m_bound;
	afx_msg void OnLvnItemchangedListApps(NMHDR *pNMHDR, LRESULT *pResult);

	CToolTipCtrl m_ToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonConf();
	CButton m_btnConfCtrl;


	CTE_ConfCtrl* m_confCtrl;
	CTE_DIAL_PLATE* m_dailCtrl;
	CButton m_btnAtov;
	CButton m_btnVtoa;
	afx_msg void OnBnClickedBtnAtov();
	afx_msg void OnBnClickedBtnVtoa();
	afx_msg void OnBnClickedBtnDialPlate();
	afx_msg void OnNMCustomdrawSliderVoiceout(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSpeakerButton(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderVoicein(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_vedioAnswer;
	afx_msg void OnBnClickedBtnVedioanswer();
};
