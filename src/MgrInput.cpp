//===========================================================================
// MgrInput.cpp
//
// CMgrInput
//   user interface class. Handles all user input including mouse, keyboard,
//   and commands.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrInput::CMgrInput()
{
	for( int i=0; i<256; i++ )
		keyDown[i] = FALSE;

	mouseRotatingXY = FALSE;
	mouseRotatingZ = FALSE;

	firstStarNum = secondStarNum = -1;
}

CMgrInput::~CMgrInput()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

/////////////////////////////////////////////////////////////////////////////
// Keyboard

// Key is down
void CMgrInput::KeyDown( UINT nChar ) 
{
	keyDown[nChar] = TRUE;
}

// Key is up
void CMgrInput::KeyUp( UINT nChar ) 
{
	keyDown[nChar] = FALSE;
}

// Called rapidly so animation is smooth
void CMgrInput::ProcessKeys()
{
	// Don't handle view keys if
	if( state != state_Viewing )
		return;

	BOOL update = FALSE;

	// Rotating
	if( keyDown[VK_UP] )
	{
		starfield.RotateUp();
		update = TRUE;
	}
	if( keyDown[VK_DOWN] )
	{
		starfield.RotateDown();
		update = TRUE;
	}
	if( keyDown[VK_RIGHT] )
	{
		starfield.RotateRight();
		update = TRUE;
	}
	if( keyDown[VK_LEFT] )
	{
		starfield.RotateLeft();
		update = TRUE;
	}

	// Zooming
	if( keyDown['X'] )
	{
		starfield.ZoomIn();
		graphicsMgr.Projection();
		update = TRUE;
	}
	if( keyDown['Z'] )
	{
		starfield.ZoomOut();
		graphicsMgr.Projection();
		update = TRUE;
	}

	// Resets
	if( keyDown[' '] )
	{
		starfield.ResetZoom();
		graphicsMgr.Projection();
		update = TRUE;
	}
	if( keyDown[VK_RETURN] )
	{
		starfield.ResetView();
		graphicsMgr.Projection();
		update = TRUE;
	}

	if( update )
		Redraw();
}


/////////////////////////////////////////////////////////////////////////////
// Mouse handlers

// Main handler for left mouse button down
void CMgrInput::MouseLDown( CPoint point ) 
{
	// Give view the focus
	GetView()->SetFocus();

	mousePoint = point;
	mouseLDownPoint = point;

	// Call appropriate function based on state
	switch( state )
	{
	case state_Viewing:
		MouseLDownViewing();
		break;
	case state_AddingLine:
		MouseLDownAddingLine();
		break;
	case state_DeletingLine:
		MouseLDownDeletingLine();
		break;
	default:
		break;
	}
}

// Main handler for left mouse button up
void CMgrInput::MouseLUp( CPoint point ) 
{
	mousePoint = point;
	mouseLDownPoint = CPoint(0,0);

	switch( state )
	{
	case state_Viewing:
		MouseLUpViewing();
		break;
	case state_AddingLine:
		MouseLUpAddingLine();
		break;
	case state_DeletingLine:
		MouseLUpDeletingLine();
		break;
	default:
		break;
	}
}

// Main handler for right mouse button down
void CMgrInput::MouseRDown( CPoint point ) 
{
	// Give view the focus
	GetView()->SetFocus();

	mousePoint = point;
	mouseRDownPoint = point;

	switch( state )
	{
	case state_Viewing:
		MouseRDownViewing();
		break;
	case state_AddingLine:
		MouseRDownAddingLine();
		break;
	case state_DeletingLine:
		MouseRDownDeletingLine();
		break;
	default:
		break;
	}
}

// Main handler for right mouse button up
void CMgrInput::MouseRUp( CPoint point ) 
{
	mousePoint = point;
	mouseRDownPoint = CPoint(0,0);

	switch( state )
	{
	case state_Viewing:
		MouseRUpViewing();
		break;
	case state_AddingLine:
		MouseRUpAddingLine();
		break;
	case state_DeletingLine:
		MouseRUpDeletingLine();
		break;
	default:
		break;
	}
}

// Main handler for mouse move
void CMgrInput::MouseMove( CPoint point ) 
{
	mousePoint = point;

	switch( state )
	{
	case state_Viewing:
		MouseMoveViewing();
		break;
	case state_AddingLine:
		MouseMoveAddingLine();
		break;
	case state_DeletingLine:
		MouseMoveDeletingLine();
		break;
	default:
		break;
	}


}


