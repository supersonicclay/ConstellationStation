; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgOptionsStar
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConStation.h"
LastPage=0

ClassCount=12
Class1=CConStationApp
Class2=CDlgLocation
Class3=CConStationView
Class4=CConStationFrame
Class5=CDlgAbout
Class6=CDlgOptionsTerr
Class7=CBarStarf
Class8=CDlgConstName
Class9=CDlgShowHide
Class10=CDlgOptionsStar

ResourceCount=13
Resource1="IDR_TOOLBAR1"
Resource2=IDR_STARFIELD
Resource3=IDD_OPTIONS_TERR
Resource4=IDR_MAINFRAME
Resource5=IDD_OPTIONS_GENERAL
Resource6=IDD_ABOUTBOX
Resource7=IDD_SHOW_HIDE
Resource8=IDD_LOCATION
Resource9=IDD_OPTIONS_CONST
Class11=CDlgOptionsConst
Resource10=IDD_CONST_NAME
Resource11=IDR_CONSTELLATION
Resource12=IDD_TIME
Class12=CDlgTime
Resource13=IDD_OPTIONS_STAR

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
LastObject=ID_TERR_TOGGLE
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
Command17=ID_OPTIONS_STAR
Command18=ID_OPTIONS_CONST
Command19=ID_OPTIONS_TERR
Command20=ID_OPTIONS_GENERAL
Command21=ID_APP_ABOUT
CommandCount=21

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

[DLG:IDD_CONST_NAME]
Type=1
Class=CDlgConstName
ControlCount=3
Control1=IDC_CONST_NAME,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

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

[DLG:IDD_LOCATION]
Type=1
Class=CDlgLocation
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242848

[TB:IDR_STARFIELD]
Type=1
Class=CConStationFrame
Command1=ID_STARF_NEWACTUAL
Command2=ID_STARF_NEWRANDOM
Command3=ID_STARF_OPEN
Command4=ID_STARF_SAVE
Command5=ID_OPTIONS_LOCATION
Command6=ID_STARF_DATE
Command7=ID_STARF_TIME
Command8=ID_STARF_SPEED
Command9=ID_STARS_TOGGLE
Command10=ID_CONST_TOGGLE
Command11=ID_TERR_TOGGLE
Command12=ID_OPTIONS_STAR
Command13=ID_OPTIONS_CONST
Command14=ID_OPTIONS_TERR
Command15=ID_TERR_NEW
Command16=ID_STARF_ROTATE
CommandCount=16

[CLS:CDlgLocation]
Type=0
HeaderFile=DlgLocation.h
ImplementationFile=DlgLocation.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgLocation

[DLG:IDD_OPTIONS_STAR]
Type=1
Class=CDlgOptionsStar
ControlCount=16
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STARS_VISIBLE,button,1342242819
Control3=IDC_STARS_LABELED,button,1342242819
Control4=IDC_STARS_TEXTURED,button,1342242819
Control5=IDC_STARS_COLORED,button,1342242819
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STARS_LIMMAG_TXT,edit,1484857472
Control8=IDC_STARS_LIMMAG,msctls_trackbar32,1342242821
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STARS_GAMMA,msctls_trackbar32,1342242840
Control12=IDC_STATIC,static,1342308864
Control13=IDC_STARS_CONTRAST,msctls_trackbar32,1342242840
Control14=IDOK,button,1342242817
Control15=IDCANCEL,button,1342242816
Control16=IDC_STARS_DEFAULTS,button,1342242816

[DLG:IDD_OPTIONS_CONST]
Type=1
Class=CDlgOptionsConst
ControlCount=13
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CONST_VISIBLE,button,1342242819
Control3=IDC_CONST_LABELED,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDC_CONST_NORMCOLOR,button,1342242816
Control6=IDC_CONST_NORMCOLOR_PREV,edit,1484849280
Control7=IDC_CONST_SELCOLOR,button,1342242816
Control8=IDC_CONST_SELCOLOR_PREV,edit,1484849280
Control9=IDC_CONST_ACTIVECOLOR,button,1342242816
Control10=IDC_CONST_ACTIVECOLOR_PREV,edit,1484849280
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_CONST_DEFAULTS,button,1342242816

[DLG:IDD_TIME]
Type=1
Class=CDlgTime
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CDlgTime]
Type=0
HeaderFile=DlgTime.h
ImplementationFile=DlgTime.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgTime

[CLS:CDlgOptionsConst]
Type=0
HeaderFile=DlgOptionsConst.h
ImplementationFile=DlgOptionsConst.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgOptionsConst
VirtualFilter=dWC

[CLS:CDlgOptionsTerr]
Type=0
HeaderFile=DlgOptionsTerr.h
ImplementationFile=DlgOptionsTerr.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgOptionsTerr
VirtualFilter=dWC

[DLG:IDD_OPTIONS_GENERAL]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CDlgOptionsStar]
Type=0
HeaderFile=DlgOptionsStar.h
ImplementationFile=DlgOptionsStar.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgOptionsStar
VirtualFilter=dWC

[DLG:IDD_OPTIONS_TERR]
Type=1
Class=CDlgOptionsTerr
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_TERR_VISIBLE,button,1342242819
Control3=IDC_TERR_TEXTURED,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDC_TERR_ROUGHNESS_TXT,edit,1484783744
Control6=IDC_TERR_ROUGHNESS,msctls_trackbar32,1342242821
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_TERR_SEASONS,listbox,1350631681
Control10=IDC_TERR_COLOR,button,1342242816
Control11=IDC_TERR_COLOR_PREV,edit,1484783744
Control12=IDC_TERR_NEW,button,1342242816
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_TERR_DEFAULTS,button,1342242816

[CLS:CBarStarf]
Type=0
HeaderFile=barstarf.h
ImplementationFile=barstarf.cpp
BaseClass=CToolBar 
LastObject=CBarStarf

[CLS:CDlgConstName]
Type=0
HeaderFile=dlgconstname.h
ImplementationFile=dlgconstname.cpp
BaseClass=CDialog
LastObject=CDlgConstName

