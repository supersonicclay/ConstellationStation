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
CMgrInput		inputMgr;
CMgrGraphics	graphicsMgr;
CMgrOptions		optionsMgr;
CMgrDocument	documentMgr;
CMgrStarfield	starfieldMgr;
CMgrConst		constMgr;
CMgrTerrain		terrainMgr;
CMgrTeacher		teacherMgr;

state_e state = state_Viewing;

// Data
CDataStarfield starfield;
CDataTerrain terrain;


/////////////////////////////////////////////////////////////////////////////
// MFC CLASS ACCESS
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
const color_s	COLOR_WHITE			= {1.0f, 1.0f, 1.0f},
				COLOR_BLACK			= {0.0f, 0.0f, 0.0f},
				COLOR_RED			= {1.0f, 0.0f, 0.0f},
				COLOR_GREEN			= {0.0f, 1.0f, 0.0f},
				COLOR_DARKGREEN		= {0.1f, 0.2f, 0.1f},
				COLOR_BLUE			= {0.0f, 0.0f, 1.0f},
				COLOR_DARKBLUE		= {0.0f, 0.0f, 0.5f},
				COLOR_YELLOW		= {1.0f, 1.0f, 0.0f},
				COLOR_TEAL			= {0.0f, 1.0f, 1.0f},
				COLOR_DARKTEAL		= {0.0f, 0.5f, 0.5f};


/////////////////////////////////////////////////////////////////////////////
// ABSOLUTE DEFAULTS

const BOOL		DEF_STARS_VISIBLE		= TRUE;
const BOOL		DEF_STARS_LABELED		= FALSE;
const BOOL		DEF_STARS_TEXTURED		= TRUE;
const BOOL		DEF_STARS_COLORED		= TRUE;
const float		DEF_STARS_LIMMAG		= 5.0f;
const int		DEF_STARS_GAMMA			= 50;
const int		DEF_STARS_CONTRAST		= 50;
const BOOL		DEF_CONST_VISIBLE		= TRUE;
const BOOL		DEF_CONST_LABELED		= TRUE;
const color_s	DEF_CONST_NORMCOLOR		= {0.0f, 0.5f, 0.5f};
const color_s	DEF_CONST_SELCOLOR		= {0.0f, 1.0f, 1.0f};
const color_s	DEF_CONST_ACTIVECOLOR	= {1.0f, 1.0f, 0.0f};
const color_s	DEF_CONST_STARCOLOR		= {0.0f, 0.0f, 1.0f};
const BOOL		DEF_CONST_STARSCOLORED	= TRUE;
const BOOL		DEF_SUN_VISIBLE			= TRUE;
const BOOL		DEF_SUN_SHINE			= TRUE;
const BOOL		DEF_TERR_VISIBLE		= TRUE;
const float		DEF_TERR_ROUGHNESS		= 0.1f;
const BOOL		DEF_TERR_TEXTURED		= FALSE;
const season_e	DEF_TERR_SEASON			= season_Summer;
const color_s	DEF_TERR_WINCOLOR		= {0.4f, 0.4f, 0.4f};
const color_s	DEF_TERR_SPRCOLOR		= {0.15f, 0.25f, 0.1f};
const color_s	DEF_TERR_SUMCOLOR		= {0.1f, 0.3f, 0.1f};
const color_s	DEF_TERR_FALCOLOR		= {0.25f, 0.25f, 0.15f};
const color_s	DEF_COMPASS_CROSSCOLOR	= {0.3f, 0.3f, 0.8f};
const color_s	DEF_COMPASS_NEEDLECOLOR	= {0.7f, 1.0f, 0.7f};


/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

void SetState( state_e s )
{
	inputMgr.ClearSelection();

	state = s;
}

void Redraw()
{
	GetView()->InvalidateRect( NULL, FALSE );
}

// Message boxes (handle not specified)
void CSInfo( char* msg, char* title )
{
	CSInfo( GetFrame()->GetSafeHwnd(), msg, title );
}

int CSQuestion( char* msg, char* title )
{
	return CSQuestion( GetFrame()->GetSafeHwnd(), msg, title );
}

int CSYesNoCancel( char* msg, char* title )
{
	return CSYesNoCancel( GetFrame()->GetSafeHwnd(), msg, title );
}

void CSWarn( char* msg, char* title )
{
	CSWarn( GetFrame()->GetSafeHwnd(), msg, title );
}

void CSError( char* msg, char* title )
{
	CSError( GetFrame()->GetSafeHwnd(), msg, title );
}

// Message boxes (handle specified)
void CSInfo( HWND parent, char* msg, char* title )
{
	MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONINFORMATION | MB_OK );
}

int CSQuestion( HWND parent, char* msg, char* title )
{
	return MessageBox( parent, msg, title, MB_ICONQUESTION | MB_YESNO );
}

int  CSYesNoCancel( HWND parent, char* msg, char* title )
{
	return MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONQUESTION | MB_YESNOCANCEL );
}

void CSWarn( HWND parent, char* msg, char* title )
{
	MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONWARNING | MB_OK );
}

void CSError( HWND parent, char* msg, char* title )
{
	MessageBox( GetFrame()->GetSafeHwnd(), msg, title, MB_ICONERROR | MB_OK );
	PostQuitMessage(0);
}


