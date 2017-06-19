// LockMouseDlg.h : header file
//

#if !defined(AFX_LOCKMOUSEDLG_H__7C8D7D86_9E74_449E_8430_962B00CF76AC__INCLUDED_)
#define AFX_LOCKMOUSEDLG_H__7C8D7D86_9E74_449E_8430_962B00CF76AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLockMouseDlg dialog

class CLockMouseDlg : public CDialog
{
// Construction
public:
	CLockMouseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLockMouseDlg)
	enum { IDD = IDD_LOCKMOUSE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLockMouseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	RECT m_rcClipOld;
	BOOL m_bClipping;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLockMouseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCKMOUSEDLG_H__7C8D7D86_9E74_449E_8430_962B00CF76AC__INCLUDED_)
