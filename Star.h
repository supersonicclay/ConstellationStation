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

	void Randomize();
	void PickXYZ();
	void PickLocation();
	void PickMag();

	void Serialize( CArchive& ar );

private:
	ra_s ra;
	dec_s dec;
	float mag;
	float x, y, z;
	color_s color;
	float radius;

public:

	float GetMag() const;
	color_s GetColor() const;
	float GetRadius() const;
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetTheta() const;
	float GetPhi() const;

	void SetMag( float mag_ );
	void SetColor( color_s color_ );
	void SetColorFromMag();
	void SetRadiusFromMag();
	void SetX( float x_ );
	void SetY( float y_ );
	void SetZ( float z_ );
	void SetRA( ra_s ra_ );
	void SetDec( dec_s dec_ );
	void SetRA( unsigned short hour,
				unsigned short minute,
				float second );
	void SetDec( bool positive,
				 unsigned short degree,
				 unsigned short minute,
				 float second );
	void SetRADecFromXYZ();
	void SetXYZFromRADec();
};

#endif

