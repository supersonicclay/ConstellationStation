//===========================================================================
// MgrGraphics.cpp
//
// CMgrGraphics
//   handles all OpenGL graphics.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "MgrGraphics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrGraphics::CMgrGraphics()
{
}

CMgrGraphics::~CMgrGraphics()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Destroy the rendering context
void CMgrGraphics::Destroy() 
{
	//Make the RC non-current
	if( wglMakeCurrent(0,0) == FALSE )
	{
		CSDebug( "Could not make RC non-current", "CMgrGraphics::Destroy" );
		exit(0);
		return;
	}
	
	//Delete the RC
	if( wglDeleteContext(hRC)==FALSE )
	{
		CSDebug("Could not delete RC", "CMgrGraphics::Destroy" );
		exit(0);
		return;
	}
}


/////////////////////////////////////////////////////////////////////////////
// OpenGL Initialization

// Main initialization function
BOOL CMgrGraphics::InitializeOpenGL()
{
	// Get a DC for the Client Area
	hDC = GetView()->GetDC()->GetSafeHdc();
	if( hDC == NULL )
	{
		CSDebug( "Error Obtaining DC", "CMgrGraphics::InitializeOpenGL" );
		return FALSE;
	}

	// Try setting up pixel format
	if( !SetupPixelFormat() )
	{
		CSDebug( "Error setting up pixel format", "CMgrGraphics::InitializeOpenGL" );
		return FALSE;
	}

	// Create Rendering Context
	hRC = wglCreateContext( hDC );
	if( hRC == 0 )
	{
		CSDebug( "Error Creating RC", "CMgrGraphics::InitializeOpenGL" );
		return FALSE;
	}

	// Make the RC Current
	if( wglMakeCurrent( hDC, hRC ) == FALSE )
	{
		CSDebug( "Error making RC Current", "CMgrGraphics::InitializeOpenGL" );
		return FALSE;
	}

	// Try loading textures
	if( !LoadTextures() )
	{
		CSDebug( "Error loading textures", "CMgrGraphics::InitializeOpenGL" );
		return FALSE;
	}

	// Sky
	skySphere = gluNewQuadric();
	gluQuadricNormals( skySphere, GLU_SMOOTH );
	gluQuadricTexture( skySphere, GL_TRUE );

	// Sun
	sunSphere = gluNewQuadric();
	glEnable( GL_LIGHT0 );

	// Settings
	glClearColor( 0.0f,0.0f,0.0f,1.0f );
	glClearDepth( 1.0f );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glEnable( GL_LINE_SMOOTH );
	glShadeModel( GL_SMOOTH );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glEnable( GL_CULL_FACE );

	// Material
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable( GL_COLOR_MATERIAL );

	return TRUE;
}

// Setup pixel format
BOOL CMgrGraphics::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |		    // support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int pixelFormat = ChoosePixelFormat( hDC, &pfd );

	if( pixelFormat == 0 )
	{
		CSDebug( "Couldn't Choose Pixel Format", "CMgrGraphics::SetupPixelFormat" );
		return FALSE;
	}

	if( SetPixelFormat(hDC, pixelFormat, &pfd) == FALSE )
	{
		CSDebug( "Couldn't Set Pixel Format", "CMgrGraphics::SetupPixelFormat" );
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Colors

// Convinience function for glColor3f
void CMgrGraphics::SetColor( color_s c )
{
	glColor3f( c.r, c.g, c.b );
}


/////////////////////////////////////////////////////////////////////////////
// Textures

// Load a TGA file and put its OpenGL id in texID. Returns TRUE on success.
BOOL CMgrGraphics::LoadTGA( UINT &texID, char* filename )
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
	FILE *file = fopen( filename, "rb" );

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
	for( GLuint i=0; i<int(imageSize); i+=bytesPerPixel )
	{
		temp=texture.data[i];
		texture.data[i] = texture.data[i + 2];
		texture.data[i + 2] = temp;
	}

	fclose (file);											// Close The File

	glGenTextures( 1, &texture.id );

	glBindTexture( GL_TEXTURE_2D, texture.id );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	if( bitsPerPixel==24 )
		type=GL_RGB;

	glTexImage2D( GL_TEXTURE_2D, 0, type, texture.width, texture.height, 0, type, GL_UNSIGNED_BYTE, texture.data );

	texID = texture.id;

	delete texture.data;

	return TRUE;
}

