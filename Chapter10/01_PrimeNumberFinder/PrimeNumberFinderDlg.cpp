// PrimeNumberFinderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrimeNumberFinder.h"
#include "PrimeNumberFinderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderDlg dialog

CPrimeNumberFinderDlg::CPrimeNumberFinderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrimeNumberFinderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrimeNumberFinderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrimeNumberFinderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrimeNumberFinderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPrimeNumberFinderDlg, CDialog)
	//{{AFX_MSG_MAP(CPrimeNumberFinderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderDlg message handlers

BOOL CPrimeNumberFinderDlg::OnInitDialog()
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

void CPrimeNumberFinderDlg::OnPaint() 
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
HCURSOR CPrimeNumberFinderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPrimeNumberFinderDlg::OnOK() 
{
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	CString strResult;
	CString strTemp;
	int nTotal = 0;
	//���浱ǰʱ�䱸��
	DWORD dwTick = GetTickCount();	
	UINT nInput = GetDlgItemInt(IDC_EDT_INPUT);	
	//��ʾ����Ƶ�ʿ��ƣ���ΪGDI�����ȽϺ�ʱ�����������ʾ�������100��
	int nWatch = nInput / 100;
	if(nWatch == 0)
		nWatch = 1;
	while(nInput > 2)
	{
		//��ʾ��ǰ����
		if(nInput % nWatch == 0)	
		{
			strTemp.Format(_T("�����жϣ�%d"), nInput);
			SetDlgItemText(IDC_CUR_NUM, strTemp);
		}
		//�ж��Ƿ�����������ǣ�������������
		if(IsPrimeNumber(nInput))	
		{
			nTotal ++;
			strTemp.Format(_T("%d\r\n"), nInput);
			strResult += strTemp;
		}
		nInput --;
	}
	//��ʾ���
	SetDlgItemText(IDC_EDT_RESULT, strResult);
	//��ʾ����ʱ��
	dwTick = GetTickCount() - dwTick;
	strTemp.Format(_T("�ҵ�������%d\t����\n����ʱ�䣺%d\t���롣"), nTotal, dwTick);
	SetDlgItemText(IDC_COST, strTemp);

	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

inline BOOL CPrimeNumberFinderDlg::IsPrimeNumber(int nInput)
{
	//�ж��Ƿ�����
	for(int i = 2; i < nInput/2; i++)
	{
		if(nInput % i == 0) 
			return FALSE;
	}
	return TRUE;
}
