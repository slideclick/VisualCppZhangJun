// MfcSdiView.cpp : implementation of the CMfcSdiView class
//

#include "stdafx.h"
#include "MfcSdi.h"

#include "MfcSdiDoc.h"
#include "MfcSdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiView

IMPLEMENT_DYNCREATE(CMfcSdiView, CFormView)

BEGIN_MESSAGE_MAP(CMfcSdiView, CFormView)
	//{{AFX_MSG_MAP(CMfcSdiView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiView construction/destruction

CMfcSdiView::CMfcSdiView()
	: CFormView(CMfcSdiView::IDD)
{
	//{{AFX_DATA_INIT(CMfcSdiView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMfcSdiView::~CMfcSdiView()
{
}

void CMfcSdiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcSdiView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CMfcSdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMfcSdiView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiView printing

BOOL CMfcSdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMfcSdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMfcSdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMfcSdiView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiView diagnostics

#ifdef _DEBUG
void CMfcSdiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMfcSdiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMfcSdiDoc* CMfcSdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcSdiDoc)));
	return (CMfcSdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiView message handlers
