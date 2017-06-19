// TcpServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TcpServer.h"
#include "TcpServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTcpServerDlg dialog

CTcpServerDlg::CTcpServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcpServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcpServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcpServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTcpServerDlg, CDialog)
	//{{AFX_MSG_MAP(CTcpServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LISTEN, OnBtnListen)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	//�ֶ���ӵ���Ϣӳ��
	ON_MESSAGE(WM_USER_SOCKACCEPT, OnSockAccept)
	ON_MESSAGE(WM_USER_SOCKMSG, OnSockMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpServerDlg message handlers

BOOL CTcpServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//������ʼ��
	m_nClients = 0;
	memset(m_clients, 0, sizeof(m_clients));
	//��ʼ������
	WSADATA wd = {0};
	int nStart = WSAStartup(MAKEWORD(SOCK_VER, 0), &wd);
	if(nStart = 0)
	{
		return TRUE;
	}
	if(LOBYTE(wd.wVersion) != 2)
	{
		return TRUE;
	}
	//����SOCKET
	m_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_server == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return TRUE;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTcpServerDlg::OnPaint() 
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
HCURSOR CTcpServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//��ȡ������ϸ��Ϣ������ʾ����
void CTcpServerDlg::ErrMsg(int nCode)
{
	TCHAR szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, nCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		szErr, 1024, NULL);
	strcat(szErr, "\n");
	OutputMsg(szErr);	
}
//���ı���׷���ı�
void CTcpServerDlg::OutputMsg(LPCTSTR lpMsg)
{
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDT_RECEIVE);
	int nTotleLen = ::SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	::SendMessage(hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	::SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)lpMsg);
}
//����SOCKET����Ϣ��Ӧ
void CTcpServerDlg::OnSockAccept(WPARAM wp, LPARAM lp)
{
	int nErr = WSAGETSELECTERROR(lp);
	if(nErr != 0)
	{
		ErrMsg(nErr);
		return;
	}
	switch(WSAGETSELECTEVENT(lp)) 
	{
	//��������
	case FD_ACCEPT:
		{
			//����������
			SOCKET sock;
			sockaddr_in addr = {0};
			int nLen = sizeof(addr);
			sock = accept(m_server, (sockaddr *)&addr, &nLen);
			if(sock == INVALID_SOCKET)
			{
				ErrMsg(WSAGetLastError());
				break;
			}
			if (m_nClients >= MAX_SOCKETS - 1)
			{
				OutputMsg(_T("�������ͻ���\n"));
				closesocket(sock);
			}
			else
			{
				TCHAR szBuf[128] = {0};
				_stprintf(szBuf, _T("�¿ͻ��ˣ�%s,%d\n"), inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
				OutputMsg(szBuf);
				//������SOCKETΪ�첽ģʽ
				WSAAsyncSelect(sock, m_hWnd, WM_USER_SOCKMSG, FD_READ|FD_CLOSE);
				m_clients[m_nClients] = sock;
				//��ӵ�������
				_stprintf(szBuf, _T("%d"), m_nClients);
				CComboBox *pCmb = (CComboBox *)GetDlgItem(IDC_CMB_CLIENT);
				pCmb->AddString(szBuf);
				if(pCmb->GetCount() == 1)
				{
					pCmb->SetCurSel(0);
					GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
				}
				m_nClients ++;
			}
		}
		break;
	default:
		break;
	}
}
//�Ϳͻ���ͨѶ��SOCKET��Ϣ��Ӧ
void CTcpServerDlg::OnSockMsg(WPARAM wp, LPARAM lp)
{
	int nErr = WSAGETSELECTERROR(lp);
	if(nErr != 0)
	{
		ErrMsg(nErr);
		return;
	}
	//�ҵ���ǰSOCKET���
	int nIndex = -1;
	for(UINT i=0; i<m_nClients; i++)
	{
		if(wp == m_clients[i])
		{
			nIndex = i;
			break;
		}
	}
	ASSERT(nIndex >= 0);
	if(nIndex == -1)
	{
		return;
	}
	//������������Ϊ��ǰSOCKET
	CComboBox *pCmb = (CComboBox *)GetDlgItem(IDC_CMB_CLIENT);
	pCmb->SetCurSel(nIndex);
	//�¼�����	
	switch(WSAGETSELECTEVENT(lp)) 
	{
	//�����ѹر�
	case FD_CLOSE:
		OutputMsg(_T("�����ѶϿ�.\n"));
		m_clients[nIndex] = 0;
		break;
	//������Ϣ
	case FD_READ:
		{
			TCHAR szBuf[1024] = {0};
			int nRecv = recv(wp, (char *)szBuf, 1024 * sizeof(TCHAR), 0);
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
//�󶨰�ť����Ӧ����
void CTcpServerDlg::OnBtnListen() 
{
	//��ȡ����
	int nPort = GetDlgItemInt(IDC_EDT_PORT);
	CString str;
	GetDlgItemText(IDC_EDT_IP, str);
	//�󶨵��˿�
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = inet_addr(str);
	int nBind = bind(m_server, (sockaddr *)&addr, sizeof(addr));
	if(nBind != 0)
	{
		ErrMsg(WSAGetLastError());
		return ;
	}
	//����Ϊ�첽ģʽ
	int nSelect = WSAAsyncSelect(m_server, m_hWnd, WM_USER_SOCKACCEPT, FD_ACCEPT|FD_CLOSE);
	if(nSelect != 0)
	{
		ErrMsg(WSAGetLastError());
		return ;
	}
	//��ʼ����	
	int nRet = listen(m_server, SOMAXCONN);
	if(nRet == SOCKET_ERROR)
		ErrMsg(WSAGetLastError());
	else
	{
		OutputMsg(_T("��ʼ����...\n"));
		GetDlgItem(IDC_BTN_LISTEN)->EnableWindow(FALSE);
	}
}
//���Ͱ�ť����Ӧ����
void CTcpServerDlg::OnBtnSend() 
{
	//��ȡ��ǰ��ѡSOCKET
	CComboBox *pCmb = (CComboBox *)GetDlgItem(IDC_CMB_CLIENT);
	int nIndex = pCmb->GetCurSel();
	if(nIndex >= 0)
	{
		//��ȡ�û�����
		TCHAR szText[1024];
		GetDlgItemText(IDC_EDT_SEND, szText, 1024);
		if(*szText == 0)
			return;
		char *p = (char *)szText;
		int nTotal = (_tcslen(szText) + 1) * sizeof(TCHAR);
		//�����ı�
		int nSend = send(m_clients[nIndex], p, nTotal, 0);
		if(nSend == SOCKET_ERROR)
			ErrMsg(WSAGetLastError());
		else
			OutputMsg(_T("�ı�������ϡ�\n"));
	}
}

void CTcpServerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//�ر�SOCKET
	closesocket(m_server);
	for(UINT i=0; i<m_nClients; i++)
	{
		if(m_clients[i] > 0)
			closesocket(m_clients[i]);
	}
	//������
	WSACleanup();
}
