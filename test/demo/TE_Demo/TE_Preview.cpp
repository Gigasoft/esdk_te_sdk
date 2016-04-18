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
#include "TE_Preview.h"
#include "TE_Demo.h"
#include "TE_DemoDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CTE_Preview,CDialog)

CTE_Preview::CTE_Preview(CWnd* pParent /*NULL*/)
		:CDialog(CTE_Preview::IDD,pParent)
	{

	}

	CTE_Preview::~CTE_Preview()
	{

	}

	void CTE_Preview::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_STATIC_PREVIEW, m_preview);
	}

	BEGIN_MESSAGE_MAP(CTE_Preview,CDialog)
		ON_BN_CLICKED(IDOK, &CTE_Preview::OnBnClickedOk)
		ON_WM_CLOSE()
	END_MESSAGE_MAP()

	void CTE_Preview::OnBnClickedOk()
	{
		// TODO: 在此添加控件通知处理程序代码
		OnOK();
	}

	void CTE_Preview::OnClose()
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		TE_ClosePreview();	
		CDialog::OnClose();
	}
