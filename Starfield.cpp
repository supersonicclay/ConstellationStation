// Starfield.cpp : implementation of the CStarfield class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Starfield.h"

#include "Star.h"
#include "Constellation.h"

// For randomization
#include <time.h>

CStarfield::CStarfield()
{
	numStars = 5000;
	stars = new CStar[numStars];
	SetupStars();

	numConstellations = 0;
	constellations = new CConstellation[numConstellations];
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

	if ( newRotX > -90 && newRotX < 10)
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
	stars[0].SetOrigColor(GREEN);
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

	///////////////////////////////
	// Restore the stars' colors //
	///////////////////////////////
	for (i=0; i<curConstellation->GetNumLines(); i++)
	{
		curConstellation->GetLine(i)->GetStar1()->RestoreColor();
		curConstellation->GetLine(i)->GetStar2()->RestoreColor();
	}

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
	// If current constellation is already set
	if (constellations[numCurConstellation].GetName() == name)
		return true;

	constellations[numCurConstellation].SetActive(false);

	// Search for constellation name
	for (int i=0; i<numConstellations; i++)
	{
		if (constellations[i].GetName() == name)
		{
			numCurConstellation = i;
			constellations[numCurConstellation].SetActive();
			return true;
		}
	}

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


/////////////////
// Save / Load //
/////////////////
/*
void CStarfield::Save()
{
	FILE *file;
	char oneline[255];
	file = fopen("data/starfield.txt", "wt");

///	NUMSTARS = 10000;
///	star = new CStar[NUMSTARS];
///	SetupStars();

	fputs ("----------------------------------------\n", file);
	fputs ("WARNING: Modify at your own risk!\n", file);
	fputs ("Constellations may not display correctly.\n", file);
	fputs ("----------------------------------------\n\n", file);
	sprintf (oneline, "NUMSTARS\t%i\n\n", NUMSTARS);
	fputs (oneline, file);
	fputs ("X\t\tY\t\tZ\t\tBRIGHTNESS\n", file);
	for (int i=0; i<NUMSTARS; i++)
	{
		sprintf (oneline, "%f\t%f\t%f\t%f\n",
			star[i].GetX(), star[i].GetY(), star[i].GetZ(), star[i].GetBrightness());
		fputs (oneline, file);
	}

	fclose(file);
}

void CStarfield::Load()
{
	float x, y, z, b;
	FILE *file;
	char oneline[255];
	file = fopen("data/starfield.txt", "rt");				// File To Load World Data From

	ReadLine(file,oneline);
	sscanf(oneline, "NUMSTARS %d\n", &NUMSTARS);
	star = new CStar[NUMSTARS];

	for (int i = 0; i < NUMSTARS; i++)
	{
		ReadLine(file,oneline);
		sscanf(oneline, "%f %f %f %f", &x, &y, &z, &b);
		star[i].SetX(x);
		star[i].SetY(y);
		star[i].SetZ(z);
		star[i].SetBrightness(b);
	}
	fclose(file);
}

void CStarfield::ReadLine(FILE *file,char *string) const
{
	do
	{
		fgets(string, 255, file);
	} while ((string[0] == 'X') || (string[0] == '\n'));
	return;
}
*/
