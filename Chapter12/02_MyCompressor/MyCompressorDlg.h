// MyCompressorDlg.h : header file
//

#if !defined(AFX_MYCOMPRESSORDLG_H__DC50A8AA_8EE9_4059_9214_BC8F3F1BB199__INCLUDED_)
#define AFX_MYCOMPRESSORDLG_H__DC50A8AA_8EE9_4059_9214_BC8F3F1BB199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyCompressorDlg dialog

class CMyCompressorDlg : public CDialog
{
// Construction
public:
	CMyCompressorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyCompressorDlg)
	enum { IDD = IDD_MYCOMPRESSOR_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCompressorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyCompressorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnDecom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOMPRESSORDLG_H__DC50A8AA_8EE9_4059_9214_BC8F3F1BB199__INCLUDED_)
