// Star.cpp : implementation of the CStar class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Star.h"


IMPLEMENT_SERIAL (CStar, CObject, 0)

CStar::CStar()
{
	x = 0.0f;
	y = 1.0f;
	z = 0.0f;
	longitude = 0.0f;
	latitude = 0.0f;
	brightness = 1.0f;
	color = COLOR_WHITE;
}

CStar::~CStar()
{
}

float CStar::GetX() const
{
	return x;
}

float CStar::GetY() const
{
	return y;
}

float CStar::GetZ() const
{
	return z;
}

float CStar::GetLongitude() const
{
	return longitude;
}

float CStar::GetLatitude() const
{
	return latitude;
}

float CStar::GetBrightness() const
{
	return brightness;
}

CColor CStar::GetColor() const
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

void CStar::SetLongitude( float longitude_ )
{
	longitude = longitude_;
}

void CStar::SetLatitude( float latitude_ )
{
	latitude = latitude_;
}

void CStar::SetBrightness(float brightness_)
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
	PickDirection();
	PickBrightness();
}

void CStar::PickDirection()
{
	PickXYZ();


	if( z >= 0 )
	{
		longitude = (float) asin( (double) (x / sqrt((double)(z*z) + (x*x))) );
	}
	else
	{
		longitude = (float) (PI - asin( (double)(x / sqrt((double)(z*z) + (x*x))) ));
	}
//	longitude = (float) atan( (double) (x / z) ) * (float) (180 / PI);
	latitude  = (float) acos( (double) y  );

	longitude = longitude * (float) (180 / PI);
	latitude  = latitude  * (float) (180 / PI);
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
	// Pick random number from 0.00 to 100.00
	float random = (float)(rand()%1000)/10;


	if( random < 97.0f )
	{
		brightness = (float)(rand()%1000)/2000;
	}
	else if( random < 99.3f )
	{
		brightness = (float)(rand()%1000)/2000 + 0.5f;
	}
	else
	{
		brightness = (float)(rand()%1000)/1000 + 0.75f;
	}

	PickColor();
}

void CStar::PickColor()
{
	if( brightness < 1.0f )
	{
		color.r = brightness;
		color.g = brightness;
		color.b = brightness;
	}
	else
	{
		color = COLOR_WHITE;
	}
}

void CStar::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << latitude << longitude
		   << x << y << z
		   << brightness
		   << color.r << color.g << color.b;
	}

	else
	{
		ar >> latitude >> longitude
		   >> x >> y >> z
		   >> brightness
		   >> color.r >> color.g >> color.b;
	}
}
