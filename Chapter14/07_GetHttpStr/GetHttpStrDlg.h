// GetHttpStrDlg.h : header file
//

#if !defined(AFX_GETHTTPSTRDLG_H__C9348A8D_B57D_4F77_B974_6ABD880AE29E__INCLUDED_)
#define AFX_GETHTTPSTRDLG_H__C9348A8D_B57D_4F77_B974_6ABD880AE29E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetHttpStrDlg dialog

class CGetHttpStrDlg : public CDialog
{
// Construction
public:
	CGetHttpStrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetHttpStrDlg)
	enum { IDD = IDD_GETHTTPSTR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetHttpStrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetHttpStrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETHTTPSTRDLG_H__C9348A8D_B57D_4F77_B974_6ABD880AE29E__INCLUDED_)
