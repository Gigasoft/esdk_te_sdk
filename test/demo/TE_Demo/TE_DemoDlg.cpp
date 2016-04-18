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
// TE_DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "TE_Preview.h"
#include "TE_IncomingCall.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(lib,"ws2_32.lib")



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTE_DemoDlg 对话框

void CALLBACK TeEventCallBack(
    TE_INT32   iEventType,    //事件类型
    TE_VOID*   pEventBuf,     //事件数据
    TE_UINT32  uiBufSize,      //buf长度
    TE_VOID*   pUserData     //用户数据，自定义，相应回调函数被调用时返回该参数
	)
{
	switch(iEventType)
	{
		case TE_E_EVT_LOGIN_RESULT:
		{
			CTE_DemoDlg *pWnd =NULL;
			TE_S_LOGIN_RESULT *pLoginResult = NULL;


			pWnd = (CTE_DemoDlg *)pUserData;
			pLoginResult = (TE_S_LOGIN_RESULT *)pEventBuf; 
			if(!pWnd || !pLoginResult)
			{
				return;
			}

			::PostMessage(pWnd->GetSafeHwnd(), WM_SIGNIN_NOTIFY, WPARAM(pLoginResult->loginState), NULL);	// send  sign in state message
			break;
		}
		case TE_E_EVT_CALL_RESULT:
		{
			TE_S_CALL_STATE_INFO *pCallStateInfo = new TE_S_CALL_STATE_INFO;
			CTE_DemoDlg *pWnd =NULL;
			pWnd = (CTE_DemoDlg *)pUserData;

			memcpy(pCallStateInfo, pEventBuf, sizeof(TE_S_CALL_STATE_INFO));
			if (TE_E_CALL_EVENT_AUDIOVIDEOINCOMING == pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_AVSESSION_ADDED, NULL, LPARAM(pCallStateInfo));	//send audio/video coming call message.

			}
			else if(TE_E_CALL_EVENT_CLOSE == pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_AVSESSION_CLOSED, NULL, LPARAM(pCallStateInfo));	//send call end message.

			}
			else if(TE_E_CALL_EVENT_ANSWERRSP == pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_AVSESSION_CONNECTED, NULL, LPARAM(pCallStateInfo)); //send receive call message.

			}
			else if(TE_E_CALL_EVENT_CALLRING == pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_AVSESSION_CALLRING, NULL, LPARAM(pCallStateInfo)); //send call ring message.
			}
			else if( TE_E_CALL_EVENT_OPEN_VEDIO== pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_OPEN_VEDIO, NULL, NULL);
			}
			else if(TE_E_CALL_EVENT_CLOSE_VEDIO == pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CLOSE_VEDIO, NULL, NULL);
			}
			else if(TE_E_CALL_EVENT_ANSWER_VEDIO == pCallStateInfo->enCallEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_ANSWER_VEDIO, NULL, NULL);
			}

			break;
		}
		case TE_E_EVT_CONF_RESULT:
		{
			TE_S_CONF_RESULT *pConfRest = new TE_S_CONF_RESULT;
			CTE_DemoDlg *pWnd =NULL;
			pWnd = (CTE_DemoDlg *)pUserData;

			memcpy(pConfRest, pEventBuf, sizeof(TE_S_CONF_RESULT));
			if (TE_E_EVT_CREATE_CONF_STATE_CHANGE==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_CREATE_CONF_STATE_CHANGE, NULL, (LPARAM)pConfRest);

			} 
			else if(TE_E_EVT_APPLY_CONF_CHAIRMAN==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_APPLY_CHAIRMAN, NULL, (LPARAM)pConfRest);
			}
			else if(TE_E_EVT_RELEASE_CONF_CHAIRMAN==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_RELEASE_CHAIRMAN, NULL, (LPARAM)pConfRest);
			}
			else if(TE_E_EVT_CONF_MEMLISTREFRESH==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_MEMLISTREFRESH, NULL, NULL);
			}
			else if(TE_E_EVT_CONF_CHAIRMAN_THENDO==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_CHAIRMAN_THENDO, NULL, NULL);
			}
			else if(TE_E_EVT_ADDSITETOCONF_RESULT==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_ADDHALL_RESULT, NULL, (LPARAM)pConfRest);
			}
			else if(TE_E_EVT_CONF_EXTEND_RESULT==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_EXTEND_RESULT, NULL, (LPARAM)pConfRest);
			}
			else if(TE_E_EVT_CONF_EXTENDTIME_NOTE==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_EXTENDTIME_NOTE, NULL, (LPARAM)pConfRest);
			}
			else if(TE_E_EVT_CONF_BROADCAST_MEMLISTREFRESH==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_MEMLISTREFRESH, NULL, NULL);
			}
			else if(TE_E_EVT_CONF_BROADCAST_RESULT==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_BROADCAST_RESULT, NULL, (LPARAM)pConfRest);
			}
			else if(TE_E_EVT_SITE_WATCH_RESULT==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_CONFERENCE_WATCH_RESULT, NULL, (LPARAM)pConfRest);
			}

			break;
		}
		case TE_E_EVT_DATA_RESULT:
		{
			TE_S_CALL_STATE_INFO *pCallStateInfo = new TE_S_CALL_STATE_INFO;
			CTE_DemoDlg *pWnd =NULL;
			pWnd = (CTE_DemoDlg *)pUserData;
			memcpy(pCallStateInfo, pEventBuf, sizeof(TE_S_CALL_STATE_INFO));

			if (TE_E_DATA_EVENT_DATASEND == pCallStateInfo->enDataEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_DATA_START_SENDING, NULL, LPARAM(pCallStateInfo));	//send audio/video coming call message.

			}
			else if(TE_E_DATA_EVENT_DATARECIEVE == pCallStateInfo->enDataEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_DATA_START_RECVING, NULL, LPARAM(pCallStateInfo));	//send call end message.

			}
			else if(TE_E_DATA_EVENT_DATASTOPED == pCallStateInfo->enDataEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_DATA_STOPED, NULL, LPARAM(pCallStateInfo)); //send receive call message.

			}
			else if(TE_E_DATA_EVENT_DATASENDFAILURE == pCallStateInfo->enDataEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(), WM_DATA_START_FAIL, NULL, LPARAM(pCallStateInfo)); //send call ring message.
			}
			else if (TE_E_DATA_BFCPMODIFIED_RESULT== pCallStateInfo->enDataEvent)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_IM_BFCP_MODIFIED_RESULT, NULL, (LPARAM)pCallStateInfo);

			}

			break;
		}
		case  TE_E_EVT_ENTERPRISE_RESULT:
		{
			TE_S_ENTERPRISE_RESULT *pConfRest = new TE_S_ENTERPRISE_RESULT;
			CTE_DemoDlg *pWnd =NULL;
			pWnd = (CTE_DemoDlg *)pUserData;

			memcpy(pConfRest, pEventBuf, sizeof(TE_S_ENTERPRISE_RESULT));

			if(TE_E_EVT_LDAP_CONTACTS_ADDRESS==pConfRest->eventType)
			{
				::PostMessage(pWnd->GetSafeHwnd(),WM_LDAPCONTACTSLIST, NULL, (LPARAM)pConfRest);
			}
			break;
		}
		case TE_E_EVT_USER_STATUS:
		{
			int *pState = new int;
			CTE_DemoDlg *pWnd = NULL;
			pWnd = (CTE_DemoDlg *)pUserData;
			memcpy(pState,pEventBuf,sizeof(int));
			::PostMessage(pWnd->GetSafeHwnd(),WM_CONTACTSTATUS,NULL,(LPARAM)pState);
			break;
		}
		default:
		{
			break;
		}
		
	}
	
	return;
}
bool CTE_DemoDlg::m_bClose = false;

CTE_DemoDlg::CTE_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTE_DemoDlg::IDD, pParent)
	, m_CStrServerIP(_T("172.22.8.4"))
	, m_CStrPortNum(_T("5061"))
	, m_CStrUsername(_T("01052418"))
	, m_CStrPassword(_T("Huawei@123"))
	, m_CStrCallNum(_T("01052417"))
	, m_pDeskRimDlg(NULL)
	,isDataSending(false)
	,m_dwPID(0)
	,mainWnd(NULL)
	,m_pOutSideDlg(NULL)
	, m_cameraname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_incomingCall = NULL;
	m_handCallDlg=NULL;
	m_Preview = NULL;
	m_Pcontact = NULL;
	m_pContactDlg = NULL;
	m_Enterprise = NULL;
	m_HistroyRecord = NULL;
	m_isLogin = 0;
	TE_SetLogSwitch(1);
	//TE_SetLogPath("D:\\Client_Ext1_20151119\\test");
	TE_SetLogPath("");
	TE_SDK_Init();
	TE_SDK_SetEventCallBack(TeEventCallBack,this);
	
	
	
}

CTE_DemoDlg::~CTE_DemoDlg()
{
	delete m_Preview;
	m_Preview = NULL;
		delete m_Pcontact;
	m_Pcontact = NULL;
	delete m_Enterprise;
	m_Enterprise = NULL;
	delete m_HistroyRecord;
	m_HistroyRecord = NULL;

	if (m_handCallDlg)
	{
		(void)m_handCallDlg->DestroyWindow();
	}

	if (m_handCallDlg)
	{
		delete m_handCallDlg;
		m_handCallDlg=NULL;
	}
	

    if (m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd())) 
	{
		(void)m_pDeskRimDlg->DestroyWindow();
	}

	if (m_pDeskRimDlg)
	{
		delete m_pDeskRimDlg;
		m_pDeskRimDlg=NULL;
	}

	if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
	{
		(void)m_pOutSideDlg->DestroyWindow();
	}
	if (m_pOutSideDlg)
	{
		delete m_pOutSideDlg;
		m_pOutSideDlg=NULL;
	}
	isDataSending=false;
}


