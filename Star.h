// Star.h : interface of the CStar class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STAR_H
#define STAR_H

class CStar : public CObject
{
DECLARE_SERIAL( CStar )

public:
	CStar ();
	~CStar();

	void Serialize( CArchive& ar );

private:
	float x, y, z;
	float longitude;
	float latitude;
	float brightness;
	color_t color;

public:

	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetLongitude() const;
	float GetLatitude() const;
	float GetBrightness() const;
	color_t GetColor() const;

	void SetX( float x_ );
	void SetY( float y_ );
	void SetZ( float z_ );
	void SetLongitude( float longitude_ );
	void SetLatitude( float latitude_ );
	void SetBrightness( float brightness_ );
	void SetColor( color_t color_ );

	void Randomize();
	void PickXYZ();
	void PickDirection();
	void PickBrightness();
	void PickColor();

};

#endif

