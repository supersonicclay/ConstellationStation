

#ifndef GLOBAL_H
#define GLOBAL_H


#include "stdafx.h"



// TYPES
typedef struct
{
	float r;
	float g;
	float b;
} color_t;

typedef struct
{
	GLubyte* data;
	GLuint width;
	GLuint height;
	GLuint textureID;
} texture_t;

enum state_t {	state_Viewing,
				state_AddingLine,
				state_AddingPoly,
				state_DeletingLine};


#include "Starfield.h"
#include "Terrain.h"


// VARIABLES
extern CStarfield* starfield;
extern CTerrain* terrain;
extern state_t state;
extern const color_t COLOR_WHITE,
					 COLOR_BLACK,
					 COLOR_SKY,
					 COLOR_CROSS,
					 COLOR_ACTIVESTAR,
					 COLOR_NORTHSTAR,
					 COLOR_CONSTLINE;

#define	PI		3.14159265358979323846


// FUNCTIONS
void glColor( color_t c );

BOOL LoadTGA( texture_t &texture, char* filename );

void SetState( enum state_t s );

/// TIME CONSUMING, SHOULD BE CALLED SPARINGLY
void RedrawView();


#endif