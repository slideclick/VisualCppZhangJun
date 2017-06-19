#if !defined(AFX_PAGE1DLG_H__08B1BD56_7EEE_4A60_B1AE_DA8FDF56D961__INCLUDED_)
#define AFX_PAGE1DLG_H__08B1BD56_7EEE_4A60_B1AE_DA8FDF56D961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage1Dlg dialog

class CPage1Dlg : public CDialog
{
// Construction
public:
	CPage1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPage1Dlg)
	enum { IDD = IDD_PAGE1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPage1Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1DLG_H__08B1BD56_7EEE_4A60_B1AE_DA8FDF56D961__INCLUDED_)