// Load all textures used by graphics manager
BOOL CMgrGraphics::LoadTextures()
{
	if( !LoadTGA(starTex, "data/star.tga") )
	{
		CSDebug( "Unable to load star texture", "CMgrGraphics::LoadTextures" );
		return FALSE;
	}

	if( !LoadTGA(skyTex, "data/sky.tga") )
	{
		CSDebug( "Unable to load sky texture", "CMgrGraphics::LoadTextures" );
		return FALSE;
	}

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Frustum

// Frustum sides (for easy readability)
enum FrustumSide
{
	RIGHT	= 0,
	LEFT	= 1,
	BOTTOM	= 2,
	TOP		= 3,
	BACK	= 4,
	FRONT	= 5	
}; 

// Plane coefficients (again, for readability)
enum PlaneCoeff
{
	A = 0,				// The X value of the plane's normal
	B = 1,				// The Y value of the plane's normal
	C = 2,				// The Z value of the plane's normal
	D = 3				// The distance the plane is from the origin
};

// Calculate frustum dimensions based on current modelview and projection matrices
void CMgrGraphics::CalculateFrustum()
{
	float   proj[16];								// This will hold our projection matrix
	float   modl[16];								// This will hold our modelview matrix
	float   clip[16];								// This will hold the clipping frustum

	// glGetFloatv() is used to extract information about our OpenGL world.
	// Below, we pass in GL_PROJECTION_MATRIX to abstract our projection matrix.
	// It then stores the matrix into an array of [16].
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	// By passing in GL_MODELVIEW_MATRIX, we can abstract our model view matrix.
	// This also stores it in an array of [16].
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	// Now that we have our modelview and projection matrix, if we combine these 2 matrices,
	// it will give us our clipping frustum.  To combine 2 matrices, we multiply them.

	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];
	
	// Now we actually want to get the sides of the frustum.  To do this we take
	// the clipping frustum we received above and extract the sides from them.

	matrix44   proj2 = proj;								// This will hold our projection matrix
	matrix44   modl2;								// This will hold our modelview matrix
	matrix44   clip2;								// This will hold the clipping frustum

	// This will extract the RIGHT side of the frustum
	frustum[RIGHT][A] = clip[ 3] - clip[ 0];
	frustum[RIGHT][B] = clip[ 7] - clip[ 4];
	frustum[RIGHT][C] = clip[11] - clip[ 8];
	frustum[RIGHT][D] = clip[15] - clip[12];

	// Now that we have a normal (A,B,C) and a distance (D) to the plane,
	// we want to normalize that normal and distance.

	// Normalize the RIGHT side
	frustum[RIGHT].normalize();

	// This will extract the LEFT side of the frustum
	frustum[LEFT][A] = clip[ 3] + clip[ 0];
	frustum[LEFT][B] = clip[ 7] + clip[ 4];
	frustum[LEFT][C] = clip[11] + clip[ 8];
	frustum[LEFT][D] = clip[15] + clip[12];

	// Normalize the LEFT side
	frustum[LEFT].normalize();

	// This will extract the BOTTOM side of the frustum
	frustum[BOTTOM][A] = clip[ 3] + clip[ 1];
	frustum[BOTTOM][B] = clip[ 7] + clip[ 5];
	frustum[BOTTOM][C] = clip[11] + clip[ 9];
	frustum[BOTTOM][D] = clip[15] + clip[13];

	// Normalize the BOTTOM side
	frustum[BOTTOM].normalize();

	// This will extract the TOP side of the frustum
	frustum[TOP][A] = clip[ 3] - clip[ 1];
	frustum[TOP][B] = clip[ 7] - clip[ 5];
	frustum[TOP][C] = clip[11] - clip[ 9];
	frustum[TOP][D] = clip[15] - clip[13];

	// Normalize the TOP side
	frustum[TOP].normalize();

	// This will extract the BACK side of the frustum
	frustum[BACK][A] = clip[ 3] - clip[ 2];
	frustum[BACK][B] = clip[ 7] - clip[ 6];
	frustum[BACK][C] = clip[11] - clip[10];
	frustum[BACK][D] = clip[15] - clip[14];

	// Normalize the BACK side
	frustum[BACK].normalize();

	// This will extract the FRONT side of the frustum
	frustum[FRONT][A] = clip[ 3] + clip[ 2];
	frustum[FRONT][B] = clip[ 7] + clip[ 6];
	frustum[FRONT][C] = clip[11] + clip[10];
	frustum[FRONT][D] = clip[15] + clip[14];

	// Normalize the FRONT side
	frustum[FRONT].normalize();
}

