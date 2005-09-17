//===========================================================================
// MgrText.cpp
//
// CMgrText
//   manager class for text functions.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "MgrText.h"

#include "DlgOptionsText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrText::CMgrText()
{
}

CMgrText::~CMgrText()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Initialize display lists for the font(s)
void CMgrText::InitFonts()
{
	constBase = glGenLists( 96 );
	starBase = glGenLists( 96 );
	dirBase = glGenLists( 96 );
}

// Build display lists for the fonts
void CMgrText::BuildFonts()
{
	HDC hDC = graphicsMgr.hDC;

	SelectObject( hDC, CreateFontIndirect( &optionsMgr.GetTextConstFont() ));
	wglUseFontBitmaps( hDC, 32, 96, constBase );
	SelectObject( hDC, CreateFontIndirect( &optionsMgr.GetTextStarFont() ));
	wglUseFontBitmaps( hDC, 32, 96, starBase );
	SelectObject( hDC, CreateFontIndirect( &optionsMgr.GetTextDirFont() ));
	wglUseFontBitmaps( hDC, 32, 96, dirBase );
}

void CMgrText::KillFonts()
{
	glDeleteLists( constBase, 96 );
	glDeleteLists( starBase, 96 );
	glDeleteLists( dirBase, 96 );
}

// Open text options dialog
void CMgrText::Options()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgOptionsText dialog;
	if( dialog.DoModal() == IDOK )
	{
		// All fonts are updated in realtime (in dialog)
	}
	else
	{
		// Reset fonts (they are updated in realtime)
		optionsMgr.SetTextConstFont( dialog.origConstFont );
		optionsMgr.SetTextStarFont( dialog.origStarFont );
		optionsMgr.SetTextDirFont( dialog.origDirFont );
		BuildFonts();
	}
}

void CMgrText::TypeConst( CDataConst* constellation )
{
	if( constellation == starfield.GetCurConst() )
		graphicsMgr.SelectColor4( optionsMgr.GetTextConstSelColor(), graphicsMgr.constAlpha );
	else
		graphicsMgr.SelectColor4( optionsMgr.GetTextConstColor(), graphicsMgr.constAlpha );

	vector3 c = constellation->GetCenter();
	glRasterPos3f( c.x, c.y, c.z );

	CString name = constellation->GetName();

	glListBase( constBase-32 );
	glCallLists( name.GetLength(), GL_UNSIGNED_BYTE, (const char*)name );
}

void CMgrText::TypeStar( CDataStar* star )
{
	if( graphicsMgr.starAlpha > 0.99f )
		glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	graphicsMgr.SelectColor4( optionsMgr.GetTextStarColor(), graphicsMgr.starAlpha );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	vector3 c = graphicsMgr.perspMat*graphicsMgr.starfMat*star->GetCenter();
	glRasterPos2f( c.x, c.y-0.01f );/// needs to be dynamic

	CString name = star->GetName();

	glListBase( starBase-32 );
	glCallLists( 3+name.GetLength(), GL_UNSIGNED_BYTE, CString(" < ") + name );

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glEnable( GL_BLEND );
	if( optionsMgr.AreStarsTextured() )
		glEnable( GL_TEXTURE_2D );
}

void CMgrText::TypeDirections( float offset )
{
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );
	graphicsMgr.SelectColor( optionsMgr.GetTextDirColor() );
	glListBase( dirBase-32 );

	// N
	glRasterPos3f( 0.0f, offset-0.1f, -1.0f );
	glCallLists( 1, GL_UNSIGNED_BYTE, "N" );

	// E
	glRasterPos3f( 1.0f, offset-0.1f, 0.0f );
	glCallLists( 1, GL_UNSIGNED_BYTE, "E" );

	// S
	glRasterPos3f( 0.0f, offset-0.1f, 1.0f );
	glCallLists( 1, GL_UNSIGNED_BYTE, "S" );

	// W
	glRasterPos3f( -1.0f, offset-0.1f, 0.0f );
	glCallLists( 1, GL_UNSIGNED_BYTE, "W" );

	glEnable( GL_BLEND );
	glEnable( GL_TEXTURE_2D );
}