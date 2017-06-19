// MfcSockDlg.h : header file
//

#if !defined(AFX_MFCSOCKDLG_H__E2704680_DF7F_4CE9_8EC2_41AEF76DF66A__INCLUDED_)
#define AFX_MFCSOCKDLG_H__E2704680_DF7F_4CE9_8EC2_41AEF76DF66A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfcSockDlg dialog
#include "mysocket.h"

class CMfcSockDlg : public CDialog
{
// Construction
public:
	CMfcSockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfcSockDlg)
	enum { IDD = IDD_MFCSOCK_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcSockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void OutputMsg(LPCTSTR lpMsg);
protected:
	CMySocket m_sock;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMfcSockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSOCKDLG_H__E2704680_DF7F_4CE9_8EC2_41AEF76DF66A__INCLUDED_)
