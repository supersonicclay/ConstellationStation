/****************************
*							*
*  Stars and Constellations	*
*							*
*      Starfield.cpp		*
*							*
****************************/

#include "ConStation.h"
//#include "Starfield.h"

// For randomization of stars
#include <time.h>
#include <math.h>


/************
*			*
*	Star	*
*			*
************/
Star::Star()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	brightness = 1.0f;
	color = WHITE;
}

Star::Star(float x_, float y_, float z_, float brightness_)
{
	x = x_;
	y = y_;
	z = z_;
	brightness = brightness_;
}

Star::~Star()
{
}

float Star::GetX()
{
	return x;
}

float Star::GetY()
{
	return y;
}

float Star::GetZ()
{
	return z;
}

float Star::GetBrightness()
{
	return brightness;
}

COLOR Star::GetColor()
{
	return color;
}

void Star::SetX(float x_)
{
	x = x_;
}

void Star::SetY(float y_)
{
	y = y_;
}

void Star::SetZ(float z_)
{
	z = z_;
}

void Star::SetBrightness(float brightness_)
{
	brightness = brightness_;
}

void Star::SetColor(COLOR color_)
{
	color = color_;
	/*
	color.r = color_.r;
	color.g = color_.g;
	color.b = color_.b;
	*/
}

void Star::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

// Pick random x then a random y and z so that x,y,z has length of 1
void Star::PickXYZ()
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

void Star::Draw() const
{
//	glColor3f (1.0f,1.0f,1.0f);
	glColor3f (color.r, color.g, color.b);
	if (starfield.GetZoom() > 0)
		glPointSize(brightness * (starfield.GetZoom()+1));
	else glPointSize(brightness * (starfield.GetZoom() + 3) * 0.3f);
//	if ((int) newBrightness > 0)
//	{
		glBegin(GL_POINTS);
			glVertex3f ( x, y, z);
		glEnd();
//	}
}


/********************
*					*
*	Constellation	*
*					*
********************/
Constellation::Constellation()
{

}

Constellation::~Constellation()
{
}

void Constellation::Draw() const
{
}


/****************
*				*
*	Starfield	*
*				*
****************/
Starfield::Starfield()
{
//	star = new Star[NUMSTARS];
//	SetupStars();
//	Load();
	Save();

	constellation = new Constellation[1];
	ResetView();

	starMouseOver = NULL;////
}

Starfield::~Starfield()
{
	delete [] star;
}

Star* Starfield::GetStar(GLuint x) const
{
	return &star[x];
}

float Starfield::GetZoom() const
{
	return zoom;
}

float Starfield::GetRotX() const
{
	return rotX;
}

float Starfield::GetRotY() const
{
	return rotY;
}

/*////
Star* Starfield::GetStarMouseOver()
{
	return starMouseOver;
}
*/

void Starfield::SetRotX(float rotX_)
{
	rotX = rotX_;
}

void Starfield::SetRotY(float rotY_)
{
	rotY = rotY_;
}

/*////
void Starfield::SetStarMouseOver(Star* s)
{
	starMouseOver = s;
}
*/

void Starfield::RotateUp ()
{
	if (rotX > -90)								// Keep rotX between +- 90
		rotX -= 0.3f * (-zoom + 1);				// Change is smaller if zoomed out
}

void Starfield::RotateDown ()
{
	if (rotX < 90)								// Keep rotX between +- 90
		rotX += 0.3f * (-zoom + 1);				// Change is smaller if zoomed out
}

void Starfield::RotateLeft ()
{
	rotY -= 0.3f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY < -360)							// Keep rotY between +- 360
		rotY += 360.0f;
}

void Starfield::RotateRight()
{
	rotY += 0.3f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY > 360)								// Keep rotY between +- 360
		rotY -= 360.0f;
}

void Starfield::ZoomIn()
{
		if (zoom < 0.9)
			zoom += 0.01f * (-zoom +1);			// Change is smaller if zoomed out
}

void Starfield::ZoomOut()
{
	if (zoom > -3.9)
		zoom -= 0.01f * (-zoom +1);				// Change is smaller if zoomed out
}

void Starfield::ResetView()
{
	rotX = 0.0f;
	rotY = 0.0f;
	zoom = 0.0f;
}

// Creates sphere of random stars with radius of 1
void Starfield::SetupStars()
{
	srand( (unsigned)time(NULL) );

	// Loop for each star
	for (int i=0; i<NUMSTARS; i++)
	{
		star[i].PickXYZ();
	}
}

void Starfield::Save()
{
	FILE *file;
	char oneline[255];
	file = fopen("data/starfield.txt", "wt");

	////
	NUMSTARS = 10000;
	star = new Star[NUMSTARS];
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

void Starfield::Load()
{
	float x, y, z, b;
	FILE *file;
	char oneline[255];
	file = fopen("data/starfield.txt", "rt");				// File To Load World Data From

	ReadLine(file,oneline);
	sscanf(oneline, "NUMSTARS %d\n", &NUMSTARS);
	star = new Star[NUMSTARS];

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

void Starfield::ReadLine(FILE *file,char *string) const
{
	do
	{
		fgets(string, 255, file);
	} while ((string[0] == 'X') || (string[0] == '\n'));
	return;
}


void Starfield::Draw() const
{
	glPushMatrix();
	// Rotate and zoom
	glTranslatef (0.0f,0.0f,zoom);
	glRotatef (rotX, 1.0f, 0.0f, 0.0f);
	glRotatef (rotY, 0.0f, 1.0f, 0.0f);

	// North Star
	glColor3f (1.0f,0.0f,0.0f);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	// The rest of the stars
	for (int i=0; i<NUMSTARS; i++)
	{
		glPushName(i);										// Assign Object A Name (ID)
		star[i].Draw();
		glPopName();
	}
	glPopMatrix();
}
