#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"


// ConfChairManApplyDlg �Ի���
#define CONF_APPLY_MSG_BEGIN					(WM_APP + 1301) //��Ϣ��ʼID
#define WM_CONF_APPLY_CHAIRMAN_RESULT			(CONF_APPLY_MSG_BEGIN+1)

class CTE_ConfCtrl;

class ConfChairManApplyDlg : public CDialog
{
	DECLARE_DYNAMIC(ConfChairManApplyDlg)

public:
	ConfChairManApplyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ConfChairManApplyDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_APPLY_CHAIRMAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
