//===========================================================================
// ConStation.cpp
//
// CConStationApp
//   main source file for Constellation Station application.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"

#include "ConStationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP( CConStationApp, CWinApp )
	//{{AFX_MSG_MAP(CConStationApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Construction

CConStationApp::CConStationApp()
{
	srand( (unsigned)::time(NULL) );
}


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

/////////////////////////////////////////////////////////////////////////////
// The one and only CConStationApp object

CConStationApp theApp;


CConStationFrame* CConStationApp::GetFrame()
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
// CConStationApp message handlers

// Open the about dialog
void CConStationApp::OnAppAbout()
{
	CDlgAbout dialog;
	dialog.DoModal();
}

