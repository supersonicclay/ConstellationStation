//===========================================================================
// Starfield.cpp
//
// CStarfield
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain settings. A CStarfield and 
//   everything in a CStarfield can be saved and opened.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "Starfield.h"

#include "Star.h"
#include "Constellation.h"

IMPLEMENT_SERIAL( CStarfield, CObject, 1 )


const int MAX_STARS = 15000;/// Make changeable


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CStarfield::CStarfield()
{
	Clear();
}

CStarfield::~CStarfield()
{
}

void CStarfield::Clear()
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

	starsVisible = TRUE;
	starsLabeled = FALSE;
	limitingMag = 5.0f;

	constsVisible = TRUE;
	constsLabeled = TRUE;

	// Time
	time_t seconds = time(NULL);
	gregorian = *(localtime( &seconds ));
	gregorian.tm_year += 1900;
///	julian = 
	rotTime = 0.0f;

	// Latitude & Longitude
	rotLatitude = 50.0f;
}

void CStarfield::New( BOOL actual )
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
void CStarfield::InitRandomStars()
{
	numStars = 8000;
	CStar newStar;

	/* /// North Star
	newStar.SetColor( COLOR_NORTHSTAR );
	newStar.SetMag( 2.0f );
	newStar.SetRA( 0, 0, 0.0f );
	newStar.SetDec( 90, 0, 0.0f );
	newStar.SetX( 0.0f );
	newStar.SetY( 1.0f );
	newStar.SetZ( 0.0f );
	stars.push_back( CStar(newStar) );
	*/

	// Sun Corona
	newStar.SetColor( COLOR_WHITE );
	newStar.SetMag( 60.0f );
	newStar.SetRA( 12, 0, 0.0f );
	newStar.SetDec( TRUE, 0, 0, 0.0f );
	newStar.SetX( 0.0f );
	newStar.SetY( 0.0f );
	newStar.SetZ(-1.0f );
	stars.push_back( CStar(newStar) );

	// Randomize the rest
	for (int i=1; i<numStars; i++)
	{
		newStar.Randomize();
		stars.push_back( CStar(newStar) );
	}
}

// Load the actual stars from the magnitude-sorted hipparcos catalog
void CStarfield::InitActualStars()
{
	CStar newStar;

	numStars = MAX_STARS;///
	stars.reserve( numStars );

	CFile file( "data\\hip_main.txt", CFile::modeRead );

	char buffer[100];
	ra_s ra = {0};
	dec_s dec = {0};
	float mag = 0;

	for( int i=0; i<MAX_STARS; ++i )
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

		stars.push_back( CStar(newStar) );
	}

	file.Close();

}

