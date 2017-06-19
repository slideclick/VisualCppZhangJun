// PicShowDlg.h : header file
//

#if !defined(AFX_PICSHOWDLG_H__99F77D74_0B63_4ECF_9CCD_5E7BE6689368__INCLUDED_)
#define AFX_PICSHOWDLG_H__99F77D74_0B63_4ECF_9CCD_5E7BE6689368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\mymemdc.h"

/////////////////////////////////////////////////////////////////////////////
// CPicShowDlg dialog

class CPicShowDlg : public CDialog
{
// Construction
public:
	CPicShowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPicShowDlg)
	enum { IDD = IDD_PICSHOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	TCHAR m_szFile[MAX_PATH];
	CMyMemDC m_dc;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPicShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICSHOWDLG_H__99F77D74_0B63_4ECF_9CCD_5E7BE6689368__INCLUDED_)
