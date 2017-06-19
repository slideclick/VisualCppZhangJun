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

////ȫ�ֺ궨��
//���������Ϣ
#define WM_USER_PRIME (WM_USER+108)
//���������Ϣ
#define WM_USER_NOTIFY (WM_USER+109)
//�Զ�ֹͣ��Ϣ
#define WM_USER_STOP (WM_USER+110)

////ȫ�ֱ�������
//�߳����б�־
volatile BOOL g_bRunning;
//�����̵߳�����ݴ����
ULONGLONG g_nProduct = 0;
//����Event
HANDLE g_hFibEvent;	
//����Event	
HANDLE g_hPrimeEvent;
//���㿪ʼʱ��	
DWORD g_dwStart = 0;

////ȫ�ֺ�������
//64λ������ƽ��
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
//�ж�һ�����Ƿ�����
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
	//��ʼ��
	g_bRunning = FALSE;
	//�Զ�Reset����ʼΪ���źŵ�Event
	g_hFibEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//�Զ�Reset����ʼΪ���źŵ�Event
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
	//����Ѿ��ڼ����У��������㡣����ʼ����
	if(g_bRunning)
	{
		SetDlgItemText(IDOK, _T("��ʼ"));
		g_bRunning = FALSE;
	}
	else
	{
		SetDlgItemText(IDOK, _T("ֹͣ"));
		g_bRunning = TRUE;
		//��ʼ���¼������״̬
		SetEvent(g_hPrimeEvent);
		ResetEvent(g_hFibEvent);
		//���浱ǰʱ��
		g_dwStart = GetTickCount();
		//���������߳�
		_beginthread(FibProc, 0, this->m_hWnd);
		//���������߳�
		_beginthread(PrimeProc, 0, this->m_hWnd);
	}
}

//�����̺߳���
void CBigPrimeNumberDlg::FibProc(LPVOID p)
{
	//����ǰһ��
	ULONGLONG nPreItem = 1;
	//������ǰ��
	ULONGLONG nCurItem = 1;
	//��ǰ������
	ULONGLONG nIndex = 2;
	ULONGLONG nProduct;

	DWORD dwWait;
	while(g_bRunning)
	{
		//������������һ��Ԫ��
		nIndex ++;
		nProduct = nPreItem + nCurItem;
		nPreItem = nCurItem;
		nCurItem = nProduct;
		//������ֽӽ�64λ�����ɱ�ʾ�����ޣ�������������
		if(nProduct > _UI64_MAX/2 || nProduct < nCurItem)
		{
			::PostMessage((HWND)p, WM_USER_STOP, 0, 0);
			return;
		}
		//������������������һ������
		if(!IsPrimeNumber(nIndex))
			continue;
		//�������������������߳�
		int iCount = 0;
		while(TRUE)
		{
			if(!g_bRunning)
				return;
			//�ȵȴ������������߳��Ƿ����
			dwWait = WaitForSingleObject(g_hPrimeEvent, 10);
			if(dwWait == WAIT_OBJECT_0) 
				break;
			else if(dwWait == WAIT_TIMEOUT)
			{
				//�����̹߳����У������ȴ�
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
				TRACE(_T("�ȴ������߳�ʱ����\n"));
				return;
			}
		}
		//�ȴ���������Event���źţ������ִ���ڹ�����
		g_nProduct = nProduct;
		//�������߳�����Ϊ���źţ�ʹ�����̵߳õ�֪ͨ
		SetEvent(g_hFibEvent);
	}
}
//�����̺߳���
void CBigPrimeNumberDlg::PrimeProc(LPVOID p)
{
	DWORD dwWait;
	while(g_bRunning)
	{
		while(TRUE)
		{
			if(!g_bRunning)
				return;
			//�ȴ������߳��ź�
			dwWait = WaitForSingleObject(g_hFibEvent, 10);
			if(dwWait == WAIT_OBJECT_0) 
				break;
			else if(dwWait == WAIT_TIMEOUT)
				Sleep(5);
			else
			{
				TRACE(_T("�ȴ������߳�ʱ����\n"));
				return;
			}
		}
		//�õ�����
		ULONGLONG nProduct = g_nProduct;
		//�ж��Ƿ�����
		if(IsPrimeNumber(nProduct))
		{
			//�������
			TRACE("%I64d\n", nProduct);
			UINT *pI = (UINT *)&nProduct;
			::PostMessage((HWND)p, WM_USER_PRIME, *pI, *(pI+1));
		}
		//������ϣ���������EventΪ���źţ�׼��������һ������
		SetEvent(g_hPrimeEvent);
	}
}

void CBigPrimeNumberDlg::OnClose() 
{
	//���ڼ����رգ�����߳�δ����������֮
	g_bRunning = FALSE;
	CDialog::OnClose();
}

void CBigPrimeNumberDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//���ڼ������٣��ͷ��¼�����
	CloseHandle(g_hPrimeEvent);
	CloseHandle(g_hFibEvent);	
}
//�����Ϣ
void CBigPrimeNumberDlg::OnUserPrime(WPARAM wp, LPARAM lp)
{
	//ȡ������
	TCHAR szText[32] ={0};
	ULONGLONG u;
	UINT *p = (UINT *)&u;
	*p = wp;
	*(p+1) = lp;
	_stprintf(szText, _T("%I64d\r\n"), u);
	//�������
	OutString(szText);
}
//����֪ͨ��Ϣ
void CBigPrimeNumberDlg::OnUserNotify(WPARAM wp, LPARAM lp)
{
	//��ǰ����
	TCHAR szText[256];
	ULONGLONG u;
	UINT *p = (UINT *)&u;
	*p = wp;
	*(p+1) = lp;
	//����ʱ��
	DWORD dwTick = GetTickCount() - g_dwStart;
	//�����Ϣ
	_stprintf(szText, _T("�����ж�:\n%I64d\n\n�Ѻ�ʱ��:\n%d��"), u, dwTick/1000);
	SetDlgItemText(IDC_NOTIFY, szText);
}

//�߳��Զ���ֹ֪ͨ
void CBigPrimeNumberDlg::OnUserStop()
{
	OnOK();
	OutString("��ﵽint64���޶���ֹ��");
}
//����ı����ı���
void CBigPrimeNumberDlg::OutString(LPCTSTR lpStr)
{
	m_edtResult.SetSel(m_edtResult.GetWindowTextLength(), m_edtResult.GetWindowTextLength() + 1);
	m_edtResult.ReplaceSel(lpStr);	
}