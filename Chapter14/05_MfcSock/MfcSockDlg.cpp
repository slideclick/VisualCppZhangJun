// MfcSockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcSock.h"
#include "MfcSockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcSockDlg dialog

CMfcSockDlg::CMfcSockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcSockDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMfcSockDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcSockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcSockDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfcSockDlg, CDialog)
	//{{AFX_MSG_MAP(CMfcSockDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcSockDlg message handlers

BOOL CMfcSockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//建立SOCKET
	if(!m_sock.Create(0, SOCK_STREAM, FD_READ|FD_CONNECT|FD_CLOSE))
	{
		TCHAR szBuf[256] = {0};
		_stprintf(szBuf, _T("创建Socket时错误：0x%.8X。"), m_sock.GetLastError());
		OutputMsg(szBuf);
	}
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMfcSockDlg::OnPaint() 
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
HCURSOR CMfcSockDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//向文本框追加文本
void CMfcSockDlg::OutputMsg(LPCTSTR lpMsg)
{
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDT_OUTPUT);
	int nTotleLen = ::SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	::SendMessage(hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	::SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)lpMsg);
}
//连接按钮的消息响应函数
void CMfcSockDlg::OnBtnConnect() 
{
	//获取输入的端口和IP
	int nPort = GetDlgItemInt(IDC_EDT_PORT);
	CString strIP;
	GetDlgItemText(IDC_EDT_IP, strIP);
	//连接
	m_sock.Connect(strIP, nPort);
}
//发送按钮的响应函数
void CMfcSockDlg::OnBtnSend() 
{
	//获取用户输入
	TCHAR szText[1024];
	GetDlgItemText(IDC_EDT_INPUT, szText, 1024);
	if(*szText == 0)
		return;
	//发送信息
	char *p = (char *)szText;
	int nTotal = (_tcslen(szText) + 1) * sizeof(TCHAR);
	int nSend = m_sock.Send(p, nTotal, 0);
	if(nSend == SOCKET_ERROR)
	{
		_stprintf(szText, _T("发送文本时错误：0x%.8X"), m_sock.GetLastError());
		OutputMsg(szText);
	}
	else
		OutputMsg(_T("文本发送完毕。\n"));
}
