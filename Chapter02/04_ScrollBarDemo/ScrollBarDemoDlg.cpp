// ScrollBarDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollBarDemo.h"
#include "ScrollBarDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDemoDlg dialog

CScrollBarDemoDlg::CScrollBarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollBarDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollBarDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScrollBarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollBarDemoDlg)
	DDX_Control(pDX, IDC_SCROLL, m_scroll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScrollBarDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollBarDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDemoDlg message handlers

BOOL CScrollBarDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//初始化滚动条控件
	SCROLLINFO si = {0};
	si.cbSize = sizeof(si);
	//要设置控件的滚动范围和每页大小
	si.fMask = SIF_RANGE | SIF_PAGE;
	//最小值为0
	si.nMin = 0;
	//最大值为100
	si.nMax = 100;
	//每页大小为10
	si.nPage = 10;
	//将信息设置到控件
	m_scroll.SetScrollInfo(&si);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScrollBarDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScrollBarDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScrollBarDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//取得滚动条控件当前状态
	SCROLLINFO si = {0};
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	pScrollBar->GetScrollInfo(&si);
	int nNewPos = si.nPos;
	//处理消息
	switch(nSBCode)
	{
	//用户拖动了滚动条，参数nPos即是滑块的新位置
	case SB_THUMBTRACK:
		nNewPos = nPos;
		break;
	//单击了左箭头，滑块位置向左移动一个单元
	case SB_LINELEFT:
		nNewPos -= 1;
		break;
	//单击了右箭头，滑块位置向右移动一个单元
	case SB_LINERIGHT:
		nNewPos += 1;
		break;
	//向左翻页
	case SB_PAGELEFT:
		nNewPos -= si.nPage;
		break;
	//向右翻页
	case SB_PAGERIGHT:
		nNewPos += si.nPage;
		break;
	default:
		break;
	}
	//将新位置设置到控件
	if(nNewPos > si.nMax)
		nNewPos = si.nMax;
	if(nNewPos < si.nMin)
		nNewPos = si.nMin;
	pScrollBar->SetScrollPos(nNewPos);
	//显示新位置
	TCHAR szOutput[128] = {0};
	_stprintf(szOutput, _T("当前：%d"), nNewPos);
	SetDlgItemText(IDC_POS, szOutput);
}
