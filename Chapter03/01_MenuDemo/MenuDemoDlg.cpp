// MenuDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MenuDemo.h"
#include "MenuDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuDemoDlg dialog

CMenuDemoDlg::CMenuDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMenuDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMenuDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMenuDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CMenuDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HIDE_MENU, OnHideMenu)
	ON_WM_DESTROY()
	ON_COMMAND(ID_MI_CHECK, OnMiCheck)
	ON_COMMAND(ID_MI_DISABLE, OnMiDisable)
	ON_COMMAND(ID_MI_ENABLE, OnMiEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuDemoDlg message handlers

BOOL CMenuDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//从资源加载菜单
	m_hMenu1 = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU1));
	m_hMenu2 = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU2));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMenuDemoDlg::OnPaint() 
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
HCURSOR CMenuDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMenuDemoDlg::OnOK() 
{
	//定义一个变量，保存当前显示的是哪个菜单
	static int nMenu = 1;
	//如果是1号菜单，切换到2号。如果是2号，切换到1号
	if(nMenu == 1)
	{
		::SetMenu(this->GetSafeHwnd(), m_hMenu2);
		nMenu = 2;
	}
	else
	{
		::SetMenu(this->GetSafeHwnd(), m_hMenu1);
		nMenu = 1;
	}
}

void CMenuDemoDlg::OnHideMenu() 
{
	//将当前窗体的菜单设置为空，以取消菜单
	::SetMenu(this->GetSafeHwnd(), NULL);
}

void CMenuDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//释放菜单资源
	DestroyMenu(m_hMenu1);
	DestroyMenu(m_hMenu2);	
}

void CMenuDemoDlg::OnMiCheck() 
{
	//单击了“选中”菜单
	MENUITEMINFO mi = {0};
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_STATE;
	//取出菜单信息
	BOOL bRet = GetMenuItemInfo(m_hMenu2, ID_MI_CHECK, FALSE, &mi);
	ASSERT(bRet);
	//如果选中，设置为未选中状态，否则设置为选中状态
	if((mi.fState & MFS_CHECKED) == MFS_CHECKED)
	{
		mi.fState = MFS_UNCHECKED;
	}
	else
	{
		mi.fState = MFS_CHECKED;
	}
	//设置菜单信息
	bRet = SetMenuItemInfo(m_hMenu2, ID_MI_CHECK, FALSE, &mi);	
	ASSERT(bRet);
}
void CMenuDemoDlg::OnMiDisable() 
{
	//单击了“禁用”菜单，禁用自己
	MENUITEMINFO mi = {0};
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_STATE;
	mi.fState = MFS_DISABLED;
	SetMenuItemInfo(m_hMenu1, ID_MI_DISABLE, FALSE, &mi);	
}
void CMenuDemoDlg::OnMiEnable() 
{
	//单击了“启用”菜单，启用被禁用的菜单
	MENUITEMINFO mi = {0};
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_STATE;
	mi.fState = MFS_ENABLED;
	SetMenuItemInfo(m_hMenu1, ID_MI_DISABLE, FALSE, &mi);
}
