#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"

//ȫ�ֱ�������
HINSTANCE	g_hInst;
HWND		g_hDlg;
HWND		g_hEdit;
//��������
BOOL WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp);
BOOL OnCommand(UINT nID);
void WatchThread(LPVOID);
void AppendNotify(LPCTSTR lpChange, LPCTSTR lpFile);

//Ӧ�ó������
int WINAPI WinMain(
				   HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nShowCmd)
{
	g_hInst		= hInstance;
	g_hDlg		= NULL;
	g_hEdit		= NULL;
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}
//�Ի������
BOOL WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
	BOOL bRet = TRUE;
	switch(uMsg)
	{
	case WM_INITDIALOG:
		g_hDlg = hDlg;
		g_hEdit = GetDlgItem(hDlg, IDC_EDT_RESULT);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		bRet = OnCommand(LOWORD(wp));
	default:
		bRet = FALSE;
	}
	return bRet;
}
//��ȡ���ʵĴ�С��λ
inline char GetRightUnit(unsigned __int64 &i64Size)
{
	if(i64Size > (ULONGLONG)1024 * 1024 * 1024 * 10)
	{
		i64Size /= (1024 * 1024 * 1024);
		return 'G';
	}
	else if(i64Size > 1024 * 1024 * 10)
	{
		i64Size /= (1024 * 1024);
		return 'M';		
	}
	else if(i64Size > 1024 * 10)
	{
		i64Size /= 1024;
		return 'K';		
	}
	else
		return 'B';
}
//��ȡ��ť
void OnOk()
{
	TCHAR szSpace[2048] = {0};
	TCHAR szTemp[256] = {0};
	TCHAR szDisk[1024] = {0};
	LPTSTR lp = szDisk;

	char chAvail, chTotal, chFree;
	unsigned __int64 i64Avail, i64Total, i64Free;
	//��ȡ�����������б�
	GetLogicalDriveStrings(1024, szDisk);
	UINT uType;
	LPCTSTR lpType;
	//ѭ����ȡ������������Ϣ
	while(*lp != 0)
	{
		//�ж�����������
		_tcscat(szSpace, lp);
		_tcscat(szSpace, _T("\t"));
		uType = GetDriveType(lp);
		switch(uType)
		{
		case DRIVE_RAMDISK:
			lpType = _T("�ڴ���̣�\t");
			break;
		case DRIVE_CDROM:
			lpType = _T("������������\t");
			break;
		case DRIVE_REMOTE:
			lpType = _T("������������\t");
			break;
		case DRIVE_FIXED:
			lpType = _T("�߼����̣�\t");
			break;
		case DRIVE_REMOVABLE:
			lpType = _T("���ƶ����̣�\t");
			break;
		case DRIVE_NO_ROOT_DIR:
			lpType = _T("�޸�Ŀ¼���̣�\t");
			break;
		case DRIVE_UNKNOWN:
		default:
			lpType = _T("δ֪���ͣ�\t");
			break;
		}
		_tcscat(szSpace, lpType);
		//��ȡ���̿ռ����
		if(!GetDiskFreeSpaceEx(lp, (PULARGE_INTEGER)&i64Avail, (PULARGE_INTEGER)&i64Total, (PULARGE_INTEGER)&i64Free))
		{
			_tcscat(szSpace, _T("�޷���ȡ��С��\r\n"));
		}
		else
		{
			chTotal = GetRightUnit(i64Total);
			chFree = GetRightUnit(i64Free);
			chAvail = GetRightUnit(i64Avail);
			_stprintf(szTemp, 
				_T("��С��%d%c��\t���У�%d%c��\t���ã�%d%c\r\n"),
				(int)i64Total, chTotal, (int)i64Free, chFree, (int)i64Avail, chAvail);
			_tcscat(szSpace, szTemp);
		}

		lp += _tcslen(lp) + 1;
	}
	//��ʾ���
	SetDlgItemText(g_hDlg, IDC_EDT_RESULT, szSpace);
}
//��ť�¼���Ӧ
BOOL OnCommand(UINT nID)
{
	switch(nID)
	{
	case IDOK:
		OnOk();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
