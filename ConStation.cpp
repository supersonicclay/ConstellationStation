/**************************************
*          nehe.gamedev.net           *
**************************************/

//#include <windows.h>
//#include <gl/gl.h>									// Header File For The OpenGL32 Library
//#include <gl/glu.h>									// Header File For The GLu32 Library

//#include "Window.h"
#include "ConStation.h"
//#include "Starfield.h"
//#include "UI.h"

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*		window;

// User Interface
KeyboardManager keyboardManager;
MouseManager	mouseManager;
Controls		controls;
HeadingBug		headingBug;

// Starfield
Starfield		starfield;


BOOL Initialize (GL_Window* w)					// Any GL Init Code & User Initialiazation Goes Here
{
	window	= w;

	// GL initialization
	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	mouseManager.SetOrigClipCursor();
	controls.Init();					// Labels can't build fonts until initialized

	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
}

void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	keyboardManager.ProcessKeys();
	mouseManager.MouseUpdate();
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix

	starfield.Draw();

	// UI
//	if (mouseManager.GetMouseRotating())
//	controls.Draw();
	headingBug.Draw();

//	glFlush ();													// Flush The GL Rendering Pipeline
}
