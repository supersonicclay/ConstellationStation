// ConStation.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ConStation.h"

#include "ConStationDoc.h"
#include "ConStationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConStationApp

BEGIN_MESSAGE_MAP(CConStationApp, CWinApp)
	//{{AFX_MSG_MAP(CConStationApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_STARF_NEWACTUAL, OnStarfNewActual)
	ON_COMMAND(ID_STARF_NEWRANDOM, OnStarfNewRandom)
	ON_COMMAND(ID_STARF_OPEN, OnStarfOpen)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_STARF_OPEN, CWinApp::OnFileOpen)
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
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

//	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CConStationDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CConStationView));

	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CMainFrame* CConStationApp::GetMainFrame() const
{
#ifdef _DEBUG
	ASSERT(m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)));
#endif
	return (CMainFrame *)m_pMainWnd;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// Globals

const CColor COLOR_WHITE = {1.0f,1.0f,1.0f},
			 COLOR_BLACK = {0.0f,0.0f,0.0f},
			 COLOR_CROSS  = {0.3f,0.3f,0.8f},
			 COLOR_ACTIVESTAR   = {1.0f,0.0f,0.0f},
			 COLOR_NORTHSTAR = {0.0f,1.0f,0.0f},
			 COLOR_CONSTLINE = {0.0f,0.5f,0.5f},
			 COLOR_TERRAIN = {0.0f,0.01f,0.06f};


// Convinience function for glColor3f
void glColor(CColor c)
{
	glColor3f(c.r, c.g, c.b);
}


/////////////////////////////////////////////////////////////////////////////
// CConStationApp message handlers

// Open the about dialog
void CConStationApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CConStationApp::OnStarfNewActual() 
{
	CWinApp::OnFileNew();

	GetMainFrame()->UpdateList();
	GetMainFrame()->GetView()->Projection();
	GetMainFrame()->GetView()->SetState( Viewing );
}

void CConStationApp::OnStarfNewRandom() 
{
	CWinApp::OnFileNew();

	GetMainFrame()->UpdateList();
	GetMainFrame()->GetView()->Projection();
	GetMainFrame()->GetView()->SetState( Viewing );
}

void CConStationApp::OnStarfOpen() 
{
	CWinApp::OnFileOpen();

	GetMainFrame()->UpdateList();
	GetMainFrame()->GetView()->Projection();
	GetMainFrame()->GetView()->SetState( Viewing );
}
