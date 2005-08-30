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
protected:

	// Common name
	CString name;

	// Hipparcos id
	int hid;

	// Position
	ra_s ra;
	dec_s dec;
	float phi;
	float theta;
	float altitude;
	float azimuth;
	vector3 center;
	vector3 trVert;
	vector3 tlVert;
	vector3 blVert;
	vector3 brVert;

	// Appearance
	float mag;
	float radius;
	float alpha;
	char spectral;


// Methods
public:

// Gets
	CString GetName();
	int GetHID();
	ra_s GetRA();
	dec_s GetDec();
	float GetPhi();
	float GetTheta();
	vector3 GetCenter();
	vector3 GetNormal();
	vector3 GetTRVert();
	vector3 GetTLVert();
	vector3 GetBLVert();
	vector3 GetBRVert();
	float GetMag();
	float GetRadius();
	float GetAlpha();
	color_s GetColor();
	char GetSpectral();

// Sets
	void SetName( CString n );
	void SetHID( int h );
	void SetRA( ra_s r );
	void SetDec( dec_s d );
	void SetRA( USHORT h, USHORT m, float s );
	void SetDec( BOOL p, USHORT d, USHORT m, float s );
	void SetCenter( vector3 c );
	void SetPhi( float p );
	void SetTheta( float t );
	void SetMag( float m );
	void SetRadius( float r );
	void SetAlpha( float a );
	void SetSpectral( char s );

// Methods
	// Right ascension and declination known
	void UpdatePosFromRADec();
	void SetPhiThetaFromRADec();
	void SetXYZFromPhiTheta();

	// X, Y, and Z coordinates known
	void UpdatePosFromXYZ();
	void SetPhiThetaFromXYZ();
	void SetRADecFromPhiTheta();

	// Phi and theta known
	void UpdatePosFromPhiTheta();

	void UpdateVerts();

	void Randomize();
	void PickXYZ();
	void PickLocation();
	void PickMag();

};

// CDataStar vector
typedef std::vector<CDataStar> star_v;
typedef star_v::iterator star_vi;

#endif

