; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConStationApp
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConStation.h"
LastPage=0

ClassCount=10
Class1=CConStationApp
Class2=CDlgLocation
Class3=CConStationView
Class4=CConStationFrame
Class5=CDlgAbout
Class6=CConstBar
Class7=CStarfBar
Class8=CConstNameDlg
Class9=CDlgShowHide
Class10=CDlgTerrain

ResourceCount=9
Resource1="IDR_TOOLBAR1"
Resource2=IDR_MAINFRAME
Resource3=IDR_STARFIELD
Resource4=IDR_CONSTELLATION
Resource5=IDD_TERRAIN
Resource6=IDD_ABOUTBOX
Resource7=IDD_CONST_NAME
Resource8=IDD_SHOW_HIDE
Resource9=IDD_LOCATION

[CLS:CConStationApp]
Type=0
HeaderFile=ConStation.h
ImplementationFile=ConStation.cpp
Filter=N
LastObject=CConStationApp
BaseClass=CWinApp 
VirtualFilter=AC

[CLS:CConStationFrame]
Type=0
HeaderFile=ConStationFrame.h
ImplementationFile=ConStationFrame.cpp
Filter=T
LastObject=ID_STARF_SAVE
BaseClass=CFrameWnd
VirtualFilter=fWC

[CLS:CDlgAbout]
Type=0
HeaderFile=ConStation.cpp
ImplementationFile=ConStation.cpp
Filter=D
LastObject=CDlgAbout

[DLG:IDD_ABOUTBOX]
Type=1
Class=CDlgAbout
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CConStationFrame
Command1=ID_STARF_NEWRANDOM
Command2=ID_STARF_NEWACTUAL
Command3=ID_STARF_OPEN
Command4=ID_STARF_SAVE
Command5=ID_STARF_SAVEAS
Command6=ID_APP_EXIT
Command7=ID_CONST_ADD
Command8=ID_CONST_DELETE
Command9=ID_CONST_HIDE
Command10=ID_CONST_ALINE
Command11=ID_CONST_DLINE
Command12=ID_CONST_SHOWHIDE
Command13=ID_CONST_SHOWALL
Command14=ID_CONST_HIDEALL
Command15=ID_OPTIONS_TIME
Command16=ID_OPTIONS_LOCATION
Command17=ID_OPTIONS_TERRAIN
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CConStationFrame
Command1=ID_CONST_ALINE
Command2=ID_CONST_ADD
Command3=ID_CONST_DLINE
Command4=ID_CONST_DELETE
Command5=ID_STARF_NEWRANDOM
Command6=ID_STARF_NEWACTUAL
Command7=ID_STARF_OPEN
Command8=ID_APP_EXIT
Command9=ID_STARF_ROTATE
Command10=ID_STARF_SAVE
Command11=ID_EDIT_UNDO
CommandCount=11

[CLS:CConStationView]
Type=0
HeaderFile=ConStationView.h
ImplementationFile=ConStationView.cpp
BaseClass=CWnd
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
Command5=ID_CONST_SHOWHIDE
Command6=ID_CONST_HIDE
Command7=ID_CONST_ALINE
Command8=ID_CONST_DLINE
CommandCount=8

[CLS:CConstBar]
Type=0
HeaderFile=ConstBar.h
ImplementationFile=ConstBar.cpp
Filter=W
VirtualFilter=WC
LastObject=CConstBar
BaseClass=CToolBar

[CLS:CStarfBar]
Type=0
HeaderFile=StarfBar.h
ImplementationFile=StarfBar.cpp
Filter=W
VirtualFilter=WC
LastObject=CStarfBar
BaseClass=CToolBar 

[DLG:IDD_CONST_NAME]
Type=1
Class=CConstNameDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CONST_NAME,edit,1350631552

[DLG:IDD_SHOW_HIDE]
Type=1
Class=CDlgShowHide
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_CONST_LIST,listbox,1352728843
Control3=IDC_SHOWALL,button,1342242816
Control4=IDC_HIDEALL,button,1342242816
Control5=IDC_INVERT,button,1342242816
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgShowHide]
Type=0
HeaderFile=DlgShowHide.h
ImplementationFile=DlgShowHide.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgShowHide
VirtualFilter=dWC

[DLG:IDD_TERRAIN]
Type=1
Class=CDlgTerrain
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
Class=CDlgLocation
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242848

[CLS:CDlgTerrain]
Type=0
HeaderFile=DlgTerrain.h
ImplementationFile=DlgTerrain.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgTerrain
VirtualFilter=dWC

[TB:IDR_STARFIELD]
Type=1
Class=CConStationFrame
Command1=ID_STARF_NEWACTUAL
Command2=ID_STARF_NEWRANDOM
Command3=ID_STARF_OPEN
Command4=ID_STARF_SAVE
Command5=ID_OPTIONS_LOCATION
Command6=ID_OPTIONS_TERRAIN
Command7=ID_TERR_NEW
Command8=ID_STARF_ROTATE
Command9=ID_STARF_DATE
Command10=ID_STARF_DATE
Command11=ID_STARF_TIME
Command12=ID_STARF_TIME
Command13=ID_STARF_SPEED
Command14=ID_BUTTON32857
Command15=ID_BUTTON32858
Command16=ID_BUTTON32859
Command17=ID_BUTTON32860
Command18=ID_BUTTON32861
CommandCount=18

[CLS:CDlgLocation]
Type=0
HeaderFile=DlgLocation.h
ImplementationFile=DlgLocation.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgLocation

[CLS:CConstNameDlg]
Type=0
HeaderFile=constnamedlg.h
ImplementationFile=constnamedlg.cpp
BaseClass=CDialog
LastObject=CConstNameDlg

