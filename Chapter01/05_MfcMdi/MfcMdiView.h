// MfcMdiView.h : interface of the CMfcMdiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMDIVIEW_H__B8F4DD42_5AE7_4FE9_89DA_0F1C3BD664B9__INCLUDED_)
#define AFX_MFCMDIVIEW_H__B8F4DD42_5AE7_4FE9_89DA_0F1C3BD664B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcMdiView : public CEditView
{
protected: // create from serialization only
	CMfcMdiView();
	DECLARE_DYNCREATE(CMfcMdiView)

// Attributes
public:
	CMfcMdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcMdiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcMdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcMdiView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MfcMdiView.cpp
inline CMfcMdiDoc* CMfcMdiView::GetDocument()
   { return (CMfcMdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIVIEW_H__B8F4DD42_5AE7_4FE9_89DA_0F1C3BD664B9__INCLUDED_)
