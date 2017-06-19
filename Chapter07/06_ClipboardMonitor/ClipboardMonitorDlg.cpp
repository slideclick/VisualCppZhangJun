// ClipboardMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipboardMonitor.h"
#include "ClipboardMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipboardMonitorDlg dialog

CClipboardMonitorDlg::CClipboardMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipboardMonitorDlg::IDD, pParent), m_hwndNextViewer(NULL)
{
	//{{AFX_DATA_INIT(CClipboardMonitorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipboardMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipboardMonitorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipboardMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CClipboardMonitorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipboardMonitorDlg message handlers

BOOL CClipboardMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//将本窗体加入剪切板监视消息链
	m_hwndNextViewer = SetClipboardViewer(); 
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClipboardMonitorDlg::OnPaint() 
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
		//显示剪切板中内容
		DrawClipboard();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClipboardMonitorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClipboardMonitorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//从消息链移除本窗体
	ChangeClipboardChain(m_hwndNextViewer); 
}

//剪切板消息链发生变化
void CClipboardMonitorDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 
{
	CDialog::OnChangeCbChain(hWndRemove, hWndAfter);
	
	if (hWndRemove == m_hwndNextViewer) 
		m_hwndNextViewer = hWndAfter; 
	else if (m_hwndNextViewer != NULL) 
		::SendMessage(m_hwndNextViewer, WM_CHANGECBCHAIN, 
			(WPARAM)hWndRemove, (LPARAM)hWndAfter); 
	
}
//剪切板内容发生变化
void CClipboardMonitorDlg::OnDrawClipboard() 
{
	CDialog::OnDrawClipboard();
	//刷新本窗体
	InvalidateRect(NULL, TRUE);
	//将消息转发至消息链中的下一个窗体
	::SendMessage(m_hwndNextViewer, WM_DRAWCLIPBOARD, 0, 0); 
}

void CClipboardMonitorDlg::DrawClipboard()
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(m_hWnd, &ps); 
	RECT rc = {0};
	GetClientRect(&rc);
	//程序感兴趣的格式列表
	static UINT auPriorityList[] = 
	{ 
        CF_OWNERDISPLAY, 
		CF_TEXT, 
		CF_ENHMETAFILE, 
		CF_BITMAP 
    }; 
	//获取剪切板内容格式
    int nFmt = GetPriorityClipboardFormat(auPriorityList, 4); 
	//显示内容
	switch (nFmt) 
	{ 
	//自绘类型，调用其拥有者窗口显示
	case CF_OWNERDISPLAY: 
		{
			//取得剪切板数据所有者
			HWND hwndOwner = ::GetClipboardOwner(); 
			HGLOBAL hgbPs = GlobalAlloc(GMEM_MOVEABLE, sizeof(PAINTSTRUCT)); 
			LPPAINTSTRUCT pps = (LPPAINTSTRUCT)GlobalLock(hgbPs);
			memcpy(pps, &ps, sizeof(PAINTSTRUCT)); 
			GlobalUnlock(hgbPs); 
			//发送绘制消息
			::SendMessage(hwndOwner, WM_PAINTCLIPBOARD, 
				(WPARAM)m_hWnd, (LPARAM)hgbPs); 
			//释放数据
			GlobalFree(hgbPs); 
		}
		break; 
	//位图，直接绘制到窗体
	case CF_BITMAP: 
		{
			//建立兼容DC
			HDC hdcMem = CreateCompatibleDC(hdc); 
			if (hdcMem != NULL) 
			{ 
				//打开剪切板
				if (OpenClipboard()) 
				{ 
					//得到位图
					HBITMAP hBmp = (HBITMAP) GetClipboardData(nFmt); 
					HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hBmp); 
					//绘制位图
					BitBlt(hdc, 0, 0, rc.right, rc.bottom, 
						hdcMem, 0, 0, SRCCOPY); 
					SelectObject(hdcMem, hOld);
					//关闭剪切板
					CloseClipboard(); 
				} 
				DeleteDC(hdcMem); 
			} 
		}
		break; 
	//文本数据
	case CF_TEXT: 
		//打开剪切板
		if (OpenClipboard()) 
		{ 
			//得到文本
			HGLOBAL hgbText = GetClipboardData(nFmt); 
			LPCSTR lpstr = (LPCSTR)GlobalLock(hgbText); 
			//绘制文本到窗体
			DrawText(hdc, lpstr, -1, &rc, DT_LEFT); 
			//关闭数据
			GlobalUnlock(hgbText); 
			CloseClipboard(); 
		} 
		break; 
	//增强型图元文件
	case CF_ENHMETAFILE: 
		//打开剪切板
		if (OpenClipboard()) 
		{ 
			//得到内容
			HENHMETAFILE hemf = (HENHMETAFILE)GetClipboardData(nFmt); 
			//显示文件内容
			PlayEnhMetaFile(hdc, hemf, &rc); 
			//关闭剪切板
			CloseClipboard(); 
		} 
		break; 
	//没有取得内容
	case 0: 
		DrawText(hdc, _T("*剪切板上目前无数据。"), -1, 
			&rc, DT_CENTER | DT_SINGLELINE | 
			DT_VCENTER); 
		break; 
	//其他类型
	default: 
		DrawText(hdc, _T("*剪切板上的数据不可显示。"), -1, 
			&rc, 
			DT_CENTER | DT_SINGLELINE | DT_VCENTER); 
	} 
	EndPaint(&ps); 
}