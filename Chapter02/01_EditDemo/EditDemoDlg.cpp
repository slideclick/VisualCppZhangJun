// EditDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditDemo.h"
#include "EditDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDemoDlg dialog

CEditDemoDlg::CEditDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDemoDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COUNT, OnBtnCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDemoDlg message handlers

BOOL CEditDemoDlg::OnInitDialog()
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

void CEditDemoDlg::OnPaint() 
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
HCURSOR CEditDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“统计”按钮的单击事件响应函数
void CEditDemoDlg::OnBtnCount() 
{
	CString strInput;
	//取得输入文本框中的内容
	GetDlgItemText(IDC_EDT_INPUT, strInput);
	//获取字符串长度
	int nLen = strInput.GetLength();
	int nCount = 0;
	//循环计算字符个数
	for(int i=0; i<nLen; i++)
	{
		if((BYTE)strInput[i] > 0x7F)
		{
			i++;
		}
		nCount ++;
	}
	//输出结果到界面上
	CString strOutput;
	strOutput.Format(_T("字符串长度：%d，字符个数：%d。"), nLen, nCount);
	SetDlgItemText(IDC_OUTPUT, strOutput);
}
