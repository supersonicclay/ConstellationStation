//===========================================================================
// MgrDocument.cpp
//
// CMgrDocument
//   manager class for document functions
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "MgrDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrDocument::CMgrDocument()
{
	strncpy( title, "Untitled.str", MAX_DOC_NAME );
}

CMgrDocument::~CMgrDocument()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Initialize an OPENFILENAME struct for saving or opening
void CMgrDocument::InitOFN( BOOL saving )
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
	ofn.nMaxFileTitle = MAX_DOC_NAME;
	ofn.lpstrInitialDir = starfieldDir;
	ofn.lpstrFilter = "Starfields (*.str)\0*.str\0";
	ofn.lpstrDefExt = "str";

	if( saving )
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	else
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

// User selected to make a new actual starfield
void CMgrDocument::NewActual()
{
	// See if starfield needs saved
	if( CheckModified() == IDCANCEL )
		return;

	strncpy( title, "Untitled.str", MAX_DOC_NAME );

	terrain.New();
	starfield.New( true );

	/// Add test constellation on startup
	starfield.AddConst( CString("TEST") );
	starfield.SelectConst( CString("TEST") );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// User selected to make a new random starfield
void CMgrDocument::NewRandom()
{
	// Check if starfield needs saved
	if( CheckModified() == IDCANCEL )
		return;

	strncpy( title, "Untitled.str", MAX_DOC_NAME );

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
void CMgrDocument::Open()
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
	{
		CSDebug( "Unable to open file", "CMgrDocument::Open" );
		return;
	}

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
void CMgrDocument::Save()
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
	{
		CSDebug( "Unable to open file", "CMgrDocument::Save" );
		return;
	}

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
void CMgrDocument::SaveAs()
{
	// Initialize OPENFILENAME for saving
	InitOFN( true );

	// Get filename from user
	if( !GetSaveFileName( &ofn ) )
		return;

	// Open file for writing
	CFile file;
	if( !file.Open( filename, CFile::modeCreate | CFile::modeWrite ) )
	{
		CSDebug( "Unable to open file", "CMgrDocument::SaveAs" );
		return;
	}

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

// Checks to see if the starfield needs to be saved
//  returns answer to dialog or IDNO if starfield isn't modified
int CMgrDocument::CheckModified()
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

// Sets the title of the window to "Constellation Station - [DocumentName.str]"
void CMgrDocument::UpdateTitle()
{
	char windowTitle[100];
	strncpy( windowTitle, "Constellation Station - [", 100 );
	strncat( windowTitle, title, MAX_DOC_NAME );

	if( starfield.IsModified() )
		strncat( windowTitle, " *]", 3 );
	else
		strncat( windowTitle, "]", 1 );

	GetFrame()->SetWindowText( windowTitle );
}

