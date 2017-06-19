// ODBC_DemoView.h : interface of the CODBC_DemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODBC_DEMOVIEW_H__46761924_1733_480B_AB4C_877EF4E71C5B__INCLUDED_)
#define AFX_ODBC_DEMOVIEW_H__46761924_1733_480B_AB4C_877EF4E71C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODBC_DemoSet;

class CODBC_DemoView : public CRecordView
{
protected: // create from serialization only
	CODBC_DemoView();
	DECLARE_DYNCREATE(CODBC_DemoView)

public:
	//{{AFX_DATA(CODBC_DemoView)
	enum { IDD = IDD_ODBC_DEMO_FORM };
	CODBC_DemoSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CODBC_DemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBC_DemoView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CODBC_DemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CODBC_DemoView)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ODBC_DemoView.cpp
inline CODBC_DemoDoc* CODBC_DemoView::GetDocument()
   { return (CODBC_DemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBC_DEMOVIEW_H__46761924_1733_480B_AB4C_877EF4E71C5B__INCLUDED_)
