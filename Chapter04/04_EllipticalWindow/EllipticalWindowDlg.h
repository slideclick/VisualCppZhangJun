// EllipticalWindowDlg.h : header file
//

#if !defined(AFX_ELLIPTICALWINDOWDLG_H__18B3C65D_B4BF_4677_BC45_767DDC97CE9A__INCLUDED_)
#define AFX_ELLIPTICALWINDOWDLG_H__18B3C65D_B4BF_4677_BC45_767DDC97CE9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEllipticalWindowDlg dialog

class CEllipticalWindowDlg : public CDialog
{
// Construction
public:
	CEllipticalWindowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEllipticalWindowDlg)
	enum { IDD = IDD_ELLIPTICALWINDOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEllipticalWindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HRGN m_hRgn;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEllipticalWindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELLIPTICALWINDOWDLG_H__18B3C65D_B4BF_4677_BC45_767DDC97CE9A__INCLUDED_)