void CTE_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT_NUM, m_CStrPortNum);
	DDX_Text(pDX, IDC_USERNAME, m_CStrUsername);
	DDX_Text(pDX, IDC_PASSWORD, m_CStrPassword);
	DDX_Text(pDX, IDC_CALLNUM, m_CStrCallNum);
	DDX_Control(pDX, IDC_CHECK2, m_btnVideo);
	DDX_Control(pDX, IDC_SERVER_IPADDRESS, m_ipCtrlServerIP);
	DDX_Control(pDX, IDC_COMBO1, m_cameralist);
	DDX_CBString(pDX, IDC_COMBO1, m_cameraname);
	DDX_Control(pDX, IDC_STATIC_INFO, m_confInfo);
	DDX_Control(pDX, IDC_COMBO2, m_transMode);
	DDX_Control(pDX, IDC_COMBO3, m_audioInList);
	DDX_Control(pDX, IDC_COMBO4, m_audioOutList);
	DDX_Control(pDX, IDC_LICENSE_IPADDRESS, m_licenseServerIP);
}

BEGIN_MESSAGE_MAP(CTE_DemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDLOGIN, &CTE_DemoDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_CALL_BUTTON, &CTE_DemoDlg::OnBnClickedCallButton)
	ON_MESSAGE(WM_SIGNIN_NOTIFY, &CTE_DemoDlg::OnSigninNotify)
	ON_MESSAGE(WM_AVSESSION_ADDED, &CTE_DemoDlg::OnAVSessAdded)
	ON_MESSAGE(WM_AVSESSION_CLOSED, &CTE_DemoDlg::OnAVSessClosed)
	ON_MESSAGE(WM_AVSESSION_CONNECTED, &CTE_DemoDlg::OnAVSessConnected)
	ON_MESSAGE(WM_AVSESSION_CALLRING, &CTE_DemoDlg::OnAVSessCallRing)
	ON_MESSAGE(WM_IM_BFCP_MODIFIED_RESULT, &CTE_DemoDlg::OnBFCPModifiedResult)
	ON_MESSAGE(WM_DATA_START_SENDING, &CTE_DemoDlg::OnDataStartSending)	          //辅流发送请求成功响应
	ON_MESSAGE(WM_DATA_START_RECVING, &CTE_DemoDlg::OnDataStartRecving)                //有辅流到达
	ON_MESSAGE(WM_DATA_STOPED, &CTE_DemoDlg::OnDataStoped)                     //辅流关闭
	ON_MESSAGE(WM_DATA_START_FAIL,&CTE_DemoDlg::OnDataStartFail)                     //辅流请求发送失败
	ON_MESSAGE(WM_CONFERENCE_CREATE_CONF_STATE_CHANGE,&CTE_DemoDlg::OnConfCreateStateChange)
	ON_MESSAGE(WM_CONFERENCE_APPLY_CHAIRMAN,&CTE_DemoDlg::OnConfApplyChairman)
	ON_MESSAGE(WM_CONFERENCE_RELEASE_CHAIRMAN,&CTE_DemoDlg::OnConfReleaseChairman)
	ON_MESSAGE(WM_CONFERENCE_MEMLISTREFRESH,&CTE_DemoDlg::OnConfAttendeeListRefresh)
	ON_MESSAGE(WM_CONFERENCE_CHAIRMAN_THENDO,&CTE_DemoDlg::OnConfChairManInd)
	ON_MESSAGE(WM_CONFERENCE_ADDHALL_RESULT,&CTE_DemoDlg::OnConfAddHallRst)
	ON_MESSAGE(WM_CONFERENCE_EXTEND_RESULT,&CTE_DemoDlg::OnConfExtendTimeRst)
	ON_MESSAGE(WM_CONFERENCE_EXTENDTIME_NOTE,&CTE_DemoDlg::OnConfTimeRemnant)
	ON_MESSAGE(WM_CONFERENCE_BROADCAST_RESULT,&CTE_DemoDlg::OnConfBroadcastRest)
	ON_MESSAGE(WM_CONFERENCE_WATCH_RESULT,&CTE_DemoDlg::OnConfWatchRest)
	ON_MESSAGE(WM_OPEN_VEDIO,&CTE_DemoDlg::OnOpenVedio)
	ON_MESSAGE(WM_CLOSE_VEDIO,&CTE_DemoDlg::OnCloseVedio)
	ON_MESSAGE(WM_ANSWER_VEDIO,&CTE_DemoDlg::OnAnswerVedio)
	ON_MESSAGE(WM_LDAPCONTACTSLIST,&CTE_DemoDlg::OnLdapContactsList)
	ON_MESSAGE(WM_CONTACTSTATUS,&CTE_DemoDlg::OnContactStaus)
	

	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK2, &CTE_DemoDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDLOGOUT, &CTE_DemoDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOPREVIEW, &CTE_DemoDlg::OnBnClickedButtonVideopreview)
	ON_BN_CLICKED(IDC_BUTTON2, &CTE_DemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_CONFCREATE, &CTE_DemoDlg::OnBnClickedButtonConfcreate)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_CAMERA, &CTE_DemoDlg::OnBnClickedButtonSwitchCamera)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTE_DemoDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTE_DemoDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CTE_DemoDlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON3, &CTE_DemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTE_DemoDlg::OnBnClickedButton4)
	ON_STN_CLICKED(IDC_STATIC_INFO, &CTE_DemoDlg::OnStnClickedStaticInfo)
END_MESSAGE_MAP()


// CTE_DemoDlg 消息处理程序

