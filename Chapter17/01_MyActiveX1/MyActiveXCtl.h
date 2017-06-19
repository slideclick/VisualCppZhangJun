#if !defined(AFX_MYACTIVEXCTL_H__DF5D0456_D3AC_4404_848C_74227136D312__INCLUDED_)
#define AFX_MYACTIVEXCTL_H__DF5D0456_D3AC_4404_848C_74227136D312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MyActiveXCtl.h : Declaration of the CMyActiveXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl : See MyActiveXCtl.cpp for implementation.

class CMyActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMyActiveXCtrl)

// Constructor
public:
	CMyActiveXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyActiveXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CMyActiveXCtrl();

	DECLARE_OLECREATE_EX(CMyActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMyActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMyActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMyActiveXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMyActiveXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMyActiveXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMyActiveXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMyActiveXCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACTIVEXCTL_H__DF5D0456_D3AC_4404_848C_74227136D312__INCLUDED)
