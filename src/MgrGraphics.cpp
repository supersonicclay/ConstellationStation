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
	glClearDepth( 1.0f );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
///	glEnable( GL_LINE_SMOOTH );
	glShadeModel( GL_SMOOTH );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glEnable( GL_BLEND );
	glEnable( GL_CULL_FACE );
	glEnable( GL_TEXTURE_2D );

	// Fog
	glFogi( GL_FOG_MODE, GL_EXP2  );
	glFogf( GL_FOG_DENSITY, 1.0f );
	glHint( GL_FOG_HINT, GL_FASTEST );
	glFogf( GL_FOG_START, 0.75f );
	glFogf( GL_FOG_END, 1.0f );

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
// CMgrGraphics drawing

// Main draw function
void CMgrGraphics::Draw()
{

	UpdateMats();
	UpdateDayFactor();
	UpdateDayAlpha();
	UpdateColors();

	glClearColor( skyColor.r, skyColor.g, skyColor.b, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if( starfield.IsSunShining() )
	{
		glLoadMatrixf( skyMat.getFloats() );
		DrawSky();

		glLoadMatrixf( sunMat.getFloats() );
		DrawSunlight();
	}

	glLoadMatrixf( starfMat.getFloats() );

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
		glLoadMatrixf( sunMat.getFloats() );
		DrawSun();
	}

	if( optionsMgr.IsTerrVisible() )
	{
		glLoadMatrixf( terrainMat.getFloats() );
		DrawTerrain();
	}

	// Draw heading indicator
	DrawCompass();

#ifdef _DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		CSDebug( "There has been an OpenGL error somewhere.", "CMgrGraphics::Draw" );
		exit(0);
	}
#endif

	SwapBuffers( hDC );
}

// Draw terrain
void CMgrGraphics::DrawTerrain()
{
	glEnable( GL_DEPTH_TEST );
	if( terrFog ) glEnable( GL_FOG ); ///
	glDisable( GL_BLEND );
	if( !optionsMgr.IsTerrTextured() )
		glDisable( GL_TEXTURE_2D );

	if( starfield.IsSunShining() )
		glEnable( GL_LIGHTING );

	// Select terrain color
	if( optionsMgr.IsTerrTextured() )
		SelectColor( COLOR_WHITE );
	else
	{
		// Set color darker if sunshine is off
		if( starfield.IsSunShining() )
			SelectColor( optionsMgr.GetTerrColor() );
		else
			SelectColor( optionsMgr.GetTerrColor()*0.3f );
	}

	float x, z;    // Coordinates
	float cInc;    // Coordinates increment
	int i, j;      // Array index
	int iInc;      // Array index increment
	vector3 n;     // Normal

	float**   heights      = terrain.GetHeights();
	vector3** upperNormals = terrain.GetUpperNormals();
	vector3** lowerNormals = terrain.GetLowerNormals();
	int       arraySize    = terrain.GetArraySize();
	int       size         = terrain.GetSize();
	int       texIters     = optionsMgr.GetTerrTexIters();
	int       heightIters  = optionsMgr.GetTerrHeightIters();
	float     r            = optionsMgr.GetTerrRoughness();
	float     scale        = optionsMgr.GetTerrScale();
	float     scale2       = scale*2;

	iInc = (1<<(texIters-heightIters));

	x = -scale;
	z = scale;
	cInc = (float)pow(2, -heightIters+1)*scale;

	glPushName( 0 );

	glBindTexture( GL_TEXTURE_2D, terrain.GetTexID() );
///	SelectColor( COLOR_WHITE );
///	glDisable( GL_LIGHTING );

	for( i=0; i<size; i+=iInc )
	{
		for( j=0; j<size; j+=iInc )
		{
			// Draw upper triangle
///			n = upperNormals[i][j];
			n = vector3(0,1,0);
			glBegin( GL_TRIANGLES );
				glNormal3f( n.x, n.y, n.z );

				glTexCoord2f( (float)(i     )/size, (float)(j     )/size );
				  glVertex3f( x     , heights[i     ][j     ]*r, z      );
				glTexCoord2f( (float)(i+iInc)/size, (float)(j+iInc)/size );
				  glVertex3f( x+cInc, heights[i+iInc][j+iInc]*r, z-cInc );
				glTexCoord2f( (float)(i     )/size, (float)(j+iInc)/size );
				  glVertex3f( x     , heights[i     ][j+iInc]*r, z-cInc );

			glEnd();

			/// DRAW UPPER NORMALS
//			glDisable( GL_LIGHTING );
//			glColor3f(0,1,0);
//			glBegin( GL_LINES );
//				glVertex3f( x    , heights[i][j]*r    , z     );
//				glVertex3f( x+n.x, heights[i][j]*r+n.y, z+n.z );
//			glEnd();
//			glEnable( GL_LIGHTING );
//			SelectColor( optionsMgr.GetTerrColor() );

			// Draw lower triangle
///			n = lowerNormals[i][j];
			n = vector3(0,1,0);
			glBegin( GL_TRIANGLES );
				glNormal3f( n.x, n.y, n.z );

				glTexCoord2f( (float)(i     )/size, (float)(j     )/size );
				  glVertex3f( x     , heights[i     ][j     ]*r, z      );
				glTexCoord2f( (float)(i+iInc)/size, (float)(j     )/size );
				  glVertex3f( x+cInc, heights[i+iInc][j     ]*r, z      );
				glTexCoord2f( (float)(i+iInc)/size, (float)(j+iInc)/size );
				  glVertex3f( x+cInc, heights[i+iInc][j+iInc]*r, z-cInc );

			glEnd();

			z -= cInc;
		}
		z = scale;
		x += cInc;
	}
	glPopName();

	/// Draw Terrain texture below terrain
	SelectColor( COLOR_WHITE );
	glBindTexture( GL_TEXTURE_2D, terrain.GetTexID() );
	glBegin( GL_QUADS );
		glTexCoord2i(1,1); glVertex3f(  scale,-0.5f,-scale );
		glTexCoord2i(0,1); glVertex3f( -scale,-0.5f,-scale );
		glTexCoord2i(0,0); glVertex3f( -scale,-0.5f, scale );
		glTexCoord2i(1,0); glVertex3f(  scale,-0.5f, scale );
	glEnd();

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glDisable( GL_FOG );
	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );
}

