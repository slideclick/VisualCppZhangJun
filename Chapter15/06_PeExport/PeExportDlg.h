// PeExportDlg.h : header file
//

#if !defined(AFX_PEEXPORTDLG_H__73542E0D_AD0E_49FE_98F5_D76AB5F7FDB6__INCLUDED_)
#define AFX_PEEXPORTDLG_H__73542E0D_AD0E_49FE_98F5_D76AB5F7FDB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPeExportDlg dialog

class CPeExportDlg : public CDialog
{
// Construction
public:
	CPeExportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPeExportDlg)
	enum { IDD = IDD_PEEXPORT_DIALOG };
	CListBox	m_lst_Functions;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeExportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPeExportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEEXPORTDLG_H__73542E0D_AD0E_49FE_98F5_D76AB5F7FDB6__INCLUDED_)
