// MyWebProtocolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyWebProtocol.h"
#include "MyWebProtocolDlg.h"
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWebProtocolDlg dialog

CMyWebProtocolDlg::CMyWebProtocolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyWebProtocolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyWebProtocolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyWebProtocolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyWebProtocolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyWebProtocolDlg, CDialog)
	//{{AFX_MSG_MAP(CMyWebProtocolDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_REGISTER, OnBtnRegister)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWebProtocolDlg message handlers

BOOL CMyWebProtocolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//��ȡ�����в���
	LPTSTR lpCmdLine = AfxGetApp()->m_lpCmdLine;
	//�����Ƿ��в���������������У��������ͨ���������ַ����
	if(*lpCmdLine != _T('\0'))
	{
		TCHAR szMsg[1024] = {0};
		_stprintf(szMsg, _T("ͨ��������򿪣�\n����Ϊ��%s"), lpCmdLine);
		//�õ�Э��������������ʾ��Э�����ı�����
		TCHAR *p = _tcschr(lpCmdLine, _T(':'));
		ASSERT(p);
		*p = _T('\0');
		SetDlgItemText(IDC_EDT_NAME, lpCmdLine + 1);
		//������ʾ
		AfxMessageBox(szMsg);
	}
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyWebProtocolDlg::OnPaint() 
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
HCURSOR CMyWebProtocolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//ע�ᰴť����Ӧ����
void CMyWebProtocolDlg::OnBtnRegister() 
{
	TCHAR szName[MAX_PATH] = {0};
	TCHAR szErr[MAX_PATH] = {0};
	//ȡ������
	GetDlgItemText(IDC_EDT_NAME, szName, MAX_PATH);
	if(*szName == _T('\0'))
	{
		AfxMessageBox(_T("������Э�����ƣ�"));
		return;
	}
	//����ע����
	HKEY hKey;
	DWORD dwOut = 0;
	LONG lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, 
		szName, 0, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_WRITE, NULL, &hKey, &dwOut);
	if(lRet != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("��ע����ʧ�ܡ�"));
		return ;
	}
	else if(dwOut == REG_OPENED_EXISTING_KEY)
	{
		AfxMessageBox(_T("������������Ѵ��ڣ������ظ�ע�ᣡ"));
		return;
	}
	TCHAR szValue[MAX_PATH] = {0};
	DWORD dwLen;
	//����URL Protocol��ֵ
	GetModuleFileName(NULL, szValue, MAX_PATH);
	dwLen = (_tcslen(szValue) + 1) * sizeof(TCHAR);
	RegSetValueEx(hKey, _T("URL Protocol"), 0, REG_SZ, (BYTE *)szValue, dwLen);
	//����shell�Ӽ�
	HKEY hShell = NULL;
	lRet = RegCreateKeyEx(hKey, _T("shell"), 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hShell, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("������shell���Ӽ�ʱ����%0x.8X��"), lRet);
		AfxMessageBox(szErr);
		RegCloseKey(hKey);
		return;
	}
	//����open�Ӽ�
	HKEY hOpen = NULL;
	lRet = RegCreateKeyEx(hShell, _T("open"), 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hOpen, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("������open���Ӽ�ʱ����%0x.8X��"), lRet);
		AfxMessageBox(szErr);
		RegCloseKey(hShell);
		RegCloseKey(hKey);
		return;
	}
	//����command�Ӽ�
	HKEY hCmd = NULL;
	lRet = RegCreateKeyEx(hOpen, _T("command"), 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hCmd, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("������command���Ӽ�ʱ����%0x.8X��"), lRet);
		AfxMessageBox(szErr);
		RegCloseKey(hOpen);
		RegCloseKey(hShell);
		RegCloseKey(hKey);
		return;
	}
	//д���ֵ
	*szValue = _T('"');
	GetModuleFileName(NULL, szValue + 1, MAX_PATH);
	_tcscat(szValue, _T("\" \"%1\""));
	dwLen = (_tcslen(szValue) + 1) * sizeof(TCHAR);
	lRet = RegSetValueEx(hCmd, NULL, 0, REG_SZ, (BYTE *)szValue, dwLen);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("д��ע����ֵʱ��������%0x.8X��"), lRet);
		AfxMessageBox(szErr);
	}
	else
	{
		AfxMessageBox(_T("ע��ɹ���"));
	}
	//�ر�ע����ֵ
	RegCloseKey(hCmd);
	RegCloseKey(hOpen);
	RegCloseKey(hShell);
	RegCloseKey(hKey);
}
//ɾ����ť����Ӧ����
void CMyWebProtocolDlg::OnBtnDelete() 
{
	//��ȡ�û�����
	TCHAR szName[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDT_NAME, szName, MAX_PATH);
	if(*szName == _T('\0'))
	{
		AfxMessageBox(_T("������Э�����ƣ�"));
		return;
	}
	//ɾ��Э���ע���������Ӽ�
	LONG lDel = SHDeleteKey(HKEY_CLASSES_ROOT, szName);
	if(lDel == ERROR_SUCCESS)
	{
		AfxMessageBox(_T("�����ɹ���"));
	}
	else
	{
		TCHAR szErr[MAX_PATH] = {0};
		_stprintf(szErr, _T("ɾ��ע����ʱ����0x%.8X"), lDel);
		AfxMessageBox(szErr);
	}
}
