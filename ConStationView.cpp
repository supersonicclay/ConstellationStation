// ConStationView.cpp : implementation of the CConStationView class
//

#include "stdafx.h"
#include "ConStation.h"

#include "ConStationDoc.h"
#include "ConStationView.h"

#include "Starfield.h"
#include "Star.h"
#include "Constellation.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////
// CConStationView

IMPLEMENT_DYNCREATE(CConStationView, CView)

BEGIN_MESSAGE_MAP(CConStationView, CView)
	//{{AFX_MSG_MAP(CConStationView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////////
// CConStationView construction/destruction

CConStationView::CConStationView()
{
	for( int i=0; i<256; i++ )
		keyDown[i] = FALSE;

	mouseRotatingXY = false;
	mouseRotatingZ = false;
}

CConStationView::~CConStationView()
{
//	delete starTex.data;
}

BOOL CConStationView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_OWNDC ;
    cs.cx = 600;
    cs.cy = 400;

	return CView::PreCreateWindow(cs);
}


///////////////////////////////////////////////////////////////////////////////
// CConStationView diagnostics

#ifdef _DEBUG
void CConStationView::AssertValid() const
{
	CView::AssertValid();
}

void CConStationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG


///////////////////////////////////////////////////////////////////////////////
// CConStationView message handlers

int CConStationView::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Initialize OpenGL
	if (!InitializeOpenGL())
		MessageBox("Error initializing OpneGL", "ERROR");

	SetTimer( 1, 20, NULL );

	return 0;
}


void CConStationView::OnDestroy() 
{
	
	//Make the RC non-current
	if(::wglMakeCurrent (0,0) == FALSE)
	{
		MessageBox("Could not make RC non-current");
	}
	
	//Delete the rendering context
	if(::wglDeleteContext (m_hRC)==FALSE)
	{
		MessageBox("Could not delete RC");
	}

	// Delete the DC
	if(m_pDC)
	{
		delete m_pDC;
	}
	// Set it to NULL
	m_pDC = NULL;

	delete terrain;
	delete starfield;
}

BOOL CConStationView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	// Don't erase the background
}

void CConStationView::OnSize(UINT nType, int cx, int cy) 
{
	width = cx;
	height = cy;

	
	if ( width <= 0 || height <= 0)
	{
		return;
	}

    glViewport(0, 0, width, height);

	Projection ();
}


///////////////////////////////////////////////////////////////////////////////
// Open GL Initialization

BOOL CConStationView::InitializeOpenGL()
{
	// Get a DC for the Client Area
	m_pDC = new CClientDC(this);

	// Failure to Get DC
	if( m_pDC == NULL )
	{
		MessageBox("Error Obtaining DC");
		return FALSE;
	}

	// Failure to set the pixel format
	if( !SetupPixelFormat() )
	{
		return FALSE;
	}

	// Create Rendering Context
	m_hRC = wglCreateContext( m_pDC->GetSafeHdc () );

	// Failure to Create Rendering Context
	if( m_hRC == 0 )
	{
		MessageBox("Error Creating RC");
		return FALSE;
	}
	
	// Make the RC Current
	if( wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) == FALSE )
	{
		MessageBox( "Error making RC Current" );
		return FALSE;
	}

	// Settings
	glClearColor( 0.0f,0.0f,0.0f,1.0f );
	glClearDepth( 1.0f );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glEnable( GL_LINE_SMOOTH );
	glShadeModel( GL_SMOOTH );

	// Textures
	if( !LoadTextures() )
	{
		MessageBox( "Error loading textures" );
		return FALSE;
	}
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );

	// Sky
	skySphere = gluNewQuadric();
	gluQuadricNormals( skySphere, GLU_SMOOTH );
	gluQuadricTexture( skySphere, GL_TRUE );

	// Sun
	sunSphere = gluNewQuadric();
	glEnable( GL_LIGHT0 );

	// Material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	return TRUE;
}

