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
		keyDown[i] = false;

	mouseRotatingXY = false;
	mouseRotatingZ = false;
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
	keyDown[nChar] = true;
}

// Key is up
void CMgrInput::KeyUp( UINT nChar ) 
{
	keyDown[nChar] = false;
}

// Called rapidly so animation is smooth
void CMgrInput::ProcessKeys()
{
	// Don't handle view keys if
	if (state != state_Viewing)
		return;

	BOOL update = false;

	// Rotating
	if ( keyDown[VK_UP] )
	{
		starfield.RotateUp();
		update = true;
	}
	if ( keyDown[VK_DOWN] )
	{
		starfield.RotateDown();
		update = true;
	}
	if ( keyDown[VK_RIGHT] )
	{
		starfield.RotateRight();
		update = true;
	}
	if ( keyDown[VK_LEFT] )
	{
		starfield.RotateLeft();
		update = true;
	}

	// Zooming
	if ( keyDown['X'] )
	{
		starfield.ZoomIn();
		graphicsMgr.Projection();
		update = true;
	}
	if ( keyDown['Z'] )
	{
		starfield.ZoomOut();
		graphicsMgr.Projection();
		update = true;
	}

	// Resets
	if ( keyDown[' '] )
	{
		starfield.ResetZoom();
		graphicsMgr.Projection();
		update = true;
	}
	if ( keyDown[VK_RETURN] )
	{
		starfield.ResetView();
		graphicsMgr.Projection();
		update = true;
	}

	if ( update )
		Redraw();
}


/////////////////////////////////////////////////////////////////////////////
// Mouse Buttons

// Main handler for left mouse button down
void CMgrInput::MouseLDown(  CPoint point ) 
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


/////////////////////////////////////////////////////////////////////////////
// Left mouse button

void CMgrInput::MouseLDownViewing()
{
	// Start rotating XY
	mouseRotatingXY = true;

	if (!mouseRotatingZ)
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
	if (selectedStarNum == -1)
		return;

	// If this is the first star of the line
	if (prevStarNum == -1)
		prevStarNum = selectedStarNum;

	// Adding a line so this should complete a line
	//   and set the previous star number
	else
	{
		// Unless they selected the same star twice
		if (prevStarNum == selectedStarNum)
			return;

		// Make a new line
		starfield.GetCurConstellation()->AddLine( prevStarNum, selectedStarNum );

		prevStarNum = selectedStarNum;

		starfield.SetModified();
		Redraw();
	}
}

void CMgrInput::MouseLDownDeletingLine()
{
	int selectedLineNum = SelectConstLine();

	// If a line was selected
	if (selectedLineNum != -1)
	{
		starfield.GetCurConstellation()->DeleteLine(selectedLineNum);
		starfield.SetModified();
		Redraw();
	}
}

void CMgrInput::MouseLUpViewing()
{
	mouseRotatingXY = false;

	if (!mouseRotatingZ)
		ReleaseCapture();
}

void CMgrInput::MouseLUpAddingLine()
{
}

void CMgrInput::MouseLUpDeletingLine()
{
}


/////////////////////////////////////////////////////////////////////////////
// Right mouse button

void CMgrInput::MouseRDownViewing()
{
	mouseRotatingZ = true;

	SetCur(IDC_ROTZ);
	if (!mouseRotatingXY)
		GetView()->SetCapture();
}

void CMgrInput::MouseRDownAddingLine()
{
	prevStarNum = -1;
	SetState( state_Viewing );
}

void CMgrInput::MouseRDownDeletingLine()
{
	SetState( state_Viewing );
}

void CMgrInput::MouseRUpViewing()
{
	mouseRotatingZ = false;
	if (!mouseRotatingXY)
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
	if (zDelta < 0)
	{
		starfield.ZoomOut();
		starfield.ZoomOut();
		starfield.ZoomOut();
		starfield.ZoomOut();
	}
	if (zDelta > 0)
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

// Mouse moved
void CMgrInput::MouseMove( CPoint point ) 
{
	mousePoint = point;

	if (mouseRotatingXY || mouseRotatingZ)
	{
		if (state != state_Viewing)
		{
			CSWarn("Shouldn't be able to Mouse Rotate");
			mouseRotatingXY = false;
			mouseRotatingZ = false;
			return;
		}

		float rotX = starfield.GetRotX();

		if (mouseRotatingXY && !mouseRotatingZ)
		{
			starfield.AdjRotX((point.y-mouseLDownPoint.y) / 20.0f);// * (1-zoom);
			starfield.AdjRotY((point.x-mouseLDownPoint.x) / 20.0f);// * (1-zoom);
		}
		if (mouseRotatingZ)
			starfield.AdjRotTime((point.y-mouseRDownPoint.y) / 10.0f);// * (1-zoom);

		Redraw();

		// Set the mouse point
		mouseLDownPoint=point;
		mouseRDownPoint=point;

	}

}

/////////////////////////////////////////////////////////////////////////////
// Cursor

// Determine what cursor to use
void CMgrInput::DetermineCursor() 
{
	WORD cursor = IDC_POINT;

	if (state == state_AddingLine)
	{
		if (prevStarNum == -1)
		{
			if (Select(select_Star))
				cursor = IDC_EDITX;
			else
				cursor = IDC_EDIT;
		}
		else
		{
			if (Select(select_Star))
				cursor = IDC_ALINEX;
			else
				cursor = IDC_ALINE;
		}
	}
	else if (state == state_DeletingLine)
	{
		if (Select(select_Line))
			cursor = IDC_DLINEX;
		else
			cursor = IDC_DLINE;
	}

	SetCur (cursor);
}

// Set cursor to the resource id cur
void CMgrInput::SetCur( WORD cur )
{
	SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(cur)));
}


/////////////////////////////////////////////////////////////////////////////
// Selecting

// No star has been selected
void CMgrInput::ClearSelection()
{
	prevStarNum = -1;
}

// Try selecting a star or line
BOOL CMgrInput::Select( select_e selection )
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
	graphicsMgr.Perspective();

	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();

	if (selection == select_Star)
	{
		graphicsMgr.DrawTerrain();
		graphicsMgr.DrawStars();
	}
	else if (selection == select_Line)
		graphicsMgr.DrawConstellation(starfield.GetNumCurConstellation());

	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix

	glMatrixMode(GL_MODELVIEW);
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was

	// Check if there is a hit
	if( hits <= 0 )
		return false;
	else
	{
		// Test if terrain was hit
		if( selection == select_Star )
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

// Try selecting a star. Returns -1 if no star was selected
int CMgrInput::SelectStar()
{
	if (Select(select_Star))	// If a hit occured in starfield
	{
		int numStar = selectBuffer[3] - 1;	// Subtract 1 because terrain is 0
		CStar* selectedStar = starfield.GetStar(numStar);

		// If there was more than one hit
		for (int i=1; i<hits; i++)
		{
			// Get the brightest
			if (starfield.GetStar(selectBuffer[i*4+3]-1)->GetMag() <
						selectedStar->GetMag())
			{
				numStar = selectBuffer[i*4+3] - 1;	// Subtract 1 because terrain is 0
				selectedStar = starfield.GetStar(numStar);
			}
		}
		return numStar;
	}
	else return -1;
}

// Try selecting a line. Returns -1 if no line was selected
int CMgrInput::SelectConstLine()
{
	if (Select(select_Line))	// If a hit occured
		return selectBuffer[3];
	else return -1;
}

