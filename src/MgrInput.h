//===========================================================================
// MgrInput.h
//
// CMgrInput
//   user interface class. Handles all user input including mouse, keyboard,
//   and commands.
//===========================================================================

#ifndef CS_MGRINPUT_H
#define CS_MGRINPUT_H 


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
	BOOL   mouseRotatingXY;
	BOOL   mouseRotatingZ;
	CPoint mousePoint;
	CPoint mouseLDownPoint;
	CPoint mouseRDownPoint;

	// Selecting
	GLuint selectBuffer[100];
	GLint  hits;

	// Constellation editor
	int firstStarNum;
	int secondStarNum;


// Operations
public:

	// Keyboard
	void ProcessKeys();
	void KeyDown( UINT nChar );
	void KeyUp( UINT nChar );

	// Mouse

	// Mouse left button
	void MouseLDown( CPoint point );
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
	void MouseMoveAddingLine();
	void MouseMoveDeletingLine();

	// Other mouse methods
	void MouseWheel( short zDelta );
	void DetermineCursor();
	void SetCur( WORD cur );

	// Selecting
	void ClearSelection();
	int SelectStar();
	int SelectConstLine();
	BOOL Select( select_e selection );

// Destruction
public:
	~CMgrInput();

};

#endif