BOOL CConStationView::SetupPixelFormat()
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

    int m_nPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if ( m_nPixelFormat == 0 )
	{
		MessageBox("Couldn't Choose Pixel Format");
		return FALSE;
	}

	if ( SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		MessageBox("Couldn't Set Pixel Format");
		return FALSE;
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// Textures

BOOL CConStationView::LoadTextures()
{
	if (!LoadTGA(starTex, "data/star.tga"))
		return FALSE;

	if (!LoadTGA(skyTex, "data/sky.tga"))
		return FALSE;

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// Frustum

void CConStationView::CalculateFrustum()
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

bool CConStationView::SphereInFrustum( float x, float y, float z, float radius ) const
{
	// Go through all the sides of the frustum
	for(int i = 0; i < 6; i++ )	
	{
		// If the center of the sphere is farther away from the plane than the radius
		if( frustum[i][A] * x + frustum[i][B] * y + frustum[i][C] * z + frustum[i][D] <= -radius )
		{
			// The distance was greater than the radius so the sphere is outside of the frustum
			return false;
		}
	}
	
	// The sphere was inside of the frustum!
	return true;
}



///////////////////////////////////////////////////////////////////////////////
// CConStationView drawing

void CConStationView::Redraw()
{
	InvalidateRect( NULL, FALSE );
}

void CConStationView::OnDraw(CDC* pDC)
{
    CPaintDC dc(this); // Needed 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CalculateFrustum();

///	DrawSky();
	DrawStarfield();
	DrawSun();
	DrawTerrain();
	DrawHeading();

	/// ACTIVE LINE ///
	// Draw Active Line
//	if (state == AddingLine && firstStarNum != -1)
//		DrawActiveLine();

	SwapBuffers(m_pDC->GetSafeHdc());

}

void CConStationView::DrawTerrain() const
{
	glEnable( GL_LIGHTING );

	glLoadIdentity();
	RotateXY();
	PositionTerrain();

	glColor( terrain->GetColor() );

	int i, j;
	float x, z;
	float inc;

	float* heights = terrain->GetHeights();
	int arraySize = terrain->GetArraySize();
	int size = terrain->GetSize();

	float* n;

	float scale = terrain->GetScale();
	int iterations = terrain->GetIterations();

	x = -scale;
	z = -scale;
	inc = (float)pow(2, -iterations+1);

	glPushName( 0 );

	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			/* /// DRAW NORMALS
			glDisable( GL_LIGHTING );
			glColor3f( 1, 0, 0 );
			glBegin(GL_LINES);
				glVertex3f( x, heights[ i*arraySize + j ], z );
				glVertex3f( x, heights[ i*arraySize + j ]+0.5f, z );
				glVertex3f( n[0], n[1], n[2] );
			glEnd();
			glEnable( GL_LIGHTING );
			*/

			n = terrain->GetUpperNormal( i, j );
			glBegin(GL_TRIANGLES);
				glNormal3f( n[0], n[1], n[2] );
				glVertex3f( x, heights[ (i*arraySize) + j ], z );
				glVertex3f( x, heights[ (i*arraySize) + (j+1) ], z+inc );
				glVertex3f( x+inc, heights[ ((i+1)*arraySize) + j ], z );
			glEnd();

			n = terrain->GetLowerNormal( i, j );
			glBegin(GL_TRIANGLES);
				glNormal3f( n[0], n[1], n[2] );
				glVertex3f( x+inc, heights[ ((i+1)*arraySize) + (j+1) ], z+inc );
				glVertex3f( x+inc, heights[ ((i+1)*arraySize) + j ], z );
				glVertex3f( x, heights[ (i*arraySize) + (j+1) ], z+inc );
			glEnd();

			z += inc;
		}
		z = -scale;
		x += inc;
	}

	glPopName();

	glDisable( GL_LIGHTING );
}

// Set the viewer on top of the midpoint of the terrain
void CConStationView::PositionTerrain() const
{
	glTranslatef( 0.0f, -terrain->GetViewHeight(), 0.0f );
}

void CConStationView::DrawSky() const
{
	glLoadIdentity();
//	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
	RotateXY();
	RotateLatitude();
	RotateTime();

	// Enable texture
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, skyTex );

	// Draw sky background
	glColor( COLOR_SKY );
	gluSphere( skySphere, 1.0f, 20, 5 );

	glDisable( GL_TEXTURE_2D );
}

