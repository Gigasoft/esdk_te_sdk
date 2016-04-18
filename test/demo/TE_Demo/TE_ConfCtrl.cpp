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
// TE_ConfCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "TE_ConfCtrl.h"


// CTE_ConfCtrl �Ի���

IMPLEMENT_DYNAMIC(CTE_ConfCtrl, CDialog)

CTE_ConfCtrl::CTE_ConfCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CTE_ConfCtrl::IDD, pParent)
{
	m_applyChairmanDlg=NULL;
	m_inviteDlg=NULL;
	m_extendTime=NULL;
}

CTE_ConfCtrl::~CTE_ConfCtrl()
{
	if (m_applyChairmanDlg)
	{
		m_applyChairmanDlg->DestroyWindow();
	}
	m_applyChairmanDlg=NULL;

	if (m_inviteDlg)
	{
		m_inviteDlg->DestroyWindow();
	}
	m_inviteDlg=NULL;


	if (m_extendTime)
	{
		m_extendTime->DestroyWindow();
	}
	m_extendTime=NULL;
	
}

void CTE_ConfCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EXTEND_TIME, m_extendTimeBtn);
	DDX_Control(pDX, IDC_BTN_APPLY_CHAIRMAN, m_applyChairMan);
	DDX_Control(pDX, IDC_BTN_ADD_MEM, m_addMember);
	DDX_Control(pDX, IDC_LIST_JIONED_MEM, m_confMemList);
	DDX_Control(pDX, IDC_BTN_RELEASE_CHAIRMAN, m_releaseChairMan);
}


BEGIN_MESSAGE_MAP(CTE_ConfCtrl, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_JIONED_MEM, &CTE_ConfCtrl::OnNMRClickListJionedMem)
	ON_BN_CLICKED(IDC_BTN_EXTEND_TIME, &CTE_ConfCtrl::OnBnClickedBtnExtendTime)
	ON_BN_CLICKED(IDC_BTN_APPLY_CHAIRMAN, &CTE_ConfCtrl::OnBnClickedBtnApplyChairman)
	ON_MESSAGE(WM_CONF_FRESH_MEMLIST, &CTE_ConfCtrl::ToRefreshAttendeeList)
	ON_MESSAGE(WM_CONF_RELEASE_CHAIRMAN_RESULT, &CTE_ConfCtrl::ToReleaseChairmanRst)
	ON_MESSAGE(WM_CONF_APPLY_SUCCEED,&CTE_ConfCtrl::AfterApplySucceed)
	ON_MESSAGE(WM_CONF_EXTEND_TIME_REST,&CTE_ConfCtrl::ExtendTimeResult)
	ON_MESSAGE(WM_CONF_EXTEND_REMAIN_TIME,&CTE_ConfCtrl::ExtendTimeRemain)
	ON_MESSAGE(WM_CONF_BROADCAST_REST,&CTE_ConfCtrl::BroadcastResult)
	ON_MESSAGE(WM_CONF_WATCH_REST,&CTE_ConfCtrl::WatchResult)
	ON_BN_CLICKED(IDC_BTN_RELEASE_CHAIRMAN, &CTE_ConfCtrl::OnBnClickedBtnReleaseChairman)
	ON_BN_CLICKED(IDC_BTN_ADD_MEM, &CTE_ConfCtrl::OnBnClickedBtnAddMem)
	ON_COMMAND(ID_MENU_MUTE, &CTE_ConfCtrl::OnMenuMute)
	ON_COMMAND(32774, &CTE_ConfCtrl::OnMenuUnmute)
	ON_COMMAND(32775, &CTE_ConfCtrl::OnMenuApplyChairman)
	ON_COMMAND(32776, &CTE_ConfCtrl::OnMenuReleaseChairman)
	ON_COMMAND(32777, &CTE_ConfCtrl::OnMenuBroadcast)
	ON_COMMAND(ID_MENU_STOP_BROADCAST, &CTE_ConfCtrl::OnMenuStopBroadcast)
	ON_COMMAND(32780, &CTE_ConfCtrl::OnMenuCallupHall)
	ON_COMMAND(32781, &CTE_ConfCtrl::OnMenuDeleteHall)
	ON_COMMAND(32782, &CTE_ConfCtrl::OnMenuHandup)
	ON_COMMAND(32783, &CTE_ConfCtrl::OnMenuWatch)
