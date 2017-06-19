// PrimeNumberFinalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrimeNumberFinal.h"
#include "PrimeNumberFinalDlg.h"
#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_USER_WAITTHREADEND (WM_USER+101)

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinalDlg dialog

CPrimeNumberFinalDlg::CPrimeNumberFinalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrimeNumberFinalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrimeNumberFinalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bRunning = FALSE;
	m_nMaxNumber = 0;
	m_nThreadCount = 0;
	m_nFoundCount = 0;
	m_dwStartTick = 0;
	m_pThreadHandles = NULL;
	m_hRunEvent = NULL;
}

void CPrimeNumberFinalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrimeNumberFinalDlg)
	DDX_Control(pDX, IDC_SPIN_THREAD, m_spin_thread);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPrimeNumberFinalDlg, CDialog)
	//{{AFX_MSG_MAP(CPrimeNumberFinalDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_WAITTHREADEND, OnWaitThreadEnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinalDlg message handlers

BOOL CPrimeNumberFinalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//��ʼ���ٽ�������
	InitializeCriticalSection(&m_csGet);
	InitializeCriticalSection(&m_csAdd);
	//�����¼�����
	m_hRunEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//��ʼ������ؼ�
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_THREAD);
	pSpin->SetRange(1, 10);
	SetDlgItemText(IDC_EDT_THREADNUM, _T("2"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPrimeNumberFinalDlg::OnPaint() 
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
HCURSOR CPrimeNumberFinalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPrimeNumberFinalDlg::OnOK() 
{
	if(m_bRunning)
	{
		CloseAllThread();
		return;
	}
	m_nFoundCount = 0;
	//ȡ���û�����
	m_nMaxNumber = GetDlgItemInt(IDC_EDT_INPUT);
	m_nThreadCount = GetDlgItemInt(IDC_EDT_THREADNUM);
	ASSERT(m_nThreadCount > 0);
	ASSERT(m_nMaxNumber > 2);
	//����������Ϊ����״̬
	m_bRunning = TRUE;
	SetDlgItemText(IDOK, _T("ֹͣ"));
	m_strPrimeNumbers = _T("");
	//���������߳�
	SetEvent(m_hRunEvent);
	m_pThreadHandles = new HANDLE[m_nThreadCount];
	m_dwStartTick = GetTickCount();
	for(int i=0; i<m_nThreadCount; i++)
	{
		m_pThreadHandles[i] = (HANDLE)_beginthread(WorkProc, 0, this);
	}
}

void CPrimeNumberFinalDlg::OnDestroy() 
{
	//�ͷ��ٽ�������
	DeleteCriticalSection(&m_csGet);
	DeleteCriticalSection(&m_csAdd);
	CloseHandle(m_hRunEvent);

	CDialog::OnDestroy();	
}

int CPrimeNumberFinalDlg::GetANumber()
{
	//�����ٽ���������Ѿ��������߳̽��룬��ǰ�̵߳ȴ���ֱ���Ѿ�������߳��˳���
	EnterCriticalSection(&m_csGet);
	//����Ѿ��������������0���߳̽���
	int nRet;
	if(m_nMaxNumber <= 2)
	{
		nRet = 0;
		CloseAllThread();
	}
	else
		nRet = m_nMaxNumber;
	//���ټ����������½���
	static int nWatch = m_nMaxNumber / 100;
	if(nWatch == 0)
		nWatch = 1;
	m_nMaxNumber--;
	if(m_nMaxNumber % nWatch == 0)
	{
		TCHAR szBuf[32] = {0};
		_stprintf(szBuf, _T("��ǰ��%d"), m_nMaxNumber);
		SetDlgItemText(IDC_CUR_NUM, szBuf);
	}
	//�˳��ٽ���
	LeaveCriticalSection(&m_csGet);
	return nRet;
}

void CPrimeNumberFinalDlg::AddNewPrimeNumber(int nNumber)
{
	static CString strTemp;
	//�����ٽ���
	EnterCriticalSection(&m_csAdd);
	m_nFoundCount ++;
	strTemp.Format(_T("%d\r\n"), nNumber);
	m_strPrimeNumbers += strTemp;
	//�˳��ٽ���
	LeaveCriticalSection(&m_csAdd);
}

void CPrimeNumberFinalDlg::CloseAllThread()
{
	//�����¼�Ϊ���źţ�֪ͨ�����̹߳ر�
	ResetEvent(m_hRunEvent);
	PostMessage(WM_USER_WAITTHREADEND, 0, 0);	
}

void CPrimeNumberFinalDlg::OnWaitThreadEnd()
{
	//�ȴ��߳��˳����ָ�������棬
	//�߳��Զ��˳������û���ֹ����ñ�����
	if(m_bRunning)
	{
		//���ȴ�500���룬�Ա������߳��˳�
		UINT nWait = WaitForMultipleObjects(m_nThreadCount, m_pThreadHandles, TRUE, 500);
			
		if(nWait >= WAIT_OBJECT_0 )
			TRACE(_T("�����߳��ѳɹ�������\n"));
		else if(nWait == WAIT_TIMEOUT)
			TRACE(_T("�ȴ����й����߳��˳�ʱ��������ʱ��\n"));
		else if (nWait == WAIT_FAILED)
			TRACE(_T("�ȴ����й����߳��˳�ʱ����������%d\n"), GetLastError());
		else
			TRACE(_T("�ȴ����й����߳��˳�ʱ���������⣡\n"));

		m_bRunning = FALSE;

		if(m_pThreadHandles)
		{
			delete []m_pThreadHandles;
			m_pThreadHandles = NULL;
		}

		TCHAR szBuf[128] = {0};
		_stprintf(szBuf, _T("�ҵ�������%d\t����\n����ʱ�䣺%d\t���롣"), m_nFoundCount, GetTickCount() - m_dwStartTick);
		SetDlgItemText(IDC_COST, szBuf);
		SetDlgItemText(IDOK, _T("��ʼ"));

		SetDlgItemText(IDC_EDT_RESULT, m_strPrimeNumbers);
	}
}

void CPrimeNumberFinalDlg::WorkProc(LPVOID lpParam)
{
	TRACE("�߳�0x%X���롣\n", GetCurrentThreadId());
	CPrimeNumberFinalDlg *pDlg = (CPrimeNumberFinalDlg *)lpParam;
	int nNumber;
	UINT nWait;
	BOOL bIsPrimeNumber;
	while(TRUE)
	{
		//�Ƿ�������У����m_hRunEvent���û�ź�״̬�����˳�
		nWait = WaitForSingleObject(pDlg->m_hRunEvent, 0);
		if(WAIT_OBJECT_0 != nWait)
			break;
		nNumber = pDlg->GetANumber();
		//���GetANumber����0�������Ѿ�������ɣ��߳������˳�
		if(nNumber == 0)
			break;
		//�ж��Ƿ�����
		bIsPrimeNumber = TRUE;
		for(int i = 2; i < nNumber/2; i++)
		{
			if(nNumber % i == 0) 
			{
				bIsPrimeNumber = FALSE;
				break;
			}
		}
		//����ҵ�������
		if(bIsPrimeNumber)
			pDlg->AddNewPrimeNumber(nNumber);
	}
	TRACE("�߳�0x%X�����˳���\n", GetCurrentThreadId());
}

void CPrimeNumberFinalDlg::OnClose() 
{
	//������������˳����ȹر��߳�
	if (m_bRunning)
		CloseAllThread();
	
	CDialog::OnClose();
}