// Draw sky (not including stars and sun). Must be done before any other drawing
void CMgrGraphics::DrawSky()
{
	// DRAW SUNRISE/SUNSET GRADIENT
	glBlendFunc( GL_ONE, GL_ONE ); /// for it to work with sphere texture
	glDisable( GL_CULL_FACE );
	glBindTexture( GL_TEXTURE_2D, skyTex );
	SelectColor( redColor );
	gluSphere( skySphere, 1.0f, 20, 5 );
	glEnable( GL_CULL_FACE );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}

// Draw sun
void CMgrGraphics::DrawSun()
{
	CDataSun* sun = starfield.GetSun();
	vector3 center = sun->GetCenter();

	// Get vertices
	vector3 trVert = sun->GetTRVert();
	vector3 tlVert = sun->GetTLVert();
	vector3 blVert = sun->GetBLVert();
	vector3 brVert = sun->GetBRVert();

	//-------------
	// Draw Corona
	//-------------
	glBindTexture( GL_TEXTURE_2D, sunCoronaTex );
	SelectColor( sun->GetColor() );

	// Draw a star quad counterclockwise
	glBegin( GL_QUADS );
		glTexCoord2i(1,1); glVertex3f( trVert.x, trVert.y, trVert.z );
		glTexCoord2i(0,1); glVertex3f( tlVert.x, tlVert.y, tlVert.z );
		glTexCoord2i(0,0); glVertex3f( blVert.x, blVert.y, blVert.z );
		glTexCoord2i(1,0); glVertex3f( brVert.x, brVert.y, brVert.z );
	glEnd();


	//-----------
	// Draw Body
	//-----------
	glBindTexture( GL_TEXTURE_2D, sunBodyTex );
	SelectColor( COLOR_WHITE );
	glBlendFunc( GL_DST_COLOR, GL_ZERO );
	// Draw a star quad counterclockwise
	glBegin( GL_QUADS );
		glTexCoord2i(1,1); glVertex3f( trVert.x, trVert.y, trVert.z );
		glTexCoord2i(0,1); glVertex3f( tlVert.x, tlVert.y, tlVert.z );
		glTexCoord2i(0,0); glVertex3f( blVert.x, blVert.y, blVert.z );
		glTexCoord2i(1,0); glVertex3f( brVert.x, brVert.y, brVert.z );
	glEnd();
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );


	//-----------
	// Draw Glow
	//-----------
	if( starfield.IsSunShining() && optionsMgr.IsTerrVisible() )
	{
		glDisable( GL_CULL_FACE );
		glBindTexture( GL_TEXTURE_2D, sunGlowTex );

		SelectColor( redColor );

		// Load view matrix and work in world coordinates
		glLoadMatrixf( starfield.GetViewMat()->getFloats() );

		// Get world coordinates of sun center
		vector3 wc = *(starfield.GetStarfMat()) * *(starfield.GetSun()->GetTimeMat()) * center;

		float glowSize = 3.5f;
		glBegin( GL_QUADS );
			// Draw big glow
			glTexCoord2i(1,1); glVertex3f( wc.x, wc.y+glowSize, wc.z+glowSize );
			glTexCoord2i(0,1); glVertex3f( wc.x, wc.y+glowSize, wc.z-glowSize );
			glTexCoord2i(0,0); glVertex3f( wc.x, wc.y-glowSize, wc.z-glowSize );
			glTexCoord2i(1,0); glVertex3f( wc.x, wc.y-glowSize, wc.z+glowSize );

			// Draw smaller glow
			glTexCoord2i(1,1); glVertex3f( wc.x, wc.y+glowSize/3, wc.z+glowSize/2 );
			glTexCoord2i(0,1); glVertex3f( wc.x, wc.y+glowSize/3, wc.z-glowSize/2 );
			glTexCoord2i(0,0); glVertex3f( wc.x, wc.y-glowSize/3, wc.z-glowSize/2 );
			glTexCoord2i(1,0); glVertex3f( wc.x, wc.y-glowSize/3, wc.z+glowSize/2 );

			// Draw smallest glow just red
			color_s justRed = redColor;
			justRed.g = 0.0f;
			SelectColor( justRed );
			glTexCoord2i(1,1); glVertex3f( wc.x, wc.y+glowSize/3, wc.z+glowSize/4 );
			glTexCoord2i(0,1); glVertex3f( wc.x, wc.y+glowSize/3, wc.z-glowSize/4 );
			glTexCoord2i(0,0); glVertex3f( wc.x, wc.y-glowSize/3, wc.z-glowSize/4 );
			glTexCoord2i(1,0); glVertex3f( wc.x, wc.y-glowSize/3, wc.z+glowSize/4 );
		glEnd();

		glEnable( GL_CULL_FACE );
	}
}

