// WideTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WideText.h"
#include "WideTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWideTextDlg dialog

CWideTextDlg::CWideTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWideTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWideTextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWideTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWideTextDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWideTextDlg, CDialog)
	//{{AFX_MSG_MAP(CWideTextDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWideTextDlg message handlers

BOOL CWideTextDlg::OnInitDialog()
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

void CWideTextDlg::OnPaint() 
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
HCURSOR CWideTextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWideTextDlg::OnOpen() 
{
	//选择要打开的文件
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.txt|*.txt||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//打开文件
	CFile file;	
	if(!file.Open(dlg.GetPathName(), CFile::modeRead))
		return;
	//分配一个缓冲区，因为Unicode一个字符占2个字节，
	//为了确保字符串后有一个正确的结尾字符0，这里要多分配2个字节
	DWORD dwLen = file.GetLength();
	byte *pBuf = new byte[dwLen + 2];
	byte *pTemp = pBuf;
	ZeroMemory(pBuf, dwLen + 2);
	//将文件内容读取至缓冲区
	file.ReadHuge(pBuf, dwLen);
	//判断是否有Unicode标志
	BOOL bWide = FALSE;
	if(dwLen > 2 && pBuf[0] == 0xFF && pBuf[1] == 0xFE)
	{
		//如果有Unicode标志，则确定是Unicode字符
		bWide = TRUE;
		//从字符串中排除标志，因为这2个字节不是字符串成员
		pTemp += 2;
	}
	else
	{
		//如果没有明确的标志，用API函数进行猜测判断，其结果不能确保正确
		bWide = IsTextUnicode(pBuf, dwLen, NULL);
	}

	//如果没有定义UNICODE宏，文本框只接受Ansi字符串
#ifndef UNICODE
	//如果文本是Unicode字符串，则要先转换为Ansi字符串
	if(bWide)
	{
		//分配一个Ansi字符串缓冲区
		char *pBufA = new char[dwLen + 1];
		ZeroMemory(pBufA, dwLen + 1);
		//Unicode字符串到Ansi字符串转换
		WideCharToMultiByte(CP_ACP, 0, (WCHAR *)pTemp, -1, pBufA, dwLen, NULL, NULL);
		//本文显示到文本框
		SetDlgItemText(IDC_TEXT, pBufA);
		//释放缓冲区
		delete []pBufA;
	}
	//如果文本不是Unicode字符串，则直接显示
	else
	{
		SetDlgItemText(IDC_TEXT, (char *)pBuf);
	}
	//如果定义了UNICODE宏，文本框只接受Unicode字符串
#else
	//如果文本是Unicode字符串，则直接显示
	if(bWide)
	{
		SetDlgItemText(IDC_TEXT, (WCHAR *)pBuf);
	}
	//如果文本不是Unicode，要先转换为Unicode字符串
	else
	{
		//分配一个缓冲区
		WCHAR *pBufW = new WCHAR[dwLen + 1];
		ZeroMemory(pBufW, (dwLen + 1) * sizeof(WCHAR));
		//Ansi字符串转换为Unicode字符串
		MultiByteToWideChar(CP_ACP, 0, (char *)pBuf, -1, pBufW, dwLen + 1);
		//显示文本
		SetDlgItemText(IDC_TEXT, pBufW);
		//释放缓冲区
		delete []pBufW;
	}
#endif
	delete []pBuf;
	file.Close();
}

void CWideTextDlg::OnSave() 
{
	//得到文件名
	CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_OVERWRITEPROMPT, _T("*.txt|*.txt||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//创建文件
	CFile file;	
	if(!file.Open(dlg.GetPathName(), CFile::modeWrite | CFile::modeCreate))
		return;
	//向文件写入Unicode标志
	byte pFlags[2] = {0xFF, 0xFE};
	file.Write(pFlags, 2);
	//取得文本框中的字符
	CString str;
	GetDlgItemText(IDC_TEXT, str);
	//得到文本框长度
	int nLen = str.GetLength();
	//如果没有定义UNICODE宏，则str中的字符为Ansi字符。
	//先将str中的字符转换为UNICODE
#ifndef UNICODE
	//开辟一块缓冲区
	WCHAR *pBufW = new WCHAR[nLen + 1];
	//缓冲区的实际字节数
	int nBytes = (nLen + 1) * sizeof(WCHAR);
	//初始化缓冲区
	ZeroMemory(pBufW, nBytes);
	//Ansi字符串转换为Unicode字符串
	MultiByteToWideChar(CP_ACP, 0, str, -1, pBufW, nLen + 1);
	//将Unicode文本写入文件
	file.WriteHuge(pBufW, wcslen(pBufW)*sizeof(WCHAR));
	//释放缓冲区
	delete []pBufW;
#else
	//如果定义了UNICODE宏，则str中的字符为Unicode字符。
	//str中的字符不用转换为UNICODE，直接保存
	file.WriteHuge((LPCTSTR)str, str.GetLength()*sizeof(WCHAR));	
#endif
	file.Close();
}
