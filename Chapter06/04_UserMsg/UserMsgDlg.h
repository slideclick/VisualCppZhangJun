// UserMsgDlg.h : header file
//

#if !defined(AFX_USERMSGDLG_H__F65CEA1B_4A6E_4273_92A7_2C364D6A40E1__INCLUDED_)
#define AFX_USERMSGDLG_H__F65CEA1B_4A6E_4273_92A7_2C364D6A40E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUserMsgDlg dialog

class CUserMsgDlg : public CDialog
{
// Construction
public:
	CUserMsgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUserMsgDlg)
	enum { IDD = IDD_USERMSG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUserMsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnMymsg();
	//}}AFX_MSG
	afx_msg void OnMyRegisteredMsg();
	afx_msg void OnMyDefinedMsg();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERMSGDLG_H__F65CEA1B_4A6E_4273_92A7_2C364D6A40E1__INCLUDED_)
