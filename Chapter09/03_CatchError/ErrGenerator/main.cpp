#include <windows.h>

//Ӧ�ó�����ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//�����������
	if(GetTickCount() % 2 == 0)
	{
		//��������Υ������
		CreateProcess(NULL, "", NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL);
		return 0;
	}
	else
	{
		//�������������
		int n = 0;
		n = 5/n;
		return n;
	}
}