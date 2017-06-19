// PasswordShowDlg.h : header file
//

#if !defined(AFX_PASSWORDSHOWDLG_H__A84A2DE8_5AD3_4EA2_9DD8_C0A527B31BCB__INCLUDED_)
#define AFX_PASSWORDSHOWDLG_H__A84A2DE8_5AD3_4EA2_9DD8_C0A527B31BCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPasswordShowDlg dialog

typedef DWORD (*StartProc)(HWND);
typedef DWORD (*StopProc)();

class CPasswordShowDlg : public CDialog
{
// Construction
public:
	CPasswordShowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswordShowDlg)
	enum { IDD = IDD_PASSWORDSHOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMODULE m_hHookDll;
	StartProc m_procStart;
	StopProc m_procStop;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPasswordShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDSHOWDLG_H__A84A2DE8_5AD3_4EA2_9DD8_C0A527B31BCB__INCLUDED_)
