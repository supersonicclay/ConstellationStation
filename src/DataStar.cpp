//===========================================================================
// DataStar.cpp
//
// CDataStar
//   star data.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataStar.h"

IMPLEMENT_SERIAL( CDataStar, CObject, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataStar::CDataStar()
{
	Init();
}

CDataStar::CDataStar( const CDataStar& s )
{
	*this = s;
}

CDataStar::~CDataStar()
{
}

const CDataStar& CDataStar::operator=( const CDataStar& s )
{
	name = s.name;
	hid = s.hid;
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
	alpha = s.alpha;
	spectral = s.spectral;
	return *this;
}

void CDataStar::Init()
{
	name = "";
	hid = -1;
	ra.hour = 0;
	ra.minute = 0;
	ra.second = 0.0f;
	dec.positive = TRUE;
	dec.degree = 0;
	dec.minute = 0;
	dec.second = 0.0f;
	phi = 0.0f;
	theta = 0.0f;
	center = vector3( 0.0f, 0.0f, 0.0f );
	trVert = vector3( 0.0f, 0.0f, 0.0f );
	tlVert = vector3( 0.0f, 0.0f, 0.0f );
	blVert = vector3( 0.0f, 0.0f, 0.0f );
	brVert = vector3( 0.0f, 0.0f, 0.0f );
	mag = 10.0f; // Make dim so it won't ever be seen
	radius = 0.0f;
	alpha = 1.0f;
	spectral = 'A';
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CString		CDataStar::GetName()		{	return name;		}
int			CDataStar::GetHID()			{	return hid;			}
ra_s		CDataStar::GetRA()			{	return ra;			}
dec_s		CDataStar::GetDec()			{	return dec;			}
float		CDataStar::GetPhi()			{	return phi;			}
float		CDataStar::GetTheta()		{	return theta;		}
vector3		CDataStar::GetCenter()		{	return center;		}
vector3		CDataStar::GetTRVert()		{	return trVert;		}
vector3		CDataStar::GetTLVert()		{	return tlVert;		}
vector3		CDataStar::GetBLVert()		{	return blVert;		}
vector3		CDataStar::GetBRVert()		{	return brVert;		}
float		CDataStar::GetMag()			{	return mag;			}
float		CDataStar::GetRadius()		{	return radius;		}
float		CDataStar::GetAlpha()		{	return alpha;		}
char		CDataStar::GetSpectral()	{	return spectral;	}

color_s		CDataStar::GetColor()
{
	color_s c = COLOR_WHITE*alpha;
	if( !optionsMgr.AreStarsColored() )
		return c;
	else
	{
//obafgkm
		if( spectral == 'O' )
			return c*DEF_STARS_SPECTRAL_O_COLOR;
		if( spectral == 'B' )
			return c*DEF_STARS_SPECTRAL_B_COLOR;
		if( spectral == 'A' )
			return c*DEF_STARS_SPECTRAL_A_COLOR;
		if( spectral == 'F' )
			return c*DEF_STARS_SPECTRAL_F_COLOR;
		if( spectral == 'G' )
			return c*DEF_STARS_SPECTRAL_G_COLOR;
		if( spectral == 'K' )
			return c*DEF_STARS_SPECTRAL_K_COLOR;
		if( spectral == 'M' )
			return c*DEF_STARS_SPECTRAL_M_COLOR;
		if( spectral == 'C' || spectral == 'N' || spectral == 'S' || spectral == 'W' || spectral == 'D' )///
			return c;

		CSDebug( CString("Bad spectral type: ") + spectral, "CDataStar::GetColor" );
		PostQuitMessage(1);
		return COLOR_WHITE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataStar::SetName( CString n )	{	name = n;		}
void CDataStar::SetHID( int h )			{	hid = h;		}
void CDataStar::SetRA( ra_s r )			{	ra = r;			}
void CDataStar::SetDec( dec_s d )		{	dec = d;		}
void CDataStar::SetCenter( vector3 c )	{	center = c;		}
void CDataStar::SetPhi( float p )		{	phi = p;		}
void CDataStar::SetTheta( float t )		{	theta = t;		}
void CDataStar::SetMag( float m )		{	mag = m;		}
void CDataStar::SetRadius( float r )	{	radius = r;		}
void CDataStar::SetAlpha( float a )		{	alpha = a;		}
void CDataStar::SetSpectral( char s )	{	spectral = s;	}

void CDataStar::SetRA( USHORT h, USHORT m, float s )
{
	ra.hour = h;
	ra.minute = m;
	ra.second = s;
}

void CDataStar::SetDec( BOOL p, USHORT d, USHORT m, float s )
{
	dec.positive = p;
	dec.degree = d;
	dec.minute = m;
	dec.second = s;
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Update all position info from the right ascension and declination that are already set
void CDataStar::UpdatePosFromRADec()
{
	SetPhiThetaFromRADec();
	SetXYZFromPhiTheta();
}

// Update all position info from the x, y, and z coordinates that are already set
void CDataStar::UpdatePosFromXYZ()
{
	SetPhiThetaFromXYZ();
	SetRADecFromPhiTheta();
}

// Set the x, y, and z coords from the right ascension and declination
// Phi and theta must already be calculated
void CDataStar::SetXYZFromPhiTheta()
{
	center.x = (float) ( sin(phi) * sin(theta) );
	center.y = (float) ( cos(phi) );
	center.z = (float) ( sin(phi) * cos(theta) );
}

// Set spherical coordinate (phi and theta) from the right ascension and declination
void CDataStar::SetPhiThetaFromRADec()
{
	// Calculate phi
	float radians = DegToRad( dec.degree + (dec.minute+dec.second/60)/60 );
	if( dec.positive )
		phi = PIHALF-radians;
	else
		phi = PIHALF+radians;

	// Calculate theta
	theta = PI2 * (ra.hour+(ra.minute+ra.second/60)/60)/24;
}

// Set right ascension and Declination from the x, y, and z coordinates
// Phi and theta must already be calculated
void CDataStar::SetRADecFromPhiTheta()
{
	float hour, minute;

	// Convert phi to declination form
	// At this point:    0 <= phi <= PI.
	// Need it to be:   90 <= deg <= -90. (for declination)
	float degrees = 90.0f - RadToDeg(phi);
	if( degrees < 0.0f ) { dec.positive = FALSE; degrees = -degrees; }
	minute = (degrees - (int)degrees)*60;
	dec.second = (minute - (int)minute)*60;
	dec.minute = (int)minute;
	dec.degree = (int)degrees;

	// Convert theta to right ascension form
	hour = theta*12/PI;
	minute = (hour - (int)hour)*60;
	ra.second = (minute - (int)minute)*60;
	ra.minute = (int)minute;
	ra.hour = (int)hour;
}

// Set spherical coordinates (phi and theta) from the  x, y, and z coordinates
void CDataStar::SetPhiThetaFromXYZ()
{
	// Phi is measured from 0 (north) to PI (south)
	phi  = (float) acos( (double) center.y  );

	// Theta is measured from 0 to 2*PI degrees
	if( center.z == 0.0f && center.x == 0.0f )  // Prevent divide by 0
	{
		theta = 0.0f;
		return;
	}
	if( center.z >= 0 )
		theta = (float)       asin( center.x / sqrt( (double)(center.z*center.z) + (center.x*center.x) ) );
	else
		theta = (float) (PI - asin( center.x / sqrt( (double)(center.z*center.z) + (center.x*center.x) ) ));

	if( theta < 0.0f )	theta += 2*PI;	// Prevent negative theta
}

// Sets the quad vertices based on spherical coordinates, phi and theta
void CDataStar::UpdateVerts()
{
	matrix44 mat;
	mat.identity();

	// Initialize local-to-world matrix
	mat = RotateRadMatrix44( 'y', theta );
	mat *= RotateRadMatrix44( 'x', phi );
	mat *= TranslateMatrix44( 0.0f, 1.0f, 0.0f );

	// Calculate vertices
	trVert = mat*vector3(  radius, 0.0f,  radius );
	tlVert = mat*vector3( -radius, 0.0f,  radius );
	blVert = mat*vector3( -radius, 0.0f, -radius );
	brVert = mat*vector3(  radius, 0.0f, -radius );
}

// Pick random x then a random y and z so that x,y,z has length of 1
//   and pick random brightess with higher chance of being dim
void CDataStar::Randomize()
{
	PickLocation();
	PickMag();
}

// Pick a random location in the sky
void CDataStar::PickLocation()
{
	PickXYZ();
	UpdatePosFromXYZ();
}

// Pick random x, y, and z values such that <x,y,z> is normalized
void CDataStar::PickXYZ()
{
	center.x = (float)(rand()%2000)/1000-1;	// +1.0 to -1.0

	int chooseYbeforeZ;					// Helps randomize stars
	float absYMax;						// The maximum absolute value of Y based on X
	float absZMax;						// The maximum absolute value of Z based on X
	int plus_minus;						// +1 or -1 (for easier reading)

	chooseYbeforeZ = rand()%2;			// 0 or 1 (T or F)

	if(chooseYbeforeZ)
	{
		absYMax = (float)pow(1.0-(center.x*center.x), 0.5);
		if ((int)(absYMax*1000) != 0)
		{
			plus_minus = (rand()%2)*2-1;
			center.y = plus_minus * (float)(rand()%(int)(absYMax*1000))/1000;
		}
		else
		{
			center.y = 0.0;
		}
		plus_minus = (rand()%2)*2-1;
		center.z = plus_minus * (float)pow((1.0-(center.x * center.x)-(center.y * center.y)), 0.5);
	}
	else //chooseZbeforeY
	{
		absZMax = (float)pow(1.0-(center.x*center.x), 0.5);
		if ((int)(absZMax*1000) != 0)
		{
			plus_minus = (rand()%2)*2-1;
			center.z = plus_minus * (float)(rand()%(int)(absZMax*1000))/1000;
		}
		else
		{
			center.z = 0.0;
		}
		plus_minus = (rand()%2)*2-1;
		center.y = plus_minus * (float)pow((1.0-(center.x * center.x)-(center.z * center.z)), 0.5);
	}
}

// Pick a random magnitude
// Distribution of star magnitudes
//  is approximately normal (slight skewed to left) with
//
// Mean = 9
// St. Dev = 1.3
//
// PickMag picks a random magnitude between 3.8 and 13
//  such that the distribution will be approximately normal.
void CDataStar::PickMag()
{
	// Pick random percent from 0.00 to 100.00
	float percent = (float)(rand()%1000)/10;

	// 50.53% between 8 and 9
	if( percent < 50.53f )
		mag = (rand()%100)/100.0f + 8.0f;

	// 30.91% between 7 and 8
	else if( percent < 50.53f + 30.91f )
	{
		mag = (rand()%100)/100.0f + 7.0f;
	}

	// 12.54% between 6 and 7
	else if( percent < 50.53f + 30.91f + 12.54f )
	{
		mag = (rand()%100)/100.0f + 6.0f;
	}

	// 04.08% between 5 and 6
	else if( percent < 50.53f + 30.91f + 12.54f + 04.08f )
	{
		mag = (rand()%100)/100.0f + 5.0f;
	}
	
	// 01.32% between 4 and 5
	else if( percent < 50.53f + 30.91f + 12.54f + 04.08f + 01.32f )
	{
		mag = (rand()%100)/100.0f + 4.0f;
	}
	
	// 00.41% between 3 and 4
	else if( percent < 50.53f + 30.91f + 12.54f + 04.08f + 01.32f + 00.41f )
	{
		mag = (rand()%100)/100.0f + 3.0f;
	}
	
	// 00.15% between 2 and 3
	else if( percent < 50.53f + 30.91f + 12.54f + 04.08f + 01.32f + 00.41f + 00.15f )
	{
		mag = (rand()%100)/100.0f + 2.0f;
	}
	
	// 00.04% between 1 and 2
	else if( percent < 50.53f + 30.91f + 12.54f + 04.08f + 01.32f + 00.41f + 00.15f + 00.04f )
	{
		mag = (rand()%100)/100.0f + 1.0f;
	}
	
	// 00.02% between 0 and 1
	else
	{
		mag = (rand()%100)/100.0f + 0.0f;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataStar::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	CSDebug( "Shouldn't be serializing a star", "CDataStar::Serialize" );
	return;

	if( ar.IsLoading() )
	{
		ar >> name >> hid
		   >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> mag >> center.x >> center.y >> center.z
		   >> radius
		   >> alpha;
	}
	else
	{
		ar << name << hid
		   << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << mag << center.x << center.y << center.z
		   << radius
		   << alpha;
	}
}

