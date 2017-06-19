#include "main.h"


//----------------
//ȫ�ֱ�������
//-----------------
HINSTANCE g_hInst	=	NULL;
//���Ի���Ĵ��ھ��
HWND g_hDlg			=	NULL;
//���οؼ��ľ��
HWND g_hTree		=	NULL;
//�Ի���ı�֮ǰ�Ĵ�С
SIZE g_siDlg		=	{0};
//�Ի���ԭʼ��С
SIZE g_siOrig		=	{0};
BOOL g_bInited		=	FALSE;
//�����϶��Ŀؼ�����
RECT g_rcDragIcon	=	{0};
//�϶�ʱ�Ĺ��
HICON g_hDragIcon	=	NULL;
//����Ƿ����϶�״̬
BOOL g_bDragging		=	FALSE;
//�������
HICON g_hNormalIcon =	NULL;
//����ͼ��
HICON g_hWndIcon	=	NULL;

//------------------
//����ʵ��
//------------------
//Ӧ�ó������ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	//��ʼ�������ؼ�
	InitCommonControls();
	//����һ��ģʽ�Ի��򣬲��ȴ��Ի������
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
	return 0;
}
//�Ի�����̺���
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:		//�Ի����ʼ��
		//���洰�ھ��
		g_hDlg = hwndDlg;		
		OnInitDialog();
		return 1;
	case WM_COMMAND:		//��������
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//�رնԻ���
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_SIZE:			//�Ի����С�ı�
		OnSize(wParam, lParam);
		return 1;
		break;
	case WM_GETMINMAXINFO:	//��ѯ���������С�ߴ�
		{
			//���ƴ�����С�ߴ�
			LPMINMAXINFO lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMinTrackSize.x = g_siOrig.cx;
			lpmm->ptMinTrackSize.y = g_siOrig.cy;
		}
		return 1;
	case WM_LBUTTONDOWN:	//����������
		OnLButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
		return 1;
	case WM_LBUTTONUP:		//����Ҽ�����
		OnLButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
		return 1;
	case WM_ACTIVATE:		//���ڻ״̬�ı�
		if(wParam == WA_INACTIVE && g_bDragging)
		{
			//����϶�;�д���ʧȥ���㣬���������϶�
			BOOL b = ReleaseCapture();
			g_bDragging = FALSE;
		}
		return 1;
	case WM_NOTIFY:			//�ؼ�֪ͨ��Ϣ
		if(wParam == IDC_TREE)
		{
			//ֻ������״�ؼ���ѡ�иı�֪ͨ
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
	//Ĭ�Ϸ���0
	return 0;
}
//��ʼ���Ի���
void OnInitDialog()
{
	//���洰��ԭʼ�ߴ�
	RECT rc = {0};
	GetWindowRect(g_hDlg, &rc);
	g_siOrig.cx = rc.right - rc.left;
	g_siOrig.cy = rc.bottom - rc.top;
	//���洰�ڿͻ�����С
	GetClientRect(g_hDlg, &rc);
	g_siDlg.cx = rc.right - rc.left;
	g_siDlg.cy = rc.bottom - rc.top;
	//������״�ؼ����
	g_hTree = GetDlgItem(g_hDlg, IDC_TREE);
	//�����϶����
	g_hDragIcon		= LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DRAG));
	//�����������
	g_hNormalIcon	= LoadCursor(NULL, IDC_ARROW);
	//���ش���ͼ��
	g_hWndIcon		= LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MAIN));
	//���ô��ڴ�ͼ��
	SendMessage(g_hDlg, WM_SETICON, ICON_BIG, (LPARAM)g_hWndIcon);
	//���ô���Сͼ��
	SendMessage(g_hDlg, WM_SETICON, ICON_SMALL, (LPARAM)g_hWndIcon);
	//��ȡ�϶�ͼ���Ӧ��Χ
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_DRAG);
	GetWindowRect(hCtrl, &g_rcDragIcon);
	ScreenToClientRect(&g_rcDragIcon);
	g_bInited = TRUE;
}
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp)
{
	int nID = LOWORD(wp);
	switch(nID)
	{
	//������ˢ�¡���ť�����б�
	case IDOK:
		GetWindowList(NULL);
		break;
	//�������رա���ťʱ�����Ի���
	case IDCANCEL:
		SendMessage(g_hDlg, WM_CLOSE, 0, 0);
		break;
	}
}
//WM_SIZE��Ϣ��Ӧ
void OnSize(WPARAM wp, LPARAM lp)
{
	//ֻ�����Ҫ����Ϣ�����ڷǱ�Ҫ��Ϣֱ�ӷ���
	switch(wp)
	{
	case SIZE_MAXHIDE:
	case SIZE_MAXSHOW:
	case SIZE_MINIMIZED:
		return;
	}
	//ȡ�öԻ�����´�С
	int nWidth = LOWORD(lp);
	int nHeight = HIWORD(lp);
	//��øı�Ĳ�ֵ
	int x, y;
	x = nWidth - g_siDlg.cx;
	y = nHeight - g_siDlg.cy;
	//��ʼ�ƶ��ؼ�������Ӧ�ĳ�ʼ��
	HDWP hDwp = BeginDeferWindowPos(5);
	if(hDwp == NULL)
		return;
	//�ƶ����οؼ�
	hDwp = MoveCtrl(hDwp, IDC_TREE, x, y, FALSE, FALSE, FALSE, TRUE);
	//�ƶ��ı���
	hDwp = MoveCtrl(hDwp, IDC_EDT_DETAIL, x, y, FALSE, FALSE, TRUE, TRUE);
	//�ƶ���ö�����д��塱��ť
	hDwp = MoveCtrl(hDwp, IDOK, x, y, FALSE, TRUE, FALSE, TRUE);
	//�ƶ����϶���ͼ��
	hDwp = MoveCtrl(hDwp, IDC_DRAG, x, y, FALSE, TRUE, FALSE, TRUE);
	//�ƶ���ʾ�ı�
	hDwp = MoveCtrl(hDwp, IDC_TIP, x, y, FALSE, TRUE, FALSE, TRUE);
	//�����ƶ���ʹ���пؼ�һ��������ƶ�
	EndDeferWindowPos(hDwp);
	//�����϶�ͼ���Ӧ��Χ
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_DRAG);
	GetWindowRect(hCtrl, &g_rcDragIcon);
	ScreenToClientRect(&g_rcDragIcon);
	//���浱ǰ��С
	g_siDlg.cx = nWidth;
	g_siDlg.cy = nHeight;
}
//����ָ�������ƶ�ĳ���ؼ�
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom)
{
	//��ȡ�ؼ����
	HWND hCtrl = GetDlgItem(g_hDlg, nID);
	//ȡ�ÿؼ�λ�úʹ�С
	RECT rc = {0};
	GetWindowRect(hCtrl, &rc);
	//����Ļ����ת��Ϊ��������
	ScreenToClientRect(&rc);
	//����ѡ��ı�λ�úʹ�С
	if(bLeft)
		rc.left += x;
	if(bTop)
		rc.top += y;
	if(bRight)
		rc.right += x;
	if(bBottom)
		rc.bottom += y;
	//�ƶ��ؼ�
	return DeferWindowPos(hDwp, hCtrl, 0, rc.left, rc.top, 
		rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
}
//WM_LBUTTONDOWN��Ϣ��Ӧ
void OnLButtonDown(UINT nType, int x, int y)
{
	//��������϶��ؼ���Ӧ��Χ�ڰ���ʱ�������϶�״̬
	if(x >= g_rcDragIcon.left && x <= g_rcDragIcon.right 
		&& y >= g_rcDragIcon.top && y <= g_rcDragIcon.bottom)
	{
		g_bDragging = TRUE;
		//�ı���
		SetCursor(g_hDragIcon);
		//��ʼ��׽���
		SetCapture(g_hDlg);
	}
}
//WM_LBUTTONUP��Ϣ��Ӧ
void OnLButtonUp(UINT nType, int x, int y)
{
	if(g_bDragging)
	{
		//�ָ����
		SetCursor(g_hNormalIcon);
		//�ͷ���겶��
		ReleaseCapture();
		//�õ���ǰ���λ��
		POINT pt = {x, y};
		//����������ת��Ϊ��Ļ����
		ClientToScreen(g_hDlg, &pt);
		//��ȡ������Ĵ��ھ��
		HWND hWnd = WindowFromPoint(pt);
		if(hWnd != NULL)
			GetWindowList(hWnd);
		else
			MessageBeep(MB_ICONEXCLAMATION);
	}
}
//���οؼ�ѡ����ı���Ϣ
void OnTreeSelChanged(LPNMHDR pnmh)
{
	//��ȡ��Ϣ����
	LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)pnmh;
	//��ȡ��Ϊѡ��״̬�Ľڵ��б���Ĵ��ھ��
	HWND hWnd = (HWND)pnmtv->itemNew.lParam;
	//��ȡ������Ϣ
	TCHAR	szBuf[1024]			= {0};
	RECT	rc					= {0};
	TCHAR	szClass[MAX_PATH]	= {0};
	TCHAR	szText[MAX_PATH]	= {0};
	//��ȡ����λ��
	GetWindowRect(hWnd, &rc);
	//��ȡ��������
	GetClassName(hWnd, szClass, MAX_PATH);
	//��ȡ�����ı�
	GetWindowText(hWnd, szText, MAX_PATH);
	_stprintf(szBuf, 
		_T("�����0x%.8X\r\n�ı���%s\r\n������%s\r\nλ�ã�%d,%d,%d,%d\r\n"), 
		hWnd, szText, szClass, rc.left, rc.top, rc.right, rc.bottom);
	//����Ϣ��ʾ��������
	SetDlgItemText(g_hDlg, IDC_EDT_DETAIL, szBuf);
}
//����Ļ����ת��Ϊ��������
void ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(g_hDlg, (LPPOINT)prc);
	ScreenToClient(g_hDlg, ((LPPOINT)prc) + 1);	
}
//����������ת��Ϊ��Ļ����
void ClientToScreenRect(LPRECT prc)
{
	ClientToScreen(g_hDlg, (LPPOINT)prc);
	ClientToScreen(g_hDlg, ((LPPOINT)prc) + 1);		
}
//ȡ�ô����б�
void GetWindowList(HWND hWnd)
{
	//�����
	TreeView_DeleteAllItems(g_hTree);
	//�Ƿ��ȡ����ϵͳ�д���
	if(hWnd == NULL)
		hWnd = GetDesktopWindow();
	//�ݹ��ȡ���д���
	GetListFunc(hWnd, TVI_ROOT);
	//�õ����ĸ��ڵ�
	HTREEITEM hRoot = TreeView_GetRoot(g_hTree);
	//ѡ�и��ڵ�
	if(hRoot != NULL)
		TreeView_SelectItem(g_hTree, hRoot);
}
//��ȡ�������Ӵ��ڵĵݹ麯��
void GetListFunc(HWND hWnd, HTREEITEM hItem)
{
	//�õ������ı�
	TCHAR szBuf[MAX_PATH] = {0};
	GetWindowText(hWnd, szBuf, MAX_PATH);
	//����ı�Ϊ�գ���ȡ������
	if(*szBuf == _T('\0'))
	{
		*szBuf = _T('[');
		GetClassName(hWnd, szBuf+1, MAX_PATH - 2);
		_tcscat(szBuf, _T("]"));
	}
	//����ڵ�
	TV_INSERTSTRUCT tis = {0};
	tis.hInsertAfter	= TVI_LAST;
	tis.hParent			= hItem;
	tis.item.mask		= TVIF_TEXT | TVIF_PARAM;
	tis.item.pszText	= szBuf;
	tis.item.lParam		= (LPARAM)hWnd;
	HTREEITEM hChildItem = TreeView_InsertItem(g_hTree, &tis);
	//����ö��
	EnumChildWindows(hWnd, EnumFunc, (LPARAM)hChildItem);
}
//ö�ٴ��ڵĻص�����
BOOL CALLBACK EnumFunc(HWND hwnd, LPARAM lParam)
{
	GetListFunc(hwnd, (HTREEITEM)lParam);
	return TRUE;
}