/// LIGHTING NEEDS WORK
void CMgrGraphics::DrawSunlight()
{
	// Update sunlight (GL_LIGHT0)
	float light[4];
	light[0] = 1.0f;
	light[1] = 1.0f;
	light[2] = 1.0f;
	light[3] = 1.0f;
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light );

	vector3 pos = starfield.GetSun()->GetCenter();
	glLightfv( GL_LIGHT0, GL_POSITION, pos.getFloats() );
}

// Draw all constellations
void CMgrGraphics::DrawConsts()
{
	glDisable( GL_TEXTURE_2D );
	glLineWidth( optionsMgr.GetConstLineWidth() );

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
	glEnable( GL_TEXTURE_2D );
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
	SelectColor4( optionsMgr.GetConstNormColor(), constAlpha );

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
	// Set color for lines
	SelectColor4( optionsMgr.GetConstActiveColor(), constAlpha );

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

	// Draw constellation lines
	for( int lineIndex=0; lineIndex<lineCount; lineIndex++ )
	{
		// Set color if this is an active line
		if( lineIndex == curConst->GetActiveLineNum() &&
			state == state_DeletingLine )
			SelectColor4( optionsMgr.GetConstActiveColor(), constAlpha );
		else
			SelectColor4( optionsMgr.GetConstSelColor(), constAlpha );

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
	}
	else
	{
		glDisable( GL_TEXTURE_2D );

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

		glEnable( GL_TEXTURE_2D );
	}
}

// Draw star i as a textured quad
void CMgrGraphics::DrawStarQuad( int i )
{
	CDataStar* curStar = starfield.GetStar(i);

	// Find color for this star
	if( starfield.AreConstsVisible() && optionsMgr.AreConstStarsColored() &&
		starfield.IsStarInHiddenConst(i) )
		SelectColor4( optionsMgr.GetConstStarColor(), starAlpha );
	else
		SelectColor4( curStar->GetColor(), starAlpha );

	// Get vertices
	vector3 trVert = curStar->GetTRVert();
	vector3 tlVert = curStar->GetTLVert();
	vector3 blVert = curStar->GetBLVert();
	vector3 brVert = curStar->GetBRVert();

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
		SelectColor4( optionsMgr.GetConstStarColor(), starAlpha );
	else
		SelectColor4( curStar->GetColor(), starAlpha );

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
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );

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
	SelectColor( DEF_COMPASS_CROSSCOLOR );
	glBegin( GL_LINES );
		glVertex3f ( 1.0f, 0.0f, 0.0f);
		glVertex3f (-1.0f, 0.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f, 1.0f);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	// North Star Pointer
	glMultMatrixf( starfield.GetLatMat()->getFloats() );
	SelectColor( DEF_COMPASS_NEEDLECOLOR );
	glBegin( GL_LINES );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 1.0f, 0.0f );
	glEnd();

	// Pop Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	// Switch back to Model View
	glMatrixMode( GL_MODELVIEW );

	glDisable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glEnable( GL_TEXTURE_2D );
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
	fov = ( 1 - starfield.GetZoom() ) * 45;

	gluPerspective( fov, (float)width / (float)height, 0.001f, 10.0f );
}

