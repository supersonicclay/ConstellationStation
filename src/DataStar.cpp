//===========================================================================
// DataStar.h
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
	ra = s.ra;
	dec = s.dec;
	x = s.x; y = s.y; z = s.z;
	phi = s.phi;
	theta = s.theta;
	mat = s.mat;
	mag = s.mag;
	radius = s.radius;
	color = s.color;
	return *this;
}

void CDataStar::Init()
{
	x = 0.0f;
	y = 1.0f;
	z = 0.0f;
	ra.hour = 0;
	ra.minute = 0;
	ra.second = 0.0f;
	dec.positive = TRUE;
	dec.degree = 0;
	dec.minute = 0;
	dec.second = 0.0f;
	phi = 0.0f;
	theta = 0.0f;
	mag = 1.0f;
	radius = 0.0f;
	color = COLOR_WHITE;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

ra_s		CDataStar::GetRA()		{	return ra;		}
dec_s		CDataStar::GetDec()		{	return dec;		}
float		CDataStar::GetX()		{	return x;		}
float		CDataStar::GetY()		{	return y;		}
float		CDataStar::GetZ()		{	return z;		}
float		CDataStar::GetMag()		{	return mag;		}
float		CDataStar::GetRadius()	{	return radius;	}
color_s		CDataStar::GetColor()	{	return color;	}
matrix44*	CDataStar::GetMat()		{	return &mat;	}
float		CDataStar::GetPhi()		{	return phi;		}
float		CDataStar::GetTheta()	{	return theta;	}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataStar::SetRA( ra_s r )			{	ra = r;		}
void CDataStar::SetDec( dec_s d )		{	dec = d;	}
void CDataStar::SetX( float x_ )		{	x = x_;		}
void CDataStar::SetY( float y_ )		{	y = y_;		}
void CDataStar::SetZ( float z_ )		{	z = z_;		}
void CDataStar::SetMag( float m )		{	mag = m;	}
void CDataStar::SetRadius( float r )	{	radius = r;	}
void CDataStar::SetColor( color_s c )	{	color = c;	}

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

//*/// test star color/radius
void CDataStar::SetColorFromMag()
{
	if( mag < 3.5f )
		color.r = color.g = color.b = starfMgr.GetStarsBrightColor();
	else
		color.r = color.g = color.b = starfMgr.GetStarsDimColor();
}

void CDataStar::SetRadiusFromMag()
{
	if( mag < 3.5f )
		radius = starfMgr.GetStarsBrightRadius();
	else
		radius = starfMgr.GetStarsDimRadius();
}
///*/

/*/// old star color/radius
void CDataStar::SetColorFromMag()
{
	if( mag > 2.0f )
	{
		color.r = (8-mag)/7;
		color.g = (8-mag)/7;
		color.b = (8-mag)/7;
	}
	else
	{
		color = COLOR_WHITE;
	}
}

void CDataStar::SetRadiusFromMag()
{
	radius = (8-mag) / 600.0f;
}
///*/

// Set right ascension and Declination from the x, y, and z coordinates
// Phi and theta must already be calculated
void CDataStar::SetRADecFromXYZ()
{
	float hour, minute;

	// Convert phi to declination form
	// At this point:    0 <= phi <= 180.
	// Need it to be:   90 <= deg <= -90. (for declination)
	float deg = 90.0f - phi;
	if( deg < 0.0f ) { dec.positive = FALSE; deg = -deg; }
	minute = (deg - (int)deg)*60;
	dec.second = (minute - (int)minute)*60;
	dec.minute = (int)minute;
	dec.degree = (int)deg;

	// Convert theta to right ascension form
	hour = theta*24/360;
	minute = (hour - (int)hour)*60;
	ra.second = (minute - (int)minute)*60;
	ra.minute = (int)minute;
	ra.hour = (int)hour;
}

// Set the x, y, and z coords from the right ascension and declination
// Phi and theta must already be calculated
void CDataStar::SetXYZFromRADec()
{
	float phiRad = DegToRad(phi);
	float thetaRad = DegToRad(theta);

	x = (float) ( sin(phiRad) * sin(thetaRad) );
	y = (float) ( cos(phiRad) );
	z = (float) ( sin(phiRad) * cos(thetaRad) );
}

// Set spherical coordinate (phi and theta) from the right ascension and declination
void CDataStar::SetPhiThetaFromRADec()
{
	// Calculate phi
	float degrees = dec.degree + (dec.minute+dec.second/60)/60;
	if( dec.positive )
		phi = 90.0f-degrees;
	else
		phi = 90.0f+degrees;

	// Calculate theta
	theta = 360 * (ra.hour+(ra.minute+ra.second/60)/60)/24;
}

// Set spherical coordinates (phi and theta) from the  x, y, and z coordinates
void CDataStar::SetPhiThetaFromXYZ()
{
	// Phi is measured from 0 (north) to 180 (south) degrees
	phi  = (float) acos( (double) y  );
	phi  = RadToDeg(phi);

	// Theta is measured from 0 to 360 degrees
	if( z >= 0 )
		theta = (float)       asin( x / sqrt( (double)(z*z) + (x*x) ) );
	else
		theta = (float) (PI - asin( x / sqrt( (double)(z*z) + (x*x) ) ));
	theta = RadToDeg(theta);
	if( theta < 0 )	theta += 360.0f;	/// Prevent negative theta (necessary?)
}

// Sets the local-to-world matrix based on right ascension and declination
void CDataStar::SetMatFromPhiTheta()
{
	mat.identity();

	mat = RotateRadMatrix44( 'y', DegToRad(theta) );
	mat *= RotateRadMatrix44( 'x', DegToRad(phi) );
	mat *= TranslateMatrix44( 0.0f, 1.0f, 0.0f );
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
	SetPhiThetaFromXYZ();
	SetRADecFromXYZ();
	SetMatFromPhiTheta();
}

// Pick random x, y, and z values such that <x,y,z> is normalized
void CDataStar::PickXYZ()
{
	x = (float)(rand()%2000)/1000-1;	// +1.0 to -1.0

	int chooseYbeforeZ;					// Helps randomize stars
	float absYMax;						// The maximum absolute value of Y based on X
	float absZMax;						// The maximum absolute value of Z based on X
	int plus_minus;						// +1 or -1 (for easier reading)

	chooseYbeforeZ = rand()%2;			// 0 or 1 (T or F)

	if(chooseYbeforeZ)
	{
		absYMax = (float)pow(1.0-(x*x), 0.5);
		if ((int)(absYMax*1000) != 0)
		{
			plus_minus = (rand()%2)*2-1;
			y = plus_minus * (float)(rand()%(int)(absYMax*1000))/1000;
		}
		else
		{
			y = 0.0;
		}
		plus_minus = (rand()%2)*2-1;
		z = plus_minus * (float)pow((1.0-(x * x)-(y * y)), 0.5);
	}
	else //chooseZbeforeY
	{
		absZMax = (float)pow(1.0-(x*x), 0.5);
		if ((int)(absZMax*1000) != 0)
		{
			plus_minus = (rand()%2)*2-1;
			z = plus_minus * (float)(rand()%(int)(absZMax*1000))/1000;
		}
		else
		{
			z = 0.0;
		}
		plus_minus = (rand()%2)*2-1;
		y = plus_minus * (float)pow((1.0-(x * x)-(z * z)), 0.5);
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
	// Magnitude of 3.8 and 13 correspond to
	// -4 and 3 for z-score
	// Pick a random z-score
	float z = (float)(rand()%7000)/100.0f - 4.0f;

///	plug into dist curve
	mag = 3.0f;///

/*/// Old pickmag
	// Pick random number from 0.00 to 100.00
	float random = (float)(rand()%1000)/10;

	// 97% pick mag to be 3 to 6
	if( random < 97.0f )
	{
		mag = (float)(rand()%3000)/1000 + 3.0f;
	}
	// 2.3% pick mag to be 2 to 6
	else if( random < 99.3f )
	{
		mag = (float)(rand()%4000)/1000 + 2.0f;
	}
	// 0.7% pick mag to be 0 to 6
	else
	{
		mag = (float)(rand()%6000)/1000;
	}
*/

	SetColorFromMag();
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
		ar >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> mag >> x >> y >> z
		   >> color
		   >> radius;
	}
	else
	{
		ar << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << mag << x << y << z
		   << color
		   << radius;
	}
}