void CConStationView::DrawSun() const
{
	glLoadIdentity();
	RotateXY();
	RotateLatitude();
	RotateTime();

	glTranslatef( 0.0f, 0.0f,-1.0f );

	// Sun Sphere
	glColor( COLOR_SUN );
	gluSphere( sunSphere, 0.02f, 15, 2 );

	/// LIGHTING NEEDS WORK
	float light[4];
	light[0] = 1.0f;
	light[1] = 1.0f;
	light[2] = 1.0f;
	light[3] = 1.0f;
	glLightfv( GL_LIGHT0, GL_SPECULAR, light );

	float pos[3];
	pos[0] = 0.0f;
	pos[1] = 1.0f;
	pos[2] = 0.0f;
	glLightfv( GL_LIGHT0, GL_POSITION, pos );

}

void CConStationView::DrawStarfield() const
{
	// Rotation and Zooming done in these functions

	DrawConstellations();

	DrawStars();
}

void CConStationView::DrawConstellations() const
{
	glLineWidth(3);
	glColor(COLOR_CONSTLINE);

	// Draw each constellation
	for (int i=0; i<starfield->GetNumConstellations(); i++)
	{
		if (starfield->GetConstellation(i)->IsVisible())
			DrawConstellation(i);
	}
}

void CConStationView::DrawConstellation(int i) const
{
	glLoadIdentity();

	RotateXY();
	RotateLatitude();
	RotateTime();

	CConstellation* curConstellation = starfield->GetConstellation(i);
	int numLines = curConstellation->GetNumLines();

	float x1, y1, z1, x2, y2, z2;

	for (int j=0; j<numLines; j++)
	{
		glPushName(j);
		x1 = curConstellation->GetLine(j)->GetX1();
		y1 = curConstellation->GetLine(j)->GetY1();
		z1 = curConstellation->GetLine(j)->GetZ1();
		x2 = curConstellation->GetLine(j)->GetX2();
		y2 = curConstellation->GetLine(j)->GetY2();
		z2 = curConstellation->GetLine(j)->GetZ2();
		glBegin(GL_LINES);
			glVertex3f (x1, y1, z1);
			glVertex3f (x2, y2, z2);
		glEnd();
		glPopName();
	}
}

void CConStationView::DrawStars() const
{
	glLoadIdentity();
	
	RotateXY();
	RotateLatitude();
	RotateTime();

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );

	glBindTexture( GL_TEXTURE_2D, starTex );

	// Go in reverse order so north star (star 0) is drawn last
	for (int i=starfield->GetNumStars()-1; i>=0; i--)
	{
		CStar* star = starfield->GetStar(i);
		// Check if in frustum
		if( SphereInFrustum( star->GetX(), star->GetY(), star->GetZ(), star->GetRadius() ) )
		{
			glPushName( i+1 );
			DrawStar( i );
			glPopName();
		}
	}

	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
}

void CConStationView::DrawStar(int i) const
{
	CStar* curStar = starfield->GetStar(i);
	color_s color;

	bool active = false;

	// Determine if this star is active (part of the current constellation)
	if (starfield->GetNumConstellations() > 0)
	{
		for (int lineIndex=0; lineIndex < starfield->GetCurConstellation()->GetNumLines(); lineIndex++)
		{
			if (curStar == starfield->GetCurConstellation()->GetLine(lineIndex)->GetStar1() ||
				curStar == starfield->GetCurConstellation()->GetLine(lineIndex)->GetStar2())
			{
				active = true;
				break;
			}
		}
	}

	if (active)
		color = COLOR_ACTIVESTAR;
	else
		color = curStar->GetColor();

	// Push matrix so quad rotation doesn't affect anything
	glPushMatrix();

	// Now we're ready to draw the star
	glColor (color);

	glRotatef( curStar->GetTheta(),  0.0f, 1.0f, 0.0f );
	glRotatef( curStar->GetPhi(), 1.0f, 0.0f, 0.0f );
	glTranslatef( 0.0f, 1.0f, 0.0f );

	// Draw a star quad
	float quadSize = curStar->GetRadius();
	glBegin( GL_QUADS );
		glNormal3f( 0.0f,-1.0f, 0.0f );
		glTexCoord2i( 0, 1 ); glVertex3f( -quadSize, 0.0f,  quadSize );
		glTexCoord2i( 1, 1 ); glVertex3f(  quadSize, 0.0f,  quadSize );
		glTexCoord2i( 1, 0 ); glVertex3f(  quadSize, 0.0f, -quadSize );
		glTexCoord2i( 0, 0 ); glVertex3f( -quadSize, 0.0f, -quadSize );
	glEnd();

	glPopMatrix();
}

