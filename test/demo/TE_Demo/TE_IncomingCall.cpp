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

// TE_IncomingCall.cpp :
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "TE_IncomingCall.h"
#include <Psapi.h>
#include "string"
#pragma comment(lib, "Psapi.lib")  

static std::vector<ST_WndInfo> m_stAppList;
static std::map<DWORD, HWND> m_proWndMap;
// CTE_IncomingCall 


IMPLEMENT_DYNAMIC(CTE_IncomingCall, CDialog)

CTE_IncomingCall::CTE_IncomingCall(CWnd* pParent /*NULL*/)
	: CDialog(CTE_IncomingCall::IDD, pParent)
	,m_lDuration(0)
	, m_CallState(_T(""))
	,m_isMicMute(0)
	,m_isSpeakerMute(0)
	,m_isVideo(0)
	,m_isCheckVedio(0)
	,m_isCheckAudio(0)
	,m_dataShareWind(NULL)
	,isEXEshare(false)
	,m_isSharingWnd(false)
{
	m_confCtrl=NULL;
	m_dailCtrl=NULL;

}

CTE_IncomingCall::~CTE_IncomingCall()
{
	m_dataShareWind=NULL;
	if (m_confCtrl)
	{
		m_confCtrl->DestroyWindow();
	}
	m_confCtrl=NULL;
	if (m_dailCtrl)
	{
		m_dailCtrl->DestroyWindow();
	}
	m_dailCtrl=NULL;
}

void CTE_IncomingCall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPEAKER_BUTTON2, m_bSpeaker);
	DDX_Control(pDX, IDC_MIC_BUTTON2, m_bMIC);
	DDX_Text(pDX, IDC_CALL_STATE, m_CallState);
	DDX_Control(pDX, IDANSWER, m_btnAnswer);
	DDX_Control(pDX, IDREJECT, m_btnReject);
	DDX_Control(pDX, IDC_HANGUP_BUTTON, m_btnHangup);
	DDX_Control(pDX, IDC_STATIC_REMOTE, m_RemoteWindow);
	DDX_Control(pDX, IDC_STATIC_LOCAL, m_LocalWindow);
	DDX_Control(pDX, IDC_VIDEO_BUTTON, m_btnVideo);
	DDX_Control(pDX, IDC_STARTSHARE_BTN, m_btnShare);
	DDX_Control(pDX, IDC_STATIC_DISPLAYSHARE, m_displayShareWind);
	DDX_Control(pDX, IDC_STOPSHARE_BTN, m_btnStopShare);
	DDX_Control(pDX, IDC_LIST_APPS, m_listApps);
	DDX_Control(pDX, IDC_SHAREEXE_BTN, exeShareBtn);
	DDX_Control(pDX, IDC_STATIC1, m_bound);
	DDX_Control(pDX, IDC_BUTTON_CONF, m_btnConfCtrl);
	DDX_Control(pDX, IDC_BTN_ATOV, m_btnAtov);
	DDX_Control(pDX, IDC_BTN_VTOA, m_btnVtoa);
	DDX_Control(pDX, IDC_BTN_VEDIOANSWER, m_vedioAnswer);
}


BEGIN_MESSAGE_MAP(CTE_IncomingCall, CDialog)
	ON_BN_CLICKED(IDANSWER, &CTE_IncomingCall::OnBnClickedOk)
	ON_BN_CLICKED(IDREJECT, &CTE_IncomingCall::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SPEAKER_BUTTON2, &CTE_IncomingCall::OnBnClickedSpeakerButton2)
	ON_BN_CLICKED(IDC_MIC_BUTTON2, &CTE_IncomingCall::OnBnClickedMicButton2)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_HANGUP_BUTTON, &CTE_IncomingCall::OnBnClickedHangupButton)
	ON_MESSAGE(WM_CALL_UPDATE_STATE, &CTE_IncomingCall::UpdateCallState)
	ON_BN_CLICKED(IDC_VIDEO_BUTTON, &CTE_IncomingCall::OnBnClickedVideoButton)
	ON_BN_CLICKED(IDC_STARTSHARE_BTN, &CTE_IncomingCall::OnBnClickedStartshareBtn)
	ON_BN_CLICKED(IDC_STOPSHARE_BTN, &CTE_IncomingCall::OnBnClickedStopshareBtn)
	ON_BN_CLICKED(IDC_SHAREEXE_BTN, &CTE_IncomingCall::OnBnClickedShareexeBtn)
	ON_NOTIFY(NM_CLICK, IDC_LIST_APPS, &CTE_IncomingCall::OnNMClickListApps)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_APPS, &CTE_IncomingCall::OnLvnItemchangedListApps)
	ON_BN_CLICKED(IDC_BUTTON_CONF, &CTE_IncomingCall::OnBnClickedButtonConf)
	ON_BN_CLICKED(IDC_BTN_ATOV, &CTE_IncomingCall::OnBnClickedBtnAtov)
	ON_BN_CLICKED(IDC_BTN_VTOA, &CTE_IncomingCall::OnBnClickedBtnVtoa)
	ON_BN_CLICKED(IDC_BTN_DIAL_PLATE, &CTE_IncomingCall::OnBnClickedBtnDialPlate)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VOICEOUT, &CTE_IncomingCall::OnNMCustomdrawSliderVoiceout)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SPEAKER_BUTTON, &CTE_IncomingCall::OnNMCustomdrawSpeakerButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VOICEIN, &CTE_IncomingCall::OnNMCustomdrawSliderVoicein)
	ON_BN_CLICKED(IDC_BTN_VEDIOANSWER, &CTE_IncomingCall::OnBnClickedBtnVedioanswer)
