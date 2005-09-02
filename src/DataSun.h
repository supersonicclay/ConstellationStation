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
	float altitude;
	float azimuth;

	matrix44 timeMat; /// CHANGE NAME to rotMat or something


// Methods
public:

	color_s GetColor();

	matrix44* GetTimeMat();

	void UpdatePosition( int year, int month, int day, int hour, int minute, int second, float lat, float lon );
	void UpdateTimeMat();

};

#endif

