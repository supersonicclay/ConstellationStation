/************************
*						*
*	User Interface		*
*						*
*		UI.cpp			*
*						*
************************/

#include "ConStation.h"
//#include "UI.h"
//#include "Window.h"

/********************
*					*
*	KeyboardManager	*
*					*
********************/
KeyboardManager::KeyboardManager()
{
	ZeroMemory (&keyDown, sizeof (keyDown));									// Zero keys Structure
}

KeyboardManager::~KeyboardManager()
{
}

// Processing for keyboard events
void KeyboardManager::ProcessKeys()
{

	if (keyDown [VK_ESCAPE] == TRUE)
	{
		TerminateApplication (window);
	}

	if (keyDown [VK_F1] == TRUE)
	{
		keyDown [VK_F1] = FALSE;
		ToggleFullscreen (window);
	}

	if (keyDown [VK_UP])
	{
		starfield.RotateUp();
	}

	if (keyDown [VK_DOWN])
	{
		starfield.RotateDown();
	}

	if (keyDown [VK_LEFT])
	{
		starfield.RotateLeft();
	}

	if (keyDown [VK_RIGHT])
	{
		starfield.RotateRight();
	}

	if (keyDown ['E'])
	{
		starfield.ZoomIn();
	}

	if (keyDown ['Q'])
	{
		starfield.ZoomOut();
	}

	if (keyDown [' '])
	{
		starfield.ResetView();
	}
}

void KeyboardManager::SetKeyDown(WPARAM i, BOOL state)
{
	keyDown[i] = state;
}


/********************
*					*
*	MouseManager	*
*					*
********************/
MouseManager::MouseManager()
{
}

MouseManager::~MouseManager()
{
}

void MouseManager::MouseMove(LPARAM pos)
{
	SetPos (mousePos, pos);
	MouseUpdate();
}

void MouseManager::MouseUpdate()
{
	/***** Highlights star that mouse is over********SLOW AS HELL!!!************
	Star* selectedStar = SelectStar();
	if (selectedStar!=NULL)										// Mouse is over a star
	{
		selectedStar->SetColor(RED);							// Set this star's color to red
		if (starfield.GetStarMouseOver()==NULL)					// If starMouseOver is not set
		{
			starfield.SetStarMouseOver(selectedStar);			// Set it to selectedStar
		}
		else if (starfield.GetStarMouseOver() != selectedStar)	// Mouse is over a different star as before
		{
				starfield.GetStarMouseOver()->SetColor(WHITE);	// Set old starMouseOver's color to WHITE
		}
																// Else mouse is still over same star
	}
	else if (starfield.GetStarMouseOver() != NULL)				// Mouse isn't over a star but it was before
	{
		starfield.GetStarMouseOver()->SetColor(WHITE);
		starfield.SetStarMouseOver(NULL);
	}
	***************************************************************************/

	if (mouseRotating)
	{
		deltaMousePosR.x = mousePos.x-mousePosRDown.x;
		deltaMousePosR.y = mousePos.y-mousePosRDown.y;

////	SetCursorPos(mousePosLDown.x, mousePosLDown.y);

		//// Figure out how to slow zoom without distorting rotation
//		newRotX = origRotX + (float)(deltaMousePosR.y)*0.07f;//(-starfield.GetZoom() + 1)*0.07f;
//		newRotY = origRotY + (float)(deltaMousePosR.x)*0.07f;//(-starfield.GetZoom() + 1)*0.07f;
		newRotX = origRotX + (float)(deltaMousePosR.y)*(-starfield.GetZoom() + 1)*0.07f;
		newRotY = origRotY + (float)(deltaMousePosR.x)*(-starfield.GetZoom() + 1)*0.07f;

		if ( newRotX > -90 && newRotX < 90)
			starfield.SetRotX(newRotX);
		starfield.SetRotY(newRotY);
	}
}

/*********
* Clicks *
*********/
void MouseManager::MouseLDown(LPARAM pos)
{
	mouseLDown = TRUE;
	SetPos (mousePos, pos);
	SetPos (mousePosLDown, pos);
	MouseUpdate();

	Star* selectedStar = SelectStar();
	if (selectedStar!=NULL)
		selectedStar->SetColor(RED);
	/*
	Button* selectedButton = SelectButton();
	if (selectedButton!=NULL)
		selectedButton->SetFGColor(WHITE);
	*/
}

