; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CToolbarDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ToolbarDemo.h"

ClassCount=2
Class1=CToolbarDemoApp
Class2=CToolbarDemoDlg

ResourceCount=5
Resource2=IDR_MAINFRAME
Resource3=IDR_TOOLBAR
Resource4=IDR_MENU
Resource5=IDD_TOOLBARDEMO_DIALOG

[CLS:CToolbarDemoApp]
Type=0
HeaderFile=ToolbarDemo.h
ImplementationFile=ToolbarDemo.cpp
Filter=N

[CLS:CToolbarDemoDlg]
Type=0
HeaderFile=ToolbarDemoDlg.h
ImplementationFile=ToolbarDemoDlg.cpp
Filter=W
LastObject=CToolbarDemoDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_TOOLBARDEMO_DIALOG]
Type=1
Class=CToolbarDemoDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_MI_TEST
Command2=ID_MI_DISABLE
CommandCount=2

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=ID_MI_TEST
Command2=ID_MI_DISABLE
CommandCount=2

