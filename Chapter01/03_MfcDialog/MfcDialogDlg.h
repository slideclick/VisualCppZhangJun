// MfcDialogDlg.h : header file
//

#if !defined(AFX_MFCDIALOGDLG_H__FA313E44_9BA6_4CA0_A9CE_9787842D11B6__INCLUDED_)
#define AFX_MFCDIALOGDLG_H__FA313E44_9BA6_4CA0_A9CE_9787842D11B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfcDialogDlg dialog

class CMfcDialogDlg : public CDialog
{
// Construction
public:
	CMfcDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfcDialogDlg)
	enum { IDD = IDD_MFCDIALOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMfcDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDIALOGDLG_H__FA313E44_9BA6_4CA0_A9CE_9787842D11B6__INCLUDED_)
