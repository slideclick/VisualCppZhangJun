#if !defined(AFX_MYACTIVEXPPG_H__304F1F3F_B76A_4A43_B727_546A4F80BF77__INCLUDED_)
#define AFX_MYACTIVEXPPG_H__304F1F3F_B76A_4A43_B727_546A4F80BF77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MyActiveXPpg.h : Declaration of the CMyActiveXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMyActiveXPropPage : See MyActiveXPpg.cpp.cpp for implementation.

class CMyActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMyActiveXPropPage)
	DECLARE_OLECREATE_EX(CMyActiveXPropPage)

// Constructor
public:
	CMyActiveXPropPage();

// Dialog Data
	//{{AFX_DATA(CMyActiveXPropPage)
	enum { IDD = IDD_PROPPAGE_MYACTIVEX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMyActiveXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACTIVEXPPG_H__304F1F3F_B76A_4A43_B727_546A4F80BF77__INCLUDED)