END_MESSAGE_MAP()


// CTE_ConfCtrl ��Ϣ�������

void CTE_ConfCtrl::OnPaint()
{
	CDialog::OnPaint();
}

BOOL CTE_ConfCtrl::OnInitDialog()
{

	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_TIME)); // IDB_BITMAP_TESTΪ��ԴͼƬID  
	((CButton *)GetDlgItem(IDC_BTN_EXTEND_TIME))->SetBitmap(hBitmap); 

	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CHAIRMAN)); // IDB_BITMAP_TESTΪ��ԴͼƬID  
	((CButton *)GetDlgItem(IDC_BTN_APPLY_CHAIRMAN))->SetBitmap(hBitmap);  

	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CHAIRMAN1)); // IDB_BITMAP_TESTΪ��ԴͼƬID  
	((CButton *)GetDlgItem(IDC_BTN_RELEASE_CHAIRMAN))->SetBitmap(hBitmap);  

	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_ADD)); // IDB_BITMAP_TESTΪ��ԴͼƬID  
	((CButton *)GetDlgItem(IDC_BTN_ADD_MEM))->SetBitmap(hBitmap);  

	/*::SetWindowPos(m_LocalWindow.GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOREDRAW);
	::SetWindowPos(m_RemoteWindow.GetSafeHwnd(),HWND_BOTTOM,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);*/


	m_ToolTip.Create(this);//��������
	m_ToolTip.AddTool( GetDlgItem(IDC_BTN_EXTEND_TIME), "�ӳ�����ʱ��" ); 
	m_ToolTip.AddTool( GetDlgItem(IDC_BTN_APPLY_CHAIRMAN), "���������ϯ" ); 
	m_ToolTip.AddTool( GetDlgItem(IDC_BTN_RELEASE_CHAIRMAN), "�ͷŻ�����ϯ" ); 
	m_ToolTip.AddTool( GetDlgItem(IDC_BTN_ADD_MEM), "�������" ); 

	m_ToolTip.SetDelayTime(200);
	m_ToolTip.SetTipTextColor( RGB(0,0,0 ));//������ʾ������ɫ
	m_ToolTip.SetTipBkColor( RGB(255,255,255));//������ʾ������ɫ
	m_ToolTip.Activate(TRUE);


	//����ͼ������
	myimage.Create(11,11,ILC_COLOR4,6,5);			//myimage������listctrlDlg.H������
	bitmapMuti.LoadBitmap(IDB_BITMAP_MUTI);
	bitmapUnmute.LoadBitmap(IDB_BITMAP_UNMUTE);
	bitmapMute.LoadBitmap(IDB_BITMAP_MUTE);
	bitmapMan.LoadBitmap(IDB_BITMAP_CHAIRMAN);
	bitmapOut.LoadBitmap(IDB_BITMAP_OUT);
	bitmapBroad.LoadBitmap(IDB_BITMAP_BROADCAST);

	myimage.Add(&bitmapMuti,RGB(0,0,0));
	myimage.Add(&bitmapUnmute,RGB(0,0,0));
	myimage.Add(&bitmapMute,RGB(0,0,0));
	myimage.Add(&bitmapMan,RGB(0,0,0));
	myimage.Add(&bitmapOut,RGB(0,0,0));
	myimage.Add(&bitmapBroad,RGB(0,0,0));


	//m_testlist.SetExtendedStyle(m_confMemList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);	

	//�����б�ؼ�LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
	//m_confMemList.SetExtendedStyle(m_confMemList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);	
	
	
	//m_confMemList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
	//m_confMemList.SetImageList(&myimage,LVSIL_SMALL);	//����ͼ������

	//CRect rect;   

	//m_confMemList.GetClientRect(&rect);  
	//m_confMemList.InsertColumn(0,_T(""),LVCFMT_CENTER,rect.Width()/2);		//��������
	//m_confMemList.InsertColumn(1,_T(""),LVCFMT_LEFT,rect.Width()/4);
	//m_confMemList.InsertColumn(2,_T(""),LVCFMT_CENTER,rect.Width()/4);



	//RefreshAttendeeList();

	CDialog::OnInitDialog();
	//::SetWindowPos(m_LocalWindow.GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);
	return TRUE;  // return TRUE unless you set the focus to a control
}

