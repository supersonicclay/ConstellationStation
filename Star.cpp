// Star.cpp : implementation of the CStar class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Star.h"

// For star randomization
#include <math.h>

CStar::CStar()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	brightness = 1.0f;
	color = WHITE;
	origColor = WHITE;
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

void CStar::SetBrightness(float brightness_)
{
	brightness = brightness_;
}

void CStar::SetColor(CColor color_)
{
	color = color_;
}

void CStar::SetOrigColor(CColor origColor_)
{
	origColor = origColor_;
}

void CStar::RestoreColor()
{
	color = origColor;
}

// Pick random x then a random y and z so that x,y,z has length of 1
//   and pick random brightess with higher chance of being dim
void CStar::Randomize()
{
	PickXYZ();
	PickBrightness();
}

void CStar::PickXYZ()
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

void CStar::PickBrightness()
{

///	brightness = (float)((rand()%600) * (rand()%600) * (rand()%600))/21600000 + 0;
///	brightness = (float)((rand()%60) * (rand()%60) * (rand()%60) * (rand()%60))/3000000 + 1;
///*

	float random = (float)(rand()%1000)/10;
	if (random < 75)
	{
		brightness = (float)(rand()%1000)/1000;
	}
	else if (random < 90)
	{
		brightness = (float)(rand()%2000)/1000;
	}
	else if (random < 95)
	{
		brightness = (float)(rand()%3000)/1000;
	}
	else //if (random <  99)
	{
		brightness = (float)(rand()%5000)/1000;
	}

	// Set Color
	if (brightness < 1)
	{
		color.r = brightness;
		color.g = brightness;
		color.b = brightness;
	}
	else if (brightness < 2)
	{
		color.r = brightness-1;
		color.g = brightness-1;
		color.b = brightness-1;
	}
	/*
	else if (brightness < 3)
	{
		color.r = brightness-2;
		color.g = brightness-2;
		color.b = brightness-2;
	}
	else if (brightness < 4)
	{
		color.r = brightness-3;
		color.g = brightness-3;
		color.b = brightness-3;
	}

	else if (brightness < 5)
	{
		color.r = brightness-4;
		color.g = brightness-4;
		color.b = brightness-4;
	}
//*/
	origColor = color;
}

