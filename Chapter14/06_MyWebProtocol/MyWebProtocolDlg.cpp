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
	//获取命令行参数
	LPTSTR lpCmdLine = AfxGetApp()->m_lpCmdLine;
	//看看是否有参数传进来，如果有，则代表是通过浏览器地址栏打开
	if(*lpCmdLine != _T('\0'))
	{
		TCHAR szMsg[1024] = {0};
		_stprintf(szMsg, _T("通过浏览器打开，\n参数为：%s"), lpCmdLine);
		//得到协议名，并将其显示在协议名文本框中
		TCHAR *p = _tcschr(lpCmdLine, _T(':'));
		ASSERT(p);
		*p = _T('\0');
		SetDlgItemText(IDC_EDT_NAME, lpCmdLine + 1);
		//弹出提示
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
//注册按钮的响应函数
void CMyWebProtocolDlg::OnBtnRegister() 
{
	TCHAR szName[MAX_PATH] = {0};
	TCHAR szErr[MAX_PATH] = {0};
	//取得输入
	GetDlgItemText(IDC_EDT_NAME, szName, MAX_PATH);
	if(*szName == _T('\0'))
	{
		AfxMessageBox(_T("请输入协议名称！"));
		return;
	}
	//创建注册表键
	HKEY hKey;
	DWORD dwOut = 0;
	LONG lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, 
		szName, 0, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_WRITE, NULL, &hKey, &dwOut);
	if(lRet != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("打开注册表键失败。"));
		return ;
	}
	else if(dwOut == REG_OPENED_EXISTING_KEY)
	{
		AfxMessageBox(_T("所输入的名称已存在，不能重复注册！"));
		return;
	}
	TCHAR szValue[MAX_PATH] = {0};
	DWORD dwLen;
	//创建URL Protocol键值
	GetModuleFileName(NULL, szValue, MAX_PATH);
	dwLen = (_tcslen(szValue) + 1) * sizeof(TCHAR);
	RegSetValueEx(hKey, _T("URL Protocol"), 0, REG_SZ, (BYTE *)szValue, dwLen);
	//创建shell子键
	HKEY hShell = NULL;
	lRet = RegCreateKeyEx(hKey, _T("shell"), 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hShell, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("创建‘shell’子键时错误：%0x.8X！"), lRet);
		AfxMessageBox(szErr);
		RegCloseKey(hKey);
		return;
	}
	//创建open子键
	HKEY hOpen = NULL;
	lRet = RegCreateKeyEx(hShell, _T("open"), 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hOpen, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("创建‘open’子键时错误：%0x.8X！"), lRet);
		AfxMessageBox(szErr);
		RegCloseKey(hShell);
		RegCloseKey(hKey);
		return;
	}
	//创建command子键
	HKEY hCmd = NULL;
	lRet = RegCreateKeyEx(hOpen, _T("command"), 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hCmd, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("创建‘command’子键时错误：%0x.8X！"), lRet);
		AfxMessageBox(szErr);
		RegCloseKey(hOpen);
		RegCloseKey(hShell);
		RegCloseKey(hKey);
		return;
	}
	//写入键值
	*szValue = _T('"');
	GetModuleFileName(NULL, szValue + 1, MAX_PATH);
	_tcscat(szValue, _T("\" \"%1\""));
	dwLen = (_tcslen(szValue) + 1) * sizeof(TCHAR);
	lRet = RegSetValueEx(hCmd, NULL, 0, REG_SZ, (BYTE *)szValue, dwLen);
	if(lRet != ERROR_SUCCESS)
	{
		_stprintf(szErr, _T("写入注册表键值时发生错误：%0x.8X！"), lRet);
		AfxMessageBox(szErr);
	}
	else
	{
		AfxMessageBox(_T("注册成功！"));
	}
	//关闭注册表键值
	RegCloseKey(hCmd);
	RegCloseKey(hOpen);
	RegCloseKey(hShell);
	RegCloseKey(hKey);
}
//删除按钮的响应函数
void CMyWebProtocolDlg::OnBtnDelete() 
{
	//获取用户输入
	TCHAR szName[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDT_NAME, szName, MAX_PATH);
	if(*szName == _T('\0'))
	{
		AfxMessageBox(_T("请输入协议名称！"));
		return;
	}
	//删除协议的注册表键及其子键
	LONG lDel = SHDeleteKey(HKEY_CLASSES_ROOT, szName);
	if(lDel == ERROR_SUCCESS)
	{
		AfxMessageBox(_T("操作成功！"));
	}
	else
	{
		TCHAR szErr[MAX_PATH] = {0};
		_stprintf(szErr, _T("删除注册表键时错误：0x%.8X"), lDel);
		AfxMessageBox(szErr);
	}
}
