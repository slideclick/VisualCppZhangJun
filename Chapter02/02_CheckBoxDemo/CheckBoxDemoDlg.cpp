// CheckBoxDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CheckBoxDemo.h"
#include "CheckBoxDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDemoDlg dialog

CCheckBoxDemoDlg::CCheckBoxDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckBoxDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckBoxDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckBoxDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckBoxDemoDlg)
	DDX_Control(pDX, IDC_RD_ROUND, m_rd_round);
	DDX_Control(pDX, IDC_RD_RECT, m_rd_rect);
	DDX_Control(pDX, IDC_CHK_RED, m_chk_red);
	DDX_Control(pDX, IDC_CHK_GREEN, m_chk_green);
	DDX_Control(pDX, IDC_CHK_BLUE, m_chk_blue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckBoxDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckBoxDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHK_BLUE, OnChkBlue)
	ON_BN_CLICKED(IDC_CHK_GREEN, OnChkGreen)
	ON_BN_CLICKED(IDC_CHK_RED, OnChkRed)
	ON_BN_CLICKED(IDC_RD_RECT, OnRdRect)
	ON_BN_CLICKED(IDC_RD_ROUND, OnRdRound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDemoDlg message handlers

BOOL CCheckBoxDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//默认选择“圆形”单选按钮
	CheckRadioButton(IDC_RD_RECT, IDC_RD_ROUND, IDC_RD_ROUND);	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCheckBoxDemoDlg::OnPaint() 
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
HCURSOR CCheckBoxDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//WM_ERASEBKGND消息的响应函数
BOOL CCheckBoxDemoDlg::OnEraseBkgnd(CDC* pDC) 
{
	//先绘制默认背景
	BOOL bRet = CDialog::OnEraseBkgnd(pDC);
	//获取复选框控件所选的颜色
	int nRed, nGreen, nBlue;
	nRed = m_chk_red.GetCheck() ? 255 : 0;
	nGreen = m_chk_green.GetCheck() ? 255 : 0;
	nBlue = m_chk_blue.GetCheck() ? 255 : 0;
	//根据选择组成颜色
	COLORREF crFore = RGB(nRed, nGreen, nBlue);
	//创建指定颜色的画刷
	CBrush brush;
	brush.CreateSolidBrush(crFore);
	//将画刷选入DC
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	//根据选择，绘制矩形或圆形
	RECT rc = {50, 20, 150, 120};
	if(m_rd_rect.GetCheck())
		pDC->Rectangle(&rc);
	else
		pDC->Ellipse(&rc);
	//恢复DC原状
	pDC->SelectObject(pOldBrush);
	return bRet;
}
//界面上的单选按钮和复选框的单击事件响应函数
void CCheckBoxDemoDlg::OnChkBlue() 
{
	//选项改变时，让对话框重绘
	Invalidate();
}
//其余控件均采用相同的处理代码
void CCheckBoxDemoDlg::OnChkGreen() 
{
	OnChkBlue();
}
void CCheckBoxDemoDlg::OnChkRed() 
{
	OnChkBlue();
}
void CCheckBoxDemoDlg::OnRdRect() 
{
	OnChkBlue();
}
void CCheckBoxDemoDlg::OnRdRound() 
{
	OnChkBlue();
}
