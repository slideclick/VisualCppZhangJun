; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CODBC_DemoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ODBC_Demo.h"
LastPage=0

ClassCount=6
Class1=CODBC_DemoApp
Class2=CODBC_DemoDoc
Class3=CODBC_DemoView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CODBC_DemoSet
Resource7=IDD_ODBC_DEMO_FORM

[CLS:CODBC_DemoApp]
Type=0
HeaderFile=ODBC_Demo.h
ImplementationFile=ODBC_Demo.cpp
Filter=N

[CLS:CODBC_DemoDoc]
Type=0
HeaderFile=ODBC_DemoDoc.h
ImplementationFile=ODBC_DemoDoc.cpp
Filter=N

[CLS:CODBC_DemoView]
Type=0
HeaderFile=ODBC_DemoView.h
ImplementationFile=ODBC_DemoView.cpp
Filter=D
BaseClass=CRecordView
VirtualFilter=RVWC
LastObject=CODBC_DemoView


[CLS:CODBC_DemoSet]
Type=0
HeaderFile=ODBC_DemoSet.h
ImplementationFile=ODBC_DemoSet.cpp
Filter=N

[DB:CODBC_DemoSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[StudentID], 4, 4
Column2=[StudentName], 12, 64


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=ODBC_Demo.cpp
ImplementationFile=ODBC_Demo.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_RECORD_FIRST
Command15=ID_RECORD_PREV
Command16=ID_RECORD_NEXT
Command17=ID_RECORD_LAST
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ODBC_DEMO_FORM]
Type=1
Class=CODBC_DemoView
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDT_ID,edit,1350631552
Control4=IDC_EDT_NAME,edit,1350631552
Control5=IDC_BTN_ADD,button,1342242816
Control6=IDC_BTN_EDIT,button,1342242816
Control7=IDC_BTN_DELETE,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_RECORD_FIRST
Command9=ID_RECORD_PREV
Command10=ID_RECORD_NEXT
Command11=ID_RECORD_LAST
Command12=ID_APP_ABOUT
CommandCount=12

