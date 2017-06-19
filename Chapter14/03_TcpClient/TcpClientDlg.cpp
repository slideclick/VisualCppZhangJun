// TcpClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TcpClient.h"
#include "TcpClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTcpClientDlg dialog

CTcpClientDlg::CTcpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcpClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcpClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcpClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTcpClientDlg, CDialog)
	//{{AFX_MSG_MAP(CTcpClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	//手动映射的消息
	ON_MESSAGE(WM_USER_SOCK, OnSockNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpClientDlg message handlers

BOOL CTcpClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//初始化环境
	WSADATA wd = {0};
	int nStart = WSAStartup(MAKEWORD(SOCK_VER, 0), &wd);
	if(nStart = 0)
	{
		return 0;
	}
	if(LOBYTE(wd.wVersion) != 2)
	{
		return 0;
	}
	//创建SOCKET
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sock == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return TRUE;
	}
	//设置为异步模式
	int nSelect = WSAAsyncSelect(m_sock, m_hWnd, WM_USER_SOCK, FD_CONNECT|FD_READ|FD_CLOSE);
	if(nSelect != 0)
	{
		ErrMsg(WSAGetLastError());
		return TRUE;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTcpClientDlg::OnPaint() 
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
HCURSOR CTcpClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//获取错误详细信息，并输出
void CTcpClientDlg::ErrMsg(int nCode)
{
	TCHAR szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, nCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		szErr, 1024, NULL);
	_tcscat(szErr, _T("\n"));
	OutputMsg(szErr);	
}
//向输出文本框输出信息
void CTcpClientDlg::OutputMsg(LPCTSTR lpMsg)
{
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDT_RECEIVE);
	int nTotleLen = ::SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	::SendMessage(hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	::SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)lpMsg);
}
//SOCKET的消息响应函数
void CTcpClientDlg::OnSockNotify(WPARAM wp, LPARAM lp)
{
	int nErr = WSAGETSELECTERROR(lp);
	if(nErr != 0)
	{
		ErrMsg(nErr);
		return;
	}
	switch(WSAGETSELECTEVENT(lp)) 
	{
	//连接已建立
	case FD_CONNECT:
		OutputMsg(_T("已成功连接到服务器.\n"));
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
		break;
	//连接已关闭
	case FD_CLOSE:
		OutputMsg(_T("连接已断开.\n"));
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
		break;
	//收到信息
	case FD_READ:
		{
			TCHAR szBuf[1024] = {0};
			int nRecv = recv(m_sock, (char *)szBuf, 1024 * sizeof(TCHAR), 0);
			if(nRecv == SOCKET_ERROR)
			{
				ErrMsg(WSAGetLastError());
			}
			else
			{
				_tcscat(szBuf, _T("\n"));
				OutputMsg(szBuf);
			}
		}
		break;
	default:
		break;
	}
}
//连接按钮的响应函数
void CTcpClientDlg::OnBtnConnect() 
{
	//获取输入的端口和IP
	int nPort = GetDlgItemInt(IDC_EDT_PORT);
	CString strIP;
	GetDlgItemText(IDC_EDT_IP, strIP);
	//连接
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = inet_addr(strIP);
	int nConn = connect(m_sock, (sockaddr *)&addr, sizeof(addr));
	if(nConn == SOCKET_ERROR)
	{
		//在异步模式下WSAEWOULDBLOCK错误为正常情况，不能当错误来处理
		int nErr = WSAGetLastError();
		if(nErr != WSAEWOULDBLOCK)
			ErrMsg(nErr);
	}
}
//发送按钮的响应函数
void CTcpClientDlg::OnBtnSend() 
{
	//获取用户输入
	TCHAR szText[1024];
	GetDlgItemText(IDC_EDT_SEND, szText, 1024);
	if(*szText == 0)
		return;
	//发送信息
	char *p = (char *)szText;
	int nTotal = (_tcslen(szText) + 1) * sizeof(TCHAR);
	int nSend = send(m_sock, p, nTotal, 0);
	if(nSend == SOCKET_ERROR)
	{
		ErrMsg(WSAGetLastError());
		return;
	}
	OutputMsg(_T("文本发送完毕。\n"));
}

void CTcpClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//关闭SOCKET
	closesocket(m_sock);
	//清理环境
	WSACleanup();
}