/// Load actual constellations somehow
void CStarfield::InitActualConstellations()
{
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CStar*			CStarfield::GetStar(int i)				{	return &stars[i];								}
int				CStarfield::GetNumStars()				{	return numStars;								}
CConstellation*	CStarfield::GetConstellation(int i)		{	return &constellations[i];						}
CConstellation*	CStarfield::GetCurConstellation()		{	return &constellations[numCurConstellation];	}
int				CStarfield::GetNumConstellations()		{	return numConstellations;						}
int				CStarfield::GetNumCurConstellation()	{	return numCurConstellation;						}
int				CStarfield::GetNumNewConstellations()	{	return numNewConstellations;					}
BOOL			CStarfield::AreStarsVisible()			{	return starsVisible;							}
BOOL			CStarfield::AreStarsLabeled()			{	return starsLabeled;							}
float			CStarfield::GetLimitingMag()			{	return limitingMag;								}
BOOL			CStarfield::AreConstsVisible()			{	return constsVisible;							}
BOOL			CStarfield::AreConstsLabeled()			{	return constsLabeled;							}
BOOL			CStarfield::IsModified()				{	return modified;								}
float			CStarfield::GetRotLatitude()			{	return rotLatitude;								}
float			CStarfield::GetRotTime()				{	return rotTime;									}
BOOL			CStarfield::IsSpinning()				{	return spinning;								}
float			CStarfield::GetRotX()					{	return rotX;									}
float			CStarfield::GetRotY()					{	return rotY;									}
float			CStarfield::GetZoom()					{	return zoom;									}

// Find the constellation with the given name
CConstellation*	CStarfield::GetConstellation( CString& name )
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

void CStarfield::IncNumNewConstellations()				{	numNewConstellations++;			}
void CStarfield::SetNumCurConstellation( int i )		{	numCurConstellation = i;		}
void CStarfield::SwitchStarsVisible()					{	starsVisible = !starsVisible;	}
void CStarfield::SetStarsVisible( BOOL x )				{	starsVisible = x;				}
void CStarfield::SwitchStarsLabeled()					{	starsLabeled = !starsLabeled;	}
void CStarfield::SetStarsLabeled( BOOL x )				{	starsLabeled = x;				}
void CStarfield::SetLimitingMag( float m )				{	limitingMag = m;				}
void CStarfield::SwitchConstsVisible()					{	constsVisible = !constsVisible;	}
void CStarfield::SetConstsVisible( BOOL x )				{	constsVisible = x;				}
void CStarfield::SwitchConstsLabeled()					{	constsLabeled = !constsLabeled;	}
void CStarfield::SetConstsLabeled( BOOL x )				{	constsLabeled = x;				}
void CStarfield::SetRotLatitude( float rotLatitude_ )	{	rotLatitude = rotLatitude_;		}
void CStarfield::SetRotTime( float rotTime_ )			{	rotTime = rotTime_;				}
void CStarfield::SwitchSpinning()						{	spinning = !spinning;			}

void CStarfield::SetModified( BOOL m )
{
	modified = m; starfieldMgr.UpdateTitle();
}

void CStarfield::AdjRotX( float deltaRotX )
{	
	// Restrict up and down rotation
	float newRotX = rotX + deltaRotX;

	if (newRotX > -90 && newRotX < 90) /// < 30
		rotX = newRotX;
}

void CStarfield::AdjRotY(float deltaRotY)
{
	rotY += deltaRotY;

	// Keep rotY between -360 and 360
	if (rotY < 360.0f)
		rotY += 360.0f;
	if (rotY > 360.0f)
		rotY -= 360.0f;
}

void CStarfield::AdjRotTime( float deltaTime )
{
	rotTime += deltaTime;
}

void CStarfield::AdjZoom( float deltaZoom )
{
	zoom += deltaZoom;
}


/////////////////////////////////////////////////////////////////////////////
// Methods


/////////////////////////////////////////////////////////////////////////////
// View Methods

void CStarfield::RotateUp()		{	AdjRotX(-0.5f);	}
void CStarfield::RotateDown()	{	AdjRotX( 0.5f);	}
void CStarfield::RotateLeft()	{	AdjRotY(-0.5f);	}
void CStarfield::RotateRight()	{	AdjRotY(0.5f);	}

void CStarfield::ZoomIn()
{
	if (zoom < 0.9f)
		zoom += 0.01f;
}

void CStarfield::ZoomOut()
{
	if (zoom > -0.8f)
		zoom -= 0.01f;
}

// Reset viewing rotation and zoom
void CStarfield::ResetView()
{
	ResetRot();
	ResetZoom();
}

// Reset rotation
void CStarfield::ResetRot()
{
	rotX = 0.0f;
	rotY = 0.0f;
}

// Reset zoom
void CStarfield::ResetZoom()
{
	zoom = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Constellation Methods

// Check if the given name is already in use
BOOL CStarfield::IsDuplicate( CString& name )
{
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
			return TRUE;
	}

	return FALSE;
}

// Add a new constellation with the given name
void CStarfield::AddConstellation(CString& name)
{
	constellations.push_back( CConstellation(name) );
	++numConstellations;
}

// Delete the current constellation
void CStarfield::DeleteConstellation()
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
void CStarfield::RenameConstellation( CString& name )
{
	GetCurConstellation()->SetName(name);
}

// Set the current constellation to the one with the given name
BOOL CStarfield::SetCurConstellation( CString& name )
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
// Serialization

void CStarfield::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int i;

	modified = FALSE;

	// Serialize CStarfield attributes
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
			stars.push_back( CStar() );

		constellations.clear();
		for( i=0; i<numConstellations; ++i )
			constellations.push_back( CConstellation() );
	}

	// Serialize stars
	for( i=0; i<numStars; ++i )
		stars[i].Serialize( ar );

	// Serialize constellations
	for( i=0; i<numConstellations; ++i )
		constellations[i].Serialize( ar );
}


