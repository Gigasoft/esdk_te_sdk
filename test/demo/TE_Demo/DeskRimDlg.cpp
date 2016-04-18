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
// DeskRimDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "DeskRimDlg.h"


// CDeskRimDlg 对话框

IMPLEMENT_DYNAMIC(CDeskRimDlg, CDialog)

CDeskRimDlg::CDeskRimDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeskRimDlg::IDD, pParent)
{
	(void)m_brush.CreateSolidBrush( RGB(243, 159, 59));
}

CDeskRimDlg::~CDeskRimDlg()
{
	try
	{
		DeleteObject(m_brush);
	}
	catch (...)
	{
	}
}

void CDeskRimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeskRimDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDeskRimDlg 消息处理程序
void CDeskRimDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: 在此处添加消息处理程序代码
	CRect rcClient;

	GetClientRect( &rcClient );
	dc.FillRect( &rcClient, &m_brush);
}

int CDeskRimDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// TODO:  在此添加您专用的创建代码
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);
	CRect rcDeskTop(0, 0, 0, 0);
	::GetClientRect(GetDesktopWindow()->m_hWnd, &rcDeskTop );
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rcDeskTop.left, rcDeskTop.top, rcDeskTop.right, rcDeskTop.bottom,SWP_NOACTIVATE | SWP_SHOWWINDOW);

	HRGN RgnInside = CreateRectRgn( rcDeskTop.left + 3, rcDeskTop.top + 3,rcDeskTop.right - 3, rcDeskTop.bottom - 3 );

	HRGN RgnOut = CreateRectRgn( rcDeskTop.left, rcDeskTop.top, rcDeskTop.right, rcDeskTop.bottom );

	CombineRgn( RgnOut, RgnOut, RgnInside, RGN_DIFF );

	(void)SetWindowRgn( RgnOut, TRUE ); // 设置异形窗口
	ShowWindow( SW_SHOW );

	return 0;
}

void CDeskRimDlg::AdjustRect()
{
	CRect rcDeskTop(0, 0, 0, 0) ;
	::GetClientRect(GetDesktopWindow()->m_hWnd, &rcDeskTop );
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rcDeskTop.left, rcDeskTop.top, rcDeskTop.right, rcDeskTop.bottom, SWP_NOACTIVATE);

	HRGN RgnInside = CreateRectRgn( rcDeskTop.left + 3, rcDeskTop.top + 3,rcDeskTop.right - 3, rcDeskTop.bottom - 3 );

	HRGN RgnOut = CreateRectRgn( rcDeskTop.left, rcDeskTop.top, rcDeskTop.right, rcDeskTop.bottom );

	CombineRgn( RgnOut, RgnOut, RgnInside, RGN_DIFF );

	//FillRgn(hDCMem, RgnOut, m_brush );
	(void)SetWindowRgn( RgnOut, TRUE ); // 设置异形窗口
}
