// AnimatedWndDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnimatedWnd.h"
#include "AnimatedWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimatedWndDlg dialog

CAnimatedWndDlg::CAnimatedWndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimatedWndDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimatedWndDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnimatedWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimatedWndDlg)
	DDX_Control(pDX, IDC_CMB_ANIMATETYPE, m_cmb_AnimateType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimatedWndDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimatedWndDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_HIDE, OnBtnHide)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimatedWndDlg message handlers

BOOL CAnimatedWndDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//获取桌面的工作区域大小
	m_dlg.Create(IDD_ANIMATED);
	RECT rect = {0};
	SystemParametersInfo(SPI_GETWORKAREA,   0,   &rect,   0);  
	//调整动画窗体到桌面右下角
	RECT rcDlg = {0};
	m_dlg.GetClientRect(&rcDlg);
	rcDlg.left = rect.right - rcDlg.right - 20;
	rcDlg.top = rect.bottom - rcDlg.bottom ;
	rcDlg.right += rcDlg.left;
	rcDlg.bottom += rcDlg.top;
	m_dlg.MoveWindow(&rcDlg, FALSE);
	//初始化输入控件
	m_cmb_AnimateType.SetCurSel(0);
	SetDlgItemText(IDC_EDT_TIME, _T("500"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnimatedWndDlg::OnPaint() 
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
HCURSOR CAnimatedWndDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAnimatedWndDlg::OnOK() 
{
	//获取输入
	int nType, nTime;
	GetInput(&nType, &nTime);
	nType |= (AW_ACTIVATE | AW_VER_NEGATIVE);
	//显示窗体
	AnimateWindow(m_dlg.GetSafeHwnd(), nTime, nType);
}

void CAnimatedWndDlg::OnBtnHide() 
{
	//获取输入
	int nType, nTime;
	GetInput(&nType, &nTime);
	nType |= (AW_HIDE | AW_VER_POSITIVE);
	//隐藏窗体
	AnimateWindow(m_dlg.GetSafeHwnd(), nTime, nType);
}

void CAnimatedWndDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	m_dlg.DestroyWindow();
}

void CAnimatedWndDlg::GetInput(int *nAnimateType, int *nTime)
{
	//获取时间输入
	*nTime = GetDlgItemInt(IDC_EDT_TIME, NULL, FALSE);
	if (*nTime < 200) 
		*nTime = 200;
	//获取动画方式
	switch(m_cmb_AnimateType.GetCurSel())
	{
	case 1:
		*nAnimateType = AW_SLIDE;
		break;
	case 2:
		*nAnimateType = AW_BLEND;
		break;
	case 3:
		*nAnimateType = AW_CENTER;
		break;
	default:
		*nAnimateType = 0;
		break;
	}
}
