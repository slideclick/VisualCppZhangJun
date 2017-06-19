// NCMsgDlg.h : header file
//

#if !defined(AFX_NCMSGDLG_H__1F81C7F0_C54D_4CAB_8D2E_D3DAE3664917__INCLUDED_)
#define AFX_NCMSGDLG_H__1F81C7F0_C54D_4CAB_8D2E_D3DAE3664917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNCMsgDlg dialog

class CNCMsgDlg : public CDialog
{
// Construction
public:
	CNCMsgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNCMsgDlg)
	enum { IDD = IDD_NCMSG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNCMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNCMsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NCMSGDLG_H__1F81C7F0_C54D_4CAB_8D2E_D3DAE3664917__INCLUDED_)