void CConStationView::DrawHeading() const
{
	glEnable(GL_DEPTH_TEST);
	glDisable( GL_LINE_SMOOTH );

	// Set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();

	// Set up the ortho view
	//  horizontal dependant on vertical
	float aspect = (float)width / (float)height;
	glOrtho(-12*aspect, 12*aspect, -2, 22, -2,2);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	RotateXY();

	// Cross
	glLineWidth(3);
	glColor (COLOR_CROSS);
	glBegin(GL_LINES);
		glVertex3f ( 1.0f, 0.0f, 0.0f);
		glVertex3f (-1.0f, 0.0f, 0.0f);
		//glVertex3f ( 0.0f, 1.0f, 0.0f);
		//glVertex3f ( 0.0f,-1.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f, 1.0f);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	// North Star Pointer
	RotateLatitude();
	glColor (COLOR_NORTHSTAR);
	glBegin(GL_LINES);
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 1.0f, 0.0f );
	glEnd();

	// Pop Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Switch back to Model View
	glMatrixMode(GL_MODELVIEW);

	glEnable( GL_LINE_SMOOTH );
	glDisable( GL_DEPTH_TEST );
}

/* ///ACTIVE LINE
void CConStationView::DrawActiveLine() const
{
	// Set up 2d Projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw Line
	glColor(COLOR_CONSTLINE);
	glLineWidth(3);
	glBegin(GL_LINES);
		glVertex2i(prevStarPoint.x, prevStarPoint.y);
		glVertex2i(mousePoint.x, mousePoint.y);
	glEnd();

	// Pop Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}
*/


///////////////////////////////////////////////////////////////////////////////
// View Manipulation

void CConStationView::Projection() const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	Perspective ();

    glMatrixMode(GL_MODELVIEW);
}

void CConStationView::Perspective() const
{
	float persp = (1 - starfield->GetZoom()) * 45;

	gluPerspective(persp,(float)width/(float)height,0.001f,10.0f);
}

void CConStationView::RotateXY() const
{
	glRotatef (starfield->GetRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef (starfield->GetRotY(), 0.0f, 1.0f, 0.0f);
}

// Rotate the view depending on the latitude
void CConStationView::RotateLatitude() const
{
	glRotatef( -starfield->GetRotLatitude(), 1.0f, 0.0f, 0.0f );
}

// Rotate the view depending on the time
void CConStationView::RotateTime() const
{
	glRotatef (starfield->GetRotTime(), 0.0f, 1.0f, 0.0f);
}

BOOL CConStationView::IsRotating() const
{
	return mouseRotatingXY || mouseRotatingZ;
}


///////////////////////////////////////////////////////////////////////////////
// Keyboard
void CConStationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	keyDown[nChar] = true;
}

void CConStationView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	keyDown[nChar] = false;
}

// Timer for animation
void CConStationView::OnTimer(UINT nIDEvent) 
{
	ProcessKeys();

	if (starfield->IsSpinning() &&
		state == state_Viewing)
	{
//		starfield->AdjRotTime(0.05f);
		starfield->AdjRotTime(0.5f);
		Redraw();
	}
}