/////////////////////////////////////////////////////////////////////////////
// Left mouse button

void CMgrInput::MouseLDownViewing()
{
	// Start rotating XY
	mouseRotatingXY = TRUE;

	if( !mouseRotatingZ )
	{
		SetCur(IDC_ROTXY);
		GetView()->SetCapture();
	}
}

void CMgrInput::MouseLDownAddingLine()
{
	// Try to select star
	int selectedStarNum = SelectStar();

	// If no star was selected
	if( selectedStarNum == -1 )
		return;

	firstStarNum = selectedStarNum;

	// Set newline's first and second star
	starfield.GetCurConstellation()->GetNewLine()->SetStar1(firstStarNum);
	starfield.GetCurConstellation()->GetNewLine()->SetStar2(firstStarNum);
	Redraw();
}

void CMgrInput::MouseLDownDeletingLine()
{
	int selectedLineNum = SelectConstLine();

	// If a line was selected
	if( selectedLineNum != -1 )
	{
		starfield.GetCurConstellation()->DeleteLine(selectedLineNum);
		starfield.SetModified();
		Redraw();
	}
}

void CMgrInput::MouseLUpViewing()
{
	mouseRotatingXY = FALSE;

	if( !mouseRotatingZ )
		ReleaseCapture();
}

void CMgrInput::MouseLUpAddingLine()
{
	if( starfield.GetCurConstellation()->GetNewLine()->GetStar2() != -1 )
		starfield.GetCurConstellation()->AddLine();

	ClearSelection();

	Redraw();
}

void CMgrInput::MouseLUpDeletingLine()
{
}


/////////////////////////////////////////////////////////////////////////////
// Right mouse button

void CMgrInput::MouseRDownViewing()
{
	mouseRotatingZ = TRUE;

	SetCur(IDC_ROTZ);
	if( !mouseRotatingXY )
		GetView()->SetCapture();
}

void CMgrInput::MouseRDownAddingLine()
{
	SetState( state_Viewing );
	Redraw();
}

void CMgrInput::MouseRDownDeletingLine()
{
	SetState( state_Viewing );
}

void CMgrInput::MouseRUpViewing()
{
	mouseRotatingZ = FALSE;
	if( !mouseRotatingXY )
		ReleaseCapture();
	else
		SetCur(IDC_ROTXY);
}

void CMgrInput::MouseRUpAddingLine()
{
}

void CMgrInput::MouseRUpDeletingLine()
{
}


/////////////////////////////////////////////////////////////////////////////
// Mouse Wheel

// Mouse wheel handler
void CMgrInput::MouseWheel( short zDelta ) 
{
	// Don't process if not viewing
	if( state != state_Viewing )
		return;

	// Zoom faster than with keys
	if( zDelta < 0 )
	{
		starfield.ZoomOut();
		starfield.ZoomOut();
		starfield.ZoomOut();
		starfield.ZoomOut();
	}
	if( zDelta > 0 )
	{
		starfield.ZoomIn();
		starfield.ZoomIn();
		starfield.ZoomIn();
		starfield.ZoomIn();
	}

	graphicsMgr.Projection();

	Redraw();
}


/////////////////////////////////////////////////////////////////////////////
// Mouse Move

void CMgrInput::MouseMoveViewing()
{
	if( !mouseRotatingXY && !mouseRotatingZ )
		return;

	float rotX = starfield.GetRotX();

	if( mouseRotatingXY && !mouseRotatingZ )
	{
		starfield.AdjRotX( (mousePoint.y-mouseLDownPoint.y) / 20.0f );// * (1-zoom);
		starfield.AdjRotY( (mousePoint.x-mouseLDownPoint.x) / 20.0f );// * (1-zoom);
	}
	if( mouseRotatingZ )
		starfield.AdjRotTime( (mousePoint.y-mouseRDownPoint.y) / 10.0f );// * (1-zoom);

	Redraw();

	mouseLDownPoint = mousePoint;
	mouseRDownPoint = mousePoint;
}

void CMgrInput::MouseMoveAddingLine()
{
	// If we haven't selected first star yet
	if( firstStarNum == -1 )
		return;

	// Try to select star
	int selectedStarNum = SelectStar();

	// If no new star was selected
	if( selectedStarNum == -1 || selectedStarNum == secondStarNum )
		return;

	// Set second star
	secondStarNum = selectedStarNum;
	starfield.GetCurConstellation()->GetNewLine()->SetStar2(secondStarNum);

	Redraw();
}

