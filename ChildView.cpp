// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "sdindv.h"
#include "ChildView.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	ZeroMemory (&keyDown, sizeof (keyDown));

	mouseRotating = false;
	rotX = 0.0f;
	rotY = 0.0f;
	zoom = 0.0f;

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )

	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()


	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//Initialize OpenGL Here
	InitializeOpenGL();
	
	return 0;
}


void CChildView::OnDestroy() 
{
//	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
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
	
	//Delete the DC
	if(m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}

BOOL CChildView::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);

	//Failure to Get DC
	if(m_pDC == NULL)
	{
		MessageBox("Error Obtaining DC");
		return FALSE;
	}

	//Failure to set the pixel format
	if(!SetupPixelFormat())
	{
		return FALSE;
	}

	//Create Rendering Context
	m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());

	//Failure to Create Rendering Context
	if(m_hRC == 0)
	{
		MessageBox("Error Creating RC");
		return FALSE;
	}
	
	//Make the RC Current
	if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
	{
		MessageBox("Error making RC Current");
		return FALSE;
	}

	//Specify Black as the clear color
	::glClearColor(0.0f,0.0f,0.0f,0.0f);

	//Specify the back of the buffer as clear depth
	::glClearDepth(1.0f);

	//Enable Depth Testing
	::glEnable(GL_DEPTH_TEST);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//Setup Pixel Format
BOOL CChildView::SetupPixelFormat()
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
    
    int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if ( m_nPixelFormat == 0 )
	{
       return FALSE;
	}

    if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
    {
       return FALSE;
	}

    return TRUE;
}
BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//comment out the original call
	//return CView::OnEraseBkgnd(pDC);
	//Tell Windows not to erase the background
	return TRUE;
}

void CChildView::OnSize(UINT nType, int cx, int cy) 
{
//	CWnd::OnSize(nType, cx, cy);
	
	width = cx;
	height = cy;
	// TODO: Add your message handler code here
	GLdouble aspect_ratio; // width/height ratio
	
	if ( 0 >= cx || 0 >= cy )
	{
		return;
	}

	// select the full client area
    glViewport(0, 0, cx, cy);

	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;

	// select the projection matrix and clear it
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();

	// select the viewing volume
	::gluPerspective(45.0f, aspect_ratio, 0.05f, 200.0f);
	
	// switch back to the modelview matrix and clear it
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
}


/*
void CChildView::RenderScene ()
{
	glLoadIdentity();
	glTranslatef(0.0f, m_yPos, -5.0f);
	glRotatef(m_xAngle, 1.0f,0.0f,0.0f);
	glRotatef(m_yAngle, 0.0f,1.0f,0.0f);

	DrawStarfield();	// Draw cube

}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
		case VK_UP:		m_yPos = m_yPos + 0.1f;
						break;
		case VK_DOWN:	m_yPos = m_yPos - 0.1f;
						break;
		case VK_LEFT:	m_xPos = m_xPos - 0.1f;
						break;
		case VK_RIGHT:  m_xPos = m_xPos + 0.1f;
						break;
		default:		MessageBox("Press the arrow keys only");
						break;
	}		

	InvalidateRect(NULL,FALSE);
	
//	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_MouseDownPoint=point;
	SetCapture();
	
//	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_MouseDownPoint=CPoint(0,0);
	ReleaseCapture();
	
//	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// Check if we have captured the mouse
	if (GetCapture()==this)
	{
//		GetCapture();
		//Increment the object rotation angles
		m_xAngle+=(point.y-m_MouseDownPoint.y)/3.6;
		m_yAngle+=(point.x-m_MouseDownPoint.x)/3.6;
		//Redraw the view
		InvalidateRect(NULL,FALSE);
		//Set the mouse point
		m_MouseDownPoint=point;
	}
	
//	CWnd::OnMouseMove(nFlags, point);
}
*/

/////////////////////////////////////////////////////////////////////////////
// DRAWING
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// Clear out the color & depth buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// TODO: Add your message handler code here
	DrawGLScene();

	// Tell OpenGL to flush its pipeline
//	::glFinish();

	// Now Swap the buffers
	SwapBuffers( m_pDC->GetSafeHdc() );
	
	// Do not call CWnd::OnPaint() for painting messages
}

int CChildView::DrawGLScene(void) const			// Here's Where We Do All The Drawing
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	//// Rotate and Zoom
	//// Draw starfield
	//// Draw constellation(s)

	DrawStarfield();
	return TRUE;										// Keep Going
}

void CChildView::DrawStarfield() const
{
	// Rotate and zoom
	glTranslatef (0.0f,0.0f,zoom);
	glRotatef (rotX, 1.0f, 0.0f, 0.0f);
	glRotatef (rotY, 0.0f, 1.0f, 0.0f);

	// North Star
	glColor(RED);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	glColor(WHITE);
	// The rest of the stars
	for (int i=0; i<starfield.GetNumStars(); i++)
	{
		glPushName(i);										// Assign Object A Name (ID)
		DrawStar(i);
		glPopName();
	}
}

