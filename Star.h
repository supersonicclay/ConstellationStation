// Star.h : interface of the CStar class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STAR_H
#define STAR_H

class CStar : public CObject
{
DECLARE_SERIAL (CStar)

public:
	CStar ();
	CStar (float x_, float y_, float z_, float brightness_=1);
	~CStar();

	void Serialize (CArchive& ar);

private:
	float x, y, z;
	float brightness;
	CColor color;

public:

	float GetX(), GetY(), GetZ();
	float GetBrightness();
	CColor GetColor();

	void SetX (float x_);
	void SetY (float y_);
	void SetZ (float z_);
	void SetBrightness (float brightness_);
	void SetColor (CColor color_);

	void Randomize();
	void PickXYZ();
	void PickBrightness();

};

#endif

