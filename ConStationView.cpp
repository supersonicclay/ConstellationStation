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


/////////////////////////////////////////////////////////////////////////////
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


/////////////////////////////////////////////////////////////////////////////
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


/////////////////////////////////////////////////////////////////////////////
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

/*
// Calculate the offset of the terrain, so the viewer is placed above it.
void CConStationView::SetTerrainOffset()
{
	// Get the index of the midpoint
	int middleIndex = terrain->GetSize() / 2;

	// Average the heights around the midpoint,
	//  so the viewer isn't placed in a deep pit.

	// Average of square points directly around middle
	float avg1 = terrain->AvgSquare(middleIndex, middleIndex, 1);
	// Average of diamond points directly around middle
	float avg2 = terrain->AvgDiamond(middleIndex, middleIndex, 1);

	// Average the two averages
	float height = ((avg1 + avg2) / 2);

	// Make sure the new height is not less than the height at the midpoint
	//  (this would put the viewer under the terrain)
	// If it is, then switch to the height of the midpoint
	if (height < terrain->GetHeight(middleIndex, middleIndex))
		height = terrain->GetHeight(middleIndex, middleIndex) + 0.2f;

	// Move it down a little more than that so the viewer isn't exactly on the surface
	terrainOffset = -height - 0.05f;
}
*/




/////////////////////////////////////////////////////////////////////////////
// CConStationView message handlers

int CConStationView::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Initialize OpenGL
	if (!InitializeOpenGL())
		MessageBox("Error initializing OpneGL", "ERROR");

//	SetTimer(TIMER_VIEWKEYS, 20, 0);
//	SetTimer(TIMER_ROTATE, 50, 0);

	SetTimer( 1, 20, 0 );
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
	// Don't erase the background
	return TRUE;
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


/////////////////////////////////////////////////////////////////////////////
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
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
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


/////////////////////////////////////////////////////////////////////////////
// Textures

BOOL CConStationView::LoadTextures()
{
	if (!LoadTGA(starTex, "textures/star.tga"))
		return FALSE;

	if (!LoadTGA(skyTex, "textures/sky.tga"))
		return FALSE;

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CConStationView drawing

void CConStationView::Redraw()
{
	InvalidateRect( NULL, FALSE );
}

void CConStationView::OnDraw(CDC* pDC)
{
    CPaintDC dc(this); // Needed 

	// Useful in multidoc templates
	/// WELL THANK GOODNESS WE DON'T USE MDI!
//	HWND hWnd = GetSafeHwnd();
//	HDC hDC = ::GetDC(hWnd);
//	wglMakeCurrent(hDC,m_hglrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawSky();
	DrawSun();
	DrawStarfield();
	DrawTerrain();
	DrawHeading();

	/// ACTIVE LINE ///
	// Draw Active Line
///	if (state == AddingLine && firstStarNum != -1)
///		DrawActiveLine();

	SwapBuffers(m_pDC->GetSafeHdc());

}

/// Used for speedy adding of lines
void CConStationView::DrawCurConstellation( CDC* pDC )
{
	CPaintDC dc(this);

	glLineWidth(3);
	glColor(COLOR_CONSTLINE);

///	DrawStars();
	DrawConstellation( starfield->GetNumCurConstellation() );

	SwapBuffers( m_pDC->GetSafeHdc() );
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

///	float* n;

	float scale = terrain->GetScale();
	int iterations = terrain->GetIterations();

	float* n;

	x = -scale;
	z = -scale;
	inc = (float)pow(2, -iterations+1);

	glPushName( 0 );

	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			/* ///
			glDisable( GL_LIGHTING );
			glColor3f( 1, 0, 0 );
			glBegin(GL_LINES);
				glVertex3f( x, heights[ i*arraySize + j ], z );
				glVertex3f( x, heights[ i*arraySize + j ]+0.5f, z );
				glVertex3f( n[0], n[1], n[2] );
			glEnd();
			glEnable( GL_LIGHTING );
//			*/

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
	RotateSeason();
	RotateTime();

	// Enable texture
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, skyTex.textureID );

	// Draw sky background
	glColor( COLOR_SKY );
	gluSphere( skySphere, 1.0f, 20, 5 );

	glDisable( GL_TEXTURE_2D );
}

