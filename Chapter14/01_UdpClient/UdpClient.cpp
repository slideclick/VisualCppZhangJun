// UdpClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
//Windows�׽��������ͷ�ļ�
#include <WINSOCK.H>
//Windows�׽��ֽӿڵĿ��ļ�
#pragma comment(lib, "WSOCK32.LIB")

//����ʹ�õ�WinSock���汾
#define SOCK_VER 2
//�����ͺ�������
SOCKET g_sock = 0;
void ErrMsg(DWORD dwErr);

//Ӧ�ó������
int main(int argc, char* argv[])
{
	//��ʼ��WinSock����
	WSADATA wd = {0};
	int nStart = WSAStartup(MAKEWORD(SOCK_VER, 0), &wd);
	if(nStart = 0)
	{
		//��ʼ��ʧ��
		return 0;
	}
	//��⵱ǰϵͳ��WinSock�汾�Ƿ�֧������汾
	if(LOBYTE(wd.wVersion) != 2)
	{
		return 0;
	}
	//����һ��UDP Socket
	g_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(g_sock == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return 0;
	}
	printf("Socket�����ɹ�\n");
	//�����ݵ�Ŀ���ַ
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2800);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//�������ݰ�
	char szBuff[] = "hello UDP!";
	int nSent = sendto(g_sock, szBuff, strlen(szBuff) + 1, 0, (sockaddr *)&addr, sizeof(addr));
	if(nSent == 0)
		ErrMsg(WSAGetLastError());
	else
		printf("��Ϣ�ɹ��������ȴ���Ӧ...\n");
	//�ȴ���Ӧ
	sockaddr_in saServer = {0};
	int nFromLen = sizeof(saServer);
	*szBuff = '\0';
	int nRecv = recvfrom(g_sock, szBuff, 256, 0, (sockaddr *)&saServer, &nFromLen);
	if(SOCKET_ERROR == nRecv)
		ErrMsg(WSAGetLastError());
	else
		printf("�յ���Ӧ��%s ��%s,%d\n", szBuff, inet_ntoa(saServer.sin_addr), ntohs(saServer.sin_port));
	//�ر��׽���
	closesocket(g_sock);
	//�ȴ��û�����
	system("pause");
	//����SOCKET����
	WSACleanup();
	return 0;
}
//��ȡ������ϸ��Ϣ�������
void ErrMsg(DWORD dwErr)
{
	char szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), szErr, 1024, NULL);
	printf(szErr);
}