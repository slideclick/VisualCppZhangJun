//��������ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Ӧ�ó������
int main(int argc, char* argv[])
{
	int nAddend = 0, nSummand = 0;
	//�ڿ���̨�����ӭ�ַ�
	printf("Hello Console!\n-----------\n");
	//�������
	char chTemp = 0;
	while(chTemp < '0' || chTemp > '9')
	{
		printf("�����������\n");
		chTemp = getch();
	}
	printf("%c\n", chTemp);
	//�õ�����
	nAddend = chTemp - '0';
	//���뱻����
	chTemp = 0;
	while(chTemp < '0' || chTemp > '9')
	{
		printf("�����뱻������\n");
		chTemp = getch();
	}
	printf("%c\n", chTemp);
	nSummand = chTemp - '0';
	//���������
	printf("������Ϊ��\n%d + %d = %d\n", 
		nAddend, nSummand, nAddend + nSummand);
	//��ͣ��ֱ�����������
	system("pause");
	//�˳�����������ζ��Ӧ�ó������
	return 0;
}