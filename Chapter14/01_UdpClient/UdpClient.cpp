// UdpClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
//Windows套接字所需的头文件
#include <WINSOCK.H>
//Windows套接字接口的库文件
#pragma comment(lib, "WSOCK32.LIB")

//程序使用的WinSock主版本
#define SOCK_VER 2
//变量和函数声明
SOCKET g_sock = 0;
void ErrMsg(DWORD dwErr);

//应用程序入口
int main(int argc, char* argv[])
{
	//初始化WinSock环境
	WSADATA wd = {0};
	int nStart = WSAStartup(MAKEWORD(SOCK_VER, 0), &wd);
	if(nStart = 0)
	{
		//初始化失败
		return 0;
	}
	//检测当前系统的WinSock版本是否支持所需版本
	if(LOBYTE(wd.wVersion) != 2)
	{
		return 0;
	}
	//创建一个UDP Socket
	g_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(g_sock == INVALID_SOCKET)
	{
		ErrMsg(WSAGetLastError());
		return 0;
	}
	printf("Socket创建成功\n");
	//发数据的目标地址
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2800);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//发出数据包
	char szBuff[] = "hello UDP!";
	int nSent = sendto(g_sock, szBuff, strlen(szBuff) + 1, 0, (sockaddr *)&addr, sizeof(addr));
	if(nSent == 0)
		ErrMsg(WSAGetLastError());
	else
		printf("信息成功发出，等待回应...\n");
	//等待回应
	sockaddr_in saServer = {0};
	int nFromLen = sizeof(saServer);
	*szBuff = '\0';
	int nRecv = recvfrom(g_sock, szBuff, 256, 0, (sockaddr *)&saServer, &nFromLen);
	if(SOCKET_ERROR == nRecv)
		ErrMsg(WSAGetLastError());
	else
		printf("收到回应：%s 从%s,%d\n", szBuff, inet_ntoa(saServer.sin_addr), ntohs(saServer.sin_port));
	//关闭套接字
	closesocket(g_sock);
	//等待用户输入
	system("pause");
	//清理SOCKET环境
	WSACleanup();
	return 0;
}
//获取错误详细信息，并输出
void ErrMsg(DWORD dwErr)
{
	char szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), szErr, 1024, NULL);
	printf(szErr);
}