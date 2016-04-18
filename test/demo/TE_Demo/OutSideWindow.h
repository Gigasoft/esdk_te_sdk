#pragma once


// COutSideWindow �Ի���
enum ECalcResult{
	EError = 0,
	ESuc = 1,
	ENoChange = 2
};


class COutSideWindow : public CDialog
{
	DECLARE_DYNAMIC(COutSideWindow)

public:
	COutSideWindow(CWnd* pParent = NULL, HWND hAttachWnd = NULL);   // ��׼���캯��
	virtual ~COutSideWindow();

// �Ի�������
	enum { IDD = IDD_OUTSIDE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();

	VOID HideWnd();
	VOID ShowWnd();
	BOOL IsNeedDealMsg( UINT uMsg );

	BOOL IsNeedShowMsg( UINT uMsg );

	BOOL IsValibleWindow( HWND hWnd );
	BOOL IsBaseWindow( HWND hWnd );

	BOOL IsTopWindow( HWND hwnd );
	ECalcResult CalcOutSideWindowRect(RECT& rc);


	HWND m_hAttachHWnd;
	CBrush m_brush;
	RECT m_hAttachWindowRect;
};
