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
#include "TE_Contact.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"
#include "TE_IncomingCall.h"
#include "CApplication0.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"

IMPLEMENT_DYNAMIC(CTE_Contact,CDialog)

CTE_Contact::CTE_Contact(CWnd* pParent /*NULL*/)
:CDialog(CTE_Contact::IDD,pParent)
, m_searchcontact(_T(""))
{
	m_PcontactInfo = NULL;
	m_group = NULL;
	m_renamegroup = NULL;
	m_Nickname = NULL;
	memset(&m_contactinfo, 0, sizeof(TE_S_CONTACT_INFO));
	memset(m_ID, 0x00, sizeof(char) * 1000000);
	num = 0;
	contacttype = 0;
	Initnum= 0;
	SetFlagContact =0;
	m_incomingCall = NULL;
	m_hItemContact = NULL;
	m_Import = NULL;
	m_export=NULL;
	m_imortContact = NULL;
	m_parent =  (CTE_DemoDlg *)pParent;
	m_menuflag = 0;
}

CTE_Contact::~CTE_Contact()
{
	delete m_PcontactInfo;
	m_PcontactInfo = NULL;
	delete m_incomingCall;
	m_incomingCall = NULL;
	delete m_group;
	m_group = NULL;
	delete m_renamegroup;
	m_renamegroup =NULL;
	delete m_Nickname;
	m_Nickname =NULL;
	delete m_Import;
	m_Import =NULL;
	delete m_export;
	m_export = NULL;
	delete m_imortContact;
	m_imortContact = NULL;
}

void CTE_Contact::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_searchcontact);
	//DDX_Control(pDX, IDC_CHECK1, m_ContactVideo);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CTE_Contact,CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CTE_Contact::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON1, &CTE_Contact::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &CTE_Contact::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CTE_Contact::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON4, &CTE_Contact::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON6, &CTE_Contact::OnBnClickedButton6)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CTE_Contact::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CTE_Contact::OnNMRClickListContactMenu)
	//ON_COMMAND(32784, &CTE_Contact::OnMenuAddContact)
	//ON_COMMAND(32787,&CTE_Contact::OnMenuImport)
	//ON_COMMAND(32788,&CTE_Contact::OnMenuExportGroup)
	//ON_COMMAND(32789, &CTE_Contact::OnMenuAddGroup)
	//ON_COMMAND(32791,&CTE_Contact::OnMenuAddGroup)
	//ON_COMMAND(32792,&CTE_Contact::OnMenuRenameGroup)
	//ON_COMMAND(32793,&CTE_Contact::OnMenudeleteGroup)
	//ON_COMMAND(32794,&CTE_Contact::OnMenuVideoCall)
	//ON_COMMAND(32795,&CTE_Contact::OnMenuAudioCall)
	//ON_COMMAND(32796,&CTE_Contact::OnMenuSetNickName)
	//ON_COMMAND(32798,&CTE_Contact::OnMenuEditContact)
	//ON_COMMAND(32799,&CTE_Contact::OnMenuDeleteContact)
	//ON_COMMAND(32800,&CTE_Contact::OnMenuAddContact)
	//ON_COMMAND(32801,&CTE_Contact::OnMenuImport)
	//ON_COMMAND(32802,&CTE_Contact::OnMenuExportGroup)
	//ON_COMMAND(32803,&CTE_Contact::OnMenuAddGroup)
	//ON_COMMAND(32804,&CTE_Contact::OnMenuAddContact)
	//ON_COMMAND(32805,&CTE_Contact::OnMenuAddContact)
	//ON_COMMAND(32806,&CTE_Contact::OnMenuImport)
	//ON_COMMAND(32807,&CTE_Contact::OnMenuExportGroup)
	//ON_COMMAND(32808,&CTE_Contact::OnMenuImport)
	//ON_COMMAND(32809,&CTE_Contact::OnMenuExportGroup)
	//ON_COMMAND(32810,&CTE_Contact::OnMenuCopyContactToGroup)
	//ON_COMMAND(32811,&CTE_Contact::OnMoveContactToGroup)
	//ON_COMMAND(32814,&CTE_Contact::OnMenuSetNickName)

	
	
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CTE_Contact::OnClickMessage)
END_MESSAGE_MAP()