BOOL CTE_ConfCtrl::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
		m_ToolTip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}
void CTE_ConfCtrl::OnNMRClickListJionedMem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	POSITION pos = m_confMemList.GetFirstSelectedItemPosition();//���б���ͼ�ؼ��л�ȡ��һ��ѡ�����λ�� 
	curHall=(int)pos;
	curHall--;
	if (pos!=NULL)
	{  
		CMenu popMenu;
		popMenu.LoadMenu(IDR_MENU_POPUP);		//����˵�
		CMenu *pPopup;
		pPopup=popMenu.GetSubMenu(0);	//����Ӳ˵�ָ��

		//pPopup->EnableMenuItem(ID_1,MF_BYCOMMAND|MF_ENABLED);	//����˵���ʹ��
		//pPopup->EnableMenuItem(ID_2,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);	//������˵���ʹ��

		//pPopup->RemoveMenu(ID_MENU_APPLY,MF_BYCOMMAND);
		if (localHall.isChairMan_)
		{
			if (curHall==0)
			{
				if (_confHallList.list[0].isBroadcast_)
				{
					pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_APPLY,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_RELEASE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_BROADCAST,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_CALLUP,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_DELETE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_HANDUP,MF_BYCOMMAND);

				} 
				else
				{
					pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_APPLY,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_RELEASE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_STOP_BROADCAST,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_CALLUP,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_DELETE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_HANDUP,MF_BYCOMMAND);
				}
				
			}
			else
			{	
				if (_confHallList.list[curHall].M_ == localHall.M_ && _confHallList.list[curHall].T_ == localHall.T_)
				{
					pPopup->RemoveMenu(ID_MENU_CALLUP,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_DELETE,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_HANDUP,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_APPLY,MF_BYCOMMAND);
					if(localHall.isBroadcast_)
					{
						pPopup->RemoveMenu(ID_MENU_BROADCAST,MF_BYCOMMAND);
					}
					else
					{
						pPopup->RemoveMenu(ID_MENU_STOP_BROADCAST,MF_BYCOMMAND);
					}
					if (localHall.isMute_)
					{
						pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
					} 
					else
					{
						pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
					}

				}
				else
				{
					
					pPopup->RemoveMenu(ID_MENU_APPLY,MF_BYCOMMAND);
					pPopup->RemoveMenu(ID_MENU_RELEASE,MF_BYCOMMAND);
					
					if (_confHallList.list[curHall].isJoined_)
					{
						if (_confHallList.list[curHall].isBroadcast_)
						{
							pPopup->RemoveMenu(ID_MENU_BROADCAST,MF_BYCOMMAND);
						} 
						else
						{
							pPopup->RemoveMenu(ID_MENU_STOP_BROADCAST,MF_BYCOMMAND);
						}
						if (_confHallList.list[curHall].isMute_)
						{
							pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
						} 
						else
						{
							pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
						}
						pPopup->RemoveMenu(ID_MENU_CALLUP,MF_BYCOMMAND);

					} 
					else
					{
						pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
						pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
						pPopup->RemoveMenu(ID_MENU_BROADCAST,MF_BYCOMMAND);
						pPopup->RemoveMenu(ID_MENU_STOP_BROADCAST,MF_BYCOMMAND);
						pPopup->RemoveMenu(ID_MENU_HANDUP,MF_BYCOMMAND);
						pPopup->RemoveMenu(ID_MENU_WATCH,MF_BYCOMMAND);
					}

				}

			}

		} 
		else
		{
			if (_confHallList.list[curHall].M_ == localHall.M_ && _confHallList.list[curHall].T_ == localHall.T_)
			{
				pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_RELEASE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_BROADCAST,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_STOP_BROADCAST,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_CALLUP,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_DELETE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_HANDUP,MF_BYCOMMAND);

			}
			else
			{
				pPopup->RemoveMenu(ID_MENU_MUTE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_UNMUTE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_APPLY,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_RELEASE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_BROADCAST,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_STOP_BROADCAST,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_CALLUP,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_DELETE,MF_BYCOMMAND);
				pPopup->RemoveMenu(ID_MENU_HANDUP,MF_BYCOMMAND);
			}
		}

		POINT pt = {0};  
		GetCursorPos(&pt);
		//ClientToScreen(&point);		//���ͻ�������ת������Ļ����
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);			//��ʾ�����˵�����������Ϊ(����ڲ˵����|�����Ҽ���x��y��this)
		pPopup->Detach();
		popMenu.DestroyMenu(); 
	}  
	UpdateData(FALSE);  

	*pResult = 0;
}