// Return whether sphere is in frustum.
BOOL CMgrGraphics::SphereInFrustum( vector3 v, float radius )
{
	// Go through all the sides of the frustum
	for( int i = 0; i < 6; ++i )	
	{
		// If the center of the sphere is farther away from the plane than the radius
		if( frustum[i][A] * v.x + frustum[i][B] * v.y + frustum[i][C] * v.z + frustum[i][D] <= -radius )
		{
			// The distance was greater than the radius so the sphere is outside of the frustum
			return FALSE;
		}
	}
	
	// The sphere was inside of the frustum!
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMgrGraphics drawing

// Main draw function
void CMgrGraphics::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	LoadSkyMat();

	if( starfield.IsSunShining() )
		DrawSky();

	LoadStarfMat();

	// Calculate frustum for star culling
	CalculateFrustum();

	// Draw starfield objects
	if( starfield.AreConstsVisible() )
		DrawConsts();
	if( starfield.AreStarsVisible() )
		DrawStars();

	// Draw sun
	if( starfield.IsSunVisible() )
	{
		LoadSunMat();
		DrawSun();
	}

	if( optionsMgr.IsTerrVisible() )
	{
		LoadTerrainMat();
		DrawTerrain();
	}

	// Draw heading indicator
	DrawCompass();

#ifdef _DEBUG
	if( glGetError() != GL_NO_ERROR )
		CSDebug( "There has been an OpenGL error somewhere.", "CMgrGraphics::Draw" );
#endif

	SwapBuffers( hDC );
}

// Draw terrain
void CMgrGraphics::DrawTerrain()
{
	glEnable( GL_DEPTH_TEST );

	if( starfield.IsSunShining() )
		glEnable( GL_LIGHTING );

	SetColor( optionsMgr.GetTerrColor() );

	int i, j;
	float x, z;
	float inc;

	float** heights = terrain.GetHeights();
	int arraySize = terrain.GetArraySize();
	int size = terrain.GetSize();

	vector3 n;

	float scale = optionsMgr.GetTerrScale();
	int iterations = optionsMgr.GetTerrIters();

	x = -scale;
	z = -scale;
	inc = (float)pow(2, -iterations+1);

	glPushName( 0 );

	for( i=0; i<size; ++i )
	{
		for( j=0; j<size; ++j )
		{
			n = terrain.GetUpperNormal( i, j );
			glBegin( GL_TRIANGLES );
				glNormal3f( n.x, n.y, n.z );
				glVertex3f( x, heights[i][j], z );
				glVertex3f( x, heights[i][j+1], z+inc );
				glVertex3f( x+inc, heights[i+1][j], z );
			glEnd();

			/*/// DRAW UPPER NORMALS
			glDisable( GL_LIGHTING );
			glColor3f(0,1,0);
			glBegin( GL_LINES );
				glVertex3f( x, heights[ i*arraySize + j ], z );
				glVertex3f( x+n.x, heights[ i*arraySize + j ]+n.y, z+n.z );
		//		glVertex3f( n.x, n.y, n.z );
			glEnd();
			glEnable( GL_LIGHTING );
			SetColor( optionsMgr.GetTerrColor() );
//			*/

			n = terrain.GetLowerNormal( i, j );
			glBegin( GL_TRIANGLES );
				glNormal3f( n.x, n.y, n.z );
				glVertex3f( x+inc, heights[i+1][j+1], z+inc );
				glVertex3f( x+inc, heights[i+1][j], z );
				glVertex3f( x, heights[i][j+1], z+inc );
			glEnd();

			z += inc;
		}
		z = -scale;
		x += inc;
	}

	glPopName();

	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );
}