BOOL CTE_Contact::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!m_PcontactInfo)
	{
		m_PcontactInfo = new CTE_ContactInfo(m_parent);
		if(m_PcontactInfo)
		{
			m_PcontactInfo->Create(IDD_DIALOG_CONTACTINFO);
		}
	}
	m_PcontactInfo->m_info = this;
	if (!m_group)
	{
		m_group = new CTE_Group(m_parent);
		if(m_group)
		{
			m_group->Create(IDD_DIALOG_GROUP);
		}
	}
	m_group->m_contactdlg = this;

	if (!m_imortContact)
	{
		m_imortContact = new CTE_ImportContact(m_parent);
		if(m_imortContact)
		{
			m_imortContact->Create(IDD_DIALOG_IMPORT);
		}
	}
	m_imortContact->m_contacts_ = this;

	if (!m_renamegroup)
	{
		m_renamegroup = new CTE_RenameGroup(this);
		if(m_renamegroup)
		{
			m_renamegroup->Create(IDD_DIALOG_RenameGroup);
		}
	}
	if (!m_Nickname)
	{
		m_Nickname = new CTE_Nickname(this);
		if(m_Nickname)
		{
			m_Nickname->Create(IDD_DIALOG_NICKNAME);
		}
	}
	if (!m_Import)
	{
		m_Import = new CTE_ImportAddr(m_parent);
		if(m_Import)
		{
			m_Import->Create(IDD_DIALOG_IMPORTFILE);
			if(m_imortContact)
			{
				m_Import->m_pContactDlg = m_imortContact;
			}	
		}
	}
	if (!m_export)
	{
		m_export = new CTE_ExportGroup();
		if(m_export)
		{
			m_export->Create(IDD_DIALOG_EXPORTGROUP);
		}
	}
	return TRUE;
}

void CTE_Contact::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}



void CTE_Contact::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetForegroundWindow();
	ShowWindow(SW_HIDE);
	CDialog::OnClose();
}


void CTE_Contact::OnMenuImport()
{
	if (!m_Import)
	{
		m_Import = new CTE_ImportAddr(m_parent);
		if(m_Import)
		{
			m_Import->Create(IDD_DIALOG_IMPORTFILE);
		}
	}

	m_Import->ShowWindow(SW_SHOWNORMAL);
}

void CTE_Contact::ClickMessage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (!m_PcontactInfo)
	{
		m_PcontactInfo = new CTE_ContactInfo(m_parent);
		if(m_PcontactInfo)
		{
			m_PcontactInfo->Create(IDD_DIALOG_CONTACTINFO);
		}
	}
	m_PcontactInfo->ShowWindow(SW_HIDE);
	int len = 0;
	if(pNMListView->iItem!=-1)
	{
		num = pNMListView->iItem;
		len = m_PcontactInfo->m_ContactName.GetLength();
		strncpy(m_contactinfo.name ,m_PcontactInfo->m_ContactName.GetBuffer(len),len);
		len = m_PcontactInfo->m_ContactNumber.GetLength();
		//m_contactinfo.id = m_list.GetItemText(num,8);
//	strncpy(m_contactinfo.id ,m_ID[m_PcontactInfo->m_iLogItem -1],50);
	}
	*pResult = 0;
}



void CTE_Contact::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int len = 0,ret = 0,i=0;
	char searchkey[512]={0};
	TE_S_CONTACTS_INFO m_getContact;
	std::wstring cstrName;
	m_getContact.contact = NULL;
	m_getContact.num = 0;
	UpdateData(TRUE);
	len = m_searchcontact.GetLength();
	strncpy(searchkey ,m_searchcontact.GetBuffer(len),len);
	ret = TE_SearchContact(searchkey,&m_getContact);
	if(ret == 0)
	{
		m_tree.DeleteAllItems();//删除所有节点
		m_hItemContact = m_tree.InsertItem("通讯录");//添加根节点
		for(i=0;i<m_getContact.num;i++)
		{
			TVINSERTSTRUCT tvStruct;
			tvStruct.hParent = m_hItemContact;
			tvStruct.hInsertAfter = NULL;
			tvStruct.item.mask = TVIF_TEXT|TVIF_PARAM;

			/*CString strTmp;
			cstrName = m_parent->Utf82Unicode(m_getContact.contact[i].name);
			strTmp.Format("%s", m_parent->WSToString(cstrName).c_str());*/

			tvStruct.item.pszText = m_getContact.contact[i].name;
			/*strTmp.ReleaseBuffer();*/
			HTREEITEM hItemSub = m_tree.InsertItem(&tvStruct);
			m_tree.SetItemData(hItemSub, (DWORD_PTR)(m_getContact.contact[i].name));
		}	
		m_tree.Expand(m_hItemContact, TVE_EXPAND);
	}
	TE_FreeMemory(m_getContact.contact);
}


