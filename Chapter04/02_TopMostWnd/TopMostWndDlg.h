// TopMostWndDlg.h : header file
//

#if !defined(AFX_TOPMOSTWNDDLG_H__3C4A8025_9DFE_4269_B51C_C3B490CCC30A__INCLUDED_)
#define AFX_TOPMOSTWNDDLG_H__3C4A8025_9DFE_4269_B51C_C3B490CCC30A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTopMostWndDlg dialog

class CTopMostWndDlg : public CDialog
{
// Construction
public:
	CTopMostWndDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTopMostWndDlg)
	enum { IDD = IDD_TOPMOSTWND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopMostWndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTopMostWndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChkTopmost();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPMOSTWNDDLG_H__3C4A8025_9DFE_4269_B51C_C3B490CCC30A__INCLUDED_)
