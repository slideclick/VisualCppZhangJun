#include <windows.h>

//应用程序入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//随机产生错误
	if(GetTickCount() % 2 == 0)
	{
		//产生访问违例错误
		CreateProcess(NULL, "", NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL);
		return 0;
	}
	else
	{
		//产生被零除错误
		int n = 0;
		n = 5/n;
		return n;
	}
}