BOOL CTE_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_ipCtrlServerIP.SetAddress(172,22,8,4);
	m_licenseServerIP.SetAddress(172,22,9,22);
	m_btnVideo.SetCheck(0);
	m_cameralist.EnableWindow(FALSE);
	m_audioInList.EnableWindow(FALSE);
	m_audioOutList.EnableWindow(FALSE);

	if (!m_Preview)
	{
		m_Preview = new CTE_Preview();
		if(m_Preview)
		{
			m_Preview->Create(IDD_DIALOG_PREVIEW);
			m_Preview->ShowWindow(SW_HIDE);
		}
		
	}
 
	if(!m_incomingCall)
	{
		m_incomingCall = new CTE_IncomingCall();
		if(m_incomingCall)
		{
			m_incomingCall->Create(IDD_COMMINGCALL_DIALOG);
			m_incomingCall->ShowWindow(SW_HIDE);
		}
		
	}
	
	TE_SetDisplayHandle(m_incomingCall->m_LocalWindow.GetSafeHwnd(),m_incomingCall->m_RemoteWindow.GetSafeHwnd(),m_incomingCall->m_displayShareWind.GetSafeHwnd());

	if (!m_Pcontact)
	{
		m_Pcontact = new CTE_Contact(this);
		if(m_Pcontact)
		{
			m_Pcontact->Create(IDD_DIALOG_CONTACT);
			m_Pcontact->ShowWindow(SW_HIDE);
		}
	}

	if (!m_Enterprise)
	{
		m_Enterprise = new CTE_Enterprise(this);
		if(m_Enterprise)
		{
			m_Enterprise->Create(IDD_DIALOG_ENTERPRISE_ADDR);
			m_Enterprise->ShowWindow(SW_HIDE);
		}
	}
	
	if (!m_HistroyRecord)
	{
		m_HistroyRecord = new CTE_HistoryRecord(this);
		if(m_HistroyRecord)
		{
			m_HistroyRecord->Create(IDD_DIALOG_HISTORYRECORD);
			m_HistroyRecord->ShowWindow(SW_HIDE);
		}
	}

	if (!m_pContactDlg)
	{
		m_pContactDlg = new CTE_ConfContacts();
		if(m_pContactDlg)
		{
			m_pContactDlg->Create(IDD_DIALOG_CONFERENCE_CONTACTS);
			m_pContactDlg->ShowWindow(SW_HIDE);
		}
	}
	//m_Pcontact->m_ContactVideo.SetCheck(0);

	CFont * f; 
	f = new CFont; 
	f->CreateFont(16,            // nHeight 
		0,           // nWidth 
		0,           // nEscapement 
		0,           // nOrientation 
		FW_BOLD,     // nWeight 
		FALSE,        // bItalic 
		FALSE,       // bUnderline 
		0,           // cStrikeOut 
		ANSI_CHARSET,              // nCharSet 
		OUT_DEFAULT_PRECIS,        // nOutPrecision 
		CLIP_DEFAULT_PRECIS,       // nClipPrecision 
		DEFAULT_QUALITY,           // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("Arial"));              // lpszFac

	m_confInfo.SetFont(f); 

	m_transMode.InsertString(0,_T("TLS"));
    m_transMode.InsertString(1,_T("UDP"));
    m_transMode.SetCurSel(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
/**************************************************
 * @fn         OnSigninNotify(WPARAM wParm, LPARAM Lparam)
 * @brief      show login or logout state.
 * @param[in]  WPARAM wParm: TE Login State
 * @param[in]  LPARAM Lparam:call state info
 * @attention 
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnSigninNotify(WPARAM wParm, LPARAM Lparam)
{
	int state = (int)wParm;
	
	if (m_isLogin )
	{
		if(TE_E_LGOIN_FAIL_UNREGISTER == state)
		{
			m_isLogin = 0;
			AfxMessageBox(_T("Logout"));
			return 0L;
		}
		if(TE_E_LOGIN_KICKOUT == state)
		{
			m_isLogin = 0;
			TE_SDK_Logout();
			AfxMessageBox(_T("Kick Out"));
			return 0L;
		}
	}
	
	

	if (TE_E_LOGIN_SUCCESS == state && !m_isLogin)
	{
		AfxMessageBox(_T("Login success"));
		m_isLogin = 1;
		TE_S_NETWORK_CONFIG networkConfig;
		networkConfig.media_auto_reply = TE_E_SETTING_MEDIA_AUTO_REPLY_DISABLE;
		networkConfig.media_bandwidth = TE_E_SETTING_MEDIA_BANDWIDTH_2048;
		networkConfig.media_open_slide = TE_E_SETTING_MEDIA_OPEN_SLIDE_ENABLE;
		networkConfig.srtp_mode = TE_E_SETTING_SRTP_MODE_OPTION;
		networkConfig.setFrameRate=false;
		networkConfig.setDataRate=false;
		networkConfig.setFrameSize=false;
		TE_SetNetworkConfig(networkConfig);
		m_cameralist.EnableWindow(TRUE);
		m_audioInList.EnableWindow(TRUE);
		m_audioOutList.EnableWindow(TRUE);
		OnUpdateDeviceList(-1);
		if (m_incomingCall)
		{
			((CSliderCtrl*)m_incomingCall->GetDlgItem(IDC_SLIDER_VOICEIN))->SetPos(TE_GetVolume(TE_E_VOLUME_TYPE_MIC));
			((CSliderCtrl*)m_incomingCall->GetDlgItem(IDC_SLIDER_VOICEOUT))->SetPos(TE_GetVolume(TE_E_VOLUME_TYPE_SPEAK));
		}
		//TE_SetUserConfig();
	}
	else if(TE_E_LOGIN_FAIL_CER_INVALID == state || TE_E_LOGIN_FAIL_AUTH == state)
	{
		AfxMessageBox(_T("Login failure"));
	}
	else if (TE_E_LOGIN_FAIL_TIMEOUT == state)
	{
		AfxMessageBox(_T("Login Fail Timeout"));
	}
	else if (TE_E_LOGIN_FAIL_LICENSE_TYPE_FAILED == state)
	{
		AfxMessageBox(_T("Get license type failed"));
	}
	else if (TE_E_LOGIN_FAIL_LICENSE_TYPE_INVALID == state)
	{
		AfxMessageBox(_T("license type invalid"));
	}
	else if (TE_E_LOGIN_FAIL_LICENSE_APPLY_FAILED == state)
	{
		AfxMessageBox(_T("apply license failed"));
	}
	else if (TE_E_LOGIN_FAIL_LICENSE_REFRESH_FAILED == state)
	{
		AfxMessageBox(_T("refresh license failed"));
	}
	return 0L;
}
/**************************************************
 * @fn         OnAVSessClosed(WPARAM wParm, LPARAM Lparam)
 * @brief      show state which call end.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: call state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnAVSessClosed(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	
	if (m_incomingCall != NULL)
	{
		//m_incomingCall->MessageBox(_T("Call End"));
		m_incomingCall->KillTimer(TIME_ID);
		m_incomingCall->m_lDuration = 0;
		m_incomingCall->m_CallState.Format(_T("Call End"));
		memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
		::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	
		//m_incomingCall->PostMessage(WM_CLOSE);
	}
	

	if (m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd())) 
	{
		(void)m_pDeskRimDlg->DestroyWindow();
	}

	if (m_pDeskRimDlg)
	{
		delete m_pDeskRimDlg;
		m_pDeskRimDlg=NULL;
	}

	if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
	{
		(void)m_pOutSideDlg->DestroyWindow();
	}
	if (m_pOutSideDlg)
	{
		delete m_pOutSideDlg;
		m_pOutSideDlg=NULL;

	}


	if (param)
	{
		delete param;
		param = NULL;
	}

	return 0L;

}
/**************************************************
 * @fn         OnAVSessAdded(WPARAM wParm, LPARAM Lparam)
 * @brief      show state which is calling.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: call state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnAVSessAdded(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	CString msg;

	if (NULL == param)
	{
		AfxMessageBox(_T("Error: Lparam is Null Pointer"));
		return 0L;
	}
	
	if(!m_incomingCall)
	{
		m_incomingCall = new CTE_IncomingCall();
		m_incomingCall->Create(IDD_COMMINGCALL_DIALOG);
	}
	m_incomingCall->m_bIsHangup = false;
	m_incomingCall->m_CallState.Format(_T("Calling..."));
	
	
	memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
	strncpy(m_incomingCall->callername,param->acDisplayName,TE_D_NAME_LEN);
	m_incomingCall->rectLarge = CRect(561,286,1515,1006);
	m_incomingCall->rectSmall = CRect(561,286,1515,423);

	CRect picRect;  

	m_incomingCall->m_bound.GetWindowRect(&picRect); 
	m_incomingCall->rectSmall.bottom=415;  
	if (m_incomingCall->m_CallStateInfo.enCallType == TE_E_CALL_TYPE_IPVIDEO)
	{
		m_incomingCall->m_isVideo = TRUE;
		m_incomingCall->m_btnShare.EnableWindow(TRUE);
		m_incomingCall->m_btnStopShare.EnableWindow(TRUE);
		m_incomingCall->exeShareBtn.EnableWindow(TRUE);
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectLarge.Width(),m_incomingCall->rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectSmall.Width(),m_incomingCall->rectSmall.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}

	m_incomingCall->ShowWindow(SW_SHOWNORMAL);
	m_incomingCall->SetForegroundWindow();

	
	msg.Format("%s",param->acDisplayName);
	m_incomingCall->SetWindowText(msg);
	::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	
	
	delete param;

	return 0L;
}
/**************************************************
 * @fn         OnAVSessConnected(WPARAM wParm, LPARAM Lparam)
 * @brief      show state which is the conversation.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: call state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT  CTE_DemoDlg::OnAVSessConnected(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	if (NULL == m_incomingCall)
	{
		return 0L;
	}

	m_incomingCall->SetTimer(TIME_ID,SECOND,NULL);
	m_incomingCall->m_CallState.Format(_T("Conversation"));
	memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
	//TE_SetDisplayHandle(param->ulCallID,m_incomingCall->m_LocalWindow.GetSafeHwnd(), m_incomingCall->m_RemoteWindow.GetSafeHwnd());
	::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	
	
	if (param)
	{
		delete param;
		param = NULL;
	}
	return 0L;
}
/**************************************************
 * @fn         OnAVSessCallRing(WPARAM wParm, LPARAM Lparam)
 * @brief      show state which is calling.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: call state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/

LRESULT  CTE_DemoDlg::OnAVSessCallRing(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	if (NULL == m_incomingCall)
	{
		return 0L;
	}

	m_incomingCall->m_CallState.Format(_T("Calling..."));
	memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
	::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	
	
	if (param)
	{
		delete param;
		param = NULL;
	}

	return 0L;
}


LRESULT  CTE_DemoDlg::OnOpenVedio(WPARAM wParm, LPARAM Lparam)
{
	if (m_incomingCall)
	{
		if (!m_handCallDlg || (::IsWindow(m_handCallDlg->GetSafeHwnd())==FALSE))
		{
			m_handCallDlg = new CTE_HandleCallDlg();
			m_handCallDlg->Create(IDD_DIALOG_ANSWER_REJECT);
		}

		m_handCallDlg->m_callIncome=m_incomingCall;
		memcpy(&m_handCallDlg->m_callInfo, &m_incomingCall->m_CallStateInfo, sizeof(TE_S_CALL_STATE_INFO));


		// 获得桌面大小  
		CRect rectWorkArea;  
		SystemParametersInfo(SPI_GETWORKAREA,0,&rectWorkArea,SPIF_SENDCHANGE);     

		// 获得对话框大小  
		CRect rectDlg;  
		m_handCallDlg->GetWindowRect(&rectDlg);  
		int nW = rectDlg.Width();  
		int nH = rectDlg.Height();  

		// 将窗口设置到右下角  
		::SetWindowPos(m_handCallDlg->GetSafeHwnd(),HWND_TOPMOST,rectWorkArea.right-nW-20,rectWorkArea.bottom-nH,nW,nH,SWP_NOZORDER);  


		m_handCallDlg->ShowWindow(SW_SHOWNORMAL);
		m_handCallDlg->SetForegroundWindow();
	}



	return 0L;
}


LRESULT  CTE_DemoDlg::OnCloseVedio(WPARAM wParm, LPARAM Lparam)
{
	if (m_incomingCall)
	{
		m_incomingCall->m_btnVtoa.EnableWindow(FALSE);
		m_incomingCall->m_btnVtoa.ShowWindow(SW_HIDE);

		m_incomingCall->m_btnAtov.EnableWindow(TRUE);
		m_incomingCall->m_btnAtov.ShowWindow(SW_SHOW);

		m_incomingCall->m_isCheckVedio=FALSE;
		m_incomingCall->m_isCheckAudio=TRUE;
		m_incomingCall->m_isVideo = FALSE;
		m_incomingCall->m_btnShare.EnableWindow(FALSE);
		m_incomingCall->m_btnStopShare.EnableWindow(FALSE);
		m_incomingCall->exeShareBtn.EnableWindow(FALSE);
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectSmall.Width(),m_incomingCall->rectSmall.Height(),SWP_NOMOVE | SWP_NOZORDER);

	}

	return 0L;
}


LRESULT  CTE_DemoDlg::OnAnswerVedio(WPARAM wParm, LPARAM Lparam)
{
	if (m_incomingCall)
	{

		m_incomingCall->m_LocalWindow.ShowWindow(SW_SHOW);
		m_incomingCall->m_RemoteWindow.ShowWindow(SW_SHOW);
		m_incomingCall->m_btnVideo.EnableWindow(TRUE);
		m_incomingCall->m_btnAnswer.EnableWindow(FALSE);
		m_incomingCall->m_vedioAnswer.EnableWindow(FALSE);
		m_incomingCall->m_btnReject.EnableWindow(FALSE);
		m_incomingCall->m_bSpeaker.EnableWindow(TRUE);
		m_incomingCall->m_bMIC.EnableWindow(TRUE);
		m_incomingCall->m_btnHangup.EnableWindow(TRUE);


		TE_S_SITE_INFO localHall;
		memset(&localHall, 0, sizeof(TE_S_SITE_INFO));

		TE_GetLocalSite(&localHall);

		if (localHall.isJoined_ && localHall.T_!=0)
		{


			m_incomingCall->m_btnVtoa.EnableWindow(FALSE);
			m_incomingCall->m_btnVtoa.ShowWindow(SW_HIDE);
			m_incomingCall->m_btnVtoa.RedrawWindow(0,NULL,RDW_ALLCHILDREN|RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
			m_incomingCall->m_btnAtov.EnableWindow(FALSE);
			m_incomingCall->m_btnAtov.ShowWindow(SW_HIDE);
			m_incomingCall->m_btnAtov.RedrawWindow(0,NULL,RDW_ALLCHILDREN|RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
			m_incomingCall->m_btnConfCtrl.ShowWindow(SW_SHOW);
			m_incomingCall->m_btnConfCtrl.EnableWindow(TRUE);

		}
		else
		{
			m_incomingCall->m_btnVtoa.EnableWindow(TRUE);
			m_incomingCall->m_btnVtoa.ShowWindow(SW_SHOW);

			m_incomingCall->m_btnAtov.EnableWindow(FALSE);
			m_incomingCall->m_btnAtov.ShowWindow(SW_HIDE);
		}

		m_incomingCall->m_isCheckVedio=TRUE;
		m_incomingCall->m_isCheckAudio=FALSE;
		m_incomingCall->m_isVideo = TRUE;
		m_incomingCall->m_btnShare.EnableWindow(TRUE);
		m_incomingCall->m_btnStopShare.EnableWindow(TRUE);
		m_incomingCall->exeShareBtn.EnableWindow(TRUE);
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectLarge.Width(),m_incomingCall->rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);

	}

	return 0L;
}

LRESULT CTE_DemoDlg::OnContactStaus(WPARAM wParm,LPARAM  Lparam)
{
	return 0L;
}

LRESULT CTE_DemoDlg::OnLdapContactsList(WPARAM wParm, LPARAM Lparam)
{
	TE_S_ENTERPRISE_RESULT* wParam = (TE_S_ENTERPRISE_RESULT *)Lparam;
	if(!wParam)
	{
		return -1;
	}
	OnShowEnterpriseResult(&wParam->enterpriseContacts);
	return 0L;
}

LRESULT CTE_DemoDlg::OnMessageNetBookType(WPARAM wParm, LPARAM Lparam)
{
	return 0L;
}


/**************************************************
 * @fn         OnBFCPModifiedResult(WPARAM wParm, LPARAM Lparam)
 * @brief      deal with bfcp result.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: bfcp result info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnBFCPModifiedResult(WPARAM /*wParam*/, LPARAM lParam)
{
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)lParam;
	
	TE_BFCPModifiedResult(param->ulCallID,param->sessionType);


	if (param)
	{
		delete param;
		param = NULL;
	}


	return 0L;//lint !e438
}

