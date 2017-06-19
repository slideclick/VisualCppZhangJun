// UdpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
//ʹ��WinSock�����ͷ�ļ�
#include <WINSOCK.H>
//ʹ��WinSock����Ŀ��ļ�
#pragma comment(lib, "WSOCK32.LIB")

//������Ҫʹ�õ�WinSock���汾
#define SOCK_VER 2
//�����ͺ�������
SOCKET g_sock = 0;
void ErrMsg(DWORD dwErr);

//Ӧ�ó������
int main(int argc, char* argv[])
{
	//��ʼ������
	WSADATA wd = {0};
	int nStart = WSAStartup(MAKEWORD(SOCK_VER, 0), &wd);
	if(nStart = 0)
	{
		return 0;
	}
	if(LOBYTE(wd.wVersion) != 2)
	{
		return 0;
	}
	//����SOCKET
	g_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(g_sock == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return 0;
	}
	printf("Socket�����ɹ���\n");
	//�󶨵��˿�28000
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2800);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int nBind = bind(g_sock, (sockaddr *)&addr, sizeof(addr));
	if(nBind != 0)
	{
		ErrMsg(WSAGetLastError());
		return 0;
	}
	//ȡ���Ѱ󶨵Ķ˿ں�
	int nLen = sizeof(addr);
	getsockname(g_sock, (sockaddr *)&addr, &nLen);
	printf("Socket�ɹ��󶨵��˿ڣ�%d���ȴ�����...\n", ntohs(addr.sin_port));
	//�ȴ���������Ϣ
	sockaddr_in saClient = {0};
	int nFromLen = sizeof(saClient);
	char szBuff[256] = {0};
	recvfrom(g_sock, szBuff, 256, 0, (sockaddr *)&saClient, &nFromLen);
	printf("�յ���Ϣ����%s������%s,%d\n", 
		szBuff, inet_ntoa(saClient.sin_addr), ntohs(saClient.sin_port));
	//��ͻ��˷�����Ӧ
	strcpy(szBuff, "OK!");
	int nSent = sendto(g_sock, szBuff, strlen(szBuff) + 1, 0, (sockaddr *)&saClient, sizeof(saClient));
	if(nSent == 0)
		ErrMsg(WSAGetLastError());
	else
		printf("�ɹ�������Ӧ��\n");
	//�ر�SOCKET
	closesocket(g_sock);
	//�ȴ��û�����
	system("pause");
	//������
	WSACleanup();
	return 0;
}
//ȡ�ô�����ϸ����������
void ErrMsg(DWORD dwErr)
{
	char szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		szErr, 1024, NULL);
	printf(szErr);
}