END_MESSAGE_MAP()


// CTE_IncomingCall 
/**************************************************
 * @fn         OnBnClickedOk()
 * @brief      answer phone call
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  call ID,video call flag
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnBnClickedOk()
{
	int ret =0;
	// TODO: 
	if (TE_E_CALL_TYPE_IPAUDIO == m_CallStateInfo.enCallType)
	{
		ret = TE_AnswerAudioCall(m_CallStateInfo.ulCallID);
	}
	else if(TE_E_CALL_TYPE_IPVIDEO == m_CallStateInfo.enCallType)
	{
		ret = TE_AnswerVideoCall(m_CallStateInfo.ulCallID,1);
	}
	
	//OnOK();
}
/**************************************************
 * @fn         OnBnClickedCancel()
 * @brief      reject coming call
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  Call ID
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnBnClickedCancel()
{
	// TODO: 
	int ret = TE_RejectCall(m_CallStateInfo.ulCallID);
	m_lDuration = 0;
	KillTimer(TIME_ID);
	m_CallState.Format(_T("Call End"));
	UpdateData(FALSE);
	OnCancel();
}
/**************************************************
 * @fn         OnBnClickedSpeakerButton2()
 * @brief      Set speaker mute or unmute
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  Call ID,flag     0:unmute 1:mute
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnBnClickedSpeakerButton2()
{
	// TODO: 
	int ret = 0;
	if (m_isSpeakerMute == 0)
	{
		ret = TE_SetLocalSpeaker(m_CallStateInfo.ulCallID,true);
		if (TE_SDK_Success == ret)
		{
			m_isSpeakerMute = 1;
			m_bSpeaker.SetWindowTextA(_T("Speaker UnMute"));
			((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->SetPos(0);
			UpdateData(true);
		}
		else
		{
			CString msg;
			msg.Format("Login Failure: %d", ret);
			SetWindowText(msg);
		}
		
	}
	else
	{
		ret = TE_SetLocalSpeaker(m_CallStateInfo.ulCallID,false);
		if (TE_SDK_Success == ret)
		{
			m_isSpeakerMute = 0;
			m_bSpeaker.SetWindowTextA(_T("Speaker Mute"));
			((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->SetPos(20);
			UpdateData(true);
		}
		else
		{
			CString msg;
			msg.Format("Login Failure: %d", ret);
			SetWindowText(msg);
		}

	}
}
/**************************************************
 * @fn         OnBnClickedMicButton2()
 * @brief      Set mic mute or unmute
 * @return     Success return 0,
 *			   Failure return errCode,see EM_TEServiceRetvCode
 * @param[in]  Call ID,flag     0:unmute 1:mute
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnBnClickedMicButton2()
{
	
	int ret = 0;
	if (m_isMicMute == 0)
	{
		ret = TE_SetLocalMic(m_CallStateInfo.ulCallID,1);
		if (TE_SDK_Success == ret)
		{
			m_isMicMute = 1;
			m_bMIC.SetWindowTextA(_T("Mic UnMute"));

			((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->SetPos(0);

			UpdateData(true);
		}
		else
		{
			CString msg;
			msg.Format("Login Failure: %d", ret);
			SetWindowText(msg);
		}
		
	}
	else
	{
		ret = TE_SetLocalMic(m_CallStateInfo.ulCallID,0);
		if (TE_SDK_Success == ret)
		{
			m_isMicMute = 0;
			m_bMIC.SetWindowTextA(_T("Mic Mute"));
			((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->SetPos(20);
			UpdateData(true);
		}
		else
		{
			CString msg;
			msg.Format("Login Failure: %d", ret);
			SetWindowText(msg);
		}

	}
}


BOOL CTE_IncomingCall::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
		m_ToolTip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}



void CTE_IncomingCall::OnPaint()
{
	CDialog::OnPaint();
}
BOOL CTE_IncomingCall::OnInitDialog()
{

	LONG style = GetWindowLong(GetDlgItem(IDC_STATIC_LOCAL)->GetSafeHwnd(),GWL_STYLE);
	style = style | WS_CLIPSIBLINGS ;
	SetWindowLong(GetDlgItem(IDC_STATIC_LOCAL)->GetSafeHwnd(),GWL_STYLE,style);

	style = GetWindowLong(GetDlgItem(IDC_STATIC_REMOTE)->GetSafeHwnd(),GWL_STYLE);
	style = style | WS_CLIPSIBLINGS ;
	SetWindowLong(GetDlgItem(IDC_STATIC_REMOTE)->GetSafeHwnd(),GWL_STYLE,style);

	

	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CONF)); // IDB_BITMAP_TEST为资源图片ID  
	((CButton *)GetDlgItem(IDC_BUTTON_CONF))->SetBitmap(hBitmap);  

	HBITMAP   hBitmap1;   
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_DIAL_PLATE)); // IDB_BITMAP_TEST为资源图片ID  
	((CButton *)GetDlgItem(IDC_BTN_DIAL_PLATE))->SetBitmap(hBitmap1);  
	/*::SetWindowPos(m_LocalWindow.GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOREDRAW);
	::SetWindowPos(m_RemoteWindow.GetSafeHwnd(),HWND_BOTTOM,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);*/


	m_ToolTip.Create(this);//创建对象
	m_ToolTip.AddTool( GetDlgItem(IDC_BUTTON_CONF), "会议控制" ); 

	m_ToolTip.SetDelayTime(200);
	m_ToolTip.SetTipTextColor( RGB(0,0,0 ));//设置提示字体颜色
	m_ToolTip.SetTipBkColor( RGB(255,255,255));//设置提示背景颜色
	m_ToolTip.Activate(TRUE);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->SetRange(0,100);//设置滑动范围
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->SetTicFreq(10);//每5个单位画一刻度
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->SetPos(TE_GetVolume(TE_E_VOLUME_TYPE_MIC));

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->SetRange(0,100);//设置滑动范围
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->SetTicFreq(10);//每5个单位画一刻度
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->SetPos(TE_GetVolume(TE_E_VOLUME_TYPE_SPEAK));


	CDialog::OnInitDialog();
	//::SetWindowPos(m_LocalWindow.GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);
	return TRUE;  // return TRUE unless you set the focus to a control
}
/**************************************************
 * @fn         OnTimer(UINT_PTR nIDEvent)
 * @brief      set calling time.
 * @return     NA 
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnTimer(UINT_PTR nIDEvent)
{

	if(TIME_ID == nIDEvent)
	{
		m_lDuration++;
		CString strTimer;
		int secod = m_lDuration%60;
		int minte = m_lDuration/60;
		int hour = minte/60;
		minte = minte%60;
		strTimer.Format("%2d:%2d:%2d  %s",hour,minte,secod,m_CallStateInfo.acDisplayName);
		SetWindowText(strTimer);
	}

	CDialog::OnTimer(nIDEvent);
}
/**************************************************
 * @fn         OnClose()
 * @brief      Close Call Window
 * @return     NA
 * @param[in]  NA
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnClose()
{
	if (m_btnConfCtrl.IsWindowEnabled())
	{
		if (TE_SDK_Success==TE_IsConfChairMan())
		{

			int rest=::MessageBox(NULL,"点击‘是’结束会议；点击‘否’离开会议；点击‘取消’放弃本次操作！","INFO",MB_YESNOCANCEL);
			if(IDYES==rest) 
			{
				TE_EndConf();
			}
			else if(IDNO==rest) 
			{

			}
			else
			{
				return;
			}
		}
	}

	if (m_isSharingWnd)
	{
		TE_StopLecture(m_CallStateInfo.ulCallID);
		m_isSharingWnd=false;
	}
    Sleep(1000);
	if(!m_bIsHangup)
	{
		TE_DropCall(m_CallStateInfo.ulCallID);

	}

	KillTimer(TIME_ID);
	

	if (m_listApps.GetItemCount()>0)
	{
		m_listApps.DeleteColumn(0);
		m_listApps.DeleteColumn(0);
		m_listApps.DeleteAllItems();
	}


	if (m_confCtrl)
	{
		m_confCtrl->DestroyWindow();
	}

	m_confCtrl=NULL;


	if (m_dailCtrl)
	{
		m_dailCtrl->DestroyWindow();
	}

	m_dailCtrl=NULL;

	m_lDuration = 0;

	

	CDialog::OnClose();
}
/**************************************************
 * @fn         UpdateCallState(WPARAM wParm, LPARAM Lparam)
 * @brief      update call window
 * @attention  NA
****************************************************/
LRESULT CTE_IncomingCall::UpdateCallState(WPARAM wParm, LPARAM Lparam)
{

	if (!m_isCheckVedio && !m_isCheckAudio)
	{
		if(TE_E_CALL_TYPE_IPAUDIO == m_CallStateInfo.enCallType)
		{
			m_isVideo = FALSE;
		}
		else if(TE_E_CALL_TYPE_IPVIDEO == m_CallStateInfo.enCallType)
		{
			m_isVideo = TRUE;

		}
		else
		{
			m_isVideo = FALSE;
		}
	}
	

	switch(m_CallStateInfo.enCallEvent)
	{
		case TE_E_CALL_EVENT_AUDIOVIDEOINCOMING:
		{
			if(TRUE == m_isVideo)
			{
				m_btnVideo.EnableWindow(TRUE);
				m_btnShare.EnableWindow(TRUE);
				m_btnStopShare.EnableWindow(TRUE);
				exeShareBtn.EnableWindow(TRUE);

				m_btnVtoa.EnableWindow(TRUE);
				m_btnVtoa.ShowWindow(SW_SHOW);

				m_btnAtov.EnableWindow(FALSE);
				m_btnAtov.ShowWindow(SW_HIDE);
				m_vedioAnswer.EnableWindow(TRUE);
				m_btnAnswer.EnableWindow(TRUE);
				//TE_SetDisplayHandle(m_CallStateInfo.ulCallID,m_LocalWindow.GetSafeHwnd(), m_RemoteWindow.GetSafeHwnd());

			}
			else
			{
				m_btnShare.EnableWindow(FALSE);
				m_btnStopShare.EnableWindow(FALSE);
				exeShareBtn.EnableWindow(FALSE);

				m_btnVtoa.EnableWindow(FALSE);
				m_btnVtoa.ShowWindow(SW_HIDE);

				m_btnAtov.EnableWindow(TRUE);
				m_btnAtov.ShowWindow(SW_SHOW);
				m_vedioAnswer.EnableWindow(FALSE);
				m_btnAnswer.EnableWindow(TRUE);
			}
			
			m_btnReject.EnableWindow(TRUE);
			m_bSpeaker.EnableWindow(FALSE);
			m_bMIC.EnableWindow(FALSE);
			m_btnHangup.EnableWindow(FALSE);
			m_btnVideo.EnableWindow(FALSE);
			
			break;
		}
		case TE_E_CALL_EVENT_CALLRING:
		{
			if(TRUE == m_isVideo)
			{
				m_LocalWindow.ShowWindow(SW_SHOW);
				m_RemoteWindow.ShowWindow(SW_SHOW);
				//TE_SetDisplayHandle(m_CallStateInfo.ulCallID,m_LocalWindow.GetSafeHwnd(), m_RemoteWindow.GetSafeHwnd());

			}
			m_btnAnswer.EnableWindow(FALSE);
			m_vedioAnswer.EnableWindow(FALSE);
			m_btnReject.EnableWindow(TRUE);
			m_bSpeaker.EnableWindow(FALSE);
			m_bMIC.EnableWindow(FALSE);
			m_btnHangup.EnableWindow(FALSE);
			m_btnVideo.EnableWindow(FALSE);
			break;
		}
		case TE_E_CALL_EVENT_ANSWERRSP:
		{
			if(TRUE == m_isVideo)
			{
				m_LocalWindow.ShowWindow(SW_SHOW);
				m_RemoteWindow.ShowWindow(SW_SHOW);
				m_btnVideo.EnableWindow(TRUE);
				m_btnAnswer.EnableWindow(FALSE);
				m_vedioAnswer.EnableWindow(FALSE);
				m_btnReject.EnableWindow(FALSE);
				m_bSpeaker.EnableWindow(TRUE);
				m_bMIC.EnableWindow(TRUE);
				m_btnHangup.EnableWindow(TRUE);
				m_btnVtoa.EnableWindow(TRUE);
				m_btnVtoa.ShowWindow(SW_SHOW);
				m_btnShare.EnableWindow(TRUE);
				m_btnAtov.EnableWindow(FALSE);
				m_btnAtov.ShowWindow(SW_HIDE);

				Sleep(6000);

				TE_S_SITE_INFO localHall;
				memset(&localHall, 0, sizeof(TE_S_SITE_INFO));

				TE_GetLocalSite(&localHall);

				if (localHall.isJoined_ && localHall.T_!=0)
				{

					
					m_btnVtoa.EnableWindow(FALSE);
					m_btnVtoa.ShowWindow(SW_HIDE);
					m_btnVtoa.RedrawWindow(0,NULL,RDW_ALLCHILDREN|RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
					m_btnAtov.EnableWindow(FALSE);
					m_btnAtov.ShowWindow(SW_HIDE);
					m_btnAtov.RedrawWindow(0,NULL,RDW_ALLCHILDREN|RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
					m_btnConfCtrl.ShowWindow(SW_SHOW);
					m_btnConfCtrl.EnableWindow(TRUE);

				}



			}
			else
			{
				m_btnAnswer.EnableWindow(FALSE);
				m_vedioAnswer.EnableWindow(FALSE);
				m_btnReject.EnableWindow(FALSE);
				m_bSpeaker.EnableWindow(TRUE);
				m_bMIC.EnableWindow(TRUE);
				m_btnHangup.EnableWindow(TRUE);
				m_btnVideo.EnableWindow(FALSE);

				m_btnVtoa.EnableWindow(FALSE);
				m_btnVtoa.ShowWindow(SW_HIDE);

				m_btnAtov.EnableWindow(TRUE);
				m_btnAtov.ShowWindow(SW_SHOW);
			}
			

			break;
		}
		case TE_E_CALL_EVENT_CLOSE:
		{
			m_btnAnswer.EnableWindow(FALSE);
			m_vedioAnswer.EnableWindow(FALSE);
			m_btnReject.EnableWindow(FALSE);
			m_bSpeaker.EnableWindow(FALSE);
			m_bMIC.EnableWindow(FALSE);
			m_btnHangup.EnableWindow(FALSE);
			if(TRUE == m_isVideo)
			{
				m_LocalWindow.ShowWindow(SW_HIDE);
				m_RemoteWindow.ShowWindow(SW_HIDE);
			}
			m_isVideo = 0;
			m_isMicMute = 0;
			m_isSpeakerMute = 0;
			UpdateData(FALSE);
			OnCancel();

			if (m_listApps.GetItemCount()>0)
			{
				m_listApps.DeleteColumn(0);
				m_listApps.DeleteColumn(0);
				m_listApps.DeleteAllItems();
			}
			AfxMessageBox(_T("call end"));
			break;
		}
		default:
		{
			//do nothing.
			break;
		}


	}
	if (m_CallStateInfo.enDataEvent==TE_E_DATA_EVENT_DATASEND)
	{
		//m_btnShare.EnableWindow(FALSE);
	}
	if (m_CallStateInfo.enDataEvent==TE_E_DATA_EVENT_DATARECIEVE)
	{
		/*m_btnShare.EnableWindow(FALSE);
		m_btnStopShare.EnableWindow(FALSE);
		exeShareBtn.EnableWindow(FALSE);*/
		m_displayShareWind.ShowWindow(SW_SHOW);
		TE_StartRecvLecture(m_CallStateInfo.ulCallID);

	}
	if (m_CallStateInfo.enDataEvent==TE_E_DATA_EVENT_DATASTOPED)
	{
		if (!m_isCheckAudio)
		{
			m_btnShare.EnableWindow(TRUE);
			m_btnStopShare.EnableWindow(TRUE);
			exeShareBtn.EnableWindow(TRUE);
			m_displayShareWind.ShowWindow(SW_HIDE);
		}
		
		TE_StopRecvLecture(m_CallStateInfo.ulCallID);
		
	}
	
	UpdateData(FALSE);
	return 0L;
}
/**************************************************
 * @fn         OnBnClickedHangupButton()
 * @brief      hung up 
 * @param[in]  CALL ID
 * @attention  NA
****************************************************/
void CTE_IncomingCall::OnBnClickedHangupButton()
{
	if (m_btnConfCtrl.IsWindowEnabled())
	{
		if (TE_SDK_Success==TE_IsConfChairMan())
		{

			int rest=::MessageBox(NULL,"点击‘是’结束会议；点击‘否’离开会议；点击‘取消’放弃本次操作！","INFO",MB_YESNOCANCEL);
			if(IDYES==rest) 
			{
				TE_EndConf();
			}
			else if(IDNO==rest) 
			{
		
			}
			else
			{
				return;
			}
		}
	}

	m_bIsHangup = true;
	m_lDuration = 0;

	if (m_isSharingWnd)
	{
		TE_StopLecture(m_CallStateInfo.ulCallID);
		m_isSharingWnd=false;
	}

	Sleep(1000);
	TE_DropCall(m_CallStateInfo.ulCallID);
	m_lDuration = 0;
	KillTimer(TIME_ID);
	m_CallState.Format(_T("Call End"));
	UpdateData(FALSE);
	
	//m_LocalWindow.ShowWindow(SW_HIDE);
	//m_RemoteWindow.ShowWindow(SW_HIDE);
	//UpdateData(FALSE);
	//m_LocalWindow.SetRedraw();
	//m_RemoteWindow.SetRedraw();
	//m_RemoteWindow.RedrawWindow()
	m_LocalWindow.ShowWindow(SW_HIDE);
	m_RemoteWindow.ShowWindow(SW_HIDE);
	m_isVideo = 0;
	m_isCheckVedio=0;
	m_isCheckAudio=0;
	
	OnCancel();

	if (m_listApps.GetItemCount()>0)
	{
		m_listApps.DeleteColumn(0);
		m_listApps.DeleteColumn(0);
		m_listApps.DeleteAllItems();
	}
	//PostMessage(WM_CLOSE);
	m_btnConfCtrl.ShowWindow(SW_HIDE);
	m_btnConfCtrl.EnableWindow(FALSE);
	if (m_confCtrl)
	{
		m_confCtrl->DestroyWindow();
	}
	m_confCtrl=NULL;
	if (m_dailCtrl)
	{
		m_dailCtrl->DestroyWindow();
	}
	m_dailCtrl=NULL;

	
}

void CTE_IncomingCall::OnBnClickedVideoButton()
{
	int ret = 0;
	if (m_isVideo == 0)
	{
		ret = TE_SetLocalVideo(m_CallStateInfo.ulCallID,1);
		if (TE_SDK_Success == ret)
		{
			m_isVideo = 1;
			m_btnVideo.SetWindowTextA(_T("Close Video"));
			UpdateData(true);
		}
		else
		{
			CString msg;
			msg.Format("Login Failure: %d", ret);
			SetWindowText(msg);
		}

	}
	else
	{
		ret = TE_SetLocalVideo(m_CallStateInfo.ulCallID,0);
		if (TE_SDK_Success == ret)
		{
			m_isVideo = 0;
			m_btnVideo.SetWindowTextA(_T("Open Video"));
			UpdateData(true);
		}
		else
		{
			CString msg;
			msg.Format("Login Failure: %d", ret);
			SetWindowText(msg);
		}

	}
}

void CTE_IncomingCall::OnBnClickedStartshareBtn()
{
	m_dataShareWind= ::GetDesktopWindow();
	TE_SetShareWindHandle(m_CallStateInfo.ulCallID,m_dataShareWind);

	isEXEshare=false;

	if(TE_StartLecture(m_CallStateInfo.ulCallID)==TE_SDK_Success)
	{
		m_isSharingWnd=true;
		m_btnShare.EnableWindow(FALSE);
	}

	return;
}

void CTE_IncomingCall::OnBnClickedStopshareBtn()
{
	TE_StopLecture(m_CallStateInfo.ulCallID);
	m_isSharingWnd=false;
	return;
}

void CTE_IncomingCall::OnBnClickedShareexeBtn()
{
	if (m_listApps.GetItemCount()>0)
	{
		m_listApps.DeleteColumn(0);
		m_listApps.DeleteColumn(0);
		m_listApps.DeleteAllItems();
	}

	CRect rect;   
 
	m_listApps.GetClientRect(&rect);   

	m_listApps.InsertColumn(0, _T("line"), LVCFMT_CENTER, rect.Width()/3, 0);   
	m_listApps.InsertColumn(1, _T("Process"), LVCFMT_CENTER, rect.Width()*2/3, 1); 

	GetAppList();

	char rowno[10];
	for (int  nIndex = 0 ; nIndex <(int)m_stAppList.size() ; nIndex++)
	{
		itoa(nIndex,rowno,10);
		m_listApps.InsertItem(nIndex, (LPCTSTR)rowno);   
		m_listApps.SetItemText(nIndex, 1, _T(m_stAppList[nIndex].csWndTitle));
	}

}

BOOL CTE_IncomingCall::GetAppList()
{
	if(!m_proWndMap.empty())
	{
		m_proWndMap.clear();
	}
	if(!m_stAppList.empty())
	{
		m_stAppList.clear();
	}
	
	HANDLE hToken;
	HANDLE hProcess = GetCurrentProcess();
	if(OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		TOKEN_PRIVILEGES tkp;
		if(LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid))
		{
			tkp.PrivilegeCount = 1;
			tkp.Privileges[0].Attributes =SE_PRIVILEGE_ENABLED;
			BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
			if(FALSE == bRet)
			{
				
			}
		}
		(void)CloseHandle(hToken);
	}
	::EnumWindows(EnumWindowProc, (LPARAM)this);

	return TRUE;
}

BOOL CALLBACK CTE_IncomingCall::EnumWindowProc(HWND hWnd, LPARAM lParam)
{
	CTE_IncomingCall * pDlg = (CTE_IncomingCall*)lParam;

	if (hWnd == NULL)
	{
		return FALSE;
	}

	if (pDlg && hWnd == pDlg->m_hWnd)
	{
		return TRUE;
	}

	if (::IsWindow(hWnd) && ::IsWindowVisible(hWnd)
		&& (::GetWindowLong(hWnd, GWL_EXSTYLE)&WS_EX_TOOLWINDOW)!=WS_EX_TOOLWINDOW
		&& ::GetWindowLong(hWnd, GWL_HWNDPARENT)==0 )
	{
		DWORD dwPID = 0;  

		GetWindowThreadProcessId(hWnd, &dwPID);  
		HANDLE hBrowser = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);  

		WCHAR exePath[MAX_PATH +1];

		memset(exePath,0, MAX_PATH +1);
		(void)GetModuleFileNameEx(hBrowser, NULL, (LPSTR)exePath, MAX_PATH);
		(void)CloseHandle(hBrowser);
		CString strTemp;
		for(unsigned int i=0; i<wcslen(exePath); i++)  
			strTemp.AppendChar(exePath[i]); 

		(void)strTemp.MakeLower();

		if (!strTemp.IsEmpty() && strTemp.Find(_T("explorer.exe")) == -1)
		{
			//if(m_proWndMap.find(dwPID) == m_proWndMap.end() && dwPID !=GetCurrentProcessId())
			if(dwPID !=GetCurrentProcessId())
			{
				(void)m_proWndMap.insert(std::make_pair(dwPID, hWnd));

				ST_WndInfo taskInfo;
				taskInfo.hWnd = hWnd;
				TCHAR szWindow[256]={0};
				::GetWindowText(hWnd, szWindow, 255); 
				taskInfo.csWndTitle = szWindow;
				//taskInfo.hSmallIcon = GetWindowIcon(hWnd, ICON_SMALL);
				taskInfo.bChecked = FALSE;

				m_stAppList.push_back(taskInfo);
				memset(szWindow, 0, 256);
			}
			else
			{
				return TRUE;
			}
		}
	}

	return TRUE;
}
void CTE_IncomingCall::OnNMClickListApps(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	

	CString strLangName;   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   

	if (-1 != pNMListView->iItem)        
	{   
		  
		strLangName = m_listApps.GetItemText(pNMListView->iItem, 0);   
	    //AfxMessageBox(_T(strLangName));

		int  intResult;  

		intResult= atoi(strLangName); 
		
		m_dataShareWind=(HWND)m_stAppList[intResult].hWnd ;

		TE_SetShareWindHandle(m_CallStateInfo.ulCallID,m_dataShareWind);

		isEXEshare=true;

		if(TE_StartLecture(m_CallStateInfo.ulCallID)==TE_SDK_Success)
		{
			
			//m_btnShare.EnableWindow(FALSE);
			m_isSharingWnd=true;
		}


	}   


}