void MouseManager::MouseLUp(LPARAM pos)
{
	mouseLDown = FALSE;
	MouseUpdate();
}

void MouseManager::MouseRDown(LPARAM pos)
{
	mouseRDown = TRUE;
	SetPos (mousePos, pos);
	SetPos (mousePosRDown, pos);
	MouseUpdate();

	// Mouse Controlling Rotation
	// if (SelectHeadingBug())
	mouseRotating = TRUE;
	origRotX = starfield.GetRotX();
	origRotY = starfield.GetRotY();

//	ShowCursor(FALSE);
//	GetClientRect (window->hWnd, &starfieldClipCursor);
	GetWindowRect (window->hWnd, &starfieldClipCursor);
	starfieldClipCursor.left+=8;						//// Keep in window
	starfieldClipCursor.top+=25;						//// Keep in window
	ClipCursor(&starfieldClipCursor);
}

void MouseManager::MouseRUp(LPARAM pos)
{
	mouseRDown = FALSE;
	mouseRotating = FALSE;
	MouseUpdate();

//	ShowCursor(TRUE);

	if (!mouseLDown)
		ClipCursor(&origClipCursor);
}

// Get and Set functions
BOOL MouseManager::GetMouseRotating()
{
	return mouseRotating;
}

BOOL MouseManager::GetMouseLDown()
{
	return mouseLDown;
}

BOOL MouseManager::GetMouseRDown()
{
	return mouseRDown;
}

// Set a mouse position from an LPARAM
void MouseManager::SetPos(csPOINT &point, LPARAM pos)
{
	point.x = LOWORD(pos);
	point.y = HIWORD(pos);
}

void MouseManager::SetOrigClipCursor()
{
	GetClipCursor(&origClipCursor);
}


/************
* Selecting *
************/
BOOL MouseManager::Select(GUIElement *g)
{
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
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
	gluPickMatrix((GLdouble) mousePos.x, (GLdouble) (viewport[3]-mousePos.y), 4.0f, 4.0f, viewport);

	// Apply The Perspective Matrix
	gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.05f, 100.0f);

	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();

	g->Draw();													// Render The Targets To The Selection Buffer

	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix

	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was
	if (hits != 0)
	{
		return TRUE;
	}
	return FALSE;												// Nothing selected
}

Star* MouseManager::SelectStar()
{
	if (Select(&starfield))	// If a hit occured in starfield
	{
		Star* selectedStar = starfield.GetStar(selectBuffer[3]);
		for (int i=1; i<hits; i++)
		{
			// If this star is brighter than the prev make it the selected star
			if (starfield.GetStar(selectBuffer[i*4+3])->GetBrightness() >
						selectedStar->GetBrightness())
				selectedStar = starfield.GetStar(selectBuffer[i*4+3]);
		}
		return selectedStar;
	}
	else return NULL;
}

/****************
*				*
*	HeadingBug	*
*				*
****************/

HeadingBug::HeadingBug()
{
}

HeadingBug::~HeadingBug()
{
}

void HeadingBug::Draw() const
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-16, 16,-2, 22, -2,2);			// Set up Orth view

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Rotate and Zoom
	glRotatef (starfield.GetRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef (starfield.GetRotY(), 0.0f, 1.0f, 0.0f);

	// Cross
	glLineWidth(2);
	glColor3f (0.0f,0.6f,0.0f);				// Green
	glBegin(GL_LINES);
		glVertex3f ( 1.0f, 0.0f, 0.0f);
		glVertex3f (-1.0f, 0.0f, 0.0f);
		glVertex3f ( 0.0f, 1.0f, 0.0f);
		glVertex3f ( 0.0f,-1.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f, 1.0f);
		glVertex3f ( 0.0f, 0.0f, 0.0f);
		// North indicator
		glColor3f (1.0f,0.0f,0.0f);			// Red
		glVertex3f ( 0.0f, 0.0f, 0.0f);
		glVertex3f ( 0.0f, 0.0f,-1.0f);
	glEnd();

	glPopMatrix();							// Pop MODELVIEW matrix
	glMatrixMode(GL_PROJECTION);			// Switch to PROJECTION matrix
	glPopMatrix();							// Pop PROJECTION matrix
	glMatrixMode(GL_MODELVIEW);				// Switch back to MODELVIEW matrix
}


/************
*			*
*	Panel	*
*			*
************/
Panel::Panel()
{
	bgColor = BLACK;
	fgColor = WHITE;
}

