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
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT, OnEdit)
	ON_UPDATE_COMMAND_UI(ID_EDIT, OnUpdateEdit)
	ON_WM_MOUSEWHEEL()
	ON_UPDATE_COMMAND_UI(ID_CONSTELLATION_CREATE, OnUpdateConstellationCreate)
	ON_UPDATE_COMMAND_UI(ID_CONSTELLATION_DELETE, OnUpdateConstellationDelete)
	ON_UPDATE_COMMAND_UI(ID_CONSTELLATION_LOAD, OnUpdateConstellationLoad)
	ON_UPDATE_COMMAND_UI(ID_CONSTELLATION_STORE, OnUpdateConstellationStore)
	ON_UPDATE_COMMAND_UI(ID_CONSTELLATION_STOREAS, OnUpdateConstellationStoreas)
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_NLINE, OnNewLine)
	ON_UPDATE_COMMAND_UI(ID_NLINE, OnUpdateNewLine)
	ON_COMMAND(ID_DLINE, OnDelLine)
	ON_UPDATE_COMMAND_UI(ID_DLINE, OnUpdateDelLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConStationView construction/destruction

CConStationView::CConStationView()
{
	editing = false;
	makingLine = false;
	deletingLine = false;

	ZeroMemory (&keyDown, sizeof (keyDown));

	mouseRotatingXY = false;
	mouseRotatingZ = false;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	zoom = 0.0f;
//	persp = 45.0f;
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

CConStationDoc* CConStationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConStationDoc)));
	return (CConStationDoc*)m_pDocument;
}
#endif //_DEBUG



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

	pStarfield = GetDocument()->GetStarfield();

	// For view keys
	SetTimer(1, 20, 0);

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

bool CConStationView::InitializeOpenGL()
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

	////Enable Depth Testing (only for heading)
	//glEnable(GL_DEPTH_TEST);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
//Setup Pixel Format
bool CConStationView::SetupPixelFormat()
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
		MessageBox("Couldn't Choose Pixel Format");
		return false;
	}

	if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
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
// CConStationView drawing

void CConStationView::OnDraw(CDC* pDC)
{
	CConStationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CPaintDC dc(this); // Needed 

	// Useful in multidoc templates
	//// WELL THANK GOODNESS WE DON'T USE MDI!
//	HWND hWnd = GetSafeHwnd();
//	HDC hDC = ::GetDC(hWnd);
//	wglMakeCurrent(hDC,m_hglrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawStarfield();
	DrawGround();
	DrawHeading();

	SwapBuffers(m_pDC->GetSafeHdc());

}

void CConStationView::DrawGround() const
{
	glLoadIdentity();

	// Rotate
	Rotate();

	glColor(DARKGREEN);

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
	glLoadIdentity();

	// Rotate ////and zoom
	Rotate();
	RotateLatitude();
	RotateSeason();
	RotateTime();
////	glTranslatef (0.0f,0.0f,zoom);
////	glRotatef (rotX, 1.0f, 0.0f, 0.0f);
////	glRotatef (rotY, 0.0f, 1.0f, 0.0f);

	glLineWidth(3);
	glColor(CONSTGREEN);
	//glColor(DARKGREEN);

	// Draw each constellation
	for (int i=0; i<pStarfield->GetNumConstellations(); i++)
		DrawConstellation(i);
}

void CConStationView::DrawConstellation(int i) const
{
	CConstellation* curConstellation = pStarfield->GetConstellation(i);
	int numLines = curConstellation->GetNumLines();

	float x1, y1, z1, x2, y2, z2;

	glBegin(GL_LINES);
		for (int j=0; j<numLines; j++)
		{
			x1 = curConstellation->GetLine(j)->GetX1();
			y1 = curConstellation->GetLine(j)->GetY1();
			z1 = curConstellation->GetLine(j)->GetZ1();
			x2 = curConstellation->GetLine(j)->GetX2();
			y2 = curConstellation->GetLine(j)->GetY2();
			z2 = curConstellation->GetLine(j)->GetZ2();
			glVertex3f (x1, y1, z1);
			glVertex3f (x2, y2, z2);
		}
	glEnd();
}

void CConStationView::DrawStars() const
{
	glLoadIdentity();

	// Rotate
	Rotate();
	RotateLatitude();
	RotateSeason();
	RotateTime();

	// North Star
	glColor(RED);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f ( 0.0f, 0.0f,-0.95f);
	glEnd();

	// The rest of the stars
	for (int i=0; i<pStarfield->GetNumStars(); i++)
	{
		glPushName(i);										// Assign Object A Name (ID)
		DrawStar(i);
		glPopName();
	}
}

