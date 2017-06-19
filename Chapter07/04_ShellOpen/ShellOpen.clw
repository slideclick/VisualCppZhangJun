; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShellOpenDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShellOpen.h"

ClassCount=4
Class1=CShellOpenApp
Class2=CShellOpenDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_SHELLOPEN_DIALOG

[CLS:CShellOpenApp]
Type=0
HeaderFile=ShellOpen.h
ImplementationFile=ShellOpen.cpp
Filter=N

[CLS:CShellOpenDlg]
Type=0
HeaderFile=ShellOpenDlg.h
ImplementationFile=ShellOpenDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SHELLOPEN_DIALOG]
Type=1
Class=CShellOpenDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_BTN_TXT,button,1342242816
Control3=IDC_BTN_URL,button,1342242816
Control4=IDC_BTN_MAIL,button,1342242816
Control5=IDC_BTN_BMP,button,1342242816

