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

// Timer
#define TIMER_VIEWKEYS	1
#define TIMER_ROTATE	2

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
	state = Viewing;

	ZeroMemory (&keyDown, sizeof (keyDown));

	mouseRotatingXY = false;
	mouseRotatingZ = false;
}

CConStationView::~CConStationView()
{
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

CConStationDoc* CConStationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConStationDoc)));
	return (CConStationDoc*)m_pDocument;
}
#endif //_DEBUG

CStarfield* CConStationView::GetStarfield() const
{
	return GetDocument()->GetStarfield();
}


/////////////////////////////////////////////////////////////////////////////
// CConStationView message handlers

int CConStationView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Initialize OpenGL
	if (!InitializeOpenGL())
		MessageBox("Error initializing OpneGL", "ERROR");

//	GetGLInfo();

	SetTimer(TIMER_VIEWKEYS, 20, 0);
	SetTimer(TIMER_ROTATE, 50, 0);

	return 0;
}


void CConStationView::OnDestroy() 
{
//	CView::OnDestroy();
	
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

BOOL CConStationView::InitializeOpenGL()
{
	// Get a DC for the Client Area
	m_pDC = new CClientDC(this);

	// Failure to Get DC
	if(m_pDC == NULL)
	{
		MessageBox("Error Obtaining DC");
		return false;
	}

	// Failure to set the pixel format
	if(!SetupPixelFormat())
	{
		return false;
	}

	// Create Rendering Context
	m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());

	// Failure to Create Rendering Context
	if(m_hRC == 0)
	{
		MessageBox("Error Creating RC");
		return false;
	}
	
	// Make the RC Current
	if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
	{
		MessageBox("Error making RC Current");
		return false;
	}

	//Specify Black as the clear color
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	//Specify the back of the buffer as clear depth
	glClearDepth(1.0f);

	// Set Perspective Calculations To Most Accurate
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
//Setup Pixel Format
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
		return false;
	}

	if ( SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		MessageBox("Couldn't Set Pixel Format");
		return false;
	}

	return true;
}

// Get OpenGL Information
void CConStationView::GetGLInfo() 
{

	CString who2;
	who2 =  "OpenGL Information\n\nWho: ";
	who2 += glGetString( GL_VENDOR );
	who2 += "\nWhich: ";
	who2 += glGetString( GL_RENDERER );
	who2 += "\nVersion: ";
	who2 += glGetString( GL_VERSION );
	who2 += "\nExtensions: ";
	who2 += glGetString( GL_EXTENSIONS );

	::AfxMessageBox(who2,MB_ICONINFORMATION);

}

BOOL CConStationView::OnEraseBkgnd(CDC* pDC) 
{
	//return CView::OnEraseBkgnd(pDC);

	//don't erase the background
	return TRUE;
}

void CConStationView::OnSize(UINT nType, int cx, int cy) 
{
//	CView::OnSize(nType, cx, cy);
	
	width = cx;
	height = cy;

	
	if ( width <= 0 || height <= 0)
	{
		return;
	}

    glViewport(0, 0, cx, cy);

	Projection ();
}


/////////////////////////////////////////////////////////////////////////////
// States
StateType CConStationView::GetState() const
{
	return state;
}

void CConStationView::SetState(StateType state_)
{
	state = state_;

	if (state == AddingLine || state == AddingPoly)
		firstStarNum = -1;
}

BOOL CConStationView::IsRotating() const
{
	return mouseRotatingXY || mouseRotatingZ;
}

/////////////////////////////////////////////////////////////////////////////
// CConStationView drawing

void CConStationView::OnDraw(CDC* pDC)
{
	CConStationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CPaintDC dc(this); // Needed 

	// Useful in multidoc templates
	/// WELL THANK GOODNESS WE DON'T USE MDI!
//	HWND hWnd = GetSafeHwnd();
//	HDC hDC = ::GetDC(hWnd);
//	wglMakeCurrent(hDC,m_hglrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawStarfield();
	DrawGround();
	DrawHeading();

	/// GROGGY ///
	// Draw Active Line
///	if (state == AddingLine && firstStarNum != -1)
///		DrawActiveLine();

	SwapBuffers(m_pDC->GetSafeHdc());

}

