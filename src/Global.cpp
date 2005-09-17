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

BOOL dbgGod = FALSE;
BOOL dbgFog = TRUE;
BOOL dbgTerrExternal = FALSE;
BOOL dbgTerrWire = FALSE;
BOOL dbgStarfDepthTest = FALSE;
float dbgTerrViewHeight = 0.0f;
float dbgTerrViewDistance = 0.0f;



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

const location_s	DEF_LOCATION_HOME = location_s
(
	CString("USA"),
	CString("NM"),
	CString("Portales"),
	34,
	12,
	'N',
	103,
	20,
	'W',
	-7
);

const BOOL			DEF_STARS_VISIBLE			= TRUE;
const BOOL			DEF_STARS_DAYLIGHT			= FALSE;
const BOOL			DEF_STARS_LABELED			= FALSE;
const BOOL			DEF_STARS_TEXTURED			= TRUE;
const BOOL			DEF_STARS_COLORED			= FALSE;
const int			DEF_STARS_LIMMAGX10			= 70;
const int			DEF_STARS_SIZE				= 25;
const int			DEF_STARS_SCONTRAST			= 50;
const int			DEF_STARS_CCONTRAST			= 75;
const float			DEF_STARS_BRIGHT_RADIUS		= 0.013f;
const float			DEF_STARS_BRIGHT_COLOR		= 1.0f;
const float			DEF_STARS_RADIUS_DIFF		= 0.011f;
const float			DEF_STARS_COLOR_DIFF		= 0.8f;
const color_s		DEF_STARS_SPECTRAL_O_COLOR	= { 1.0f, 0.85f, 1.0f };
const color_s		DEF_STARS_SPECTRAL_B_COLOR	= { 0.5f, 1.0f, 1.0f };
const color_s		DEF_STARS_SPECTRAL_A_COLOR	= { 1.0f, 1.0f, 1.0f };
const color_s		DEF_STARS_SPECTRAL_F_COLOR	= { 1.0f, 1.0f, 0.5f };
const color_s		DEF_STARS_SPECTRAL_G_COLOR	= { 1.0f, 0.95f, 1.0f };
const color_s		DEF_STARS_SPECTRAL_K_COLOR	= { 1.0f, 0.75f, 1.0f };
const color_s		DEF_STARS_SPECTRAL_M_COLOR	= { 1.0f, 0.75f, 0.5f };


const BOOL			DEF_CONST_VISIBLE		= TRUE;
const BOOL			DEF_CONST_DAYLIGHT		= TRUE;
const BOOL			DEF_CONST_LABELED		= TRUE;
const BOOL			DEF_CONST_LINESVISIBLE	= TRUE;
const color_s		DEF_CONST_NORMCOLOR		= {0.5f, 0.25f, 0.0f};
///const color_s		DEF_TEXT_CONSTCOLOR		= {0.5f, 0.0f, 0.5f}; /// purple theme
const color_s		DEF_CONST_SELCOLOR		= {0.0f, 0.75f, 0.25f};
const color_s		DEF_CONST_ACTIVECOLOR	= {1.0f, 1.0f, 0.0f};
const color_s		DEF_CONST_STARCOLOR		= {1.0f, 0.5f, 1.0f};
const BOOL			DEF_CONST_STARSCOLORED	= TRUE;
const int			DEF_CONST_LINEWIDTH		= 3;

const float			DEF_SUN_RADIUS			= 0.08f;
const color_s		DEF_SUN_COLOR			= {1.0f, 1.0f, 0.5f};
const BOOL			DEF_SUN_VISIBLE			= TRUE;
const BOOL			DEF_SUN_SHINE			= TRUE;

const color_s		DEF_SKY_COLOR			= {0.7f, 0.9f, 1.0f};///{0.6f, 0.7f, 1.0f};

