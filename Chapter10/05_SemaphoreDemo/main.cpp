#include <windows.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
#include <stdio.h>

//信号量对象
HANDLE g_hSemaphore;

//线程函数
void ThreadProc(LPVOID p)
{
	TCHAR szMsg[128] = {0};
	sprintf(szMsg, "线程%d运行了。\n", p);
	OutputDebugString(szMsg);

	//随机延时一段时间
	srand(time(0) * (int)p);
	Sleep(rand()%500);
	//等待信号量，最多等待15秒
	DWORD dwWait = WaitForSingleObject(g_hSemaphore, 15000);
	if(dwWait == WAIT_OBJECT_0)
	{
		//得到信号量，输出信息
		MessageBox(NULL, szMsg, szMsg, MB_OK|MB_ICONINFORMATION);
		//释放资源，增加计数值
		ReleaseSemaphore(g_hSemaphore, 1, NULL);
	}
	else
		OutputDebugString("等待失败。\n");
}

//程序入口
int main()
{
	//建立一个无名称、最大计数为2，初始计数为2的信号量
	g_hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);
	//启动3个线程
	HANDLE hThreads[3];
	hThreads[0] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)1);
	hThreads[1] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)2);
	hThreads[2] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)3);

	//等待线程结束
	WaitForMultipleObjects(3, hThreads, TRUE, 20000);
	CloseHandle(g_hSemaphore);
	system("pause");
	//释放信号量资源
	return 0;
}