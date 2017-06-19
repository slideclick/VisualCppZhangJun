; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTcpClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TcpClient.h"

ClassCount=2
Class1=CTcpClientApp
Class2=CTcpClientDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_TCPCLIENT_DIALOG

[CLS:CTcpClientApp]
Type=0
HeaderFile=TcpClient.h
ImplementationFile=TcpClient.cpp
Filter=N

[CLS:CTcpClientDlg]
Type=0
HeaderFile=TcpClientDlg.h
ImplementationFile=TcpClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTcpClientDlg



[DLG:IDD_TCPCLIENT_DIALOG]
Type=1
Class=CTcpClientDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDT_IP,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDT_PORT,edit,1350631552
Control6=IDC_BTN_CONNECT,button,1342242816
Control7=IDC_EDT_SEND,edit,1353781380
Control8=IDC_BTN_SEND,button,1476460544
Control9=IDC_EDT_RECEIVE,edit,1353783428

