#ifndef CONSTATION_H
#define CONSTATION_H

#include <windows.h>
#include <stdio.h>					// Header File For Standard Input/Output
#include <stdarg.h>					// Header File For Variable Argument Routines
#include <gl/gl.h>					// Header File For The OpenGL32 Library
#include <gl/glu.h>					// Header File For The GLu32 Library
#include <gl/glaux.h>				// Header File For The GLaux Library

#include "Globals.h"
#include "Window.h"
#include "Starfield.h"
#include "UI.h"

/************
*  Globals  *
************/
extern GL_Window*		window;

// User Interface
extern KeyboardManager	keyboardManager;
extern MouseManager		mouseManager;
extern Controls			controls;
extern HeadingBug		headingBug;

// Starfield
extern Starfield		starfield;


/**************
*  Functions  *
**************/

BOOL Initialize (GL_Window* window);				// Performs All Your Initialization

void Deinitialize ();								// Performs All Your DeInitialization

void Update (DWORD milliseconds);					// Perform Motion Updates

void Draw ();										// Perform All Your Scene Drawing

//void ProcessKeys();

//void Selection(float r, float g, float b);

#endif