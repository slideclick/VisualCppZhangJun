; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMultiLanguageDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MultiLanguage.h"

ClassCount=2
Class1=CMultiLanguageApp
Class2=CMultiLanguageDlg

ResourceCount=6
Resource2=IDR_MAINFRAME
Resource3=IDD_MULTILANGUAGE_DIALOG (English (U.S.))
Resource4=IDD_MULTILANGUAGE_DIALOG
Resource5=IDR_MENU
Resource6=IDR_MENU (English (U.S.))

[CLS:CMultiLanguageApp]
Type=0
HeaderFile=MultiLanguage.h
ImplementationFile=MultiLanguage.cpp
Filter=N

[CLS:CMultiLanguageDlg]
Type=0
HeaderFile=MultiLanguageDlg.h
ImplementationFile=MultiLanguageDlg.cpp
Filter=D
LastObject=IDR_EN
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MULTILANGUAGE_DIALOG]
Type=1
Class=CMultiLanguageDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDR_CHS
Command2=IDR_EN
CommandCount=2

[DLG:IDD_MULTILANGUAGE_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_MENU (English (U.S.))]
Type=1
Class=?
Command1=IDR_CHS
Command2=IDR_EN
CommandCount=2

