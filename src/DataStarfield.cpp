//===========================================================================
// DataStarfield.cpp
//
// CDataStarfield
//   starfield data.
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain options. A CDataStarfield and 
//   everything in a CDataStarfield can be saved and opened.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataStarfield.h"

#include "DataStar.h"
#include "DataConst.h"

IMPLEMENT_SERIAL( CDataStarfield, CObject, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataStarfield::CDataStarfield()
{
	Clear();
}

CDataStarfield::~CDataStarfield()
{
}

void CDataStarfield::Clear()
{
	modified = FALSE;

	numStars = 0;
	numConstellations = 0;
	numNewConstellations = 0;
	numCurConstellation = 0;

	stars.clear();
	constellations.clear();

	rotX = 0.0f;
	rotY = 0.0f;
	zoom = 0.0f;
	spinning = FALSE;

	LoadStarDefaults();
	LoadConstDefaults();
	LoadSunDefaults();

	// Time
	time_t seconds = time(NULL);
	gregorian = *(localtime( &seconds ));
	gregorian.tm_year += 1900;
///	julian = 
	rotTime = 0.0f;

	// Latitude & Longitude
	rotLatitude = 50.0f;
}

void CDataStarfield::New( BOOL actual )
{
	Clear();

	if( actual )
	{
		InitActualStars();
		InitActualConstellations();
	}
	else
	{
		InitRandomStars();
	}
}

// Creates sphere of random stars with radius of 1
void CDataStarfield::InitRandomStars()
{
	numStars = 8000;
	CDataStar newStar;

	/* /// North Star
	newStar.SetColor( COLOR_NORTHSTAR );
	newStar.SetMag( 2.0f );
	newStar.SetRA( 0, 0, 0.0f );
	newStar.SetDec( 90, 0, 0.0f );
	newStar.SetX( 0.0f );
	newStar.SetY( 1.0f );
	newStar.SetZ( 0.0f );
	stars.push_back( CDataStar(newStar) );
	*/

	// Sun Corona
	newStar.SetColor( COLOR_WHITE );
	newStar.SetMag( 60.0f );
	newStar.SetRA( 12, 0, 0.0f );
	newStar.SetDec( TRUE, 0, 0, 0.0f );
	newStar.SetX( 0.0f );
	newStar.SetY( 0.0f );
	newStar.SetZ(-1.0f );
	stars.push_back( CDataStar(newStar) );

	// Randomize the rest
	for (int i=1; i<numStars; i++)
	{
		newStar.Randomize();
		stars.push_back( CDataStar(newStar) );
	}
}

// Load the actual stars from the magnitude-sorted hipparcos catalog
void CDataStarfield::InitActualStars()
{
	CDataStar newStar;

	numStars = MAX_STARS;///
	stars.reserve( numStars );

	CFile file( "data\\hip_main.txt", CFile::modeRead );

	char buffer[100];
	ra_s ra = {0};
	dec_s dec = {0};
	float mag = 0;

	for( int i=0; i<numStars; ++i )
	{
		file.Seek( 17, CFile::current );
		ZeroMemory(&buffer, sizeof(buffer));

		// Right Ascension
		file.Read( buffer, 2 );
		ra.hour = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 2 );
		ra.minute = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 5 );
		ra.second = (float) atof( buffer );

		file.Seek( 1, CFile::current );
		ZeroMemory(&buffer, sizeof(buffer));

		// Declination
		file.Read( buffer, 1 );
		dec.positive = buffer[0] == '+';

		file.Read( buffer, 2 );
		dec.degree = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 2 );
		dec.minute = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 4 );
		dec.second = (float) atof( buffer);

		file.Seek( 1, CFile::current );
		ZeroMemory(&buffer, sizeof(buffer));

		// Magnitude
		file.Read( buffer, 5 );
		mag = (float) atof( buffer );

		// Ignore rest of line
		file.Seek( 406, CFile::current );

		newStar.SetRA( ra );
		newStar.SetDec( dec );
		newStar.SetXYZFromRADec();
		newStar.SetMag( mag );
		newStar.SetColorFromMag();
		newStar.SetRadiusFromMag();

		stars.push_back( CDataStar(newStar) );
	}

	file.Close();

}

