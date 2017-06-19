// ColorStatusBarDlg.h : header file
//

#if !defined(AFX_COLORSTATUSBARDLG_H__4D2B131A_472E_4DD5_95ED_41F11D12DABA__INCLUDED_)
#define AFX_COLORSTATUSBARDLG_H__4D2B131A_472E_4DD5_95ED_41F11D12DABA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "colorprogress.h"

/////////////////////////////////////////////////////////////////////////////
// CColorStatusBarDlg dialog

class CColorStatusBarDlg : public CDialog
{
// Construction
public:
	CColorStatusBarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorStatusBarDlg)
	enum { IDD = IDD_COLORSTATUSBAR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatusBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CColorProgress m_progress;
	CStatusBar m_status;
	UINT m_nTimerID;
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CColorStatusBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATUSBARDLG_H__4D2B131A_472E_4DD5_95ED_41F11D12DABA__INCLUDED_)
