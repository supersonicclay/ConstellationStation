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
	for( int i=0; i<256; ++i )
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
	// Don't handle view keys if..
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

	/// Resets
	if( keyDown[' '] )
	{
		starfield.ResetZoom();
		graphicsMgr.Projection();
		keyDown[' '] = FALSE; // Prevent repeat
		update = TRUE;
	}
	if( keyDown[VK_RETURN] )
	{
		starfield.ResetView();
		graphicsMgr.Projection();
		keyDown[VK_RETURN] = FALSE; // Prevent repeat
		update = TRUE;
	}

	/// Test Terrain Height
	if( keyDown[VK_ADD] )
	{
		terrain.IncViewHeight();
		update = TRUE;
	}
	if( keyDown[VK_SUBTRACT] )
	{
		terrain.DecViewHeight();
		update = TRUE;
	}

	/// Test finding and tracking
	if( keyDown['T'] )
	{
		keyDown['T'] = FALSE; // Prevent repeat
		starfMgr.StartTracking( starfield.GetConst(0) );
//		starfMgr.Find( starfield.GetConst(0) );
		// 8 = Betelgeuse
//		starfMgr.StartTracking( starfield.GetStar(8) );
//		starfMgr.Find( starfield.GetStar(8) );
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
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );

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

	mouseLPoint = mousePoint;
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );
	mouseScreenLPoint = mouseScreenPoint;

	// Call appropriate function based on state
	switch( state )
	{
	case state_Viewing:
		MouseLDownViewing();
//		MouseLDownTest();
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
	mouseLPoint = CPoint(0,0);
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );
	mouseScreenLPoint = CPoint(0,0);

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

	mouseRPoint = mousePoint;
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );
	mouseScreenRPoint = mouseScreenPoint;

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
	mouseRPoint = CPoint(0,0);
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );
	mouseScreenRPoint = CPoint(0,0);

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
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );

	switch( state )
	{
	case state_Viewing:
		MouseMoveViewing3();/// PICK ONE
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

void CMgrInput::MouseLDownTest()///
{
	// Find coordinates on celestial sphere
	vector3 coord = GetMouseSphereCoord();

	int selectedStarNum = SelectStar();
	if( selectedStarNum != -1 )
		starfield.GetStar( selectedStarNum )->SetColor( COLOR_GREEN );

	Redraw();
}

void CMgrInput::MouseLDownViewing()
{
	// Start rotating XY
	mouseRotatingXY = TRUE;

	mouseLDownCoord = GetMouseSphereCoord();

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
		documentMgr.SetModified();
		Redraw();
	}

	// Set active line number to -1
	starfield.GetCurConst()->SetActiveLineNum( -1 );
}

void CMgrInput::MouseLUpViewing()
{
	mouseRotatingXY = FALSE;

	// Add and clear the temporary rotation
	starfield.AdjRotX( starfield.GetTempRotX() );
	starfield.AdjRotY( starfield.GetTempRotY() );
	starfield.SetTempRotX( 0.0f );
	starfield.SetTempRotY( 0.0f );

	if( !mouseRotatingZ )
	{
		ReleaseCapture();
///		ShowCursor( TRUE );
	}
}

