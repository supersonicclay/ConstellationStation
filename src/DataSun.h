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
	float rotTime;


// Methods
public:

	float   GetRotTime();

	void AdjRotTime( float delta );

};

#endif

