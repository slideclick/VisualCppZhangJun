// MultiLanguageDlg.h : header file
//

#if !defined(AFX_MULTILANGUAGEDLG_H__35A4A92C_4048_43C0_BD23_592BFE8DE3F5__INCLUDED_)
#define AFX_MULTILANGUAGEDLG_H__35A4A92C_4048_43C0_BD23_592BFE8DE3F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageDlg dialog

class CMultiLanguageDlg : public CDialog
{
// Construction
public:
	CMultiLanguageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMultiLanguageDlg)
	enum { IDD = IDD_MULTILANGUAGE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiLanguageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMultiLanguageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChs();
	afx_msg void OnEn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILANGUAGEDLG_H__35A4A92C_4048_43C0_BD23_592BFE8DE3F5__INCLUDED_)
