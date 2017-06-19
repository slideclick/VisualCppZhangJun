// InputDlg_DemoDlg.h : header file
//

#if !defined(AFX_INPUTDLG_DEMODLG_H__0F8017CA_F9FF_442F_A46D_5A3B09B963F9__INCLUDED_)
#define AFX_INPUTDLG_DEMODLG_H__0F8017CA_F9FF_442F_A46D_5A3B09B963F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInputDlg_DemoDlg dialog

class CInputDlg_DemoDlg : public CDialog
{
// Construction
public:
	CInputDlg_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInputDlg_DemoDlg)
	enum { IDD = IDD_INPUTDLG_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInputDlg_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_DEMODLG_H__0F8017CA_F9FF_442F_A46D_5A3B09B963F9__INCLUDED_)
