// PopMenuDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PopMenuDemo.h"
#include "PopMenuDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopMenuDemoDlg dialog

CPopMenuDemoDlg::CPopMenuDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopMenuDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopMenuDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPopMenuDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopMenuDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPopMenuDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CPopMenuDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopMenuDemoDlg message handlers

BOOL CPopMenuDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//初始化变量
	m_nClickCount = 0;
	m_bChecked = FALSE;
	//加载菜单
	m_menu.LoadMenu(IDR_MENU_POP);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPopMenuDemoDlg::OnPaint() 
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
HCURSOR CPopMenuDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPopMenuDemoDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	//弹出菜单，并等待其返回
	CMenu *pSub = m_menu.GetSubMenu(0);
	int nCmd = pSub->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, 
		point.x, point.y, this);
	CString strCount;
	switch(nCmd)
	{
		//单击了“点击次数”菜单项，将计数加1，并更新菜单。
	case ID_MI_CLICKCOUNT:
		m_nClickCount++;
		strCount.Format(_T("点击次数：%d"), m_nClickCount);
		pSub->ModifyMenu(ID_MI_CLICKCOUNT, MF_BYCOMMAND, 
			ID_MI_CLICKCOUNT, strCount);
		break;
		//单击了“复位”菜单项，将计数复位为0，并更新菜单。
	case ID_MI_RESET:
		m_nClickCount = 0;
		strCount.Format(_T("点击次数：%d"), m_nClickCount);
		pSub->ModifyMenu(ID_MI_CLICKCOUNT, MF_BYCOMMAND, 
			ID_MI_CLICKCOUNT, strCount);
		break;
	case ID_MI_CHECK:
		//单击了“选择”菜单项，改变其状态
		m_bChecked = (!m_bChecked);
		if(m_bChecked)
			pSub->CheckMenuItem(ID_MI_CHECK, MF_CHECKED|MF_BYCOMMAND);
		else
			pSub->CheckMenuItem(ID_MI_CHECK, MF_UNCHECKED|MF_BYCOMMAND);
		break;
	}
}

void CPopMenuDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//释放资源
	m_menu.DestroyMenu();
}
