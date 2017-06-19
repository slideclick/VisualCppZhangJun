// ToolbarDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolbarDemo.h"
#include "ToolbarDemoDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarDemoDlg dialog

CToolbarDemoDlg::CToolbarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolbarDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolbarDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolbarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolbarDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolbarDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CToolbarDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MI_TEST, OnMiTest)
	ON_COMMAND(ID_MI_DISABLE, OnMiDisable)
	ON_UPDATE_COMMAND_UI(ID_MI_TEST, OnUpdateMiTest)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarDemoDlg message handlers

BOOL CToolbarDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_bCanTest = TRUE;
	//创建工具栏
	BOOL bRet = m_toolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER);//|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC
	bRet = m_toolbar.LoadToolBar(IDR_TOOLBAR);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToolbarDemoDlg::OnPaint() 
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
HCURSOR CToolbarDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CToolbarDemoDlg::OnMiTest() 
{
	AfxMessageBox(_T("你按下了测试按钮！"));	
}

void CToolbarDemoDlg::OnMiDisable() 
{
	//按下禁用按钮，改变测试按钮的禁用状态
	m_bCanTest = (!m_bCanTest);
}

void CToolbarDemoDlg::OnUpdateMiTest(CCmdUI* pCmdUI) 
{
	//更新ID_MI_TEST的界面，包括工具栏和菜单
	pCmdUI->Enable(m_bCanTest);	
}

LRESULT CToolbarDemoDlg:: OnKickIdle(WPARAM wParam, LPARAM ICount)
{
	//向工具栏发出更新消息
	if(m_toolbar.IsWindowVisible()) 
	{ 
		CFrameWnd* pParent = ( CFrameWnd* ) m_toolbar.GetParent(); 
		if( pParent ) 
			m_toolbar.OnUpdateCmdUI( pParent, ( WPARAM ) TRUE ); 
	} 
	
	//向菜单发出更新消息
	CMenu* pMainMenu = GetMenu(); 
	CCmdUI cmdUI; 
	for (UINT n = 0; n < pMainMenu->GetMenuItemCount(); ++n) 
	{ 
		CMenu* pSubMenu = pMainMenu->GetSubMenu(n); 
		cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount(); 
		for (UINT i = 0; i < cmdUI.m_nIndexMax;++i) 
		{ 
			cmdUI.m_nIndex = i; 
			cmdUI.m_nID = pSubMenu->GetMenuItemID(i); 
			cmdUI.m_pMenu = pSubMenu; 
			cmdUI.DoUpdate(this, FALSE); 
		} 
	}
	return 0;
}

void CToolbarDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//释放工具栏资源
	m_toolbar.DestroyWindow();	
}
