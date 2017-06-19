#define UNICODE
#define _UNICODE
#define _WIN32_WINNT   0x0400 

#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <shlobj.h>
#include "resource.h"

//�궨��
#define FILE_NOTIFY_CHANGE_ALL (FILE_NOTIFY_CHANGE_FILE_NAME|\
								FILE_NOTIFY_CHANGE_DIR_NAME|\
								FILE_NOTIFY_CHANGE_ATTRIBUTES|\
								FILE_NOTIFY_CHANGE_SIZE|\
								FILE_NOTIFY_CHANGE_LAST_WRITE|\
								FILE_NOTIFY_CHANGE_LAST_ACCESS|\
								FILE_NOTIFY_CHANGE_CREATION|\
								FILE_NOTIFY_CHANGE_SECURITY)
#define FNI FILE_NOTIFY_INFORMATION
//ȫ�ֱ�������
HINSTANCE	g_hInst;
HWND		g_hDlg;
HWND		g_hEdit;
TCHAR		g_szDir[MAX_PATH];
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
	//��ʼ��ȫ�ֱ���
	g_hInst		= hInstance;
	g_hDlg		= NULL;
	g_hEdit		= NULL;
	*g_szDir	= _T('\0');
	//��ʾ�Ի���
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
		g_hEdit = GetDlgItem(hDlg, IDC_EDT_LOG);
		SendMessage(g_hEdit, EM_LIMITTEXT, 0, 0);
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
//��ť������Ӧ
BOOL OnCommand(UINT nID)
{
	switch(nID)
	{
	case IDC_BTN_BEGIN:
		{
			//����������һ��Ŀ¼�Լ��
			BROWSEINFO bi = {0};
			LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
			if(pidl != NULL)
			{
				SHGetPathFromIDList(pidl, g_szDir);
				EnableWindow(GetDlgItem(g_hDlg, IDC_BTN_BEGIN), FALSE);
				//��ʼ���
				_beginthread(WatchThread, 0, NULL);
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
//����߳�
void WatchThread(LPVOID)
{
	//��Ŀ¼�Ա���
	HANDLE hDir = CreateFile(
		g_szDir, 
		FILE_LIST_DIRECTORY,		//�����Ȩ��
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_BACKUP_SEMANTICS, //�����ѡ��
		NULL);
	if(INVALID_HANDLE_VALUE != hDir)
	{
		char buf[5*(sizeof(FNI) + sizeof(WCHAR)*MAX_PATH)];
		
		DWORD dwRead;
		FNI *pNotify;
		LPCTSTR lpChange;
		WCHAR szFile[MAX_PATH];
		while(TRUE)
		{
			//ͬ����ʽ��ñ仯֪ͨ
			if( ReadDirectoryChangesW(hDir, buf, 
				sizeof(buf), 
				TRUE,					//������Ŀ¼
				FILE_NOTIFY_CHANGE_ALL, //������б仯
				&dwRead,
				NULL,
				NULL))
			{ 
				//�����仯����
				pNotify = (FNI *)buf;
				while(TRUE) 
				{
					switch(pNotify->Action) 
					{
					case FILE_ACTION_ADDED:
						lpChange = _T("׷��");
						break;
					case FILE_ACTION_REMOVED:
						lpChange = _T("ɾ��");
						break;
					case FILE_ACTION_MODIFIED:
						lpChange = _T("�޸�");
						break;
					case FILE_ACTION_RENAMED_OLD_NAME:
					case FILE_ACTION_RENAMED_NEW_NAME:
						lpChange = _T("����");
						break;
					default:
						lpChange = _T("δ֪");
						break;
					}
					_tcsncpy(szFile, pNotify->FileName, pNotify->FileNameLength/sizeof(WCHAR));
					szFile[pNotify->FileNameLength/sizeof(WCHAR)] = _T('\0');
					//��ʾ�仯������
					AppendNotify(lpChange, szFile);
					//������һ��֪ͨ
					if(!pNotify->NextEntryOffset)
						break;
					pNotify = (FNI *)((char *)pNotify + pNotify->NextEntryOffset);
				} 
			}
			else
			{
				break;
			}
		}
	}
}
//���ı���׷������
void AppendNotify(LPCTSTR lpChange, LPCTSTR lpFile)
{
	TCHAR szText[MAX_PATH * 2] = {0};
	SYSTEMTIME time = {0};
	GetLocalTime(&time);
	_stprintf(szText, _T("%.2d:%.2d%.2d %s %s\r\n"), 
		time.wHour, time.wMinute, time.wSecond, lpChange, lpFile);
	int nTotleLen = SendMessage(g_hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(g_hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	SendMessage(g_hEdit, EM_REPLACESEL, FALSE, (LPARAM)szText);
}