//��������ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>

//�궨�壬Ҫ��������ָ���
#define MAX_NUM 10
//�궨�壬�ж������е����֣������ϴ��һ������ƶ�
#define SWITCH(ar, i) if(ar[i] < ar[i + 1]){ \
	int nTemp = ar[i]; \
	ar[i] = nNums[i + 1]; \
	ar[i + 1] = nTemp;}

//Ӧ�ó�����ں���
int main(int argc, char* argv[])
{
	int nNums[MAX_NUM];
	int nCount = 0;
	char chInput[16] = {0};
	//����ָ������������
	while(nCount < MAX_NUM)
	{
		printf("�������%d�����֣��س�ȷ�ϣ���\n", nCount + 1);
		*chInput = '\0';
		fgets(chInput, sizeof(chInput) - 1, stdin);
		nNums[nCount] = atoi(chInput);
		printf("%d\n", nNums[nCount]);
		nCount++;
	}
	//ѭ������
	int x, y;
	for(x=0; x<MAX_NUM - 1; x++)
	{
		for(y=0; y<MAX_NUM-x-1; y++)
		{
			SWITCH(nNums, y);
		}
	}
	//���������
	printf("������Ϊ��\n");
	for(x=0; x<MAX_NUM; x++)
	{
		printf("%d\n", nNums[x]);
	}
	//������ͣ
	system("pause");
	//�˳�����������Ӧ�ó���
	return 0;
}
