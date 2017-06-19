// MfcMdiView.cpp : implementation of the CMfcMdiView class
//

#include "stdafx.h"
#include "MfcMdi.h"

#include "MfcMdiDoc.h"
#include "MfcMdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiView

IMPLEMENT_DYNCREATE(CMfcMdiView, CEditView)

BEGIN_MESSAGE_MAP(CMfcMdiView, CEditView)
	//{{AFX_MSG_MAP(CMfcMdiView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiView construction/destruction

CMfcMdiView::CMfcMdiView()
{
	// TODO: add construction code here

}

CMfcMdiView::~CMfcMdiView()
{
}

BOOL CMfcMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiView drawing

void CMfcMdiView::OnDraw(CDC* pDC)
{
	CMfcMdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiView printing

BOOL CMfcMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMfcMdiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMfcMdiView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiView diagnostics

#ifdef _DEBUG
void CMfcMdiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMfcMdiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMfcMdiDoc* CMfcMdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcMdiDoc)));
	return (CMfcMdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiView message handlers
