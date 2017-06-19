// TransExecDlg.h : header file
//

#if !defined(AFX_TRANSEXECDLG_H__EAFB7A88_5A38_44C7_A4D3_D7F89155294B__INCLUDED_)
#define AFX_TRANSEXECDLG_H__EAFB7A88_5A38_44C7_A4D3_D7F89155294B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//引入ADO类型库。
//注意，不同的计算机环境，ado类型库所在位置可能不同，请酌情修改本行代码
#import "d:\Program files\common files\system\ado\msado15.dll"  no_namespace rename ("EOF", "adoEOF") 

/////////////////////////////////////////////////////////////////////////////
// CTransExecDlg dialog

class CTransExecDlg : public CDialog
{
// Construction
public:
	CTransExecDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTransExecDlg)
	enum { IDD = IDD_TRANSEXEC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransExecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	_ConnectionPtr	m_pConnection;	//数据库连接对象
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTransExecDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSEXECDLG_H__EAFB7A88_5A38_44C7_A4D3_D7F89155294B__INCLUDED_)
