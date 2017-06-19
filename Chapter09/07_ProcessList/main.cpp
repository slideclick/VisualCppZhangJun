#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>
#include <Psapi.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Psapi.lib")

//----------------
//ȫ�ֱ�������
//-----------------
//���Ի���Ĵ��ھ��
HWND g_hDlg = NULL;
//�б�ؼ��ľ��
HWND g_hList = NULL;
//�Ի���ı�֮ǰ�Ĵ�С
SIZE g_siDlg = {0};
//�Ի���ԭʼ��С
SIZE g_siOrig = {0};
//�б������ʱ��������
int g_nSortCol = -1;
//�б�ؼ�����ʱ��¼˳��
BOOL g_bSortAsc = TRUE;

//----------------
//��������
//----------------
//�Ի�����̺���
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//�Ի����ʼ����Ϣ����
void OnInitDialog();
//��ʼ���б�ؼ�
void InitList();
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp);
//WM_SIZE��Ϣ��Ӧ
void OnSize(WPARAM wp, LPARAM lp);
//��ʱ����Ϣ��Ӧ
void OnTimer();
//����ָ�������ƶ�ĳ���ؼ�
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom);
//����Ļ����ת��Ϊ��������
void ScreenToClientRect(LPRECT prc);
//��ȡ�����б�
BOOL GetProcessList();
//ȡ�ý�����ϸ��Ϣ����ʾ���б�ؼ���
void AddProcessRow(DWORD dwPID);
//�򿪻�رյ�ǰ���̵�DEBUGȨ��
BOOL SetDebugPrivilege(BOOL bEnable); 
//�б�ؼ�����ص�����
int CALLBACK ListSortFunc(
		LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

//------------------
//����ʵ��
//------------------
//Ӧ�ó������ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
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
	case WM_NOTIFY:			//�ؼ�֪ͨ��Ϣ
		if(wParam == IDC_LIST)
		{
			LPNMHDR pnmh = (LPNMHDR)lParam;
			//��Ӧ�б����ⵥ����Ϣ
			if(pnmh->code == LVN_COLUMNCLICK)
			{
				//ȡ����Ϣ����
				LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
				//�������������ź��ϴβ�ͬ
				if(g_nSortCol != pnmv->iSubItem)
				{
					//���е�һ������������
					g_bSortAsc = TRUE;
					//��¼�����
					g_nSortCol = pnmv->iSubItem;
				}
				else
				{
					//�ٴε���ʱ�����պ��ϴ��෴��˳������
					g_bSortAsc = (!g_bSortAsc);
				}
				//����������Ϣ
				ListView_SortItems(g_hList, ListSortFunc, pnmv->iSubItem);
				return 1;
			}
		}
		break;
	case WM_GETMINMAXINFO:
		{
			//���ƴ�����С�ߴ�
			LPMINMAXINFO lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMinTrackSize.x = g_siOrig.cx;
			lpmm->ptMinTrackSize.y = g_siOrig.cy;
		}
		return 1;
	case WM_TIMER:
		OnTimer();
		return 1;
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
	//�����б�ؼ����
	g_hList = GetDlgItem(g_hDlg, IDC_LIST);
	//��ʼ���б�ؼ�
	InitList();
	//�õ����Զ�ˢ�¡���ѡ��ؼ����
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_CHK_AUTO);
	//�ÿؼ�Ĭ��ѡ��
	SendMessage(hCtrl, BM_SETCHECK, BST_CHECKED, 0);
	//�����б�
	GetProcessList();
	//������ʱ��
	SetTimer(g_hDlg, 1, 4000, NULL);
}
//��ʼ���б�ؼ�
void InitList()
{
	//�ؼ�������
	const int nCount = 4;
	//ÿ�еĿ��
	int pWidth[nCount] = {50, 100, 50, 400};
	//ÿ�еı���
	LPTSTR pName[nCount] = 
		{_T("PID"), _T("��������"), _T("���ȼ�"), _T("EXE·��")};
	//ѭ��������
	LVCOLUMN col = {0};
	col.mask = LVCF_TEXT | LVCF_WIDTH;
	for(int i=0; i<nCount; i++)
	{
		col.cx = pWidth[i];
		col.pszText = pName[i];
		ListView_InsertColumn(g_hList, i, &col);
	}
	//�����б�ؼ����ʹ�䡰���С�ѡȡ
	SendMessage(g_hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT );
}
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp)
{
	int nID = LOWORD(wp);
	switch(nID)
	{
	//������ˢ�¡���ť�����б�
	case IDOK:
		GetProcessList();
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
	//�ƶ���ˢ�¡���ť
	hDwp = MoveCtrl(hDwp, IDOK, x, y, TRUE, FALSE, TRUE, FALSE);
	//�ƶ����رա���ť
	hDwp = MoveCtrl(hDwp, IDCANCEL, x, y, TRUE, FALSE, TRUE, FALSE);
	//�ƶ�����ʱˢ�¡���ѡ��
	hDwp = MoveCtrl(hDwp, IDC_CHK_AUTO, x, y, TRUE, TRUE, TRUE, TRUE);
	//�ƶ��ı���
	hDwp = MoveCtrl(hDwp, IDC_LIST, x, y, FALSE, FALSE, TRUE, TRUE);
	//�ƶ��ı���ؼ�
	hDwp = MoveCtrl(hDwp, IDC_EDT_MSG, x, y, FALSE, TRUE, TRUE, TRUE);
	//�����ƶ���ʹ���пؼ�һ��������ƶ�
	EndDeferWindowPos(hDwp);
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
//����Ļ����ת��Ϊ��������
void ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(g_hDlg, (LPPOINT)prc);
	ScreenToClient(g_hDlg, ((LPPOINT)prc) + 1);	
}
//��ʱ����Ϣ��Ӧ
void OnTimer()
{
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_CHK_AUTO);
	UINT nCheck = SendMessage(hCtrl, BM_GETCHECK, 0, 0);
	if(nCheck)
	{
		GetProcessList();
	}
}
//ȡ�õ�ǰϵͳ�����б�
BOOL GetProcessList()
{
	//����б�ؼ�
	ListView_DeleteAllItems(g_hList);
	//��ʼ�����������С
	int nLenArray = 32;
	//��������С���ֽ���
	int nLenBytes = nLenArray * sizeof(DWORD);;
	//���뻺����
	DWORD *pdwPID = new DWORD[nLenArray];
	DWORD dwNeeded = 0;
	//��ȡ�����б�
	BOOL bRet = EnumProcesses(pdwPID, nLenBytes, &dwNeeded);
	//������������������󻺳��������µõ������б�
	while(bRet && dwNeeded == nLenBytes)
	{
		delete []pdwPID;
		pdwPID = NULL;
		nLenArray += 32;
		nLenBytes = nLenArray * sizeof(DWORD);
		pdwPID = new DWORD[nLenArray];
		bRet = EnumProcesses(pdwPID, nLenBytes, &dwNeeded);
	}
	//�õ����̸���
	int nCount = dwNeeded / sizeof(DWORD);
	//����������ʾ��������
	TCHAR szCount[128];
	_stprintf(szCount, _T("��������%d"), nCount);
	SetDlgItemText(g_hDlg, IDC_EDT_MSG, szCount);
	//ȡ��DEBUGȨ��
	SetDebugPrivilege(TRUE);
	//ѭ����ȡÿ��������Ϣ
	DWORD dwPID;
	for(int i=0; i<nCount; i++)
	{
		dwPID = pdwPID[i];
		AddProcessRow(dwPID);
	}
	//�ͷŻ�����
	delete []pdwPID;
	//�ر�DEBUGȨ��
	SetDebugPrivilege(FALSE);
	//��������
	ListView_SortItems(g_hList, ListSortFunc, g_nSortCol < 0 ? 0 : g_nSortCol);
	return TRUE;
}
//ȡ�ý�����ϸ��Ϣ����ʾ���б�ؼ���
void AddProcessRow(DWORD dwPID)
{
	HANDLE	hProcess;
	HMODULE hModule;
	DWORD	dwPriority;
	TCHAR	szPID[32] = {0};
	TCHAR	szPriority[32] = {0};
	TCHAR	szBaseName[MAX_PATH] = {0};
	TCHAR	szFileName[MAX_PATH] = {0};
	int		nIndex;
	
	//���б�ؼ�����һ��
	LVITEM item = {0};
	item.mask	= LVIF_TEXT | LVIF_PARAM;
	item.iItem	= ListView_GetItemCount(g_hList);
	item.lParam	= dwPID;
	_stprintf(szPID, _T("%d"), dwPID);
	item.pszText = szPID;
	nIndex = ListView_InsertItem(g_hList, &item);
	if(nIndex < 0)
		DebugBreak();
	//�򿪽���	
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
	if(hProcess != NULL)
	{
		//�õ����̵ĵ�һ��ģ��
		BOOL	bRet;
		DWORD	dwNeeded;
		bRet =  EnumProcessModules(hProcess, &hModule, sizeof(HMODULE), &dwNeeded);
		if(bRet)
		{
			//ȡ�ý������ȼ�
			dwPriority = GetPriorityClass (hProcess); 
			_stprintf(szPriority, _T("%d"), dwPriority);
			//ȡ��ģ��ӳ������
			GetModuleBaseName(hProcess, hModule, szBaseName, MAX_PATH);
			//ȡ��ģ���ļ���
			GetModuleFileNameEx(hProcess, hModule, szFileName, MAX_PATH);
			//��ʾ���б�ؼ�
			ListView_SetItemText(g_hList, nIndex, 1, szBaseName);
			ListView_SetItemText(g_hList, nIndex, 2, szPriority);
			ListView_SetItemText(g_hList, nIndex, 3, szFileName);
		}
		//�رմ򿪵Ľ��̾��
		CloseHandle(hProcess);
	}	
}
//�򿪻�رյ�ǰ���̵�DEBUGȨ��
BOOL SetDebugPrivilege(BOOL bEnable) 
{ 
	HANDLE hToken; 
	BOOL bRet;
	//��ý��̷������ƾ��
	bRet = OpenProcessToken(GetCurrentProcess(),
		TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken);
	if(bRet)
	{ 
		TOKEN_PRIVILEGES TokenPrivileges; 
		TokenPrivileges.PrivilegeCount = 1; 
		//ȡ��DEBUGȨ�޵�LUID
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &TokenPrivileges.Privileges[0].Luid); 
		//���ݲ������򿪻�ر���ӦȨ��
		TokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0; 
		//����Ȩ��
		bRet = AdjustTokenPrivileges(hToken,FALSE,&TokenPrivileges,sizeof(TOKEN_PRIVILEGES),NULL,NULL); 
		//�رվ��
		CloseHandle(hToken); 
	} 
	return bRet; 
}
//�б�ؼ�����ص�����
int CALLBACK ListSortFunc(
		LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iFlag = g_bSortAsc ? 1 : -1;
	//����Ե�һ����������PID���������ͣ�ֱ�ӱȽϲ�����
	if(lParamSort == 0)
	{
		return (lParam1 - lParam2) * iFlag;
	}
	int nIndex1, nIndex2;
	TCHAR szText1[MAX_PATH] = {0};
	TCHAR szText2[MAX_PATH] = {0};
	//��ʼ�������б�����ṹ
	LVFINDINFO lv = {0};
	lv.flags = LVFI_PARAM;
	//���ݵ�һ��������������ҵ�������
	lv.lParam = lParam1;
	nIndex1 = ListView_FindItem(g_hList, -1, &lv);
	//���ݵڶ�����������ҵ�������
	lv.lParam = lParam2;
	nIndex2 = ListView_FindItem(g_hList, -1, &lv);
	//ȡ�õ�һ����ı�
	ListView_GetItemText(g_hList, nIndex1, lParamSort, szText1, MAX_PATH);
	//ȡ�õڶ�����ı�
	ListView_GetItemText(g_hList, nIndex2, lParamSort, szText2, MAX_PATH);
	//�Ƚ��ַ���
	int iCmp = _tcsicmp(szText1, szText2);
	return iCmp * iFlag;
}
