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
#include "resource.h"
//#include "TE_Sheet.h"

// CTE_CallPage 对话框
class CTE_Sheet;

class CTE_CallPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTE_CallPage)

public:
	CTE_CallPage();
	virtual ~CTE_CallPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	
private:
	CTE_Sheet* m_sheet;

public:
	void SetSheet(CTE_Sheet* sheet) {;m_sheet = sheet;}


	afx_msg void OnBnClickedCallButton();
};