void CConStationView::DrawGround() const
{
	glLoadIdentity();

	RotateXY();

	glColor(GROUNDGREEN);

	// Rotate to horizontal
	glRotatef (90.0f, 1.0f,0.0f,0.0f);

	// Move ground down
	glTranslatef (0.0f,0.0f,0.2f);

	// Draw Ground (disk)
	gluDisk(gluNewQuadric(),0.0f,0.98f,40,40);

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
	glColor(CONSTGREEN);

	// Draw each constellation
	for (int i=0; i<GetStarfield()->GetNumConstellations(); i++)
	{
		if (GetStarfield()->GetConstellation(i)->IsVisible())
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

	CConstellation* curConstellation = GetStarfield()->GetConstellation(i);
	int numLines = curConstellation->GetNumLines();

	float x1, y1, z1, x2, y2, z2;

	glBegin(GL_LINES);
		for (int j=0; j<numLines; j++)
		{
			glPushName(j);
			x1 = curConstellation->GetLine(j)->GetX1();
			y1 = curConstellation->GetLine(j)->GetY1();
			z1 = curConstellation->GetLine(j)->GetZ1();
			x2 = curConstellation->GetLine(j)->GetX2();
			y2 = curConstellation->GetLine(j)->GetY2();
			z2 = curConstellation->GetLine(j)->GetZ2();
			glVertex3f (x1, y1, z1);
			glVertex3f (x2, y2, z2);
			glPopName();
		}
	glEnd();
}

void CConStationView::DrawStars() const
{
	glLoadIdentity();

	RotateXY();
	RotateLatitude();
	RotateSeason();
	RotateTime();

	for (int i=0; i<GetStarfield()->GetNumStars(); i++)
	{
		glPushName(i);
		DrawStar(i);
		glPopName();
	}
}

void CConStationView::DrawStar(int i) const
{
	CStar* curStar = GetStarfield()->GetStar(i);
	float x = curStar->GetX();
	float y = curStar->GetY();
	float z = curStar->GetZ();
	float brightness = curStar->GetBrightness();
	CColor color;

	// Determine if this star is active (part of the current constellation)
	bool active = false;

	if (GetStarfield()->GetNumConstellations() > 0)
	{
		for (int lineIndex=0; lineIndex < GetStarfield()->GetCurConstellation()->GetNumLines(); lineIndex++)
		{
			if (curStar == GetStarfield()->GetCurConstellation()->GetLine(lineIndex)->GetStar1() ||
				curStar == GetStarfield()->GetCurConstellation()->GetLine(lineIndex)->GetStar2())
			{
				active = true;
				break;
			}
		}
	}

	if (active)
		color = RED;
	else
		color = curStar->GetColor();

	glColor (color);

	/// Brightness depending on zoom
	if (GetStarfield()->GetZoom() > 0)
		 brightness *= (GetStarfield()->GetZoom() + 1);
	else brightness *= (GetStarfield()->GetZoom() + 3) * 0.3f;

	//	Don't show if too dim
	if (brightness > 0.2f)
	{
		glPointSize(brightness);

		glColor (color);

		glBegin(GL_POINTS);
			glVertex3f ( x, y, z);
		glEnd();
	}
}

void CConStationView::DrawHeading() const
{
	// Enable Depth Test
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

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
	glColor (GREEN);
	glBegin(GL_LINES);
		glVertex3f ( 1.0f, 0.0f, 0.0f);
		glVertex3f (-1.0f, 0.0f, 0.0f);
		glVertex3f ( 0.0f, 1.0f, 0.0f);
		glVertex3f ( 0.0f,-1.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f, 1.0f);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	// North Star Pointer
	RotateLatitude();
	RotateSeason();
	glColor (RED);
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	// Pop Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Switch back to Model View
	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();
}

/*
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
	glColor(CONSTGREEN);
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
// View Manipulation (draw)

void CConStationView::Projection() const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	Perspective ();

    glMatrixMode(GL_MODELVIEW);
}

void CConStationView::Perspective() const
{
	float persp = (1 - GetStarfield()->GetZoom()) * 60 + 5;

	gluPerspective(persp,(float)width/(float)height,0.01f,10.0f);
}

void CConStationView::RotateXY() const
{
	glRotatef (GetStarfield()->GetRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef (GetStarfield()->GetRotY(), 0.0f, 1.0f, 0.0f);
}

// Rotate the view depending on the latitude
void CConStationView::RotateLatitude() const
{
	/// Should be stored in CStarfield
	glRotatef (30.0f, 1.0f, 0.0f, 0.0f);
}

// Rotate the view depending on the season
void CConStationView::RotateSeason() const
{
	/// Should be stored in CStarfield
}

// Rotate the view depending on the time
void CConStationView::RotateTime() const
{
	glRotatef (GetStarfield()->GetTime(), 0.0f, 0.0f, 1.0f);
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
	if (nIDEvent == TIMER_VIEWKEYS)
		ProcessKeys();
	if (nIDEvent == TIMER_ROTATE && GetStarfield()->IsSpinning() && state == Viewing)
	{
		GetStarfield()->AdjTime(0.1f);
		InvalidateRect(NULL, FALSE);
	}
}

void CConStationView::ProcessKeys()
{
	// Don't handle view keys if
	if (state != Viewing)
		return;

	BOOL update = false;

	// Rotating
	if ( keyDown[VK_UP] )
	{
		GetStarfield()->RotateUp();
		update = true;
	}
	if ( keyDown[VK_DOWN] )
	{
		GetStarfield()->RotateDown();
		update = true;
	}
	if ( keyDown[VK_RIGHT] )
	{
		GetStarfield()->RotateRight();
		update = true;
	}
	if ( keyDown[VK_LEFT] )
	{
		GetStarfield()->RotateLeft();
		update = true;
	}

	// Zooming
	if ( keyDown['X'] )
	{
		GetStarfield()->ZoomIn();
		Projection();
		update = true;
	}
	if ( keyDown['Z'] )
	{
		GetStarfield()->ZoomOut();
		Projection();
		update = true;
	}

	// Resets
	if ( keyDown[' '] )
	{
		GetStarfield()->ResetZoom();
		Projection();
		update = true;
	}
	if ( keyDown[VK_RETURN] )
	{
		GetStarfield()->ResetView();
		Projection();
		update = true;
	}

	if ( update )
	{
		GetDocument()->SetModifiedFlag();
		InvalidateRect(NULL,FALSE);
	}

}

/////////////////////////////////////////////////////////////////////////////
// Mouse Buttons
void CConStationView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mousePoint = point;
	mouseLDownPoint = point;

	if (state == AddingLine || state == AddingPoly)
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
				GetStarfield()->AddConstLine(prevStarNum, selectedStarNum);

				prevStarNum = selectedStarNum;
///				prevStarPoint = point;

				InvalidateRect(NULL, FALSE);
			}
		}
	}
	else if (state == DeletingLine)
	{
		int selectedLineNum = SelectConstLine();

		// If a line was selected
		if (selectedLineNum != -1)
		{
			GetStarfield()->GetCurConstellation()->DeleteLine(selectedLineNum);
			InvalidateRect(NULL, FALSE);
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

	GetDocument()->SetModifiedFlag();
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

	if (state == AddingLine)
	{
		// If drawing lines
		if (firstStarNum != -1)
			firstStarNum = -1;
		else
			SetState(Viewing);
	}
	else if (state == AddingPoly)
	{
		// Complete Line
		if (firstStarNum != -1)
		{
			GetStarfield()->AddConstLine(firstStarNum, prevStarNum);
			firstStarNum = -1;
			InvalidateRect(NULL, FALSE);
		}
		else
			SetState(Viewing);
	}
	else if (state == DeletingLine)
		SetState(Viewing);
	else if (state == Viewing)
	{
		mouseRotatingZ = true;

		SetCur(IDC_ROTZ);
		if (!mouseRotatingXY)
			SetCapture();
	}

	GetDocument()->SetModifiedFlag();
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
	// Zoom faster than with keys
	if (zDelta < 0)
	{
		GetStarfield()->ZoomOut();
		GetStarfield()->ZoomOut();
		GetStarfield()->ZoomOut();
		GetStarfield()->ZoomOut();
	}
	if (zDelta > 0)
	{
		GetStarfield()->ZoomIn();
		GetStarfield()->ZoomIn();
		GetStarfield()->ZoomIn();
		GetStarfield()->ZoomIn();
	}

	Projection();

	GetDocument()->SetModifiedFlag();

	InvalidateRect(NULL, FALSE);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Mouse Move
void CConStationView::OnMouseMove(UINT nFlags, CPoint point) 
{
	mousePoint = point;

	if (mouseRotatingXY || mouseRotatingZ)
	{
		if (state != Viewing)
		{
			MessageBox("Shouldn't be able to Mouse Rotate");
			mouseRotatingXY = false;
			mouseRotatingZ = false;
			return;
		}

		float rotX = GetStarfield()->GetRotX();

		if (mouseRotatingXY && !mouseRotatingZ)
		{
			GetStarfield()->AdjRotX((point.y-mouseLDownPoint.y) / 20.0f);// * (1-zoom);
			GetStarfield()->AdjRotY((point.x-mouseLDownPoint.x) / 20.0f);// * (1-zoom);
		}
		if (mouseRotatingZ)
			GetStarfield()->AdjTime((point.y-mouseRDownPoint.y) / 10.0f);// * (1-zoom);

		InvalidateRect(NULL,FALSE);

		// Set the mouse point
		mouseLDownPoint=point;
		mouseRDownPoint=point;
		
		///SetCursorPos(mouseLDownPoint.x, mouseLDownPoint.y);
	}
	/// GROGGY ///
	// Invalidate so it will show line as mouse moves
///	if (state == AddingLine && firstStarNum != -1)
///		InvalidateRect(NULL, FALSE);
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

	if (state == AddingLine)
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
	else if (state == AddingPoly)
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
	else if (state == DeletingLine)
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
		DrawStars();
	else if (selection == Line)
		DrawConstellation(GetStarfield()->GetNumCurConstellation());

	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix

	glMatrixMode(GL_MODELVIEW);
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was

	if (hits > 0)
	{
		return true;
	}
	return false;												// Nothing selected
}

int CConStationView::SelectStar()
{
	if (Select(Star))	// If a hit occured in starfield
	{
		int numStar = selectBuffer[3];
		CStar* selectedStar = GetStarfield()->GetStar(numStar);

		// If there was more than one hit
		for (int i=1; i<hits; i++)
		{
			// Get the brightest
			if (GetStarfield()->GetStar(selectBuffer[i*4+3])->GetBrightness() >
						selectedStar->GetBrightness())
			{
				numStar = selectBuffer[i*4+3];
				selectedStar = GetStarfield()->GetStar(numStar);
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
