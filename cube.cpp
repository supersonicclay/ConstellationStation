#include <afxwin.h>		// MFC Windows include file
#include <GL/gl.h>		// OpenGL include file
#include <GL/glu.h>		// OpenGL Utilities include file
#include <cmath>		// C++ Math include file




void DrawGLCube()	// Draw cube
{
	double l = 1.0;	// half size of cube orgin (0,0,0)  
	
	double sf = 1.2*l;	// scale factor


		glBegin(GL_QUAD_STRIP);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3d(-l, l, l);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3d(-l, -l, l);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3d(l, l, l);

			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3d(l, -l, l);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3d(l, l, -l);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3d(l, -l, -l);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3d(-l, l, -l);

			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3d(-l, -l, -l);

			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3d(-l, l, l);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3d(-l, -l, l);

		glEnd();

		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3d(-l, l, l);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3d(l, l, l);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3d(l, l, -l);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3d(-l, l, -l);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3d(-l, -l, l);

			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3d(l, -l, l);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3d(l, -l, -l);

			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3d(-l, -l, -l);

		glEnd();
	
	// draw local axes
//	glScaled(sf, sf, sf);
//	glCallList( axes );

	return;
}