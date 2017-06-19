// AnimatedWndDlg.h : header file
//

#if !defined(AFX_ANIMATEDWNDDLG_H__3DCF7E47_8550_4C6E_882C_8FD8D3DECBA1__INCLUDED_)
#define AFX_ANIMATEDWNDDLG_H__3DCF7E47_8550_4C6E_882C_8FD8D3DECBA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAnimatedWndDlg dialog
#include "animateddlg.h"

class CAnimatedWndDlg : public CDialog
{
// Construction
public:
	CAnimatedWndDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimatedWndDlg)
	enum { IDD = IDD_ANIMATEDWND_DIALOG };
	CComboBox	m_cmb_AnimateType;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimatedWndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAnimatedDlg m_dlg;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAnimatedWndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnBtnHide();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void GetInput(int *nAnimateType, int *nTime);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEDWNDDLG_H__3DCF7E47_8550_4C6E_882C_8FD8D3DECBA1__INCLUDED_)
