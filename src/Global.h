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
	season_Fall
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
	GLuint width;
	GLuint height;
	GLubyte* data;
} texture_s;

typedef struct
{
	unsigned short hour;
	unsigned short minute;
	float second;
} ra_s;

typedef struct
{
	BOOL positive;
	unsigned short degree;
	unsigned short minute;
	float second;
} dec_s;


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

#define PI      3.14159265358979323846f


/////////////////////////////////////////////////////////////////////////////
// DEFAULTS

extern const BOOL		DEF_STARS_VISIBLE;
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
extern const BOOL		DEF_CONST_VISIBLE;
extern const BOOL		DEF_CONST_LABELED;
extern const color_s	DEF_CONST_NORMCOLOR;
extern const color_s	DEF_CONST_SELCOLOR;
extern const color_s	DEF_CONST_ACTIVECOLOR;
extern const color_s	DEF_CONST_STARCOLOR;
extern const BOOL		DEF_CONST_STARSCOLORED;
extern const BOOL		DEF_SUN_VISIBLE;
extern const BOOL		DEF_SUN_SHINE;
extern const BOOL		DEF_TERR_VISIBLE;
extern const BOOL		DEF_TERR_TEXTURED;
extern const int		DEF_TERR_ROUGHNESSX100;
extern const int		DEF_TERR_SCALE;
extern const int		DEF_TERR_ITERS;
extern const season_e	DEF_TERR_SEASON;
extern const color_s	DEF_TERR_WINCOLOR;
extern const color_s	DEF_TERR_SPRCOLOR;
extern const color_s	DEF_TERR_SUMCOLOR;
extern const color_s	DEF_TERR_FALCOLOR;
extern const color_s	DEF_COMPASS_CROSSCOLOR;
extern const color_s	DEF_COMPASS_NEEDLECOLOR;


/////////////////////////////////////////////////////////////////////////////
// MAXIMUMS / MINIMUMS

#define	MAX_STARS					100000
#define	MAX_CONSTS					200
#define MAX_CONSTLINES				100
#define	MAX_DOC_NAME				32
#define MIN_STARS_MAG				-1.44F
#define MAX_STARS_BRIGHT_RADIUS		0.02F
#define MIN_STARS_BRIGHT_RADIUS		0.005F
#define MAX_STARS_BRIGHT_COLOR		1.0F
#define MIN_STARS_BRIGHT_COLOR		0.01F
// Dim radius is stored as a percent of the brightest radius
#define MAX_STARS_DIM_RADIUS_PERC	100   // User has full control from 100%
#define MIN_STARS_DIM_RADIUS_PERC	0     //  to 0%
// Dim color is stored as a percent of the brightest color
#define MAX_STARS_DIM_COLOR_PERC	100   // User has full control from 100%
#define MIN_STARS_DIM_COLOR_PERC	0     //  to 0%


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

// Special CArchive functions
CArchive& operator>> ( CArchive& ar, season_e& s );
CArchive& operator>> ( CArchive& ar, color_s& c );

CArchive& operator<< ( CArchive& ar, season_e s );
CArchive& operator<< ( CArchive& ar, color_s c );


// Message boxes (handle not specified)
void CSInfo( char* msg, char* title="Information" );
int  CSQuestion(  char* msg, char* title="Question" );
int  CSYesNoCancel( char* msg, char* title="Question" );
void CSWarn( char* msg, char* title="Warning" );
void CSError( char* msg, char* title="Error" );
void CSDebug( char* msg, char* title );

// Message boxes (handle specified)
void CSInfo( HWND parent, char* msg, char* title="Information" );
int  CSQuestion(  HWND parent, char* msg, char* title="Question" );
int  CSYesNoCancel( HWND parent, char* msg, char* title="Question" );
void CSWarn( HWND parent, char* msg, char* title="Warning" );
void CSError( HWND parent, char* msg, char* title );


#endif