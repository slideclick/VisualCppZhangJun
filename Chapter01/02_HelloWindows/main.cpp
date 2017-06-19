//必须的头文件
#include <windows.h>

//全局的WinMain函数，整个应用程序的入口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPTSTR lpCmdLine, int nCmdShow)
{
	//弹出一个系统对话框
	MessageBox(NULL, "Hello Windows!", 
		"第一个Windows应用程序", MB_OK | MB_ICONINFORMATION);
	//退出函数，结束应用程序
	return 0;
}
