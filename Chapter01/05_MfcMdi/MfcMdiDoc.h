// MfcMdiDoc.h : interface of the CMfcMdiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMDIDOC_H__CD2C6513_95CE_49EC_AADC_6DCA2A2C18F6__INCLUDED_)
#define AFX_MFCMDIDOC_H__CD2C6513_95CE_49EC_AADC_6DCA2A2C18F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcMdiDoc : public CDocument
{
protected: // create from serialization only
	CMfcMdiDoc();
	DECLARE_DYNCREATE(CMfcMdiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcMdiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcMdiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcMdiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIDOC_H__CD2C6513_95CE_49EC_AADC_6DCA2A2C18F6__INCLUDED_)
