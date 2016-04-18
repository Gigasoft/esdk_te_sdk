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
#pragma  once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "TE_AddGroup.h"
#include "TE_ContactInfo.h"
#include "TE_RenameGroup.h"
#include "TE_InComingCall.h"
#include "TE_NickName.h"
#include "TE_ImportContact.h"
#include "TE_ImportAddr.h"
#include "TE_ExportGroup.h"
#include "TE_ImportContact.h"
#include <list>
#include <map>

class  CTE_DemoDlg;
class  CTE_RenameGroup;
class  CTE_Nickname;
class CTE_ImportContact;
class CTE_ImportAddr;
class CTE_ExportGroup;

#define CTK_ANSI_TO_WSTRING(inBuf, inLen, outBuf, outLen) \
	MultiByteToWideChar(CTK_CP_DEFAULT, 0, inBuf, inLen, outBuf, outLen)

class CTE_Contact : public CDialog
{
	DECLARE_DYNAMIC(CTE_Contact)

public:
	CTE_Contact(CWnd* pParent = NULL);
	virtual ~CTE_Contact();

	enum { IDD = IDD_DIALOG_CONTACT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
private:
public:
	CTE_ContactInfo* m_PcontactInfo;
	CTE_DemoDlg *m_parent;
	CTE_Group *m_group;
	CTE_RenameGroup *m_renamegroup;
	CTE_Nickname *m_Nickname;
	CTE_ImportAddr *m_Import;
	CTE_ExportGroup *m_export;
	CTE_ImportContact *m_imortContact;

	int num;
	int  contacttype; // difference between add new contact and edit contact.
	int Initnum;
	int SetFlagContact; 
	std::string CurrentVideo;
	CString m_newGroupName;
	HTREEITEM m_hItemContact;
	std::string m_contactName;
	std::string m_groupName;
	TE_CHAR m_ID[1000][1000];
	TE_S_CONTACT_INFO  m_contactinfo;
	CTE_IncomingCall* m_incomingCall;
	CMenu m_menu1;
	int m_menuflag;
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();

	afx_msg void ClickMessage(NMHDR *pNMHDR, LRESULT *pResult);

	CString m_searchcontact;
	afx_msg void OnBnClickedButton6();
	
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_tree;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListContactMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuAddContact();
	afx_msg void OnMenuAddGroup();
	afx_msg void OnMenudeleteGroup();
	afx_msg void OnMenuRenameGroup();
	afx_msg void OnMenuVideoCall();
	afx_msg void OnMenuAudioCall();
	afx_msg void OnMenuDeleteContact();
	afx_msg void OnMenuEditContact();
	afx_msg void OnMenuSetNickName();
	afx_msg void OnBnClickedOpennc();
	afx_msg void OnMenuImport();
	afx_msg void OnMenuExportGroup();
	afx_msg void OnMenuCopyContactToGroup();
	afx_msg void OnMoveContactToGroup();
	void OnUpdateRecordList();
	BOOL  OnCommand(WPARAM wParam, LPARAM lParam);
	void  OnMenuMoveToGroup();
	void  OnMenuCopyFromGroup();

	afx_msg void OnClickMessage(NMHDR *pNMHDR, LRESULT *pResult);
};