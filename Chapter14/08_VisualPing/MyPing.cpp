// MyPing.cpp: implementation of the CMyPing class.
//
//////////////////////////////////////////////////////////////////////
#include "MyPing.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyPing::CMyPing()
{
	//变量初始化
	m_hHost			=	NULL;
	m_socket		=	INVALID_SOCKET;
	m_dwDestIP		=	0;
	m_dwInterval	=	0;
	m_dwTimeout		=	0;
	m_hRunEvent		=	NULL;
	m_hThread		=	NULL;
}
CMyPing::~CMyPing()
{
}
//初始化对象
BOOL CMyPing::StartPing(HWND hHost, LPCTSTR lpDestHost, 
			UINT nMsgID, DWORD dwInterval, DWORD dwTimeout)
{
	DWORD dwErr;
	//保存参数
	m_hHost		 = hHost;
	m_nMsgID	 = nMsgID;
	m_dwInterval = dwInterval;
	m_dwTimeout	 = dwTimeout;
	//获取目标主机IP
	struct hostent* dest = gethostbyname(lpDestHost);
	if(dest == NULL)
	{
		dwErr = WSAGetLastError();
		DebugPrint("错误: 无法解析的主机名%s,%.8X.\n", lpDestHost, dwErr);
		return FALSE;
	}
	m_dwDestIP = *(DWORD*)dest->h_addr_list[0];
	//创建原始套接字
	m_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(m_socket == INVALID_SOCKET)
	{
		dwErr = WSAGetLastError();
		DebugPrint(_T("创建套接字失败:%.8X.\n"), dwErr);
		return FALSE;
	}
	int nTimeOut = m_dwTimeout;
	//设置接收超时
	int nRet = setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, 
		(const char*)&nTimeOut, sizeof(nTimeOut));
	if(nRet == SOCKET_ERROR)
	{
		dwErr = WSAGetLastError();
		DebugPrint(_T("设置接收超时时错误:%.8X.\n"), dwErr);
		return FALSE;
	}
	//创建事件对象，该对象用于确定线程退出和线程延时
	m_hRunEvent = CreateEvent(NULL, TRUE, FALSE, _T("Ping_Thread_Event"));
	//启动线程
	UINT nID;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, WorkProc, this, 0, &nID);
	//CloseHandle(hThread);
	return TRUE;
}
//释放对象创建的资源
void  CMyPing::Release()
{
	//将事件对象设置为有信号，使线程结束
	SetEvent(m_hRunEvent);
	//等待线程结束
	DWORD dwWait = WaitForSingleObject(m_hThread, m_dwTimeout * 2);
	if(dwWait != WAIT_OBJECT_0)
		DebugPrint(_T("警告，线程可能未正常关闭...\n"));
	CloseHandle(m_hThread);
	//释放事件对象
	CloseHandle(m_hRunEvent);
	m_hRunEvent = NULL;
	//释放套接字
	closesocket(m_socket);
	m_socket = INVALID_SOCKET;
}
//输出调试信息
void CMyPing::DebugPrint(LPCTSTR lpMsg, ...)
{
#ifdef _DEBUG
	//根据参数格式化文本
	TCHAR szErr[1024] = {0};
	va_list pArgs;
    va_start(pArgs, lpMsg);
    _vsntprintf(szErr, 1020, lpMsg, pArgs);
    va_end(pArgs);
	//输出调试信息
	OutputDebugString(szErr);
#endif
}
//计算校验和
WORD CMyPing::GetCheckSum(char *pBuf, int nLen)
{
	WORD *pwBuf = (WORD *)pBuf;
	UINT nSum = 0;
	while(nLen > 1)
	{
		nSum += *pwBuf;
		++pwBuf;
		nLen -= sizeof(WORD);
	}
	if(nLen)
	{
		nSum += *(BYTE*)pwBuf;
	}
	nSum = (nSum >> 16) + (nSum & 0xffff);
	nSum += (nSum>>16);
	return (WORD)(~nSum);
}
//Ping线程函数
UINT CALLBACK CMyPing::WorkProc(LPVOID p)
{
	//保存传来的类指针
	CMyPing *pMyPing = (CMyPing *)p;
	//循环中要用到的变量
	struct sockaddr_in destAddr = {0};
	char bySendBuf[sizeof(ICMP_HDR)+32] = {0};
	PICMP_HDR pIcmp = (PICMP_HDR)bySendBuf;
	char byRecvBuf[1024] = {0};
	int nSeq = 0;
	int nRet = 0;
	int nLen = 0;
	DWORD dwErr = 0;
	DWORD dwTicks;
	DWORD dwTime;
	UINT  nFlag;
	DWORD dwWait;
	//生成目标主机地址
	destAddr.sin_family = AF_INET;
	destAddr.sin_addr.s_addr = pMyPing->m_dwDestIP;
	destAddr.sin_port = htons(0);
	//创建ICMP封包，8代表回显请求包
	pIcmp->icmp_type = 8;
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (unsigned short)GetCurrentProcessId();
	pIcmp->icmp_sequence = 0;
	memset(&bySendBuf[sizeof(ICMP_HDR)], 0xA, 32);
	//循环Ping目标主机
	while(TRUE)
	{
		dwTime = 0;
		nFlag  = 4;
		//包序号加1
		++nSeq;
		//填充ICMP包数据
		pIcmp->icmp_checksum = 0;
		pIcmp->icmp_sequence = nSeq;
		pIcmp->imcp_timestamp = GetTickCount();
		pIcmp->icmp_checksum = CMyPing::GetCheckSum(
			bySendBuf, sizeof(ICMP_HDR)+32);
		//发送ICMP包
		nRet = sendto(pMyPing->m_socket, bySendBuf, sizeof(ICMP_HDR)+32, 
			0, (SOCKADDR*)&destAddr, sizeof(destAddr));
		if(nRet == SOCKET_ERROR)
		{
			//发送失败
			dwErr = WSAGetLastError();
			DebugPrint(_T("发送ICMP包时失败,0x%.8X.\n"), dwErr);
			return 0;
		}
		//循环接收应答包
		while(TRUE)
		{
			//如果在超时时间到来还没接收到正确的回应，则超时退出
			dwTicks = GetTickCount();
			if(dwTicks - pIcmp->imcp_timestamp >= pMyPing->m_dwTimeout)
			{
				DebugPrint("Wait timed out.\n");
				nFlag = 3;
				break;
			}
			//接收数据
			memset(byRecvBuf, 0, sizeof(byRecvBuf));
			nLen = sizeof(destAddr);
			nRet = recvfrom(pMyPing->m_socket, byRecvBuf, sizeof(byRecvBuf), 
				0, (SOCKADDR*)&destAddr, &nLen);
			if(nRet == SOCKET_ERROR)
			{
				dwErr = WSAGetLastError();
				//超时
				if(dwErr == WSAETIMEDOUT)
				{
					DebugPrint(_T("Request timed out.\n"));
					nFlag = 1;
				}
				//其它错误
				else
				{
					DebugPrint(_T("接收ICMP包时失败,0x%.8X.\n"), dwErr);
					nFlag = 2;
				}
				//退出接收循环，继续主循环
				break;
			}
			
			//解析收到的数据包
			dwTicks = GetTickCount();
			if(nRet < sizeof(IP_HDR) + sizeof(ICMP_HDR))
			{
				//数据包长度有误
				DebugPrint(_T("接收到异常数据包,从:%s.\n"), 
					inet_ntoa(destAddr.sin_addr));
				nFlag = 3;
			}
			else
			{
				PICMP_HDR pRecvIcmp = (PICMP_HDR)&byRecvBuf[sizeof(IP_HDR)];
				if(pRecvIcmp->icmp_type != 0)
				{
					//数据包类型不对，不是回显应答包
					DebugPrint(_T("收到错误的应答类型:%d.\n"), 
						pRecvIcmp->icmp_type);
					nFlag = 3;
				}
				else
				{
					if(pRecvIcmp->icmp_id != GetCurrentProcessId())
					{
						//数据包ID不对
						DebugPrint(_T("收到非本进程发出的应答包.\n"));
						nFlag = 3;
					}
					else if(pRecvIcmp->icmp_sequence != pIcmp->icmp_sequence)
					{
						//数据包序号不对
						DebugPrint(_T("收到非预期序号的包.\n"));
						nFlag = 3;
					}
					else
					{
						//接收到正常数据
						nFlag = 0;
						dwTime = dwTicks - pRecvIcmp->imcp_timestamp;
						DebugPrint(_T("收到回应包，序号=%d,Time=%d.\n"), 
							pRecvIcmp->icmp_sequence, dwTime);
						//退出接收循环，继续主循环
						break;
					}
				}
			}
		}//End of 循环接收应答包
		if(nFlag < 3)
		{
			//将Ping值发送给窗口
			PostMessage(pMyPing->m_hHost, pMyPing->m_nMsgID, nFlag, dwTime);
			//等待事件，如果没信号，达到延时的目的。
			//如果有信号，代表需要立即结束线程
			dwWait = WaitForSingleObject(pMyPing->m_hRunEvent, pMyPing->m_dwInterval);
			if(dwWait != WAIT_TIMEOUT)
			{
				DebugPrint(_T("End Thread\n"));
				break;
			}
		}
		else
		{
			//如果nFlag为3，代表数据错误，继续接收
		}
	}//End of 循环Ping目标主机
	return 0;
}