// Draw sky (not including stars and sun)
void CMgrGraphics::DrawSky()
{
	// Enable texture
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, skyTex );

	// Draw sky background
	SetColor( COLOR_BLUE );
	gluSphere( skySphere, 1.0f, 20, 5 );

	glDisable( GL_TEXTURE_2D );
}

// Draw sun
void CMgrGraphics::DrawSun()
{
	// Sun Sphere
	SetColor( COLOR_WHITE );
	gluSphere( sunSphere, 0.02f, 15, 2 );

	/// LIGHTING NEEDS WORK
	float light[4];
	light[0] = 1.0f;
	light[1] = 1.0f;
	light[2] = 1.0f;
	light[3] = 1.0f;
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light );

	float pos[3];
	pos[0] = 0.0f;
	pos[1] = 1.0f;
	pos[2] = 0.0f;
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
}

// Draw all constellations
void CMgrGraphics::DrawConsts()
{
	glLineWidth(3);

	// Draw each constellation
	for( int i=0; i<starfield.GetConstCount(); ++i )
	{
		if( starfield.GetConst(i)->IsVisible() )
		{
			if( i == starfield.GetCurConstNum() )
				DrawCurConst(i);
			else
				DrawConst(i);
		}
	}
}

// Draw constellation i
void CMgrGraphics::DrawConst( int i )
{
	CDataConst* curConst = starfield.GetConst(i);
	int lineCount = curConst->GetLineCount();

	CDataStar* s1;
	CDataStar* s2;
	float x1, y1, z1, x2, y2, z2;

	// Set color for lines
	SetColor( optionsMgr.GetConstNormColor() );

	// Draw constellation lines
	for( int lineIndex=0; lineIndex<lineCount; lineIndex++ )
	{
		glPushName( 1 + MAX_STARS + (i*MAX_CONSTLINES) + lineIndex );

		s1 = starfield.GetStar( curConst->GetLine( lineIndex )->GetStar1() );
		s2 = starfield.GetStar( curConst->GetLine( lineIndex )->GetStar2() );

		x1 = s1->GetCenter().x;
		y1 = s1->GetCenter().y;
		z1 = s1->GetCenter().z;
		x2 = s2->GetCenter().x;
		y2 = s2->GetCenter().y;
		z2 = s2->GetCenter().z;

		glBegin(GL_LINES);
			glVertex3f (x1, y1, z1);
			glVertex3f (x2, y2, z2);
		glEnd();

		glPopName();
	}
}

// Draw current constellation (i is used for glPushName)
void CMgrGraphics::DrawCurConst( int i )
{
	CDataConst* curConst = starfield.GetCurConst();
	int lineCount = curConst->GetLineCount();

	CDataStar* s1;
	CDataStar* s2;
	float x1, y1, z1, x2, y2, z2;

	// Draw new (proposed) line
	SetColor( optionsMgr.GetConstActiveColor() );
	if( curConst->GetNewLine()->GetStar2() != -1 )
	{
		s1 = starfield.GetStar( curConst->GetNewLine()->GetStar1() );
		s2 = starfield.GetStar( curConst->GetNewLine()->GetStar2() );

		x1 = s1->GetCenter().x;
		y1 = s1->GetCenter().y;
		z1 = s1->GetCenter().z;
		x2 = s2->GetCenter().x;
		y2 = s2->GetCenter().y;
		z2 = s2->GetCenter().z;

		glBegin( GL_LINES );
			glVertex3f( x1, y1, z1 );
			glVertex3f( x2, y2, z2 );
		glEnd();
	}

	// Set color for the rest of the lines
	SetColor( optionsMgr.GetConstSelColor() );

	// Draw constellation lines
	for( int lineIndex=0; lineIndex<lineCount; lineIndex++ )
	{
		// Set color if this is an active line
		if( lineIndex == curConst->GetActiveLineNum() &&
			state == state_DeletingLine )
			SetColor( optionsMgr.GetConstActiveColor() );
		else
			SetColor( optionsMgr.GetConstSelColor() );

		glPushName( 1 + MAX_STARS + (i*MAX_CONSTLINES) + lineIndex );

		s1 = starfield.GetStar( curConst->GetLine( lineIndex )->GetStar1() );
		s2 = starfield.GetStar( curConst->GetLine( lineIndex )->GetStar2() );

		x1 = s1->GetCenter().x;
		y1 = s1->GetCenter().y;
		z1 = s1->GetCenter().z;
		x2 = s2->GetCenter().x;
		y2 = s2->GetCenter().y;
		z2 = s2->GetCenter().z;

		glBegin(GL_LINES);
			glVertex3f (x1, y1, z1);
			glVertex3f (x2, y2, z2);
		glEnd();

		glPopName();
	}
}


