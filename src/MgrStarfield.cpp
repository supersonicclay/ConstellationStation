//===========================================================================
// MgrStarfield.cpp
//
// CMgrStarfield
//   manager class for starfield functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrStarfield.h"

#include "DlgLocation.h"
#include "DlgTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrStarfield::CMgrStarfield()
{
	strncpy( title, "Untitled.str", MAX_DOCNAMELENGTH );
}

CMgrStarfield::~CMgrStarfield()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

CBarStarf* CMgrStarfield::GetStarfBar()
{
	return GetFrame()->GetStarfBar();
}


// User selected to make a new actual starfield
void CMgrStarfield::NewActual()
{
	// See if starfield needs saved
	if( CheckModified() == IDCANCEL )
		return;

	strncpy( title, "Untitled.str", MAX_DOCNAMELENGTH );

	terrain.New();
	starfield.New( true );

	/// Add test constellation on startup
	starfield.AddConstellation( CString("TEST") );
	starfield.SetCurConstellation( CString("TEST") );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// User selected to make a new random starfield
void CMgrStarfield::NewRandom()
{
	// Check if starfield needs saved
	if( CheckModified() == IDCANCEL )
		return;

	strncpy( title, "Untitled.str", MAX_DOCNAMELENGTH );

	terrain.New();
	starfield.New( FALSE );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();

}

// User selected to open a starfield
void CMgrStarfield::Open()
{
	// Check if starfield needs saved
	if( CheckModified() == IDCANCEL )
		return;

	// Initialize OPENFILENAME for opening
	InitOFN( FALSE );

	// Get filename from user
	if( !GetOpenFileName( &ofn ) )
		return;

	// Open file for reading
	CFile file;
	if( !file.Open( filename, CFile::modeRead ) )
		CSError( "Unable to open file", "CMgrStarfield::Open" );

	// Create an archive for loading
	CArchive ar( &file, CArchive::load );
	starfield.Serialize( ar );
	terrain.Serialize( ar );

	// Close archive and file
	ar.Close();
	file.Close();

	// Set the current directory back
	SetCurrentDirectory( cwd );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// User selected to save the starfield
void CMgrStarfield::Save()
{
	// If user is working on an unsaved document
	if( !strcmp(title, "Untitled.str") )
	{
		SaveAs();
		return;
	}
	// Otherwise just save the file

	// Open file for writing
	CFile file;
	if( !file.Open( filename, CFile::modeCreate | CFile::modeWrite ) )
		CSError( "Unable to open file", "CMgrStarfield::Save" );

	// Create an archive for storing
	CArchive ar( &file, CArchive::store );
	starfield.Serialize( ar );
	terrain.Serialize( ar );

	// Close archive and file
	ar.Close();
	file.Close();

	// Set the current directory back
	SetCurrentDirectory( cwd );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// User selected to saveas the starfield
void CMgrStarfield::SaveAs()
{
	// Initialize OPENFILENAME for saving
	InitOFN( true );

	// Get filename from user
	if( !GetSaveFileName( &ofn ) )
		return;

	// Open file for writing
	CFile file;
	if( !file.Open( filename, CFile::modeCreate | CFile::modeWrite ) )
		CSError( "Unable to open file", "CMgrStarfield::SaveAs" );

	// Create an archive for storing
	CArchive ar( &file, CArchive::store );
	starfield.Serialize( ar );
	terrain.Serialize( ar );

	// Close archive and file
	ar.Close();
	file.Close();

	// Set the current directory
	SetCurrentDirectory( cwd );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// Initialize an OPENFILENAME struct for saving or opening
void CMgrStarfield::InitOFN( BOOL saving )
{
	// Get the current directory
	GetCurrentDirectory( MAX_PATH, cwd );
	// Get the starfield directory
	strncpy( starfieldDir, cwd, MAX_PATH );
	strncat( starfieldDir, "\\starfields", MAX_PATH );

	// Zero the structure
	ZeroMemory( &ofn, sizeof(ofn) );

	// Fill the structure
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetFrame()->GetSafeHwnd();
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = title;
	ofn.nMaxFileTitle = MAX_DOCNAMELENGTH;
	ofn.lpstrInitialDir = starfieldDir;
	ofn.lpstrFilter = "Starfields (*.str)\0*.str\0";
	ofn.lpstrDefExt = "str";

	if( saving )
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	else
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

// Checks to see if the starfield needs to be saved
//  returns answer to dialog or IDNO if starfield isn't modified
int CMgrStarfield::CheckModified()
{
	return IDNO;/// MAKES MY LIFE EASIER FOR NOW
	// Check if starfield is modified
	if( starfield.IsModified() )
	{
		int a = CSYesNoCancel( "The starfield is modified.\nDo you want to save it?" );
		if( a == IDYES )
			Save();
		return a;
	}
	// Not modified
	return IDNO;
}

// Sets the title of the window to "Constellation Station - DocumentName"
void CMgrStarfield::UpdateTitle()
{
	char windowTitle[100];
	strncpy( windowTitle, "Constellation Station - [", 100 );
	strncat( windowTitle, title, MAX_DOCNAMELENGTH );

	if( starfield.IsModified() )
		strncat( windowTitle, " *]", 3 );
	else
		strncat( windowTitle, "]", 1 );

	GetFrame()->SetWindowText( windowTitle );
}

// Turns starfield spinning on/off
void CMgrStarfield::Rotate()
{
	starfield.SwitchSpinning();
}

/// Opens the location dialog
void CMgrStarfield::Location()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgLocation dialog;

	dialog.DoModal();	
}

/// Opens the time dialog
void CMgrStarfield::Time()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgTime dialog;
	dialog.DoModal();
}

