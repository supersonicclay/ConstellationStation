#include "stdafx.h"
#include "ConStation.h"
#include "Starfield.h"

#include <math.h>


/************
*			*
*	CStar	*
*			*
************/
CStar::CStar()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	brightness = 1.0f;
////color = WHITE;
}

CStar::CStar(float x_, float y_, float z_, float brightness_)
{
	x = x_;
	y = y_;
	z = z_;
	brightness = brightness_;
}

CStar::~CStar()
{
}

float CStar::GetX()
{
	return x;
}

float CStar::GetY()
{
	return y;
}

float CStar::GetZ()
{
	return z;
}

float CStar::GetBrightness()
{
	return brightness;
}

/*////
COLOR CStar::GetColor()
{
	return color;
}
*/

void CStar::SetX(float x_)
{
	x = x_;
}

void CStar::SetY(float y_)
{
	y = y_;
}

void CStar::SetZ(float z_)
{
	z = z_;
}

void CStar::SetBrightness(float brightness_)
{
	brightness = brightness_;
}

/*
void CStar::SetColor(COLOR color_)
{
	color = color_;

//	color.r = color_.r;
//	color.g = color_.g;
//	color.b = color_.b;
}

void CStar::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}
*/

// Pick random x then a random y and z so that x,y,z has length of 1
void CStar::Randomize()
{
	x = (float)(rand()%2000)/1000-1;		// +1.0 to -1.0

	int chooseYbeforeZ;						// Helps randomize stars
	float absYMax;							// The maximum absolute value of Y based on X
	float absZMax;							// The maximum absolute value of Z based on X
	int plus_minus;							// +1 or -1 (for easier reading)

	chooseYbeforeZ = rand()%2;				// 0 or 1 (T or F)

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
//	brightness = (float)((rand()%600) * (rand()%600) * (rand()%600))/21600000 + 0;
	brightness = (float)((rand()%60) * (rand()%60) * (rand()%60) * (rand()%60))/2000000 + 1;
}


/********************
*					*
*	CConstellation	*
*					*
********************/
CConstellation::CConstellation()
{

}

CConstellation::~CConstellation()
{
}

/*
void CConstellation::Draw() const
{
}
*/

/****************
*				*
*	CStarfield	*
*				*
****************/
CStarfield::CStarfield()
{
	numStars = 10000;
	stars = new CStar[numStars];
	SetupStars();

	constellations = new CConstellation[1];
////ResetView();

////starMouseOver = NULL;
}

CStarfield::~CStarfield()
{
	delete [] stars;
}

CStar* CStarfield::GetStar(int i) const
{
	return &stars[i];
}

int CStarfield::GetNumStars() const
{
	return numStars;
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



