// Starfield.cpp : implementation of the CStarfield class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Starfield.h"

#include "Star.h"
#include "Constellation.h"

#include <fstream.h>


/// Make changeable
#define MAX_STARS  15000


//////////
// Init //
//////////
CStarfield::CStarfield( bool random )
{
	numStars = 0;
	stars = new CStar[MAX_STARS];

	// Gregorian Time
	time_t seconds = time(NULL);
	gregorian = *(localtime( &seconds ));
	gregorian.tm_year += 1900;

	/// Julian Date
///	julian = 

	/// Latitude & Longitude

///	random = true;///

	Init();

	if( random )
	{
		InitRandomStars();
		InitRandomConstellations();
	}
	else
	{
		InitActualStars();
		InitActualConstellations();
	}
}

CStarfield::~CStarfield()
{
	delete[] stars;
	delete[] constellations;
}

void CStarfield::Init()
{
	rotLatitude = 70.0f; ///
	rotTime = 0.0f;
	spinning = FALSE;

	rotX = 0.0f;
	rotY = 0.0f;
	zoom = 0.0f;
}

////////////////
// Stars Init //
////////////////
// Creates sphere of random stars with radius of 1
void CStarfield::InitRandomStars()
{
	numStars = 8000;
	/* /// North Star
	stars[0].SetColor( COLOR_NORTHSTAR );
	stars[0].SetMag( 2.0f );
	stars[0].SetRA( 0, 0, 0.0f );
	stars[0].SetDec( 90, 0, 0.0f );
	stars[0].SetX( 0.0f );
	stars[0].SetY( 1.0f );
	stars[0].SetZ( 0.0f );
	*/

	// Sun Corona
	stars[0].SetColor( COLOR_WHITE );
	stars[0].SetMag( 60.0f );
	stars[0].SetRA( 12, 0, 0.0f );
	stars[0].SetDec( TRUE, 0, 0, 0.0f );
	stars[0].SetX( 0.0f );
	stars[0].SetY( 0.0f );
	stars[0].SetZ(-1.0f );


	// Randomize the rest
	for (int i=1; i<numStars; i++)
	{
		stars[i].Randomize();
	}
}

void CStarfield::InitActualStars()
{
	numStars = MAX_STARS;

	ifstream file( "data/hip_main.txt" );

	char buffer[100];
	ra_s ra = {0};
	char sign = 0;
	dec_s dec = {0};
	float mag = 0;

	for( int i=0; i<MAX_STARS; ++i )
	{
		file.ignore( 17 );

		// Right Ascension
		file.read( buffer, 2 );
		ra.hour = atoi( buffer );
			file.ignore();
		file.read( buffer, 2 );
		ra.minute = atoi( buffer );
			file.ignore();
		file.read( buffer, 5 );
		ra.second = (float) atof( buffer );

		file.ignore();

		// Declination
		sign = file.get();
		dec.positive = sign == '+';

		file.read( buffer, 2 );
		dec.degree = atoi( buffer );
			file.ignore();
		file.read( buffer, 2 );
		dec.minute = atoi( buffer );
			file.ignore();
		file.read( buffer, 4 );
		dec.second = (float) atof( buffer);

		file.ignore();

		// Magnitude
		file.read( buffer, 5 );
		mag = (float) atof( buffer );

		// Ignore rest of line
		file.ignore(500, '\n');

		stars[i].SetRA( ra );
		stars[i].SetDec( dec );
		stars[i].SetXYZFromRADec();
		stars[i].SetMag( mag );
		stars[i].SetColorFromMag();
		stars[i].SetRadiusFromMag();
	}

	file.close();
}


////////////////////////
// Constellation Init //
////////////////////////

void CStarfield::InitRandomConstellations()
{
		numConstellations = 0;
		numNewConstellations = 0;
		numCurConstellation = 0;
		constellations = new CConstellation[1];
}

void CStarfield::InitActualConstellations()
{
		numConstellations = 0;
		numNewConstellations = 0;
		numCurConstellation = 0;
		constellations = new CConstellation[1];
}

//////////
// Gets //
//////////
CStar* CStarfield::GetStars() const
{
	return stars;
}

CConstellation* CStarfield::GetConstellations() const
{
	return constellations;
}

CStar* CStarfield::GetStar(int i) const
{
	return &stars[i];
}

CConstellation* CStarfield::GetConstellation(int i) const
{
	return &constellations[i];
}

CConstellation* CStarfield::GetConstellation(CString &name) const
{
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
			return &constellations[i];
	}
	return 0;
}

CConstellation* CStarfield::GetCurConstellation() const
{
	return &constellations[numCurConstellation];
}

