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
#include "TE_HistoryRecord.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_HistoryRecord,CDialog)

CTE_HistoryRecord::CTE_HistoryRecord(CWnd* pParent /*NULL*/)
:CDialog(CTE_HistoryRecord::IDD,pParent)
, m_historySearch(_T(""))
{
	historyRecord = (CTE_DemoDlg *)pParent;
}

CTE_HistoryRecord::~CTE_HistoryRecord()
{

}

void CTE_HistoryRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_historyRecord);
	DDX_Text(pDX, IDC_EDIT_HISTORY_SEARCH, m_historySearch);
}

BEGIN_MESSAGE_MAP(CTE_HistoryRecord,CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY_SEARCH, &CTE_HistoryRecord::OnBnClickedButtonHistorySearch)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CTE_HistoryRecord::OnNMRClickHistoryRecordMenu)
	ON_COMMAND(32810,&CTE_HistoryRecord::OnMenuVideoCall)
	ON_COMMAND(32811,&CTE_HistoryRecord::OnMenuAudioCall)
	ON_COMMAND(32812,&CTE_HistoryRecord::OnMenuDeleteOneRecord)
	ON_COMMAND(32813,&CTE_HistoryRecord::OnMenuDeleteAllRecord)
END_MESSAGE_MAP()



void CTE_HistoryRecord::OnBnClickedButtonHistorySearch()
{
	// TODO: 在此添加控件通知处理程序代码
	char searchKey[512]={0};
	TE_S_PERSONS_INFO historyRecords;
	historyRecords.historyRecords = NULL;
	historyRecords.num = 0;
	UpdateData(TRUE);
	int len = m_historySearch.GetLength();
	strncpy(searchKey,m_historySearch.GetBuffer(len),len);
	TE_SearchHistoryRecords(searchKey,&historyRecords);
	ShowHistoryRecords(&historyRecords);
	TE_FreeMemory(historyRecords.historyRecords);
}



void CTE_HistoryRecord::OnNMRClickHistoryRecordMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu m,*pm;
	CString str;
	TE_CHAR ContactName[512]={0};
	if(!m.LoadMenu(IDR_MENU_HISTORY))
	{
		MessageBox(_T("error"));
	}
	POSITION pos =  m_historyRecord.GetFirstSelectedItemPosition();     
	int indexToBeDeleted = m_historyRecord.GetNextSelectedItem(pos);   
	str = m_historyRecord.GetItemText(indexToBeDeleted,0);
	historycord = m_historyRecord.GetItemText(indexToBeDeleted,2);
	if(strcmp(str,""))
	{
		pm = m.GetSubMenu(0);
		CPoint pot;
		GetCursorPos(&pot);
		pm->TrackPopupMenu(TPM_LEFTALIGN,pot.x,pot.y,this);
	}
	m_contactName = str;
}


void CTE_HistoryRecord::OnMenuVideoCall()
{
	CString msg;
	TE_CHAR m_contact[512]={0};
	strncpy(m_contact,m_contactName.c_str(),sizeof(m_contact));
	if (historyRecord)
	{
		historyRecord->ContactVideoCall(m_contact);
		historyRecord->OnBnClickedButton4();
	}
}

void CTE_HistoryRecord::OnMenuAudioCall()
{
	TE_CHAR m_contact[512]={0};
	strncpy(m_contact,m_contactName.c_str(),sizeof(m_contact));
	if (historyRecord)
	{
		historyRecord->ContactAudioCall(m_contact);
		historyRecord->OnBnClickedButton4();
	}
}

void CTE_HistoryRecord::OnMenuDeleteOneRecord()
{
	/*TE_ULONG histroyRecordId;*/
	char contactName[512]={"0"};
	strncpy(contactName,historycord.c_str(),sizeof(contactName));
	TE_DeleteOneCallRecord(contactName);
	UpdateHistoryRecord();
}

void CTE_HistoryRecord::OnMenuDeleteAllRecord()
{
	TE_ClearAllCallRecord();
	UpdateHistoryRecord();
}

void CTE_HistoryRecord::UpdateHistoryRecord()
{
	historyRecord->OnBnClickedButton4();
}

void CTE_HistoryRecord::ShowHistoryRecords(TE_S_PERSONS_INFO*  historyInfo)
{
	if(!historyInfo)
	{
		return;
	}
	if(historyInfo->historyRecords == NULL)
	{
		return;
	}
	LONG lStyle;
	lStyle = GetWindowLong(m_historyRecord.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_historyRecord.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_historyRecord.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_historyRecord.SetExtendedStyle(dwStyle); //设置扩展风格
	while   (m_historyRecord.DeleteColumn(0));
	m_historyRecord.InsertColumn( 1, "NUMBER", LVCFMT_LEFT, 150 );
	m_historyRecord.InsertColumn( 2, "TIME", LVCFMT_LEFT, 120 );
	m_historyRecord.InsertColumn( 3, "ID", LVCFMT_LEFT, 10 );
	char key[512] = {"0"};

	TE_UINT32 num =0;
	int i = 0,j=0;
	int nRowNum =1;
	std::wstring cstrName;
	CString strTmp;
	m_historyRecord.DeleteAllItems();
	for( int j = 0; j < historyInfo->num; j++ )
	{
		// 插入一行，先插入行号, 作为第一列
		int nRowNum = m_historyRecord.InsertItem( j , historyInfo->historyRecords[j].strName);
		// 插入第二列的值
		m_historyRecord.SetItemText( nRowNum, 1,historyInfo->historyRecords[j].strTime );

		CString TempValue;
		long long historycord = historyInfo->historyRecords[j].recordID;
		TempValue.Format("%ld", historycord);
		m_historyRecord.SetItemText( nRowNum, 2,TempValue );
	}
}