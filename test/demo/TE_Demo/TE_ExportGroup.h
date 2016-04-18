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
#include "TE_Contact.h"
#include "string"

class CTE_ExportGroup : public CDialog
{
	DECLARE_DYNAMIC(CTE_ExportGroup)

public:
	CTE_ExportGroup(CWnd* pParent = NULL);
	virtual ~CTE_ExportGroup();

	enum { IDD = IDD_DIALOG_EXPORTGROUP };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_exportGroupList;
	afx_msg void OnBnClickedOk();
};