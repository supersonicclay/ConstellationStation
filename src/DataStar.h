//===========================================================================
// DataStar.h
//
// CDataStar
//   star data.
//===========================================================================

#ifndef CS_DATASTAR_H
#define CS_DATASTAR_H

#include "Matrix.h"

class CDataStar : public CObject
{
DECLARE_SERIAL( CDataStar )

// Construction / Destruction
public:
	CDataStar();
	CDataStar( const CDataStar& s );
	~CDataStar();

	void Init();

	const CDataStar& operator=( const CDataStar& s );
	void Serialize( CArchive& ar );


// Attributes
private:
	// Position
	matrix44 mat;
	ra_s ra;
	dec_s dec;
	float phi;
	float theta;
	float x, y, z;

	// Appearance
	float mag;
	color_s color;
	float radius;


// Methods
public:

// Gets
	ra_s GetRA();
	dec_s GetDec();
	float GetMag();
	color_s GetColor();
	float GetRadius();
	float GetX();
	float GetY();
	float GetZ();
	float GetPhi();
	float GetTheta();
	matrix44* GetMat();

// Sets
	void SetMag( float m );
	void SetColor( color_s c );
	void SetRadius( float r );
	void SetX( float x_ );
	void SetY( float y_ );
	void SetZ( float z_ );
	void SetRA( ra_s r );
	void SetDec( dec_s d );
	void SetRA( USHORT h, USHORT m, float s );
	void SetDec( BOOL p, USHORT d, USHORT m, float s );


// Methods
	void SetColorFromMag();
	void SetRadiusFromMag();
	void SetRADecFromXYZ();
	void SetXYZFromRADec();
	void SetPhiThetaFromRADec();
	void SetPhiThetaFromXYZ();
	void SetMatFromPhiTheta();

	void Randomize();
	void PickXYZ();
	void PickLocation();
	void PickMag();
};

// CDataStar vector
typedef std::vector<CDataStar> star_v;
typedef star_v::iterator star_vi;

#endif

