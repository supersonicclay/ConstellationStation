#ifndef STARFIELD_H
#define STARFIELD_H

//#include <windows.h>
/*
#include <gl/gl.h>									// Header File For The OpenGL32 Library
#include <gl/glu.h>									// Header File For The GLu32 Library
#include <gl/glaux.h>								// Header File For The GLaux Library
*/
//#include "UI.h"

typedef struct
{
	float x;
	float y;
	float z;
} starPoint;

class Star : public GUIElement
{
private:
	float x, y, z;
	float r, g, b;
	float brightness;
	COLOR color;
public:
	Star ();
	Star (float x_, float y_, float z_, float brightness_=0.0f);
	~Star();

	float GetX(), GetY(), GetZ();
	float GetBrightness();
	COLOR GetColor();

	void SetX (float x_);
	void SetY (float y_);
	void SetZ (float z_);
	void SetColor (COLOR c);
	void SetColor (float r, float g, float b);
	void SetBrightness (float brightness_);

	void PickXYZ();

	void Draw() const;
};

class Constellation : public GUIElement
{
private:
	
public:
	Constellation();
	~Constellation();

	void Draw() const;

};

class Starfield : public GUIElement
{
private:
	Star *star;
	Constellation *constellation;

	int NUMSTARS;

	float zoom;
	float rotX, rotY;

	Star* starMouseOver;

public:
	Starfield();
	~Starfield();

	Star* GetStar(GLuint x) const;
	float GetZoom() const;
	float GetRotX() const;
	float GetRotY() const;
	Star* GetStarMouseOver() const;

	void SetRotX(float rotX_);
	void SetRotY(float rotY_);
	void SetStarMouseOver(Star* s);

	void ResetView  ();
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn ();
	void ZoomOut();

	void SetupStars();

	void Load();	// Returns NUMSTARS
	void ReadLine(FILE *f,char *string) const;
	void Save();	//// should be const

	void Draw() const;
};


#endif