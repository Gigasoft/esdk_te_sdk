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
#include "stdafx.h"
#include "TE_Sheet.h"
// CTEX0_Sheet

IMPLEMENT_DYNAMIC(CTE_Sheet, CPropertySheet)

CTE_Sheet::CTE_Sheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{


	AddPage(&m_callPage);
	m_callPage.SetSheet(this);
	m_callPage.m_psp.dwFlags |= PSP_USETITLE;
	m_callPage.m_psp.pszTitle = "Call";

}

CTE_Sheet::CTE_Sheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	
	AddPage(&m_callPage);

	m_callPage.SetSheet(this);

	m_callPage.m_psp.dwFlags |= PSP_USETITLE;
	m_callPage.m_psp.pszTitle = "Call";

}

CTE_Sheet::~CTE_Sheet()
{
	TE_SDK_Logout();
}


BEGIN_MESSAGE_MAP(CTE_Sheet, CPropertySheet)
	ON_WM_NCCREATE()
END_MESSAGE_MAP()


// CTEX0_Sheet message handlers


BOOL CTE_Sheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	//��������ҳĬ�ϰ�ť
	//GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDOK,_T("�ǳ�"));
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);

	//���������С����Ĭ�ϰ�ť����
	CRect btnRect;
	GetDlgItem(IDOK)->GetWindowRect(&btnRect);
	CRect wndRect; 
	GetWindowRect(&wndRect);  
	::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, wndRect.Width(), wndRect.Height(), SWP_NOMOVE | SWP_NOZORDER); 

#if 0
	//��ʼ����
	StartMsgRetrieval();

	//����������ʾ����
	m_incomingCall = new CTEX0_IncomingCall();
	m_incomingCall->Create(IDD_DLG_INCOMING_CALL, this);
	m_checkConfCtrlPWD.Create(IDD_CHECK_CTRL_CONF_PWD_DIALOG, this);
#endif	
	return bResult;
}


BOOL CTE_Sheet::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!CPropertySheet::OnNcCreate(lpCreateStruct))
		return FALSE;

	// TODO:  Add your specialized creation code here
	//��ʾ��С����ť
	ModifyStyle(0, WS_SYSMENU | WS_MINIMIZEBOX, SWP_NOZORDER);

	return TRUE;
}

#if 0

unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TEX0_FAIL;
	}

	CTEX0_Sheet* instance = (CTEX0_Sheet*)para;
	instance->MainLoop();
	return TEX0_SUCCESS;
}


