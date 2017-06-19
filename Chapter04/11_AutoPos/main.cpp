#include <windows.h>
#include "resource.h"

//ȫ�ֱ�������
//���Ի���Ĵ��ھ��
HWND g_hWnd = NULL;
//�Ի���ı�֮ǰ�Ĵ�С
BOOL g_bAuto = FALSE;

//��������
//�Ի�����̺���
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp);

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
		g_hWnd = hwndDlg;
		SetDlgItemInt(g_hWnd, IDC_EDT_RANGE, 10, FALSE);
		return 1;
	case WM_COMMAND:		//��������
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//�رնԻ���
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_WINDOWPOSCHANGING:
		{
			//���ѡ���ˡ�ͣ������ѡ��
			if(g_bAuto)
			{
				//��ȡͣ����Χ
				int nRange = GetDlgItemInt(g_hWnd, IDC_EDT_RANGE, NULL, FALSE);
				if(nRange < 50 && nRange > 0)
				{
					//�õ���Ϣ����
					WINDOWPOS *wp = (WINDOWPOS *)lParam;
					//�������ͣ����Χ�ڣ�ʵ��ͣ��Ч��
					if(wp->x < nRange && wp->x > -nRange)
						wp->x = 0;
					if(wp->y < nRange)
						wp->y = 0;
				}
			}
		}
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
	//��ͣ������ѡ�򵥻�
	case IDC_CHK_AUTO:
		{
			//ȡ�ÿؼ����
			HWND hCtrl = GetDlgItem(g_hWnd, IDC_CHK_AUTO);
			//��ȡ�ؼ�ѡ��״̬
			UINT nCheck = SendMessage(hCtrl, BM_GETCHECK, 0, 0);
			//���ñ���ֵ
			g_bAuto = (nCheck == BST_CHECKED);
		}
		break;
	}
}
