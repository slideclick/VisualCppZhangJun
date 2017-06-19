// AppSnapDlg.h : header file
//

#if !defined(AFX_APPSNAPDLG_H__AFDC7FF7_836D_4154_9C6D_43FB885DE18D__INCLUDED_)
#define AFX_APPSNAPDLG_H__AFDC7FF7_836D_4154_9C6D_43FB885DE18D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAppSnapDlg dialog

class CAppSnapDlg : public CDialog
{
// Construction
public:
	CAppSnapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAppSnapDlg)
	enum { IDD = IDD_APPSNAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppSnapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAppSnapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPSNAPDLG_H__AFDC7FF7_836D_4154_9C6D_43FB885DE18D__INCLUDED_)
