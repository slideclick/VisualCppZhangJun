// LimitSizeDlg.h : header file
//

#if !defined(AFX_LIMITSIZEDLG_H__AF49E1CB_7973_45A7_A4FE_E096ABB0E3B1__INCLUDED_)
#define AFX_LIMITSIZEDLG_H__AF49E1CB_7973_45A7_A4FE_E096ABB0E3B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLimitSizeDlg dialog

class CLimitSizeDlg : public CDialog
{
// Construction
public:
	CLimitSizeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLimitSizeDlg)
	enum { IDD = IDD_LIMITSIZE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLimitSizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLimitSizeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIMITSIZEDLG_H__AF49E1CB_7973_45A7_A4FE_E096ABB0E3B1__INCLUDED_)
