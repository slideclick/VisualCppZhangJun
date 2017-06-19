; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTcpServerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TcpServer.h"

ClassCount=2
Class1=CTcpServerApp
Class2=CTcpServerDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_TCPSERVER_DIALOG

[CLS:CTcpServerApp]
Type=0
HeaderFile=TcpServer.h
ImplementationFile=TcpServer.cpp
Filter=N

[CLS:CTcpServerDlg]
Type=0
HeaderFile=TcpServerDlg.h
ImplementationFile=TcpServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTcpServerDlg



[DLG:IDD_TCPSERVER_DIALOG]
Type=1
Class=CTcpServerDlg
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDT_IP,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDT_PORT,edit,1350631552
Control6=IDC_BTN_LISTEN,button,1342242816
Control7=IDC_EDT_SEND,edit,1353781380
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CMB_CLIENT,combobox,1344339971
Control10=IDC_BTN_SEND,button,1476460544
Control11=IDC_EDT_RECEIVE,edit,1353783428