void CTE_Contact::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	CString str;
	// TODO: 在此添加控件通知处理程序代码

	CString  CurrentVideo = m_tree.GetItemText(m_tree.GetSelectedItem());

	m_contactName = CurrentVideo;
	m_renamegroup->m_reName= CurrentVideo;

	HTREEITEM hItem = m_tree.GetSelectedItem();//得到你选中的节点（单击的节点）
	// Expand the parent, if possible.
	HTREEITEM hParent = m_tree.GetParentItem(hItem );
	if (hParent != NULL) 
	{
		str.Format(_T("%s"),(LPCTSTR)m_tree.GetItemText(hParent ));
	}
	m_groupName = str;
	*pResult = 0;

}
void CTE_Contact::OnNMRClickListContactMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int i=0;
	TE_S_GROUPS_INFO  m_getGroup;
//	TE_S_GROUP_INFO m_groups;
	TE_S_CONTACTS_INFO  m_getContact;
//	TE_S_CONTACT_INFO contact;
	std::wstring cstrName;
	std::string m_Name;
	CMenu m,*pm;
	TE_CHAR ContactName[512]={0};
	m_getContact.contact = NULL;
	m_getGroup.groupInfo = NULL;
	m_getContact.num = 0;
	m_getGroup.num = 0;
	TE_E_USEKEY_SORT_RULE sortRule = group_status_first;
	if(!m.LoadMenu(IDR_MENU_CONTACT))
	{
		MessageBox(_T("error"));
	}
	if(!strcmp(m_contactName.c_str() ,"通讯录"))
	{
		pm = m.GetSubMenu(0);
		CPoint pot;
		GetCursorPos(&pot);
		pm->TrackPopupMenu(TPM_LEFTALIGN,pot.x,pot.y,this);
	}
	
	POINT pos ;
	if(!GetCursorPos(&pos))
		return ;
	m_tree.ScreenToClient(&pos);
	UINT uFlags;
	HTREEITEM hItem = m_tree.HitTest(pos, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		m_tree.Select(hItem, TVGN_CARET);
	}
	strncpy(ContactName ,m_contactName.c_str(),65);
	// 显示菜单
	int ret = TE_GetCustomGroupList(&m_getGroup);
	if(ret ==0)
	{
		for(i=0;i<m_getGroup.num;i++)
		{
			//cstrName = m_parent->Utf82Unicode(m_getGroup.group[i].name);
			if(!strcmp(m_contactName.c_str(),m_getGroup.groupInfo[i].groupName))
			{
				if(!strcmp("recent  contact" ,m_getGroup.groupInfo[i].groupName))
				{
					continue;
				}
				if(!strcmp("default group" ,m_getGroup.groupInfo[i].groupName))
				{
					pm = m.GetSubMenu(3);
					CPoint pot;
					GetCursorPos(&pot);
					m_tree.ScreenToClient(&pot);
					HTREEITEM hItem = m_tree.GetSelectedItem();
					if(hItem)
					{
						int nIndex = 1;
						while(NULL != (hItem = m_tree.GetParentItem(hItem)))
						{
							nIndex++;
						}
						if(nIndex!= 2)
						{
							continue;
						}
					}
					GetCursorPos(&pot);
					pm->TrackPopupMenu(TPM_LEFTALIGN,pot.x,pot.y,this);
					continue;
				}
					pm = m.GetSubMenu(1);
					CPoint pot;
					GetCursorPos(&pot);
					m_tree.ScreenToClient(&pot);
					HTREEITEM hItem = m_tree.GetSelectedItem();
					if(hItem)
					{
						int nIndex = 1;
						while(NULL != (hItem = m_tree.GetParentItem(hItem)))
						{
							nIndex++;
						}
						if(nIndex!= 2)
						{
							continue;
						}
					}
					GetCursorPos(&pot);
					pm->TrackPopupMenu(TPM_LEFTALIGN,pot.x,pot.y,this);
		     }
		  }
    	}
	int len = TE_GetContactList(sortRule,&m_getContact);
	if(0 == len)
	{
		for(i=0;i<m_getContact.num;i++)
		{
			//cstrName = m_parent->Utf82Unicode(m_getContact.contact[i].name);
			if(!strcmp(m_contactName.c_str(),m_getContact.contact[i].name))
			{
				pm = m.GetSubMenu(2);
				CPoint pot;
				GetCursorPos(&pot);
				m_tree.ScreenToClient(&pot);
				HTREEITEM hItem = m_tree.GetSelectedItem();
				if(hItem)
				{
					int nIndex = 1;
					while(NULL != (hItem = m_tree.GetParentItem(hItem)))
					{
						nIndex++;
					}
					if(nIndex!= 3)
					{
						continue;
					}
				}
				GetCursorPos(&pot);
				pm->TrackPopupMenu(TPM_LEFTALIGN,pot.x,pot.y,this);
			}
		}
	}
	TE_FreeMemory(m_getContact.contact);
	TE_FreeMemory(m_getGroup.groupInfo);
}

