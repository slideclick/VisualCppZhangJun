// SendMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SendMsg.h"
#include "SendMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg dialog

CSendMsgDlg::CSendMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hCursor = NULL;
	m_bCapturing = FALSE;
	SetRect(&m_rtCtrl, 0, 0, 0, 0);
	m_hwndDest = NULL;
}

void CSendMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CSendMsgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_SETTEXT, OnBtnSettext)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg message handlers

BOOL CSendMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//加载拖动光标
	m_hCursor = LoadCursor(NULL, IDC_SIZEALL);
	//获取拖动控件的位置和大小
	GetDlgItem(IDC_CAP)->GetWindowRect(&m_rtCtrl);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSendMsgDlg::OnPaint() 
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
HCURSOR CSendMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSendMsgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//判断鼠标是否在IDC_CAP上，如果是，则设置捕获鼠标。
	if (point.x >= m_rtCtrl.left && point.x <= m_rtCtrl.right
		|| point.y >= m_rtCtrl.top && point.y <= m_rtCtrl.bottom) 
	{
		m_bCapturing = TRUE;
		SetCapture();
		SetCursor(m_hCursor);
	}
}

void CSendMsgDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//鼠标左键松开，如果处于捕获状态则做相应处理
	if(m_bCapturing)
	{
		//恢复状态
		ReleaseCapture();
		m_bCapturing = FALSE;
		//取得当前鼠标位置的窗体句柄
		POINT pt = point;
		ClientToScreen(&pt);
		m_hwndDest = ::WindowFromPoint(pt);
		//显示句柄
		TCHAR szBuf[MAX_PATH] = {0};
		_stprintf(szBuf, _T("0x%.8X"), m_hwndDest);
		SetDlgItemText(IDC_EDT_HWND, szBuf);
		//取得并显示类名
		GetClassName(m_hwndDest, szBuf, MAX_PATH);
		SetDlgItemText(IDC_EDT_CLASS, szBuf);
		//取得并显示文本
		::SendMessage(m_hwndDest, WM_GETTEXT, MAX_PATH, (LPARAM)szBuf);
		SetDlgItemText(IDC_EDT_TEXT, szBuf);
	}
}

void CSendMsgDlg::OnBtnSettext() 
{
	//设置目标窗体的文本
	CString str;
	GetDlgItemText(IDC_EDT_TEXT, str);
	::SendMessage(m_hwndDest, WM_SETTEXT, 0,  (LPARAM)(LPCTSTR)str);
}

void CSendMsgDlg::OnBtnClose() 
{
	//关闭目标窗体
	::SendMessage(m_hwndDest, WM_CLOSE, 0, 0);
}
