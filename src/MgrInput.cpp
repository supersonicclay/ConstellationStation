//===========================================================================
// MgrInput.cpp
//
// CMgrInput
//   handles all user input and selection (not including frame commands).
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
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

// Main handler for left mouse button double click
void CMgrInput::MouseLDbl( CPoint point )
{
	mouseClientPoint = point;

	int constNum = SelectConst();

	// If no constellation was selected
	if( constNum == -1 )
		return;

	constMgr.Select( constNum );
	Redraw();
}

// Main handler for left mouse button down
void CMgrInput::MouseLDown( CPoint point ) 
{
	// Give view the focus
	GetView()->SetFocus();

	GetCursorPos( &mousePoint );
	mouseLPoint = mousePoint;
	mouseClientPoint = point;

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
	GetCursorPos( &mousePoint );
	mouseLPoint = CPoint(0,0);
	mouseClientPoint = point;

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

	GetCursorPos( &mousePoint );
	mouseRPoint = mousePoint;
	mouseClientPoint = point;

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
	GetCursorPos( &mousePoint );
	mouseRPoint = CPoint(0,0);
	mouseClientPoint = point;

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
	GetCursorPos( &mousePoint );
	mouseClientPoint = point;

	switch( state )
	{
	case state_Viewing:
		MouseMoveViewing2();/// PICK ONE
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
///		ShowCursor( FALSE );
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
	starfield.GetCurConst()->GetNewLine()->SetStar1(firstStarNum);
	starfield.GetCurConst()->GetNewLine()->SetStar2(firstStarNum);
	Redraw();
}

void CMgrInput::MouseLDownDeletingLine()
{
	int selectedLineNum = SelectConstLine();

	// If a line was selected
	if( selectedLineNum != -1 )
	{
		starfield.GetCurConst()->DeleteLine(selectedLineNum);
		starfield.SetModified();
		Redraw();
	}
}

void CMgrInput::MouseLUpViewing()
{
	mouseRotatingXY = FALSE;

	if( !mouseRotatingZ )
	{
		ReleaseCapture();
///		ShowCursor( TRUE );
	}
}

void CMgrInput::MouseLUpAddingLine()
{
	if( starfield.GetCurConst()->GetNewLine()->GetStar2() != -1 )
		starfield.GetCurConst()->AddLine();

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
	{
		GetView()->SetCapture();
///		ShowCursor( FALSE );
	}
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
	{
		ReleaseCapture();
///		ShowCursor( TRUE );
	}
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

	if( mouseRotatingZ )
	{
		float deltaTime = (mousePoint.y-mouseRPoint.y) / 10.0f;

		SetCursorPos( mouseRPoint.x, mouseRPoint.y );

		starfield.AdjRotTime( deltaTime );
	}
	else if( mouseRotatingXY )
	{
		float deltaX = (mousePoint.y-mouseLPoint.y) / 20.0f;
		float deltaY = (mousePoint.x-mouseLPoint.x) / 20.0f;

		SetCursorPos( mouseLPoint.x, mouseLPoint.y );

		starfield.AdjRotX( deltaX );
		starfield.AdjRotY( deltaY );
	}

	GetView()->RedrawWindow();  // Force a redraw
}

void CMgrInput::MouseMoveViewing2()
{
	if( !mouseRotatingXY && !mouseRotatingZ )
		return;

	float rotX = starfield.GetRotX();

	if( mouseRotatingXY && !mouseRotatingZ )
	{
		starfield.AdjRotX( (mousePoint.y-mouseLPoint.y) / 20.0f );// * (1-zoom);
		starfield.AdjRotY( (mousePoint.x-mouseLPoint.x) / 20.0f );// * (1-zoom);
	}
	if( mouseRotatingZ )
		starfield.AdjRotTime( (mousePoint.y-mouseRPoint.y) / 10.0f );// * (1-zoom);

	Redraw();

	mouseLPoint = mousePoint;
	mouseRPoint = mousePoint;
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
	starfield.GetCurConst()->GetNewLine()->SetStar2(secondStarNum);

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
	starfield.GetCurConst()->GetNewLine()->SetStar1(-1);
	starfield.GetCurConst()->GetNewLine()->SetStar2(-1);
}

// Try selecting a star or line
//   Names for selection are as follows:
//		0											Terrain
//		1											Star number 0
//		MAX_STARS									Star number (MAX_STARS-1)
//		MAX_STARS+1									Constellation number 0 lines
//		MAX_STARS+1 + (MAX_CONSTS*MAX_CONSTLINES)	Constellation number (MAX_CONSTS-1) Lines
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
		gluPickMatrix( (GLdouble) mouseClientPoint.x, (GLdouble) (viewport[3]-mouseClientPoint.y), 5.0f, 5.0f, viewport );
	else if( selection == select_Line )
		gluPickMatrix( (GLdouble) mouseClientPoint.x, (GLdouble) (viewport[3]-mouseClientPoint.y), 15.0f, 15.0f, viewport );
	else if( selection == select_Const )
		gluPickMatrix( (GLdouble) mouseClientPoint.x, (GLdouble) (viewport[3]-mouseClientPoint.y), 100.0f, 100.0f, viewport );


	// Apply The Perspective Matrix
	graphicsMgr.Perspective();

	glMatrixMode( GL_MODELVIEW );

	if( selection == select_Star )
	{
		// Draw stars
		/// optimize
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.RotateLatitude();
		graphicsMgr.RotateTime();
		graphicsMgr.DrawStars();

		// Draw terrain
		/// optimize
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.PositionTerrain();
		graphicsMgr.DrawTerrain();
	}
	else if( selection == select_Line )
	{
		// Draw current constellation
		/// optimize
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.RotateLatitude();
		graphicsMgr.RotateTime();
		graphicsMgr.DrawConstellation( starfield.GetCurConstNum() );

		// Draw terrain
		/// optimize
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.PositionTerrain();
		graphicsMgr.DrawTerrain();
	}
	else if( selection == select_Const )
	{
		// Draw all constellations
		/// optimize
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.RotateLatitude();
		graphicsMgr.RotateTime();
		graphicsMgr.DrawConstellations();

		// Draw terrain
		/// optimize
		glLoadIdentity();
		graphicsMgr.RotateXY();
		graphicsMgr.PositionTerrain();
		graphicsMgr.DrawTerrain();
	}

	glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix

	glMatrixMode( GL_MODELVIEW );
	hits = glRenderMode( GL_RENDER );								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was

	// Check if there is a hit
	if( hits <= 0 )
		return FALSE;

	// Test if terrain was hit
	for( int i=0; i<hits; i++ )
	{
		// If terrain was hit (terrain is 0)
		if( selectBuffer[i*4 + 3] == 0 )
			return FALSE;
	}

	// Terrain wasn't hit
	return TRUE;
}