const BOOL			DEF_TERR_VISIBLE		= TRUE;
const BOOL			DEF_TERR_TEXTURED		= TRUE;
const int			DEF_TERR_ROUGHNESSX100	= 20;
const int			DEF_TERR_SCALE			= 5;
const int			DEF_TERR_TEX_ITERS		= 7;
const int			DEF_TERR_HEIGHT_ITERS	= 5;
const float			DEF_TERR_VIEW_HEIGHT	= 0.1f;
const season_e		DEF_TERR_SEASON			= season_Spring;
const color_s		DEF_TERR_WINCOLOR		= {0.7f, 0.7f, 0.7f};
const color_s		DEF_TERR_SPRCOLOR		= {0.15f, 0.25f, 0.1f};
const color_s		DEF_TERR_SUMCOLOR		= {0.1f, 0.3f, 0.1f};
const color_s		DEF_TERR_FALCOLOR		= {0.25f, 0.25f, 0.15f};

const color_s		DEF_TEXT_CONSTCOLOR		= {1.0f, 0.5f, 0.0f};
///const color_s		DEF_TEXT_CONSTCOLOR		= {1.0f, 0.5f, 0.7f}; /// purple theme
const color_s		DEF_TEXT_CONSTSELCOLOR	= {1.0f, 1.0f, 1.0f};
const color_s		DEF_TEXT_STARCOLOR		= {1.0f, 0.0f, 0.0f};
const color_s		DEF_TEXT_DIRCOLOR		= {1.0f, 0.5f, 0.0f};

const color_s		DEF_COMPASS_CROSSCOLOR	= {0.4f, 0.8f, 0.5f};
const color_s		DEF_COMPASS_FRUSTUMCOLOR	= {1.0f, 1.0f, 0.7f};
///const color_s		DEF_COMPASS_CROSSCOLOR	= {0.4f, 0.25f, 0.1f};//{0.3f, 0.3f, 0.8f};
///const color_s		DEF_COMPASS_FRUSTUMCOLOR	= {0.7f, 1.0f, 0.7f};

const float			DEF_FOG_DENSITY			= 0.2f;//1.0f
const float			DEF_FOG_START			= 4.5f;//0.9f
const float			DEF_FOG_END				= 4.8f;//1.0f

const LOGFONT		DEF_TEXT_CONSTFONT = 
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

const LOGFONT		DEF_TEXT_STARFONT = 
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
	OUT_STROKE_PRECIS,				// Output Precision
	CLIP_STROKE_PRECIS,				// Clipping Precision
	ANTIALIASED_QUALITY,			// Output Quality
	FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
	"Courier New"					// Font Name
};

