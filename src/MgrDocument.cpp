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
	modified = FALSE;
}

CMgrDocument::~CMgrDocument()
{
}


/////////////////////////////////////////////////////////////////////////////
// Gets

char*	CMgrDocument::GetTitle()	{	return title;		}
BOOL	CMgrDocument::IsModified()	{	return modified;	}


/////////////////////////////////////////////////////////////////////////////
// Sets
void CMgrDocument::SetModified()	{	modified = TRUE; UpdateTitle();	}


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
	modified = FALSE;

	// New data
	terrain.New();
	starfield.New( true );

	/// Add test constellation on startup
	starfield.AddConst( CString("TEST") );
	starfield.SelectConst( CString("TEST") );

	// Reset UI and refresh screen
	GetFrame()->GetStarfBar()->SetTimeToNow();
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.UpdateMats();
	Redraw();
}

// User selected to make a new random starfield
void CMgrDocument::NewRandom()
{
	// Check if starfield needs saved
	if( CheckModified() == IDCANCEL )
		return;

	strncpy( title, "Untitled.str", MAX_DOC_NAME );
	modified = FALSE;

	// New data
	terrain.New();
	starfield.New( FALSE );

	// Reset UI and refresh screen
	GetFrame()->GetStarfBar()->SetTimeToNow();
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.UpdateMats();
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

	// Set the current directory back
	SetCurrentDirectory( cwd );

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

	// Document isn't modified
	modified = FALSE;

	// Close archive and file
	ar.Close();
	file.Close();


	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	GetFrame()->GetStarfBar()->ChangeSpeed( starfield.GetSpeed() );
	graphicsMgr.UpdateMats();
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

	// Document isn't modified
	modified = FALSE;

	// Close archive and file
	ar.Close();
	file.Close();

	// Set the current directory back
//	SetCurrentDirectory( cwd );

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.UpdateMats();
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

	// Set the current directory back
	SetCurrentDirectory( cwd );

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

	// Document isn't modified
	modified = FALSE;

	// Close archive and file
	ar.Close();
	file.Close();

	// Reset UI and refresh screen
	UpdateTitle();
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.UpdateMats();
	Redraw();
}

// Checks to see if the starfield needs to be saved
//  returns answer to dialog or IDNO if starfield isn't modified
int CMgrDocument::CheckModified()
{
	return IDNO;/// Don't ask for save on modified until production
	// Check if document is modified
	if( modified )
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

	if( modified )
		strncat( windowTitle, " *]", 3 );
	else
		strncat( windowTitle, "]", 1 );

	GetFrame()->SetWindowText( windowTitle );
}

