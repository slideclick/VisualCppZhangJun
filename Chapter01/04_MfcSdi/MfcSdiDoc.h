// MfcSdiDoc.h : interface of the CMfcSdiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCSDIDOC_H__81DF02FB_AE0F_484D_A580_8C6556E820DD__INCLUDED_)
#define AFX_MFCSDIDOC_H__81DF02FB_AE0F_484D_A580_8C6556E820DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcSdiDoc : public CDocument
{
protected: // create from serialization only
	CMfcSdiDoc();
	DECLARE_DYNCREATE(CMfcSdiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcSdiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcSdiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcSdiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDIDOC_H__81DF02FB_AE0F_484D_A580_8C6556E820DD__INCLUDED_)