// Draw all stars
void CMgrGraphics::DrawStars()
{
	if( optionsMgr.AreStarsTextured() )
	{
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
		glBindTexture( GL_TEXTURE_2D, starTex );

		// Go in reverse order so north star (star 0) is drawn last
		for( int i=starfield.GetStarCount()-1; i>=0; --i )
		{
			CDataStar* star = starfield.GetStar(i);
			// Check if in frustum
			if( SphereInFrustum( star->GetCenter(), star->GetRadius() ) )
			{
				glPushName( 1 + i );
				DrawStarQuad( i );
				glPopName();
			}
		}

		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
	}
	else
	{
		// Go in reverse order so north star (star 0) is drawn last
		for( int i=starfield.GetStarCount()-1; i>=0; --i )
		{
			CDataStar* star = starfield.GetStar(i);
			// Check if in frustum
			if( SphereInFrustum( star->GetCenter(), star->GetRadius() ) )
			{
				glPushName( 1 + i );
				DrawStarPoint( i );
				glPopName();
			}
		}
	}
}

// Draw star i as a textured quad
void CMgrGraphics::DrawStarQuad( int i )
{
	CDataStar* curStar = starfield.GetStar(i);

	// Find color for this star
	if( starfield.AreConstsVisible() && optionsMgr.AreConstStarsColored() &&
		starfield.IsStarInHiddenConst(i) )
		SetColor( optionsMgr.GetConstStarColor() );
	else
		SetColor( curStar->GetColor() );

	// Get vertices
	vector3 trVert = curStar->GetTRVert();
	vector3 tlVert = curStar->GetTLVert();
	vector3 blVert = curStar->GetBLVert();
	vector3 brVert = curStar->GetBRVert();

	/* Draw normals for star 8 ///
	if( i == 8 )
	{
		vector3 center = curStar->GetCenter();
		glDisable( GL_TEXTURE_2D );
		glDisable( GL_BLEND );
		SetColor( COLOR_GREEN );
		glLineWidth( 1 );
		glBegin( GL_LINES );
			glVertex3f( center.x, center.y, center.z );
			glVertex3f( center.x+normal.x, center.y+normal.y, center.z+normal.z );
		glEnd();
		glEnable( GL_BLEND );
		glEnable( GL_TEXTURE_2D );

		/// Find color for this star
		if( starfield.AreConstsVisible() && optionsMgr.AreConstStarsColored() &&
			starfield.IsStarInHiddenConst(i) )
			SetColor( optionsMgr.GetConstStarColor() );
		else
			SetColor( curStar->GetColor() );
	}
///	*/

	// Draw a star quad counterclockwise
	glBegin( GL_QUADS );
		glTexCoord2i( 1, 1 ); glVertex3f( trVert.x, trVert.y, trVert.z );
		glTexCoord2i( 0, 1 ); glVertex3f( tlVert.x, tlVert.y, tlVert.z );
		glTexCoord2i( 0, 0 ); glVertex3f( blVert.x, blVert.y, blVert.z );
		glTexCoord2i( 1, 0 ); glVertex3f( brVert.x, brVert.y, brVert.z );
	glEnd();
}

