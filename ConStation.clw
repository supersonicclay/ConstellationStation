; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConStationView
LastTemplate=CToolBarCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConStation.h"
LastPage=0

ClassCount=5
Class1=CConStationApp
Class2=CConStationDoc
Class3=CConStationView
Class4=CMainFrame

ResourceCount=4
Resource1="IDR_TOOLBAR1"
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Resource3=IDR_CONSTELLATION
Resource4=IDD_ABOUTBOX

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
Command1=ID_APP_EXIT
Command2=ID_STARFIELD_NEWRANDOM
Command3=ID_STARFIELD_NEWACTUAL
Command4=ID_STARFIELD_OPEN
Command5=ID_STARFIELD_SAVE
Command6=ID_STARFIELD_SAVEAS
Command7=ID_EDIT
Command8=ID_CONSTELLATION_CREATE
Command9=ID_CONSTELLATION_DELETE
Command10=ID_CONSTELLATION_LOAD
Command11=ID_CONSTELLATION_STORE
Command12=ID_CONSTELLATION_STOREAS
Command13=ID_EDIT_UNDO
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CONSTELLATION_CREATE
Command2=ID_CONSTELLATION_DELETE
Command3=ID_NLINE
Command4=ID_CONSTELLATION_LOAD
Command5=ID_STARFIELD_NEWRANDOM
Command6=ID_STARFIELD_NEWACTUAL
Command7=ID_STARFIELD_OPEN
Command8=ID_APP_EXIT
Command9=ID_CONSTELLATION_STORE
Command10=ID_STARFIELD_SAVE
Command11=ID_EDIT
Command12=ID_EDIT_UNDO
CommandCount=12

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_STARFIELD_NEWRANDOM
Command2=ID_STARFIELD_OPEN
Command3=ID_STARFIELD_SAVE
Command4=ID_APP_ABOUT
CommandCount=4

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
Command1=ID_EDIT
Command2=ID_NLINE
Command3=ID_DLINE
CommandCount=3

