//===========================================================================
// DataStar.h
//
// CDataStar
//   star data.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
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
	mag = s.mag;
	x = s.x; y = s.y; z = s.z;
	color = s.color;
	radius = s.radius;
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
	mag = 1.0f;
	radius = 0.0f;
	color = COLOR_WHITE;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

float CDataStar::GetMag() const
{
	return mag;
}

color_s CDataStar::GetColor() const
{
	return color;
}

float CDataStar::GetRadius() const
{
	return radius;
}

float CDataStar::GetX() const
{
	return x;
}

float CDataStar::GetY() const
{
	return y;
}

float CDataStar::GetZ() const
{
	return z;
}

// Spherical coordinate theta
float CDataStar::GetTheta() const
{
	float degrees;
	degrees = 360 * (ra.hour+(ra.minute+ra.second/60)/60)/24;
	return degrees;
}

// Spherical coordinate phi
float CDataStar::GetPhi() const
{
	float degrees;

	degrees = dec.degree + (dec.minute+dec.second/60)/60;

	if( dec.positive )
		return 90.0f-degrees;
	else
		return 90.0f+degrees;
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataStar::SetMag( float mag_ )
{
	mag = mag_;
}

void CDataStar::SetColor( color_s color_ )
{
	color = color_;
}

void CDataStar::SetColorFromMag()
{
	if( mag > 2.0f )
	{
		color.r = (6-mag)/5;
		color.g = (6-mag)/5;
		color.b = (6-mag)/5;
	}
	else
	{
		color = COLOR_WHITE;
	}
}

void CDataStar::SetRadiusFromMag()
{
	radius = (6-mag) / 500.0f;///
}

void CDataStar::SetX( float x_ )
{
	x = x_;
}

void CDataStar::SetY( float y_ )
{
	y = y_;
}

void CDataStar::SetZ( float z_ )
{
	z = z_;
}

void CDataStar::SetRA( ra_s ra_ )
{
	ra = ra_;
}

void CDataStar::SetDec( dec_s dec_ )
{
	dec = dec_;
}

void CDataStar::SetRA( unsigned short hour,
				  unsigned short minute,
				  float second )
{
	ra.hour = hour;
	ra.minute = minute;
	ra.second = second;
}

void CDataStar::SetDec( BOOL positive,
				   unsigned short degree,
				   unsigned short minute,
				   float second )
{
	dec.positive = positive;
	dec.degree = degree;
	dec.minute = minute;
	dec.second = second;
}


/////////////////////////////////////////////////////////////////////////////
// Sets

// Set Right Ascension and Declination from the x, y, and z coords.
//   First calculates spherical coordinates for x, y, z.
//   Then converts the coordinates to right ascension, declination form.
void CDataStar::SetRADecFromXYZ()
{
	// Theta is measured from 0 to 360 degrees
	// Phi is measured from 0 (north) to 180 (south) degrees
	float theta, phi;
	float hour, minute;


	// Right Ascension
	if( z >= 0 )
		theta = (float) asin( (double) (x / sqrt((double)(z*z) + (x*x))) );
	else
		theta = (float) (PI - asin( (double)(x / sqrt((double)(z*z) + (x*x))) ));
	theta = theta * (float) (180 / PI);	// Convert from radians to degrees
	if( theta < 0 )	theta += 360.0f;	// Prevent negative theta

	// Convert to right ascension form
	hour = theta*24/360;
	minute = (hour - (int)hour)*60;
	ra.second = (minute - (int)minute)*60;
	ra.minute = (int)minute;
	ra.hour = (int)hour;


	// Declination
	phi  = (float) acos( (double) y  );
	phi  = phi  * (float) (180 / PI);	// Convert from radians to degrees

	// At this point 0 <= phi <= 180.
	// Needs to be  90 <= phi <= -90. (for declination)
	phi = 90.0f - phi;

	// Store phi's sign
	dec.positive = phi >= 0.0f;
	// Take absolute value
	if( phi < 0.0f )   phi = -phi;
	// Convert to declination form
	minute = (phi - (int)phi)*60;
	dec.second = (minute - (int)minute)*60;
	dec.minute = (int)minute;
	dec.degree = (int)phi;
}

// Set the x, y, and z coords from the right ascension and declination
//   First converts right ascension and declination to spherical coordinates
//   Then calculates x, y, and z from those coordinates
void CDataStar::SetXYZFromRADec()
{
	double theta = (double)GetTheta();
	double phi = (double)GetPhi();

	// Convert to radians
	theta *= PI / 180;
	phi *= PI / 180;

	x = (float) (sin(phi)*sin(theta));
	y = (float) (cos(phi));
	z = (float) (sin(phi)*cos(theta));
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
	SetRADecFromXYZ();
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
void CDataStar::PickMag()
{
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

	SetColorFromMag();
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataStar::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if( ar.IsLoading() )
	{
		ar >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> mag >> x >> y >> z
		   >> color.r >> color.g >> color.b
		   >> radius;
	}
	else
	{
		ar << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << mag << x << y << z
		   << color.r << color.g << color.b
		   << radius;
	}
}


