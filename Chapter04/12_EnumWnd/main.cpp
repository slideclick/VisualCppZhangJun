#include "main.h"


//----------------
//全局变量声明
//-----------------
HINSTANCE g_hInst	=	NULL;
//主对话框的窗口句柄
HWND g_hDlg			=	NULL;
//树形控件的句柄
HWND g_hTree		=	NULL;
//对话框改变之前的大小
SIZE g_siDlg		=	{0};
//对话框原始大小
SIZE g_siOrig		=	{0};
BOOL g_bInited		=	FALSE;
//用来拖动的控件区域
RECT g_rcDragIcon	=	{0};
//拖动时的光标
HICON g_hDragIcon	=	NULL;
//鼠标是否处于拖动状态
BOOL g_bDragging		=	FALSE;
//正常光标
HICON g_hNormalIcon =	NULL;
//窗口图标
HICON g_hWndIcon	=	NULL;

//------------------
//函数实现
//------------------
//应用程序的入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	//初始化公共控件
	InitCommonControls();
	//弹出一个模式对话框，并等待对话框结束
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
	return 0;
}
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:		//对话框初始化
		//保存窗口句柄
		g_hDlg = hwndDlg;		
		OnInitDialog();
		return 1;
	case WM_COMMAND:		//发生命令
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//关闭对话框
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_SIZE:			//对话框大小改变
		OnSize(wParam, lParam);
		return 1;
		break;
	case WM_GETMINMAXINFO:	//查询窗口最大最小尺寸
		{
			//限制窗体最小尺寸
			LPMINMAXINFO lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMinTrackSize.x = g_siOrig.cx;
			lpmm->ptMinTrackSize.y = g_siOrig.cy;
		}
		return 1;
	case WM_LBUTTONDOWN:	//鼠标左键按下
		OnLButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
		return 1;
	case WM_LBUTTONUP:		//鼠标右键按下
		OnLButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
		return 1;
	case WM_ACTIVATE:		//窗口活动状态改变
		if(wParam == WA_INACTIVE && g_bDragging)
		{
			//如果拖动途中窗口失去焦点，结束本次拖动
			BOOL b = ReleaseCapture();
			g_bDragging = FALSE;
		}
		return 1;
	case WM_NOTIFY:			//控件通知消息
		if(wParam == IDC_TREE)
		{
			//只处理树状控件的选中改变通知
			LPNMHDR pnmh = (LPNMHDR)lParam;
			if(pnmh->code == TVN_SELCHANGED)
			{
				OnTreeSelChanged(pnmh);
				return 1;
			}
		}
		break;
	default:
		break;
	}
	//默认返回0
	return 0;
}
//初始化对话框
void OnInitDialog()
{
	//保存窗口原始尺寸
	RECT rc = {0};
	GetWindowRect(g_hDlg, &rc);
	g_siOrig.cx = rc.right - rc.left;
	g_siOrig.cy = rc.bottom - rc.top;
	//保存窗口客户区大小
	GetClientRect(g_hDlg, &rc);
	g_siDlg.cx = rc.right - rc.left;
	g_siDlg.cy = rc.bottom - rc.top;
	//保存树状控件句柄
	g_hTree = GetDlgItem(g_hDlg, IDC_TREE);
	//加载拖动光标
	g_hDragIcon		= LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DRAG));
	//加载正常光标
	g_hNormalIcon	= LoadCursor(NULL, IDC_ARROW);
	//加载窗口图标
	g_hWndIcon		= LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MAIN));
	//设置窗口大图标
	SendMessage(g_hDlg, WM_SETICON, ICON_BIG, (LPARAM)g_hWndIcon);
	//设置窗口小图标
	SendMessage(g_hDlg, WM_SETICON, ICON_SMALL, (LPARAM)g_hWndIcon);
	//获取拖动图标感应范围
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_DRAG);
	GetWindowRect(hCtrl, &g_rcDragIcon);
	ScreenToClientRect(&g_rcDragIcon);
	g_bInited = TRUE;
}
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp)
{
	int nID = LOWORD(wp);
	switch(nID)
	{
	//单击“刷新”按钮更新列表
	case IDOK:
		GetWindowList(NULL);
		break;
	//单击“关闭”按钮时结束对话框
	case IDCANCEL:
		SendMessage(g_hDlg, WM_CLOSE, 0, 0);
		break;
	}
}
//WM_SIZE消息响应
void OnSize(WPARAM wp, LPARAM lp)
{
	//只处理必要的消息，对于非必要消息直接返回
	switch(wp)
	{
	case SIZE_MAXHIDE:
	case SIZE_MAXSHOW:
	case SIZE_MINIMIZED:
		return;
	}
	//取得对话框的新大小
	int nWidth = LOWORD(lp);
	int nHeight = HIWORD(lp);
	//获得改变的差值
	int x, y;
	x = nWidth - g_siDlg.cx;
	y = nHeight - g_siDlg.cy;
	//开始移动控件，做相应的初始化
	HDWP hDwp = BeginDeferWindowPos(5);
	if(hDwp == NULL)
		return;
	//移动树形控件
	hDwp = MoveCtrl(hDwp, IDC_TREE, x, y, FALSE, FALSE, FALSE, TRUE);
	//移动文本框
	hDwp = MoveCtrl(hDwp, IDC_EDT_DETAIL, x, y, FALSE, FALSE, TRUE, TRUE);
	//移动“枚举所有窗体”按钮
	hDwp = MoveCtrl(hDwp, IDOK, x, y, FALSE, TRUE, FALSE, TRUE);
	//移动“拖动”图标
	hDwp = MoveCtrl(hDwp, IDC_DRAG, x, y, FALSE, TRUE, FALSE, TRUE);
	//移动提示文本
	hDwp = MoveCtrl(hDwp, IDC_TIP, x, y, FALSE, TRUE, FALSE, TRUE);
	//结束移动，使所有控件一次性完成移动
	EndDeferWindowPos(hDwp);
	//更新拖动图标感应范围
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_DRAG);
	GetWindowRect(hCtrl, &g_rcDragIcon);
	ScreenToClientRect(&g_rcDragIcon);
	//保存当前大小
	g_siDlg.cx = nWidth;
	g_siDlg.cy = nHeight;
}
//按照指定规则移动某个控件
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom)
{
	//获取控件句柄
	HWND hCtrl = GetDlgItem(g_hDlg, nID);
	//取得控件位置和大小
	RECT rc = {0};
	GetWindowRect(hCtrl, &rc);
	//将屏幕坐标转换为窗口坐标
	ScreenToClientRect(&rc);
	//根据选项改变位置和大小
	if(bLeft)
		rc.left += x;
	if(bTop)
		rc.top += y;
	if(bRight)
		rc.right += x;
	if(bBottom)
		rc.bottom += y;
	//移动控件
	return DeferWindowPos(hDwp, hCtrl, 0, rc.left, rc.top, 
		rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
}
//WM_LBUTTONDOWN消息响应
void OnLButtonDown(UINT nType, int x, int y)
{
	//当鼠标在拖动控件感应范围内按下时，进入拖动状态
	if(x >= g_rcDragIcon.left && x <= g_rcDragIcon.right 
		&& y >= g_rcDragIcon.top && y <= g_rcDragIcon.bottom)
	{
		g_bDragging = TRUE;
		//改变光标
		SetCursor(g_hDragIcon);
		//开始捕捉鼠标
		SetCapture(g_hDlg);
	}
}
//WM_LBUTTONUP消息响应
void OnLButtonUp(UINT nType, int x, int y)
{
	if(g_bDragging)
	{
		//恢复光标
		SetCursor(g_hNormalIcon);
		//释放鼠标捕获
		ReleaseCapture();
		//得到当前鼠标位置
		POINT pt = {x, y};
		//将窗体坐标转换为屏幕坐标
		ClientToScreen(g_hDlg, &pt);
		//获取该坐标的窗口句柄
		HWND hWnd = WindowFromPoint(pt);
		if(hWnd != NULL)
			GetWindowList(hWnd);
		else
			MessageBeep(MB_ICONEXCLAMATION);
	}
}
//树形控件选中项改变消息
void OnTreeSelChanged(LPNMHDR pnmh)
{
	//获取消息参数
	LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)pnmh;
	//获取变为选中状态的节点中保存的窗口句柄
	HWND hWnd = (HWND)pnmtv->itemNew.lParam;
	//获取窗口信息
	TCHAR	szBuf[1024]			= {0};
	RECT	rc					= {0};
	TCHAR	szClass[MAX_PATH]	= {0};
	TCHAR	szText[MAX_PATH]	= {0};
	//获取窗口位置
	GetWindowRect(hWnd, &rc);
	//获取窗口类名
	GetClassName(hWnd, szClass, MAX_PATH);
	//获取窗口文本
	GetWindowText(hWnd, szText, MAX_PATH);
	_stprintf(szBuf, 
		_T("句柄：0x%.8X\r\n文本：%s\r\n类名：%s\r\n位置：%d,%d,%d,%d\r\n"), 
		hWnd, szText, szClass, rc.left, rc.top, rc.right, rc.bottom);
	//将信息显示到界面上
	SetDlgItemText(g_hDlg, IDC_EDT_DETAIL, szBuf);
}
//将屏幕坐标转换为窗体坐标
void ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(g_hDlg, (LPPOINT)prc);
	ScreenToClient(g_hDlg, ((LPPOINT)prc) + 1);	
}
//将窗体坐标转换为屏幕坐标
void ClientToScreenRect(LPRECT prc)
{
	ClientToScreen(g_hDlg, (LPPOINT)prc);
	ClientToScreen(g_hDlg, ((LPPOINT)prc) + 1);		
}
//取得窗口列表
void GetWindowList(HWND hWnd)
{
	//清除树
	TreeView_DeleteAllItems(g_hTree);
	//是否获取整个系统中窗口
	if(hWnd == NULL)
		hWnd = GetDesktopWindow();
	//递归获取所有窗口
	GetListFunc(hWnd, TVI_ROOT);
	//得到树的根节点
	HTREEITEM hRoot = TreeView_GetRoot(g_hTree);
	//选中根节点
	if(hRoot != NULL)
		TreeView_SelectItem(g_hTree, hRoot);
}
//获取窗口中子窗口的递归函数
void GetListFunc(HWND hWnd, HTREEITEM hItem)
{
	//得到窗口文本
	TCHAR szBuf[MAX_PATH] = {0};
	GetWindowText(hWnd, szBuf, MAX_PATH);
	//如果文本为空，获取其类名
	if(*szBuf == _T('\0'))
	{
		*szBuf = _T('[');
		GetClassName(hWnd, szBuf+1, MAX_PATH - 2);
		_tcscat(szBuf, _T("]"));
	}
	//插入节点
	TV_INSERTSTRUCT tis = {0};
	tis.hInsertAfter	= TVI_LAST;
	tis.hParent			= hItem;
	tis.item.mask		= TVIF_TEXT | TVIF_PARAM;
	tis.item.pszText	= szBuf;
	tis.item.lParam		= (LPARAM)hWnd;
	HTREEITEM hChildItem = TreeView_InsertItem(g_hTree, &tis);
	//继续枚举
	EnumChildWindows(hWnd, EnumFunc, (LPARAM)hChildItem);
}
//枚举窗口的回调函数
BOOL CALLBACK EnumFunc(HWND hwnd, LPARAM lParam)
{
	GetListFunc(hwnd, (HTREEITEM)lParam);
	return TRUE;
}