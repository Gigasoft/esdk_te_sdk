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
#include "afxcmn.h"
#include "TE_CallPage.h"

class CTE_Sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTE_Sheet)

public:
	CTE_Sheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTE_Sheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CTE_Sheet();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CTE_CallPage m_callPage;

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	void ShowTitleMsg(CString msg) {SetWindowText(msg);}
#if 0
	void MainLoop();
	void StartMsgRetrieval();
	void StopMsgRetrieval();
	void OpenAddressBook(vector<SiteAddrRecord> &callRecords);
#endif
};