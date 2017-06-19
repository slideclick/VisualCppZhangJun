// ActiveXInDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ActiveXInDlg.h"
#include "ActiveXInDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveXInDlgDlg dialog

CActiveXInDlgDlg::CActiveXInDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CActiveXInDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActiveXInDlgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CActiveXInDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveXInDlgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CActiveXInDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CActiveXInDlgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PUT, OnBtnPut)
	ON_BN_CLICKED(IDC_BTN_ANIMATE, OnBtnAnimate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveXInDlgDlg message handlers

BOOL CActiveXInDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//��ÿؼ�ָ��
	m_pMyActiveX = (CMyActiveX *)GetDlgItem(IDC_MYACTIVEX);
	if(m_pMyActiveX == NULL)
	{
		AfxMessageBox(_T("�ؼ�δ�����ɹ���"));
	}
	else
	{
		//�õ��ؼ���Ĭ���߿�
		int nWidth = m_pMyActiveX->GetLineWidth();
		//�õ��ؼ���Ĭ������
		int nCycle = m_pMyActiveX->GetCycle();
		//����ֵ���õ�����
		SetDlgItemInt(IDC_EDT_LINEWIDTH, nWidth);
		SetDlgItemInt(IDC_EDT_CYCLE, nCycle);
		//�õ��ؼ�Ĭ�ϵ�ǰ��ɫ
		COLORREF crFore = m_pMyActiveX->GetForeColor();
		//����ɫ���õ��Ի���
		TCHAR szBuf[32] = {0};
		_stprintf(szBuf, _T("%d,%d,%d"), 
			GetRValue(crFore), GetGValue(crFore), GetBValue(crFore));
		SetDlgItemText(IDC_EDT_COLOR, szBuf);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CActiveXInDlgDlg::OnPaint() 
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
HCURSOR CActiveXInDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//�����á���ť����Ӧ����
void CActiveXInDlgDlg::OnBtnPut() 
{
	int nWidth, nCycle;
	COLORREF crFore;
	//ȡ��������߿�
	nWidth = GetDlgItemInt(IDC_EDT_LINEWIDTH);
	//ȡ�����������
	nCycle = GetDlgItemInt(IDC_EDT_CYCLE);
	//ȡ�������ǰ��ɫ
	TCHAR szBuf[32] = {0};
	GetDlgItemText(IDC_EDT_COLOR, szBuf, 32);
	int r,g,b;
	_stscanf(szBuf, _T("%d,%d,%d"), &r, &g, &b);
	crFore = RGB(r, g, b);
	//���������õ��ؼ�
	m_pMyActiveX->SetLineWidth(nWidth);
	m_pMyActiveX->SetCycle(nCycle);
	m_pMyActiveX->SetForeColor(crFore);
	
}
//����������ť����Ӧ����
void CActiveXInDlgDlg::OnBtnAnimate() 
{
	//��ʼ��ֹͣ����
	m_pMyActiveX->Animate();
}
