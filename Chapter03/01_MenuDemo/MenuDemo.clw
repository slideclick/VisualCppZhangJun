; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMenuDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MenuDemo.h"

ClassCount=2
Class1=CMenuDemoApp
Class2=CMenuDemoDlg

ResourceCount=5
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU1
Resource4=IDD_MENUDEMO_DIALOG
Resource5=IDR_MENU2

[CLS:CMenuDemoApp]
Type=0
HeaderFile=MenuDemo.h
ImplementationFile=MenuDemo.cpp
Filter=N

[CLS:CMenuDemoDlg]
Type=0
HeaderFile=MenuDemoDlg.h
ImplementationFile=MenuDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_MI_ENABLE



[DLG:IDD_MENUDEMO_DIALOG]
Type=1
Class=CMenuDemoDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HIDE_MENU,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MI_DISABLE
Command2=ID_MI_ENABLE
CommandCount=2

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=ID_MI_CHECK
CommandCount=1