void CConStationView::DrawSun() const
{
	glLoadIdentity();
//	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
	RotateXY();
	RotateLatitude();
	RotateSeason();
	RotateTime();

	glTranslatef( 0.0f, 0.0f,-1.0f );

	// Sun Sphere
	glColor( COLOR_WHITE );
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
	RotateSeason();
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
	RotateSeason();
	RotateTime();

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );

	glBindTexture(GL_TEXTURE_2D, starTex.textureID);

	// Go in reverse order so north star (star 0) is drawn last
	for (int i=starfield->GetNumStars()-1; i>=0; i--)
	{
		glPushName( i+1 );
		DrawStar( i );
		glPopName();
	}

	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
}

void CConStationView::DrawStar(int i) const
{
	CStar* curStar = starfield->GetStar(i);
	float longitude = curStar->GetLongitude();
	float latitude = curStar->GetLatitude();
	float brightness = curStar->GetBrightness();
	color_t color;

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

	///
//	if (i == 1175)
//		color = COLOR_CROSS;
//	if (i == 3619)
//		color = COLOR_CROSS;


	// Push matrix so quad rotation doesn't affect anything
	glPushMatrix();

	// Now we're ready to draw the star
	glColor (color);
	glPointSize(brightness);

	glRotatef(longitude, 0.0f, 1.0f, 0.0f );
	glRotatef( latitude, 1.0f, 0.0f, 0.0f );
	glTranslatef( 0.0f, 1.0f, 0.0f );

	/// Draw a star quad
	float quadSize = brightness / 170.0f;
	glBegin( GL_QUADS );
		glNormal3f( 0.0f, -1.0f, 0.0f );
		glTexCoord2i( 0, 1 ); glVertex3f( -quadSize, 0.0f,  quadSize );
		glTexCoord2i( 1, 1 ); glVertex3f(  quadSize, 0.0f,  quadSize );
		glTexCoord2i( 1, 0 ); glVertex3f(  quadSize, 0.0f, -quadSize );
		glTexCoord2i( 0, 0 ); glVertex3f( -quadSize, 0.0f, -quadSize );
	glEnd();

	/*/// POINT
	glColor( COLOR_CROSS );
	glBegin(GL_POINTS);
		glVertex2f( 0, 0 );
	glEnd();
//		*/

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
	RotateSeason();
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


/////////////////////////////////////////////////////////////////////////////
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
	glRotatef( -starfield->GetLatitude(), 1.0f, 0.0f, 0.0f );
}

// Rotate the view depending on the season
void CConStationView::RotateSeason() const
{
	glRotatef( starfield->GetSeason(), 1.0f, 0.0f, 0.0f );
}

// Rotate the view depending on the time
void CConStationView::RotateTime() const
{
	glRotatef (starfield->GetTime(), 0.0f, 1.0f, 0.0f);
}

BOOL CConStationView::IsRotating() const
{
	return mouseRotatingXY || mouseRotatingZ;
}


/////////////////////////////////////////////////////////////////////////////
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
//		starfield->AdjTime(0.05f);
		starfield->AdjTime(0.5f);
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

/////////////////////////////////////////////////////////////////////////////
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
///				prevStarPoint = point;
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
///				prevStarPoint = point;

				/// GetDocument()->SetModifiedFlag();
				/// DrawCurConstellation( GetDC() );
				OnDraw( GetDC() );
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

/////////////////////////////////////////////////////////////////////////////
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
			starfield->AdjTime((point.y-mouseRDownPoint.y) / 10.0f);// * (1-zoom);

		Redraw();

		// Set the mouse point
		mouseLDownPoint=point;
		mouseRDownPoint=point;

	}

	/// ACTIVE LINE ///
	// Invalidate so it will show line as mouse moves
///	if (state == AddingLine && firstStarNum != -1)
///		Redraw();
}

/////////////////////////////////////////////////////////////////////////////
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


/////////////////////////////////////////////////////////////////////////////
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

	/// TAKE OUT after we're sure this doesn't happen
	if( hits < 0 )
	{
		MessageBox("Hits is less than 0");
		return false;
	}

	if( hits == 0 )
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
			if (starfield->GetStar(selectBuffer[i*4+3]-1)->GetBrightness() >
						selectedStar->GetBrightness())
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
