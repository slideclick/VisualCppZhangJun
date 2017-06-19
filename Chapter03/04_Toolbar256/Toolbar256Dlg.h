// Toolbar256Dlg.h : header file
//

#if !defined(AFX_TOOLBAR256DLG_H__8557F267_9109_4BE4_8EFB_80667425BFD6__INCLUDED_)
#define AFX_TOOLBAR256DLG_H__8557F267_9109_4BE4_8EFB_80667425BFD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolbar256Dlg dialog

class CToolbar256Dlg : public CDialog
{
// Construction
public:
	CToolbar256Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CToolbar256Dlg)
	enum { IDD = IDD_TOOLBAR256_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbar256Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar	m_toolbar;	//¹¤¾ßÀ¸
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CToolbar256Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBAR256DLG_H__8557F267_9109_4BE4_8EFB_80667425BFD6__INCLUDED_)
