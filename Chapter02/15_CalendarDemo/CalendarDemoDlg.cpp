// CalendarDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalendarDemo.h"
#include "CalendarDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDlg dialog

CCalendarDemoDlg::CCalendarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalendarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDemoDlg)
	DDX_Control(pDX, IDC_CALENDAR, m_calendar);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalendarDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(MCN_SELCHANGE, IDC_CALENDAR, OnSelchangeCalendar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDlg message handlers

BOOL CCalendarDemoDlg::OnInitDialog()
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

void CCalendarDemoDlg::OnPaint() 
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
HCURSOR CCalendarDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalendarDemoDlg::OnSelchangeCalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//��ȡ�ؼ���ǰ��ѡ����
	SYSTEMTIME st = {0};
	m_calendar.GetCurSel(&st);
	//���Сʱ�����ӵȳ�Ա�������ں��������н��õ�����Ľ��
	st.wHour = st.wMinute = st.wSecond = st.wMilliseconds = 0; 
	//�õ������1��1��
	CTime timeBegin(st.wYear, 1, 1, 0, 0, 0);
	//�õ���ѡ���ں͸���1��1�յĲ�ֵ
	CTime timeSel(st);
	CTimeSpan ts = timeSel - timeBegin;
	//���ݲ�ֵ�õ�������
	TCHAR szOutput[128] = {0};
	_stprintf(szOutput, _T("%d��%d��%d����%d��ĵ�%d�졣"), 
		timeSel.GetYear(), timeSel.GetMonth(), timeSel.GetDay(),
		timeSel.GetYear(), ts.GetDays() + 1);
	//������
	SetDlgItemText(IDC_OUTPUT, szOutput);

	*pResult = 0;
}
