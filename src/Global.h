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

#include "Starfield.h"
#include "Terrain.h"


extern state_e state;
extern const color_s COLOR_WHITE,
					 COLOR_BLACK,
					 COLOR_CROSS,
					 COLOR_ACTIVESTAR,
					 COLOR_CONSTLINE,
					 COLOR_SUN,
					 COLOR_SKY,
					 COLOR_NORTHSTAR;

#define PI      3.14159265358979323846f


/////////////////////////////////////////////////////////////////////////////
// MAIN CLASSES

#include "ConStation.h"
#include "ConStationFrame.h"
#include "ConStationView.h"
#include "MgrInput.h"
#include "MgrGraphics.h"
#include "MgrConst.h"
#include "MgrStarf.h"
#include "MgrTerrain.h"
#include "MgrTeacher.h"

extern CMgrInput inputMgr;
extern CMgrGraphics graphicsMgr;
extern CMgrConst constMgr;
extern CMgrStarf starfMgr;
extern CMgrTerrain terrainMgr;
extern CMgrTeacher teacherMgr;

extern CStarfield starfield;
extern CTerrain terrain;


/////////////////////////////////////////////////////////////////////////////
// MFC CLASS ACCESS

CConStationApp* GetApp();
CConStationFrame* GetFrame();
CConStationView* GetView();


/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

void SetState( state_e s );
void Redraw();
void CSInfo( char* msg, char* title="Information" );
int  CSQuestion( char* msg, char* title="Question" );
int  CSYesNoCancel( char* msg, char* title );
void CSWarn( char* msg, char* title="Error" );
void CSError( char* msg, char* title );


#endif