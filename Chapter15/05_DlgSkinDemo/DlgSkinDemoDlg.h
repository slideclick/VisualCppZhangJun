// DlgSkinDemoDlg.h : header file
//

#if !defined(AFX_DLGSKINDEMODLG_H__E19FEC96_2A4C_44B1_AAC9_ECE878D66605__INCLUDED_)
#define AFX_DLGSKINDEMODLG_H__E19FEC96_2A4C_44B1_AAC9_ECE878D66605__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgSkinDemoDlg dialog

class CDlgSkinDemoDlg : public CDialog
{
// Construction
public:
	CDlgSkinDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSkinDemoDlg)
	enum { IDD = IDD_DLGSKINDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSkinDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgSkinDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSKINDEMODLG_H__E19FEC96_2A4C_44B1_AAC9_ECE878D66605__INCLUDED_)
