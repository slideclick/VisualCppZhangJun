; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPopMenuDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PopMenuDemo.h"

ClassCount=2
Class1=CPopMenuDemoApp
Class2=CPopMenuDemoDlg

ResourceCount=3
Resource2=IDD_POPMENUDEMO_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDR_MENU_POP

[CLS:CPopMenuDemoApp]
Type=0
HeaderFile=PopMenuDemo.h
ImplementationFile=PopMenuDemo.cpp
Filter=N

[CLS:CPopMenuDemoDlg]
Type=0
HeaderFile=PopMenuDemoDlg.h
ImplementationFile=PopMenuDemoDlg.cpp
Filter=D
LastObject=CPopMenuDemoDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_POPMENUDEMO_DIALOG]
Type=1
Class=CPopMenuDemoDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_MENU_POP]
Type=1
Class=?
Command1=ID_MI_CLICKCOUNT
Command2=ID_MI_RESET
Command3=ID_MI_CHECK
CommandCount=3

