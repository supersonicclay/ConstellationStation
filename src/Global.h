//===========================================================================
// Global.h
//
// Various global variables and types
//===========================================================================

#ifndef CS_GLOBAL_H
#define CS_GLOBAL_H

#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// TYPES

enum state_e
{
	state_Viewing,
	state_AddingLine,
	state_DeletingLine
};

enum select_e
{
	select_Star,
	select_Const,
	select_Line
};

enum season_e
{
	season_Winter=0,
	season_Spring,
	season_Summer,
	season_Autumn
};

enum track_e
{
	track_None,
	track_Const,
	track_Star,
	track_RADec
};

enum animation_e
{
	animation_Paused,
	animation_Forward,
	animation_Reverse
};

enum speed_e
{
	speed_Now=0,
	speed_Realtime,
	speed_Seconds,
	speed_Minutes,
	speed_Hours,
	speed_Days,
	speed_Years,
	speed_SiderealDays
};

enum popup_e
{
	popup_Constellation=0,
	popup_Star,
	popup_ConstellationAndStar
};

typedef struct
{
	float r;
	float g;
	float b;
} color_s;

typedef struct
{
	GLuint id;
	GLuint type;
	GLuint width;
	GLuint height;
	GLubyte* data;
} texture_s;

typedef struct
{
	int hour;
	int minute;
	float second;
} ra_s;

typedef struct
{
	BOOL positive;
	USHORT degree;
	USHORT minute;
	float second;
} dec_s;


/////////////////////////////////////////////////////////////////////////////
/// DEBUG VARS

extern BOOL terrFog;
extern BOOL terrExternal;
extern BOOL terrWire;


/////////////////////////////////////////////////////////////////////////////
// VARIABLES

extern state_e state;
extern const color_s COLOR_WHITE,
					 COLOR_BLACK,
					 COLOR_RED,
					 COLOR_GREEN,
					 COLOR_DARKGREEN,
					 COLOR_BLUE,
					 COLOR_DARKBLUE,
					 COLOR_YELLOW,
					 COLOR_TEAL,
					 COLOR_DARKTEAL;

#define PI	    3.1415926535898f
#define PIHALF  1.5707963267949f
#define PI2     6.2831853071796f


/////////////////////////////////////////////////////////////////////////////
// DEFAULTS

extern const BOOL		DEF_STARS_VISIBLE;
extern const BOOL		DEF_STARS_DAYLIGHT;
extern const BOOL		DEF_STARS_LABELED;
extern const BOOL		DEF_STARS_TEXTURED;
extern const BOOL		DEF_STARS_COLORED;
extern const int		DEF_STARS_LIMMAGX10;
extern const int		DEF_STARS_SIZE;
extern const int		DEF_STARS_SCONTRAST;
extern const int		DEF_STARS_CCONTRAST;
extern const float		DEF_STARS_BRIGHT_RADIUS;
extern const float		DEF_STARS_BRIGHT_COLOR;
extern const float		DEF_STARS_RADIUS_DIFF;
extern const float		DEF_STARS_COLOR_DIFF;
extern const color_s	DEF_STARS_SPECTRAL_O_COLOR;
extern const color_s	DEF_STARS_SPECTRAL_B_COLOR;
extern const color_s	DEF_STARS_SPECTRAL_A_COLOR;
extern const color_s	DEF_STARS_SPECTRAL_F_COLOR;
extern const color_s	DEF_STARS_SPECTRAL_G_COLOR;
extern const color_s	DEF_STARS_SPECTRAL_K_COLOR;
extern const color_s	DEF_STARS_SPECTRAL_M_COLOR;

extern const BOOL		DEF_CONST_VISIBLE;
extern const BOOL		DEF_CONST_DAYLIGHT;
extern const BOOL		DEF_CONST_LABELED;
extern const BOOL		DEF_CONST_LINESVISIBLE;
extern const color_s	DEF_CONST_NORMCOLOR;
extern const color_s	DEF_CONST_SELCOLOR;
extern const color_s	DEF_CONST_ACTIVECOLOR;
extern const color_s	DEF_CONST_STARCOLOR;
extern const BOOL		DEF_CONST_STARSCOLORED;
extern const int		DEF_CONST_LINEWIDTH;

extern const float		DEF_SUN_RADIUS;
extern const color_s	DEF_SUN_COLOR;
extern const BOOL		DEF_SUN_VISIBLE;
extern const BOOL		DEF_SUN_SHINE;

extern const color_s	DEF_SKY_COLOR;

extern const BOOL		DEF_TERR_VISIBLE;
extern const BOOL		DEF_TERR_TEXTURED;
extern const int		DEF_TERR_ROUGHNESSX100;
extern const int		DEF_TERR_SCALE;
extern const int		DEF_TERR_TEX_ITERS;
extern const int		DEF_TERR_HEIGHT_ITERS;
extern const season_e	DEF_TERR_SEASON;
extern const color_s	DEF_TERR_WINCOLOR;
extern const color_s	DEF_TERR_SPRCOLOR;
extern const color_s	DEF_TERR_SUMCOLOR;
extern const color_s	DEF_TERR_FALCOLOR;

extern const LOGFONT	DEF_TEXT_CONSTFONT;
extern const LOGFONT	DEF_TEXT_STARFONT;
extern const LOGFONT	DEF_TEXT_DIRFONT;
extern const color_s	DEF_TEXT_CONSTCOLOR;
extern const color_s	DEF_TEXT_CONSTSELCOLOR;
extern const color_s	DEF_TEXT_STARCOLOR;
extern const color_s	DEF_TEXT_DIRCOLOR;

