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

#include "DataStarfield.h"
#include "DataTerrain.h"


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
// ABSOLUTE DEFAULTS

extern const BOOL		DEF_STARS_VISIBLE;
extern const BOOL		DEF_STARS_LABELED;
extern const BOOL		DEF_STARS_TEXTURED;
extern const BOOL		DEF_STARS_COLORED;
extern const float		DEF_STARS_LIMMAG;
extern const int		DEF_STARS_GAMMA;
extern const int		DEF_STARS_CONTRAST;
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
extern const float		DEF_TERR_ROUGHNESS;
extern const BOOL		DEF_TERR_TEXTURED;
extern const season_e	DEF_TERR_SEASON;
extern const color_s	DEF_TERR_WINCOLOR;
extern const color_s	DEF_TERR_SPRCOLOR;
extern const color_s	DEF_TERR_SUMCOLOR;
extern const color_s	DEF_TERR_FALCOLOR;
extern const color_s	DEF_COMPASS_CROSSCOLOR;
extern const color_s	DEF_COMPASS_NEEDLECOLOR;


/////////////////////////////////////////////////////////////////////////////
// MAXIMUMS

#define	MAX_STARS			15000///100000
#define	MAX_CONSTS			200
#define MAX_CONSTLINES		100
#define	MAX_DOC_NAME		32


/////////////////////////////////////////////////////////////////////////////
// MAIN CLASSES

#include "ConStation.h"
#include "ConStationFrame.h"
#include "ConStationView.h"
#include "MgrInput.h"
#include "MgrGraphics.h"
#include "MgrOptions.h"
#include "MgrDocument.h"
#include "MgrStarfield.h"
#include "MgrConst.h"
#include "MgrTerrain.h"
#include "MgrTeacher.h"

extern CMgrInput		inputMgr;
extern CMgrGraphics		graphicsMgr;
extern CMgrOptions		optionsMgr;
extern CMgrDocument		documentMgr;
extern CMgrStarfield	starfieldMgr;
extern CMgrConst		constMgr;
extern CMgrTerrain		terrainMgr;
extern CMgrTeacher		teacherMgr;

extern CDataStarfield	starfield;
extern CDataTerrain		terrain;


/////////////////////////////////////////////////////////////////////////////
// MFC CLASS ACCESS

CConStationApp* GetApp();
CConStationFrame* GetFrame();
CConStationView* GetView();


/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

void SetState( state_e s );
void Redraw();

// Message boxes (handle not specified)
void CSInfo( char* msg, char* title="Information" );
int  CSQuestion(  char* msg, char* title="Question" );
int  CSYesNoCancel( char* msg, char* title="Question" );
void CSWarn( char* msg, char* title="Warning" );
void CSError( char* msg, char* title );

// Message boxes (handle specified)
void CSInfo( HWND parent, char* msg, char* title="Information" );
int  CSQuestion(  HWND parent, char* msg, char* title="Question" );
int  CSYesNoCancel( HWND parent, char* msg, char* title="Question" );
void CSWarn( HWND parent, char* msg, char* title="Warning" );
void CSError( HWND parent, char* msg, char* title );


#endif