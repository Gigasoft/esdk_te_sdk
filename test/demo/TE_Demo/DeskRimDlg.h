#pragma once


// CDeskRimDlg �Ի���

class CDeskRimDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeskRimDlg)

public:
	CDeskRimDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeskRimDlg();

// �Ի�������
	enum { IDD = IDD_DLG_DESK_RIM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

private:
	CBrush m_brush;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void AdjustRect();
};

