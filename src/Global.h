

#ifndef GLOBAL_H
#define GLOBAL_H


#include "stdafx.h"



// TYPES
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

enum state_e {	state_Viewing,
				state_AddingLine,
				state_AddingPoly,
				state_DeletingLine};

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

#include "Starfield.h"
#include "Terrain.h"


// VARIABLES
extern CStarfield* starfield;
extern CTerrain* terrain;
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


// FUNCTIONS
void glColor( color_s c );

BOOL LoadTGA( UINT &texID, char* filename );

void SetState( enum state_e s );

// TIME CONSUMING, SHOULD BE CALLED SPARINGLY
void RedrawView();


#endif