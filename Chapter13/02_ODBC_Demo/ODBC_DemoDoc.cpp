// ODBC_DemoDoc.cpp : implementation of the CODBC_DemoDoc class
//

#include "stdafx.h"
#include "ODBC_Demo.h"

#include "ODBC_DemoSet.h"
#include "ODBC_DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoDoc

IMPLEMENT_DYNCREATE(CODBC_DemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CODBC_DemoDoc, CDocument)
	//{{AFX_MSG_MAP(CODBC_DemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoDoc construction/destruction

CODBC_DemoDoc::CODBC_DemoDoc()
{
	// TODO: add one-time construction code here

}

CODBC_DemoDoc::~CODBC_DemoDoc()
{
}

BOOL CODBC_DemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoDoc serialization

void CODBC_DemoDoc::Serialize(CArchive& ar)
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
// CODBC_DemoDoc diagnostics

#ifdef _DEBUG
void CODBC_DemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CODBC_DemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoDoc commands