const LOGFONT		DEF_TEXT_DIRFONT = 
{
	-18,							// Height Of Font
	0,								// Width Of Font
	0,								// Angle Of Escapement
	0,								// Orientation Angle
	FW_NORMAL,						// Font Weight
	FALSE,							// Italic
	FALSE,							// Underline
	FALSE,							// Strikeout
	ANSI_CHARSET,					// Character Set Identifier
	OUT_STROKE_PRECIS,				// Output Precision
	CLIP_STROKE_PRECIS,				// Clipping Precision
	ANTIALIASED_QUALITY,			// Output Quality
	FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
	"Arial"							// Font Name
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


// Time functions
double UTtoJulian( int y, int m, int d, int h, int n, int s )
{
	// Method for converting gregorian date to julian date from
	//  http://scienceworld.wolfram.com/astronomy/JulianDate.html
	
	/// Mostly accurate. Doesn't account for deleted/added days in the past
	double j = 367*y - 7*(y+(m+9)/12)/4
		 - 3*((y+(m-9)/7)/100+1)/4
		 + 275*m/9 + d + 1721028.5
		 + (h+(n+(s/60.0))/60.0)/24.0;
	return j;
}

double UTtoJulian( COleDateTime& ut )
{
	return UTtoJulian( ut.GetYear(), ut.GetMonth(), ut.GetDay(), ut.GetHour(), ut.GetMinute(), ut.GetSecond() );
}

COleDateTime LTtoUT( COleDateTime& lt, float tz, BOOL dst )
{
	COleDateTime ut;
	ut.m_dt = lt.m_dt - tz/24.0;
	if( dst ) ut.m_dt -= 1/24.0;
	return ut;
}

COleDateTime UTtoLT( COleDateTime& ut, float tz, BOOL dst )
{
	COleDateTime lt;
	lt.m_dt = ut.m_dt + tz/24.0;
	if( dst ) lt.m_dt += 1/24.0;
	return lt;
}

COleDateTime JulianToUT( double j )
{
	// From http://www.csgnetwork.com/julianmodifdateconv.html
	int year, month, day, hour, minute, second;
	double ut;
	double l, n;

	int jdi = (int)j;
	double jdf = j-jdi+0.5;

    if (jdf >= 1.0) {
       jdf = jdf - 1.0;
       jdi = jdi + 1;
    }

	// Calculate time
    ut = jdf * 24.0;
	hour = (int)ut;
	ut -= hour;
	minute = (int)(ut*60);
	ut -= minute/60.0;
	second = (int)(ut*3600);


    l = jdi + 68569;
    n = (int)(4 * l / 146097.0);
   
    l = (int)l - (int)((146097 * n + 3) / 4.0);
    year = (int) (4000 * (l + 1) / 1461001.0);
    
    l = l - (int)(1461 * year / 4.0) + 31;
    month = (int)(80 * l / 2447.0);
    
    day = l - (int)(2447 * month / 80.0);
    
    l = (int)(month / 11.0);
    
    month = (int)(month + 2 - 12 * l);
    year = (int)(100 * (n - 49) + year + l);

	return COleDateTime( year, month, day, hour, minute, second );

	/*
    if (month < 10)
       month = "0" + month;
       
    if (day < 10)
       day = "0" + day;
    
    //year = year - 1900;
    
    return (new Array (year, month, day));

	/*
    var year;
    var month;
    var day;
    var hour;
    var jd;
    var jdi;
    var jdf
    var l;
    var n;
    
    
    // Julian day
    jd = Math.floor (mjd_in) + 2400000.5;

    // Integer Julian day
    jdi = Math.floor (jd);
    
    // Fractional part of day
    jdf = jd - jdi + 0.5;
    
    // Really the next calendar day?
    if (jdf >= 1.0) {
       jdf = jdf - 1.0;
       jdi = jdi + 1;
    }


    hour = jdf * 24.0;    
    l = jdi + 68569;
    n = Math.floor (4 * l / 146097);
   
    l = Math.floor (l) - Math.floor ((146097 * n + 3) / 4);
    year = Math.floor (4000 * (l + 1) / 1461001);
    
    l = l - (Math.floor (1461 * year / 4)) + 31;
    month = Math.floor (80 * l / 2447);
    
    day = l - Math.floor (2447 * month / 80);
    
    l = Math.floor (month / 11);
    
    month = Math.floor (month + 2 - 12 * l);
    year = Math.floor (100 * (n - 49) + year + l);

    if (month < 10)
       month = "0" + month;
       
    if (day < 10)
       day = "0" + day;
    
    //year = year - 1900;
    
    return (new Array (year, month, day));
	*/
}



// CArchive reads
CArchive& operator>> ( CArchive& ar, location_s& l )
{
	return ar
		>> l.country
		>> l.state
		>> l.city
		>> l.latd
		>> l.latm
		>> l.ns
		>> l.lond
		>> l.lonm
		>> l.ew
		>> l.timezone;
}

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
CArchive& operator<< ( CArchive& ar, location_s& l )
{
	return ar
		<< l.country
		<< l.state
		<< l.city
		<< l.latd
		<< l.latm
		<< l.ns
		<< l.lond
		<< l.lonm
		<< l.ew
		<< l.timezone;
}

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

// OpenGL convenience functions
void glColor( const color_s c )
{
	glColor3f( c.r, c.g, c.b );
}

void glColor4( const color_s c, float alpha )
{
	glColor4f( c.r, c.g, c.b, alpha );
}

void glVertex( vector3 v )
{
	glVertex3f( v.x, v.y, v.z );
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


