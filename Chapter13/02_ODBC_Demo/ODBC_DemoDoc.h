// ODBC_DemoDoc.h : interface of the CODBC_DemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODBC_DEMODOC_H__F8580F85_D945_4B0B_A577_486844484C3C__INCLUDED_)
#define AFX_ODBC_DEMODOC_H__F8580F85_D945_4B0B_A577_486844484C3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ODBC_DemoSet.h"


class CODBC_DemoDoc : public CDocument
{
protected: // create from serialization only
	CODBC_DemoDoc();
	DECLARE_DYNCREATE(CODBC_DemoDoc)

// Attributes
public:
	CODBC_DemoSet m_oDBC_DemoSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBC_DemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CODBC_DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CODBC_DemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBC_DEMODOC_H__F8580F85_D945_4B0B_A577_486844484C3C__INCLUDED_)
