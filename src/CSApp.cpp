//===========================================================================
// CSApp.cpp
//
// CCSApp
//   main source file for Constellation Station application.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP( CCSApp, CWinApp )
	//{{AFX_MSG_MAP(CCSApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Construction

CCSApp::CCSApp()
{
	srand( (unsigned)::time(NULL) );
}


/////////////////////////////////////////////////////////////////////////////
// CCSApp initialization

BOOL CCSApp::InitInstance()
{
//	AfxEnableControlContainer();

	// Standard initialization
	Enable3dControls();

	// Change the registry key under which our settings are stored.
	SetRegistryKey( _T("Constellation Station") );

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Init Frame
	CCSFrame* pFrame = new CCSFrame;
	m_pMainWnd = pFrame;
	
	pFrame->LoadFrame( IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
		NULL, NULL );

	m_pMainWnd->ShowWindow( SW_MAXIMIZE );
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


CCSFrame* CCSApp::GetFrame()
{
	return (CCSFrame *)m_pMainWnd;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CCSApp object

CCSApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CCSApp message handlers

