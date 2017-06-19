// RegOCXDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegOCX.h"
#include "RegOCXDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegOCXDlg dialog

CRegOCXDlg::CRegOCXDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegOCXDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegOCXDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegOCXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegOCXDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegOCXDlg, CDialog)
	//{{AFX_MSG_MAP(CRegOCXDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_REG, OnBtnReg)
	ON_BN_CLICKED(IDC_BTN_UNREG, OnBtnUnreg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegOCXDlg message handlers

BOOL CRegOCXDlg::OnInitDialog()
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

void CRegOCXDlg::OnPaint() 
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
HCURSOR CRegOCXDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“浏览”按钮的响应函数
void CRegOCXDlg::OnBtnBrowse() 
{
	//显示一个打开文件对话框，以浏览文件
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, 
		_T("*.ocx|*.ocx|*.dll|*.dll|*.*||*.*||"), this);
	if (dlg.DoModal() == IDOK) 
	{
		//将所选文件路径保存在文本框中
		SetDlgItemText(IDC_EDT_FILENAME, dlg.GetPathName());
	}
}
//“注册”按钮的响应函数
void CRegOCXDlg::OnBtnReg() 
{
	RegProc(TRUE);
}
//“注销”按钮的响应函数
void CRegOCXDlg::OnBtnUnreg() 
{
	RegProc(FALSE);
}
//实际的注册代码
BOOL CRegOCXDlg::RegProc(BOOL bReg)
{
	//获取用户输入的文件名
	TCHAR szFilename[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDT_FILENAME, szFilename, MAX_PATH);
	if(*szFilename == _T('\0'))
	{
		AfxMessageBox(_T("请输入文件名！"));
		return FALSE;
	}
	//加载文件
	BOOL bRet = FALSE;
	TCHAR szErrMsg[256] = {0};
	HINSTANCE hMod = LoadLibrary(szFilename);
	if(hMod != NULL)
	{
		//文件加载成功后，取得其注册或注销函数的地址
		FARPROC lpDllEntryPoint; 
		lpDllEntryPoint = GetProcAddress(hMod, 
			bReg?_T("DllRegisterServer"):_T("DllUnregisterServer"));	
		if(lpDllEntryPoint != NULL)
		{
			//调用函数
			HRESULT hr = ( (*lpDllEntryPoint)() );
			if(hr != S_OK)
			{
				_stprintf(szErrMsg, _T("注册/注销文件失败：0x%.8X"), hr);
				AfxMessageBox(szErrMsg);
			}
			else
			{
				AfxMessageBox(_T("注册/注销文件成功！"));
				bRet = TRUE;
			}
		}
		else
		{
			AfxMessageBox(_T("无法在该文件中找到注册函数！"));
		}
		//释放加载的模块
		FreeLibrary(hMod);
	}
	else
	{
		DWORD dwErr = GetLastError();
		_stprintf(szErrMsg, _T("加载文件失败:%d."), dwErr);
		AfxMessageBox(szErrMsg);
	}
	return bRet;
}