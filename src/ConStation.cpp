//===========================================================================
// ConStation.cpp
//
// CConStationApp
//   main source file for Constellation Station
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"

#include "ConStationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConStationApp

BEGIN_MESSAGE_MAP( CConStationApp, CWinApp )
	//{{AFX_MSG_MAP(CConStationApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_STARF_NEWACTUAL, OnStarfNewActual)
	ON_COMMAND(ID_STARF_NEWRANDOM, OnStarfNewRandom)
	ON_COMMAND(ID_STARF_OPEN, OnStarfOpen)
	ON_COMMAND(ID_STARF_SAVE, OnStarfSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConStationApp construction

CConStationApp::CConStationApp()
{
	srand( (unsigned)::time(NULL) );
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CConStationApp object

CConStationApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CConStationApp initialization

BOOL CConStationApp::InitInstance()
{
//	AfxEnableControlContainer();

	// Standard initialization
	Enable3dControls();

	// Change the registry key under which our settings are stored.
	SetRegistryKey( _T("Constellation Station") );

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Init Frame
	CConStationFrame* pFrame = new CConStationFrame;
	m_pMainWnd = pFrame;
	
	pFrame->LoadFrame( IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
		NULL, NULL );

	m_pMainWnd->ShowWindow( SW_MAXIMIZE );
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CConStationFrame* CConStationApp::GetFrame() const
{
	return (CConStationFrame *)m_pMainWnd;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgAbout dialog used for App About

class CDlgAbout : public CDialog
{
public:
	CDlgAbout();

// Dialog Data
	//{{AFX_DATA(CDlgAbout)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CDlgAbout)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CDlgAbout::CDlgAbout() : CDialog( CDlgAbout::IDD )
{
	//{{AFX_DATA_INIT(CDlgAbout)
	//}}AFX_DATA_INIT
}

void CDlgAbout::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP( CDlgAbout, CDialog )
	//{{AFX_MSG_MAP(CDlgAbout)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Methods

// Open the about dialog
void CConStationApp::OnAppAbout()
{
	CDlgAbout aboutDlg;
	aboutDlg.DoModal();
}

// Initialize an OPENFILENAME struct for saving or opening
void CConStationApp::InitOFN( BOOL saving )
{
	strncpy( starfieldDir, cwd, MAX_PATH );
	strncat( starfieldDir, "\\starfields", MAX_PATH );

	// Zero the structure
	ZeroMemory( &ofn, sizeof(ofn) );

	// Fill the structure
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetFrame()->GetSafeHwnd();
	ofn.lpstrFile = filename;
	ofn.lpstrInitialDir = starfieldDir;
	ofn.lpstrFilter = "Starfields (*.str)\0*.str\0";
	ofn.lpstrDefExt = "str";
	ofn.nMaxFile = MAX_PATH;

	if( saving )
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	else
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

// Check for modification and create a new actual starfield
void CConStationApp::OnStarfNewActual() 
{
	// Check if starfield is modified
	if( starfield.IsModified() )
	{
		int a = CSYesNoCancel( "The starfield is modified.\nDo you want to save it?" );
		if( a == ID_CANCEL )
			return
		if( a == ID_OK )
			OnStarfSave();
	}

	terrain.New();
	starfield.New( TRUE );

	// Reset UI and refresh screen
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// Check for modification and create a new random starfield
void CConStationApp::OnStarfNewRandom() 
{
	// Check if starfield is modified
	if( starfield.IsModified() )
	{
		int a = CSYesNoCancel( "The starfield is modified.\nDo you want to save it?" );
		if( a == ID_CANCEL )
			return
		if( a == ID_OK )
			OnStarfSave();
	}

	terrain.New();
	starfield.New( FALSE );

	// Reset UI and refresh screen
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// Check for modification and open a starfield
void CConStationApp::OnStarfOpen() 
{
	/// Check if starfield is modified (do I want it to open after this)
	if( starfield.IsModified() )
	{
		int a = CSYesNoCancel( "The starfield is modified.\nDo you want to save it?" );
		if( a == ID_CANCEL )
			return
		if( a == ID_OK )
			OnStarfSave();
	}

	// Get the current directory
	GetCurrentDirectory( MAX_PATH, cwd );

	// Initialize OPENFILENAME for opening
	InitOFN( FALSE );

	// Get filename from user
	if( !GetOpenFileName( &ofn ) )
		return;

	// Open file for reading
	CFile file;
	if( !file.Open( filename, CFile::modeRead ) )
		CSError( "Unable to open file", "CConStationApp::OnStarfOpen" );

	// Create an archive for loading
	CArchive ar( &file, CArchive::load );
	starfield.Serialize( ar );
	terrain.Serialize( ar );

	// Close archive and file
	ar.Close();
	file.Close();

	// Set the current directory
	SetCurrentDirectory( cwd );

	// Reset UI and refresh screen
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}

// Save the starfield
void CConStationApp::OnStarfSave() 
{
	// Get the current directory
	GetCurrentDirectory( MAX_PATH, cwd );

	// Initialize OPENFILENAME for saving
	InitOFN( TRUE );

	// Get filename from user
	if( !GetSaveFileName( &ofn ) )
		return;

	// Open file for writing
	CFile file;
	if( !file.Open( filename, CFile::modeCreate | CFile::modeWrite ) )
		CSError( "Unable to open file", "CConStationApp::OnStarfSave" );

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
	SetState( state_Viewing );
	GetFrame()->GetConstBar()->UpdateList();
	graphicsMgr.Projection();
	Redraw();
}


/*
CFile myFile("myfile.dat", CFile::modeCreate | CFile::modeReadWrite);
CAge  age(21), *pAge;

// Create a storing archive.
CArchive arStore(&myFile, CArchive::store);

// Write the object to the archive
arStore.WriteObject( &age );

// Close the storing archive
arStore.Close();

// Create a loading archive.
myFile.SeekToBegin();
CArchive arLoad(&myFile, CArchive::load);

// Verify the object is in the archive.
pAge = (CAge*) arLoad.ReadObject( RUNTIME_CLASS(CAge) );
ASSERT( age == *pAge );
*/