# Microsoft Developer Studio Project File - Name="ConStation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ConStation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ConStation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ConStation.mak" CFG="ConStation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ConStation - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ConStation - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ConStation - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /machine:I386 /out:"../ConStation.exe"

!ELSEIF  "$(CFG)" == "ConStation - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../ConStation[debug].exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ConStation - Win32 Release"
# Name "ConStation - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Main Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BarConst.cpp
# End Source File
# Begin Source File

SOURCE=.\BarStarf.cpp
# End Source File
# Begin Source File

SOURCE=.\ConStation.rc
# End Source File
# Begin Source File

SOURCE=.\CSApp.cpp
# End Source File
# Begin Source File

SOURCE=.\CSFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\CSView.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Dialog Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConstName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsConst.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsStar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSun.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsTerr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsText.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShowHide.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTime.cpp
# End Source File
# End Group
# Begin Group "Data Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataConst.cpp
# End Source File
# Begin Source File

SOURCE=.\DataStar.cpp
# End Source File
# Begin Source File

SOURCE=.\DataStarf.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSun.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTerrain.cpp
# End Source File
# End Group
# Begin Group "Mgr Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MgrBlank.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MgrConst.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrInput.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrStarf.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrTeacher.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrTerrain.cpp
# End Source File
# Begin Source File

SOURCE=.\MgrText.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Main Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BarConst.h
# End Source File
# Begin Source File

SOURCE=.\BarStarf.h
# End Source File
# Begin Source File

SOURCE=.\CSApp.h
# End Source File
# Begin Source File

SOURCE=.\CSFrame.h
# End Source File
# Begin Source File

SOURCE=.\CSView.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Dialog Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\DlgConstName.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsColor.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsConst.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsStar.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSun.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsTerr.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsText.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowHide.h
# End Source File
# Begin Source File

SOURCE=.\DlgTime.h
# End Source File
# End Group
# Begin Group "Data Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataConst.h
# End Source File
# Begin Source File

SOURCE=.\DataStar.h
# End Source File
# Begin Source File

SOURCE=.\DataStarf.h
# End Source File
# Begin Source File

SOURCE=.\DataSun.h
# End Source File
# Begin Source File

SOURCE=.\DataTerrain.h
# End Source File
# End Group
# Begin Group "Mgr Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MgrBlank.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MgrConst.h
# End Source File
# Begin Source File

SOURCE=.\MgrDocument.h
# End Source File
# Begin Source File

SOURCE=.\MgrGraphics.h
# End Source File
# Begin Source File

SOURCE=.\MgrInput.h
# End Source File
# Begin Source File

SOURCE=.\MgrOptions.h
# End Source File
# Begin Source File

SOURCE=.\MgrStarf.h
# End Source File
# Begin Source File

SOURCE=.\MgrTeacher.h
# End Source File
# Begin Source File

SOURCE=.\MgrTerrain.h
# End Source File
# Begin Source File

SOURCE=.\MgrText.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\aline.cur
# End Source File
# Begin Source File

SOURCE=.\res\alinex.cur
# End Source File
# Begin Source File

SOURCE=.\res\apoly.cur
# End Source File
# Begin Source File

SOURCE=.\res\apolyx.cur
# End Source File
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ConStation.ico
# End Source File
# Begin Source File

SOURCE=.\res\ConStation.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Constell.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\delline.cur
# End Source File
# Begin Source File

SOURCE=.\res\dline.cur
# End Source File
# Begin Source File

SOURCE=.\res\dlineg.cur
# End Source File
# Begin Source File

SOURCE=.\res\dlinex.cur
# End Source File
# Begin Source File

SOURCE=.\res\edit.cur
# End Source File
# Begin Source File

SOURCE=.\res\edit1.cur
# End Source File
# Begin Source File

SOURCE=.\res\editg.cur
# End Source File
# Begin Source File

SOURCE=.\res\editline.cur
# End Source File
# Begin Source File

SOURCE=.\res\editx.cur
# End Source File
# Begin Source File

SOURCE=.\res\file.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newline.cur
# End Source File
# Begin Source File

SOURCE=.\res\nline.cur
# End Source File
# Begin Source File

SOURCE=.\res\nlineg.cur
# End Source File
# Begin Source File

SOURCE=.\res\point.cur
# End Source File
# Begin Source File

SOURCE=.\res\point_line.cur
# End Source File
# Begin Source File

SOURCE=.\res\point_nline.cur
# End Source File
# Begin Source File

SOURCE=.\res\pointer1.cur
# End Source File
# Begin Source File

SOURCE=.\res\poly.cur
# End Source File
# Begin Source File

SOURCE=.\res\polyx.cur
# End Source File
# Begin Source File

SOURCE=.\res\rotxy.cur
# End Source File
# Begin Source File

SOURCE=.\res\rotxy1.cur
# End Source File
# Begin Source File

SOURCE=.\res\rotz.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\BUGS.TXT
# End Source File
# Begin Source File

SOURCE=..\data\sample.txt
# End Source File
# Begin Source File

SOURCE=.\TODO.txt
# End Source File
# Begin Source File

SOURCE=.\VERSION.TXT
# End Source File
# End Target
# End Project
