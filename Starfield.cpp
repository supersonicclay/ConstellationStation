// Starfield.cpp : implementation of the CStarfield class
//

#include "stdafx.h"
#include "ConStation.h"

#include "Starfield.h"
#include "Star.h"
#include "Constellation.h"

CStarfield::CStarfield()
{
	numStars = 5000;
	stars = new CStar[numStars];
	SetupStars();

	numConstellations = 0;
	constellations = new CConstellation[numConstellations];
	numCurConstellation = 0;

////starMouseOver = NULL;
}

CStarfield::~CStarfield()
{
	delete [] stars;
	delete [] constellations;
}

CStar* CStarfield::GetStar(int i) const
{
	return &stars[i];
}

CConstellation* CStarfield::GetConstellation(int i) const
{
	return &constellations[i];
}

int CStarfield::GetNumStars() const
{
	return numStars;
}

int CStarfield::GetNumConstellations() const
{
	return numConstellations;
}

void CStarfield::SetNumCurConstellation(int i)
{
	numCurConstellation = i;
}

// Creates sphere of random stars with radius of 1
void CStarfield::SetupStars()
{
	srand( (unsigned)time(NULL) );

	// Loop for each star
	for (int i=0; i<numStars; i++)
	{
		stars[i].Randomize();
	}
}

/////////////////////////////
// Constellation functions //
/////////////////////////////
void CStarfield::AddConstellation()
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

}

void CStarfield::AddConstLine(int starNum1, int starNum2)
{
	constellations[numCurConstellation].AddLine(&stars[starNum1], &stars[starNum2]);
}

/*
void CStarfield::Save()
{
	FILE *file;
	char oneline[255];
	file = fopen("data/starfield.txt", "wt");

	////
	NUMSTARS = 10000;
	star = new CStar[NUMSTARS];
	SetupStars();
	////

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
