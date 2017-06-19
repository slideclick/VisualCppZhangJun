// PrimeNumberFinderExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrimeNumberFinderEx.h"
#include "PrimeNumberFinderExDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderExDlg dialog

CPrimeNumberFinderExDlg::CPrimeNumberFinderExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrimeNumberFinderExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrimeNumberFinderExDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bRunning = FALSE;
}

void CPrimeNumberFinderExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrimeNumberFinderExDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPrimeNumberFinderExDlg, CDialog)
	//{{AFX_MSG_MAP(CPrimeNumberFinderExDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderExDlg message handlers

BOOL CPrimeNumberFinderExDlg::OnInitDialog()
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

void CPrimeNumberFinderExDlg::OnPaint() 
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
HCURSOR CPrimeNumberFinderExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CPrimeNumberFinderExDlg::OnOK() 
{
	//�����û��ʼ���㣬��ʼ��������ڼ����У���ֹͣ
	if(!m_bRunning)
	{
		m_bRunning = TRUE;
		AfxBeginThread(WorkProc, this);
	}
	else
	{
		m_bRunning = FALSE;
	}
}

inline BOOL CPrimeNumberFinderExDlg::IsPrimeNumber(int nInput)
{
	//�ж�һ�����Ƿ�����
	for(int i = 2; i < nInput/2; i++)
	{
		if(nInput % i == 0) 
			return FALSE;
	}
	return TRUE;
}

UINT CPrimeNumberFinderExDlg::WorkProc(LPVOID lpParam)
{
	//�̺߳���
	CPrimeNumberFinderExDlg *pDlg = (CPrimeNumberFinderExDlg *)lpParam;
	pDlg->SetDlgItemText(IDOK, _T("ֹͣ"));

	CString strResult;
	CString strTemp;
	int nTotal = 0;
	//���浱ǰʱ�䱸��
	DWORD dwTick = GetTickCount();	
	UINT nInput = pDlg->GetDlgItemInt(IDC_EDT_INPUT);	
	//��ʾ����Ƶ�ʿ��ƣ���ΪGDI�����ȽϺ�ʱ�����������ʾ�������100��
	int nWatch = nInput / 100;
	if(nWatch == 0)
		nWatch = 1;
	while(nInput > 2 && pDlg->m_bRunning)
	{
		//��ʾ��ǰ����
		if(nInput % nWatch == 0)	
		{
			strTemp.Format(_T("�����жϣ�%d"), nInput);
			pDlg->SetDlgItemText(IDC_CUR_NUM, strTemp);
		}
		//�ж��Ƿ�����
		if(pDlg->IsPrimeNumber(nInput))	
		{
			nTotal ++;
			strTemp.Format(_T("%d\r\n"), nInput);
			strResult += strTemp;
		}
		nInput --;
	}
	//��ʾ���
	pDlg->SetDlgItemText(IDC_EDT_RESULT, strResult);	
	//��ʾ����ʱ��
	dwTick = GetTickCount() - dwTick;
	strTemp.Format(_T("�ҵ�������%d\t����\n����ʱ�䣺%d\t���롣"), nTotal, dwTick);
	pDlg->SetDlgItemText(IDC_COST, strTemp);
	//�ָ�Ӧ�ó���״̬
	pDlg->SetDlgItemText(IDOK, _T("��ʼ"));
	pDlg->m_bRunning = FALSE;
	return 0;
}
