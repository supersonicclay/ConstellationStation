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
	mouseRotatingY = FALSE;

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
		graphicsMgr.UpdatePerspMat();
		update = TRUE;
	}
	if( keyDown['Z'] )
	{
		starfield.ZoomOut();
		graphicsMgr.UpdatePerspMat();
		update = TRUE;
	}

	/// Resets
	if( keyDown[' '] )
	{
		starfield.ResetZoom();
		graphicsMgr.UpdatePerspMat();
		keyDown[' '] = FALSE; // Prevent repeat
		update = TRUE;
	}
	if( keyDown[VK_RETURN] )
	{
		starfield.ResetView();
		graphicsMgr.UpdatePerspMat();
		keyDown[VK_RETURN] = FALSE; // Prevent repeat
		update = TRUE;
	}

	/// Debug Terrain View
	if( keyDown[VK_ADD] && keyDown[VK_SHIFT] )
	{
		terrain.IncViewDistance();
		update = TRUE;
	}
	if( keyDown[VK_SUBTRACT] && keyDown[VK_SHIFT] )
	{
		terrain.DecViewDistance();
		update = TRUE;
	}
	if( keyDown[VK_ADD] && !keyDown[VK_SHIFT] )
	{
		terrain.IncViewHeight();
		update = TRUE;
	}
	if( keyDown[VK_SUBTRACT] && !keyDown[VK_SHIFT] )
	{
		terrain.DecViewHeight();
		update = TRUE;
	}
	if( keyDown['E'] )
	{
		keyDown['E'] = FALSE;
		terrExternal = !terrExternal;
		update = TRUE;
	}
	if( keyDown['F'] )
	{
		keyDown['F'] = FALSE;
		terrFog = !terrFog;
		update = TRUE;
	}
	if( keyDown['W'] )
	{
		keyDown['W'] = FALSE;
		terrWire = !terrWire;
		update = TRUE;
	}

	/// Test keys
	if( keyDown['I'] )
	{
		keyDown['I'] = FALSE;
		starfMgr.StarInfo( starfield.GetSun() );///starfield.GetStar(8) );
	}
	if( keyDown[VK_F5] )
	{
		keyDown[VK_F5] = FALSE;
		starfield.ExportConsts();
	}
	if( keyDown[VK_F8] )
	{
		keyDown[VK_F8] = FALSE;
		starfield.ImportConsts();
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

	if( state != state_Viewing )
		return;

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
	mouseRPoint = mousePoint;
	mousePoint.x = point.x;
	mousePoint.y = graphicsMgr.height - point.y;

	GetCursorPos( &mouseScreenPoint );
	mouseScreenRPoint = mouseScreenPoint;

	// Call appropriate function based on state
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

	Redraw();
}

void CMgrInput::MouseLDownViewing()
{
	mouseLDownCoord = GetMouseSphereCoord();

	if( keyDown[VK_SHIFT] || keyDown[VK_CONTROL] || keyDown[VK_TAB] )
	{
		mouseRotatingY = TRUE;
		SetCur( IDC_ROTY );
		if( starfield.GetSpeed() == speed_Now )
			GetFrame()->GetStarfBar()->ChangeSpeed( speed_Realtime );
	}
	else
	{
		mouseRotatingXY = TRUE;
		SetCur( IDC_ROTXY );
		starfield.StopTracking();
	}

	GetView()->SetCapture();
///	ShowCursor( FALSE );
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
	mouseRotatingY = FALSE;

	// Add and clear the temporary rotation
	starfield.AdjRotX( starfield.GetTempRotX() );
	starfield.AdjRotY( starfield.GetTempRotY() );
	starfield.SetTempRotX( 0.0f );
	starfield.SetTempRotY( 0.0f );

	if( !mouseRotatingY )
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
}

void CMgrInput::MouseRDownAddingLine()
{
}

void CMgrInput::MouseRDownDeletingLine()
{
}

// FindMenuItem() will find a menu item string from the specified
// popup menu and returns its position (0-based) in the specified 
// popup menu. It returns -1 if no such menu item string is found.
int FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (strcmp(str, MenuString) == 0))
         return i;
   }

   return -1;
}

