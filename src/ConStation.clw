; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConStationUI
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConStation.h"
LastPage=0

ClassCount=12
Class1=CConStationApp
Class2=CConStationDoc
Class3=CConStationView
Class4=CConStationFrame
Class5=CDlgAbout
Class6=CConstBar
Class7=CStarfBar
Class8=CDlgConstName
Class9=CDlgShowHide
Class10=CDlgTerrain
Class11=CDlgLocation
Class12=CConStationUI

ResourceCount=9
Resource1="IDR_TOOLBAR1"
Resource2=IDR_CONSTELLATION
Resource3=IDR_STARFIELD
Resource4=IDD_TERRAIN
Resource5=IDD_CONST_NAME
Resource6=IDR_MAINFRAME
Resource7=IDD_ABOUTBOX
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
LastObject=CConStationFrame
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
Command11=ID_CONST_APOLY
Command12=ID_CONST_DLINE
Command13=ID_CONST_SHOWHIDE
Command14=ID_CONST_SHOWALL
Command15=ID_CONST_HIDEALL
Command16=ID_OPTIONS_LOCATION
Command17=ID_OPTIONS_TERRAIN
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CConStationFrame
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
Command8=ID_CONST_APOLY
Command9=ID_CONST_DLINE
CommandCount=9

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
Class=CDlgConstName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CONST_NAME,edit,1350631552

[CLS:CDlgConstName]
Type=0
HeaderFile=DlgConstName.h
ImplementationFile=DlgConstName.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CONST_NAME
VirtualFilter=dWC

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
LastObject=IDC_HIDEALL
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
LastObject=IDC_COLOR
VirtualFilter=dWC

[TB:IDR_STARFIELD]
Type=1
Class=CConStationFrame
Command1=ID_STARF_NEWRANDOM
Command2=ID_STARF_OPEN
Command3=ID_STARF_SAVE
Command4=ID_OPTIONS_LOCATION
Command5=ID_OPTIONS_TERRAIN
Command6=ID_TERR_NEW
Command7=ID_STARF_ROTATE
Command8=ID_STARF_DATE
Command9=ID_STARF_DATE
Command10=ID_STARF_TIME
Command11=ID_STARF_TIME
Command12=ID_STARF_SPEED
CommandCount=12

[CLS:CDlgLocation]
Type=0
HeaderFile=DlgLocation.h
ImplementationFile=DlgLocation.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DATETIMEPICKER2

[CLS:CConStationUI]
Type=0
HeaderFile=ConStationUI.h
ImplementationFile=ConStationUI.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CConStationUI

