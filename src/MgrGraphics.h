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

	// Matrices
	matrix44 perspMat;
	matrix44 skyMat;
	matrix44 starfMat;
	matrix44 sunMat;
	matrix44 terrainMat;

	// Fov angle
	float fov;

	// Colors
	color_s skyColor;
	color_s redColor;  // sunrise and sunset

	// Frustum
	vector4 frustum[6];

	// Textures
	UINT starTex;
	UINT sunBodyTex;
	UINT sunCoronaTex;
	UINT sunGlowTex;
	UINT skyTex;

	// Daylight
	float dayFactor;   // see UpdateDayFactor()
	float dayAlpha;    // see UpdateDayAlpha()
	float starAlpha;   // see UpdateDayAlpha()
	float constAlpha;  // see UpdateDayAlpha()

	// Sky
	GLUquadricObj* skySphere;

	// Sun
	GLUquadricObj* sunSphere;
	float sunPos[3];

	// Terrain
	float terrOffset; // terrain's vertical offset

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
	matrix44* GetPerspMat();
	void UpdateMats();
	void UpdatePerspMat();
	void UpdateSkyMat();
	void UpdateStarfMat();
	void UpdateSunMat();
	void UpdateTerrainMat();

// Daylight
	void UpdateDayFactor();
	void UpdateDayAlpha();

// Colors
	void UpdateColors();
	void SelectColor( color_s c );
	void SelectColor4( color_s c, float a );

// Textures
	BOOL LoadTGA( texture_s& tex, char* filename );
	BOOL LoadTexture( UINT& texID, char* filename );
	BOOL LoadTextures();

// Frustum
	void CalculateFrustum();
	BOOL SphereInFrustum( vector3 v, float radius );


// Destruction
public:
	~CMgrGraphics();
	void Destroy();

};

#endif