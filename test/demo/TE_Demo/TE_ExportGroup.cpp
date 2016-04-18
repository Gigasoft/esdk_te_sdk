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
#include "TE_ExportGroup.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_ExportGroup,CDialog)

CTE_ExportGroup::CTE_ExportGroup(CWnd* pParent /*NULL*/)
:CDialog(CTE_ExportGroup::IDD,pParent)
{
}

CTE_ExportGroup::~CTE_ExportGroup()
{

}

void CTE_ExportGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_exportGroupList);
}

BEGIN_MESSAGE_MAP(CTE_ExportGroup,CDialog)

	ON_BN_CLICKED(IDOK, &CTE_ExportGroup::OnBnClickedOk)
END_MESSAGE_MAP()



void CTE_ExportGroup::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		"Export.xlsx",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("Excel File (*.xlsx)||Excel File (*.xls)||CSV File (*.csv)"),
		NULL);
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
	}
	else
	{
		return;
	}
	int groupCount =0,i=0;
	int ret =0;
	TE_S_GROUPS_INFO groupsList;
	groupsList.groupInfo = NULL;
	groupsList.num = 0;
	//TE_S_GROUP_INFO* groupList = new TE_S_GROUP_INFO[1000];
	int rowEnd = m_exportGroupList.GetItemCount();
	groupsList.groupInfo = new TE_S_GROUP_INFO[rowEnd];
	memset(groupsList.groupInfo,0,sizeof(TE_S_GROUP_INFO)*rowEnd);
	for(i=0;i<rowEnd;i++)
	{
		if(m_exportGroupList.GetCheck(i))
		{
			CString m_exportData= m_exportGroupList.GetItemText(i,0);
			int len = m_exportData.GetLength();
			strncpy(groupsList.groupInfo[groupCount].groupName,m_exportData.GetBuffer(len),len);
			groupsList.num++;
			groupCount++;
		}
	}
	
	char FileName[512]={0};
	int leng = FilePathName.GetLength();
	strncpy(FileName,FilePathName.GetBuffer(leng),leng);
	// 取文件的后缀名
	CString strPostFix = FilePathName.Right(POSTFIX_COUNT);
	if (0 == strPostFix.Compare(_T("lsx")))
	{
		strPostFix = FilePathName.Right(POSTFIX_COUNT + 1);
	}

	//不是Excel文件就是csv文件
	if ((EXCEL_POSTFIX == strPostFix) || (EXCEL2007_POSTFIX == strPostFix))
	{
		ret = TE_ExportExcelFile(FileName,&groupsList,1);
		if(0 == ret)
		{
			AfxMessageBox("Export Excel File Success");
		}
		else
		{
			AfxMessageBox("Export Excel File Failed");
		}
	}
	else if (CSV_POSTFIX == strPostFix)
	{
		ret = TE_ExportExcelFile(FileName,&groupsList,2);
		if(0 == ret)
		{
			AfxMessageBox("Export Csv File Success");
		}
		else
		{
			AfxMessageBox("Export Csv File Failed");
		}
	}
	else
	{
		//Do nothing
	}
	OnOK();
}
