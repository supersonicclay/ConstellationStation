//===========================================================================
// Global.cpp
//
// Various global variables, functions, and types
//===========================================================================


#include "stdafx.h"
#include "Global.h"


/////////////////////////////////////////////////////////////////////////////
// MAIN GLOBALS

// Managers
CMgrInput inputMgr;
CMgrGraphics graphicsMgr;
CMgrConst constMgr;
CMgrStarf starfMgr;
CMgrTerrain terrainMgr;
CMgrTeacher teacherMgr;

state_e state = state_Viewing;

// Data
CStarfield starfield;
CTerrain terrain;


/////////////////////////////////////////////////////////////////////////////
// MFC classes access
CConStationApp* GetApp()
{
	return (CConStationApp*)AfxGetApp();
}

CConStationFrame* GetFrame()
{
	return (CConStationFrame*)AfxGetMainWnd();
}

CConStationView* GetView()
{
	return GetFrame()->GetView();
}


/////////////////////////////////////////////////////////////////////////////
// COLOR
const color_s	COLOR_WHITE =		{1.0f, 1.0f, 1.0f},
				COLOR_BLACK =		{0.0f, 0.0f, 0.0f},
				COLOR_CROSS =		{0.3f, 0.3f, 0.8f},
				COLOR_ACTIVESTAR =	{1.0f, 0.0f, 0.0f},
				COLOR_CONSTLINE =	{0.0f, 0.5f, 0.5f},
				COLOR_SUN =			{1.0f, 1.0f, 1.0f},
				COLOR_SKY =			{0.0f, 0.0f, 0.6f},
				COLOR_NORTHSTAR =	{0.7f, 1.0f, 0.7f};


/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
void SetState( state_e s )
{
	// Clear the selection
	inputMgr.ClearSelection();

	state = s;
}

void Redraw()
{
	GetView()->InvalidateRect( NULL, FALSE );
}

void CSInfo( char* msg, char* title )
{
	MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONINFORMATION | MB_OK );
}

int CSQuestion( char* msg, char* title )
{
	return MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONQUESTION | MB_YESNO );
}

int CSYesNoCancel( char* msg, char* title )
{
	return MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONQUESTION | MB_YESNOCANCEL );
}

void CSWarn( char* msg, char* title )
{
	MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONWARNING | MB_OK );
}

void CSError( char* msg, char* title )
{
	MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONERROR | MB_OK );
	PostQuitMessage(0);
}