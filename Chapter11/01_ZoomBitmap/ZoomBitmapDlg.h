// ZoomBitmapDlg.h : header file
//

#if !defined(AFX_ZOOMBITMAPDLG_H__326DE6C4_D05B_4877_BB09_1D1EECA14396__INCLUDED_)
#define AFX_ZOOMBITMAPDLG_H__326DE6C4_D05B_4877_BB09_1D1EECA14396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZoomBitmapDlg dialog

class CZoomBitmapDlg : public CDialog
{
// Construction
public:
	CZoomBitmapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomBitmapDlg)
	enum { IDD = IDD_ZOOMBITMAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomBitmapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nBltMode;
	int m_nZoomPercent;
	CBitmap m_bmp;
	CBitmap *m_pOldBmp;
	CDC m_dc;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZoomBitmapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnOpen();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnBalckonwhite();
	afx_msg void OnWhiteonblack();
	afx_msg void OnColoroncolor();
	afx_msg void OnHalftone();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void FreeObjects();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMBITMAPDLG_H__326DE6C4_D05B_4877_BB09_1D1EECA14396__INCLUDED_)
