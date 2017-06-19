 // MyActiveXCtl.cpp : Implementation of the CMyActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "MyActiveX.h"
#include "MyActiveXCtl.h"
#include "MyActiveXPpg.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMyActiveXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMyActiveXCtrl, COleControl)
	//{{AFX_MSG_MAP(CMyActiveXCtrl)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMyActiveXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMyActiveXCtrl)
	DISP_PROPERTY_NOTIFY(CMyActiveXCtrl, "LineWidth", m_lineWidth, OnLineWidthChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CMyActiveXCtrl, "Cycle", m_cycle, OnCycleChanged, VT_I4)
	DISP_FUNCTION(CMyActiveXCtrl, "Animate", Animate, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMyActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMyActiveXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMyActiveXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMyActiveXCtrl, 1)
	PROPPAGEID(CMyActiveXPropPage::guid)
END_PROPPAGEIDS(CMyActiveXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMyActiveXCtrl, "MYACTIVEX.MyActiveXCtrl.1",
	0xbf4c592b, 0x6856, 0x4c01, 0x90, 0xb8, 0x75, 0xb8, 0x15, 0x5f, 0x5d, 0x96)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMyActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMyActiveX =
		{ 0x13f160d, 0x32cc, 0x4e2f, { 0x85, 0xd3, 0xf5, 0x1, 0xd8, 0x99, 0x5d, 0xff } };
const IID BASED_CODE IID_DMyActiveXEvents =
		{ 0xf30cb948, 0x15b6, 0x4f24, { 0xa3, 0xbd, 0x1e, 0xab, 0x33, 0x29, 0xfc, 0x5d } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMyActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMyActiveXCtrl, IDS_MYACTIVEX, _dwMyActiveXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::CMyActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMyActiveXCtrl

BOOL CMyActiveXCtrl::CMyActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MYACTIVEX,
			IDB_MYACTIVEX,
			afxRegApartmentThreading,
			_dwMyActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::CMyActiveXCtrl - Constructor

CMyActiveXCtrl::CMyActiveXCtrl()
{
	InitializeIIDs(&IID_DMyActiveX, &IID_DMyActiveXEvents);
	//变量初始化
	m_bRunning = FALSE;
	m_nPosition = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::~CMyActiveXCtrl - Destructor

CMyActiveXCtrl::~CMyActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::OnDraw - Drawing function

void CMyActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	//清空DC
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//取得前景色
	OLE_COLOR crOleFore = GetForeColor();
	//将颜色转换为GDI颜色
	COLORREF crFore = TranslateColor(crOleFore);
	//用指定宽度和颜色创建画笔
	CPen pen;
	pen.CreatePen(PS_SOLID, m_lineWidth, crFore);
	CPen *pOldPen = pdc->SelectObject(&pen);
	//循环绘制曲线
	int nBase = rcBounds.bottom / 2;
	const double PI = 3.1415926;
	double x, y;
	POINT ptLast, ptNow;
	for(int i=0; i<rcBounds.right; i++)
	{
		x = PI * 2 * (i + m_nPosition) / m_cycle ;
		y = nBase - sin(x) * rcBounds.bottom / 2;
		ptNow.x = i;
		ptNow.y = y;
		if(i > 0)
		{
			pdc->MoveTo(ptLast);
			pdc->LineTo(ptNow);
		}
		else
		{
			ptLast.x = 0;
			ptLast.y = nBase;
		}
		ptLast = ptNow;
	}
	//恢复DC原状
	pdc->SelectObject(pOldPen);
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::DoPropExchange - Persistence support

void CMyActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	//自定义属性的存储代码
	PX_Long(pPX, _T("LineWidth"), m_lineWidth, 1);
	PX_Long(pPX, _T("Cycle"), m_cycle, 100);
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::OnResetState - Reset control to default state

void CMyActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl::AboutBox - Display an "About" box to the user

void CMyActiveXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MYACTIVEX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMyActiveXCtrl message handlers

void CMyActiveXCtrl::OnLineWidthChanged() 
{
	//LineWidth属性改变
	InvalidateControl();
	SetModifiedFlag();
}
void CMyActiveXCtrl::OnCycleChanged() 
{
	//Cycle属性改变
	InvalidateControl();
	SetModifiedFlag();
}
//WM_TIMER消息响应函数
void CMyActiveXCtrl::OnTimer(UINT nIDEvent) 
{
	//位移
	m_nPosition ++;
	//重绘控件
	InvalidateControl();	
	COleControl::OnTimer(nIDEvent);
}
//控件外部方法，使图形滚动或停止
void CMyActiveXCtrl::Animate() 
{
	if(m_bRunning)
	{
		KillTimer(1);
		m_bRunning = FALSE;
	}
	else
	{
		SetTimer(1, 200, NULL);
		m_bRunning = TRUE;
	}
}