/*
void CStarfield::Serialize(CArchive& ar)///
{
	CObject::Serialize(ar);

	// Serialize CStarfield attributes
	if (ar.IsStoring())
	{
		ar << numStars
		   << numConstellations << numNewConstellations << numCurConstellation
		   << rotLatitude << rotTime
		   << rotX << rotY << zoom;
	}
	else
	{
		ar >> numStars
		   >> numConstellations >> numNewConstellations >> numCurConstellation
		   >> rotLatitude >> rotTime
		   >> rotX >> rotY >> zoom;
	}

	// If were loading we need to allocate space for stars and constellations
	if (ar.IsLoading())
	{
		stars = new CStar[numStars];
		constellations = new CConstellation[numConstellations];
	}

	// Serialize stars and constellations
	int i;
	for (i=0; i<numStars; i++)
	{
		stars[i].Serialize(ar);
	}

	for (i=0; i<numConstellations; i++)
	{
		constellations[i].Serialize(ar);
	}

	
	SerializeConstLines(ar);
}

void CStarfield::SerializeConstLines(CArchive& ar)
{
	// Serialization for each constellation line must be done here since
	//  they reference stars
	int starIndex, constIndex, lineIndex;

	BOOL starFound;

	// Archive is storing
	if (ar.IsStoring())
	{
		// Cycle through constellations
		for (constIndex=0; constIndex < numConstellations; constIndex++)
		{
			// Cycle through lines
			for (lineIndex=0; lineIndex < constellations[constIndex].GetNumLines(); lineIndex++)
			{
				// For each star find it's corresponding star number 
				
				// Star 1
				starFound = FALSE;
				// Cycle through stars
				for (starIndex=0; starIndex < numStars; starIndex++)
				{
					// Is this the star we're looking for 
					if (constellations[constIndex].GetLine(lineIndex)->GetStar1() == &stars[starIndex])
					{
						// Store this star's number
						ar << starIndex;
						starFound = TRUE;
						break;
					}
				}
				if (!starFound)
					CSWarn("A star was not found while saving.");

				// Star 2
				starFound = FALSE;
				// Cycle through stars
				for (starIndex=0; starIndex < numStars; starIndex++)
				{
					// Is this the star we're looking for 
					if (constellations[constIndex].GetLine(lineIndex)->GetStar2() == &stars[starIndex])
					{
						// Store this star's number
						ar << starIndex;
						starFound = TRUE;
						break;
					}
				}
				if (!starFound)
					CSWarn("A star was not found while saving.");
			}
		}
	}
	else	// Archive is loading
	{
		int starNum1, starNum2;
		// Cycle through constellations
		for (constIndex=0; constIndex < numConstellations; constIndex++)
		{
			// Cycle through lines
			for (lineIndex=0; lineIndex < constellations[constIndex].GetNumLines(); lineIndex++)
			{
				// Archive has the star numbers.
				//  We need to make the line reference these stars
				ar >> starNum1 >> starNum2;

				constellations[constIndex].GetLine(lineIndex)->SetStar1(&stars[starNum1]);
				constellations[constIndex].GetLine(lineIndex)->SetStar2(&stars[starNum2]);
			}
		}
	}
}
*/