void CConStationView::ProcessKeys()
{
	// Don't handle view keys if
	if (state != state_Viewing)
		return;

	BOOL update = false;

	// Rotating
	if ( keyDown[VK_UP] )
	{
		starfield->RotateUp();
		update = true;
	}
	if ( keyDown[VK_DOWN] )
	{
		starfield->RotateDown();
		update = true;
	}
	if ( keyDown[VK_RIGHT] )
	{
		starfield->RotateRight();
		update = true;
	}
	if ( keyDown[VK_LEFT] )
	{
		starfield->RotateLeft();
		update = true;
	}

	// Zooming
	if ( keyDown['X'] )
	{
		starfield->ZoomIn();
		Projection();
		update = true;
	}
	if ( keyDown['Z'] )
	{
		starfield->ZoomOut();
		Projection();
		update = true;
	}

	// Resets
	if ( keyDown[' '] )
	{
		starfield->ResetZoom();
		Projection();
		update = true;
	}
	if ( keyDown[VK_RETURN] )
	{
		starfield->ResetView();
		Projection();
		update = true;
	}

	if ( update )
		Redraw();
}

///////////////////////////////////////////////////////////////////////////////
// Mouse Buttons
void CConStationView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mousePoint = point;
	mouseLDownPoint = point;

	if (state == state_AddingLine || state == state_AddingPoly)
	{
		// Try to select star
		int selectedStarNum = SelectStar();

		// If star was selected
		if (selectedStarNum != -1)
		{
			// If this is the first star of the line
			if (firstStarNum == -1)
			{
				prevStarNum = selectedStarNum;
				firstStarNum = selectedStarNum;
				/// ACTIVE LINE
			//	prevStarPoint = point;
			}
			// Adding a line so this should complete a line
			//   and set the previous star number
			else
			{
				// Unless they selected the same star twice
				if (prevStarNum == selectedStarNum)
					return;

				// Make a new line
				starfield->AddConstLine( prevStarNum, selectedStarNum );

				prevStarNum = selectedStarNum;
				/// ACTIVE LINE
			//	prevStarPoint = point;

				GetDocument()->SetModifiedFlag();

				OnDraw( GetDC() );	// instead of InvalidateRect so it forces a redraw
			}
		}
	}
	else if (state == state_DeletingLine)
	{
		int selectedLineNum = SelectConstLine();

		// If a line was selected
		if (selectedLineNum != -1)
		{
			starfield->GetCurConstellation()->DeleteLine(selectedLineNum);
			GetDocument()->SetModifiedFlag();
			Redraw();
		}
	}
	else
	{
		// Start rotating XY
		mouseRotatingXY = true;

		if (!mouseRotatingZ)
		{
			SetCur(IDC_ROTXY);
			SetCapture();
		}
	}

}

void CConStationView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	mousePoint = point;
	mouseLDownPoint = CPoint(0,0);

	mouseRotatingXY = false;

	if (!mouseRotatingZ)
		ReleaseCapture();
}

void CConStationView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	mousePoint = point;
	mouseRDownPoint = point;

	if (state == state_AddingLine)
	{
		// If drawing lines
		if (firstStarNum != -1)
			firstStarNum = -1;
		else
			SetState( state_Viewing );
	}
	else if (state == state_AddingPoly)
	{
		// Complete Line
		if (firstStarNum != -1)
		{
			starfield->AddConstLine(firstStarNum, prevStarNum);
			firstStarNum = -1;

			GetDocument()->SetModifiedFlag();
			Redraw();
		}
		else
			SetState( state_Viewing );
	}
	else if (state == state_DeletingLine)
		SetState( state_Viewing );
	else if (state == state_Viewing)
	{
		mouseRotatingZ = true;

		SetCur(IDC_ROTZ);
		if (!mouseRotatingXY)
			SetCapture();
	}

}

void CConStationView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	mousePoint = point;
	mouseRDownPoint = CPoint(0,0);


	mouseRotatingZ = false;
	if (!mouseRotatingXY)
		ReleaseCapture();
	else
		SetCur(IDC_ROTXY);
}

