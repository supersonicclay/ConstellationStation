//===========================================================================
// DataSun.cpp
//
// CDataSun
//   star data.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataSun.h"

IMPLEMENT_SERIAL( CDataSun, CDataStar, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataSun::CDataSun()
{
	Init();
}

CDataSun::CDataSun( const CDataSun& s )
{
	*this = s;
}

CDataSun::~CDataSun()
{
}

const CDataSun& CDataSun::operator=( const CDataSun& s )
{
	ra = s.ra;
	dec = s.dec;
	phi = s.phi;
	theta = s.theta;
	center = s.center;
	trVert = s.trVert;
	tlVert = s.tlVert;
	blVert = s.blVert;
	brVert = s.brVert;
	mag = s.mag;
	radius = s.radius;
	color = s.color;
	return *this;
}

void CDataSun::Init()
{
	ra.hour = 12;
	ra.minute = 0;
	ra.second = 0.0f;
	dec.positive = TRUE;
	dec.degree = 0;
	dec.minute = 0;
	dec.second = 0.0f;

	radius = DEF_SUN_RADIUS;
	color = DEF_SUN_COLOR;

	UpdatePosFromRADec();
	UpdateVerts();

	rotTime = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

float   CDataSun::GetRotTime()	{	return rotTime;		}


/////////////////////////////////////////////////////////////////////////////
// Methods

void CDataSun::AdjRotTime( float delta )
{
	rotTime += delta;
	if( rotTime > 360.0f )
        rotTime -= 360.0f;
	else if( rotTime < -360.0f )
		rotTime += 360.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataSun::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	CSDebug( "Shouldn't be serializing a star", "CDataSun::Serialize" );
	return;

	if( ar.IsLoading() )
	{
		ar >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> mag >> center.x >> center.y >> center.z
		   >> color
		   >> radius;
	}
	else
	{
		ar << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << mag << center.x << center.y << center.z
		   << color
		   << radius;
	}
}