/**************************************************
 * @fn         OnDataStartSending(WPARAM wParm, LPARAM Lparam)
 * @brief      data is sending.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: data state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnDataStartSending(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	(void)ShowWindow(SW_MINIMIZE);

	if (NULL != m_incomingCall)
	{

		memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
		::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	

		m_incomingCall->ShowWindow(SW_MINIMIZE);
	}

	if(!m_incomingCall->isEXEshare)
	{
		if(NULL == m_pDeskRimDlg)
		{
			m_pDeskRimDlg = new CDeskRimDlg(this);
		}
		if(m_pDeskRimDlg && !IsWindow(m_pDeskRimDlg->GetSafeHwnd()))
		{
			(void)m_pDeskRimDlg->Create(CDeskRimDlg::IDD,CWnd::GetDesktopWindow());
		}

	}
	else
	{
		if(::IsIconic(m_incomingCall->m_dataShareWind))
		{
			::ShowWindow(m_incomingCall->m_dataShareWind, SW_RESTORE);
			::ShowWindow(m_incomingCall->m_dataShareWind, SW_SHOWNORMAL);
		}
		(void)::SetForegroundWindow(m_incomingCall->m_dataShareWind);
		(void)::SetFocus(m_incomingCall->m_dataShareWind);

		RECT winSize;
		::GetWindowRect(m_incomingCall->m_dataShareWind,&winSize);
		::MoveWindow(m_incomingCall->m_dataShareWind,winSize.left-55,winSize.top-55,winSize.right-winSize.left,winSize.bottom-winSize.top,TRUE);
		//::UpdateWindow(m_incomingCall->m_dataShareWind);
		//(void)::SetWindowPos(m_incomingCall->m_dataShareWind, NULL, winSize->left, 0, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE|SWP_NOZORDER);
		//StartDrawRimDlg();

	}

	if(NULL == m_pCaptureWndTimer)
	{
		m_pCaptureWndTimer = SetTimer(IM_CAPTURE_CHANGE_TIMER, IM_CAPTURE_CHANGE_TIME, NULL);
	}

	isDataSending=true;

	if (param)
	{
		delete param;
		param = NULL;
	}


	return 0L;
}

/**************************************************
 * @fn         OnDataStartFail(WPARAM wParm, LPARAM Lparam)
 * @brief      data send failed.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: data state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnDataStartFail(WPARAM wParm, LPARAM Lparam)
{

	if (m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd())) 
	{
		(void)m_pDeskRimDlg->DestroyWindow();
	}

	if (m_pDeskRimDlg)
	{
		delete m_pDeskRimDlg;
		m_pDeskRimDlg=NULL;
	}

	if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
	{
		(void)m_pOutSideDlg->DestroyWindow();
	}
	if (m_pOutSideDlg)
	{
		delete m_pOutSideDlg;
		m_pOutSideDlg=NULL;

	}

	AfxMessageBox(_T("Share send data failed!"));
	return 0L;
}

void CTE_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

/**************************************************
 * @fn         OnDataStartRecving(WPARAM wParm, LPARAM Lparam)
 * @brief      data recieve.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: data state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnDataStartRecving(WPARAM wParm, LPARAM Lparam)
{
	
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	if (NULL == m_incomingCall)
	{
		return 0L;
	}

	memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
	//TE_SetDisplayShareHandle(param->ulCallID,m_incomingCall->m_displayShareWind.GetSafeHwnd());
	::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	

	if (param)
	{
		delete param;
		param = NULL;
	}

	return 0L;
}

/**************************************************
 * @fn         OnDataStoped(WPARAM wParm, LPARAM Lparam)
 * @brief      data stoped.
 * @param[in]  WPARAM wParm:  not used
 * @param[in]  LPARAM Lparam: data state info
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
LRESULT CTE_DemoDlg::OnDataStoped(WPARAM wParm, LPARAM Lparam)
{
	
	TE_S_CALL_STATE_INFO *param = (TE_S_CALL_STATE_INFO *)Lparam;
	/*if (NULL == m_incomingCall)
	{
		return 0L;
	}

	memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
	::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	*/
	if (m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd())) 
	{
		(void)m_pDeskRimDlg->DestroyWindow();
	}

	if (m_pDeskRimDlg)
	{
		delete m_pDeskRimDlg;
		m_pDeskRimDlg=NULL;
	}

	if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
	{
		(void)m_pOutSideDlg->DestroyWindow();
	}
	if (m_pOutSideDlg)
	{
		delete m_pOutSideDlg;
		m_pOutSideDlg=NULL;
	}

	if (isDataSending)
	{
		isDataSending=false;
		if(m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd()))
		{
			(void)m_pDeskRimDlg->ShowWindow(SW_HIDE);
		}
		if(m_pCaptureWndTimer)
		{
			(void)KillTimer(IM_CAPTURE_CHANGE_TIMER);
			m_pCaptureWndTimer = NULL;
		}
	}


	if (NULL == m_incomingCall)
	{
		if (param)
		{
			delete param;
			param = NULL;
		}
		return 0L;
	}

	memcpy(&m_incomingCall->m_CallStateInfo, param, sizeof(TE_S_CALL_STATE_INFO));
	::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	


	if (param)
	{
		delete param;
		param = NULL;
	}

	return 0L;
}


LRESULT CTE_DemoDlg::OnConfCreateStateChange(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (TE_SDK_Success == result->uResult.createConfInfo._result)
	{
		m_confInfo.SetWindowText(_T(""));

		SetTimer(NULL,2000,NULL); 

		CString cstr;
		cstr.Format("创建会议成功"); 
		MessageBox(_T(LPCSTR(cstr)),_T("CreateConfSuccess"),MB_OK); 

		//if (NULL == m_pConfCreateResultDlg)
		//{
		//	m_pConfCreateResultDlg = new ConfCreateResultDlg(CWnd::FromHandle(mainFrame_->getSafeFrameWnd()), (CWnd*)this);
		//	m_pConfCreateResultDlg->SetUIMainFrame(mainFrame_);
		//	m_pConfCreateResultDlg->Create(ConfCreateResultDlg::IDD, CWnd::FromHandle(mainFrame_->getSafeFrameWnd()) );
		//}
		//m_pConfCreateResultDlg->ShowWindow(SW_NORMAL);
		////2s后自动关闭窗口
		//::SetTimer(this->GetSafeHwnd(), ID_CLOSE_SUCCESS_DLG_TIMER, 2000, NULL);
	}
	else
	{	
		
		/*CString strTmp;
		cstrName = m_parent->Utf82Unicode(m_getContact.contact[i].name);
		strTmp.Format("%s", m_parent->WSToString(cstrName).c_str());*/

		CString cstr;
		std::wstring cstrName;
		cstrName = Utf82Unicode(result->uResult.createConfInfo._reason);
		cstr.Format("创建会议失败%s", WSToString(cstrName).c_str()); 

		m_confInfo.SetWindowText(_T(LPCSTR(cstr)));
	}

	return 0L;
}


