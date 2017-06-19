// TabCtrlDemoDlg.h : header file
//

#if !defined(AFX_TABCTRLDEMODLG_H__B40D7647_673A_4E42_984C_A2AD30718098__INCLUDED_)
#define AFX_TABCTRLDEMODLG_H__B40D7647_673A_4E42_984C_A2AD30718098__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "page1dlg.h"
#include "page2dlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDemoDlg dialog

class CTabCtrlDemoDlg : public CDialog
{
// Construction
public:
	CTabCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTabCtrlDemoDlg)
	enum { IDD = IDD_TABCTRLDEMO_DIALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPage1Dlg m_page1;
	CPage2Dlg m_page2;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTabCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCTRLDEMODLG_H__B40D7647_673A_4E42_984C_A2AD30718098__INCLUDED_)
