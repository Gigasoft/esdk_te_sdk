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

class  CTE_Contact;
class CTE_DemoDlg;

class CTE_ContactInfo : public CDialog
{
	DECLARE_DYNAMIC(CTE_ContactInfo)

public:
	CTE_ContactInfo(CWnd* pParent = NULL);
	virtual ~CTE_ContactInfo();

	enum { IDD = IDD_DIALOG_CONTACTINFO };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
private:

public:
	CString m_ContactName;
	afx_msg void OnBnClickedOk();
	CString m_ContactNumber;
	CString m_ContactDepartment;
	CString m_ContactMobilephone;
	CString m_ContactOfficephone;
	CString m_ContactEmail;
	CString m_ContactAddress;
	CComboBox m_ComboGroup;
	 CTE_Contact* m_info;
	 CTE_DemoDlg* m_demodlg;
	 afx_msg void OnBnClickedButton1();
	 int m_iLogItem ;
	 CString m_NickName;
};