void CTE_Contact::OnMenuAddContact()
{
	int ret =0,i=0,x=0;
	TE_UINT32 num = 0;
	TE_S_GROUPS_INFO getGroup;
	std::wstring cstrName;
	std::string groupName = "recent  contact";
	getGroup.groupInfo = NULL;
	getGroup.num = 0;
	ret = TE_GetCustomGroupList(&getGroup);
	m_PcontactInfo->m_ComboGroup.ResetContent();
	for(i=0;i<getGroup.num;i++)
	{
		if(!strcmp("recent  contact" ,getGroup.groupInfo[i].groupName))
		{
			continue;
		}
	//	cstrName = m_parent->Utf82Unicode(getGroup.group[i].name);
		m_PcontactInfo->m_ComboGroup.InsertString(x,getGroup.groupInfo[i].groupName);//添加第i个值
		m_PcontactInfo->m_ComboGroup.SetCurSel(0);
		x++;
	}
	contacttype = 0;
	if (!m_PcontactInfo)
	{
		m_PcontactInfo = new CTE_ContactInfo(m_parent);
		if(m_PcontactInfo)
		{
			m_PcontactInfo->Create(IDD_DIALOG_CONTACTINFO);
		}
	}
	m_PcontactInfo->m_ContactAddress.Format("");
	m_PcontactInfo->m_ContactDepartment.Format("");
	m_PcontactInfo->m_ContactEmail.Format("");
	m_PcontactInfo->m_ContactMobilephone.Format("");
	m_PcontactInfo->m_ContactName.Format("");
	m_PcontactInfo->m_ContactNumber.Format("");
	m_PcontactInfo->m_ContactOfficephone.Format("");
	m_PcontactInfo->m_NickName.Format("");
	m_PcontactInfo->UpdateData(FALSE);
	m_PcontactInfo->ShowWindow(SW_SHOWNORMAL);
	TE_FreeMemory(getGroup.groupInfo);
}

void CTE_Contact::OnMenuAddGroup()
{
	if (!m_group)
	{
		m_group = new CTE_Group(m_parent);
		if(m_group)
		{
			m_group->Create(IDD_DIALOG_GROUP);
		}
	}

	m_group->ShowWindow(SW_SHOWNORMAL);
}	

void CTE_Contact::OnMenudeleteGroup()
{
	int ret = 0,i =0;
	TE_UINT32 num = 0;
	TE_S_GROUPS_INFO getGroup;
	std::wstring cstrName;
	getGroup.groupInfo = NULL;
	getGroup.num = 0;
	ret = TE_GetCustomGroupList(&getGroup);
	if(0 == ret)
	{
		for(i=0;i<getGroup.num;i++)
		{
			//cstrName = m_parent->Utf82Unicode(getGroup.group[i].name);
			if(!strcmp(getGroup.groupInfo[i].groupName ,m_contactName.c_str()))
			{
				if(MessageBox( "Are you sure delete this group?" ,"system hint" , MB_ICONINFORMATION|MB_YESNO)==IDYES)
				{
					ret = TE_RemoveCustomGroup(getGroup.groupInfo[i].groupName);
					if(0 == ret)
					{
						AfxMessageBox(_T("delete this GROUP success"));
						OnUpdateRecordList();
					}
				}
				else
				{
					AfxMessageBox(_T("delete this group failed"));
				}
			}
		}
	}
	TE_FreeMemory(getGroup.groupInfo);
}

