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
	//�ֶ�ӳ�����Ϣ
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
	
	//��ʼ������
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
	//����SOCKET
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sock == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return TRUE;
	}
	//����Ϊ�첽ģʽ
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
//��ȡ������ϸ��Ϣ�������
void CTcpClientDlg::ErrMsg(int nCode)
{
	TCHAR szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, nCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		szErr, 1024, NULL);
	_tcscat(szErr, _T("\n"));
	OutputMsg(szErr);	
}
//������ı��������Ϣ
void CTcpClientDlg::OutputMsg(LPCTSTR lpMsg)
{
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDT_RECEIVE);
	int nTotleLen = ::SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	::SendMessage(hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	::SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)lpMsg);
}
//SOCKET����Ϣ��Ӧ����
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
	//�����ѽ���
	case FD_CONNECT:
		OutputMsg(_T("�ѳɹ����ӵ�������.\n"));
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
		break;
	//�����ѹر�
	case FD_CLOSE:
		OutputMsg(_T("�����ѶϿ�.\n"));
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
		break;
	//�յ���Ϣ
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
//���Ӱ�ť����Ӧ����
void CTcpClientDlg::OnBtnConnect() 
{
	//��ȡ����Ķ˿ں�IP
	int nPort = GetDlgItemInt(IDC_EDT_PORT);
	CString strIP;
	GetDlgItemText(IDC_EDT_IP, strIP);
	//����
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = inet_addr(strIP);
	int nConn = connect(m_sock, (sockaddr *)&addr, sizeof(addr));
	if(nConn == SOCKET_ERROR)
	{
		//���첽ģʽ��WSAEWOULDBLOCK����Ϊ������������ܵ�����������
		int nErr = WSAGetLastError();
		if(nErr != WSAEWOULDBLOCK)
			ErrMsg(nErr);
	}
}
//���Ͱ�ť����Ӧ����
void CTcpClientDlg::OnBtnSend() 
{
	//��ȡ�û�����
	TCHAR szText[1024];
	GetDlgItemText(IDC_EDT_SEND, szText, 1024);
	if(*szText == 0)
		return;
	//������Ϣ
	char *p = (char *)szText;
	int nTotal = (_tcslen(szText) + 1) * sizeof(TCHAR);
	int nSend = send(m_sock, p, nTotal, 0);
	if(nSend == SOCKET_ERROR)
	{
		ErrMsg(WSAGetLastError());
		return;
	}
	OutputMsg(_T("�ı�������ϡ�\n"));
}

void CTcpClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//�ر�SOCKET
	closesocket(m_sock);
	//������
	WSACleanup();
}