void CTEX0_Sheet::MainLoop()
{
	//int confType = 0;
	while (m_run)
	{
		vector<MsgStruct> msgStruct;
		int ret = keepAlive(m_conferencePage.m_terminalState, msgStruct);
		Sleep(600);
		if (TEX0_SUCCESS != ret)
		{
			continue;
		}


		if (NULL != m_statusPage.m_hWnd)
		{
			m_statusPage.OnStatusChange(m_conferencePage.m_terminalState);
		}

		for (unsigned int i=0; i<msgStruct.size(); ++i)
		{
			TRACE("%s\n", msgStruct[i].msgName.c_str());
			if ("MSG_REJECT_CALL" == msgStruct[i].msgName)
			{
				if (NULL != m_incomingCall && m_incomingCall->IsWindowVisible())
				{
					//�����ѱ������û��ܾ����������紦����
					m_incomingCall->ShowWindow(SW_HIDE);
					SetWindowText("�����ѱ������û��ܾ�");
				}
			}

			if ("MSG_CALL_RSP" == msgStruct[i].msgName)
			{
				Json::Value data;
				Json::Reader reader;
				if (!reader.parse(msgStruct[i].msgData, data) || data["result"].isNull() || data["siteNum"].isNull())
				{
					continue;
				}
				int ret = data["result"].asInt();
				int siteNum = data["siteNum"].asInt();
				if (0 != ret)
				{
					CString msg;
					msg.Format("����ʧ��: %d", ret);
					SetWindowText(msg);
				}
				else
				{
					CString msg;
					msg.Format("���гɹ�", ret);
					SetWindowText(msg);
					m_confType = m_conferencePage.m_terminalState.confType;
				}
				if (NULL != m_callPage.m_hWnd)
				{
					m_callPage.SetCallHandle(siteNum);
				}
				if (NULL != m_incomingCall && m_incomingCall->IsWindowVisible())
				{
					//�����ѱ������û��������������紦����
					m_incomingCall->ShowWindow(SW_HIDE);
					SetWindowText("�����ѱ������û�����");
				}
			}

			if ("MSG_START_CALL" == msgStruct[i].msgName)
			{
				Json::Value data;
				Json::Reader reader;
				if (!reader.parse(msgStruct[i].msgData, data) || data["siteNum"].isNull() || data["siteText"].isNull() || data["callDir"].isNull())
				{
					continue;
				}
				if (1 == data["callDir"].asInt())
				{
					continue;//���� ������
				}
				int siteNum = data["siteNum"].asInt();
				CString siteText;
				siteText.Format(_T("�û� [%s] ���б��ˣ��Ƿ������"), data["siteText"].asString().c_str());
				if (NULL != m_incomingCall)
				{
					//��ʾ������ʾ����
					m_incomingCall->SetCallInfo(siteNum, siteText);
					m_incomingCall->ShowWindow(SW_SHOW);
					m_incomingCall->SetForegroundWindow();
				}
			}

			if ("MSG_DEL_SITE_RSP" == msgStruct[i].msgName)
			{
				if (msgStruct[i].param1 == 0)
				{
					SetWindowText("�ɹ�ɾ���᳡");
					m_conferencePage.UpdateSiteList();
				}
				else if (msgStruct[i].param1 == 1)
				{
					CString err_msg;
					err_msg.Format("ɾ���᳡ʧ��, ʧ��ԭ��:%d",msgStruct[i].param2);
					SetWindowText(err_msg);
				}
			}

			if ("MSG_SITECALL_RSP" == msgStruct[i].msgName)
			{
				if (msgStruct[i].param1 != 0)
				{
					CString err_msg;
					err_msg.Format("����ʧ��, ʧ��ԭ��:%d",msgStruct[i].param1);
					SetWindowText(err_msg);
				}
				else
				{
					Json::Value data;
					Json::Reader reader;
					if (!reader.parse(msgStruct[i].msgData, data) || data["result"].isNull() 
						|| data["siteNum"].isNull() || data["resID"].isNull())
					{
						continue;
					}
					if (0 != data["result"].asInt())
					{
						CString err_msg;
						err_msg.Format("����ʧ��, ʧ��ԭ��:%d",data["resID"].asInt());
						SetWindowText(err_msg);
						continue;//���� ������
					}
					else
					{
						CString succ_msg;
						succ_msg.Format("�ټ��ɹ�");
						SetWindowText(succ_msg);
						m_confType = m_conferencePage.m_terminalState.confType;
						m_conferencePage.UpdateSiteList();
						//m_conferencePage.OnBnClickedQuerySiteLit();
						continue;//���� ������
					}
				}
			}

			if ("MSG_CONFCTRL_PWD_INPUT_CMD" == msgStruct[i].msgName)
			{
				m_checkConfCtrlPWD.ShowWindow(SW_SHOW);
				m_checkConfCtrlPWD.SetForegroundWindow();
			}

			if ("MSG_FREE_CHAIR_RSP" == msgStruct[i].msgName)
			{
				CString msg;
				if (msgStruct[i].param1 != 0)
				{
					msg.Format("�ͷ���ϯʧ��");
				}else
				{
					msg.Format("�ͷ���ϯ�ɹ�");
					m_conferencePage.UpdateSiteList();
				}
				SetWindowText(msg);
				continue;
			}

			if ("MSG_APPLY_CHAIR_RSP" == msgStruct[i].msgName)
			{
				CString msg;
				if (msgStruct[i].param1 != 0)
				{
					msg.Format("������ϯʧ��");
				}else
				{
					msg.Format("������ϯ�ɹ�");
					m_conferencePage.UpdateSiteList();
				}
				SetWindowText(msg);
				continue;
			}
			
			if ("MSG_END_CONF_RSP" == msgStruct[i].msgName)
			{
				CString msg;
				if (msgStruct[i].param1 != 0)
				{
					switch(m_confType)
					{
						case 0:
						{
							msg.Format("�޺���");
							break;
						}
						case 1:
						{
							msg.Format("��Ե���н���ʧ��");
							m_callPage.setHangupState(0);
							break;
						}
						case 2:
						{
							if (m_callPage.getHangupState())
							{
								msg.Format("�˳�Զ�˶�����ʧ��");
								m_callPage.setHangupState(0);
							}
							else
							{
								msg.Format("Զ�˶��������ʧ��");
							}
							
							break;
						}
						case 3:
						{
							if (m_callPage.getHangupState())
							{
								msg.Format("�˳����ض�����ʧ��");
								m_callPage.setHangupState(0);
							}
							else
							{
								msg.Format("���ض��������ʧ��");
							}
							
							break;
						}
						case 4:
						{
							if (m_callPage.getHangupState())
							{
								msg.Format("�˳������������ʧ��");
								m_callPage.setHangupState(0);
							}
							else
							{
								msg.Format("��������������ʧ��");
							}
							
							break;
						}
						default:
						{
							msg.Format("�쳣 confType:%d",m_confType);
							break;
						}	
					}
					
				}else
				{
					switch(m_confType)
					{
					case 0:
						{
							msg.Format("�޺���");
							break;
						}
					case 1:
						{
							msg.Format("��Ե���н����ɹ�");
							m_callPage.setHangupState(0);
							break;
						}
					case 2:
						{
							if (m_callPage.getHangupState())
							{
								msg.Format("�˳�Զ�˶�����ɹ�");
								m_callPage.setHangupState(0);
							}else{
								msg.Format("Զ�˶���������ɹ�");
							}

							
							break;
						}
					case 3:
						{
							if (m_callPage.getHangupState())
							{
								msg.Format("�˳����ض�����ɹ�");
								m_callPage.setHangupState(0);
							}else{
								msg.Format("���ض���������ɹ�");
							}
							
							break;
						}
					case 4:
						{
							if (m_callPage.getHangupState())
							{
								msg.Format("�˳������������ɹ�");
								m_callPage.setHangupState(0);
							}else{
								msg.Format("���������������ɹ�");
							}
							break;
						}
					default:
						{
							msg.Format("�쳣 confType:%d",m_confType);
							break;
						}	
					}
					m_conferencePage.ClearSiteList();
					
				}
				SetWindowText(msg);
				continue;
			}
			if ("MSG_ADD_SITE_RSP" == msgStruct[i].msgName)
			{
				CString msg;
				if (msgStruct[i].param1 != 0)
				{
					msg.Format("��ӻ���ʧ��");

				}else
				{
					msg.Format("��ӻ���ɹ�");
					m_conferencePage.UpdateSiteList();
				}
				SetWindowText(msg);
				continue;
			}
			
			if ("MSG_AUXVIDEO_SEND_RESULT" == msgStruct[i].msgName)
			{
				CString msg;
				if (msgStruct[i].param1 != 1)
				{
					msg.Format("���͸���ʧ��");

				}else
				{
					msg.Format("���͸����ɹ�");
				}
				SetWindowText(msg);
				continue;
			}
		}
	}
}


void CTEX0_Sheet::StartMsgRetrieval()
{
	if (NULL == m_thread)
	{
		m_run = true;
		m_thread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
	}
}


void CTEX0_Sheet::StopMsgRetrieval()
{
	if (NULL == m_thread)
	{
		return;
	}

	m_run = false;
	WaitForSingleObject(m_thread, INFINITE);
	m_thread = NULL;
}


void CTEX0_Sheet::OpenAddressBook(vector<SiteAddrRecord> &selSiteAddress)
{
	CTEX0_AddrBook addressBook;
	INT_PTR response = addressBook.DoModal();
	if (response == IDOK)
	{
		addressBook.GetSelAddrRecord(selSiteAddress);
	}
}

#endif