/// Load actual constellations somehow
void CDataStarfield::InitActualConstellations()
{
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CDataStar*	CDataStarfield::GetStar(int i)				{	return &stars[i];								}
int			CDataStarfield::GetNumStars()				{	return numStars;								}
CDataConst*	CDataStarfield::GetConstellation(int i)		{	return &constellations[i];						}
CDataConst*	CDataStarfield::GetCurConstellation()		{	return &constellations[numCurConstellation];	}
int			CDataStarfield::GetNumConstellations()		{	return numConstellations;						}
int			CDataStarfield::GetNumCurConstellation()	{	return numCurConstellation;						}
int			CDataStarfield::GetNumNewConstellations()	{	return numNewConstellations;					}
BOOL		CDataStarfield::AreStarsVisible()			{	return starsVisible;							}
BOOL		CDataStarfield::AreStarsLabeled()			{	return starsLabeled;							}
float		CDataStarfield::GetLimitingMag()			{	return limitingMag;								}
///float		CDataStarfield::GetLimitingMag()			{	return limitingMagX10 / 10.0f;					}
///int			CDataStarfield::GetLimitingMagX10()			{	return limitingMagX10;							}
BOOL		CDataStarfield::AreConstsVisible()			{	return constsVisible;							}
BOOL		CDataStarfield::AreConstsLabeled()			{	return constsLabeled;							}
BOOL		CDataStarfield::IsSunVisible()				{	return sunVisible;								}
BOOL		CDataStarfield::IsSunShining()				{	return sunShine;								}
BOOL		CDataStarfield::IsModified()				{	return modified;								}
float		CDataStarfield::GetRotLatitude()			{	return rotLatitude;								}
float		CDataStarfield::GetRotTime()				{	return rotTime;									}
BOOL		CDataStarfield::IsSpinning()				{	return spinning;								}
float		CDataStarfield::GetRotX()					{	return rotX;									}
float		CDataStarfield::GetRotY()					{	return rotY;									}
float		CDataStarfield::GetZoom()					{	return zoom;									}

// Find the constellation with the given name
CDataConst*	CDataStarfield::GetConstellation( CString& name )
{
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
			return &constellations[i];
	}
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataStarfield::IncNumNewConstellations()				{	numNewConstellations++;			}
void CDataStarfield::SetNumCurConstellation( int i )		{	numCurConstellation = i;		}
void CDataStarfield::SwitchStarsVisible()					{	starsVisible = !starsVisible;	}
void CDataStarfield::SetStarsVisible( BOOL x )				{	starsVisible = x;				}
void CDataStarfield::SwitchStarsLabeled()					{	starsLabeled = !starsLabeled;	}
void CDataStarfield::SetStarsLabeled( BOOL x )				{	starsLabeled = x;				}
void CDataStarfield::SetLimitingMag( float m )				{	limitingMag = m;				}
///void CDataStarfield::SetLimitingMagX10( int x )
void CDataStarfield::SwitchConstsVisible()					{	constsVisible = !constsVisible;	}
void CDataStarfield::SetConstsVisible( BOOL x )				{	constsVisible = x;				}
void CDataStarfield::SwitchConstsLabeled()					{	constsLabeled = !constsLabeled;	}
void CDataStarfield::SetConstsLabeled( BOOL x )				{	constsLabeled = x;				}
void CDataStarfield::SwitchSunVisible()						{	sunVisible = !sunVisible;		}
void CDataStarfield::SetSunVisible( BOOL x )				{	sunVisible = x;					}
void CDataStarfield::SwitchSunShine()						{	sunShine = !sunShine;			}
void CDataStarfield::SetSunShine( BOOL x )					{	sunShine = x;					}
void CDataStarfield::SetRotLatitude( float rotLatitude_ )	{	rotLatitude = rotLatitude_;		}
void CDataStarfield::SetRotTime( float rotTime_ )			{	rotTime = rotTime_;				}
void CDataStarfield::SwitchSpinning()						{	spinning = !spinning;			}

void CDataStarfield::SetModified( BOOL m )
{
	modified = m; documentMgr.UpdateTitle();
}

void CDataStarfield::AdjRotX( float deltaRotX )
{	
	// Restrict up and down rotation
	float newRotX = rotX + deltaRotX;

	if (newRotX > -90 && newRotX < 90) /// < 30
		rotX = newRotX;
}

void CDataStarfield::AdjRotY(float deltaRotY)
{
	rotY += deltaRotY;

	// Keep rotY between -360 and 360
	if (rotY < 360.0f)
		rotY += 360.0f;
	if (rotY > 360.0f)
		rotY -= 360.0f;
}

void CDataStarfield::AdjRotTime( float deltaTime )
{
	rotTime += deltaTime;
}

void CDataStarfield::AdjZoom( float deltaZoom )
{
	zoom += deltaZoom;
}


/////////////////////////////////////////////////////////////////////////////
// Methods


/////////////////////////////////////////////////////////////////////////////
// View Methods

void CDataStarfield::RotateUp()		{	AdjRotX(-0.5f);	}
void CDataStarfield::RotateDown()	{	AdjRotX( 0.5f);	}
void CDataStarfield::RotateLeft()	{	AdjRotY(-0.5f);	}
void CDataStarfield::RotateRight()	{	AdjRotY(0.5f);	}

void CDataStarfield::ZoomIn()
{
	if (zoom < 0.9f)
		zoom += 0.01f;
}

void CDataStarfield::ZoomOut()
{
	if (zoom > -0.8f)
		zoom -= 0.01f;
}

// Reset viewing rotation and zoom
void CDataStarfield::ResetView()
{
	ResetRot();
	ResetZoom();
}

// Reset rotation
void CDataStarfield::ResetRot()
{
	rotX = 0.0f;
	rotY = 0.0f;
}

// Reset zoom
void CDataStarfield::ResetZoom()
{
	zoom = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Star Methods

// Load default star options
void CDataStarfield::LoadStarDefaults()
{
	starsVisible = DEF_STARS_VISIBLE;
	starsLabeled = DEF_STARS_LABELED;
	limitingMag = DEF_STARS_LIMMAG;
}

// Check if the given star number belongs to a hidden constellation
BOOL CDataStarfield::IsStarInHiddenConst( int i )
{
	for( int ci=0; ci<numConstellations; ++ci )
	{
		// Continue if this constellation isn't hidden
		if( constellations[ci].IsVisible() )
			continue;
		// Otherwise search through lines
		for( int li=0; li<constellations[ci].GetNumLines(); ++li )
		{
			if( i == constellations[ci].GetLine(li)->GetStar1() ||
				i == constellations[ci].GetLine(li)->GetStar2() )
				return TRUE;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Constellation Methods

// Load default constellation options
void CDataStarfield::LoadConstDefaults()
{
	constsVisible = DEF_CONST_VISIBLE;
	constsLabeled = DEF_CONST_LABELED;
}

// Check if the given name is already in use
BOOL CDataStarfield::IsDuplicate( CString& name )
{
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
			return TRUE;
	}

	return FALSE;
}

// Add a new constellation with the given name
void CDataStarfield::AddConstellation(CString& name)
{
	constellations.push_back( CDataConst(name) );
	++numConstellations;
}

// Delete the current constellation
void CDataStarfield::DeleteConstellation()
{
	// Use an iterator to find the current constellation
	constellationsItor = constellations.begin();
	for( int i=0; i<numCurConstellation; ++i )
		++constellationsItor;

	// Delete the constellation
	constellations.erase( constellationsItor );

	--numConstellations;
}

// Rename the current constellation
void CDataStarfield::RenameConstellation( CString& name )
{
	GetCurConstellation()->SetName(name);
}

// Set the current constellation to the one with the given name
BOOL CDataStarfield::SetCurConstellation( CString& name )
{
	// Search for constellation name
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
		{
			numCurConstellation = i;
			return TRUE;
		}
	}

	// Return FALSE if name wasn't found
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// Sun methods

// Load default sun options
void CDataStarfield::LoadSunDefaults()
{
	sunVisible = DEF_SUN_VISIBLE;
	sunShine = DEF_SUN_SHINE;
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataStarfield::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int i;

	modified = FALSE;

	// Serialize CDataStarfield attributes
	if( ar.IsLoading() )
	{
		ar >> numStars
		   >> numConstellations >> numNewConstellations >> numCurConstellation
		   >> rotLatitude >> rotTime
		   >> rotX >> rotY >> zoom;
	}
	else
	{
		ar << numStars
		   << numConstellations << numNewConstellations << numCurConstellation
		   << rotLatitude << rotTime
		   << rotX << rotY << zoom;
	}

	// If we're loading, get the stars and constellations vectors ready
	if( ar.IsLoading() )
	{
		stars.clear();
		for( i=0; i<numStars; ++i )
			stars.push_back( CDataStar() );

		constellations.clear();
		for( i=0; i<numConstellations; ++i )
			constellations.push_back( CDataConst() );
	}

	// Serialize stars
	for( i=0; i<numStars; ++i )
		stars[i].Serialize( ar );

	// Serialize constellations
	for( i=0; i<numConstellations; ++i )
		constellations[i].Serialize( ar );
}