Panel::Panel(float x_, float y_, float width_, float height_,
			 COLOR bgColor_, COLOR fgColor_)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	bgColor = bgColor_;
	fgColor = fgColor_;
}

Panel::~Panel()
{
}

float Panel::GetX()
{
	return x;
}

float Panel::GetY()
{
	return y;
}

float Panel::GetWidth()
{
	return width;
}

float Panel::GetHeight()
{
	return height;
}

void Panel::Draw() const
{
	RECT windowRect;
	GetClientRect (window->hWnd, &windowRect);

	// Set up 2d drawing
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// (0,0) is top left
	glOrtho(0,windowRect.right-windowRect.left, windowRect.bottom-windowRect.top, 0, -11,11);								// Set up Orth view
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Background
	glColor3f(bgColor.r, bgColor.g, bgColor.b);
	glBegin(GL_QUADS);
		glVertex2f (x,			y);
		glVertex2f (x,			y+height);
		glVertex2f (x+width,	y+height);
		glVertex2f (x+width,	y);
	glEnd();
	// Foreground Border
	glLineWidth(3);
	glColor3f(fgColor.r, fgColor.g, fgColor.b);
	glBegin(GL_LINE_LOOP);
		glVertex2f (x,			y);
		glVertex2f (x,			y+height);
		glVertex2f (x+width,	y+height);
		glVertex2f (x+width,	y);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


/************
*			*
*	Button	*
*			*
************/
Button::Button()
		// Call base-class constructor
		: Panel()
{
	// That's all we do for now
	// Until we can click buttons
}

Button::Button(float x_, float y_,
			   float width_, float height_,
			   COLOR bgColor_, COLOR fgColor_) 
		// Call base-class constructor
		: Panel(x_, y_, width_, height_, bgColor_, fgColor_)	
{
}

Button::~Button()
{
}


/************
*			*
*	Label	*
*			*
************/
Label::Label(Panel *parent_, char *text_, float size_)
{
	parent = parent_;
	size  = (int) size_;
	SetText(text_);
	color = BLUE;
	BuildFont();
}

Label::~Label()
{
	KillFont();
}

void Label::SetDimensions()
{
	width  = (float) strlen(text) * size*3/5;	// 3 pixels / 5 font pt size
	height = (float) size*3/5;

	float centerX = parent->GetX() + parent->GetWidth()/2;
	float centerY = parent->GetY() + parent->GetHeight()/2;

	x = centerX - width/2;
	y = centerY + height/2 - size/5;	// -size/5 for j, q, p, etc
}

void Label::SetText(char *text_)
{
	text = text_;
	SetDimensions();
}

void Label::SetSize(float size_)
{
	size = (int) size_;
	BuildFont();
	SetDimensions();
}

void Label::SetColor(COLOR color_)
{
	color = color_;
}

void Label::BuildFont()									// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-size,							// Height Of Font (size is in pixels)
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(window->hDC, font);	// Selects The Font We Want
	wglUseFontBitmaps(window->hDC, 32, 96, base);		// Builds 96 Characters Starting At Character 32
	SelectObject(window->hDC, oldfont);					// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

void Label::KillFont()									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

void Label::Draw() const
{
	RECT windowRect;
	GetClientRect (window->hWnd, &windowRect);

	// Set up 2d drawing
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// (0,0) is top left
	glOrtho(0,windowRect.right-windowRect.left, windowRect.bottom-windowRect.top, 0, -11,11);								// Set up Orth view
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2f (x, y);

	// Draw Text
	glColor3f(color.r, color.g, color.b);
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


/****************
*				*
*	Controls	*
*				*
****************/
Controls::Controls()
		// Call base-class constructor
		: Panel()
{
}

void Controls::Init()
{
	x = 5.0f;
	y = 5.0f;
	width = 200.0f;
	height = 300.0f;
	panTitle = new Panel(x, y, width, height/8);
	lblTitle = new Label(panTitle, "Constellation Station", 15);
	lblTitle->SetColor(BLUE);
	butLine = new Button(width/6*1,	   height/3, width/4, height/9, BLACK, BLUE);
	butFill = new Button(width/6*3.5f, height/3, width/4, height/9, BLACK, BLUE);

}

Controls::~Controls()
{
	delete panTitle;
}

void Controls::Draw() const
{
	Panel::Draw();			// Call superclass Draw
	panTitle->Draw();
	lblTitle->Draw();
	butLine->Draw();
	butFill->Draw();
}
