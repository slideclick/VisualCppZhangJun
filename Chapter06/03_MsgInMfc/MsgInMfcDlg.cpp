// MsgInMfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MsgInMfc.h"
#include "MsgInMfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgInMfcDlg dialog

CMsgInMfcDlg::CMsgInMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgInMfcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgInMfcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsgInMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgInMfcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMsgInMfcDlg, CDialog)
	//{{AFX_MSG_MAP(CMsgInMfcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_EN_CHANGE(IDC_EDT_INPUT, OnEdtInputChange)
	ON_MESSAGE(WM_ERASEBKGND, OnEraseBackground)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgInMfcDlg message handlers

BOOL CMsgInMfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMsgInMfcDlg::OnPaint() 
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
HCURSOR CMsgInMfcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//“清空”按钮的响应函数
void CMsgInMfcDlg::OnBtnClear()
{
	//清除输入文本框中的字符
	SetDlgItemText(IDC_EDT_INPUT, _T(""));
	OnEdtInputChange();
}

//EN_CHANGE消息的响应函数
void CMsgInMfcDlg::OnEdtInputChange()
{
	//获得输入文本框句柄
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDT_INPUT);
	//获得文本框中文字的长度
	int nLen = ::SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	//显示长度到界面
	TCHAR szBuf[128] = {0};
	_stprintf(szBuf, _T("已输入：%d"), nLen);
	SetDlgItemText(IDC_LEN, szBuf);
}

//WM_ERASEBKGND消息的响应函数
void CMsgInMfcDlg::OnEraseBackground(WPARAM wp, LPARAM lp)
{
	//用自定义颜色填充窗体背景
	HDC hDC = (HDC)wp;
	RECT rc = {0};
	GetClientRect(&rc);
	HBRUSH hb = CreateSolidBrush(RGB(100, 150, 200));
	FillRect(hDC, &rc, hb);
	DeleteObject(hb);
}