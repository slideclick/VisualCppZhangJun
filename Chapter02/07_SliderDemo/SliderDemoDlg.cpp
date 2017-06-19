// SliderDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SliderDemo.h"
#include "SliderDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliderDemoDlg dialog

CSliderDemoDlg::CSliderDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSliderDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSliderDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSliderDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSliderDemoDlg)
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSliderDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSliderDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliderDemoDlg message handlers

BOOL CSliderDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//设置滑块的滑动范围
	m_slider.SetRange(0, 100, FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSliderDemoDlg::OnPaint() 
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
HCURSOR CSliderDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSliderDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//获得滑块当前值
	TCHAR szOutput[128] = {0};
	_stprintf(szOutput, _T("当前值：%d"), m_slider.GetPos());
	//输出当前值到界面上
	SetDlgItemText(IDC_OUTPUT, szOutput);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