void CMgrInput::MouseRUpViewing()
{
	CMenu menu_bar;
	menu_bar.LoadMenu( IDR_POPUP );

	CMenu* constMenu;
	CMenu* starMenu;
	CString constName;
	CString starName;

	// Try to select a constellation and a star
	popupConstNum = SelectConst();
	popupStarNum = SelectStar();

	// Create const menu
	if( popupConstNum != -1 )
	{
		constMenu = menu_bar.GetSubMenu( popup_Constellation );
		if( !constMenu )
		{
			CSDebug( "Can't get submenu of popup menubar", "CMgrInput::MouseRUpViewing" );
			return;
		}
		// Rename first item to name of constellation
		constName = "Constellation: " + starfield.GetConst( popupConstNum )->GetName();
		if( !constMenu->InsertMenu( 0, MF_BYPOSITION | MF_DISABLED, 0, constName ) )
		{
			CSDebug( "Can't rename popup menu item name", "CMgrInput::MouseRUpViewing" );
			return;
		}
	}

	// Create star menu
	if( popupStarNum != -1 )
	{
		starMenu = menu_bar.GetSubMenu( popup_Star );
		if( !starMenu )
		{
			CSDebug( "Can't get submenu of popup menubar", "CMgrInput::MouseRUpViewing" );
			return;
		}

		// Rename first item to name of star
		if( starfield.GetStar( popupStarNum )->GetName().IsEmpty() )
			starName.Format( "Star: HID %d", starfield.GetStar( popupStarNum )->GetHID() );
		else
			starName = "Star: " + starfield.GetStar( popupStarNum )->GetName();
		if( !starMenu->InsertMenu( 0, MF_BYPOSITION | MF_DISABLED, 0, starName ) )
		{
			CSDebug( "Can't rename popup menu item name", "CMgrInput::MouseRUpViewing" );
			return;
		}
	}

	// If both are selected
	if( popupConstNum != -1 && popupStarNum != -1 )
	{
		popup = popup_ConstellationAndStar;

		// Create a menu for each
		CMenu comboMenu;
		if( !comboMenu.CreatePopupMenu() )
		{
			CSDebug( "Can't create combo popup menu", "CMgrInput::MouseRUpViewing" );
			return;
		}
		if( !comboMenu.AppendMenu( MF_POPUP, (UINT)constMenu->GetSafeHmenu(), constName ) )
		{
			CSDebug( "Can't append constellation menu to combo popup menu", "CMgrInput::MouseRUpViewing" );
			return;
		}
		if( !comboMenu.AppendMenu( MF_POPUP, (UINT)starMenu->GetSafeHmenu(), starName ) )
		{
			CSDebug( "Can't append star menu to combo popup menu", "CMgrInput::MouseRUpViewing" );
			return;
		}
		if( !comboMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON, mouseScreenPoint.x, mouseScreenPoint.y, GetFrame() ) )
		{
			CSDebug( "Can't track combo popup menu", "CMgrInput::MouseRUpViewing" );
			return;
		}
	}

	// If just a constellation was selected
	else if( popupConstNum != -1 )
	{
		popup = popup_Constellation;
		if( !constMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON, mouseScreenPoint.x, mouseScreenPoint.y, GetFrame() ) )
		{
			CSDebug( "Can't track constellation popup menu", "CMgrInput::MouseRUpViewing" );
			return;
		}
	}

	// If just a star was selected
	else if( popupStarNum != -1 )
	{
		popup = popup_Star;
		if( !starMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON, mouseScreenPoint.x, mouseScreenPoint.y, GetFrame() ) )
		{
			CSDebug( "Can't track star popup menu", "CMgrInput::MouseRUpViewing" );
			return;
		}
	}
}

void CMgrInput::MouseRUpAddingLine()
{
	SetState( state_Viewing );
}

void CMgrInput::MouseRUpDeletingLine()
{
	SetState( state_Viewing );
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

	graphicsMgr.UpdatePerspMat();

	Redraw();
}