void CTE_IncomingCall::OnLvnItemchangedListApps(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTE_IncomingCall::OnBnClickedButtonConf()
{
	// TODO: 在此添加控件通知处理程序代码
	/*TE_S_SITE_JIONEDLIST _confHallList;
	memset(&_confHallList, 0, sizeof(TE_S_SITE_JIONEDLIST));
	TE_GetConfMemberSites(&_confHallList);


	TE_S_SITE_INFO localHall;
	memset(&localHall, 0, sizeof(TE_S_SITE_INFO));

	TE_GetLocalSite(&localHall);

	

	int i=0;*/


	if(!m_confCtrl)
	{
		m_confCtrl = new CTE_ConfCtrl();
		m_confCtrl->Create(IDD_DIALOG_CONF);
	}
	m_confCtrl->ShowWindow(SW_SHOWNORMAL);
	m_confCtrl->SetForegroundWindow();
	m_confCtrl->m_extendTimeBtn.EnableWindow(FALSE);
	//m_confCtrl->m_applyChairMan.EnableWindow(FALSE);
	m_confCtrl->m_addMember.EnableWindow(FALSE);
	//m_confCtrl->m_releaseChairMan.ShowWindow(SW_HIDE);

	if (m_confCtrl->m_confMemList.GetItemCount()>0)
	{
		m_confCtrl->m_confMemList.DeleteAllItems();
		while(m_confCtrl->m_confMemList.DeleteColumn(0)){}
	}

	m_confCtrl->m_confMemList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
	m_confCtrl->m_confMemList.SetImageList(&m_confCtrl->myimage,LVSIL_SMALL);	//设置图像链表

	CRect rect;   

	m_confCtrl->m_confMemList.GetClientRect(&rect);  
	m_confCtrl->m_confMemList.InsertColumn(0,_T(""),LVCFMT_CENTER,rect.Width()/2);		//插入两列
	m_confCtrl->m_confMemList.InsertColumn(1,_T(""),LVCFMT_LEFT,rect.Width()/4);
	m_confCtrl->m_confMemList.InsertColumn(2,_T(""),LVCFMT_CENTER,rect.Width()/4);


	m_confCtrl->RefreshAttendeeList();
	//::PostMessage(m_incomingCall->GetSafeHwnd(), WM_CALL_UPDATE_STATE, NULL, NULL);	
}


void CTE_IncomingCall::OnBnClickedBtnAtov()
{
	// TODO: 在此添加控件通知处理程序代码

	TE_UpdateCall(m_CallStateInfo.ulCallID,TE_E_CALL_TYPE_IPVIDEO);

	m_isCheckVedio=TRUE;
	m_isCheckAudio=FALSE;
	m_isVideo=TRUE;

    m_btnVideo.EnableWindow(TRUE);

	m_btnVtoa.EnableWindow(TRUE);
	m_btnVtoa.ShowWindow(SW_SHOW);

	m_btnAtov.EnableWindow(FALSE);
	m_btnAtov.ShowWindow(SW_HIDE);
}

void CTE_IncomingCall::OnBnClickedBtnVtoa()
{
	// TODO: 在此添加控件通知处理程序代码

	m_isCheckVedio=TRUE;
	m_isCheckAudio=FALSE;

	m_btnVideo.EnableWindow(FALSE);

	TE_UpdateCall(m_CallStateInfo.ulCallID,TE_E_CALL_TYPE_IPAUDIO);

	m_btnVtoa.EnableWindow(FALSE);
	m_btnVtoa.ShowWindow(SW_HIDE);

	m_btnAtov.EnableWindow(TRUE);
	m_btnAtov.ShowWindow(SW_SHOW);
}

void CTE_IncomingCall::OnBnClickedBtnDialPlate()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_dailCtrl)
	{
		m_dailCtrl = new CTE_DIAL_PLATE();
		m_dailCtrl->Create(IDD_DIALOG_DIAL);
	}



	CRect re;
	GetDlgItem(IDC_BTN_DIAL_PLATE)->GetWindowRect(&re);
	::SetWindowPos(m_dailCtrl->GetSafeHwnd(),NULL,re.BottomRight().x-140,re.BottomRight().y,0,0,SWP_NOSIZE | SWP_NOZORDER);



	m_dailCtrl->ShowWindow(SW_SHOWNORMAL);
	m_dailCtrl->SetForegroundWindow();
	m_dailCtrl->m_callId=m_CallStateInfo.ulCallID;


}


