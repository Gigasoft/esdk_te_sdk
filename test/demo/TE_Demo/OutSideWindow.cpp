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
// OutSideWindow.cpp : 实现文件
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "OutSideWindow.h"


// COutSideWindow 对话框

IMPLEMENT_DYNAMIC(COutSideWindow, CDialog)

#define WIDTHHEIGHTADD 3

COutSideWindow::COutSideWindow(CWnd* pParent /*=NULL*/, HWND hAttachWnd)
: CDialog(COutSideWindow::IDD, pParent)
{
	m_hAttachWindowRect.left = 0;
	m_hAttachWindowRect.right = 0;
	m_hAttachWindowRect.top = 0;
	m_hAttachWindowRect.bottom = 0;

	m_hAttachHWnd = hAttachWnd;
	(void)m_brush.CreateSolidBrush( RGB(243, 159, 59) );
}

COutSideWindow::~COutSideWindow()
{
	try
	{
		m_hAttachHWnd = NULL;
		DeleteObject(m_brush);
	}
	catch (...)
	{
	}
}

void COutSideWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COutSideWindow, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// COutSideWindow 消息处理程序
/*******************************************************************************
* 函数名称 : OnPaint
* 函数描述 : 创建异型窗口
* 输入参数 : N/A
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
void COutSideWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rc(0, 0, 0, 0);
	GetClientRect(&rc);
	dc.FillRect( &rc, &m_brush);

	HRGN RgnInside = CreateRectRgn( rc.left + WIDTHHEIGHTADD, rc.top + WIDTHHEIGHTADD,rc.right - WIDTHHEIGHTADD, rc.bottom - WIDTHHEIGHTADD );

	HRGN RgnOut = CreateRectRgn( rc.left, rc.top, rc.right, rc.bottom );

	CombineRgn( RgnOut, RgnOut, RgnInside, RGN_DIFF );
	(void)SetWindowRgn( RgnOut, TRUE ); // 设置异形窗口

	DeleteObject( RgnInside );
	DeleteObject( RgnOut );

}

void COutSideWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	ShowWnd();
}

int COutSideWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);

	return 0;
}

int COutSideWindow::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COutSideWindow::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

/*******************************************************************************
* 函数名称 : ShowWnd
* 函数描述 : 显示异型窗口
* 输入参数 : N/A
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
VOID COutSideWindow::ShowWnd()
{
	RECT rc = {0, 0, 0, 0};
	ECalcResult eResult = CalcOutSideWindowRect( rc ) ;
	if ( EError == eResult ) 
	{
		::SetWindowPos( m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE | SWP_HIDEWINDOW );
		//::ShowWindow( m_hWnd, SW_HIDE );
		return;
	}
	else if ( ENoChange == eResult )
	{
		return;
	}

	//     ::MoveWindow( m_hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE );
	//     ::ShowWindow( m_hWnd, SW_SHOW );
	::SetWindowPos( m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);

}

/*******************************************************************************
* 函数名称 : HideWnd
* 函数描述 : 隐藏异型窗口
* 输入参数 : N/A
* 输出参数 : N/A
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
VOID COutSideWindow::HideWnd()
{
	::SetWindowPos( m_hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |SWP_NOACTIVATE | SWP_HIDEWINDOW );
}

/*******************************************************************************
* 函数名称 : CalcOutSideWindowRect
* 函数描述 : 计算窗口外围大小
* 输入参数 : N/A
* 输出参数 : RECT& rc
* 返 回 值 : 0:        成功
*            其他:     失败
* 其他说明 : N/A
* 修改历史 : 2014-1-21    1.0.0   zhuxudong
*  1.日    期 : 2014-1-21
*    作    者 : z00220320
*    修改内容 : 初始版本
*******************************************************************************/
ECalcResult COutSideWindow::CalcOutSideWindowRect(RECT& rc)
{
	ECalcResult eResult = EError;

	do 
	{
		if ( NULL == m_hAttachHWnd ) 
		{
			break;
		}

		static CRect rcAttachWindowLast(0,0,0,0);
		CRect rcAttachWindow(0,0,0,0);
		if ( FALSE == ::GetWindowRect( m_hAttachHWnd, &rcAttachWindow ) ) 
		{
			break;
		}

		if ( rcAttachWindow.left != rcAttachWindowLast.left 
			|| rcAttachWindow.right != rcAttachWindowLast.right
			|| rcAttachWindow.top != rcAttachWindowLast.top 
			|| rcAttachWindow.bottom != rcAttachWindowLast.bottom )
		{
			if(rcAttachWindowLast.IsRectEmpty())
			{
				eResult = EError;
			}

			rcAttachWindowLast = rcAttachWindow;
			rc.left = rcAttachWindow.left - WIDTHHEIGHTADD;
			rc.top = rcAttachWindow.top - WIDTHHEIGHTADD;
			rc.right = rcAttachWindow.right + WIDTHHEIGHTADD;
			rc.bottom = rcAttachWindow.bottom + WIDTHHEIGHTADD;
			break;
		}


		if ( rcAttachWindow.left == m_hAttachWindowRect.left 
			&& rcAttachWindow.right == m_hAttachWindowRect.right
			&& rcAttachWindow.top == m_hAttachWindowRect.top 
			&& rcAttachWindow.bottom == m_hAttachWindowRect.bottom )
		{
			eResult = ENoChange;
			break;
		}
		else
		{
			m_hAttachWindowRect = rcAttachWindow;
		}

		rc.left = rcAttachWindow.left - WIDTHHEIGHTADD;
		rc.top = rcAttachWindow.top - WIDTHHEIGHTADD;
		rc.right = rcAttachWindow.right + WIDTHHEIGHTADD;
		rc.bottom = rcAttachWindow.bottom + WIDTHHEIGHTADD;

		eResult = ESuc;
		break;
	} while (0);
	return eResult;
}