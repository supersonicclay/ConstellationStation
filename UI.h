#ifndef UI_H
#define UI_H

/****************************************************
*													*
*						GUI							*
*													*
****************************************************/

/****************
*	HeadingBug	*
****************/
class HeadingBug : public GUIElement
{
private:

public:
	HeadingBug ();
	~HeadingBug();

	void Draw() const;
};

/************
*	Panel	*
************/
class Panel : public GUIElement
{
protected:
	float x;
	float y;
	float width;
	float height;
	COLOR bgColor;
	COLOR fgColor;
public:
	Panel ();
	Panel (float x_, float y_, float width_, float height_,
		COLOR bgColor_=BLACK, COLOR fgColor_=WHITE);	// white on black
	~Panel();

	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();

	void Draw() const;
};

/************
*	Button	*
************/
class Button : public Panel
{
protected:
public:
	Button ();
	Button (float x_, float y_, float width_, float height_,
		COLOR bgColor_=BLACK, COLOR fgColor_=WHITE);	// white on black
	~Button();

//	void Draw() const;
};

/************
*	Label	*
************/
class Label : public GUIElement
{
protected:
	Panel *parent;
	char *text;
	// x, y will be bottom left of text
	float x;
	float y;
	float width;
	float height;
	int size;
	COLOR color;
	// Base Display List For The Font Set
	GLuint	base;
public:
	Label (Panel *parent_, char *text_="", float size_=12);
	~Label();

	void SetDimensions();
	void SetText(char *text_);
	void SetSize(float size_);
	void SetColor(COLOR color_);

	void BuildFont();
	void KillFont();

	void Draw() const;
};

/****************
*	Controls	*
****************/
class Controls : public Panel
{
private:
	Panel  *panTitle;
	Label  *lblTitle;
	Button *butLine;
	Button *butFill;
public:
	Controls ();
	~Controls();

	void Init();

	void Draw() const;
};


/****************************************************
*													*
*						INPUT						*
*													*
****************************************************/
/************************
*	KeyboardManager		*
************************/
// Controls keyboard input
class KeyboardManager
{
private:
	BOOL keyDown [256];				// keyboard key down

public:
	KeyboardManager ();
	~KeyboardManager();

	void ProcessKeys();

	void SetKeyDown(WPARAM i, BOOL state);

};


/********************
*	MouseManager	*
********************/
// Controls mouse input
class MouseManager
{
private:
	BOOL mouseLDown, mouseRDown;	// L and R mouse button down
	csPOINT mousePos;
	csPOINT lastMousePos;
	csPOINT deltaMousePosL;			// The distance dragged with L button
	csPOINT deltaMousePosR;			// The distance dragged with R button

	// Positions where buttons were pressed and released
	csPOINT mousePosLDown;
	csPOINT mousePosLUp;
	csPOINT mousePosRDown;
	csPOINT mousePosRUp;

	// Selecting
	GLuint selectBuffer[100];
	GLint hits;

	// Mouse controlling rotation
	BOOL mouseRotating;
	float origRotX, origRotY;
	float newRotX, newRotY;
	// Cursor clipping
	RECT origClipCursor;
	RECT starfieldClipCursor;

public:
	MouseManager ();
	~MouseManager();

	void MouseUpdate();
	void MouseMove  (LPARAM lParam);		// Called when mouse is moved
	void MouseLDown (LPARAM lParam);		// Called when L button is pressed
	void MouseLUp   (LPARAM lParam);		// Called when L button is released
	void MouseRDown (LPARAM lParam);		// Called when R button is pressed
	void MouseRUp   (LPARAM lParam);		// Called when R button is released

	// Set mouse position
	void SetPos (csPOINT &point, LPARAM pos);

	BOOL Select(GUIElement *g);
	Star* SelectStar();

	BOOL GetMouseLDown();
	BOOL GetMouseRDown();
	BOOL GetMouseRotating();

	void SetOrigClipCursor();
};
#endif