LRESULT CTE_DemoDlg::OnConfApplyChairman(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}
	if (NULL == m_incomingCall->m_confCtrl->m_applyChairmanDlg)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	m_incomingCall->m_confCtrl->m_applyChairmanDlg->result=result->uResult.result;
	::PostMessage(m_incomingCall->m_confCtrl->m_applyChairmanDlg->GetSafeHwnd(), WM_CONF_APPLY_CHAIRMAN_RESULT, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}


	return 0L;
}


LRESULT CTE_DemoDlg::OnConfBroadcastRest(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	m_incomingCall->m_confCtrl->broadcastRest=result->uResult.result;
	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_BROADCAST_REST, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}


	return 0L;
}


LRESULT CTE_DemoDlg::OnConfWatchRest(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	m_incomingCall->m_confCtrl->watchRest=result->uResult.result;
	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_WATCH_REST, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}


	return 0L;
}



LRESULT CTE_DemoDlg::OnConfReleaseChairman(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}
	

	m_incomingCall->m_confCtrl->result=(bool)result->uResult.result;
	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_RELEASE_CHAIRMAN_RESULT, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}


	return 0L;
}


LRESULT CTE_DemoDlg::OnConfAttendeeListRefresh(WPARAM wParm, LPARAM Lparam)
{
	if (NULL == m_incomingCall)
	{
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		return 0L;
	}

	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_FRESH_MEMLIST, NULL, NULL);	


	return 0L;
}


LRESULT CTE_DemoDlg::OnConfChairManInd(WPARAM wParm, LPARAM Lparam)
{
	if (NULL == m_incomingCall)
	{
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		return 0L;
	}

	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_FRESH_MEMLIST, NULL, NULL);	


	return 0L;
}


LRESULT CTE_DemoDlg::OnConfAddHallRst(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}


	if (NULL == m_incomingCall->m_confCtrl->m_inviteDlg)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}



	memcpy(&m_incomingCall->m_confCtrl->m_inviteDlg->m_addHallRest, &result->uResult.addHallRest, sizeof(TE_S_ADDSITETOCONF_RESULT));
	::PostMessage(m_incomingCall->m_confCtrl->m_inviteDlg->GetSafeHwnd(), WM_CONF_ADD_HALL_RESULT, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}

	return 0L;
}


LRESULT CTE_DemoDlg::OnConfExtendTimeRst(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}


	m_incomingCall->m_confCtrl->extendRest=(bool)result->uResult.result;
	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_EXTEND_TIME_REST, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}


	return 0L;
}


LRESULT CTE_DemoDlg::OnConfTimeRemnant(WPARAM wParm, LPARAM Lparam)
{
	TE_S_CONF_RESULT* result = (TE_S_CONF_RESULT*)Lparam;

	if (NULL == m_incomingCall)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	if (NULL == m_incomingCall->m_confCtrl)
	{
		if (result)
		{
			delete result;
			result = NULL;
		}
		return 0L;
	}

	m_incomingCall->m_confCtrl->remainTime=result->uResult.result;
	::PostMessage(m_incomingCall->m_confCtrl->GetSafeHwnd(), WM_CONF_EXTEND_REMAIN_TIME, NULL, NULL);	


	if (result)
	{
		delete result;
		result = NULL;
	}


	return 0L;
}



// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTE_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


/**************************************************
 * @fn         OnTimer(UINT_PTR nIDEvent)
 * @brief      set calling time.
 * @return     NA 
 * @attention  NA
****************************************************/
void CTE_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nIDEvent)
	{
	case IM_CAPTURE_CHANGE_TIMER:
		{
			CaptureChangeTime_T();
		}
		break;
	case IM_CAPTURE_CHANGE_DRAW_TIMER:
		{
			UpdateRimDlgs();
			//m_pOutSideDlg->ShowWnd();
		}
		break;
	default:
		break;
	}


	HWND hWnd=::FindWindow(NULL,_T("CreateConfSuccess"));   //查找标题为B的窗口，返回窗口句柄
	if (hWnd)   //如果窗口句柄存在
	{
		::SendMessage(hWnd,WM_SYSCOMMAND,SC_CLOSE,NULL);   //关闭这个窗口,如果Messagebox的对话框没有MB_YESNO或者MB_OKCANCEL这样类似的属性，这个也可以实现关闭
		//keybd_event(13,0,0,0); //模拟回车键按下
		KillTimer(nIDEvent);
	}
	

	CDialog::OnTimer(nIDEvent);
}

void CTE_DemoDlg::UpdateRimDlgs()
{

	if (m_incomingCall->m_bIsHangup==true)
	{
		if (m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd())) 
		{
			(void)m_pDeskRimDlg->DestroyWindow();
		}

		if (m_pDeskRimDlg)
		{
			delete m_pDeskRimDlg;
			m_pDeskRimDlg=NULL;
		}

		if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
		{
			(void)m_pOutSideDlg->DestroyWindow();
		}
		if (m_pOutSideDlg)
		{
			delete m_pOutSideDlg;
			m_pOutSideDlg=NULL;
		}

	    (void)KillTimer(IM_CAPTURE_CHANGE_DRAW_TIMER);
	     return;
	}

	if(!::IsWindow(mainWnd) || !::IsWindowVisible(mainWnd))
	{
		if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
		{
			(void)m_pOutSideDlg->DestroyWindow();
		}
		if (m_pOutSideDlg) 
		{
			delete m_pOutSideDlg;
			m_pOutSideDlg=NULL;
		}

		mainWnd = GetCurShareMainWnd(m_dwPID);
		if(NULL != mainWnd)
		{
			CWnd* pWnd=FromHandle(mainWnd);

			m_pOutSideDlg = new COutSideWindow(this, mainWnd);
			(void)m_pOutSideDlg->Create(COutSideWindow::IDD, pWnd);
			(void)m_pOutSideDlg->ShowWindow(SW_SHOW);
			::UpdateWindow(m_pOutSideDlg->GetSafeHwnd());
		}
		else
		{
			(void)KillTimer(IM_CAPTURE_CHANGE_DRAW_TIMER);
		}
	}
	else
	{
		if(m_pOutSideDlg)
		{
			m_pOutSideDlg->ShowWnd();
			::UpdateWindow(m_pOutSideDlg->GetSafeHwnd());

		}
	}
}


