; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySocket
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MfcSock.h"

ClassCount=3
Class1=CMfcSockApp
Class2=CMfcSockDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CMySocket
Resource2=IDD_MFCSOCK_DIALOG

[CLS:CMfcSockApp]
Type=0
HeaderFile=MfcSock.h
ImplementationFile=MfcSock.cpp
Filter=N

[CLS:CMfcSockDlg]
Type=0
HeaderFile=MfcSockDlg.h
ImplementationFile=MfcSockDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MFCSOCK_DIALOG]
Type=1
Class=CMfcSockDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDT_IP,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDT_PORT,edit,1350631552
Control6=IDC_BTN_CONNECT,button,1342242816
Control7=IDC_EDT_INPUT,edit,1353781380
Control8=IDC_BTN_SEND,button,1342242816
Control9=IDC_EDT_OUTPUT,edit,1353779332

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CMySocket

