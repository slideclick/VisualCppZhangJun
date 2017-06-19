//引入必须的头文件
#include <stdio.h>
#include <stdlib.h>

//宏定义，要排序的数字个数
#define MAX_NUM 10
//宏定义，判断数组中的数字，并将较大的一个向后移动
#define SWITCH(ar, i) if(ar[i] < ar[i + 1]){ \
	int nTemp = ar[i]; \
	ar[i] = nNums[i + 1]; \
	ar[i + 1] = nTemp;}

//应用程序入口函数
int main(int argc, char* argv[])
{
	int nNums[MAX_NUM];
	int nCount = 0;
	char chInput[16] = {0};
	//输入指定个数的数字
	while(nCount < MAX_NUM)
	{
		printf("请输入第%d个数字（回车确认）：\n", nCount + 1);
		*chInput = '\0';
		fgets(chInput, sizeof(chInput) - 1, stdin);
		nNums[nCount] = atoi(chInput);
		printf("%d\n", nNums[nCount]);
		nCount++;
	}
	//循环排序
	int x, y;
	for(x=0; x<MAX_NUM - 1; x++)
	{
		for(y=0; y<MAX_NUM-x-1; y++)
		{
			SWITCH(nNums, y);
		}
	}
	//输出排序结果
	printf("排序结果为：\n");
	for(x=0; x<MAX_NUM; x++)
	{
		printf("%d\n", nNums[x]);
	}
	//程序暂停
	system("pause");
	//退出函数，结束应用程序
	return 0;
}