LRESULT CTE_ConfCtrl::AfterApplySucceed(WPARAM wParm, LPARAM Lparam)
{

	m_extendTimeBtn.EnableWindow(TRUE);
	m_addMember.EnableWindow(TRUE);

	m_releaseChairMan.ShowWindow(SW_SHOW);
	m_applyChairMan.ShowWindow(SW_HIDE);

	return 0L;
}

LRESULT CTE_ConfCtrl::ExtendTimeResult(WPARAM wParm, LPARAM Lparam)
{

	if (extendRest)
	{
		AfxMessageBox(_T("�ӳ�����ʱ��ɹ�"));
	} 
	else
	{
		AfxMessageBox(_T("�ӳ�����ʱ��ʧ��"));
	}
	return 0L;
}


LRESULT CTE_ConfCtrl::ExtendTimeRemain(WPARAM wParm, LPARAM Lparam)
{

	//���ʱ�仹ʣ��10�������ϲ���ʾ
	if (remainTime <= 10 )
	{
		if (NULL != m_extendTime)
		{
			m_extendTime->DestroyWindow();
			m_extendTime = NULL;
		}

		m_extendTime = new CTE_ExtendTime(this);
		m_extendTime->Create(CTE_ExtendTime::IDD, this);

		m_extendTime->m_timeList.ResetContent();

		m_extendTime->m_timeList.AddString(_T("0.5Сʱ"));

		m_extendTime->m_timeList.AddString(_T("1Сʱ"));

		m_extendTime->m_timeList.AddString(_T("1.5Сʱ"));

		m_extendTime->m_timeList.AddString(_T("2Сʱ"));

		m_extendTime->m_timeList.AddString(_T("3Сʱ"));

		m_extendTime->m_timeList.SetCurSel(0);
		m_extendTime->ShowWindow(SW_SHOW);
		m_extendTime->CenterWindow(this);
	}

	return 0L;
}


LRESULT CTE_ConfCtrl::BroadcastResult(WPARAM wParm, LPARAM Lparam)
{
	if (0 != broadcastRest)
	{
		AfxMessageBox(_T("�㲥�᳡ʧ��."));

	}
	else
	{
		RefreshAttendeeList();
	}

	return 0L;
}


LRESULT CTE_ConfCtrl::WatchResult(WPARAM wParm, LPARAM Lparam)
{
	if (0 != watchRest)
	{
		AfxMessageBox(_T("�ۿ��᳡ʧ��."));
		
	}
	else
	{
		RefreshAttendeeList();
	}

	return 0L;
}