void CMgrInput::MouseLUpAddingLine()
{
	if( starfield.GetCurConst()->GetNewLine()->GetStar2() != -1 )
	{
		starfield.GetCurConst()->AddLine();
		documentMgr.SetModified();
	}

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

void CMgrInput::MouseMoveViewing3()  // Trackball
{
	if( !mouseRotatingXY && !mouseRotatingZ )
		return;

	if( mouseRotatingZ )
	{
		// If shift is down, it only rotates sun
		if( keyDown[VK_SHIFT] )
			starfield.GetSun()->AdjRotTime( (mousePoint.y-mouseRPoint.y) / 10.0f );
		else
			starfield.AdjRotTime( (mousePoint.y-mouseRPoint.y) / 10.0f );// * (1-zoom);
		mouseRPoint = mousePoint;
	}

	else if( mouseRotatingXY )
	{
		// Find coordinates on outside sphere
		mouseCoord = GetMouseSphereCoord();

		// Intermediate coordinate
		vector3 c;
		c.x = mouseCoord.x;
		c.y = mouseLDownCoord.y;
		c.z = -(float)sqrt(1.0f-c.x*c.x-c.y*c.y);

		/// Calculate y-axis rotation necessary (mouseLDownCoord -> intermediate)
		float cosY = DotProduct( mouseLDownCoord, c );
		if( cosY > 1.0f )
			cosY = 1.0f;
		float rotY = (float)acos( cosY );

		/// Calculate x-axis rotation necessary (intermediate -> mouseCoord)
		float cosX = DotProduct( c, mouseCoord );
		if( cosX > 1.0f )
			cosX = 1.0f;
		float rotX = (float)acos( cosX );

		// Since dot product doesn't give use direction info
		if( mouseCoord.x > mouseLDownCoord.x )
			starfield.SetTempRotY( -rotY );
		else
			starfield.SetTempRotY( rotY );
		if( mouseCoord.y < mouseLDownCoord.y )
			starfield.SetTempRotX( -rotX );
		else
			starfield.SetTempRotX( rotX );
	}

	Redraw();
}

void CMgrInput::MouseMoveViewing2()  // Mouse stays in place
{
	if( !mouseRotatingXY && !mouseRotatingZ )
		return;

	if( mouseRotatingZ )
	{
		float deltaTime = (mouseScreenPoint.y-mouseScreenRPoint.y) / 10.0f;

		SetCursorPos( mouseScreenRPoint.x, mouseScreenRPoint.y );

		starfield.AdjRotTime( deltaTime );
	}

	else if( mouseRotatingXY )
	{
		float deltaX = (mouseScreenPoint.y-mouseScreenLPoint.y) / 200.0f;
		float deltaY = (mouseScreenPoint.x-mouseScreenLPoint.x) / 200.0f;

		SetCursorPos( mouseScreenLPoint.x, mouseScreenLPoint.y );

		starfield.AdjRotX( deltaX, FALSE ); // Prevent matrix update;
		starfield.AdjRotY( deltaY );        // it's done here.
	}

	GetView()->RedrawWindow();  // Force a redraw
}

void CMgrInput::MouseMoveViewing()  // Original
{
	if( !mouseRotatingXY && !mouseRotatingZ )
		return;

	if( mouseRotatingZ )
		starfield.AdjRotTime( (mousePoint.y-mouseRPoint.y) / 10.0f );// * (1-zoom);

	else if( mouseRotatingXY && !mouseRotatingZ )
	{
		starfield.AdjRotX( (mousePoint.y-mouseLPoint.y) / 20.0f, FALSE );// * (1-zoom);
		starfield.AdjRotY( -(mousePoint.x-mouseLPoint.x) / 20.0f );// * (1-zoom);
	}

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
	// Set active line number to selected line number
	starfield.GetCurConst()->SetActiveLineNum( SelectConstLine() );
	Redraw();
}

// Find the coordinate on the outside sphere based on mouse's position
vector3 CMgrInput::GetMouseSphereCoord()
{
	float  spread = (float)tan( DegToRad(graphicsMgr.fov/2.0f) );
	return vector3(
		spread * (mousePoint.x-graphicsMgr.width/2.0f)  /(graphicsMgr.height/2.0f),
		spread * (mousePoint.y-graphicsMgr.height/2.0f) /(graphicsMgr.height/2.0f),
		-1.0f ).normalize();
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
	starfield.GetCurConst()->GetNewLine()->SetStar1( -1 );
	starfield.GetCurConst()->GetNewLine()->SetStar2( -1 );
	starfield.GetCurConst()->SetActiveLineNum( -1 );
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

	// Tell OpenGL about the selection buffer
	glSelectBuffer( 100, selectBuffer );

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	glRenderMode( GL_SELECT );

	glInitNames();

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	if( selection == select_Star )
		gluPickMatrix( (GLdouble) mousePoint.x, (GLdouble) mousePoint.y, 5.0f, 5.0f, viewport );
	else if( selection == select_Line )
		gluPickMatrix( (GLdouble) mousePoint.x, (GLdouble) mousePoint.y, 15.0f, 15.0f, viewport );
	else if( selection == select_Const )
		gluPickMatrix( (GLdouble) mousePoint.x, (GLdouble) mousePoint.y, 100.0f, 100.0f, viewport );

	// Apply The Perspective Matrix
	graphicsMgr.Perspective();

	glMatrixMode( GL_MODELVIEW );

	if( selection == select_Star )
	{
		// Draw stars
		graphicsMgr.LoadStarfMat();
		graphicsMgr.DrawStars();

		// Draw terrain
		if( optionsMgr.IsTerrVisible() )
		{
			graphicsMgr.LoadTerrainMat();
			graphicsMgr.DrawTerrain();
		}
	}
	else if( selection == select_Line )
	{
		// Draw current constellation
		graphicsMgr.LoadStarfMat();
		graphicsMgr.DrawCurConst( starfield.GetCurConstNum() );

		// Draw terrain
		if( optionsMgr.IsTerrVisible() )
		{
			graphicsMgr.LoadTerrainMat();
			graphicsMgr.DrawTerrain();
		}
	}
	else if( selection == select_Const )
	{
		// Draw all constellations
		graphicsMgr.LoadStarfMat();
		graphicsMgr.DrawConsts();

		// Draw terrain
		if( optionsMgr.IsTerrVisible() )
		{
			graphicsMgr.LoadTerrainMat();
			graphicsMgr.DrawTerrain();
		}
	}

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	hits = glRenderMode( GL_RENDER );

	// Check if there is a hit
	if( hits <= 0 )
		return FALSE;

	// Test if terrain was hit
	for( int i=0; i<hits; ++i )
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