// Draw star i as a point
void CMgrGraphics::DrawStarPoint( int i )
{
	CDataStar* curStar = starfield.GetStar(i);

	// Find color for this star
	if( starfield.AreConstsVisible() && optionsMgr.AreConstStarsColored() &&
		starfield.IsStarInHiddenConst(i) )
		SetColor( optionsMgr.GetConstStarColor() );
	else
		SetColor( curStar->GetColor() );

	// Set point size (dependent on zoom)
	glPointSize( curStar->GetRadius()*500*(starfield.GetZoom()+2) );

	// Draw point
	glBegin( GL_POINTS );
		glVertex3f( curStar->GetCenter().x, curStar->GetCenter().y, curStar->GetCenter().z );
	glEnd();
}

// Draw the compass
void CMgrGraphics::DrawCompass()
{
	glEnable( GL_DEPTH_TEST );
	glDisable( GL_LINE_SMOOTH );

	// Set up projection
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();

	glLoadIdentity();

	// Set up the ortho view
	//  horizontal dependant on vertical
	float aspect = (float)width / (float)height;
	glOrtho( -12*aspect, 12*aspect, -2, 22, -2,2 );

	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	glMultMatrixf( starfield.GetViewMat()->getFloats() );

	// Cross
	glLineWidth(3);
	SetColor( DEF_COMPASS_CROSSCOLOR );
	glBegin( GL_LINES );
		glVertex3f ( 1.0f, 0.0f, 0.0f);
		glVertex3f (-1.0f, 0.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f, 1.0f);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	// North Star Pointer
	glMultMatrixf( starfield.GetLatMat()->getFloats() );
	SetColor( DEF_COMPASS_NEEDLECOLOR );
	glBegin( GL_LINES );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 1.0f, 0.0f );
	glEnd();

	// Pop Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	// Switch back to Model View
	glMatrixMode( GL_MODELVIEW );

	glEnable( GL_LINE_SMOOTH );
	glDisable( GL_DEPTH_TEST );
}


/////////////////////////////////////////////////////////////////////////////
// View Manipulation

// Change the size of the viewport
void CMgrGraphics::Size( int cx, int cy ) 
{
	if( cx <= 0 || cy <= 0 )
		return;

	width = cx;
	height = cy;

	glViewport( 0, 0, width, height );

	Projection();
}

// Set up projection matrix with a perspective matrix
void CMgrGraphics::Projection()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	Perspective();

	glMatrixMode( GL_MODELVIEW );
}

// Apply perspective matrix
void CMgrGraphics::Perspective()
{
	float persp = ( 1 - starfield.GetZoom() ) * 45;

	gluPerspective( persp, (float)width / (float)height, 0.001f, 10.0f );
}

// Load matrix for sky
void CMgrGraphics::LoadSkyMat()
{
	glLoadIdentity();
	glMultMatrixf( starfield.GetViewMat()->getFloats() );
	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
}

// Load matrix for starfield objects (stars, constellations)
void CMgrGraphics::LoadStarfMat()
{
	glLoadIdentity();
///	glTranslatef( 0, 0, -3 );///
	glMultMatrixf( starfield.GetViewMat()->getFloats() );
	glMultMatrixf( starfield.GetLatMat()->getFloats() );
	glMultMatrixf( starfield.GetTimeMat()->getFloats() );
}

// Load matrix for sun
void CMgrGraphics::LoadSunMat()
{
	/// Some needs to be in CDataSun
	glLoadIdentity();
	glMultMatrixf( starfield.GetViewMat()->getFloats() );
	glMultMatrixf( starfield.GetLatMat()->getFloats() );
	glMultMatrixf( starfield.GetTimeMat()->getFloats() );

	glTranslatef( 0.0f, 0.0f,-1.0f );
}

// Load matrix for terrain
void CMgrGraphics::LoadTerrainMat()
{
	glLoadIdentity();
	glMultMatrixf( starfield.GetViewMat()->getFloats() );
	glTranslatef( 0.0f, -terrain.GetViewHeight(), 0.0f );
}

