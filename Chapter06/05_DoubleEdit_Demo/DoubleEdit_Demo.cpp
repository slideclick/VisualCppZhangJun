// DoubleEdit_Demo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "..\..\comm\DoubleEdit.h"

//double�ı���
CDoubleEdit g_edit;

//�Ի������
BOOL WINAPI DlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		//��ʼ���Ի��򣬽�double�ı���Ϳؼ�����
		g_edit.Attach(GetDlgItem(hDlg, IDC_EDT_INPUT));
		return TRUE;
	case WM_DESTROY:
		//�Ի��򼴽����٣�ȡ��double�ı���Ϳؼ��Ĺ���
		g_edit.Detach();
		 return TRUE;
	case WM_COMMAND:
		if (LOWORD(wp) == IDCANCEL)
		{
			//�����˹رհ�ť�������Ի���
			EndDialog(hDlg, 0);
		}
		else if(LOWORD(wp) == IDOK)
		{
			//��ȡ�������ֵ������ʾ
			double dValue = 0;
			if(g_edit.GetDoubleValue(&dValue))
			{
				TCHAR szBuf[128] = {0};
				_stprintf(szBuf, _T("�������ֵΪ��%.10f"), dValue);
				SetDlgItemText(hDlg, IDC_RESULT, szBuf);
			}
			else
			{
				SetDlgItemText(hDlg, IDC_RESULT, _T("û�����롣"));
			}
		}
	default:
		return FALSE;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	//Ӧ�ó�����ڣ������Ի���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
	return 0;
}
