//===========================================================================
// ConStationView.cpp
//
// CConStationView
//   forwards input events to CInput and directs CGraphics
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"

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

BEGIN_MESSAGE_MAP(CConStationView, CWnd)
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
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConStationView construction/destruction

CConStationView::CConStationView()
{
}

CConStationView::~CConStationView()
{
}

BOOL CConStationView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_EX_CLIENTEDGE; //WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_OWNDC ;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	cs.cx = 600;
	cs.cy = 400;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CConStationView message handlers

int CConStationView::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Initialize OpenGL
	if (!graphicsMgr.InitializeOpenGL())
		CSError( "Error initializing OpenGL", "CConStationView::OnCreate" );

	SetTimer( 1, 20, NULL );

	return 0;
}

void CConStationView::OnDestroy() 
{
	graphicsMgr.Destroy();
}

BOOL CConStationView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	// Don't erase the background
}

void CConStationView::OnSize(UINT nType, int cx, int cy) 
{
	graphicsMgr.Size( cx, cy );
}


/////////////////////////////////////////////////////////////////////////////
// Drawing

void CConStationView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	graphicsMgr.Draw();
}


/////////////////////////////////////////////////////////////////////////////
// Keyboard
void CConStationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	inputMgr.KeyDown( nChar );
}

void CConStationView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	inputMgr.KeyUp( nChar );
}

// Timer for animation
void CConStationView::OnTimer(UINT nIDEvent)
{
	inputMgr.ProcessKeys();

	if (starfield.IsSpinning() &&
		state == state_Viewing)
	{
//		starfield.AdjRotTime(0.05f);
		starfield.AdjRotTime(0.5f);
		Redraw();
	}
}


/////////////////////////////////////////////////////////////////////////////
// Mouse
void CConStationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	inputMgr.MouseLDown( point );
}

void CConStationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	inputMgr.MouseLUp( point );
}

void CConStationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	inputMgr.MouseRDown( point );
}

void CConStationView::OnRButtonUp(UINT nFlags, CPoint point)
{
	inputMgr.MouseRUp( point );
}

BOOL CConStationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	inputMgr.MouseWheel( zDelta );
	return TRUE;
}

void CConStationView::OnMouseMove(UINT nFlags, CPoint point)
{
	inputMgr.MouseMove( point );
}

/////////////////////////////////////////////////////////////////////////////
// Cursor
BOOL CConStationView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	inputMgr.DetermineCursor();
	return TRUE;
}







