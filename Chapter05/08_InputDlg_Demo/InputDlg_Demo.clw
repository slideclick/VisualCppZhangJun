; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInputDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "InputDlg_Demo.h"

ClassCount=4
Class1=CInputDlg_DemoApp
Class2=CInputDlg_DemoDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=InputDlg
Class4=CInputDlg
Resource2=IDD_INPUTDLG_DEMO_DIALOG

[CLS:CInputDlg_DemoApp]
Type=0
HeaderFile=InputDlg_Demo.h
ImplementationFile=InputDlg_Demo.cpp
Filter=N

[CLS:CInputDlg_DemoDlg]
Type=0
HeaderFile=InputDlg_DemoDlg.h
ImplementationFile=InputDlg_DemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_INPUTDLG_DEMO_DIALOG]
Type=1
Class=CInputDlg_DemoDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_INPUT,static,1342308352

[CLS:InputDlg]
Type=0
HeaderFile=InputDlg.h
ImplementationFile=InputDlg.cpp
BaseClass=CDialog
Filter=D

[CLS:CInputDlg]
Type=0
HeaderFile=inputdlg.h
ImplementationFile=inputdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInputDlg

