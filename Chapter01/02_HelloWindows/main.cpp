//�����ͷ�ļ�
#include <windows.h>

//ȫ�ֵ�WinMain����������Ӧ�ó�������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPTSTR lpCmdLine, int nCmdShow)
{
	//����һ��ϵͳ�Ի���
	MessageBox(NULL, "Hello Windows!", 
		"��һ��WindowsӦ�ó���", MB_OK | MB_ICONINFORMATION);
	//�˳�����������Ӧ�ó���
	return 0;
}