// Try selecting a star. Returns -1 if no star was selected
int CMgrInput::SelectStar()
{
	// If no star was selected
	if( !Select(select_Star) )
		return -1;

	int starNum = selectBuffer[3] - 1;	// Subtract 1 because terrain is 0

	// If there was more than one hit
	for( int i=1; i<hits; ++i )
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

// Try selecting a constellation. Returns -1 if no constellation was selected
int CMgrInput::SelectConst()
{
	// If no or more than one line was selected
	if( !Select(select_Const) )
		return -1;

	// Calculate constellation number
	int constNum = (selectBuffer[3] - MAX_STARS - 1) / MAX_CONSTLINES;

	// See if a line from another constellation was selected
	for( int i=1; i<hits; ++i )
	{
		if( (selectBuffer[i*4+3] - MAX_STARS - 1) / MAX_CONSTLINES != constNum )
			return -1;
	}

	// Sanity check
	if( constNum < 0 || constNum > starfield.GetConstCount()-1 )
	{
		CSDebug( "constNum out of range", "CMgrInput::SelectConst" );
		return -1;
	}

	return constNum;
}

// Try selecting a line. Returns -1 if no line was selected
int CMgrInput::SelectConstLine()
{
	// If no or more than one line was selected
	if( !Select(select_Line) || hits > 1 )
		return -1;

	// Calculate line number
	int lineNum = selectBuffer[3] - MAX_STARS - 1 - (starfield.GetCurConstNum()*MAX_CONSTLINES);

	// Sanity check (Select only draws current constellation)
	if( lineNum < 0 || lineNum > starfield.GetCurConst()->GetLineCount()-1 )
	{
		CSDebug( "lineNum out of range", "CMgrInput::SelectConstLine" );
		return -1;
	}

	return lineNum;
}