void CConStationView::DrawStar(int i) const
{
	CStar* curStar = pStarfield->GetStar(i);
	float x = curStar->GetX();
	float y = curStar->GetY();
	float z = curStar->GetZ();
	int brightness = curStar->GetBrightness();
	CColor color = curStar->GetColor();

	glPointSize((float)brightness);

	glColor (color);

	glBegin(GL_POINTS);
		glVertex3f ( x, y, z);
	glEnd();

	/*
	// Set Brightness depending on zoom
	if (zoom > 0)
		 brightness *= (zoom + 1);
	else brightness *= (zoom + 3) * 0.3f;

	//	Don't show if too dim
	if (brightness > 1.0f)
	{
		glPointSize(brightness);

		glColor (color);

		glBegin(GL_POINTS);
			glVertex3f ( x, y, z);
		glEnd();
	}
	*/
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
	Rotate();

	// Cross
	glLineWidth(2);
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

	// Pop the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Switch back to Model View
	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();
}

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
	float persp = (1-zoom) * 60 + 5;

	gluPerspective(persp,(float)width/(float)height,0.01f,10.0f);
}

void CConStationView::Rotate () const
{
	glRotatef (rotX, 1.0f, 0.0f, 0.0f);
	glRotatef (rotY, 0.0f, 1.0f, 0.0f);
}

// Rotate the view depending on the latitude
void CConStationView::RotateLatitude () const
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
	glRotatef (rotZ, 0.0f, 0.0f, 1.0f);
}

/////////////////////////////////////////////////////////////////////////////
// View Manipulation (data)

void CConStationView::RotateUp ()
{
	if (rotX > -90.0f)								// Keep rotX between +- 90
		rotX -= 0.5f * (-zoom + 1);				// Change is smaller if zoomed out
}

void CConStationView::RotateDown ()
{
	if (rotX < 90.0f)								// Keep rotX between +- 90
		rotX += 0.5f * (-zoom + 1);				// Change is smaller if zoomed out
}

void CConStationView::RotateLeft ()
{
	rotY -= 0.5f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY < -360.0f)							// Keep rotY between +- 360
		rotY += 360.0f;
}

void CConStationView::RotateRight()
{
	rotY += 0.5f * (-zoom + 1);					// Change is smaller if zoomed out
	if (rotY > 360.0f)							// Keep rotY between +- 360
		rotY -= 360.0f;
}

void CConStationView::ZoomIn()
{
	if (zoom < 0.8f)
	{
		zoom += 0.01f;// * (1-zoom);
		Projection();
	}
}

void CConStationView::ZoomOut()
{
	if (zoom > -0.9f)
	{
		zoom -= 0.01f;// * (1-zoom);
		Projection();
	}
}

/////////////////////////////////////////////////////////////////////////////
// View resets
void CConStationView::ResetView()
{
	ResetRot();
	ResetZoom();
}

void CConStationView::ResetRot()
{
	rotX = 0.0f;
	rotY = 0.0f;
}