void CChildView::DrawStar(int i) const
{
	CStar* curStar = starfield.GetStar(i);
	float x = curStar->GetX();
	float y = curStar->GetY();
	float z = curStar->GetZ();
	float brightness = curStar->GetBrightness();


//	/*
	// Set Brightness depending on zoom
	if (zoom > 0)
		glPointSize(brightness * (zoom+1));
	else glPointSize(brightness * (zoom + 3) * 0.3f);
//	*/
	glPointSize(brightness);

	//// Don't show if too dim??
//	if ((int) newBrightness > 0)
//	{
		glBegin(GL_POINTS);
			glVertex3f ( x, y, z);
		glEnd();
//	}
}

void CChildView::RotateUp ()
{
	if (rotX > -90)								// Keep rotX between +- 90
		rotX -= 0.3f * (-zoom + 1);				// Change is smaller if zoomed out
}

void CChildView::RotateDown ()
{
	if (rotX < 90)								// Keep rotX between +- 90
		rotX += 0.3f * (-zoom + 1);				// Change is smaller if zoomed out
}

void CChildView::RotateLeft ()
{
	rotY -= 0.3f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY < -360)							// Keep rotY between +- 360
		rotY += 360.0f;
}

void CChildView::RotateRight()
{
	rotY += 0.3f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY > 360)								// Keep rotY between +- 360
		rotY -= 360.0f;
}

void CChildView::ZoomIn()
{

	if (zoom < 0.6)
	{
		zoom += 0.02f * (-zoom +1);			// Change is smaller if zoomed out

		float persp = 45.0f / (zoom + 1);
		// Change in perspective is less if zooming out
	//	if (zoom < 0)
	//		persp *= 0.5f;

		// Change perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(persp,(float)width/(float)height,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);
	}

}

void CChildView::ZoomOut()
{
	if (zoom > -0.6)
	{
		zoom -= 0.02f * (-zoom +1);				// Change is smaller if zoomed out

		float persp = 45.0f / (zoom + 1);
		// Change in perspective is less if zooming out
//		if (zoom < 0)
//			persp *= 0.5f;
	
		// Change perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(persp,(float)width/(float)height,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);
	}
}

void CChildView::ResetView()
{
	rotX = 0.0f;
	rotY = 0.0f;
	zoom = 0.0f;
}

/////////////////////////////////////////////////////////////////////////////
// Input Management

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_UP:
			keyDown[VK_UP] = TRUE;
			break;
		case VK_DOWN:
			keyDown[VK_DOWN] = TRUE;
			break;
		case VK_LEFT:
			keyDown[VK_LEFT] = TRUE;
			break;
		case VK_RIGHT:
			keyDown[VK_RIGHT] = TRUE;
			break;
		case 'Q':
			keyDown['Q'] = TRUE;
			ZoomOut();
			break;
		case 'E':
			keyDown['E'] = TRUE;
			ZoomIn();
			break;
		default:
			break;
	}

	InvalidateRect(NULL,FALSE);

	////  Do I need??
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::ProcessKeys ()
{
//	/*
	BOOL update = FALSE;

	if ( keyDown[VK_UP] )
	{
		RotateUp();
		update = TRUE;
	}
	if ( keyDown[VK_DOWN] )
	{
		RotateDown();
		update = TRUE;
	}
	if ( keyDown[VK_LEFT] )
	{
		RotateLeft();
		update = TRUE;
	}
	if ( keyDown[VK_RIGHT] )
	{
		RotateRight();
		update = TRUE;
	}
	if ( keyDown['Q'] )
	{
		ZoomOut();
		update = TRUE;
	}
	if ( keyDown['E'] )
	{
		ZoomIn();
		update = TRUE;
	}

	if ( update )
		InvalidateRect(NULL,FALSE);
//	*/
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_UP:
			keyDown[VK_UP] = FALSE;
			break;
		case VK_DOWN:
			keyDown[VK_DOWN] = FALSE;
			break;
		case VK_LEFT:
			keyDown[VK_LEFT] = FALSE;
			break;
		case VK_RIGHT:
			keyDown[VK_RIGHT] = FALSE;
			break;
		case 'Q':
			keyDown['Q'] = FALSE;
			break;
		case 'E':
			keyDown['E'] = FALSE;
			break;
		default:
			break;
	}

	//CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (mouseRotating)
	{
		rotX += (point.y-mouseRDownPoint.y) / 20.0f * (1-zoom);
		rotY += (point.x-mouseRDownPoint.x) / 20.0f * (1-zoom);
		//Redraw the view
		InvalidateRect(NULL,FALSE);
		//Set the mouse point
		mouseRDownPoint=point;
	}
////CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	mouseRDownPoint = point;
	mouseRotating = true;
	SetCapture();


////CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	mouseRDownPoint = CPoint(0,0);
	mouseRotating = false;
	ReleaseCapture();


////CWnd::OnRButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////

const CColor WHITE = {1.0f,1.0f,1.0f},
			 BLACK = {0.0f,0.0f,0.0f},
			 RED   = {1.0f,0.0f,0.0f},
			 GREEN = {0.0f,1.0f,0.0f},
			 BLUE  = {0.0f,0.0f,1.0f};

// Convinience function for glColor3f
void glColor(CColor c)
{
	glColor3f(c.r, c.g, c.b);
}

/////////////////////////////////////////////////////////////////////////////



