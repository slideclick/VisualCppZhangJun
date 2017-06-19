// FlashWndDlg.h : header file
//

#if !defined(AFX_FLASHWNDDLG_H__70E1FEAF_5B23_46F1_90A3_775449E64545__INCLUDED_)
#define AFX_FLASHWNDDLG_H__70E1FEAF_5B23_46F1_90A3_775449E64545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\myflash.h"

/////////////////////////////////////////////////////////////////////////////
// CFlashWndDlg dialog

class CFlashWndDlg : public CDialog
{
// Construction
public:
	CFlashWndDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFlashWndDlg)
	enum { IDD = IDD_FLASHWND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashWndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyFlash m_flash;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlashWndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHWNDDLG_H__70E1FEAF_5B23_46F1_90A3_775449E64545__INCLUDED_)
