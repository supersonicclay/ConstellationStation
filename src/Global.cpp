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
CMgrText		textMgr;
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

const BOOL		DEF_STARS_VISIBLE			= TRUE;
const BOOL		DEF_STARS_DAYLIGHT			= FALSE;
const BOOL		DEF_STARS_LABELED			= FALSE;
const BOOL		DEF_STARS_TEXTURED			= TRUE;
const BOOL		DEF_STARS_COLORED			= FALSE;
const int		DEF_STARS_LIMMAGX10			= 70;
const int		DEF_STARS_SIZE				= 25;
const int		DEF_STARS_SCONTRAST			= 50;
const int		DEF_STARS_CCONTRAST			= 75;
const float		DEF_STARS_BRIGHT_RADIUS		= 0.013f;
const float		DEF_STARS_BRIGHT_COLOR		= 1.0f;
const float		DEF_STARS_RADIUS_DIFF		= 0.011f;
const float		DEF_STARS_COLOR_DIFF		= 0.8f;
const color_s	DEF_STARS_SPECTRAL_O_COLOR	= { 1.0f, 0.85f, 1.0f };
const color_s	DEF_STARS_SPECTRAL_B_COLOR	= { 0.5f, 1.0f, 1.0f };
const color_s	DEF_STARS_SPECTRAL_A_COLOR	= { 1.0f, 1.0f, 1.0f };
const color_s	DEF_STARS_SPECTRAL_F_COLOR	= { 1.0f, 1.0f, 0.5f };
const color_s	DEF_STARS_SPECTRAL_G_COLOR	= { 1.0f, 0.95f, 1.0f };
const color_s	DEF_STARS_SPECTRAL_K_COLOR	= { 1.0f, 0.75f, 1.0f };
const color_s	DEF_STARS_SPECTRAL_M_COLOR	= { 1.0f, 0.75f, 0.5f };


const BOOL		DEF_CONST_VISIBLE		= TRUE;
const BOOL		DEF_CONST_DAYLIGHT		= TRUE;
const BOOL		DEF_CONST_LABELED		= TRUE;
const BOOL		DEF_CONST_LINESVISIBLE	= TRUE;
const color_s	DEF_CONST_NORMCOLOR		= {0.5f, 0.25f, 0.0f};
const color_s	DEF_CONST_SELCOLOR		= {0.0f, 0.75f, 0.25f};
const color_s	DEF_CONST_ACTIVECOLOR	= {1.0f, 1.0f, 0.0f};
const color_s	DEF_CONST_STARCOLOR		= {1.0f, 0.5f, 1.0f};
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
const int		DEF_TERR_TEX_ITERS		= 7;
const int		DEF_TERR_HEIGHT_ITERS	= 4;
const season_e	DEF_TERR_SEASON			= season_Spring;
const color_s	DEF_TERR_WINCOLOR		= {0.7f, 0.7f, 0.7f};
const color_s	DEF_TERR_SPRCOLOR		= {0.15f, 0.25f, 0.1f};
const color_s	DEF_TERR_SUMCOLOR		= {0.1f, 0.3f, 0.1f};
const color_s	DEF_TERR_FALCOLOR		= {0.25f, 0.25f, 0.15f};

const color_s	DEF_TEXT_CONSTCOLOR		= {0.7f, 0.7f, 0.7f};
const color_s	DEF_TEXT_CONSTSELCOLOR	= {1.0f, 1.0f, 0.5f};
const color_s	DEF_TEXT_STARCOLOR		= {1.0f, 0.0f, 0.0f};
const color_s	DEF_TEXT_DIRCOLOR		= {1.0f, 0.5f, 0.0f};

const color_s	DEF_COMPASS_CROSSCOLOR	= {0.3f, 0.3f, 0.8f};
const color_s	DEF_COMPASS_NEEDLECOLOR	= {0.7f, 1.0f, 0.7f};


const LOGFONT	DEF_TEXT_CONSTFONT = 
{
	-24,							// Height Of Font
	0,								// Width Of Font
	0,								// Angle Of Escapement
	0,								// Orientation Angle
	FW_BOLD,						// Font Weight
	TRUE,							// Italic
	FALSE,							// Underline
	FALSE,							// Strikeout
	ANSI_CHARSET,					// Character Set Identifier
	OUT_TT_PRECIS,					// Output Precision
	CLIP_DEFAULT_PRECIS,			// Clipping Precision
	ANTIALIASED_QUALITY,			// Output Quality
	FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
	"Courier New"					// Font Name
};

const LOGFONT	DEF_TEXT_STARFONT = 
{
	-16,							// Height Of Font
	0,								// Width Of Font
	0,								// Angle Of Escapement
	0,								// Orientation Angle
	FW_NORMAL,						// Font Weight
	TRUE,							// Italic
	FALSE,							// Underline
	FALSE,							// Strikeout
	ANSI_CHARSET,					// Character Set Identifier
	OUT_STROKE_PRECIS,					// Output Precision
	CLIP_STROKE_PRECIS,			// Clipping Precision
	ANTIALIASED_QUALITY,			// Output Quality
	FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
	"Courier New"					// Font Name
};

