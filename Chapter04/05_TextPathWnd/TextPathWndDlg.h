// TextPathWndDlg.h : header file
//

#if !defined(AFX_TEXTPATHWNDDLG_H__A37618E1_E7C9_41BB_9688_E88BB969632C__INCLUDED_)
#define AFX_TEXTPATHWNDDLG_H__A37618E1_E7C9_41BB_9688_E88BB969632C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTextPathWndDlg dialog

#include "pathwnd.h"
#include "layeredwnd.h"

class CTextPathWndDlg : public CDialog
{
// Construction
public:
	CTextPathWndDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTextPathWndDlg)
	enum { IDD = IDD_TEXTPATHWND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextPathWndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPathWnd m_wndPath;
	CLayeredWnd m_wndLayered;
	HFONT m_hFont;
	CString m_str;

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTextPathWndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPATHWNDDLG_H__A37618E1_E7C9_41BB_9688_E88BB969632C__INCLUDED_)
