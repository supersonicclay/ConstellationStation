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
	rotTime = s.rotTime;
	alpha = s.alpha;
	color = s.color;
	timeMat = s.timeMat;
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
	timeMat.identity();
}


/////////////////////////////////////////////////////////////////////////////
// Gets

color_s		CDataSun::GetColor()	{	return color;		}
float		CDataSun::GetRotTime()	{	return rotTime;		}
matrix44*	CDataSun::GetTimeMat()	{	return &timeMat;	}



/////////////////////////////////////////////////////////////////////////////
// Methods

void CDataSun::AdjRotTime( float delta )
{
	rotTime += delta;

	// Keep rotTime between 0 and 2*PI
	if( rotTime < 0.0f )
		rotTime += PI2;
	if( rotTime > PI2 )
        rotTime -= PI2;

	UpdateTimeMat();
}

void CDataSun::UpdateTimeMat()
{
	timeMat.identity();
///	timeMat = RotateRadMatrix44( 'y', rotTime );
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataSun::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	CSDebug( "Shouldn't be serializing a sun", "CDataSun::Serialize" );
	return;

	if( ar.IsLoading() )
	{
		ar >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> mag >> center.x >> center.y >> center.z
		   >> radius
		   >> alpha
		   >> color;
	}
	else
	{
		ar << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << mag << center.x << center.y << center.z
		   << radius
		   << alpha
		   << color;
	}
}

