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
// TE_ExtendTime.cpp : 实现文件
//

#include "stdafx.h"
#include "TE_Demo.h"
#include "TE_ExtendTime.h"


// CTE_ExtendTime 对话框

IMPLEMENT_DYNAMIC(CTE_ExtendTime, CDialog)

CTE_ExtendTime::CTE_ExtendTime(CWnd* pParent /*=NULL*/)
	: CDialog(CTE_ExtendTime::IDD, pParent)
{

}

CTE_ExtendTime::~CTE_ExtendTime()
{
}

void CTE_ExtendTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIME, m_timeList);
}


BEGIN_MESSAGE_MAP(CTE_ExtendTime, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CTE_ExtendTime::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTE_ExtendTime 消息处理程序

void CTE_ExtendTime::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_timeList.GetCurSel();

	short strTimeValue;

	switch(nIndex)
	{
	case 0:
		{
			strTimeValue = 30;
		}
		break;
	case 1:
		{
			strTimeValue = 60;
		}
		break;
	case 2:
		{
			strTimeValue = 90;
		}
		break;
	case 3:
		{
			strTimeValue = 120;
		}
		break;
	case 4:
		{
			strTimeValue = 180;
		}
		break;
	default:
		{
			strTimeValue = 30;
		}
	}

	TE_ExtendConfTime(strTimeValue);

	this->DestroyWindow();
}
