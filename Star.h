// Star.h : interface of the CStar class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STAR_H
#define STAR_H

class CStar
{
private:
	float x, y, z;
	int brightness;
	CColor color;
public:
	CStar ();
	CStar (float x_, float y_, float z_, int brightness_=1);
	~CStar();

	float GetX(), GetY(), GetZ();
	int GetBrightness();
	CColor GetColor();

	void SetX (float x_);
	void SetY (float y_);
	void SetZ (float z_);
	void SetColor (CColor c);
	void SetBrightness (int brightness_);

	void Randomize();

};

#endif