void CTE_Contact::OnMenuRenameGroup()
{
	if (!m_renamegroup)
	{
		m_renamegroup = new CTE_RenameGroup(this);
		if(m_renamegroup)
		{
			m_renamegroup->Create(IDD_DIALOG_RenameGroup);
		}
	}
	m_renamegroup->ShowWindow(SW_SHOWNORMAL);
}

void CTE_Contact::OnMenuVideoCall()
{
	CString msg;
	TE_S_CONTACT_INFO contact;
	TE_CHAR m_contact[512]={0};
	strncpy(m_contact,m_contactName.c_str(),sizeof(m_contact));
	int ret = TE_GetContactByName(m_contact,&contact);
	{
		if(0 == ret)
		{
			if (m_parent)
			{
				m_parent->ContactVideoCall(contact.ucAcc);
			}
		}
	}
}

void CTE_Contact::OnMenuAudioCall()
{
	TE_S_CONTACT_INFO contact;
	TE_CHAR m_contact[512]={0};
	strncpy(m_contact,m_contactName.c_str(),65);
	int ret = TE_GetContactByName(m_contact,&contact);
	{
		if(0 == ret)
		{
			if (m_parent)
			{
				m_parent->ContactAudioCall(contact.ucAcc);
			}
		}
	}
}

void CTE_Contact::OnMenuSetNickName()
{
	if (!m_Nickname)
	{
		m_Nickname = new CTE_Nickname(this);
		if(m_Nickname)
		{
			m_Nickname->Create(IDD_DIALOG_NICKNAME);
		}
	}
	m_Nickname->ShowWindow(SW_SHOWNORMAL);
}

void CTE_Contact::OnMenuDeleteContact()
{
	int ret = 0;
	TE_CHAR contactName[512]={0};
	TE_CHAR groupName[TE_D_NAME_LEN] = {0};
	strncpy(contactName,m_contactName.c_str(),TE_D_NAME_LEN);
	strncpy(groupName,m_groupName.c_str(),TE_D_NAME_LEN);
	ret = TE_RemoveContact(contactName,groupName);
	if(TE_SDK_Success == ret)
	{
		AfxMessageBox("delete contact success");
		OnUpdateRecordList();
	}
	else
	{
		AfxMessageBox("delete contact failed");
	}
}

void CTE_Contact::OnMenuEditContact()
{
	int ret =0,i=0,x=0;
	TE_UINT32 num = 0;
	TE_S_GROUPS_INFO getGroup;
	TE_S_CONTACT_INFO contact;
	std::wstring cstrName;
	TE_CHAR contactName[512]={0};
	getGroup.groupInfo = NULL;
	getGroup.num = 0;
	ret = TE_GetCustomGroupList(&getGroup);
	m_PcontactInfo->m_ComboGroup.ResetContent();
	for(i=0;i<getGroup.num;i++)
	{
		if(!strcmp("recent  contact" ,getGroup.groupInfo[i].groupName))
		{
			continue;
		}
		m_PcontactInfo->m_ComboGroup.InsertString(x,getGroup.groupInfo[i].groupName);//添加第i个值
		m_PcontactInfo->m_ComboGroup.SetCurSel(0);
		x++;
	}
	contacttype = 1;
	if (!m_PcontactInfo)
	{
		m_PcontactInfo = new CTE_ContactInfo(m_parent);
		if(m_PcontactInfo)
		{
			m_PcontactInfo->Create(IDD_DIALOG_CONTACTINFO);
		}
	}
	strncpy(contactName,m_contactName.c_str(),TE_D_NAME_LEN);
	int len = TE_GetContactByName(contactName,&contact);	
	if(0 == len)
	{
		m_PcontactInfo->m_ContactName =contact.name;
		m_PcontactInfo->m_ContactNumber = contact.ucAcc;
		m_PcontactInfo->m_ContactOfficephone = contact.officePhone;
		m_PcontactInfo->m_ContactMobilephone = contact.mobile;
		m_PcontactInfo->m_ContactEmail = contact.email;
		m_PcontactInfo->m_ContactDepartment = contact.deptname;
		m_PcontactInfo->m_ContactAddress = contact.addresssite;
		m_PcontactInfo->m_NickName = contact.nickname;
	}
	else
	{
		AfxMessageBox("no get contact");
	}
	m_PcontactInfo->UpdateData(FALSE);
	m_PcontactInfo->ShowWindow(SW_SHOWNORMAL);
	TE_FreeMemory(getGroup.groupInfo);
}

