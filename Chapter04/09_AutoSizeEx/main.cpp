#include <windows.h>
#include "resource.h"

//ȫ�ֱ�������
//���Ի���Ĵ��ھ��
HWND g_hWnd = NULL;
//�Ի���ı�֮ǰ�Ĵ�С
SIZE g_siDlg = {0};

//��������
//�Ի�����̺���
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp);
//WM_SIZE��Ϣ��Ӧ
void OnSize(WPARAM wp, LPARAM lp);
//����ָ�������ƶ�ĳ���ؼ�
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom);
//����Ļ����ת��Ϊ��������
void ScreenToClientRect(LPRECT prc);

//Ӧ�ó������ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
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
		{
			//���洰��ԭʼ�ߴ�
			RECT rc = {0};
			GetClientRect(hwndDlg, &rc);
			g_siDlg.cx = rc.right - rc.left;
			g_siDlg.cy = rc.bottom - rc.top;
			//���洰�ھ��
			g_hWnd = hwndDlg;
			return 1;
		}
	case WM_COMMAND:		//��������
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//�رնԻ���
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_SIZE:			//�Ի����С�ı�
		OnSize(wParam, lParam);
		return 1;
	default:
		break;
	}
	//Ĭ�Ϸ���0
	return 0;
}
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp)
{
	int nID = LOWORD(wp);
	switch(nID)
	{
	//������ȷ������ȡ������ťʱ�����Ի���
	case IDOK:
	case IDCANCEL:
		SendMessage(g_hWnd, WM_CLOSE, 0, 0);
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
	HDWP hDwp = BeginDeferWindowPos(4);
	if(hDwp == NULL)
		return;
	//�ƶ���ȷ������ť
	hDwp = MoveCtrl(hDwp, IDOK, x, y, TRUE, FALSE, TRUE, FALSE);
	//�ƶ���ȡ������ť
	hDwp = MoveCtrl(hDwp, IDCANCEL, x, y, TRUE, FALSE, TRUE, FALSE);
	//�ƶ��ı���
	hDwp = MoveCtrl(hDwp, IDC_EDT_TEST, x, y, FALSE, FALSE, TRUE, TRUE);
	//�ƶ���̬�ı��ؼ�
	hDwp = MoveCtrl(hDwp, IDC_BOTTOM, x, y, FALSE, TRUE, FALSE, TRUE);
	//�����ƶ���ʹ���пؼ�һ��������ƶ�
	EndDeferWindowPos(hDwp);
	//���浱ǰ��С
	g_siDlg.cx = nWidth;
	g_siDlg.cy = nHeight;
}
//����ָ�������ƶ�ĳ���ؼ�
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom)
{
	//��ȡ�ؼ����
	HWND hCtrl = GetDlgItem(g_hWnd, nID);
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
	return DeferWindowPos(hDwp, hCtrl, 0, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
}
//����Ļ����ת��Ϊ��������
void ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(g_hWnd, (LPPOINT)prc);
	ScreenToClient(g_hWnd, ((LPPOINT)prc) + 1);	
}

