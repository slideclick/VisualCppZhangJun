// MfcSdiView.h : interface of the CMfcSdiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCSDIVIEW_H__119F5C8C_75AF_49B9_BD48_EBF75BD803BF__INCLUDED_)
#define AFX_MFCSDIVIEW_H__119F5C8C_75AF_49B9_BD48_EBF75BD803BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcSdiView : public CFormView
{
protected: // create from serialization only
	CMfcSdiView();
	DECLARE_DYNCREATE(CMfcSdiView)

public:
	//{{AFX_DATA(CMfcSdiView)
	enum{ IDD = IDD_MFCSDI_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CMfcSdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcSdiView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcSdiView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MfcSdiView.cpp
inline CMfcSdiDoc* CMfcSdiView::GetDocument()
   { return (CMfcSdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDIVIEW_H__119F5C8C_75AF_49B9_BD48_EBF75BD803BF__INCLUDED_)