void CConStationView::ResetZoom()
{
	zoom = 0.0f;
	Projection();
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

// Timer for processing keys for smooth animation
void CConStationView::OnTimer(UINT nIDEvent) 
{
	ProcessKeys();
}

void CConStationView::ProcessKeys()
{
	// Don't handle view keys if making a line or rotating
	if (makingLine || mouseRotatingXY || mouseRotatingZ)
		return;

	bool update = false;

	// Rotating
	if ( keyDown[VK_UP] )
	{
		RotateUp();
		update = true;
	}
	if ( keyDown[VK_DOWN] )
	{
		RotateDown();
		update = true;
	}
	if ( keyDown[VK_RIGHT] )
	{
		RotateRight();
		update = true;
	}
	if ( keyDown[VK_LEFT] )
	{
		RotateLeft();
		update = true;
	}

	// Zooming
	if ( keyDown['E'] )
	{
		ZoomIn();
		update = true;
	}
	if ( keyDown['Q'] )
	{
		ZoomOut();
		update = true;
	}

	// Resets
	if ( keyDown[' '] )
	{
		ResetZoom();
		update = true;
	}
	if ( keyDown[VK_RETURN] )
	{
		ResetView();
		update = true;
	}

	if ( update )
		InvalidateRect(NULL,FALSE);

}

/////////////////////////////////////////////////////////////////////////////
// Mouse Buttons
void CConStationView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mousePoint = point;
	mouseLDownPoint = point;

	// Editing
	if (makingLine)
	{
		// Try to select star
		int selectedStarNum = SelectStar();

		// If star was selected
		if (selectedStarNum != -1)
		{
			// If this is the first star of the line
			if (prevStarNum == -1)
			{
				prevStarNum = selectedStarNum;
				makingLine = true;
			}
			// Making a line so this should complete a line
			//   and set the previous star number
			else
			{
				// Unless they selected the same star twice
				if (prevStarNum == selectedStarNum)
					return;

				// Make a new line
				pStarfield->AddConstLine(prevStarNum, selectedStarNum);

				prevStarNum = selectedStarNum;

				InvalidateRect(NULL, FALSE);
			}
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
	
	if (editing)
	{
		if (makingLine)
		{
			// If drawing lines
			if (prevStarNum != -1)
				prevStarNum = -1;
			else
				makingLine = false;
		}
		else
			editing = false;
	}

	else
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
	// Zoom faster than with keys
	if (zDelta < 0)
	{
		ZoomOut();
		ZoomOut();
		ZoomOut();
		ZoomOut();
	}
	if (zDelta > 0)
	{
		ZoomIn();
		ZoomIn();
		ZoomIn();
		ZoomIn();
	}

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
		if (makingLine)
		{
			MessageBox("Shouldn't be makingLine and mouseRotating");
			mouseRotatingXY = false;
			mouseRotatingZ = false;
			return;
		}

//		if (mouseRotatingZ)
//			SetCur(IDC_ROTZ);
//		else
//			SetCur(IDC_ROTXY);

		if (mouseRotatingXY && !mouseRotatingZ)
		{
			float newRotX = rotX + (point.y-mouseLDownPoint.y) / 20.0f;// * (1-zoom);
			rotY += (point.x-mouseLDownPoint.x) / 20.0f;// * (1-zoom);

			// Restrict X Rotation
			if ( newRotX > -90 && newRotX < 10)
				rotX = newRotX;
		}
		if (mouseRotatingZ)
			rotZ += (point.y-mouseRDownPoint.y) / 10.0f;// * (1-zoom);

		InvalidateRect(NULL,FALSE);

		// Set the mouse point
		mouseLDownPoint=point;
		mouseRDownPoint=point;
		
		///SetCursorPos(mouseLDownPoint.x, mouseLDownPoint.y);
	}
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

	if (editing)
	{
		if (makingLine)
		{
///			if (prevStarNum != -1 || Select())
///				cursor = IDC_NLINE;
			if (Select())
				cursor = IDC_NLINE;
			else
				cursor = IDC_NLINEG;
		}
	}

	SetCur (cursor);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Selecting

bool CConStationView::Select()
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

	DrawStars();

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
	if (Select())	// If a hit occured in starfield
	{
		int numStar = selectBuffer[3];
		CStar* selectedStar = pStarfield->GetStar(numStar);

		// If there was more than one hit
		for (int i=1; i<hits; i++)
		{
			// Get the brightest
			if (pStarfield->GetStar(selectBuffer[i*4+3])->GetBrightness() >
						selectedStar->GetBrightness())
			{
				numStar = selectBuffer[i*4+3];
				selectedStar = pStarfield->GetStar(numStar);
			}
		}

		/// LUCKY ///
		if (numStar == 11)
			MessageBox("You picked my star you lucky dog!");

		return numStar;
	}
	else return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Constellation editor

void CConStationView::OnEdit() 
{
	if (!mouseRotatingXY && !mouseRotatingZ)
	{
		if (editing)
		{
			makingLine = false;
			deletingLine = false;
		}
		else
		{
			/// SHOULDN'T BE HERE
			pStarfield->AddConstellation();
			pStarfield->SetNumCurConstellation(pStarfield->GetNumConstellations()-1);
		}

		editing = !editing;
	}
}

void CConStationView::OnUpdateEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(editing);
}

void CConStationView::OnNewLine() 
{
	if (mouseRotatingZ)
	{
		MessageBox("You shouldn't be able to call New Line while Mouse Rotating Z");
		mouseRotatingZ = false;
		return;
	}

	if (!mouseRotatingXY)
	{
		if (!makingLine)
			prevStarNum = -1;

		makingLine = !makingLine;
	}
}

void CConStationView::OnUpdateNewLine(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
	pCmdUI->SetCheck(makingLine);
}

void CConStationView::OnDelLine() 
{
	deletingLine = !deletingLine;
}

void CConStationView::OnUpdateDelLine(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
	pCmdUI->SetCheck(deletingLine);
}

/////////////////////////////////////////////////////////////////////////////
// PLACEHOLDERS FOR NOW

void CConStationView::OnUpdateConstellationCreate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
}

void CConStationView::OnUpdateConstellationDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
}

void CConStationView::OnUpdateConstellationLoad(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
}

void CConStationView::OnUpdateConstellationStore(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
}

void CConStationView::OnUpdateConstellationStoreas(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(editing);
}


