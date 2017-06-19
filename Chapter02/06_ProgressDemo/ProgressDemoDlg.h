// ProgressDemoDlg.h : header file
//

#if !defined(AFX_PROGRESSDEMODLG_H__D0A043BA_BA1D_4F23_8CA8_4728C7C9F16E__INCLUDED_)
#define AFX_PROGRESSDEMODLG_H__D0A043BA_BA1D_4F23_8CA8_4728C7C9F16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDlg dialog

class CProgressDemoDlg : public CDialog
{
// Construction
public:
	CProgressDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDemoDlg)
	enum { IDD = IDD_PROGRESSDEMO_DIALOG };
	CProgressCtrl	m_progress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProgressDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDEMODLG_H__D0A043BA_BA1D_4F23_8CA8_4728C7C9F16E__INCLUDED_)
