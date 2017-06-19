// EditDemoDlg.h : header file
//

#if !defined(AFX_EDITDEMODLG_H__DB78DF1B_6399_42FA_9B7A_935E7A73C78C__INCLUDED_)
#define AFX_EDITDEMODLG_H__DB78DF1B_6399_42FA_9B7A_935E7A73C78C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditDemoDlg dialog

class CEditDemoDlg : public CDialog
{
// Construction
public:
	CEditDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEditDemoDlg)
	enum { IDD = IDD_EDITDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDEMODLG_H__DB78DF1B_6399_42FA_9B7A_935E7A73C78C__INCLUDED_)
