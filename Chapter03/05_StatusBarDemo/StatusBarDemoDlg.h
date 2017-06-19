// StatusBarDemoDlg.h : header file
//

#if !defined(AFX_STATUSBARDEMODLG_H__2A22E8B3_63E5_499C_A2DA_F08E2927B546__INCLUDED_)
#define AFX_STATUSBARDEMODLG_H__2A22E8B3_63E5_499C_A2DA_F08E2927B546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStatusBarDemoDlg dialog

class CStatusBarDemoDlg : public CDialog
{
// Construction
public:
	CStatusBarDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStatusBarDemoDlg)
	enum { IDD = IDD_STATUSBARDEMO_DIALOG };
	CEdit	m_edt_input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStatusBar m_status;
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStatusBarDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdtInput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSBARDEMODLG_H__2A22E8B3_63E5_499C_A2DA_F08E2927B546__INCLUDED_)
