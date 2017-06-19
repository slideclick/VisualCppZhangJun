; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTabCtrlDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TabCtrlDemo.h"

ClassCount=4
Class1=CTabCtrlDemoApp
Class2=CTabCtrlDemoDlg

ResourceCount=4
Resource2=IDD_TABCTRLDEMO_DIALOG
Resource3=IDD_PAGE1
Resource1=IDR_MAINFRAME
Class3=CPage1Dlg
Class4=CPage2Dlg
Resource4=IDD_PAGE2

[CLS:CTabCtrlDemoApp]
Type=0
HeaderFile=TabCtrlDemo.h
ImplementationFile=TabCtrlDemo.cpp
Filter=N

[CLS:CTabCtrlDemoDlg]
Type=0
HeaderFile=TabCtrlDemoDlg.h
ImplementationFile=TabCtrlDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TAB



[DLG:IDD_TABCTRLDEMO_DIALOG]
Type=1
Class=CTabCtrlDemoDlg
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TAB,SysTabControl32,1342177280

[DLG:IDD_PAGE1]
Type=1
Class=CPage1Dlg
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PAGE2]
Type=1
Class=CPage2Dlg
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CPage1Dlg]
Type=0
HeaderFile=Page1Dlg.h
ImplementationFile=Page1Dlg.cpp
BaseClass=CDialog
Filter=D

[CLS:CPage2Dlg]
Type=0
HeaderFile=Page2Dlg.h
ImplementationFile=Page2Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPage2Dlg