LRESULT CTE_ConfCtrl::ToRefreshAttendeeList(WPARAM wParm, LPARAM Lparam)
{

	/*Sleep(2000);

	m_extendTimeBtn.EnableWindow(TRUE);
	m_addMember.EnableWindow(TRUE);

	m_releaseChairMan.ShowWindow(SW_SHOW);
	m_applyChairMan.ShowWindow(SW_HIDE);*/

	RefreshAttendeeList();
	
	return 0L;
}


LRESULT CTE_ConfCtrl::ToReleaseChairmanRst(WPARAM wParm, LPARAM Lparam)
{
	if (true == result)
	{
		AfxMessageBox(_T("��ϯȨ���ͷųɹ�."));
		m_extendTimeBtn.EnableWindow(FALSE);
		m_addMember.EnableWindow(FALSE);

		m_applyChairMan.ShowWindow(SW_SHOW);
		m_releaseChairMan.ShowWindow(SW_HIDE);

		RefreshAttendeeList();
	}
	else
	{
		AfxMessageBox(_T("��ϯȨ���ͷ�ʧ��."));
	}

	return 0L;
}


void CTE_ConfCtrl::RefreshAttendeeList()
{
	//TE_S_SITE_JIONEDLIST _confHallList;
	memset(&_confHallList, 0, sizeof(TE_S_SITE_JIONEDLIST));
	TE_GetConfMemberSites(&_confHallList);


	//TE_S_SITE_INFO localHall;
	memset(&localHall, 0, sizeof(TE_S_SITE_INFO));

	TE_GetLocalSite(&localHall);

	if (m_confMemList.GetItemCount()>0)
	{
		m_confMemList.DeleteAllItems();
	}
	
	
	/*bitmapMuti.LoadBitmap(IDB_BITMAP_MUTI);
	bitmapUnmute.LoadBitmap(IDB_BITMAP_UNMUTE);
	bitmapMute.LoadBitmap(IDB_BITMAP_MUTE);
	bitmapMan.LoadBitmap(IDB_BITMAP_CHAIRMAN);
	bitmapOut.LoadBitmap(IDB_BITMAP_OUT);
	bitmapBroad.LoadBitmap(IDB_BITMAP_BROADCAST);*/
	//CString cstr;
	//cstr.Format("��������ʧ��%s", result->_reason); 
	//m_confInfo.SetWindowText(_T(LPCSTR(cstr)));

	if (localHall.isChairMan_)
	{
		m_releaseChairMan.ShowWindow(TRUE);
		m_applyChairMan.ShowWindow(FALSE);
		for (int i=0;i<_confHallList.listCount;i++)
		{
			if (i==0)
			{
				m_confMemList.InsertItem(0,_T("�໭��"),0);			
			}
			else
			{
				if (_confHallList.list[i].M_ == localHall.M_ && _confHallList.list[i].T_ == localHall.T_)
				{
					CString cstr = _T("");
					cstr.Append(_confHallList.list[i].name_);
					cstr.Append(_T("(��ϯ,����)"));
					m_confMemList.InsertItem(i,_T(LPCSTR(cstr)),3);	
					if (_confHallList.list[i].isBroadcast_)
					{
						m_confMemList.SetItem(i, 1, LVIF_IMAGE, NULL, 5, LVIS_SELECTED,LVIS_SELECTED, 0);
					} 
					if (_confHallList.list[i].isMute_)
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 2, LVIS_SELECTED,LVIS_SELECTED, 0);
					}
					else
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 1, LVIS_SELECTED,LVIS_SELECTED, 0);
					}
				} 
				else
				{
					CString cstr = _T("");
					cstr.Append(_confHallList.list[i].name_);
					m_confMemList.InsertItem(i,_T(LPCSTR(cstr)),3);	
					if (_confHallList.list[i].isJoined_)
					{
						if (_confHallList.list[i].isBroadcast_)
						{
							m_confMemList.SetItem(i, 1, LVIF_IMAGE, NULL, 5, LVIS_SELECTED,LVIS_SELECTED, 0);
						} 
						if (_confHallList.list[i].isMute_)
						{
							m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 2, LVIS_SELECTED,LVIS_SELECTED, 0);
						}
						else
						{
							m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 1, LVIS_SELECTED,LVIS_SELECTED, 0);
						}
					} 
					else
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 4, LVIS_SELECTED,LVIS_SELECTED, 0);
					}

				}
			}

		}
	}
	else
	{
		for (int i=0;i<_confHallList.listCount;i++)
		{
			if (i==0)
			{
				m_confMemList.InsertItem(0,_T("�໭��"),0);			
			}
			else
			{
				if (_confHallList.list[i].M_ == localHall.M_ && _confHallList.list[i].T_ == localHall.T_)
				{
					CString cstr = _T("");
					cstr.Append(_confHallList.list[i].name_);
					cstr.Append(_T("(����)"));
					m_confMemList.InsertItem(i,_T(LPCSTR(cstr)),3);	
					if (_confHallList.list[i].isBroadcast_)
					{
						m_confMemList.SetItem(i, 1, LVIF_IMAGE, NULL, 5, LVIS_SELECTED,LVIS_SELECTED, 0);
					} 
					if (_confHallList.list[i].isMute_)
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 2, LVIS_SELECTED,LVIS_SELECTED, 0);
					}
					else
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 1, LVIS_SELECTED,LVIS_SELECTED, 0);
					}
				} 
				else
				{
					CString cstr = _T("");

					if (_confHallList.list[i].isChairMan_)
					{
						cstr.Append(_confHallList.list[i].name_);
						cstr.Append(_T("(��ϯ)"));
					} 
					else
					{
						cstr.Append(_confHallList.list[i].name_);
					}

					m_confMemList.InsertItem(i,_T(LPCSTR(cstr)),3);	
					if (_confHallList.list[i].isBroadcast_)
					{
						m_confMemList.SetItem(i, 1, LVIF_IMAGE, NULL, 5, LVIS_SELECTED,LVIS_SELECTED, 0);
					} 
					if (_confHallList.list[i].isMute_)
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 2, LVIS_SELECTED,LVIS_SELECTED, 0);
					}
					else
					{
						m_confMemList.SetItem(i, 2, LVIF_IMAGE, NULL, 1, LVIS_SELECTED,LVIS_SELECTED, 0);
					}

				}
			}

		}
	}
	
	
}
void CTE_ConfCtrl::OnBnClickedBtnExtendTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL != m_extendTime)
	{
		m_extendTime->DestroyWindow();
		m_extendTime = NULL;
	}

	m_extendTime = new CTE_ExtendTime(this);
	m_extendTime->Create(CTE_ExtendTime::IDD, this);

	m_extendTime->m_timeList.ResetContent();

	m_extendTime->m_timeList.AddString(_T("0.5Сʱ"));

	m_extendTime->m_timeList.AddString(_T("1Сʱ"));

	m_extendTime->m_timeList.AddString(_T("1.5Сʱ"));

	m_extendTime->m_timeList.AddString(_T("2Сʱ"));

	m_extendTime->m_timeList.AddString(_T("3Сʱ"));

	m_extendTime->m_timeList.SetCurSel(0);
	m_extendTime->ShowWindow(SW_SHOW);
	m_extendTime->CenterWindow(this);
	
}

