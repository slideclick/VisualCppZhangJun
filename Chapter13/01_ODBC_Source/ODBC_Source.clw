; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CODBC_SourceDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ODBC_Source.h"

ClassCount=4
Class1=CODBC_SourceApp
Class2=CODBC_SourceDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_ODBC_SOURCE_DIALOG

[CLS:CODBC_SourceApp]
Type=0
HeaderFile=ODBC_Source.h
ImplementationFile=ODBC_Source.cpp
Filter=N

[CLS:CODBC_SourceDlg]
Type=0
HeaderFile=ODBC_SourceDlg.h
ImplementationFile=ODBC_SourceDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_ODBC_SOURCE_DIALOG]
Type=1
Class=CODBC_SourceDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDT_FILE,edit,1350631552
Control6=IDC_BTN_BROWSE,button,1342242816