void CTE_Contact::OnUpdateRecordList()
{
	int i=0,j=0,ret=0,len=0,x=0;
	TE_UINT32 num=0,Num=0;
	TE_S_GROUPS_INFO getGroup;
	TE_S_CONTACTS_INFO getContact;
	TE_S_GROUP_INFO m_groups;
	std::wstring cstrName;
	TE_E_USEKEY_SORT_RULE sortRule = group_status_first;
	memset(&m_groups, 0, sizeof(TE_S_GROUP_INFO));
	getContact.contact = NULL;
	getContact.num = 0;
	m_tree.DeleteAllItems();//删除所有节点
	m_hItemContact = m_tree.InsertItem("通讯录");//添加根节点
	ret = TE_GetCustomGroupList(&getGroup);
	if(ret == 0)
	{
		for(j = 0;j<(getGroup.num);j++)
		{
			TVINSERTSTRUCT tvStruct;
			tvStruct.hParent = m_hItemContact;
			tvStruct.hInsertAfter = NULL;
			tvStruct.item.mask = TVIF_TEXT|TVIF_PARAM;

			tvStruct.item.pszText = getGroup.groupInfo[j].groupName;
			HTREEITEM hItemSub = m_tree.InsertItem(&tvStruct);
			m_tree.SetItemData(hItemSub, (DWORD_PTR)(getGroup.groupInfo[j].groupName));
			ret = TE_GetContactsInGroup(getGroup.groupInfo[j].groupName,sortRule,&getContact);
			if(0 == ret)
			{
				for(i=0;i<getContact.num;i++)
				{
					TVINSERTSTRUCT tvStruct;
					tvStruct.hParent = hItemSub;
					tvStruct.hInsertAfter = NULL;
					tvStruct.item.mask = TVIF_TEXT|TVIF_PARAM;
					CString strTmp;
					//cstrName = m_parent->Utf82Unicode(getContact.contact[j].name);
					strTmp.Format("%s", getContact.contact[i].name);
					tvStruct.item.pszText = strTmp.GetBuffer();
					strTmp.ReleaseBuffer();
					HTREEITEM hItemSub1 = m_tree.InsertItem(&tvStruct);
					m_tree.SetItemData(hItemSub1, (DWORD_PTR)( getContact.contact[i].name));
				}
			}
		}
	}
	m_tree.Expand(m_hItemContact, TVE_EXPAND);
	if(getContact.contact)
	{
		TE_FreeMemory(getContact.contact);
	}
	if(getGroup.groupInfo)
	{
		TE_FreeMemory(getGroup.groupInfo);
	}	
}
void CTE_Contact::OnClickMessage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




