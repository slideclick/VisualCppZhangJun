// MfcSdiDoc.cpp : implementation of the CMfcSdiDoc class
//

#include "stdafx.h"
#include "MfcSdi.h"

#include "MfcSdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiDoc

IMPLEMENT_DYNCREATE(CMfcSdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcSdiDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcSdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiDoc construction/destruction

CMfcSdiDoc::CMfcSdiDoc()
{
	// TODO: add one-time construction code here

}

CMfcSdiDoc::~CMfcSdiDoc()
{
}

BOOL CMfcSdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMfcSdiDoc serialization

void CMfcSdiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiDoc diagnostics

#ifdef _DEBUG
void CMfcSdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcSdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiDoc commands