/////////////////////////////////////////////////////////////////////////////
// Mouse Move

void CMgrInput::MouseMoveViewing3()  // Trackball
{
	if( !mouseRotatingXY && !mouseRotatingY )
		return;

	if( mouseRotatingY )
	{
		int diff = mousePoint.y-mouseLPoint.y;
		// Rotate time
		if( keyDown[VK_SHIFT] )
			GetFrame()->GetStarfBar()->AdjustTime( 0, 0, 0, diff, 0 );
		// Rotate Sun
		else if( keyDown[VK_CONTROL] )
			///starfield.GetSun()->AdjRotTime( -diff * 0.002f );
			GetFrame()->GetStarfBar()->AdjustTime( 0, diff, 0, 0, 0 );
		// Rotate latitude
		else if( keyDown[VK_TAB] )
			starfield.AdjLatitude( diff * 0.1f );
		mouseLPoint = mousePoint;
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
	if( !mouseRotatingXY && !mouseRotatingY )
		return;

	if( mouseRotatingY )
	{
		float deltaTime = (mouseScreenPoint.y-mouseScreenRPoint.y);

		SetCursorPos( mouseScreenRPoint.x, mouseScreenRPoint.y );

		GetFrame()->GetStarfBar()->AdjustTime( 0, 0, 0, deltaTime, 0 );
	}

	else if( mouseRotatingXY )
	{
		float deltaX = (mouseScreenPoint.y-mouseScreenLPoint.y) / 200.0f;
		float deltaY = (mouseScreenPoint.x-mouseScreenLPoint.x) / 200.0f;

		SetCursorPos( mouseScreenLPoint.x, mouseScreenLPoint.y );

		starfield.AdjRotX( deltaX, FALSE ); // Prevent matrix update;
		starfield.AdjRotY( deltaY );        // Because it's done here.
	}

	GetView()->RedrawWindow();  // Force a redraw
}

void CMgrInput::MouseMoveViewing()  // Original
{
	if( !mouseRotatingXY && !mouseRotatingY )
		return;

	if( mouseRotatingY )
	{
		int diff = mousePoint.y-mouseRPoint.y;
		// Rotate Sun
		if( keyDown[VK_SHIFT] )
			GetFrame()->GetStarfBar()->AdjustTime( 0, diff, 0, 0, 0 );
		// Rotate latitude
		else if( keyDown[VK_CONTROL] )
			starfield.AdjLatitude( diff * 0.1f );
		// Rotate time
		else
			GetFrame()->GetStarfBar()->AdjustTime( 0, 0, 0, diff, 0 );
		mouseRPoint = mousePoint;
	}

	else if( mouseRotatingXY && !mouseRotatingY )
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
			if ( Select( select_Star, 5.0f ) )
				cursor = IDC_EDITX;
			else
				cursor = IDC_EDIT;
		}
		else
		{
			if( Select( select_Star, 5.0f ) )
				cursor = IDC_ALINEX;
			else
				cursor = IDC_ALINE;
		}
	}
	else if( state == state_DeletingLine )
	{
		if ( Select( select_Line, 15.0f ) )
			cursor = IDC_DLINEX;
		else
			cursor = IDC_DLINE;
	}
	///
	else if( state == state_Viewing )
	{
		if( mouseRotatingXY )
			cursor = IDC_ROTXY;
		else if( mouseRotatingY )
			cursor = IDC_ROTY;
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
//		i+1											Star number i
//		MAX_STARS+1 + i*(MAX_CONSTLINES+1)			Constellation i label
//		MAX_STARS+1 + i*(MAX_CONSTLINES+1) + j + 1	Constellation i line j
BOOL CMgrInput::Select( select_e selection, float radius )
{
	selecting = TRUE;

	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <width>, [3] Is <height>
	GLint	viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	// Tell OpenGL about the selection buffer
	glSelectBuffer( 100, selectBuffer );

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	glRenderMode( GL_SELECT );

	glInitNames();

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix( (GLdouble) mousePoint.x, (GLdouble) mousePoint.y, radius, radius, viewport );

	glMultMatrixf( graphicsMgr.GetPerspMat()->getFloats() );

	glMatrixMode( GL_MODELVIEW );

	if( selection == select_Star )
	{
		// Draw stars
		if( starfield.AreStarsVisible() && graphicsMgr.starAlpha > 0.0f )
		{
			glLoadMatrixf( graphicsMgr.starfMat.getFloats() );
			graphicsMgr.DrawStars();
		}

		// Draw terrain
		if( optionsMgr.IsTerrVisible() )
		{
			glLoadMatrixf( graphicsMgr.terrainMat.getFloats() );
			graphicsMgr.DrawTerrain();
		}
	}
	else if( selection == select_Line )
	{
		// Draw current constellation
		glLoadMatrixf( graphicsMgr.starfMat.getFloats() );
		graphicsMgr.DrawCurConst( starfield.GetCurConstNum() );

		// Draw terrain
		if( optionsMgr.IsTerrVisible() )
		{
			glLoadMatrixf( graphicsMgr.terrainMat.getFloats() );
			graphicsMgr.DrawTerrain();
		}
	}
	else if( selection == select_Const )
	{

		// Draw all constellations
		if( starfield.AreConstsVisible() && graphicsMgr.constAlpha > 0.0f )
		{
			glLoadMatrixf( graphicsMgr.starfMat.getFloats() );
			graphicsMgr.DrawConsts();
		}

		// Draw terrain
		if( optionsMgr.IsTerrVisible() )
		{
			glLoadMatrixf( graphicsMgr.terrainMat.getFloats() );
			graphicsMgr.DrawTerrain();
		}
	}

	glMatrixMode( GL_MODELVIEW );
	hits = glRenderMode( GL_RENDER );

	selecting = FALSE;

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

	// There was at least one hit and it wasn't the terrain
	return TRUE;
}

// Try selecting a star. Returns -1 if no star was selected
int CMgrInput::SelectStar()
{
	// If no star was selected
	if( !Select( select_Star, 5.0f ) )
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
	float radius = 100.0f;
	int constNum;

	// Try smaller and smaller radius up to 3 times
	for( int i=0; i<3; ++i )
	{
		// If no line was selected
		///if( !Select( select_Const, 100.0f ) ) why was this 100? Think it's supposed to be radius
		if( !Select( select_Const, radius ) )
			return -1;

		// Calculate constellation number
		constNum = (selectBuffer[3] - MAX_STARS - 1) / (MAX_CONSTLINES+1);

		// See if a line from another constellation was selected
		for( int j=1; j<hits; ++j )
		{
			if( (selectBuffer[j*4+3] - MAX_STARS - 1) / (MAX_CONSTLINES+1) != constNum )
			{
				// Set constNum to undefined and decrease radius.
				constNum = -1;
				radius*=0.75f;
			}
		}

		if( constNum != -1 )
			break;
	}

	// Sanity check
	if( constNum < -1 || constNum > starfield.GetConstCount()-1 )
	{
		CSDebug( "constNum out of range", "CMgrInput::SelectConst" );
		return -1;
	}

	return constNum;
}

// Try selecting a line. Returns -1 if no line was selected
int CMgrInput::SelectConstLine()
{
	float radius = 15.0f;

	// Try smaller and smaller radius up to 3 times
	for( int i=0; i<3; ++i )
	{
		if( !Select( select_Line, radius ) )
			return -1;
		else if( hits > 1 )
			radius*=0.75f;
		else
			break;
	}

	// If more than one line was selected
	if( hits > 1 )
		return -1;

	// Calculate line number
	int lineNum = selectBuffer[3] - MAX_STARS - 1 - starfield.GetCurConstNum()*(MAX_CONSTLINES+1) - 1;

	// Sanity check (Select only draws current constellation)
	if( lineNum < 0 || lineNum > starfield.GetCurConst()->GetLineCount()-1 )
	{
		CSDebug( "lineNum out of range", "CMgrInput::SelectConstLine" );
		return -1;
	}

	return lineNum;
}