void CTE_Contact::OnMoveContactToGroup()
{
	int i=0,j=0,k=0;
	int id_Begin= 10001;
	std::string temp = "recent  contact";
	int appendflag = 1;
	TE_CHAR tempName[65]={0};
	std::string tempGroup;
	TE_S_GROUPS_INFO groupsList;
	TE_S_GROUPS_INFO getGroups;
	if(m_menuflag)
	{
		m_menu1.DestroyMenu();
		m_menuflag = 0;
	}
	m_menu1.CreatePopupMenu();     //动态创建弹出式菜单对象
	int ret = TE_GetCustomGroupList(&groupsList);
	strncpy(tempName,m_contactName.c_str(),TE_D_NAME_LEN);
	ret = TE_GetCustomGroups(tempName,&getGroups);
	for(i=0;i<groupsList.num;i++)
	{
		appendflag =1;
		tempGroup = groupsList.groupInfo[i].groupName;
		for(k=0;k<getGroups.num;k++)
		{
			if((tempGroup == temp)||(getGroups.groupInfo[k].groupName == tempGroup))
			{
				appendflag = 0;
			}
		}
		if(appendflag)
		{
			m_menu1.AppendMenu(MF_STRING,id_Begin+j,groupsList.groupInfo[i].groupName);
			j++;
		}
	}
	SetForegroundWindow();
	CPoint pt;
	CString str;
	GetCursorPos(&pt);
	m_menu1.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	m_menuflag =1;
	OnUpdateRecordList();
	TE_FreeMemory(getGroups.groupInfo);
	TE_FreeMemory(groupsList.groupInfo);
	
}
void CTE_Contact::OnMenuCopyContactToGroup()
{
	int i=0,j=0,k=0;
	int id_Begin= 20001;
	std::string temp = "recent  contact";
	int appendflag = 1;
	TE_CHAR tempName[65]={0};
	std::string tempGroup;
	TE_S_GROUPS_INFO groupsList;
	TE_S_GROUPS_INFO getGroups;
	if(m_menuflag)
	{
		m_menu1.DestroyMenu();
		m_menuflag = 0;
	}
	m_menu1.CreatePopupMenu();     //动态创建弹出式菜单对象
	int ret = TE_GetCustomGroupList(&groupsList);
	strncpy(tempName,m_contactName.c_str(),TE_D_NAME_LEN);
	ret = TE_GetCustomGroups(tempName,&getGroups);
	for(i=0;i<groupsList.num;i++)
	{
		appendflag =1;
		tempGroup = groupsList.groupInfo[i].groupName;
		for(k=0;k<getGroups.num;k++)
		{
			if((tempGroup == temp)||(getGroups.groupInfo[k].groupName == tempGroup))
			{
				appendflag = 0;
			}
		}
		if(appendflag)
		{
			m_menu1.AppendMenu(MF_STRING,id_Begin+j,groupsList.groupInfo[i].groupName);
			j++;
		}
	}
	SetForegroundWindow();
	CPoint pt;
	CString str;
	GetCursorPos(&pt);
	m_menu1.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	m_menuflag =1;
	OnUpdateRecordList();
	TE_FreeMemory(getGroups.groupInfo);
	TE_FreeMemory(groupsList.groupInfo);
}

BOOL  CTE_Contact:: OnCommand(WPARAM wParam, LPARAM lParam)
{
		int menuID = LOWORD(wParam);
		switch(menuID)
		{
		case 32784:
			OnMenuAddContact();
			break;
		case  32787:
			OnMenuImport();
			break;
		case 32788:
			OnMenuExportGroup();
			break;
		case 32789:
			OnMenuAddGroup();
			break;
		case 32791:
			OnMenuAddGroup();
			break;
		case 32792:
			OnMenuRenameGroup();
			break;
		case 32793:
			OnMenudeleteGroup();
			break;
		case 32794:
			OnMenuVideoCall();
			break;
		case 32795:
			OnMenuAudioCall();
			break;
		case 32796:
			OnMenuSetNickName();
			break;
		case 32798:
			OnMenuEditContact();
			break;
		case 32799:
			OnMenuDeleteContact();
			break;
		case 32800:
			OnMenuAddContact();
			break;
		case 32801:
			OnMenuImport();
			break;
		case 32802:
			OnMenuExportGroup();
			break;
		case 32803:
			OnMenuAddGroup();
			break;
		case 32804:
			OnMenuAddContact();
			break;
		case 32805:
			OnMenuAddContact();
			break;
		case 32806:
			OnMenuImport();
			break;
		case 32807:
			OnMenuExportGroup();
			break;
		case 32808:
			OnMenuImport();
			break;
		case 32809:
			OnMenuExportGroup();
			break;
		case 32810:
			OnMenuCopyContactToGroup();
			break;
		case 32811:
			OnMoveContactToGroup();
			break;
		case 32814:
			OnMenuSetNickName();
			break;
		case IDC_BUTTON6:
			OnBnClickedButton6();
			break;

		default:
			break;
		}	
		if((menuID<20001)&&(menuID>10000))
		{
			int i =0;
			for (i=0;i<m_menu1.GetMenuItemCount();i++)
			{
				//m_newGroupName = m_menu1.GetMenuItemIDGetItemText(m_tree.GetSelectedItem());
				if(m_menu1.GetMenuItemID(i) == menuID)
				{
					m_menu1.GetMenuString(i,m_newGroupName,MF_BYPOSITION);
					break;
				}
			}
			
			OnMenuMoveToGroup();
		}
		else if((menuID>20000)&&(menuID<32784))
		{
			int i =0;
			for (i=0;i<m_menu1.GetMenuItemCount();i++)
			{
				//m_newGroupName = m_menu1.GetMenuItemIDGetItemText(m_tree.GetSelectedItem());
				if(m_menu1.GetMenuItemID(i) == menuID)
				{
					m_menu1.GetMenuString(i,m_newGroupName,MF_BYPOSITION);
					break;
				}
			}
		
			OnMenuCopyFromGroup();
		}
		else
		{
			return false;
		}
	return true;
}

