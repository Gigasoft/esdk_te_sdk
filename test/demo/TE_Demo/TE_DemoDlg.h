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
// TE_DemoDlg.h : 头文件
//

#pragma once
#include "TE_InComingCall.h"
#include "TE_Preview.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "DeskRimDlg.h"
#include "EnumProc.h"
#include "OutSideWindow.h"
#include "TE_HandleCallDlg.h"
#include "TE_Contact.h"
#include "TE_ConfereceContacts.h"
#include "TE_EnterpriseAddr.h"
#include "TE_HistoryRecord.h"



static const int IM_CAPTURE_CHANGE_TIMER = 5017;
static const int IM_CAPTURE_CHANGE_TIME = 500;


static const int IM_CAPTURE_CHANGE_DRAW_TIMER = 5018;
static const int IM_CAPTURE_CHANGE_DRAW_TIME = 200;


#define ECS_MSG_BEGIN				(WM_APP + 1001) //消息开始ID
#define WM_SIGNIN_NOTIFY			(ECS_MSG_BEGIN+1)
#define WM_AVSESSION_CONNECTED		(ECS_MSG_BEGIN+2)
#define WM_AVSESSION_CLOSED			(ECS_MSG_BEGIN+3)
#define WM_AVSESSION_ADDED			(ECS_MSG_BEGIN+4)
#define WM_AVSESSION_CALLRING		(ECS_MSG_BEGIN+5)
#define WM_IM_BFCP_MODIFIED_RESULT  (ECS_MSG_BEGIN+6)
#define WM_DATA_START_SENDING    (ECS_MSG_BEGIN+7)//发送辅流申请成功 显示正在发送
#define WM_DATA_START_RECVING    (ECS_MSG_BEGIN+8)
#define WM_DATA_STOPED           (ECS_MSG_BEGIN+9) //辅流发送申请失败 发送停止  接收停止
#define WM_DATA_START_FAIL       (ECS_MSG_BEGIN+10)
#define WM_CONFERENCE_CREATE_CONF_STATE_CHANGE		(ECS_MSG_BEGIN+11)
#define WM_CONFERENCE_APPLY_CHAIRMAN		(ECS_MSG_BEGIN+12)
#define WM_CONFERENCE_RELEASE_CHAIRMAN		(ECS_MSG_BEGIN+13)
#define WM_CONFERENCE_MEMLISTREFRESH		(ECS_MSG_BEGIN+14)
#define WM_CONFERENCE_CHAIRMAN_THENDO		(ECS_MSG_BEGIN+15)
#define WM_CONFERENCE_ADDHALL_RESULT		(ECS_MSG_BEGIN+16)
#define WM_CONFERENCE_EXTEND_RESULT			(ECS_MSG_BEGIN+17)
#define WM_CONFERENCE_EXTENDTIME_NOTE		(ECS_MSG_BEGIN+18)
#define WM_CONFERENCE_BROADCAST_RESULT		(ECS_MSG_BEGIN+19)
#define WM_CONFERENCE_WATCH_RESULT			(ECS_MSG_BEGIN+20)
#define WM_OPEN_VEDIO						(ECS_MSG_BEGIN+21)
#define WM_CLOSE_VEDIO						(ECS_MSG_BEGIN+22)
#define WM_ANSWER_VEDIO						(ECS_MSG_BEGIN+23)
#define WM_UPDATERECORDLIST		(ECS_MSG_BEGIN + 24)
#define WM_NETCONTACTSLIST		(ECS_MSG_BEGIN + 25)
#define WM_LDAPCONTACTSLIST	(ECS_MSG_BEGIN + 26)
#define WM_MESSAGE_NETBOOKTYPE_NOTIFY		(ECS_MSG_BEGIN + 27)
#define WM_CONTACTSTATUS        (ECS_MSG_BEGIN +28)


// CTE_DemoDlg 对话框
class CTE_DemoDlg : public CDialog
{
// 构造
public:
	CTE_DemoDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTE_DemoDlg();

// 对话框数据
	enum { IDD = IDD_TE_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	void CaptureChangeTime_T();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnSigninNotify(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnAVSessAdded(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnAVSessClosed(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnAVSessConnected(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnAVSessCallRing(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnBFCPModifiedResult(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnDataStartRecving(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnDataStartSending(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnDataStoped(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnDataStartFail(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfCreateStateChange(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfApplyChairman(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfReleaseChairman(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfAttendeeListRefresh(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfChairManInd(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfAddHallRst(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfExtendTimeRst(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfTimeRemnant(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfBroadcastRest(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnConfWatchRest(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnOpenVedio(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnCloseVedio(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnAnswerVedio(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnLdapContactsList(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnMessageNetBookType(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnContactStaus(WPARAM wParm, LPARAM Lparam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedLogin();
	CString m_CStrServerIP;
	CString m_CStrPortNum;
	CString m_CStrUsername;
	CString m_CStrPassword;
	afx_msg void OnBnClickedCallButton();
	CString m_CStrCallNum;
	CTE_IncomingCall* m_incomingCall;
	CTE_HandleCallDlg* m_handCallDlg;
	CTE_Preview* m_Preview;
	CTE_Contact* m_Pcontact;
	CTE_Enterprise*  m_Enterprise;
	CTE_HistoryRecord* m_HistroyRecord;
	CTE_ConfContacts* m_pContactDlg;
	bool m_isLogin;
	afx_msg void OnClose();
	static bool m_bClose;
	afx_msg void OnBnClickedCheck2();
	CButton m_btnVideo;
	CIPAddressCtrl m_ipCtrlServerIP;
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedButtonVideopreview();

	void UpdateRimDlgs();
	void StartDrawRimDlg();
	HWND GetCurShareMainWnd(DWORD pid);

	CDeskRimDlg* m_pDeskRimDlg;

	UINT_PTR m_pCaptureWndTimer;
	
	DWORD m_dwPID;
	HWND mainWnd;

	bool isDataSending;

	COutSideWindow *m_pOutSideDlg;

	std::string Unicode2Utf8(const std::wstring& widestring);
	std::wstring Utf82Unicode(const std::string& utf8string);
	std::string  WSToString(const std::wstring& ws);
	std::wstring ctow(const char* src);
	std::wstring CstringToWstring(CString m_ContactName);
	CComboBox m_cameralist;
	void OnUpdateDeviceList(int choice);
	CString m_cameraname;
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonConfcreate();
	CStatic m_confInfo;
	void CTE_DemoDlg::ContactCall(TE_CHAR* callnum);
	void CTE_DemoDlg::ContactVideoCall(TE_CHAR* callnum);
	void CTE_DemoDlg::ContactAudioCall(TE_CHAR* callnum);
	afx_msg void OnBnClickedButtonSwitchCamera();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_transMode;
	CComboBox m_audioInList;
	CComboBox m_audioOutList;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedButton3();
	void OnShowEnterpriseResult(TE_S_CONTACTS_INFO* contactsList);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnStnClickedStaticInfo();
	CIPAddressCtrl m_licenseServerIP;
};
