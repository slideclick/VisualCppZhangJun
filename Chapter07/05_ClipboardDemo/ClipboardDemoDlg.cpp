// ClipboardDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipboardDemo.h"
#include "ClipboardDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef UNICODE
  #define CT_TCHAR CF_UNICODETEXT
#else
  #define CT_TCHAR CF_TEXT
#endif //#ifdef UNICODE

/////////////////////////////////////////////////////////////////////////////
// CClipboardDemoDlg dialog

CClipboardDemoDlg::CClipboardDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipboardDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClipboardDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipboardDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipboardDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipboardDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClipboardDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EMPTY, OnBtnEmpty)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipboardDemoDlg message handlers

BOOL CClipboardDemoDlg::OnInitDialog()
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

void CClipboardDemoDlg::OnPaint() 
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
HCURSOR CClipboardDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//向剪切板写入文本
void CClipboardDemoDlg::OnBtnSet() 
{
	//读取输入的文本
	CString str;
	GetDlgItemText(IDC_EDT_INPUT, str);
	if(str.GetLength() == 0)
	{
		SetDlgItemText(IDC_STATUS, _T("请先输入一些字符。"));
		return;
	}
	//打开剪切板
	if(OpenClipboard())
	{
		//分配一块可跨进程访问的内存
		int nLen = (str.GetLength() + 1) * sizeof(TCHAR);
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nLen);
		//锁定内存并获得内存首字节指针
		LPTSTR pText = (LPTSTR)GlobalLock(hGlobal);
		//将文本复制到该内存
		_tcscpy(pText, str);
		//解锁内存
		GlobalUnlock(hGlobal);
		//将数据内存指针放置到剪切板
		SetClipboardData(CT_TCHAR, hGlobal);
		//关闭剪切板
		CloseClipboard();
		SetDlgItemText(IDC_STATUS, _T("文本已成功写入剪切板。"));
	}
	else
	{
		SetDlgItemText(IDC_STATUS, _T("打开剪切板失败。"));
	}
}
//读取剪切板上的文本
void CClipboardDemoDlg::OnBtnGet() 
{
	SetDlgItemText(IDC_EDT_INPUT, NULL);
	//打开剪切板
	if(OpenClipboard())
	{
		//尝试从剪切板获取文本型的数据
		HGLOBAL hGlobal = GetClipboardData(CT_TCHAR);
		//锁定内存
		LPCSTR lpText = (LPCSTR)GlobalLock(hGlobal);
		if(lpText)
		{
			//有文本，显示
			SetDlgItemText(IDC_EDT_INPUT, lpText);
			SetDlgItemText(IDC_STATUS, _T("成功获取到文本。"));
		}
		else
		{
			//无文本数据
			SetDlgItemText(IDC_STATUS, _T("剪切板上无文本数据。"));
		}
		GlobalUnlock(hGlobal);
		//关闭剪切板
		CloseClipboard();
	}
	else
	{
		SetDlgItemText(IDC_STATUS, _T("打开剪切板失败。"));
	}
}

void CClipboardDemoDlg::OnBtnEmpty() 
{
	//打开剪切板
	if(OpenClipboard())
	{
		//清空，并关闭剪切板
		EmptyClipboard();
		CloseClipboard();
		SetDlgItemText(IDC_STATUS, _T("剪切板已清空。"));
	}
	else
	{
		SetDlgItemText(IDC_STATUS, _T("打开剪切板失败。"));
	}
}

void CClipboardDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}
