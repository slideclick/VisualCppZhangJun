//引入必须的头文件
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//应用程序入口
int main(int argc, char* argv[])
{
	int nAddend = 0, nSummand = 0;
	//在控制台输出欢迎字符
	printf("Hello Console!\n-----------\n");
	//输入加数
	char chTemp = 0;
	while(chTemp < '0' || chTemp > '9')
	{
		printf("请输入加数：\n");
		chTemp = getch();
	}
	printf("%c\n", chTemp);
	//得到加数
	nAddend = chTemp - '0';
	//输入被加数
	chTemp = 0;
	while(chTemp < '0' || chTemp > '9')
	{
		printf("请输入被加数：\n");
		chTemp = getch();
	}
	printf("%c\n", chTemp);
	nSummand = chTemp - '0';
	//输出计算结果
	printf("计算结果为：\n%d + %d = %d\n", 
		nAddend, nSummand, nAddend + nSummand);
	//暂停，直到任意键按下
	system("pause");
	//退出主函数，意味着应用程序结束
	return 0;
}