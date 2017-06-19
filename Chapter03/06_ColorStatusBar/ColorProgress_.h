#if !defined(AFX_COLORPROGRESS_H__0B9875DB_71F1_41B9_BC31_B2F6B5A6B61A__INCLUDED_)
#define AFX_COLORPROGRESS_H__0B9875DB_71F1_41B9_BC31_B2F6B5A6B61A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorProgress window

class CColorProgress : public CStatic
{
// Construction
public:
	CColorProgress();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorProgress)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Create(LPRECT prcWnd, COLORREF crBegin, COLOREF  crEnd);
	void SetRange(int nRange);
	virtual ~CColorProgress();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorProgress)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPROGRESS_H__0B9875DB_71F1_41B9_BC31_B2F6B5A6B61A__INCLUDED_)
