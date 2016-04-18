#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"


// ConfChairManApplyDlg 对话框
#define CONF_APPLY_MSG_BEGIN					(WM_APP + 1301) //消息开始ID
#define WM_CONF_APPLY_CHAIRMAN_RESULT			(CONF_APPLY_MSG_BEGIN+1)

class CTE_ConfCtrl;

class ConfChairManApplyDlg : public CDialog
{
	DECLARE_DYNAMIC(ConfChairManApplyDlg)

public:
	ConfChairManApplyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ConfChairManApplyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_APPLY_CHAIRMAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT ApplyChairmanResult(WPARAM wParm, LPARAM Lparam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonApply();
	CString m_edtPassWord;
	void CloseConfApplyChairMan();
	int result;
	CTE_ConfCtrl* m_FromDlg;
};
