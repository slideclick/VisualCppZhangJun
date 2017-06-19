// Toolbar256Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Toolbar256.h"
#include "Toolbar256Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbar256Dlg dialog

CToolbar256Dlg::CToolbar256Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolbar256Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolbar256Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolbar256Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolbar256Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolbar256Dlg, CDialog)
	//{{AFX_MSG_MAP(CToolbar256Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbar256Dlg message handlers

BOOL CToolbar256Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//创建工具栏
	m_toolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER);
	m_toolbar.LoadToolBar(IDR_TOOLBAR);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	
	CImageList imgs;
	CBitmap	 bmp;
	//创建正常模式的图片列表
	bmp.LoadBitmap(IDB_COLD);
	imgs.Create(32, 32, ILC_MASK|ILC_COLOR24, 3, 1);
	imgs.Add(&bmp, RGB(255, 255, 255));
	//将图片列表设置到工具栏
	m_toolbar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)imgs.m_hImageList);
	imgs.Detach();
	bmp.Detach();
	
	//创建鼠标处于按钮之上的图片列表
	bmp.LoadBitmap(IDB_HOT);
	imgs.Create(32, 32, ILC_MASK|ILC_COLOR24, 3, 1);
	imgs.Add(&bmp, RGB(255, 255, 255));
	//将图片列表设置到工具栏
	m_toolbar.SendMessage(TB_SETHOTIMAGELIST, 0, (LPARAM)imgs.m_hImageList);
	imgs.Detach();
	bmp.Detach(); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToolbar256Dlg::OnPaint() 
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
HCURSOR CToolbar256Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