void CTE_ConfCtrl::OnBnClickedBtnApplyChairman()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (NULL != m_applyChairmanDlg)
	{
		m_applyChairmanDlg->DestroyWindow();
		m_applyChairmanDlg = NULL;
	}

	m_applyChairmanDlg = new ConfChairManApplyDlg(this);
	m_applyChairmanDlg->Create(ConfChairManApplyDlg::IDD, this);
	m_applyChairmanDlg->m_FromDlg=this;
	m_applyChairmanDlg->ShowWindow(SW_SHOW);
	m_applyChairmanDlg->CenterWindow(this);

	/*if(!m_applyChairmanDlg)
	{
		m_applyChairmanDlg = new ConfChairManApplyDlg();
		m_applyChairmanDlg->Create(IDD_DIALOG_APPLY_CHAIRMAN);
	}
	m_applyChairmanDlg->m_FromDlg=this;
	m_applyChairmanDlg->ShowWindow(SW_SHOWNORMAL);
	m_applyChairmanDlg->SetForegroundWindow();*/
}

void CTE_ConfCtrl::OnBnClickedBtnReleaseChairman()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(IDYES==::MessageBox(NULL,"ȷ���ͷ���ϯȨ�ޣ�","INFO",MB_YESNO)) 
	{
		TE_ReleaseConfChairman();
	}
}

