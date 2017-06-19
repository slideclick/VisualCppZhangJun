// MouseMovingDlg.h : header file
//

#if !defined(AFX_MOUSEMOVINGDLG_H__98DB4676_C9BA_4B1D_B1A6_F4F5588816C2__INCLUDED_)
#define AFX_MOUSEMOVINGDLG_H__98DB4676_C9BA_4B1D_B1A6_F4F5588816C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMouseMovingDlg dialog

class CMouseMovingDlg : public CDialog
{
// Construction
public:
	CMouseMovingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMouseMovingDlg)
	enum { IDD = IDD_MOUSEMOVING_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseMovingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPoint m_ptMouse;
	BOOL m_bMoving;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMouseMovingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEMOVINGDLG_H__98DB4676_C9BA_4B1D_B1A6_F4F5588816C2__INCLUDED_)