const LOGFONT	DEF_TEXT_DIRFONT = 
{
	-21,							// Height Of Font
	0,								// Width Of Font
	0,								// Angle Of Escapement
	0,								// Orientation Angle
	FW_NORMAL,						// Font Weight
	FALSE,							// Italic
	FALSE,							// Underline
	FALSE,							// Strikeout
	ANSI_CHARSET,					// Character Set Identifier
	OUT_STROKE_PRECIS,					// Output Precision
	CLIP_STROKE_PRECIS,			// Clipping Precision
	ANTIALIASED_QUALITY,			// Output Quality
	FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
	"Arial Black"					// Font Name
};


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


// CArchive reads
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

CArchive& operator>> ( CArchive& ar, vector3& v )
{
	return ar >> v.x >> v.y >> v.z;
}

CArchive& operator>> ( CArchive& ar, vector2& v )
{
	return ar >> v.x >> v.y;
}

CArchive& operator>> ( CArchive& ar, LOGFONT& f )
{
	CArchive* ret = &(ar
		>> f.lfHeight
		>> f.lfWidth
		>> f.lfEscapement
		>> f.lfOrientation
		>> f.lfWeight
		>> f.lfItalic
		>> f.lfUnderline
		>> f.lfStrikeOut
		>> f.lfCharSet
		>> f.lfOutPrecision
		>> f.lfClipPrecision
		>> f.lfQuality
		>> f.lfPitchAndFamily);

	for( int i=0; i<LF_FACESIZE; i++ )
		ret = &( *ret >> f.lfFaceName[i] );
	
	return *ret;
}


// CArchive writes
CArchive& operator<< ( CArchive& ar, season_e s )
{
	return ar << (int)s;
}

CArchive& operator<< ( CArchive& ar, color_s c )
{
	return ar << c.r << c.g << c.b;
}

CArchive& operator<< ( CArchive& ar, vector3 v )
{
	return ar << v.x << v.y << v.z;
}

CArchive& operator<< ( CArchive& ar, vector2 v )
{
	return ar << v.x << v.y;
}

CArchive& operator<< ( CArchive& ar, LOGFONT f )
{
	CArchive* ret = &(ar
		<< f.lfHeight
		<< f.lfWidth
		<< f.lfEscapement
		<< f.lfOrientation
		<< f.lfWeight
		<< f.lfItalic
		<< f.lfUnderline
		<< f.lfStrikeOut
		<< f.lfCharSet
		<< f.lfOutPrecision
		<< f.lfClipPrecision
		<< f.lfQuality
		<< f.lfPitchAndFamily);

	for( int i=0; i<LF_FACESIZE; i++ )
		ret = &( *ret << f.lfFaceName[i] );
	
	return *ret;
}


// Multiply color convenience functions
color_s operator* ( const color_s c, const float f )
{
	color_s ret = c;
	ret.r *= f;
	ret.g *= f;
	ret.b *= f;
	return ret;
}

color_s operator* ( const color_s c1, const color_s c2 )
{
	color_s ret;
	ret.r = c1.r*c2.r;
	ret.g = c1.g*c2.g;
	ret.b = c1.b*c2.b;
	return ret;
}


// Star comparison (for sorting by magnitude)
BOOL operator< ( CDataStar& s1, CDataStar& s2 )
{
	return s1.GetMag() < s2.GetMag();
}

// Message boxes (handle not specified)
void CSInfo( const char* msg, const char* title )
{
	CSInfo( GetFrame()->GetSafeHwnd(), msg, title );
}

int CSQuestion( const char* msg, const char* title )
{
	return CSQuestion( GetFrame()->GetSafeHwnd(), msg, title );
}

int CSYesNoCancel( const char* msg, const char* title )
{
	return CSYesNoCancel( GetFrame()->GetSafeHwnd(), msg, title );
}

void CSWarn( const char* msg, const char* title )
{
	CSWarn( GetFrame()->GetSafeHwnd(), msg, title );
}

void CSError( const char* msg, const char* title )
{
	CSError( GetFrame()->GetSafeHwnd(), msg, title );
}

void CSDebug( const char* msg, const char* title )
{
	CSError( GetFrame()->GetSafeHwnd(), msg, title );
}


// Message boxes (handle specified)
void CSInfo( HWND parent, const char* msg, const char* title )
{
	MessageBox( parent, msg, title, MB_ICONINFORMATION | MB_OK );
}

int CSQuestion( HWND parent, const char* msg, const char* title )
{
	return MessageBox( parent, msg, title, MB_ICONQUESTION | MB_YESNO );
}

int  CSYesNoCancel( HWND parent, const char* msg, const char* title )
{
	return MessageBox( parent, msg, title, MB_ICONQUESTION | MB_YESNOCANCEL );
}

void CSWarn( HWND parent, const char* msg, const char* title )
{
	MessageBox( parent, msg, title, MB_ICONWARNING | MB_OK );
}

void CSError( HWND parent, const char* msg, const char* title )
{
	MessageBox( parent, msg, title, MB_ICONERROR | MB_OK );
}