void CTE_ConfCtrl::OnBnClickedBtnAddMem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL != m_inviteDlg)
	{
		m_inviteDlg->DestroyWindow();
		m_inviteDlg = NULL;
	}

	m_inviteDlg = new CTE_InviteJion(this);
	m_inviteDlg->Create(CTE_InviteJion::IDD, this);
	
	m_inviteDlg->m_memLists.ResetContent();
	///m_inviteDlg->m_memLists.SetCheckStyle(BS_CHECKBOX);
	/*m_inviteDlg->m_memLists.AddString(_T("01052417"));
	m_inviteDlg->m_memLists.AddString(_T("01052418"));
	m_inviteDlg->m_memLists.AddString(_T("01052419"));
	m_inviteDlg->m_memLists.AddString(_T("01052420"));*/
	m_inviteDlg->ShowWindow(SW_SHOW);
	m_inviteDlg->CenterWindow(this);
}

void CTE_ConfCtrl::OnMenuMute()
{
	// TODO: �ڴ���������������
	
	TE_MuteSite(&_confHallList.list[curHall]);
}

void CTE_ConfCtrl::OnMenuUnmute()
{
	// TODO: �ڴ���������������
	TE_UnMuteSite(&_confHallList.list[curHall]);
}

void CTE_ConfCtrl::OnMenuApplyChairman()
{
	// TODO: �ڴ���������������
	if (NULL != m_applyChairmanDlg)
	{
		m_applyChairmanDlg->DestroyWindow();
		m_applyChairmanDlg = NULL;
	}

	m_applyChairmanDlg = new ConfChairManApplyDlg(this);
	m_applyChairmanDlg->Create(ConfChairManApplyDlg::IDD, this);
	m_applyChairmanDlg->m_FromDlg=this;
	m_applyChairmanDlg->ShowWindow(SW_SHOW);
	m_applyChairmanDlg->CenterWindow(this);
}

void CTE_ConfCtrl::OnMenuReleaseChairman()
{
	// TODO: �ڴ���������������
	if(IDYES==::MessageBox(NULL,"ȷ���ͷ���ϯȨ�ޣ�","INFO",MB_YESNO)) 
	{
		TE_ReleaseConfChairman();
	}
}

void CTE_ConfCtrl::OnMenuBroadcast()
{
	// TODO: �ڴ���������������
	TE_BroadCastSite(&_confHallList.list[curHall]);
}

void CTE_ConfCtrl::OnMenuStopBroadcast()
{
	// TODO: �ڴ���������������
	TE_UnBroadCastSite(&_confHallList.list[curHall]);
}

void CTE_ConfCtrl::OnMenuCallupHall()
{
	// TODO: �ڴ���������������
	TE_CallSiteToConf(&_confHallList.list[curHall]);
}

void CTE_ConfCtrl::OnMenuDeleteHall()
{
	// TODO: �ڴ���������������
	TE_DeleteSite(&_confHallList.list[curHall]);
}

void CTE_ConfCtrl::OnMenuHandup()
{
	// TODO: �ڴ���������������
	TE_HandUpSite(&_confHallList.list[curHall]);
}


void CTE_ConfCtrl::OnMenuWatch()
{
	// TODO: �ڴ���������������
	TE_WatchSite(&_confHallList.list[curHall]);
}
