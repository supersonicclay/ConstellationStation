// Star.cpp : implementation of the CStar class
//

#include "stdafx.h"
#include "ConStation.h"

#include "Star.h"

// For star randomization
#include <time.h>
#include <math.h>

CStar::CStar()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	brightness = 1;
	color = WHITE;
}

CStar::CStar(float x_, float y_, float z_, int brightness_)
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

int CStar::GetBrightness()
{
	return brightness;
}

CColor CStar::GetColor()
{
	return color;
}

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

void CStar::SetBrightness(int brightness_)
{
	brightness = brightness_;
}

void CStar::SetColor(CColor color_)
{
	color = color_;
}

// Pick random x then a random y and z so that x,y,z has length of 1
//   and pick random brightess with higher chance of being dim
void CStar::Randomize()
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
////brightness = (float)((rand()%600) * (rand()%600) * (rand()%600))/21600000 + 0;
//	brightness = (float)((rand()%60) * (rand()%60) * (rand()%60) * (rand()%60))/3000000 + 1;
///*
	float random = (float)(rand()%1000)/10;
	if (random < 85)
		brightness = 1;
	else if (random < 98)
		brightness = 2;
	else if (random < 98.5f)
		brightness = 3;
	else //if (random <  99)
		brightness = 5;
//*/
}