/*******************************************************************************
* 函数名称 : StartDrawRimDlg
* 函数描述 : 开始绘制辅流发送区域框
* 输入参数 : N/A
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
void CTE_DemoDlg::StartDrawRimDlg()
{
	(void)GetWindowThreadProcessId(m_incomingCall->m_dataShareWind, &m_dwPID);
	mainWnd = GetCurShareMainWnd(m_dwPID);

	CWnd* pWnd=FromHandle(mainWnd);
	if(!m_pOutSideDlg)
	{
		m_pOutSideDlg = new COutSideWindow(this, mainWnd);
	}
	if(!::IsWindow(m_pOutSideDlg->GetSafeHwnd()))
	{
		(void)m_pOutSideDlg->Create(COutSideWindow::IDD, pWnd);
	}
	(void)m_pOutSideDlg->ShowWindow(SW_SHOW);

	//UpdateWindow();
	::UpdateWindow(m_pOutSideDlg->GetSafeHwnd());
	(void)SetTimer(IM_CAPTURE_CHANGE_DRAW_TIMER, IM_CAPTURE_CHANGE_DRAW_TIME,NULL);
}

/*******************************************************************************
* 函数名称 : GetCurShareMainWnd
* 函数描述 : 获取共享应用主界面句柄
* 输入参数 : DWORD pid 进程pid
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
HWND CTE_DemoDlg::GetCurShareMainWnd(DWORD pid)
{
	DWORD dwPID;
	(void)GetWindowThreadProcessId(m_incomingCall->m_dataShareWind, &dwPID);  //接受一个窗口句柄。dwPID保存窗口的创建者的进程标识符，GetWindowThreadProcessId返回值是该创建者的线程标识符
	CMainWindowIterator itw(dwPID);
	for (HWND hwnd = itw.First(); hwnd; hwnd=itw.Next())
	{
		if (::IsWindow(hwnd) && ::IsWindowVisible(hwnd)
			&& (::GetWindowLong(hwnd, GWL_EXSTYLE)&WS_EX_TOOLWINDOW)!=WS_EX_TOOLWINDOW
			&& ::GetWindowLong(hwnd, GWL_HWNDPARENT)==0 && ::GetParent(hwnd) == NULL)
		{
			return hwnd;
		}
	}
	return NULL;
}


//共享辅流检测定时器
void CTE_DemoDlg::CaptureChangeTime_T()
{

	if (m_incomingCall->m_bIsHangup==true)
	{
		if (m_pDeskRimDlg && ::IsWindow(m_pDeskRimDlg->GetSafeHwnd())) 
		{
			(void)m_pDeskRimDlg->DestroyWindow();
		}

		if (m_pDeskRimDlg)
		{
			delete m_pDeskRimDlg;
			m_pDeskRimDlg=NULL;
		}

		if (m_pOutSideDlg && ::IsWindow(m_pOutSideDlg->GetSafeHwnd())) 
		{
			(void)m_pOutSideDlg->DestroyWindow();
		}
		if (m_pOutSideDlg)
		{
			delete m_pOutSideDlg;
			m_pOutSideDlg=NULL;
		}

		if(m_pCaptureWndTimer)
		{
			(void)KillTimer(IM_CAPTURE_CHANGE_TIMER);
			m_pCaptureWndTimer = NULL;
		}
		return;
	}

	if(m_pDeskRimDlg)
	{
		(void)::SetWindowPos(m_pDeskRimDlg->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}

	return;
}



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTE_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**************************************************
 * @fn         OnBnClickedLogin()
 * @brief      Login TE Button Event 
 * @return     NULL
 * @param[in]  NA
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
void CTE_DemoDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	int len = 0,ret=0,nportNum;
	TE_S_LOGIN_INFO LoginReqInfo;
	BYTE field0, field1, field2, field3; 
	CString cstrLicenseServerIP;
	memset(&LoginReqInfo, 0, sizeof(TE_S_LOGIN_INFO));
	if (m_isLogin)
	{
		AfxMessageBox(_T("Already Login in."));
		return;
	}
	UpdateData(TRUE);
	m_ipCtrlServerIP.GetAddress(field0,field1,field2,field3);
	m_CStrServerIP.Format(_T("%d.%d.%d.%d"),field0,field1,field2,field3);
	m_licenseServerIP.GetAddress(field0,field1,field2,field3);
	if(field0||field1||field2||field3)
	{
		cstrLicenseServerIP.Format(_T("%d.%d.%d.%d"),field0,field1,field2,field3);
	}
	len = m_CStrUsername.GetLength();
	if(len>=50)
	{
		AfxMessageBox("the name too long,please reenter");
		return;
	}
	strncpy(LoginReqInfo.cUserName ,m_CStrUsername.GetBuffer(len),len);
	len = m_CStrPassword.GetLength();
	if(len>30)
	{
		AfxMessageBox("the password is too long");
	}
	strncpy(LoginReqInfo.cPWD ,m_CStrPassword.GetBuffer(len),len);
	len = m_CStrPortNum.GetLength();
	nportNum = atoi(m_CStrPortNum.GetBuffer(len));
	if(len>5 || ((nportNum<0) ||(nportNum>65535)))
	{
		AfxMessageBox("input illegal,please reenter");
		return;
	}
	LoginReqInfo.uiPort = nportNum;
	len = m_CStrServerIP.GetLength();
	strncpy(LoginReqInfo.stIP,m_CStrServerIP.GetBuffer(len),len);
	len = cstrLicenseServerIP.GetLength();
	if(len)
	{
		strncpy(LoginReqInfo.licenseServer, cstrLicenseServerIP.GetBuffer(len),len);

	}
	if (m_transMode.GetCurSel()==0)
	{
		strncpy(LoginReqInfo.cTransMode,"TLS",3);
	} 
	else
	{
		strncpy(LoginReqInfo.cTransMode,"UDP",3);
	}

	if((m_CStrUsername == "")||(m_CStrServerIP == "")||(m_CStrPortNum == "")||(m_CStrPassword == ""))
	{
		AfxMessageBox((_T("the control is empty,please input ")));
		return;
	}
	
	ret = TE_SDK_Login(&LoginReqInfo);
	
	

	if (TE_SDK_Success == ret)
	{
		//CDialog::OnOK();
	}
	else
	{
		CString msg;
		msg.Format("Login Failure: %d", ret);
		SetWindowText(msg);
	}
	return;
}
/**************************************************
 * @fn         OnBnClickedCallButton()
 * @brief	   Call somebody Button Event.
 * @return     NA
 * @param[in]  NA
 * @attention  NA
 * @par 示例
 * @code
 * @endcode
****************************************************/
void CTE_DemoDlg::OnBnClickedCallButton()
{
	// TODO: 在此添加控件通知处理程序代码

	int len = 0;
	char cCallNum[512]={0};
	CString msg;
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}

	UpdateData(TRUE);
	len = m_CStrCallNum.GetLength();
	strncpy(cCallNum, m_CStrCallNum.GetBuffer(len), 511);
	if(m_btnVideo.GetCheck())
	{
		
		
		TE_MakeCall(cCallNum, TE_E_CALL_TYPE_IPVIDEO);
	}
	else
	{
		TE_MakeCall(cCallNum, TE_E_CALL_TYPE_IPAUDIO);
	}
	

	if(!m_incomingCall)
	{
		m_incomingCall = new CTE_IncomingCall();
		m_incomingCall->Create(IDD_COMMINGCALL_DIALOG);//create non-modal dialog.
	}

	if(!m_incomingCall)
	{
		return;
	}

	//::GetWindowRect(m_incomingCall->GetSafeHwnd(),&m_incomingCall->rectLarge);  
	m_incomingCall->rectLarge = CRect(561,286,1515,1006);
	m_incomingCall->rectSmall = CRect(561,286,1515,423);

	CRect picRect;  

	m_incomingCall->m_bound.GetWindowRect(&picRect); 
	/*m_incomingCall->rectSmall.left=m_incomingCall->rectLarge.left;  
	m_incomingCall->rectSmall.top=m_incomingCall->rectLarge.top;  
	m_incomingCall->rectSmall.right=m_incomingCall->rectLarge.right;  */
	m_incomingCall->rectSmall.bottom=415; 

	if(m_btnVideo.GetCheck())
	{
		m_incomingCall->m_isVideo = TRUE;
		m_incomingCall->m_btnShare.EnableWindow(TRUE);
		m_incomingCall->m_btnStopShare.EnableWindow(TRUE);
		m_incomingCall->exeShareBtn.EnableWindow(TRUE);
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectLarge.Width(),m_incomingCall->rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		m_incomingCall->m_btnShare.EnableWindow(FALSE);		
		m_incomingCall->m_btnStopShare.EnableWindow(FALSE);
		m_incomingCall->exeShareBtn.EnableWindow(FALSE); 
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectSmall.Width(),m_incomingCall->rectSmall.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}

	m_incomingCall->m_bIsHangup = false;
	m_incomingCall->ShowWindow(SW_SHOWNORMAL);
	m_incomingCall->SetForegroundWindow();//create thread of specified window to foreground and activate this window.
	strncpy(m_incomingCall->callername,cCallNum,TE_D_NAME_LEN);
	msg.Format("%s",cCallNum);
	m_incomingCall->SetWindowText(msg);

	::SetWindowLongA(m_incomingCall->m_LocalWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowLongA(m_incomingCall->m_RemoteWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);	

}


/**************************************************
 * @fn         OnClose()
 * @brief      Close Window Event
 * @return     NA
 * @param[in]  NA
 * @attention  
 * @par 示例
 * @code
 * @endcode
****************************************************/
void CTE_DemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bClose = true;

	//TE_SDK_Logout();
	if(m_isLogin)
	{
		TE_SDK_Logout();
	}
	TE_SDK_Release();
	if(NULL != m_incomingCall)
	{
		if(::IsWindow(m_incomingCall->GetSafeHwnd()))
		{
			delete m_incomingCall;
			m_incomingCall = NULL;
		}
	}
	if(NULL != m_Preview)
	{
		if(::IsWindow(m_Preview->GetSafeHwnd()))
		{
			delete m_Preview;
			m_Preview = NULL;
		}
	}
	
	if(NULL != m_Pcontact)
	{
		if(::IsWindow(m_Pcontact->GetSafeHwnd()))
		{
			delete m_Pcontact;
			m_Pcontact = NULL;
		}
	}

	if(NULL != m_Enterprise)
	{
		if(::IsWindow(m_Enterprise->GetSafeHwnd()))
		{
			delete m_Enterprise;
			m_Enterprise = NULL;
		}
	}

	if(NULL != m_HistroyRecord)
	{
		if(::IsWindow(m_HistroyRecord->GetSafeHwnd()))
		{
			delete m_HistroyRecord;
			m_HistroyRecord = NULL;
		}
	}

	CDialog::OnClose();
}

void CTE_DemoDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTE_DemoDlg::OnBnClickedLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(m_isLogin)
	{
		TE_SDK_Logout();
		m_cameralist.ResetContent();
		m_cameralist.EnableWindow(FALSE);

		m_audioInList.ResetContent();
		m_audioInList.EnableWindow(FALSE);

		m_audioOutList.ResetContent();
		m_audioOutList.EnableWindow(FALSE);
		
	}
	
	//OnCancel();
}

void CTE_DemoDlg::OnBnClickedButtonVideopreview()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CTE_Preview addressbook(this);
	INT_PTR response = addressbook.DoModal();*/
	int ret = 0;
	int choice = 0;
	TE_S_CAMERA_INFO m_camerainfolist[20];
	TE_UINT32 cameraNum ;

	if (!m_Preview)
	{
		m_Preview = new CTE_Preview();
		if(m_Preview)
		{
			m_Preview->Create(IDD_DIALOG_PREVIEW);
		}
		
	}

	
	ret = TE_GetCamerasInfo(&cameraNum, m_camerainfolist);
	if(m_isLogin)
	{
		if(TE_SDK_Success == ret)
		{
			if(0 == cameraNum)
			{
				AfxMessageBox("Not camera,Please first install camera");
				return;
			}
			choice = m_cameralist.GetCurSel();
			m_cameralist.SetCurSel(choice);
			OnUpdateDeviceList(choice);
			if(choice<0)
			{
				AfxMessageBox(_T("please first choice one device"));
				return;
			}
			ret = TE_OpenPreview(m_Preview->m_preview.GetSafeHwnd(),choice);
			if(TE_SDK_Success == ret)
			{
				//AfxMessageBox(_T("success"));
				if(m_Preview)
				{
					m_Preview->ShowWindow(SW_SHOWNORMAL);
				}
			}
			else
			{
				AfxMessageBox(_T("The device is busy now,Please hungup the call, try again."));
				//AfxMessageBox(_T("error"));
			}
			
			
		}
	}
	else
	{
		AfxMessageBox(_T("Please first Login"));
	}
	

	/*delete m_Preview;
	m_Preview = NULL;*/
}

