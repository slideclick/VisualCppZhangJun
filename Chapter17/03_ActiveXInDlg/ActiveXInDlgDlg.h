// ActiveXInDlgDlg.h : header file
//

#if !defined(AFX_ACTIVEXINDLGDLG_H__E2574DF4_56A1_4EAC_98CC_04F3434624EE__INCLUDED_)
#define AFX_ACTIVEXINDLGDLG_H__E2574DF4_56A1_4EAC_98CC_04F3434624EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "myactivex.h"

/////////////////////////////////////////////////////////////////////////////
// CActiveXInDlgDlg dialog

class CActiveXInDlgDlg : public CDialog
{
// Construction
public:
	CActiveXInDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveXInDlgDlg)
	enum { IDD = IDD_ACTIVEXINDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveXInDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyActiveX *m_pMyActiveX;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CActiveXInDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPut();
	afx_msg void OnBtnAnimate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEXINDLGDLG_H__E2574DF4_56A1_4EAC_98CC_04F3434624EE__INCLUDED_)
