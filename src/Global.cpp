

#include "stdafx.h"
#include "Global.h"
#include "ConStationFrame.h"

CStarfield* starfield = new CStarfield;
CTerrain* terrain = new CTerrain;

// STATES
state_e state = state_Viewing;

// COLOR
const color_s	COLOR_WHITE =		{1.0f, 1.0f, 1.0f},
				COLOR_BLACK =		{0.0f, 0.0f, 0.0f},
				COLOR_CROSS =		{0.3f, 0.3f, 0.8f},
				COLOR_ACTIVESTAR =	{1.0f, 0.0f, 0.0f},
				COLOR_CONSTLINE =	{0.0f, 0.5f, 0.5f},
				COLOR_SUN =			{1.0f, 1.0f, 1.0f},
				COLOR_SKY =			{0.0f, 0.0f, 0.6f},
				COLOR_NORTHSTAR =	{0.7f, 1.0f, 0.7f};


// FUNCTIONS
void glColor( color_s c )   // Convinience function for glColor3f
{
	glColor3f( c.r, c.g, c.b );
}

BOOL LoadTGA( UINT &texID, char* filename )
{
	// Temporary texture for data storage
	texture_s texture;

	// Every TGA file has this header
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};

	// Used to compare file header with TGAheader
	GLubyte		fileHeader[12];

	// Width, Height, and bpp information
	GLubyte		imageInfo[6];
	GLuint		bitsPerPixel;
	GLuint		bytesPerPixel;

	// Size of image data in bytes
	GLuint		imageSize;

	// RGBA is 32 bits per pixel; RGB is 24 bits per pixel
	GLuint		type=GL_RGBA;

	// Open for binary reading
	FILE *file = fopen(filename, "rb");

	if(	file==NULL ||
		fread(fileHeader,1,sizeof(fileHeader),file)!=sizeof(fileHeader) ||	// Make sure the header is there
		memcmp(TGAheader,fileHeader,sizeof(TGAheader))!=0				||	// Make sure the header is a TGA header
		fread(imageInfo,1,sizeof(imageInfo),file)!=sizeof(imageInfo))		// Make sure the image information is there
	{
		if (file == NULL)
			return FALSE;
		else
		{
			fclose(file);
			delete file;
			return FALSE;
		}
	}

	// Image width = highbyte*256 + lowbyte
	texture.width  = imageInfo[1] * 256 + imageInfo[0];
	// Image height = highbyte*256 + lowbyte
	texture.height = imageInfo[3] * 256 + imageInfo[2];

	bitsPerPixel	= imageInfo[4];
	bytesPerPixel	= bitsPerPixel/8;

	imageSize		= texture.width*texture.height*bytesPerPixel;
   
 	if(	texture.width	<=0	||
		texture.height	<=0	||
		(imageInfo[4]!=24 && imageInfo[4]!=32))				// Make sure TGA is 24 or 32 bits per pixel
	{
		fclose(file);
		return FALSE;
	}

	// Reserve memory to hold the image data
	texture.data = new GLubyte [imageSize];

	if(	texture.data==NULL ||									// Make sure the memory was reserved
		fread(texture.data, 1, imageSize, file)!=imageSize )	// Make sure image data size matches imageSize
	{
		// If memory was reserved, free it
		if(texture.data!=NULL)
			delete texture.data;

		fclose(file);
		delete file;
		return FALSE;
	}

	// GL uses RGB, TGA uses BGR so we must swap Red and Blue
	GLubyte temp;
	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)
	{
		temp=texture.data[i];
		texture.data[i] = texture.data[i + 2];
		texture.data[i + 2] = temp;
	}

	fclose (file);											// Close The File

	glGenTextures(1, &texture.id);

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	if (bitsPerPixel==24)
	{
		type=GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture.width, texture.height, 0, type, GL_UNSIGNED_BYTE, texture.data);

	texID = texture.id;

	delete texture.data;

	return TRUE;
}

void SetState( enum state_e s )
{
	// Clear the first star number in the view
	((CConStationFrame*)AfxGetMainWnd())->GetView()->ClearFirstStar();

	state = s;
}

// TIME CONSUMING, SHOULD BE CALLED SPARINGLY
void RedrawView()
{
	((CConStationFrame*)AfxGetMainWnd())->GetView()->Redraw();
}