BOOL CConStationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if( state == state_Viewing )
	{
		// Zoom faster than with keys
		if (zDelta < 0)
		{
			starfield->ZoomOut();
			starfield->ZoomOut();
			starfield->ZoomOut();
			starfield->ZoomOut();
		}
		if (zDelta > 0)
		{
			starfield->ZoomIn();
			starfield->ZoomIn();
			starfield->ZoomIn();
			starfield->ZoomIn();
		}

		Projection();

		Redraw();
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Mouse Move
void CConStationView::OnMouseMove(UINT nFlags, CPoint point) 
{
	mousePoint = point;

	if (mouseRotatingXY || mouseRotatingZ)
	{
		if (state != state_Viewing)
		{
			MessageBox("Shouldn't be able to Mouse Rotate");
			mouseRotatingXY = false;
			mouseRotatingZ = false;
			return;
		}

		float rotX = starfield->GetRotX();

		if (mouseRotatingXY && !mouseRotatingZ)
		{
			starfield->AdjRotX((point.y-mouseLDownPoint.y) / 20.0f);// * (1-zoom);
			starfield->AdjRotY((point.x-mouseLDownPoint.x) / 20.0f);// * (1-zoom);
		}
		if (mouseRotatingZ)
			starfield->AdjRotTime((point.y-mouseRDownPoint.y) / 10.0f);// * (1-zoom);

		Redraw();

		// Set the mouse point
		mouseLDownPoint=point;
		mouseRDownPoint=point;

	}

	/// ACTIVE LINE
	// Invalidate so it will show line as mouse moves
//	if (state == AddingLine && firstStarNum != -1)
//		Redraw();
}

///////////////////////////////////////////////////////////////////////////////
// Cursor
void CConStationView::SetCur(WORD cur)
{
	SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(cur)));
}

BOOL CConStationView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	WORD cursor = IDC_POINT;

	if (state == state_AddingLine)
	{
		if (firstStarNum == -1)
		{
			if (Select(Star))
				cursor = IDC_EDITX;
			else
				cursor = IDC_EDIT;
		}
		else
		{
			if (Select(Star))
				cursor = IDC_ALINEX;
			else
				cursor = IDC_ALINE;
		}
	}
	else if (state == state_AddingPoly)
	{
		if (firstStarNum == -1)
		{
			if (Select(Star))
				cursor = IDC_EDITX;
			else
				cursor = IDC_EDIT;
		}
		else
		{
			if (Select(Star))
				cursor = IDC_APOLYX;
			else
				cursor = IDC_APOLY;
		}
	}
	else if (state == state_DeletingLine)
	{
		if (Select(Line))
			cursor = IDC_DLINEX;
		else
			cursor = IDC_DLINE;
	}

	SetCur (cursor);
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// Selecting

void CConStationView::ClearFirstStar()
{
	firstStarNum = -1;
}

BOOL CConStationView::Select(SelectType selection)
{
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <width>, [3] Is <height>
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(100, selectBuffer);							// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	(void) glRenderMode(GL_SELECT);

	glInitNames();												// Initializes The Name Stack

	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) mousePoint.x, (GLdouble) (viewport[3]-mousePoint.y), 10.0f, 10.0f, viewport);

	// Apply The Perspective Matrix
	Perspective();

	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();

	if (selection == Star)
	{
		DrawTerrain();
		DrawStars();
	}
	else if (selection == Line)
		DrawConstellation(starfield->GetNumCurConstellation());

	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix

	glMatrixMode(GL_MODELVIEW);
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was

	// Check if there is a hit
	if( hits <= 0 )
		return false;
	else
	{
		// Test if terrain was hit
		if( selection == Star )
		{
			for( int i=0; i<hits; i++ )
			{
				// If terrain was hit (terrain is 0)
				if( selectBuffer[i*4 + 3] == 0 )
					return false;
			}

			// Terrain wasn't hit
			return true;
		}
		else
		{
			return true;
		}
	}
}

int CConStationView::SelectStar()
{
	if (Select(Star))	// If a hit occured in starfield
	{
		int numStar = selectBuffer[3] - 1;	// Subtract 1 because terrain is 0
		CStar* selectedStar = starfield->GetStar(numStar);

		// If there was more than one hit
		for (int i=1; i<hits; i++)
		{
			// Get the brightest
			if (starfield->GetStar(selectBuffer[i*4+3]-1)->GetMag() <
						selectedStar->GetMag())
			{
				numStar = selectBuffer[i*4+3] - 1;	// Subtract 1 because terrain is 0
				selectedStar = starfield->GetStar(numStar);
			}
		}
		return numStar;
	}
	else return -1;
}

int CConStationView::SelectConstLine()
{
	if (Select(Line))	// If a hit occured
		return selectBuffer[3];
	else return -1;
}
