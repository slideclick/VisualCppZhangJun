// BrushDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BrushDemo.h"
#include "BrushDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoDlg dialog

CBrushDemoDlg::CBrushDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrushDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrushDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBrushDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrushDemoDlg)
	DDX_Control(pDX, IDC_CMB_BRUSH, m_cmb_brush);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBrushDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CBrushDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CMB_BRUSH, OnSelchangeCmbBrush)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoDlg message handlers

BOOL CBrushDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//��ʼ���ؼ�ѡ��
	m_cmb_brush.SetCurSel(0);
	//����λͼ
	m_bmp.LoadBitmap(IDB_BK);
	OnSelchangeCmbBrush();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBrushDemoDlg::OnPaint() 
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
HCURSOR CBrushDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBrushDemoDlg::OnSelchangeCmbBrush() 
{
	//�ͷŻ�ˢ����
	if(m_brush.GetSafeHandle())
	{
		m_brush.DeleteObject();
	}
	//����ѡ���ؽ���ˢ����
	switch(m_cmb_brush.GetCurSel())
	{
	case 0:
		//������ɫ��ˢ
		m_brush.CreateSolidBrush(RGB(200, 200, 255));
		break;
	case 1:
		//������Ӱ��ˢ
		m_brush.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 255));
		break;
	default:
		//����ͼ����ˢ
		m_brush.CreatePatternBrush(&m_bmp);
		break;
	}
	//ˢ�´���
	Invalidate(TRUE);
}

HBRUSH CBrushDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	//���Լ��Ļ�ˢ�ı�Ի���ı���
	if(m_brush.GetSafeHandle() && nCtlColor == CTLCOLOR_DLG)
		return m_brush;
	else
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
