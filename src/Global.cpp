//===========================================================================
// Global.cpp
//
// Various global variables, functions, and types
//===========================================================================


#include "stdafx.h"
#include "Global.h"


/////////////////////////////////////////////////////////////////////////////
// MAIN GLOBALS

// Data
CDataStarf starfield;
CDataTerrain terrain;

// Managers
CMgrInput		inputMgr;
CMgrGraphics	graphicsMgr;
CMgrOptions		optionsMgr;
CMgrDocument	documentMgr;
CMgrStarf		starfMgr;
CMgrConst		constMgr;
CMgrTerrain		terrainMgr;
CMgrTeacher		teacherMgr;

// State
state_e state = state_Viewing;


/////////////////////////////////////////////////////////////////////////////
// MFC CLASS ACCESS
CCSApp* GetApp()
{
	return (CCSApp*)AfxGetApp();
}

CCSFrame* GetFrame()
{
	return (CCSFrame*)AfxGetMainWnd();
}

CCSView* GetView()
{
	return GetFrame()->GetView();
}


/////////////////////////////////////////////////////////////////////////////
/// DEBUG VARS

BOOL terrFog = TRUE;
BOOL terrExternal = FALSE;


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
// DEFAULTS

const BOOL		DEF_STARS_VISIBLE		= TRUE;
const BOOL		DEF_STARS_DAYLIGHT		= FALSE;
const BOOL		DEF_STARS_LABELED		= FALSE;
const BOOL		DEF_STARS_TEXTURED		= TRUE;
const BOOL		DEF_STARS_COLORED		= TRUE;
const int		DEF_STARS_LIMMAGX10		= 70;
const int		DEF_STARS_SIZE			= 40;
const int		DEF_STARS_SCONTRAST		= 50;
const int		DEF_STARS_CCONTRAST		= 75;
const float		DEF_STARS_BRIGHT_RADIUS	= 0.013f;
const float		DEF_STARS_BRIGHT_COLOR	= 1.0f;
const float		DEF_STARS_RADIUS_DIFF	= 0.011f;
const float		DEF_STARS_COLOR_DIFF	= 0.8f;

const BOOL		DEF_CONST_VISIBLE		= TRUE;
const BOOL		DEF_CONST_DAYLIGHT		= TRUE;
const BOOL		DEF_CONST_LABELED		= TRUE;
const color_s	DEF_CONST_NORMCOLOR		= {0.0f, 0.5f, 0.5f};
const color_s	DEF_CONST_SELCOLOR		= {0.0f, 1.0f, 1.0f};
const color_s	DEF_CONST_ACTIVECOLOR	= {1.0f, 1.0f, 0.0f};
const color_s	DEF_CONST_STARCOLOR		= {0.0f, 0.0f, 1.0f};
const BOOL		DEF_CONST_STARSCOLORED	= TRUE;
const int		DEF_CONST_LINEWIDTH		= 3;

const float		DEF_SUN_RADIUS			= 0.08f;
const color_s	DEF_SUN_COLOR			= {1.0f, 1.0f, 0.5f};
const BOOL		DEF_SUN_VISIBLE			= TRUE;
const BOOL		DEF_SUN_SHINE			= TRUE;

const color_s	DEF_SKY_COLOR			= {0.6f, 0.7f, 1.0f};

const BOOL		DEF_TERR_VISIBLE		= TRUE;
const BOOL		DEF_TERR_TEXTURED		= TRUE;
const int		DEF_TERR_ROUGHNESSX100	= 20;
const int		DEF_TERR_SCALE			= 1;
const int		DEF_TERR_TEX_ITERS		= 8;
const int		DEF_TERR_HEIGHT_ITERS	= 4;
const season_e	DEF_TERR_SEASON			= season_Spring;
const color_s	DEF_TERR_WINCOLOR		= {0.7f, 0.7f, 0.7f};
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
	Redraw();
}

void Redraw()
{
	GetView()->InvalidateRect( NULL, FALSE );
}


// Special CArchive functions
CArchive& operator>> ( CArchive& ar, season_e& s )
{
	int i;
	CArchive* ret = &(ar >> i);

	s = (season_e)i;
	return *ret;
}

CArchive& operator>> ( CArchive& ar, color_s& c )
{
	return ar >> c.r >> c.g >> c.b;
}

CArchive& operator<< ( CArchive& ar, season_e s )
{
	return ar << (int)s;
}

CArchive& operator<< ( CArchive& ar, color_s c )
{
	return ar << c.r << c.g << c.b;
}


// Multiply color by a factor
color_s operator* ( const color_s c, const float f )
{
	color_s ret = c;
	ret.r *= f;
	ret.g *= f;
	ret.b *= f;
	return ret;
}

// Star comparison (for sorting by magnitude)
BOOL operator< ( CDataStar& s1, CDataStar& s2 )
{
	return s1.GetMag() < s2.GetMag();
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

void CSDebug( char* msg, char* title )
{
	CSError( GetFrame()->GetSafeHwnd(), msg, title );
}


// Message boxes (handle specified)
void CSInfo( HWND parent, char* msg, char* title )
{
	MessageBox( parent, msg, title, MB_ICONINFORMATION | MB_OK );
}

int CSQuestion( HWND parent, char* msg, char* title )
{
	return MessageBox( parent, msg, title, MB_ICONQUESTION | MB_YESNO );
}

int  CSYesNoCancel( HWND parent, char* msg, char* title )
{
	return MessageBox( parent, msg, title, MB_ICONQUESTION | MB_YESNOCANCEL );
}

void CSWarn( HWND parent, char* msg, char* title )
{
	MessageBox( parent, msg, title, MB_ICONWARNING | MB_OK );
}

void CSError( HWND parent, char* msg, char* title )
{
	MessageBox( parent, msg, title, MB_ICONERROR | MB_OK );
}


