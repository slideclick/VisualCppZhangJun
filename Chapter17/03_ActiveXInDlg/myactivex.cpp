// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "myactivex.h"

/////////////////////////////////////////////////////////////////////////////
// CMyActiveX

IMPLEMENT_DYNCREATE(CMyActiveX, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CMyActiveX properties

OLE_COLOR CMyActiveX::GetForeColor()
{
	OLE_COLOR result;
	GetProperty(DISPID_FORECOLOR, VT_I4, (void*)&result);
	return result;
}

void CMyActiveX::SetForeColor(OLE_COLOR propVal)
{
	SetProperty(DISPID_FORECOLOR, VT_I4, propVal);
}

long CMyActiveX::GetLineWidth()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CMyActiveX::SetLineWidth(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

long CMyActiveX::GetCycle()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CMyActiveX::SetCycle(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMyActiveX operations

void CMyActiveX::Animate()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMyActiveX::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
