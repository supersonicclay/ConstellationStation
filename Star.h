// Star.h : interface of the CStar class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STAR_H
#define STAR_H

class CStar
{
private:
	float x, y, z;
	float brightness;
	CColor color;
	CColor origColor;

public:
	CStar ();
	CStar (float x_, float y_, float z_, float brightness_=1);
	~CStar();

	float GetX(), GetY(), GetZ();
	float GetBrightness();
	CColor GetColor();

	void SetX (float x_);
	void SetY (float y_);
	void SetZ (float z_);
	void SetBrightness (float brightness_);
	void SetColor (CColor color_);
	void SetOrigColor (CColor origColor_);
	void RestoreColor ();

	void Randomize();
	void PickXYZ();
	void PickBrightness();

};

#endif

