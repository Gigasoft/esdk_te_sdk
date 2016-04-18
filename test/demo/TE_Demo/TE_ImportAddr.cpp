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
#include "TE_ImportAddr.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"
#include "CApplication0.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"


#define EXCEL_POSTFIX               _T("xls")         // Excel文件后缀
#define EXCEL2007_POSTFIX           _T("xlsx")        // EXCEL2007文件后缀
#define EXCEL2010_POSTFIX           _T("xlsx")        // EXCEL2010文件后缀
#define EXCEL2012_POSTFIX           _T("xlsx")        // EXCEL2012文件后缀
#define CSV_POSTFIX                 _T("csv")         // csv文件后缀
#define POSTFIX_COUNT               3			      // 后缀名的个数
#define VNET_KEY_ROW_POS            1                 // V网伴侣文件关键字所在的行,即标题关键字
//const static int STADNTILENUM       = 13;              // 标准标题头字段数,最后一个字段为空
//const static int STADNTILENUM_OLD   = 7;              // 标准标题头字段数,最后一个字段为空(以前的字段数)

IMPLEMENT_DYNAMIC(CTE_ImportAddr,CDialog)

CTE_ImportAddr::CTE_ImportAddr(CWnd* pParent /*NULL*/)
:CDialog(CTE_ImportAddr::IDD,pParent)
, m_strFile(_T(""))
{
	m_pContactDlg = NULL;
	m_contacts = NULL;
	importContact =  (CTE_DemoDlg *)pParent;
}

CTE_ImportAddr::~CTE_ImportAddr()
{

}

void CTE_ImportAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strFile);
}

BEGIN_MESSAGE_MAP(CTE_ImportAddr,CDialog)

	ON_BN_CLICKED(IDC_BUTTON1, &CTE_ImportAddr::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CTE_ImportAddr::OnBnClickedOk)
END_MESSAGE_MAP()



void CTE_ImportAddr::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("(*.*)||(*.xlsx)||(*.xls)||(*.csv)"),
		NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_strFile=dlg.GetPathName(); //文件名保存在了FilePathName里
		UpdateData(FALSE);
	}
	else
	{
		return;
	}
}

void CTE_ImportAddr::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	char strPath[512]={0};
	int ret = 0;
	TE_S_GROUPS_CHAIN*  groupList;
	groupList = NULL;
	//判断路径是否为空
	if (m_strFile.IsEmpty())// 路径为空
	{
		// 提示:请选择等待导入的文件
	AfxMessageBox(_T("please choose and wait import file "));
		return ;
	}
	int len = m_strFile.GetLength();
	strncpy(strPath,m_strFile.GetBuffer(len),len);
	//判断能不能找到该文件
	const DWORD dwAttributes = GetFileAttributes( m_strFile );
	if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		// 提示:提示未找到该文件
	AfxMessageBox(_T(" we don't find the file"));
		return ;
	}

	// 取文件的后缀名
	CString filePostfix = _T("");
	const int postFixSize = m_strFile.GetLength() - (m_strFile.ReverseFind(_T('.')) + 1);
	if ((POSTFIX_COUNT == postFixSize) || (POSTFIX_COUNT + 1 ==postFixSize))
	{
		filePostfix = m_strFile.Right(postFixSize);
	}

	//不是Excel文件就是csv文件
	if ((EXCEL2007_POSTFIX== filePostfix) || (EXCEL_POSTFIX  == filePostfix))
	{
		ret = TE_ParseExcelFile(strPath,&groupList);
		if(0!= ret)
		{
			AfxMessageBox("parse excel file failed");
		}
	}
	else if (CSV_POSTFIX == filePostfix)
	{
		ret = TE_ParseCSVFile(strPath,&groupList);
		if(0!= ret)
		{
			AfxMessageBox("parse csv file failed");
		}
	}
	else
	{
		AfxMessageBox("Import file is not Excel Or CSV file !");
		return;
	}


	// 发消息给父窗口弹出导入进度 	// 通知父窗口显示选择联系人界面
	// 获取父窗口

	if(!m_pContactDlg)
	{
		return;
	}
	m_pContactDlg->ShowWindow(SW_SHOWNORMAL);
	::PostMessage(m_pContactDlg->GetSafeHwnd(), WM_CONTACT_SHOW_IMPORT_SELECTDLG, NULL, NULL);

	LONG lStyle;
	lStyle = GetWindowLong(m_pContactDlg->m_ContacList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_pContactDlg->m_ContacList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_pContactDlg->m_ContacList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_pContactDlg->m_ContacList.SetExtendedStyle(dwStyle); //设置扩展风格
	while   (m_pContactDlg->m_ContacList.DeleteColumn(0));
	m_pContactDlg->m_ContacList.InsertColumn( 1, "GROUP", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 2, "NAME", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 3, "NUMBER", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 4, "EMAIL", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 5, "ADDRESS", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 6, "DESCRIPTION", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 7, "DEPARTMENT", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 8, "MOBILEPHONE", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 9, "OFFICEPHONE", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 10, "DN", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 11, "TYPE", LVCFMT_LEFT, 150 );
	m_pContactDlg->m_ContacList.InsertColumn( 12, "NICKNAME", LVCFMT_LEFT, 150 );
	

	int nRowNum =1;
	int j=0;
	TE_S_CONTACTS_CHAIN *contactsChains;
	m_pContactDlg->m_ContacList.DeleteAllItems();
	if(NULL == groupList)
	{
		AfxMessageBox("error");
		return;
	}
	while(groupList)
	{
		while(groupList->group->contactsChain)
		{
			contactsChains = groupList->group->contactsChain;
			// 插入一行，先插入行号, 作为第一列
			int nRowNum = m_pContactDlg->m_ContacList.InsertItem( j , groupList->group->groupName);
			// 插入第二列的值
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 1,contactsChains->contactInfo.name );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 2,contactsChains->contactInfo.ucAcc );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 3,contactsChains->contactInfo.email );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 4,contactsChains->contactInfo.addresssite );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 5,contactsChains->contactInfo.description );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 6,contactsChains->contactInfo.deptname );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 7,contactsChains->contactInfo.mobile );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 8,contactsChains->contactInfo.officePhone );
			m_pContactDlg->m_ContacList.SetItemText( nRowNum, 11,contactsChains->contactInfo.nickname );
			groupList->group->contactsChain= groupList->group->contactsChain->next;
			TE_FreeMemory(contactsChains);
			
		}
		TE_S_GROUPS_CHAIN*  tmpgroupList=groupList;
		groupList = groupList->next;
		TE_FreeMemory(tmpgroupList);
	}
	OnOK();
}


