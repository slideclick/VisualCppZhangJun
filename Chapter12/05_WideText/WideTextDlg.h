// WideTextDlg.h : header file
//

#if !defined(AFX_WIDETEXTDLG_H__068AAD67_AAB5_445D_877A_762435BD04D0__INCLUDED_)
#define AFX_WIDETEXTDLG_H__068AAD67_AAB5_445D_877A_762435BD04D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWideTextDlg dialog

class CWideTextDlg : public CDialog
{
// Construction
public:
	CWideTextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWideTextDlg)
	enum { IDD = IDD_WIDETEXT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWideTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWideTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDETEXTDLG_H__068AAD67_AAB5_445D_877A_762435BD04D0__INCLUDED_)
