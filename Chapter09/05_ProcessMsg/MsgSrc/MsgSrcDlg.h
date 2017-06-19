// MsgSrcDlg.h : header file
//

#if !defined(AFX_MSGSRCDLG_H__D1E54D8B_A9EF_4107_ACB7_CB474DFB510D__INCLUDED_)
#define AFX_MSGSRCDLG_H__D1E54D8B_A9EF_4107_ACB7_CB474DFB510D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMsgSrcDlg dialog

class CMsgSrcDlg : public CDialog
{
// Construction
public:
	CMsgSrcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgSrcDlg)
	enum { IDD = IDD_MSGSRC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgSrcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMsgSrcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnUserCounter(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSRCDLG_H__D1E54D8B_A9EF_4107_ACB7_CB474DFB510D__INCLUDED_)