std::string CTE_DemoDlg::Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<char> resultstring(utf8size);

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);

	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}

	return std::string(&resultstring[0]);
}

std::wstring CTE_DemoDlg::Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<wchar_t> resultstring(widesize);

	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}

std::string CTE_DemoDlg::WSToString(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring CTE_DemoDlg::ctow(const char* src){
	wchar_t* dest = new wchar_t[50];
	memset(dest,0,sizeof(wchar_t)*50);
	int i = mbstowcs(dest, src, 50);
	return dest;
}


std::wstring CTE_DemoDlg::CstringToWstring(CString m_ContactName)
{
	CStringW ContactName;
	std::wstring cstrName;
	ContactName = m_ContactName;
	cstrName = ContactName;
	return cstrName;
}


void CTE_DemoDlg::OnUpdateDeviceList(int choice)
{
	int ret = 0;
	int i = 0;
	TE_S_CAMERA_INFO m_camerainfolist[20];
	TE_S_AUDIOIN_INFO m_audioInInfoList[20];
	TE_S_AUDIOOUT_INFO m_audioOutInfoList[20];
	TE_UINT32 cameraNum = 0,audioInNum = 0,audioOutNum= 0;
	memset(&m_camerainfolist,0,sizeof(TE_S_CAMERA_INFO));
	memset(&m_audioInInfoList,0,sizeof(TE_S_AUDIOIN_INFO));
	memset(&m_audioOutInfoList,0,sizeof(TE_S_AUDIOOUT_INFO));
	m_cameralist.ResetContent();
	m_audioInList.ResetContent();
	m_audioOutList.ResetContent();
	if(m_isLogin)
	{
		ret = TE_GetCamerasInfo(&cameraNum, m_camerainfolist);
		if(cameraNum>0)
		{
			for(i=0;i<cameraNum;i++)
			{
				m_cameralist.InsertString(i,m_camerainfolist[i].cName);
				if(choice == i)
				{
					m_Preview->SetWindowText(m_camerainfolist[i].cName);
					m_cameralist.SetWindowTextA(m_camerainfolist[i].cName);
				}
			}
		}


		ret = TE_GetAudioInInfo(&audioInNum, m_audioInInfoList);
		if(audioInNum>0)
		{
			for(i=0;i<audioInNum;i++)
			{
				m_audioInList.InsertString(i,m_audioInInfoList[i].cName);
			}
		}


		ret = TE_GetAudioOutInfo(&audioOutNum, m_audioOutInfoList);
		if(audioOutNum>0)
		{
			for(i=0;i<audioOutNum;i++)
			{
				m_audioOutList.InsertString(i,m_audioOutInfoList[i].cName);
			}
		}

	}
}
void CTE_DemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}
	if (!m_Pcontact)
	{
		m_Pcontact = new CTE_Contact(this);
		if(m_Pcontact)
		{
			m_Pcontact->Create(IDD_DIALOG_CONTACT);
		}
	}

	m_Pcontact->ShowWindow(SW_SHOWNORMAL);
	m_Pcontact->OnUpdateRecordList();
}

void CTE_DemoDlg::OnBnClickedButtonConfcreate()
{
	// TODO: 在此添加控件通知处理程序代码


	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}

	//TE_S_SITE_INVITEDLIST _contacts={{NULL},0};
	TE_S_SITE_INVITEDLIST _contacts;
	TE_S_CONTACTS_INFO contactslist;
	contactslist.contact = NULL;
	contactslist.num = 0;
	int i=0;
	_contacts.listCount = 0;
	TE_E_USEKEY_SORT_RULE sortRule =group_status_first;
	//memset(&_contacts,0,sizeof(TE_S_SITE_INVITEDLIST));
	if(!m_pContactDlg)
	{
		m_pContactDlg = new CTE_ConfContacts();
		m_pContactDlg->Create(IDD_DIALOG_CONFERENCE_CONTACTS);
	}

	if(m_pContactDlg)
	{
		m_pContactDlg->ShowWindow(SW_SHOWNORMAL);
		m_pContactDlg->demodlg = this;
	}
//	::PostMessage(m_pContactDlg->GetSafeHwnd(), WM_CONTACT_SHOW_IMPORT_SELECTDLG, NULL, NULL);
#if 0
	LONG lStyle;
	lStyle = GetWindowLong(m_pContactDlg->m_ConfContactsList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_pContactDlg->m_ConfContactsList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_pContactDlg->m_ConfContactsList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件

	m_pContactDlg->m_ConfContactsList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_pContactDlg->m_ConfContactsList.InsertColumn( 1, "NAME", LVCFMT_LEFT, 240 );
	m_pContactDlg->m_ConfContactsList.InsertColumn( 2, "NUMBER", LVCFMT_LEFT, 240 );
	
#endif

	std::wstring cstrName;
	CString strTmp;
	int ret = TE_GetContactList(sortRule,&contactslist);
	if(0 == ret)
	{
		m_pContactDlg->m_ConfContactsList.DeleteAllItems();
		for(i=0;i<contactslist.num;i++)
		{
			//cstrName = Utf82Unicode(contactslist.contact[i].name);
			int nRowNum = m_pContactDlg->m_ConfContactsList.InsertItem( i , contactslist.contact[i].name);
			//cstrName = Utf82Unicode(contactslist.contact[i].ucAcc);
			m_pContactDlg->m_ConfContactsList.SetItemText( nRowNum, 1,contactslist.contact[i].ucAcc);
		}
	}
	/*_contacts.list[0]="01052418";
	_contacts.list[1]="01052419";
	_contacts.listCount=2;*/

	//TE_CreateConf(&_contacts);
	//m_confInfo.SetWindowText(_T("等待服务响应，请稍后..."));*/
	TE_FreeMemory(contactslist.contact);
}
void CTE_DemoDlg::ContactCall(TE_CHAR* callnum)
{
	int len = 0;
	CString msg;
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}


		
		
	TE_MakeCall(callnum, TE_E_CALL_TYPE_IPVIDEO);
	
	

	if(!m_incomingCall)
	{
		m_incomingCall = new CTE_IncomingCall();
		m_incomingCall->Create(IDD_COMMINGCALL_DIALOG);//create non-modal dialog.
	}

	if(!m_incomingCall)
	{
		return;
	}
	m_incomingCall->rectLarge = CRect(561,286,1515,1006);
	m_incomingCall->rectSmall = CRect(561,286,1515,423);

	CRect picRect;  

	m_incomingCall->m_bound.GetWindowRect(&picRect); 
	m_incomingCall->rectSmall.bottom=415; 

	//if(m_Pcontact->m_ContactVideo.GetCheck())

	m_incomingCall->m_isVideo = TRUE;
	m_incomingCall->m_btnShare.EnableWindow(TRUE);
	m_incomingCall->m_btnStopShare.EnableWindow(TRUE);
	m_incomingCall->exeShareBtn.EnableWindow(TRUE);
	::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectLarge.Width(),m_incomingCall->rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);


	m_incomingCall->m_bIsHangup = false;
	m_incomingCall->ShowWindow(SW_SHOWNORMAL);
	m_incomingCall->SetForegroundWindow();//create thread of specified window to foreground and activate this window.
	strncpy(m_incomingCall->callername,callnum,TE_D_NAME_LEN);
	msg.Format("%s",callnum);
	m_incomingCall->SetWindowText(msg);

	::SetWindowLongA(m_incomingCall->m_LocalWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowLongA(m_incomingCall->m_RemoteWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);	
}


void CTE_DemoDlg::ContactVideoCall(TE_CHAR* callnum)
{
	int len = 0;
	CString msg;
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}

	TE_MakeCall(callnum, TE_E_CALL_TYPE_IPVIDEO);


	if(!m_incomingCall)
	{
		m_incomingCall = new CTE_IncomingCall();
		m_incomingCall->Create(IDD_COMMINGCALL_DIALOG);//create non-modal dialog.
	}

	if(!m_incomingCall)
	{
		return;
	}
	m_incomingCall->rectLarge = CRect(561,286,1515,1006);
	m_incomingCall->rectSmall = CRect(561,286,1515,423);

	CRect picRect;  

	m_incomingCall->m_bound.GetWindowRect(&picRect); 
	m_incomingCall->rectSmall.bottom=415; 

		m_incomingCall->m_isVideo = TRUE;
		m_incomingCall->m_btnShare.EnableWindow(TRUE);
		m_incomingCall->m_btnStopShare.EnableWindow(TRUE);
		m_incomingCall->exeShareBtn.EnableWindow(TRUE);
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectLarge.Width(),m_incomingCall->rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);

	m_incomingCall->m_bIsHangup = false;
	m_incomingCall->ShowWindow(SW_SHOWNORMAL);
	m_incomingCall->SetForegroundWindow();//create thread of specified window to foreground and activate this window.
	strncpy(m_incomingCall->callername,callnum,TE_D_NAME_LEN);
	msg.Format("%s",callnum);
	m_incomingCall->SetWindowText(msg);

	::SetWindowLongA(m_incomingCall->m_LocalWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowLongA(m_incomingCall->m_RemoteWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);	
}

