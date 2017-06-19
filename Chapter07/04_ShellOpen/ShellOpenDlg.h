// ShellOpenDlg.h : header file
//

#if !defined(AFX_SHELLOPENDLG_H__B5863DAF_83EF_49CB_B294_29B997F3EC90__INCLUDED_)
#define AFX_SHELLOPENDLG_H__B5863DAF_83EF_49CB_B294_29B997F3EC90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShellOpenDlg dialog

class CShellOpenDlg : public CDialog
{
// Construction
public:
	CShellOpenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShellOpenDlg)
	enum { IDD = IDD_SHELLOPEN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellOpenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShellOpenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnTxt();
	afx_msg void OnBtnUrl();
	afx_msg void OnBtnMail();
	afx_msg void OnBtnBmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void OpenTheFile(LPCTSTR lpFilename);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLOPENDLG_H__B5863DAF_83EF_49CB_B294_29B997F3EC90__INCLUDED_)
