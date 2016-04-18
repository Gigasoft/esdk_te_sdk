#pragma once


// CDeskRimDlg 对话框

class CDeskRimDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeskRimDlg)

public:
	CDeskRimDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeskRimDlg();

// 对话框数据
	enum { IDD = IDD_DLG_DESK_RIM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

private:
	CBrush m_brush;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void AdjustRect();
};

