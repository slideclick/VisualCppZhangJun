// DateTimeDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DateTimeDemo.h"
#include "DateTimeDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateTimeDemoDlg dialog

CDateTimeDemoDlg::CDateTimeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDateTimeDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDateTimeDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDateTimeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateTimeDemoDlg)
	DDX_Control(pDX, IDC_DATE_END, m_date_end);
	DDX_Control(pDX, IDC_DATE_BEGIN, m_date_begin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDateTimeDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDateTimeDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_BEGIN, OnDatetimechangeDateBegin)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_END, OnDatetimechangeDateEnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeDemoDlg message handlers

BOOL CDateTimeDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//设置控件的时间格式
	m_date_begin.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_date_end.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDateTimeDemoDlg::OnPaint() 
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
HCURSOR CDateTimeDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//开始时间发生改变后的事件处理
void CDateTimeDemoDlg::OnDatetimechangeDateBegin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CountSpan();	
	*pResult = 0;
}
//结束时间发生改变后的事件处理
void CDateTimeDemoDlg::OnDatetimechangeDateEnd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CountSpan();
	*pResult = 0;
}
//计算时间差
void CDateTimeDemoDlg::CountSpan()
{
	//取得控件中的时间
	SYSTEMTIME timeBegin = {0}, timeEnd = {0};
	m_date_begin.GetTime(&timeBegin);
	m_date_end.GetTime(&timeEnd);
	//将系统时间转换为文件时间
	FILETIME ftBegin, ftEnd;
	SystemTimeToFileTime(&timeBegin, &ftBegin);
	SystemTimeToFileTime(&timeEnd, &ftEnd);
	//将时间值复制到ULARGE_INTEGER结构中
	ULARGE_INTEGER uBegin, uEnd;
	uBegin.u.HighPart = ftBegin.dwHighDateTime;
	uBegin.u.LowPart = ftBegin.dwLowDateTime;
	uEnd.u.HighPart = ftEnd.dwHighDateTime;
	uEnd.u.LowPart = ftEnd.dwLowDateTime;
	//得到时间差，该值单位是100纳秒
	ULONGLONG uSpan;
	if(uEnd.QuadPart >= uBegin.QuadPart)
		uSpan = uEnd.QuadPart - uBegin.QuadPart;
	else
		uSpan = uBegin.QuadPart - uEnd.QuadPart;
	//得到总秒数
	int nTotalSeconds = uSpan / 10000000;
	//总分钟数
	int nTotalMinutes = nTotalSeconds / 60;
	//总小时数
	int nTotalHours = nTotalMinutes / 60;
	//总天数
	int nTotalDays = nTotalHours / 24;
	//显示结果
	TCHAR szResult[512] = {0};
	_stprintf(szResult, _T("时间间隔：\r\n总秒数：%d\r\n总分钟：%d\r\n总小时：%d\r\n总天数：%d"), 
		nTotalSeconds, nTotalMinutes, nTotalHours, nTotalDays);
	SetDlgItemText(IDC_EDT_RESULT, szResult);
}
