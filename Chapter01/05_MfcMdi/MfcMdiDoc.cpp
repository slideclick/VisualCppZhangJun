// MfcMdiDoc.cpp : implementation of the CMfcMdiDoc class
//

#include "stdafx.h"
#include "MfcMdi.h"

#include "MfcMdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiDoc

IMPLEMENT_DYNCREATE(CMfcMdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcMdiDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcMdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiDoc construction/destruction

CMfcMdiDoc::CMfcMdiDoc()
{
	// TODO: add one-time construction code here

}

CMfcMdiDoc::~CMfcMdiDoc()
{
}

BOOL CMfcMdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMfcMdiDoc serialization

void CMfcMdiDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiDoc diagnostics

#ifdef _DEBUG
void CMfcMdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcMdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiDoc commands
