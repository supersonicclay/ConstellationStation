; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConStation.h"
LastPage=0

ClassCount=9
Class1=CConStationApp
Class2=CConStationDoc
Class3=CConStationView
Class4=CMainFrame

ResourceCount=8
Resource1="IDR_TOOLBAR1"
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Resource3=IDR_CONSTELLATION
Class6=CConstBar
Resource4=IDR_MAINFRAME
Resource5=IDD_TERRAIN
Class7=CConstNameDlg
Class8=CShowHideDlg
Resource6=IDD_CONST_NAME
Resource7=IDD_SHOW_HIDE
Class9=CTerrainDlg
Resource8=IDD_LOCATION

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
LastObject=ID_CONST_ALINE
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
Command6=ID_APP_EXIT
Command7=ID_CONST_ADD
Command8=ID_CONST_DELETE
Command9=ID_CONST_ALINE
Command10=ID_CONST_APOLY
Command11=ID_CONST_DLINE
Command12=ID_CONST_HIDE
Command13=ID_OPTIONS_LOCATION
Command14=ID_OPTIONS_TERRAIN
Command15=ID_VIEW_SHOWALL
Command16=ID_VIEW_HIDEALL
Command17=ID_SHOW_HIDE
Command18=ID_APP_ABOUT
CommandCount=18

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
Command4=ID_OPTIONS_LOCATION
Command5=ID_OPTIONS_TERRAIN
Command6=ID_STARF_ROTATE
CommandCount=6

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
Command5=ID_SHOW_HIDE
Command6=ID_CONST_HIDE
Command7=ID_CONST_ALINE
Command8=ID_CONST_APOLY
Command9=ID_CONST_DLINE
CommandCount=9

[CLS:CConstBar]
Type=0
HeaderFile=ConstBar.h
ImplementationFile=ConstBar.cpp
Filter=W
VirtualFilter=WC
LastObject=ID_CONST_DELETE
BaseClass=CToolBar

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
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_CONST_LIST,listbox,1352728843
Control3=IDC_SHOWALL,button,1342242816
Control4=IDC_HIDEALL,button,1342242816
Control5=IDC_INVERT,button,1342242816
Control6=IDC_STATIC,static,1342308352

[CLS:CShowHideDlg]
Type=0
HeaderFile=ShowHideDlg.h
ImplementationFile=ShowHideDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_HIDEALL
VirtualFilter=dWC

[DLG:IDD_TERRAIN]
Type=1
Class=CTerrainDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NEW,button,1342242816
Control4=IDC_ROUGHNESS,msctls_trackbar32,1342242821
Control5=IDC_ROUGHNESS_LBL,static,1342308352
Control6=IDC_COLOR,button,1342242816
Control7=IDC_CUR_COLOR,button,1476427776
Control8=IDC_ROUGHNESS_TXT,edit,1342179456

[DLG:IDD_LOCATION]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CTerrainDlg]
Type=0
HeaderFile=TerrainDlg.h
ImplementationFile=TerrainDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COLOR
VirtualFilter=dWC

