// Starfield.cpp : implementation of the CStarfield class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Starfield.h"

#include "Star.h"
#include "Constellation.h"

// For randomization
#include <time.h>

IMPLEMENT_SERIAL (CStarfield, CObject, 0)

CStarfield::CStarfield()
{
	numStars = 5000;
	stars = new CStar[numStars];
	SetupStars();

	numConstellations = 0;
	constellations = new CConstellation[numConstellations];
	numNewConstellations = 0;
	numCurConstellation = 0;

	latitude = 30;
	season = 0;///
	time = 0;
	spinning = false;

	rotX = 0;
	rotY = 0;
	zoom = 0;
}

CStarfield::~CStarfield()
{
	delete [] stars;
	delete [] constellations;
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

float CStarfield::GetLatitude() const
{
	return latitude;
}

int CStarfield::GetSeason() const
{
	return season;
}

float CStarfield::GetTime() const
{
	return time;
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

void CStarfield::SetNumCurConstellation(int i)
{
	numCurConstellation = i;
}

void CStarfield::SetLatitude(float latitude_)
{
	latitude = latitude_;
}

void CStarfield::SetSeason(int season_)
{
	season = season_;
}

void CStarfield::SetTime(float time_)
{
	time = time_;
}

void CStarfield::SwitchSpinning()
{
	spinning = !spinning;
}

void CStarfield::AdjTime(float deltaTime)
{
	time += deltaTime;
}

void CStarfield::AdjRotX(float deltaRotX)
{
	// Restrict up and down rotation
	float newRotX = rotX + deltaRotX;

	if (newRotX > -90 && newRotX < 10)
		rotX = newRotX;
}

void CStarfield::AdjRotY(float deltaRotY)
{
	rotY += deltaRotY;
}

void CStarfield::AdjZoom(float deltaZoom)
{
	zoom += deltaZoom;
}


////////////////////
// Star functions //
////////////////////
// Creates sphere of random stars with radius of 1
void CStarfield::SetupStars()
{
	srand( (unsigned)::time(NULL) );

	// North Star
	stars[0].SetColor(GREEN);
	stars[0].SetBrightness(6.0f);
	stars[0].SetX(0);
	stars[0].SetY(0);
	stars[0].SetZ(-0.99f);

	// Randomize the rest
	for (int i=1; i<numStars; i++)
	{
		stars[i].Randomize();
	}
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

	// Backup constellations
	for (i=0; i<numConstellations; i++)
		copy[i] = constellations[i];
	
	// Increase array size
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

	/*
	///////////////////////////////
	// Restore the stars' colors //
	///////////////////////////////
	for (i=0; i<curConstellation->GetNumLines(); i++)
	{
		curConstellation->GetLine(i)->GetStar1()->RestoreColor();
		curConstellation->GetLine(i)->GetStar2()->RestoreColor();
	}
	*/

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
	/// If current constellation is already set
//	if (constellations[numCurConstellation].GetName() == name)
//		return true;

	constellations[numCurConstellation].SetCurrent(false);

	// Search for constellation name
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
		{
			numCurConstellation = i;
			constellations[numCurConstellation].SetCurrent();
			return true;
		}
	}

	// Return false if name wasn't found
	return false;
}

void CStarfield::AddConstLine(int starNum1, int starNum2)
{
	constellations[numCurConstellation].AddLine(&stars[starNum1], &stars[starNum2]);
}


////////////////////
// View Functions //
////////////////////
void CStarfield::RotateUp ()
{
	if (rotX > -90.0f)								// Keep rotX between +- 90
		rotX -= 0.5f * (-zoom + 1);				// Change is smaller if zoomed out
}

void CStarfield::RotateDown ()
{
	if (rotX < 90.0f)								// Keep rotX between +- 90
		rotX += 0.5f * (-zoom + 1);				// Change is smaller if zoomed out
}

void CStarfield::RotateLeft ()
{
	rotY -= 0.5f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY < -360.0f)							// Keep rotY between +- 360
		rotY += 360.0f;
}

void CStarfield::RotateRight()
{
	rotY += 0.5f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY > 360.0f)							// Keep rotY between +- 360
		rotY -= 360.0f;
}

void CStarfield::ZoomIn()
{
	if (zoom < 0.8f)
		zoom += 0.01f * (1-zoom);
}

void CStarfield::ZoomOut()
{
	if (zoom > -0.9f)
		zoom -= 0.01f * (1-zoom);
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

void CStarfield::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << numStars
		   << numConstellations << numNewConstellations << numCurConstellation
		   << latitude << season << time
		   << spinning
		   << rotX << rotY << zoom;
	}
	else
	{
		ar >> numStars
		   >> numConstellations >> numNewConstellations >> numCurConstellation
		   >> latitude >> season >> time
		   >> spinning
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
