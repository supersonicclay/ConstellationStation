; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowHideDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConStation.h"
LastPage=0

ClassCount=8
Class1=CConStationApp
Class2=CConStationDoc
Class3=CConStationView
Class4=CMainFrame

ResourceCount=8
Resource1="IDR_TOOLBAR1"
Class5=CAboutDlg
Resource2=IDR_CONSTELLATION
Resource3=IDR_CONSTELLATION1
Class6=CConstBar
Resource4=IDR_MAINFRAME
Resource5=IDD_CONST_NAME
Class7=CConstNameDlg
Resource6=IDR_MAINFRAME1
Resource7=IDD_ABOUTBOX
Class8=CShowHideDlg
Resource8=IDD_SHOW_HIDE

[CLS:CConStationApp]
Type=0
HeaderFile=ConStation.h
ImplementationFile=ConStation.cpp
Filter=N
LastObject=CConStationApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ConStation.cpp
ImplementationFile=ConStation.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_STARF_NEWRANDOM
Command2=ID_STARF_NEWACTUAL
Command3=ID_STARF_OPEN
Command4=ID_STARF_SAVE
Command5=ID_STARF_SAVEAS
Command6=ID_CONST_ADD
Command7=ID_CONST_DELETE
Command8=ID_CONST_ALINE
Command9=ID_CONST_APOLY
Command10=ID_CONST_DLINE
Command11=ID_EDIT_UNDO
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_APP_ABOUT
Command15=ID_APP_EXIT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CONST_ADD
Command2=ID_CONST_DLINE
Command3=ID_CONST_DELETE
Command4=ID_CONST_ALINE
Command5=ID_STARF_NEWRANDOM
Command6=ID_STARF_NEWACTUAL
Command7=ID_STARF_OPEN
Command8=ID_CONST_APOLY
Command9=ID_APP_EXIT
Command10=ID_STARF_ROTATE
Command11=ID_STARF_SAVE
Command12=ID_EDIT_UNDO
CommandCount=12

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_STARF_NEWRANDOM
Command2=ID_STARF_OPEN
Command3=ID_STARF_SAVE
Command4=ID_STARF_ROTATE
Command5=ID_SHOW_HIDE
CommandCount=5

[CLS:CConStationDoc]
Type=0
HeaderFile=ConStationDoc.h
ImplementationFile=ConStationDoc.cpp
BaseClass=CDocument
LastObject=CConStationDoc
Filter=N
VirtualFilter=DC

[CLS:CConStationView]
Type=0
HeaderFile=ConStationView.h
ImplementationFile=ConStationView.cpp
BaseClass=CView
LastObject=CConStationView
Filter=C
VirtualFilter=VWC

[TB:IDR_CONSTELLATION]
Type=1
Class=CConStationView
Command1=ID_CONST_LIST
Command2=ID_CONST_ADD
Command3=ID_CONST_DELETE
Command4=ID_CONST_RENAME
Command5=ID_CONST_HIDE
Command6=ID_CONST_ALINE
Command7=ID_CONST_APOLY
Command8=ID_CONST_DLINE
CommandCount=8

[CLS:CConstBar]
Type=0
HeaderFile=ConstBar.h
ImplementationFile=ConstBar.cpp
Filter=W
VirtualFilter=WC
LastObject=ID_CONST_DELETE
BaseClass=CToolBar

[TB:IDR_CONSTELLATION1]
Type=1
Class=?
Command1=ID_CONST_LIST
Command2=ID_CONST_ALINE
Command3=ID_CONST_DLINE
Command4=ID_CONST_ADD
Command5=ID_CONST_DELETE
CommandCount=5

[TB:IDR_MAINFRAME1]
Type=1
Class=?
Command1=ID_STARF_NEWRANDOM
Command2=ID_STARF_OPEN
Command3=ID_STARF_SAVE
Command4=ID_APP_ABOUT
Command5=ID_APP_ABOUT
CommandCount=5

[DLG:IDD_CONST_NAME]
Type=1
Class=CConstNameDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CONST_NAME,edit,1350631552

[CLS:CConstNameDlg]
Type=0
HeaderFile=ConstNameDlg.h
ImplementationFile=ConstNameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CONST_NAME
VirtualFilter=dWC

[DLG:IDD_SHOW_HIDE]
Type=1
Class=CShowHideDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CONST_LIST,listbox,1352728843

[CLS:CShowHideDlg]
Type=0
HeaderFile=ShowHideDlg.h
ImplementationFile=ShowHideDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CONST_LIST
VirtualFilter=dWC

