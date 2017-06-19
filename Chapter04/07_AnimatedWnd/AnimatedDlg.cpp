// AnimatedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnimatedWnd.h"
#include "AnimatedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimatedDlg dialog


CAnimatedDlg::CAnimatedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimatedDlg::IDD, pParent), m_hb(NULL)
{
	//{{AFX_DATA_INIT(CAnimatedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAnimatedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimatedDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimatedDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimatedDlg)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimatedDlg message handlers

HBRUSH CAnimatedDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor ==CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		//修改对话框和Static控件的背景色
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return m_hb;
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}

BOOL CAnimatedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//创建一个蓝色的画刷
	m_hb = CreateSolidBrush(RGB(0, 0, 127));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnimatedDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DeleteObject(m_hb);
	
}