int CStarfield::GetNumStars() const
{
	return numStars;
}

int CStarfield::GetNumConstellations() const
{
	return numConstellations;
}

int CStarfield::GetNumCurConstellation() const
{
	return numCurConstellation;
}

int CStarfield::GetNumNewConstellations() const
{
	return numNewConstellations;
}

float CStarfield::GetRotLatitude() const
{
	return rotLatitude;
}

float CStarfield::GetRotTime() const
{
	return rotTime;
}

BOOL CStarfield::IsSpinning() const
{
	return spinning;
}

float CStarfield::GetRotX() const
{
	return rotX;
}

float CStarfield::GetRotY() const
{
	return rotY;
}

float CStarfield::GetZoom() const
{
	return zoom;
}


//////////
// Sets //
//////////
void CStarfield::IncNumNewConstellations()
{
	numNewConstellations++;
}

void CStarfield::SetNumCurConstellation( int i )
{
	numCurConstellation = i;
}

void CStarfield::SetRotLatitude( float rotLatitude_ )
{
	rotLatitude = rotLatitude_;
}

void CStarfield::SetRotTime( float rotTime_ )
{
	rotTime = rotTime_;
}

void CStarfield::SwitchSpinning()
{
	spinning = !spinning;
}

void CStarfield::AdjRotTime(float deltaTime)
{
	rotTime += deltaTime;
}

void CStarfield::AdjRotX(float deltaRotX)
{
	// Restrict up and down rotation
	float newRotX = rotX + deltaRotX;

	if (newRotX > -90 && newRotX < 30)
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

void CStarfield::AdjZoom(float deltaZoom)
{
	zoom += deltaZoom;
}


////////////////////
// View Functions //
////////////////////
void CStarfield::RotateUp ()
{
	AdjRotX(-0.5f);
}

void CStarfield::RotateDown ()
{
	AdjRotX(0.5f);
}

void CStarfield::RotateLeft ()
{
	AdjRotY(-0.5f);
}

void CStarfield::RotateRight()
{
	AdjRotY(0.5f);
}

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

// View resets
void CStarfield::ResetView()
{
	ResetRot();
	ResetZoom();
}

void CStarfield::ResetRot()
{
	rotX = 0.0f;
	rotY = 0.0f;
}

void CStarfield::ResetZoom()
{
	zoom = 0.0f;
}


/////////////////////////////
// Constellation functions //
/////////////////////////////
BOOL CStarfield::IsDuplicate(CString &name)
{
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
			return true;
	}

	return false;
}

void CStarfield::AddConstellation(CString &name)
{
	int i;
	CConstellation* copy = new CConstellation[numConstellations];

	// Copy constellations
	for (i=0; i<numConstellations; i++)
		copy[i] = constellations[i];

	// Increase array size
	delete[] constellations;
	constellations = new CConstellation[++numConstellations];

	// Restore constellations
	for (i=0; i<numConstellations-1; i++)
		constellations[i] = copy[i];

	// Set the last constellations name
	constellations[i].SetName(name);
}

void CStarfield::DeleteConstellation()
{
	int i;

	CConstellation* curConstellation = &constellations[numCurConstellation];

	// new temporary constellation list
	CConstellation* newList = new CConstellation[numConstellations-1];

	// copy old list into new list without the constellation being deleted
	int newListIndex = 0;
	for (i=0; i<numConstellations; i++)
	{
		if (i != numCurConstellation)
			newList[newListIndex++] = constellations[i];
	}

	numConstellations--;
	numCurConstellation = 0;

	// resize array
	constellations = new CConstellation[numConstellations];

	// copy back into array
	for (i=0; i<numConstellations; i++)
	{
		constellations[i] = newList[i];
	}
}

void CStarfield::RenameConstellation(CString &name)
{
	GetCurConstellation()->SetName(name);
}

BOOL CStarfield::SetCurConstellation(CString name)
{
	// If the constellation is already current
	if (constellations[numCurConstellation].GetName() == name)
		return TRUE;

	// Search for constellation name
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
		{
			numCurConstellation = i;
			return TRUE;
		}
	}

	// Return false if name wasn't found
	return FALSE;
}

void CStarfield::AddConstLine(int starNum1, int starNum2)
{
	constellations[numCurConstellation].AddLine(&stars[starNum1], &stars[starNum2]);
}

/*
void CStarfield::Serialize(CArchive& ar)///
{
	CObject::Serialize(ar);

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
					AfxMessageBox("A star was not found while saving.", MB_ICONEXCLAMATION);

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
					AfxMessageBox("A star was not found while saving.", MB_ICONEXCLAMATION);
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