//===========================================================================
// ConStationFrame.cpp
//
// CConStationFrame
///   contains all toolbars and dialogs. Forwards commands.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "ConStationFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConStationFrame

BEGIN_MESSAGE_MAP(CConStationFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CConStationFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_CONST_ADD, OnConstAdd)
	ON_COMMAND(ID_CONST_DELETE, OnConstDelete)
	ON_COMMAND(ID_CONST_RENAME, OnConstRename)
	ON_COMMAND(ID_CONST_HIDE, OnConstHide)
	ON_COMMAND(ID_CONST_ALINE, OnConstAddLine)
	ON_COMMAND(ID_CONST_DLINE, OnConstDeleteLine)
	ON_COMMAND(ID_CONST_SHOWHIDE, OnConstShowHide)
	ON_COMMAND(ID_CONST_HIDEALL, OnConstHideAll)
	ON_COMMAND(ID_CONST_SHOWALL, OnConstShowAll)
	ON_COMMAND(ID_STARF_ROTATE, OnStarfRotate)
	ON_COMMAND(ID_TERR_NEW, OnTerrainNew)
	ON_COMMAND(ID_OPTIONS_TERRAIN, OnOptionsTerrain)
	ON_COMMAND(ID_OPTIONS_LOCATION, OnOptionsLocation)
	ON_UPDATE_COMMAND_UI(ID_CONST_LIST, OnUpdateConstList)
	ON_UPDATE_COMMAND_UI(ID_CONST_ADD, OnUpdateConstAdd)
	ON_UPDATE_COMMAND_UI(ID_CONST_DELETE, OnUpdateConstDelete)
	ON_UPDATE_COMMAND_UI(ID_CONST_RENAME, OnUpdateConstRename)
	ON_UPDATE_COMMAND_UI(ID_CONST_HIDE, OnUpdateConstHide)
	ON_UPDATE_COMMAND_UI(ID_CONST_ALINE, OnUpdateConstAddLine)
	ON_UPDATE_COMMAND_UI(ID_CONST_DLINE, OnUpdateConstDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_STARF_ROTATE, OnUpdateStarfRotate)
	ON_UPDATE_COMMAND_UI(ID_CONST_HIDEALL, OnUpdateConstHideAll)
	ON_UPDATE_COMMAND_UI(ID_CONST_SHOWALL, OnUpdateConstShowAll)
	ON_UPDATE_COMMAND_UI(ID_CONST_SHOWHIDE, OnUpdateConstShowHide)
	ON_COMMAND(ID_OPTIONS_TIME, OnOptionsTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CConStationFrame construction/destruction

CConStationFrame::CConStationFrame()
{
}

CConStationFrame::~CConStationFrame()
{
}

int CConStationFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Child View
	if (!view.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Starfield ToolBar
	if (!starfBar.Init(this))
	{
		TRACE0("Failed to create starfield toolbar\n");
		return -1;
	}

	// Constellation ToolBar
	if (!constBar.Init(this))
	{
		TRACE0("Failed to create constellation bar\n");
		return -1;
	}

	// Status Bar
	if (!statusBar.Create(this) ||
		!statusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	// Docking
	EnableDocking(CBRS_ALIGN_ANY);

	starfBar.EnableDocking(CBRS_ALIGN_ANY);
	constBar.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&starfBar);
	DockControlBar(&constBar);

	return 0;
}

BOOL CConStationFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CConStationFrame diagnostics

#ifdef _DEBUG
void CConStationFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CConStationFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////

void CConStationFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	view.SetFocus();
}

BOOL CConStationFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (view.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CConStationView* CConStationFrame::GetView()
{
	return &view;
}

CBarConst* CConStationFrame::GetConstBar()
{
	return &constBar;
}

CBarStarf* CConStationFrame::GetStarfBar()
{
	return &starfBar;
}


/////////////////////////////////////////////////////////////////////////////
// CConStationFrame message handlers

// Constellation commands
void CConStationFrame::OnConstAdd()			{	constMgr.Add();		}
void CConStationFrame::OnConstDelete()		{	constMgr.Delete();		}
void CConStationFrame::OnConstRename()		{	constMgr.Rename();		}
void CConStationFrame::OnConstHide()		{	constMgr.Hide();		}
void CConStationFrame::OnConstAddLine()		{	constMgr.AddLine();	}
void CConStationFrame::OnConstDeleteLine()	{	constMgr.DeleteLine();	}
void CConStationFrame::OnConstShowHide()	{	constMgr.ShowHide();	}
void CConStationFrame::OnConstHideAll()		{	constMgr.HideAll();	}
void CConStationFrame::OnConstShowAll()		{	constMgr.ShowAll();	}

// Starfield commands
void CConStationFrame::OnStarfRotate()		{	starfMgr.Rotate();		}
void CConStationFrame::OnOptionsLocation()	{	starfMgr.Location();	}
void CConStationFrame::OnOptionsTime()		{	starfMgr.Time();		}

// Terrain commands
void CConStationFrame::OnTerrainNew()		{	terrainMgr.New();		}
void CConStationFrame::OnOptionsTerrain()	{	terrainMgr.Options();	}


// Updates
void CConStationFrame::OnUpdateConstList(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing );
}

void CConStationFrame::OnUpdateConstAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing );
}

void CConStationFrame::OnUpdateConstDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
					starfield.GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateConstRename(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
					starfield.GetNumConstellations() > 0);
}

void CConStationFrame::OnUpdateConstHide(CCmdUI* pCmdUI) 
{
	if( starfield.GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( state == state_Viewing );
		pCmdUI->SetCheck(!starfield.GetCurConstellation()->IsVisible());
	}
}

void CConStationFrame::OnUpdateConstAddLine(CCmdUI* pCmdUI) 
{
	if( starfield.GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield.GetCurConstellation()->IsVisible() );
		pCmdUI->SetCheck( state == state_AddingLine );
	}
}

void CConStationFrame::OnUpdateConstDeleteLine(CCmdUI* pCmdUI) 
{
	if( starfield.GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield.GetCurConstellation()->IsVisible() );
		pCmdUI->SetCheck( state == state_DeletingLine );
	}
}

void CConStationFrame::OnUpdateConstHideAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield.GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateConstShowAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield.GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateConstShowHide(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield.GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateStarfRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.IsSpinning() );
}