void CTE_DemoDlg::ContactAudioCall(TE_CHAR* callnum)
{
	int len = 0;
	CString msg;
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}

		TE_MakeCall(callnum, TE_E_CALL_TYPE_IPAUDIO);


	if(!m_incomingCall)
	{
		m_incomingCall = new CTE_IncomingCall();
		m_incomingCall->Create(IDD_COMMINGCALL_DIALOG);//create non-modal dialog.
	}

	if(!m_incomingCall)
	{
		return;
	}
	m_incomingCall->rectLarge = CRect(561,286,1515,1006);
	m_incomingCall->rectSmall = CRect(561,286,1515,423);

	CRect picRect;  

	m_incomingCall->m_bound.GetWindowRect(&picRect); 
	m_incomingCall->rectSmall.bottom=415; 

	
		m_incomingCall->m_btnShare.EnableWindow(FALSE);		
		m_incomingCall->m_btnStopShare.EnableWindow(FALSE);
		m_incomingCall->exeShareBtn.EnableWindow(FALSE); 
		::SetWindowPos(m_incomingCall->GetSafeHwnd(),NULL,0,0,m_incomingCall->rectSmall.Width(),m_incomingCall->rectSmall.Height(),SWP_NOMOVE | SWP_NOZORDER);

	m_incomingCall->m_bIsHangup = false;
	m_incomingCall->ShowWindow(SW_SHOWNORMAL);
	m_incomingCall->SetForegroundWindow();//create thread of specified window to foreground and activate this window.
	strncpy(m_incomingCall->callername,callnum,TE_D_NAME_LEN);
	msg.Format("%s",callnum);
	m_incomingCall->SetWindowText(msg);

	::SetWindowLongA(m_incomingCall->m_LocalWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowLongA(m_incomingCall->m_RemoteWindow.GetSafeHwnd(),GWL_EXSTYLE,WS_CLIPSIBLINGS);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	::SetWindowPos(m_incomingCall->m_LocalWindow.GetSafeHwnd(),NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);	
}


void CTE_DemoDlg::OnBnClickedButtonSwitchCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	int choice,ret;
	TE_S_CAMERA_INFO m_camerainfolist[20];
	TE_UINT32 cameraNum ;
	ret = TE_GetCamerasInfo(&cameraNum, m_camerainfolist);
	if(m_isLogin)
	{
		if(TE_SDK_Success == ret)
		{
			if(0 == cameraNum)
			{
				AfxMessageBox("Not camera,Please first install camera");
				return;
			}
			choice = m_cameralist.GetCurSel();
			m_cameralist.SetCurSel(choice);
			TE_SwitchCamera(choice);
		}
		else if( TE_SDK_NotFoundcamera == ret)
		{
			AfxMessageBox(_T("not have cameras."));
		}
		else
		{
			AfxMessageBox(_T("The device is busy now,Please hungup the call, try again."));
		}
		
	}else
	{
		AfxMessageBox(_T("Please first Login"));
	}
	return;
}

void CTE_DemoDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_transMode.GetCurSel()==0)
	{
		m_CStrPortNum="5061";
	} 
	else
	{
		m_CStrPortNum="5060";
	}
    UpdateData(FALSE);
}

void CTE_DemoDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	TE_SetAudioInDevice(m_audioInList.GetCurSel());
}

void CTE_DemoDlg::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	TE_SetAudioOutDevice(m_audioOutList.GetCurSel());
}

void CTE_DemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}
	if (!m_Enterprise)
	{
		m_Enterprise = new CTE_Enterprise(this);
		if(m_Enterprise)
		{
			m_Enterprise->Create(IDD_DIALOG_ENTERPRISE_ADDR);
		}
	}

	m_Enterprise->ShowWindow(SW_SHOWNORMAL);

	LONG lStyle;
	lStyle = GetWindowLong(m_Enterprise->m_EnterpriseList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_Enterprise->m_EnterpriseList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_Enterprise->m_EnterpriseList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_Enterprise->m_EnterpriseList.SetExtendedStyle(dwStyle); //设置扩展风格
	while   (m_Enterprise->m_EnterpriseList.DeleteColumn(0));
	m_Enterprise->m_EnterpriseList.InsertColumn( 1, "NAME", LVCFMT_LEFT, 150 );
	m_Enterprise->m_EnterpriseList.InsertColumn( 2, "NUMBER", LVCFMT_LEFT, 150 );
	m_Enterprise->m_EnterpriseList.InsertColumn( 3, "DEPARTMENT", LVCFMT_LEFT, 150 );
	m_Enterprise->m_EnterpriseList.InsertColumn( 4, "MOBILEPHONE", LVCFMT_LEFT, 150 );
	m_Enterprise->m_EnterpriseList.InsertColumn( 5, "OFFICEPHONE", LVCFMT_LEFT, 150 );
	m_Enterprise->m_EnterpriseList.InsertColumn( 6, "EMAIL", LVCFMT_LEFT, 150 );
	m_Enterprise->m_EnterpriseList.InsertColumn( 7, "ADDRESS", LVCFMT_LEFT, 150 );
	m_Enterprise->m_search.Format("");
	m_Enterprise->UpdateData(FALSE);
	char keyword[512]={"0"};
	TE_S_CONTACTS_INFO contactsList;
	contactsList.contact = NULL;
	contactsList.num = 0;
	TE_UINT32 enterpriseType=1;
	TE_GetEnterpriseBookType(&enterpriseType);
	if(1 == enterpriseType)
	{
		TE_SearchLdap(keyword);
	}
	else
	{
		TE_GetAllEnterpriseContacts(&contactsList);
		OnShowEnterpriseResult(&contactsList);
		TE_FreeMemory(contactsList.contact);
	}
}

void CTE_DemoDlg::OnShowEnterpriseResult(TE_S_CONTACTS_INFO* contactsList)
{
	int nRowNum =1;
	CString strTmp;
	int i=0;
	m_Enterprise->m_EnterpriseList.DeleteAllItems();
	for( int j = 0; j < contactsList->num; j++ )
	{
		// 插入一行，先插入行号, 作为第一列
		strTmp.Format("%s", contactsList->contact[j].name);
		int nRowNum = m_Enterprise->m_EnterpriseList.InsertItem( j , strTmp);
		// 插入第二列的值
		CString strTempValue;
		strTempValue.Format("%s",contactsList->contact[j].ucAcc);
		m_Enterprise->m_EnterpriseList.SetItemText( nRowNum, 1,strTempValue );
		strTempValue.Format("%s", contactsList->contact[j].deptname);
		m_Enterprise->m_EnterpriseList.SetItemText( nRowNum, 2,strTempValue );
		strTempValue.Format("%s",contactsList->contact[j].mobile);
		m_Enterprise->m_EnterpriseList.SetItemText( nRowNum, 3,strTempValue );
		strTempValue.Format("%s",contactsList->contact[j].officePhone);
		m_Enterprise->m_EnterpriseList.SetItemText( nRowNum, 4,strTempValue );
		strTempValue.Format("%s",contactsList->contact[j].email);
		m_Enterprise->m_EnterpriseList.SetItemText( nRowNum, 5,strTempValue );
		strTempValue.Format("%s", contactsList->contact[j].addresssite);
		m_Enterprise->m_EnterpriseList.SetItemText( nRowNum, 6,strTempValue );
	}

}

void CTE_DemoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_isLogin)
	{
		AfxMessageBox(_T("Please Login in."));
		return;
	}
	if (!m_HistroyRecord)
	{
		m_HistroyRecord = new CTE_HistoryRecord(this);
		if(m_HistroyRecord)
		{
			m_HistroyRecord->Create(IDD_DIALOG_HISTORYRECORD);
		}
	}

	m_HistroyRecord->ShowWindow(SW_SHOWNORMAL);

	LONG lStyle;
	lStyle = GetWindowLong(m_HistroyRecord->m_historyRecord.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_HistroyRecord->m_historyRecord.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_HistroyRecord->m_historyRecord.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_HistroyRecord->m_historyRecord.SetExtendedStyle(dwStyle); //设置扩展风格
	while   (m_HistroyRecord->m_historyRecord.DeleteColumn(0));
	m_HistroyRecord->m_historyRecord.InsertColumn( 1, "NUMBER", LVCFMT_LEFT, 150 );
	m_HistroyRecord->m_historyRecord.InsertColumn( 2, "TIME", LVCFMT_LEFT, 120 );
	m_HistroyRecord->m_historyRecord.InsertColumn( 3, "ID", LVCFMT_LEFT, 10 );
	char key[512] = {"0"};
	TE_S_PERSONS_INFO  historyInfo;
	TE_UINT32 num =0;
	int i = 0,j=0;
	int nRowNum =1;
	std::wstring cstrName;
	CString strTmp;
	//int ret = TE_InitListView(key);
	historyInfo.historyRecords = NULL;
	historyInfo.num = -1;
	TE_GetRecentCallRecords(&historyInfo);
	m_HistroyRecord->m_historyRecord.DeleteAllItems();
	for( int j = 0; j < historyInfo.num; j++ )
	{
		// 插入一行，先插入行号, 作为第一列
		//cstrName = Utf82Unicode(historyInfo.historyRecords[j].strName);
		strTmp.Format("%s", historyInfo.historyRecords[j].strName);
		int nRowNum = m_HistroyRecord->m_historyRecord.InsertItem( j , strTmp);
		// 插入第二列的值
		CString strTempValue;
		//cstrName = Utf82Unicode(historyInfo.historyRecords[j].strTime);
		strTempValue.Format("%s", historyInfo.historyRecords[j].strTime);
		m_HistroyRecord->m_historyRecord.SetItemText( nRowNum, 1,strTempValue );

		CString TempValue;
		long long historycord = historyInfo.historyRecords[j].recordID;
		TempValue.Format("%ld", historycord);
		m_HistroyRecord->m_historyRecord.SetItemText( nRowNum, 2,TempValue );
	}
	TE_FreeMemory(historyInfo.historyRecords);
}

void CTE_DemoDlg::OnStnClickedStaticInfo()
{
	// TODO: 在此添加控件通知处理程序代码
}
