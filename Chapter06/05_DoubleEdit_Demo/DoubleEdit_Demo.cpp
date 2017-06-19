// DoubleEdit_Demo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "..\..\comm\DoubleEdit.h"

//double文本框
CDoubleEdit g_edit;

//对话框过程
BOOL WINAPI DlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		//初始化对话框，将double文本框和控件关联
		g_edit.Attach(GetDlgItem(hDlg, IDC_EDT_INPUT));
		return TRUE;
	case WM_DESTROY:
		//对话框即将销毁，取消double文本框和控件的关联
		g_edit.Detach();
		 return TRUE;
	case WM_COMMAND:
		if (LOWORD(wp) == IDCANCEL)
		{
			//按下了关闭按钮，结束对话框
			EndDialog(hDlg, 0);
		}
		else if(LOWORD(wp) == IDOK)
		{
			//读取输入的数值，并显示
			double dValue = 0;
			if(g_edit.GetDoubleValue(&dValue))
			{
				TCHAR szBuf[128] = {0};
				_stprintf(szBuf, _T("输入的数值为：%.10f"), dValue);
				SetDlgItemText(hDlg, IDC_RESULT, szBuf);
			}
			else
			{
				SetDlgItemText(hDlg, IDC_RESULT, _T("没有输入。"));
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
 	//应用程序入口，弹出对话框
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
	return 0;
}