void CMgrInput::MouseMoveDeletingLine()
{
}

/////////////////////////////////////////////////////////////////////////////
// Cursor

// Determine what cursor to use
void CMgrInput::DetermineCursor() 
{
	WORD cursor = IDC_POINT;

	if( state == state_AddingLine )
	{
		if( firstStarNum == -1 )
		{
			if ( Select(select_Star) )
				cursor = IDC_EDITX;
			else
				cursor = IDC_EDIT;
		}
		else
		{
			if( Select(select_Star) )
				cursor = IDC_ALINEX;
			else
				cursor = IDC_ALINE;
		}
	}
	else if( state == state_DeletingLine )
	{
		if ( Select(select_Line) )
			cursor = IDC_DLINEX;
		else
			cursor = IDC_DLINE;
	}

	SetCur( cursor );
}

// Set cursor from a give resource id
void CMgrInput::SetCur( WORD cur )
{
	SetCursor( LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(cur)) );
}


/////////////////////////////////////////////////////////////////////////////
// Selecting

// No star has been selected
void CMgrInput::ClearSelection()
{
	firstStarNum = secondStarNum = -1;
	starfield.GetCurConstellation()->GetNewLine()->SetStar1(-1);
	starfield.GetCurConstellation()->GetNewLine()->SetStar2(-1);
}

// Try selecting a star or line
BOOL CMgrInput::Select( select_e selection )
{
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <width>, [3] Is <height>
	GLint	viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	glSelectBuffer( 100, selectBuffer );							// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	glRenderMode( GL_SELECT );

	glInitNames();												// Initializes The Name Stack

	glMatrixMode( GL_PROJECTION );								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	if( selection == select_Star )
		gluPickMatrix( (GLdouble) mousePoint.x, (GLdouble) (viewport[3]-mousePoint.y), 5.0f, 5.0f, viewport );
	else if( selection == select_Line )
		gluPickMatrix( (GLdouble) mousePoint.x, (GLdouble) (viewport[3]-mousePoint.y), 15.0f, 15.0f, viewport );


	// Apply The Perspective Matrix
	graphicsMgr.Perspective();

	glMatrixMode( GL_MODELVIEW );

	if( selection == select_Star )
	{
		// Draw stars
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.RotateLatitude();
		graphicsMgr.RotateTime();
		graphicsMgr.DrawStars();

		// Draw terrain
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.PositionTerrain();
		graphicsMgr.DrawTerrain();
	}
	else if( selection == select_Line )
	{
		// Draw current constellation
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.RotateLatitude();
		graphicsMgr.RotateTime();
		graphicsMgr.DrawConstellation( starfield.GetNumCurConstellation() );
	}

	glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix

	glMatrixMode( GL_MODELVIEW );
	hits = glRenderMode( GL_RENDER );								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was

	// Check if there is a hit
	if( hits <= 0 )
		return FALSE;

	/// Do test whether star or line!!!!!
	// Test if terrain was hit
	if( selection == select_Star )
	{
		for( int i=0; i<hits; i++ )
		{
			// If terrain was hit (terrain is 0)
			if( selectBuffer[i*4 + 3] == 0 )
				return FALSE;
		}

		// Terrain wasn't hit
		return TRUE;
	}
	else
	{
		return TRUE;
	}
}

// Try selecting a star. Returns -1 if no star was selected
int CMgrInput::SelectStar()
{
	// If no star was selected
	if( !Select(select_Star) )
		return -1;

	int starNum = selectBuffer[3] - 1;	// Subtract 1 because terrain is 0

	// If there was more than one hit
	for( int i=1; i<hits; i++ )
	{
		// Get the brightest
		if( starfield.GetStar(selectBuffer[i*4+3]-1)->GetMag() <
					starfield.GetStar(starNum)->GetMag() )
		{
			starNum = selectBuffer[i*4+3] - 1;	// Subtract 1 because terrain is 0
		}
	}
	return starNum;
}

// Try selecting a line. Returns -1 if no line was selected
int CMgrInput::SelectConstLine()
{
	// If no or more than one line was selected
	if( !Select(select_Line) || hits > 1 )
		return -1;

	return selectBuffer[3];
}

