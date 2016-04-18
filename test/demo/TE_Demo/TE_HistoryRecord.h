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
#include "string"

class CTE_DemoDlg;
class CTE_HistoryRecord : public CDialog
{
	DECLARE_DYNAMIC(CTE_HistoryRecord)

public:
	CTE_HistoryRecord(CWnd* pParent = NULL);
	virtual ~CTE_HistoryRecord();

	enum { IDD = IDD_DIALOG_HISTORYRECORD};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
private:

public:
	CListCtrl m_historyRecord;
	CString m_historySearch;
	std::string m_contactName;
	std::string historycord;
	CTE_DemoDlg *historyRecord;
	afx_msg void OnBnClickedButtonHistorySearch();
	afx_msg void OnNMRClickHistoryRecordMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuVideoCall();
	afx_msg void OnMenuAudioCall();
	afx_msg void OnMenuDeleteOneRecord();
	afx_msg void OnMenuDeleteAllRecord();
	void UpdateHistoryRecord();
	void ShowHistoryRecords(TE_S_PERSONS_INFO*  historyInfo);
};