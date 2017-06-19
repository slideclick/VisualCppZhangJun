// BigPrimeNumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BigPrimeNumber.h"
#include "BigPrimeNumberDlg.h"
#include <process.h>
#include <limits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////全局宏定义
//输出素数消息
#define WM_USER_PRIME (WM_USER+108)
//输出进度消息
#define WM_USER_NOTIFY (WM_USER+109)
//自动停止消息
#define WM_USER_STOP (WM_USER+110)

////全局变量定义
//线程运行标志
volatile BOOL g_bRunning;
//生产线程的输出暂存变量
ULONGLONG g_nProduct = 0;
//生产Event
HANDLE g_hFibEvent;	
//消费Event	
HANDLE g_hPrimeEvent;
//计算开始时间	
DWORD g_dwStart = 0;

////全局函数定义
//64位整数开平方
inline ULONGLONG sqrt64(ULONGLONG input)  
{  
	int i;  
	ULONGLONG ret = 0, t;  
	
	for (i=31; i>=0; i--)   
	{  
		t = ret + (1<<i);  
		if ((unsigned __int64)t*t <= input)
			ret = t;  
	}  
	return ret;  
}
//判断一个数是否素数
BOOL IsPrimeNumber(const ULONGLONG &number)
{
	if(number < 3)
		return FALSE;
	
	ULONGLONG i, max;
	i = 2;
	max = sqrt64(number);
	for(i = 2; i <= max; i++)
	{
		if(!g_bRunning)
			return FALSE;
		if(number % i == 0) 
			return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CBigPrimeNumberDlg dialog

CBigPrimeNumberDlg::CBigPrimeNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBigPrimeNumberDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBigPrimeNumberDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//初始化
	g_bRunning = FALSE;
	//自动Reset、初始为无信号的Event
	g_hFibEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//自动Reset、初始为有信号的Event
	g_hPrimeEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
}

void CBigPrimeNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBigPrimeNumberDlg)
	DDX_Control(pDX, IDC_EDT_RESULT, m_edtResult);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBigPrimeNumberDlg, CDialog)
	//{{AFX_MSG_MAP(CBigPrimeNumberDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_PRIME, OnUserPrime)
	ON_MESSAGE(WM_USER_NOTIFY, OnUserNotify)
	ON_MESSAGE(WM_USER_STOP, OnUserStop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBigPrimeNumberDlg message handlers

BOOL CBigPrimeNumberDlg::OnInitDialog()
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

void CBigPrimeNumberDlg::OnPaint() 
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
HCURSOR CBigPrimeNumberDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBigPrimeNumberDlg::OnOK() 
{
	//如果已经在计算中，结束计算。否则开始计算
	if(g_bRunning)
	{
		SetDlgItemText(IDOK, _T("开始"));
		g_bRunning = FALSE;
	}
	else
	{
		SetDlgItemText(IDOK, _T("停止"));
		g_bRunning = TRUE;
		//初始化事件对象的状态
		SetEvent(g_hPrimeEvent);
		ResetEvent(g_hFibEvent);
		//保存当前时间
		g_dwStart = GetTickCount();
		//启动生产线程
		_beginthread(FibProc, 0, this->m_hWnd);
		//启动消费线程
		_beginthread(PrimeProc, 0, this->m_hWnd);
	}
}

//生产线程函数
void CBigPrimeNumberDlg::FibProc(LPVOID p)
{
	//数列前一项
	ULONGLONG nPreItem = 1;
	//数量当前项
	ULONGLONG nCurItem = 1;
	//当前项的序号
	ULONGLONG nIndex = 2;
	ULONGLONG nProduct;

	DWORD dwWait;
	while(g_bRunning)
	{
		//生成序列中下一个元素
		nIndex ++;
		nProduct = nPreItem + nCurItem;
		nPreItem = nCurItem;
		nCurItem = nProduct;
		//如果数字接近64位整数可表示的上限，结束整个计算
		if(nProduct > _UI64_MAX/2 || nProduct < nCurItem)
		{
			::PostMessage((HWND)p, WM_USER_STOP, 0, 0);
			return;
		}
		//如果不是素数项，继续下一个序列
		if(!IsPrimeNumber(nIndex))
			continue;
		//如果是素数项，交给消费线程
		int iCount = 0;
		while(TRUE)
		{
			if(!g_bRunning)
				return;
			//先等待，看看消费线程是否空闲
			dwWait = WaitForSingleObject(g_hPrimeEvent, 10);
			if(dwWait == WAIT_OBJECT_0) 
				break;
			else if(dwWait == WAIT_TIMEOUT)
			{
				//消费线程工作中，继续等待
				iCount ++;
				if(iCount * 20 > 500)
				{
					UINT *pTemp = (UINT *)&g_nProduct;
					::PostMessage((HWND)p, WM_USER_NOTIFY, *pTemp, *(pTemp + 1));
					iCount = 0;
				}
				Sleep(20);
			}
			else
			{
				TRACE(_T("等待消费线程时出错。\n"));
				return;
			}
		}
		//等待到了消费Event的信号，将数字存放在公共区
		g_nProduct = nProduct;
		//将生产线程设置为有信号，使消费线程得到通知
		SetEvent(g_hFibEvent);
	}
}
//消费线程函数
void CBigPrimeNumberDlg::PrimeProc(LPVOID p)
{
	DWORD dwWait;
	while(g_bRunning)
	{
		while(TRUE)
		{
			if(!g_bRunning)
				return;
			//等待生产线程信号
			dwWait = WaitForSingleObject(g_hFibEvent, 10);
			if(dwWait == WAIT_OBJECT_0) 
				break;
			else if(dwWait == WAIT_TIMEOUT)
				Sleep(5);
			else
			{
				TRACE(_T("等待生产线程时出错。\n"));
				return;
			}
		}
		//得到数字
		ULONGLONG nProduct = g_nProduct;
		//判断是否素数
		if(IsPrimeNumber(nProduct))
		{
			//输出素数
			TRACE("%I64d\n", nProduct);
			UINT *pI = (UINT *)&nProduct;
			::PostMessage((HWND)p, WM_USER_PRIME, *pI, *(pI+1));
		}
		//工作完毕，设置消费Event为有信号，准备接收下一个数字
		SetEvent(g_hPrimeEvent);
	}
}

void CBigPrimeNumberDlg::OnClose() 
{
	//窗口即将关闭，如果线程未结束，结束之
	g_bRunning = FALSE;
	CDialog::OnClose();
}

void CBigPrimeNumberDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//窗口即将销毁，释放事件对象
	CloseHandle(g_hPrimeEvent);
	CloseHandle(g_hFibEvent);	
}
//输出消息
void CBigPrimeNumberDlg::OnUserPrime(WPARAM wp, LPARAM lp)
{
	//取得数字
	TCHAR szText[32] ={0};
	ULONGLONG u;
	UINT *p = (UINT *)&u;
	*p = wp;
	*(p+1) = lp;
	_stprintf(szText, _T("%I64d\r\n"), u);
	//输出数字
	OutString(szText);
}
//进度通知消息
void CBigPrimeNumberDlg::OnUserNotify(WPARAM wp, LPARAM lp)
{
	//当前数字
	TCHAR szText[256];
	ULONGLONG u;
	UINT *p = (UINT *)&u;
	*p = wp;
	*(p+1) = lp;
	//运行时间
	DWORD dwTick = GetTickCount() - g_dwStart;
	//输出信息
	_stprintf(szText, _T("正在判断:\n%I64d\n\n已耗时间:\n%d秒"), u, dwTick/1000);
	SetDlgItemText(IDC_NOTIFY, szText);
}

//线程自动终止通知
void CBigPrimeNumberDlg::OnUserStop()
{
	OnOK();
	OutString("因达到int64上限而终止。");
}
//输出文本到文本框
void CBigPrimeNumberDlg::OutString(LPCTSTR lpStr)
{
	m_edtResult.SetSel(m_edtResult.GetWindowTextLength(), m_edtResult.GetWindowTextLength() + 1);
	m_edtResult.ReplaceSel(lpStr);	
}