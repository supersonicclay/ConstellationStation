//===========================================================================
// MgrGraphics.h
//
// CMgrGraphics
//   handles all OpenGL graphics.
//===========================================================================

#ifndef CS_MGRGRAPHICS_H
#define CS_MGRGRAPHICS_H


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

	// Textures
	UINT starTex;
	UINT skyTex;

	// Sky
	GLUquadricObj* skySphere;

	// Sun
	GLUquadricObj* sunSphere;
	float sunPos[3];


// Operations
public:

	// Initialization
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat();

	// Drawing functions
	void Draw();
	void DrawTerrain() const;
	void PositionTerrain() const;
	void DrawSky() const;
	void DrawSun() const;
	void DrawStars() const;
	void DrawStar (int i) const;
	void DrawConstellations() const;
	void DrawConstellation (int i) const;
	void DrawCompass() const;

	// View manipulation
	void Projection  () const;
	void Perspective () const;
	void RotateXY() const;
	void RotateLatitude() const;
	void RotateTime() const;

	// Textures
	BOOL LoadTGA( UINT &texID, char* filename );
	BOOL LoadTextures();

	// Colors
	void SetColor( color_s c ) const;

	// Frustum
	void CalculateFrustum();
	BOOL SphereInFrustum( float x, float y, float z, float radius ) const;

	void Destroy();
	void Paint();
	void Size( int cx, int cy );


// Destruction
public:
	~CMgrGraphics();

};

#endif