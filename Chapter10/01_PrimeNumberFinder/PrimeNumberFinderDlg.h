// PrimeNumberFinderDlg.h : header file
//

#if !defined(AFX_PRIMENUMBERFINDERDLG_H__2DC3963B_C2CE_42C6_8696_722EE36662B9__INCLUDED_)
#define AFX_PRIMENUMBERFINDERDLG_H__2DC3963B_C2CE_42C6_8696_722EE36662B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderDlg dialog

class CPrimeNumberFinderDlg : public CDialog
{
// Construction
public:
	CPrimeNumberFinderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrimeNumberFinderDlg)
	enum { IDD = IDD_PRIMENUMBERFINDER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrimeNumberFinderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	inline BOOL IsPrimeNumber(int nInput);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPrimeNumberFinderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMENUMBERFINDERDLG_H__2DC3963B_C2CE_42C6_8696_722EE36662B9__INCLUDED_)