// Update all matrices
void CMgrGraphics::UpdateMats()
{
	UpdateStarfMat();
	UpdateSkyMat();
	UpdateSunMat();
	UpdateTerrainMat();
}

// Update matrix for sky
void CMgrGraphics::UpdateSkyMat()
{
	skyMat = *(starfield.GetViewMat());
	skyMat *= RotateRadMatrix44( 'x', -PIHALF );
}

// Update matrix for starfield objects (stars, constellations, sun)
void CMgrGraphics::UpdateStarfMat()
{
	starfMat = *(starfield.GetViewMat());
	starfMat *= *(starfield.GetStarfMat());
}

// Update matrix for sun (starfield matrix must be updated first)
void CMgrGraphics::UpdateSunMat()
{
	sunMat = starfMat;
	sunMat *= *(starfield.GetSun()->GetTimeMat());
}

// Update matrix for terrain
void CMgrGraphics::UpdateTerrainMat()
{
	terrainMat = TranslateMatrix44( 0.0f, -terrain.GetViewHeight(), -terrain.GetViewDistance() );///
	if( terrExternal )///
		terrainMat *= TranslateMatrix44( 0.0f, 0.0f, -2.5f );
	terrainMat *= *(starfield.GetViewMat());
}


/////////////////////////////////////////////////////////////////////////////
// Daylight

// Update daylight factor
void CMgrGraphics::UpdateDayFactor()
{
	// Just set to -2 if
	if( !starfield.IsSunShining() || !optionsMgr.IsTerrVisible() )
	{
		dayFactor = -2.0f;
		return;
	}

	// Uses the sun's center.y as input to the function:
	//  f(x) = 7.5x

	// full night while dayFactor <= -2 (center.y <= -0.27)
	// full  day  while dayFactor >=  2 (center.y >=  0.27)
	// sun is at horizon when dayFactor = 0 (center.y = 0)

	// Find center of sun
	vector3 center = *(starfield.GetStarfMat()) *
	                 *(starfield.GetSun()->GetTimeMat()) *
	                 starfield.GetSun()->GetCenter();

	// Find factor
	dayFactor = center.y*7.5f;
}

// Update day alpha; 0 = day; 1 = night
void CMgrGraphics::UpdateDayAlpha()
{
	// Determine alpha based on dayFactor
	dayAlpha = -dayFactor/2;
	if( dayAlpha < 0.0f ) dayAlpha = 0.0f;
	else if( dayAlpha > 1.0f ) dayAlpha = 1.0f;

	// Stars get dimmer faster
	dayAlpha = dayAlpha * dayAlpha * dayAlpha * dayAlpha * dayAlpha;

	// Set stars' alpha value
	starAlpha = dayAlpha;
	if( starfield.AreStarsDaylight() )
		starAlpha = 1.0f;
	constAlpha = dayAlpha;
	if( starfield.AreConstsDaylight() )
		constAlpha = 1.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Colors

// Update all common colors
void CMgrGraphics::UpdateColors()
{
	// SET SKY COLOR
	if( starfield.IsSunShining() )
	{
		float skyFactor = (dayFactor+2)*0.25f;
		if( skyFactor > 1.0f ) skyFactor = 1.0f;
		else if( skyFactor < 0.0f ) skyFactor = 0.0f;
		skyColor = DEF_SKY_COLOR;
		skyColor.r *= skyFactor;
		skyColor.g *= skyFactor;
		skyColor.b *= skyFactor;
	}
	else
		skyColor = COLOR_BLACK;

	// SET RED COLOR
	if( starfield.IsSunShining() )
	{
		float redFactor;
		if( dayFactor > 2.0f || dayFactor < -2.0f )
			redFactor = 0;
		else
			redFactor = (float) cos( dayFactor*PI/2)/2 + 0.5;
		redColor.r = redFactor/2;
		redColor.g = redFactor/8;
		redColor.b = 0.0f;
	}
	else
		redColor = COLOR_BLACK;

	// SET FOG COLOR
	// Fog color is weighted average of clearColor and redddish
	float fogColor[4];
#if 0  /// fog color test
	fogColor[0] = (skyColor.r+skyColor.r+redColor.r)/3;
	fogColor[1] = (skyColor.g+skyColor.g+redColor.g)/3;
	fogColor[2] = (skyColor.b+skyColor.b+redColor.b)/3;
#else
	fogColor[0] = skyColor.r;
	fogColor[1] = skyColor.g;
	fogColor[2] = skyColor.b;
#endif
	fogColor[3] = 1.0f;
	glFogfv(GL_FOG_COLOR, fogColor);
}

// Convenience function for glColor3f
void CMgrGraphics::SelectColor( color_s c )
{
	glColor3f( c.r, c.g, c.b );
}

// Convenience function for glColor4f
void CMgrGraphics::SelectColor4( color_s c, float a )
{
	glColor4f( c.r, c.g, c.b, a );
}


/////////////////////////////////////////////////////////////////////////////
// Textures

// Load a TGA file and put associated texture in tex. Returns TRUE on success.
BOOL CMgrGraphics::LoadTexture( UINT& texID, char* filename )
{
	texture_s tex;

	if( !LoadTGA( tex, filename ) )
		return FALSE;

	glGenTextures( 1, &tex.id );

	glBindTexture( GL_TEXTURE_2D, tex.id );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, tex.type, tex.width, tex.height, 0, tex.type, GL_UNSIGNED_BYTE, tex.data );

	texID = tex.id;

	delete tex.data;

	return TRUE;
}

