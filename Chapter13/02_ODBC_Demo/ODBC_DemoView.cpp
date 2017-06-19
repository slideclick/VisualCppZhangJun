// ODBC_DemoView.cpp : implementation of the CODBC_DemoView class
//

#include "stdafx.h"
#include "ODBC_Demo.h"

#include "ODBC_DemoSet.h"
#include "ODBC_DemoDoc.h"
#include "ODBC_DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoView

IMPLEMENT_DYNCREATE(CODBC_DemoView, CRecordView)

BEGIN_MESSAGE_MAP(CODBC_DemoView, CRecordView)
	//{{AFX_MSG_MAP(CODBC_DemoView)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoView construction/destruction

CODBC_DemoView::CODBC_DemoView()
	: CRecordView(CODBC_DemoView::IDD)
{
	//{{AFX_DATA_INIT(CODBC_DemoView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CODBC_DemoView::~CODBC_DemoView()
{
}

void CODBC_DemoView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CODBC_DemoView)
	DDX_FieldText(pDX, IDC_EDT_ID, m_pSet->m_StudentID, m_pSet);
	DDX_FieldText(pDX, IDC_EDT_NAME, m_pSet->m_StudentName, m_pSet);
	DDV_MaxChars(pDX, m_pSet->m_StudentName, 32);
	//}}AFX_DATA_MAP
}

BOOL CODBC_DemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CODBC_DemoView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_oDBC_DemoSet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoView printing

BOOL CODBC_DemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CODBC_DemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CODBC_DemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoView diagnostics

#ifdef _DEBUG
void CODBC_DemoView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CODBC_DemoView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CODBC_DemoDoc* CODBC_DemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODBC_DemoDoc)));
	return (CODBC_DemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoView database support
CRecordset* CODBC_DemoView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoView message handlers

//添加当前文本框内的数据到数据库
void CODBC_DemoView::OnBtnAdd() 
{
	//在数据集中添加新记录
	m_pSet->AddNew();
	//将文本框中内容更新到数据集
	UpdateData(TRUE);
	//将新数据添加到数据库
	m_pSet->Update();
	//移动记录到最后
	m_pSet->MoveLast();
	//更新界面
	UpdateData(FALSE);
}
//修改当前记录
void CODBC_DemoView::OnBtnEdit() 
{
	//设置修改模式
	m_pSet->Edit();
	//将文本框中内容更新到数据集
	UpdateData(TRUE);
	//将数据集中的内容更新到数据库
	m_pSet->Update();
}
//删除当前记录
void CODBC_DemoView::OnBtnDelete() 
{
	//删除数据集中的当前记录
	m_pSet->Delete();
	//移动当前记录到首条记录
	m_pSet->MoveFirst();
	//更新界面
	UpdateData(FALSE);
}
