#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

HANDLE hRun = NULL;
//线程函数
void ThreadProc(LPVOID p)
{
	//等待启动信号
	WaitForSingleObject(hRun, INFINITE);
	//输出一些信息
	for(int i=0; i<100; i++)
	{
		printf("线程%d的第%d次输出\n", p, i);
	}
}

int main()
{
	//建立一个初始状态无信号的事件对象
	CreateEvent(NULL, TRUE, FALSE, NULL);
	//建立3个线程普通线程
	HANDLE hThreads[3];
	for(int i=0; i<3; i++)
		hThreads[i] = (HANDLE)_beginthread(ThreadProc, 0, (LPVOID)(i+1));
	//设置第一个线程优先级低于标准
	SetThreadPriority(hThreads[0], THREAD_PRIORITY_BELOW_NORMAL);
	//设置第三个线程的优先级高于标准
	SetThreadPriority(hThreads[2], THREAD_PRIORITY_ABOVE_NORMAL);
	//发出信号，让线程同时运行
	SetEvent(hRun);
	//等待线程结束
	WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);
	//释放事件对象
	CloseHandle(hRun);

	system("pause");
	return 0;
}