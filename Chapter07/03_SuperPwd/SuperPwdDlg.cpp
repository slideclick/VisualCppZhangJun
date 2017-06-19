// SuperPwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperPwd.h"
#include "SuperPwdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperPwdDlg dialog

CSuperPwdDlg::CSuperPwdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperPwdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperPwdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CSuperPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperPwdDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSuperPwdDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperPwdDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperPwdDlg message handlers

BOOL CSuperPwdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//用当前时间初始化种子
	m_nSeed = time(0);
	SetDlgItemInt(IDC_EDT_SEED, m_nSeed, FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSuperPwdDlg::OnPaint() 
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
HCURSOR CSuperPwdDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//生成随机密码
void CSuperPwdDlg::OnOK() 
{
	TCHAR szPwd[10] = {0};
	//初始化随机数序列
	srand(m_nSeed);
	//循环得到8个随机数，并将其换算到合适的范围得到响应的字母
	for(int i=0; i<8; i++)
	{
		szPwd[i] = _T('A') + rand() % (_T('Z') - _T('A') + 1);
	}
	//输出结果
	SetDlgItemText(IDC_EDT_PWD, szPwd);
}
//随机化种子
void CSuperPwdDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(point.x == 0 || point.y == 0)
		return;
	//利用鼠标坐标对种子进行运算
	UINT nNewSeed = m_nSeed * point.x * point.y;
	if(nNewSeed == 0)
	{
		m_nSeed /= (point.x * point.y);
	}
	else
	{
		m_nSeed = nNewSeed;
	}
	if(m_nSeed <= 1)
		m_nSeed = time(0);
	SetDlgItemInt(IDC_EDT_SEED, m_nSeed, FALSE);
}
