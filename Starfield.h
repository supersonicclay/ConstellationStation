// Starfield.h : header file for CStarfield, CStar, and CConstellation
//

#ifndef STARFIELD_H
#define STARFIELD_H

/////////////////////////////////////////////////////////////////////////////
// CCStar class
class CStar : public CObject
{
private:
	float x, y, z;
////float r, g, b;
	float brightness;
public:
	CStar ();
	CStar (float x_, float y_, float z_, float brightness_=0.0f);
	~CStar();

	float GetX(), GetY(), GetZ();
	float GetBrightness();
////CColor GetColor();

	void SetX (float x_);
	void SetY (float y_);
	void SetZ (float z_);
////void SetColor (CColor c);
////void SetColor (float r, float g, float b);
	void SetBrightness (float brightness_);

	void Randomize();

////void Draw() const;
};


/////////////////////////////////////////////////////////////////////////////
// CCConstellation class
class CConstellation : public CObject
{
private:
	
public:
	CConstellation();
	~CConstellation();

	void Draw() const;

};


/////////////////////////////////////////////////////////////////////////////
// CCStarfield class
class CStarfield : public CObject
{
private:
	CStar *stars;
	CConstellation *constellations;

	int numStars;

////CStar* starMouseOver;

public:
	CStarfield();
	~CStarfield();

	void SetupStars();

	CStar* GetStar(int i) const;
	int GetNumStars() const;

/*
	float GetZoom() const;
	float GetRotX() const;
	float GetRotY() const;
////CStar* GetStarMouseOver() const;

	void SetRotX(float rotX_);
	void SetRotY(float rotY_);
////void SetStarMouseOver(CStar* s);

	void ResetView  ();
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn ();
	void ZoomOut();
*/


////void Draw() const;
};

#endif