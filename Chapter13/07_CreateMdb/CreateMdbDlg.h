// CreateMdbDlg.h : header file
//

#if !defined(AFX_CREATEMDBDLG_H__28B8E8C2_92BF_4FA3_AC6F_C53C1BCC6E93__INCLUDED_)
#define AFX_CREATEMDBDLG_H__28B8E8C2_92BF_4FA3_AC6F_C53C1BCC6E93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "d:\Program Files\Common Files\system\ado\msadox.dll"
#import "d:\program files\common files\system\ado\msado15.dll"  no_namespace rename ("EOF", "adoEOF") 
/////////////////////////////////////////////////////////////////////////////
// CCreateMdbDlg dialog

class CCreateMdbDlg : public CDialog
{
// Construction
public:
	CCreateMdbDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateMdbDlg)
	enum { IDD = IDD_CREATEMDB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateMdbDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCreateMdbDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEMDBDLG_H__28B8E8C2_92BF_4FA3_AC6F_C53C1BCC6E93__INCLUDED_)