void CTE_IncomingCall::OnNMCustomdrawSliderVoiceout(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	TE_SetVolume(((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->GetPos(),TE_E_VOLUME_TYPE_SPEAK);
	if (((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEOUT))->GetPos()<=0)
	{
		TE_SetLocalSpeaker(m_CallStateInfo.ulCallID,1);
		m_isSpeakerMute = 1;
		m_bSpeaker.SetWindowTextA(_T("Speaker UnMute"));
	}
	else
	{
		TE_SetLocalSpeaker(m_CallStateInfo.ulCallID,0);
		m_isSpeakerMute = 0;
		m_bSpeaker.SetWindowTextA(_T("Speaker Mute"));
	}
	UpdateData(FALSE); 

	
	
	*pResult = 0;
}

void CTE_IncomingCall::OnNMCustomdrawSpeakerButton(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTE_IncomingCall::OnNMCustomdrawSliderVoicein(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	TE_SetVolume(((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->GetPos(),TE_E_VOLUME_TYPE_MIC);
	if (((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOICEIN))->GetPos()<=0)
	{
		TE_SetLocalMic(m_CallStateInfo.ulCallID,1);
		m_isMicMute = 1;
		m_bMIC.SetWindowTextA(_T("Mic UnMute"));
	}
	else
	{
		TE_SetLocalMic(m_CallStateInfo.ulCallID,0);
		m_isMicMute = 0;
		m_bMIC.SetWindowTextA(_T("Mic Mute"));
	}

	UpdateData(FALSE); 



	*pResult = 0;
}

void CTE_IncomingCall::OnBnClickedBtnVedioanswer()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret =0;
	// TODO: 
	ret = TE_AnswerVideoCall(m_CallStateInfo.ulCallID,0);
}

