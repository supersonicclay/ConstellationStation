//===========================================================================
// CSView.cpp
//
// CCSView
//   forwards input events to CInput and directs CGraphics.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"

#include "CSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CCSView, CWnd)
	//{{AFX_MSG_MAP(CCSView)
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
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CCSView::CCSView()
{
}

CCSView::~CCSView()
{
}

BOOL CCSView::PreCreateWindow(CREATESTRUCT& cs)
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
// CCSView message handlers

int CCSView::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Try initializing OpenGL
	if( !graphicsMgr.InitializeOpenGL() )
	{
		CSDebug( "Error initializing OpenGL", "CCSView::OnCreate" );
		graphicsMgr.Destroy();
		exit(0);
		return -1;
	}

	SetTimer( 1, 20, NULL );

	return 0;
}

void CCSView::OnDestroy() 
{
	graphicsMgr.Destroy();
}

BOOL CCSView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	// Don't erase the background
}

void CCSView::OnSize(UINT nType, int cx, int cy) 
{
	graphicsMgr.Size( cx, cy );
}


/////////////////////////////////////////////////////////////////////////////
// Drawing

void CCSView::OnDraw(CDC* pDC) 
{
	graphicsMgr.Draw();
}

void CCSView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	graphicsMgr.Draw();
}


/////////////////////////////////////////////////////////////////////////////
// Keyboard
void CCSView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	inputMgr.KeyDown( nChar );
}

void CCSView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	inputMgr.KeyUp( nChar );
}

// Timer for animation
void CCSView::OnTimer(UINT nIDEvent)
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
void CCSView::OnLButtonDown(UINT nFlags, CPoint point)
{
	inputMgr.MouseLDown( point );
}

void CCSView::OnLButtonUp(UINT nFlags, CPoint point)
{
	inputMgr.MouseLUp( point );
}

void CCSView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	inputMgr.MouseLDbl( point );
}

void CCSView::OnRButtonDown(UINT nFlags, CPoint point)
{
	inputMgr.MouseRDown( point );
}

void CCSView::OnRButtonUp(UINT nFlags, CPoint point)
{
	inputMgr.MouseRUp( point );
}

BOOL CCSView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	inputMgr.MouseWheel( zDelta );
	return TRUE;
}

void CCSView::OnMouseMove(UINT nFlags, CPoint point)
{
	inputMgr.MouseMove( point );
}

/////////////////////////////////////////////////////////////////////////////
// Cursor
BOOL CCSView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	inputMgr.DetermineCursor();
	return TRUE;
}









