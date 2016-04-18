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
#include "TE_Contact.h"
#include "string"

class CTE_ImportContact;
class CTE_Contact;

class CTE_ImportAddr : public CDialog
{
	DECLARE_DYNAMIC(CTE_ImportAddr)

public:
	CTE_ImportAddr(CWnd* pParent = NULL);
	virtual ~CTE_ImportAddr();

	enum { IDD = IDD_DIALOG_IMPORTFILE };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CTE_DemoDlg* importContact;
	CString m_strFile;
	CTE_ImportContact *m_pContactDlg;
	CTE_Contact *m_contacts;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	void initListCtrlColumn( int nColumnNum );
	void updateListCtrlData( CStringArray* arrayStr, int nRow );
};