extern const color_s	DEF_COMPASS_CROSSCOLOR;
extern const color_s	DEF_COMPASS_FRUSTUMCOLOR;


/////////////////////////////////////////////////////////////////////////////
// MAXIMUMS / MINIMUMS

#define	MAX_STARS					80000
#define	MAX_CONSTS					200
#define MAX_CONSTLINES				100
#define	MAX_DOC_NAME				32
#define MIN_STARS_MAG				-1.44F
#define MAX_STARS_BRIGHT_RADIUS		0.0300F
#define MIN_STARS_BRIGHT_RADIUS		0.0001F
#define MAX_STARS_BRIGHT_COLOR		1.0F
#define MIN_STARS_BRIGHT_COLOR		0.01F
// Dim radius is stored as a percent of the brightest radius
#define MAX_STARS_DIM_RADIUS_PERC	80   // User has control from 80%
#define MIN_STARS_DIM_RADIUS_PERC	0    //  to 0%
// Dim color is stored as a percent of the brightest color
#define MAX_STARS_DIM_COLOR_PERC	80   // User has control from 80%
#define MIN_STARS_DIM_COLOR_PERC	0    //  to 0%
#define MAX_TERR_ROUGHNESS			0.6F


/////////////////////////////////////////////////////////////////////////////
// OTHER DEFINES

#define STARS_BRIGHT_RADIUS_RANGE	(MAX_STARS_BRIGHT_RADIUS - MIN_STARS_BRIGHT_RADIUS)
#define STARS_BRIGHT_COLOR_RANGE	(MAX_STARS_BRIGHT_COLOR - MIN_STARS_BRIGHT_COLOR)
#define STARS_DIM_RADIUS_PERC_RANGE	(MAX_STARS_DIM_RADIUS_PERC - MIN_STARS_DIM_RADIUS_PERC)
#define STARS_DIM_COLOR_PERC_RANGE	(MAX_STARS_DIM_COLOR_PERC - MIN_STARS_DIM_COLOR_PERC)


/////////////////////////////////////////////////////////////////////////////
// MAIN CLASSES

#include "CSApp.h"
#include "CSFrame.h"
#include "CSView.h"

#include "DataStarf.h"
#include "DataTerrain.h"

#include "MgrInput.h"
#include "MgrGraphics.h"
#include "MgrText.h"
#include "MgrOptions.h"
#include "MgrDocument.h"
#include "MgrStarf.h"
#include "MgrConst.h"
#include "MgrTerrain.h"
#include "MgrTeacher.h"

extern CDataStarf		starfield;
extern CDataTerrain		terrain;

extern CMgrInput		inputMgr;
extern CMgrGraphics		graphicsMgr;
extern CMgrText			textMgr;
extern CMgrOptions		optionsMgr;
extern CMgrDocument		documentMgr;
extern CMgrStarf		starfMgr;
extern CMgrConst		constMgr;
extern CMgrTerrain		terrainMgr;
extern CMgrTeacher		teacherMgr;


/////////////////////////////////////////////////////////////////////////////
// MFC CLASS ACCESS

CCSApp* GetApp();
CCSFrame* GetFrame();
CCSView* GetView();


/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

void SetState( state_e s );
void Redraw();

// Math functions
double GregorianToJulian( int y, int m, int d, int h, int n, int s );

// Special CArchive functions
CArchive& operator>> ( CArchive& ar, season_e& s );
CArchive& operator>> ( CArchive& ar, color_s& c );
CArchive& operator>> ( CArchive& ar, vector3& v );
CArchive& operator>> ( CArchive& ar, vector2& v );
CArchive& operator>> ( CArchive& ar, LOGFONT& f );

CArchive& operator<< ( CArchive& ar, season_e s );
CArchive& operator<< ( CArchive& ar, color_s c );
CArchive& operator<< ( CArchive& ar, vector3 v );
CArchive& operator<< ( CArchive& ar, vector2 v );
CArchive& operator<< ( CArchive& ar, LOGFONT f );

// Multiply color convenience functions
color_s operator* ( const color_s c, const float f );
color_s operator* ( const color_s c1, const color_s c2 );

// Star comparison (for sorting by magnitude)
BOOL operator< ( CDataStar& s1, CDataStar& s2 );

// OpenGL convenience functions
void glColor( const color_s c );
void glColor4( const color_s c, float alpha );
void glVertex( const vector3 v );


// Message boxes (handle not specified)
void CSInfo( const char* msg, const char* title="Information" );
int  CSQuestion(  const char* msg, const char* title="Question" );
int  CSYesNoCancel( const char* msg, const char* title="Question" );
void CSWarn( const char* msg, const char* title="Warning" );
void CSError( const char* msg, const char* title="Error" );
void CSDebug( const char* msg, const char* title );

// Message boxes (handle specified)
void CSInfo( HWND parent, const char* msg, const char* title="Information" );
int  CSQuestion(  HWND parent, const char* msg, const char* title="Question" );
int  CSYesNoCancel( HWND parent, const char* msg, const char* title="Question" );
void CSWarn( HWND parent, const char* msg, const char* title="Warning" );
void CSError( HWND parent, const char* msg, const char* title );


#endif