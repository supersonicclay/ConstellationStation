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
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /machine:I386

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
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ConStation - Win32 Release"
# Name "ConStation - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ConStation.cpp
# End Source File
# Begin Source File

SOURCE=.\ConStation.rc
# End Source File
# Begin Source File

SOURCE=.\ConStationDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ConStationView.cpp
# End Source File
# Begin Source File

SOURCE=.\Costellation.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Star.cpp
# End Source File
# Begin Source File

SOURCE=.\Starfield.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConStation.h
# End Source File
# Begin Source File

SOURCE=.\ConStationDoc.h
# End Source File
# Begin Source File

SOURCE=.\ConStationView.h
# End Source File
# Begin Source File

SOURCE=.\Constellation.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Star.h
# End Source File
# Begin Source File

SOURCE=.\Starfield.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
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

SOURCE=.\res\edit.cur
# End Source File
# Begin Source File

SOURCE=.\res\edit1.cur
# End Source File
# Begin Source File

SOURCE=.\res\editline.cur
# End Source File
# Begin Source File

SOURCE=.\res\file.ico
# End Source File
# Begin Source File

SOURCE=.\res\newline.cur
# End Source File
# Begin Source File

SOURCE=.\res\nline.cur
# End Source File
# Begin Source File

SOURCE=.\res\nline1.cur
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

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
