//===========================================================================
// MgrInput.h
//
// CMgrInput
//   handles all user input and selection (not including frame commands).
//===========================================================================

#ifndef CS_MGRINPUT_H
#define CS_MGRINPUT_H 

#include "Matrix.h"

class CMgrInput
{
// Construction
public:
	CMgrInput();

// Attributes
public:

	// Keyboard
	BOOL keyDown[256];

	// Mouse
	BOOL    mouseRotatingXY;
	BOOL    mouseRotatingY;
	CPoint  mousePoint;
	CPoint  mouseLPoint;
	CPoint  mouseRPoint;
	CPoint  mouseScreenPoint;  // mouse point in screen coordinates
	CPoint  mouseScreenLPoint;
	CPoint  mouseScreenRPoint;
	vector3 mouseCoord;       // mouse coordinate on outside sphere
	vector3 mouseLDownCoord;  // mouse coordinate when L button clicked

	// Selecting
	BOOL selecting;
	UINT selectBuffer[100];
	UINT  hits;

	// Constellation editor
	int firstStarNum;
	int secondStarNum;


// Methods
public:

// Keyboard
	void ProcessKeys();
	void KeyDown( UINT nChar );
	void KeyUp( UINT nChar );


// Mouse

	// Mouse left button
	void MouseLDbl( CPoint point );
	void MouseLDown( CPoint point );
	void MouseLDownTest();///
	void MouseLDownViewing();
	void MouseLDownAddingLine();
	void MouseLDownDeletingLine();
	void MouseLUp( CPoint point );
	void MouseLUpViewing();
	void MouseLUpAddingLine();
	void MouseLUpDeletingLine();

	// Mouse right button
	void MouseRDown( CPoint point );
	void MouseRUp( CPoint point );
	void MouseRDownViewing();
	void MouseRDownAddingLine();
	void MouseRDownDeletingLine();
	void MouseRUpViewing();
	void MouseRUpAddingLine();
	void MouseRUpDeletingLine();

	// Mouse move
	void MouseMove( CPoint point );
	void MouseMoveViewing();
	void MouseMoveViewing2();///
	void MouseMoveViewing3();///
	void MouseMoveAddingLine();
	void MouseMoveDeletingLine();

	// Other mouse methods
	vector3 GetMouseSphereCoord();
	void MouseWheel( short zDelta );
	void DetermineCursor();
	void SetCur( WORD cur );


// Selecting
	void ClearSelection();
	int SelectStar();
	int SelectConst();
	int SelectConstLine();
	BOOL Select( select_e selection, float radius );


// Destruction
public:
	~CMgrInput();

};

#endif
