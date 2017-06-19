// ExecProcDlg.h : header file
//

#if !defined(AFX_EXECPROCDLG_H__DAA9E08F_0DBA_4FCB_AC13_0EB83B311902__INCLUDED_)
#define AFX_EXECPROCDLG_H__DAA9E08F_0DBA_4FCB_AC13_0EB83B311902__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "d:\Program files\common files\system\ado\msado15.dll"  no_namespace rename ("EOF", "adoEOF")

/////////////////////////////////////////////////////////////////////////////
// CExecProcDlg dialog

class CExecProcDlg : public CDialog
{
// Construction
public:
	CExecProcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExecProcDlg)
	enum { IDD = IDD_EXECPROC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExecProcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	_ConnectionPtr	m_pConnection;	//数据库连接对象
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExecProcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnExec1();
	afx_msg void OnBtnExec2();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXECPROCDLG_H__DAA9E08F_0DBA_4FCB_AC13_0EB83B311902__INCLUDED_)
