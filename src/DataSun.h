//===========================================================================
// DataSun.h
//
// CDataSun
//   sun data.
//===========================================================================

#ifndef CS_DATASUN_H
#define CS_DATASUN_H

#include "DataStar.h"
#include "Matrix.h"

class CDataSun : public CDataStar
{
DECLARE_SERIAL( CDataSun )

// Construction / Destruction
public:
	CDataSun();
	CDataSun( const CDataSun& s );
	~CDataSun();

	void Init();

	const CDataSun& operator=( const CDataSun& s );
	void Serialize( CArchive& ar );


// Attributes
private:

	color_s color;

	matrix44 sunMat;


// Methods
public:

	color_s GetColor();

	matrix44* GetSunMat();

	void UpdateSunMat();

	// Sun altitude/azimuth calculator from
	// http://www.jgiesen.de/astro/astroJS/SunPositionCalculator.htm
	void UpdateAltitude( int y, int m, int d, int h, int n, int s, float lat, float lon );
	void UpdateAzimuth( int y, int m, int d, int h, int n, int s, float lat, float lon );
	void UpdatePosition( COleDateTime& ut, float lat, float lon );

};

#endif

