#if !defined(AFX_ANIMATEDDLG_H__EA6916E5_824F_4683_A960_AE2026A98A03__INCLUDED_)
#define AFX_ANIMATEDDLG_H__EA6916E5_824F_4683_A960_AE2026A98A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimatedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnimatedDlg dialog

class CAnimatedDlg : public CDialog
{
// Construction
public:
	CAnimatedDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimatedDlg)
	enum { IDD = IDD_ANIMATED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimatedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HBRUSH m_hb;
	
	// Generated message map functions
	//{{AFX_MSG(CAnimatedDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEDDLG_H__EA6916E5_824F_4683_A960_AE2026A98A03__INCLUDED_)