void CTE_Contact::OnMenuMoveToGroup()
{
	char contactName[65] = {0};
	char newGroupName[65] = {0};
	char oldGroupName[65] = {0};
	strncpy(contactName,m_contactName.c_str(),TE_D_NAME_LEN);
	strncpy(oldGroupName,m_groupName.c_str(),TE_D_NAME_LEN);
	int len = m_newGroupName.GetLength();
	strncpy(newGroupName,m_newGroupName.GetBuffer(len),len);
	int ret = TE_MoveContactToGroup(contactName,newGroupName, oldGroupName);
	if(0 == ret)
	{
		AfxMessageBox("move success");
	}
	else
	{
		AfxMessageBox("move failed");
	}
	OnUpdateRecordList();
}

void CTE_Contact::OnMenuCopyFromGroup()
{
	char contactName[65] = {0};
	char groupName[65] = {0};
	int len = 0;
	strncpy(contactName,m_contactName.c_str(),TE_D_NAME_LEN);
	len = m_newGroupName.GetLength();
	strncpy(groupName,m_newGroupName.GetBuffer(len),len);
	int ret = TE_CopyContactToGroup(contactName,groupName);
	if(0 == ret)
	{
		AfxMessageBox("copy success");
	}
	else
	{
		AfxMessageBox("copy failed");
	}
	OnUpdateRecordList();
}

void CTE_Contact::OnMenuExportGroup()
{
	if (!m_export)
	{
		   m_export = new CTE_ExportGroup();
		   m_export->Create(IDD_DIALOG_EXPORTGROUP);
	}
	  m_export->ShowWindow(SW_SHOWNORMAL);
	
	int i=0,ret=0;
	TE_S_GROUPS_INFO getGroup;
	TE_UINT32 num = 0;
	std::wstring cstrName;
	LONG lStyle;
	lStyle = GetWindowLong(m_export->m_exportGroupList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_export->m_exportGroupList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_export->m_exportGroupList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_export->m_exportGroupList.SetExtendedStyle(dwStyle); //设置扩展风格
	while   (m_export->m_exportGroupList.DeleteColumn(0));
	 ret = TE_GetCustomGroupList(&getGroup);
	 if(0 == ret)
	 {
		 m_export->m_exportGroupList.InsertColumn( 0, "GROUP", LVCFMT_LEFT, 500 );    //插入列       
/*		 m_export->m_exportGroupList.InsertColumn( 1, "GROUP", LVCFMT_LEFT, 50 );   */    
		 //int nRow = m_export->m_exportGroupList.InsertItem(0, "Group");//插入行
		/* m_export->m_exportGroupList.SetItemText(nRow,1,"Group");*/
		 int nRow = 0;
		 m_export->m_exportGroupList.DeleteAllItems();
		 for(i=0;i<getGroup.num;i++)
		 {
			 if(0 == strcmp("recent  contact",getGroup.groupInfo[i].groupName))
			 {
				 continue;
			 }
			//cstrName =  m_parent->Utf82Unicode(getGroup.group[i].name);
			m_export->m_exportGroupList.InsertItem(nRow,getGroup.groupInfo[i].groupName);
			m_export->m_exportGroupList.SetItemText(nRow,0,getGroup.groupInfo[i].groupName);
			nRow++;
			}
	 }
}


