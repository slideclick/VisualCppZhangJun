// RedirectStdioDlg.h : header file
//

#if !defined(AFX_REDIRECTSTDIODLG_H__2C490EDA_EBE5_455F_A1FF_E8C158A21177__INCLUDED_)
#define AFX_REDIRECTSTDIODLG_H__2C490EDA_EBE5_455F_A1FF_E8C158A21177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRedirectStdioDlg dialog

class CRedirectStdioDlg : public CDialog
{
// Construction
public:
	CRedirectStdioDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRedirectStdioDlg)
	enum { IDD = IDD_REDIRECTSTDIO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRedirectStdioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRedirectStdioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDIRECTSTDIODLG_H__2C490EDA_EBE5_455F_A1FF_E8C158A21177__INCLUDED_)
