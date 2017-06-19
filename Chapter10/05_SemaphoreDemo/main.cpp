#include <windows.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
#include <stdio.h>

//�ź�������
HANDLE g_hSemaphore;

//�̺߳���
void ThreadProc(LPVOID p)
{
	TCHAR szMsg[128] = {0};
	sprintf(szMsg, "�߳�%d�����ˡ�\n", p);
	OutputDebugString(szMsg);

	//�����ʱһ��ʱ��
	srand(time(0) * (int)p);
	Sleep(rand()%500);
	//�ȴ��ź��������ȴ�15��
	DWORD dwWait = WaitForSingleObject(g_hSemaphore, 15000);
	if(dwWait == WAIT_OBJECT_0)
	{
		//�õ��ź����������Ϣ
		MessageBox(NULL, szMsg, szMsg, MB_OK|MB_ICONINFORMATION);
		//�ͷ���Դ�����Ӽ���ֵ
		ReleaseSemaphore(g_hSemaphore, 1, NULL);
	}
	else
		OutputDebugString("�ȴ�ʧ�ܡ�\n");
}

//�������
int main()
{
	//����һ�������ơ�������Ϊ2����ʼ����Ϊ2���ź���
	g_hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);
	//����3���߳�
	HANDLE hThreads[3];
	hThreads[0] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)1);
	hThreads[1] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)2);
	hThreads[2] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)3);

	//�ȴ��߳̽���
	WaitForMultipleObjects(3, hThreads, TRUE, 20000);
	CloseHandle(g_hSemaphore);
	system("pause");
	//�ͷ��ź�����Դ
	return 0;
}