#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

HANDLE hRun = NULL;
//�̺߳���
void ThreadProc(LPVOID p)
{
	//�ȴ������ź�
	WaitForSingleObject(hRun, INFINITE);
	//���һЩ��Ϣ
	for(int i=0; i<100; i++)
	{
		printf("�߳�%d�ĵ�%d�����\n", p, i);
	}
}

int main()
{
	//����һ����ʼ״̬���źŵ��¼�����
	CreateEvent(NULL, TRUE, FALSE, NULL);
	//����3���߳���ͨ�߳�
	HANDLE hThreads[3];
	for(int i=0; i<3; i++)
		hThreads[i] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)(i+1));
	//���õ�һ���߳����ȼ����ڱ�׼
	SetThreadPriority(hThreads[0], THREAD_PRIORITY_BELOW_NORMAL);
	//���õ������̵߳����ȼ����ڱ�׼
	SetThreadPriority(hThreads[2], THREAD_PRIORITY_ABOVE_NORMAL);
	//�����źţ����߳�ͬʱ����
	SetEvent(hRun);
	//�ȴ��߳̽���
	WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);
	//�ͷ��¼�����
	CloseHandle(hRun);

	system("pause");
	return 0;
}