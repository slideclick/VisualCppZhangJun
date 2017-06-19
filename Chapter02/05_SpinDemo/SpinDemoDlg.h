// SpinDemoDlg.h : header file
//

#if !defined(AFX_SPINDEMODLG_H__6135F3B8_B1AD_4169_93AF_99ED4D552AE7__INCLUDED_)
#define AFX_SPINDEMODLG_H__6135F3B8_B1AD_4169_93AF_99ED4D552AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSpinDemoDlg dialog

class CSpinDemoDlg : public CDialog
{
// Construction
public:
	CSpinDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpinDemoDlg)
	enum { IDD = IDD_SPINDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpinDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPINDEMODLG_H__6135F3B8_B1AD_4169_93AF_99ED4D552AE7__INCLUDED_)
