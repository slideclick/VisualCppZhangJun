#if !defined(AFX_MYACTIVEXCTL_H__DF5D0456_D3AC_4404_848C_74227136D312__INCLUDED_)
#define AFX_MYACTIVEXCTL_H__DF5D0456_D3AC_4404_848C_74227136D312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <objsafe.h> 

// MyActiveXCtl.h : Declaration of the CMyActiveXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl : See MyActiveXCtl.cpp for implementation.

class CMyActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMyActiveXCtrl)
	
	//新增代码,ISafeObject相关
	DECLARE_INTERFACE_MAP()
	
	BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety)
	STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) ( 
		/* [in] */ REFIID riid,
		/* [out] */ DWORD __RPC_FAR *pdwSupportedOptions,
		/* [out] */ DWORD __RPC_FAR *pdwEnabledOptions
		);
	STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) ( 
		/* [in] */ REFIID riid,
		/* [in] */ DWORD dwOptionSetMask,
		/* [in] */ DWORD dwEnabledOptions
		);
	END_INTERFACE_PART(ObjSafe);
	//ISafeObject结束
	
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
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMyActiveXCtrl)
	long m_lineWidth;
	afx_msg void OnLineWidthChanged();
	long m_cycle;
	afx_msg void OnCycleChanged();
	afx_msg void Animate();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMyActiveXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()
protected:
	BOOL m_bRunning;
	long m_nPosition;
// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMyActiveXCtrl)
	dispidLineWidth = 1L,
	dispidCycle = 2L,
	dispidAnimate = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACTIVEXCTL_H__DF5D0456_D3AC_4404_848C_74227136D312__INCLUDED)