// Load a TGA file and put associated texture in tex. Returns TRUE on success.
BOOL CMgrGraphics::LoadTGA( texture_s& tex, char* filename )
{
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
	tex.type=GL_RGBA;

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
	tex.width  = imageInfo[1] * 256 + imageInfo[0];
	// Image height = highbyte*256 + lowbyte
	tex.height = imageInfo[3] * 256 + imageInfo[2];

	bitsPerPixel	= imageInfo[4];
	bytesPerPixel	= bitsPerPixel/8;

	imageSize		= tex.width*tex.height*bytesPerPixel;

 	if(	tex.width	<=0	||
		tex.height	<=0	||
		(imageInfo[4]!=24 && imageInfo[4]!=32))				// Make sure TGA is 24 or 32 bits per pixel
	{
		fclose(file);
		return FALSE;
	}

	// Reserve memory to hold the image data
	tex.data = new GLubyte [imageSize];

	if(	tex.data==NULL ||									// Make sure the memory was reserved
		fread(tex.data, 1, imageSize, file)!=imageSize )	// Make sure image data size matches imageSize
	{
		// If memory was reserved, free it
		if(tex.data!=NULL)
			delete tex.data;

		fclose(file);
		delete file;
		return FALSE;
	}

	// GL uses RGB, TGA uses BGR so we must swap Red and Blue
	GLubyte temp;
	for( GLuint i=0; i<int(imageSize); i+=bytesPerPixel )
	{
		temp=tex.data[i];
		tex.data[i] = tex.data[i + 2];
		tex.data[i + 2] = temp;
	}

	fclose (file);											// Close The File

	if( bitsPerPixel==24 )
		tex.type=GL_RGB;

	return TRUE;
}

// Load all textures used by graphics manager
BOOL CMgrGraphics::LoadTextures()
{
	if( !LoadTexture( starTex, "data/star.tga" ) )
	{
		CSDebug( "Unable to load star texture", "CMgrGraphics::LoadTextures" );
		return FALSE;
	}

	if( !LoadTexture( sunCoronaTex, "data/sunCorona.tga" ) )
	{
		CSDebug( "Unable to load sun corona texture", "CMgrGraphics::LoadTextures" );
		return false;
	}

	if( !LoadTexture( sunBodyTex, "data/sunBody.tga" ) )
	{
		CSDebug( "Unable to load sun body texture", "CMgrGraphics::LoadTextures" );
		return false;
	}

	if( !LoadTexture( sunGlowTex, "data/sunGlow.tga" ) )
	{
		CSDebug( "Unable to load sun glow texture", "CMgrGraphics::LoadTextures" );
		return false;
	}

	if( !LoadTexture( skyTex, "data/sky.tga" ) )
	{
		CSDebug( "Unable to load sky texture", "CMgrGraphics::LoadTextures" );
		return FALSE;
	}

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );

	if( !terrain.LoadTextures() )
	{
		CSDebug( "Unable to load terrain textures", "CMgrGraphics::LoadTextures" );
		return FALSE;
	}

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





