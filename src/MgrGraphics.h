//===========================================================================
// MgrGraphics.h
//
// CMgrGraphics
//   handles all OpenGL graphics.
//===========================================================================

#ifndef CS_MGRGRAPHICS_H
#define CS_MGRGRAPHICS_H

#include "Matrix.h"


class CMgrGraphics
{
// Construction
public:
	CMgrGraphics();

// Attributes
public:

	// Contexts
	HDC		hDC;
	HGLRC	hRC;

	// Dimensions
	int width;
	int height;

	// Frustum
	vector4 frustum[6];

	// Fov angle
	float fov;

	// Textures
	UINT starTex;
	UINT skyTex;

	// Sky
	GLUquadricObj* skySphere;

	// Sun
	GLUquadricObj* sunSphere;
	float sunPos[3];


// Methods
public:
// Initialization
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat();

// Drawing functions
	void Paint();
	void Draw();
	void DrawTerrain();
	void DrawSky();
	void DrawSun();
	void DrawSunlight();
	void DrawStars();
	void DrawStarQuad( int i );
	void DrawStarPoint( int i );
	void DrawConsts();
	void DrawConst( int i );
	void DrawCurConst( int i );
	void DrawCompass();

// View manipulation
	void Size( int cx, int cy );
	void Projection();
	void Perspective();
	void LoadSkyMat();
	void LoadStarfMat();
	void LoadSunMat();
	void LoadTerrainMat();

// Textures
	BOOL LoadTGA( UINT &texID, char* filename );
	BOOL LoadTextures();

// Colors
	void SetColor( color_s c );

// Frustum
	void CalculateFrustum();
	BOOL SphereInFrustum( vector3 v, float radius );


// Destruction
public:
	~CMgrGraphics();
	void Destroy();

};

#endif