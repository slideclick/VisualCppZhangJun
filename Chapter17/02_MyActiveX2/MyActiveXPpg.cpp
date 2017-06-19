// MyActiveXPpg.cpp : Implementation of the CMyActiveXPropPage property page class.

#include "stdafx.h"
#include "MyActiveX.h"
#include "MyActiveXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMyActiveXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMyActiveXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMyActiveXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMyActiveXPropPage, "MYACTIVEX.MyActiveXPropPage.1",
	0x3a63c323, 0x66fa, 0x419b, 0xb8, 0x29, 0xf4, 0xe6, 0x2b, 0x8e, 0x6e, 0xa6)


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXPropPage::CMyActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMyActiveXPropPage

BOOL CMyActiveXPropPage::CMyActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MYACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXPropPage::CMyActiveXPropPage - Constructor

CMyActiveXPropPage::CMyActiveXPropPage() :
	COlePropertyPage(IDD, IDS_MYACTIVEX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMyActiveXPropPage)
	m_cycle = 0;
	m_lineWidth = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXPropPage::DoDataExchange - Moves data between page and properties

void CMyActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMyActiveXPropPage)
	DDP_Text(pDX, IDC_EDT_CYCLE, m_cycle, _T("Cycle") );
	DDX_Text(pDX, IDC_EDT_CYCLE, m_cycle);
	DDP_Text(pDX, IDC_EDT_LINEWIDTH, m_lineWidth, _T("LineWidth") );
	DDX_Text(pDX, IDC_EDT_LINEWIDTH, m_lineWidth);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXPropPage message handlers
