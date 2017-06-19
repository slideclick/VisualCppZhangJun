// UdpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
//使用WinSock所需的头文件
#include <WINSOCK.H>
//使用WinSock所需的库文件
#pragma comment(lib, "WSOCK32.LIB")

//程序中要使用的WinSock主版本
#define SOCK_VER 2
//变量和函数声明
SOCKET g_sock = 0;
void ErrMsg(DWORD dwErr);

//应用程序入口
int main(int argc, char* argv[])
{
	//初始化环境
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
	//创建SOCKET
	g_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(g_sock == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return 0;
	}
	printf("Socket创建成功！\n");
	//绑定到端口28000
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
	//取得已绑定的端口号
	int nLen = sizeof(addr);
	getsockname(g_sock, (sockaddr *)&addr, &nLen);
	printf("Socket成功绑定到端口：%d，等待数据...\n", ntohs(addr.sin_port));
	//等待并接收信息
	sockaddr_in saClient = {0};
	int nFromLen = sizeof(saClient);
	char szBuff[256] = {0};
	recvfrom(g_sock, szBuff, 256, 0, (sockaddr *)&saClient, &nFromLen);
	printf("收到信息：‘%s’，从%s,%d\n", 
		szBuff, inet_ntoa(saClient.sin_addr), ntohs(saClient.sin_port));
	//向客户端发出回应
	strcpy(szBuff, "OK!");
	int nSent = sendto(g_sock, szBuff, strlen(szBuff) + 1, 0, (sockaddr *)&saClient, sizeof(saClient));
	if(nSent == 0)
		ErrMsg(WSAGetLastError());
	else
		printf("成功发出回应！\n");
	//关闭SOCKET
	closesocket(g_sock);
	//等待用户输入
	system("pause");
	//清理环境
	WSACleanup();
	return 0;
}
//取得错误详细情况，并输出
void ErrMsg(DWORD dwErr)
{
	char szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		szErr, 1024, NULL);
	printf(szErr);
}
