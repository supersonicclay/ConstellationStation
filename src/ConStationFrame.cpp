//===========================================================================
// ConStationFrame.cpp
//
// CConStationFrame
//   handles (forwards) most non-view related commands and messages.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "ConStationFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CConStationFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CConStationFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_COMMAND(ID_STARF_NEWACTUAL, OnStarfNewActual)
	ON_COMMAND(ID_STARF_NEWRANDOM, OnStarfNewRandom)
	ON_COMMAND(ID_STARF_OPEN, OnStarfOpen)
	ON_COMMAND(ID_STARF_SAVE, OnStarfSave)
	ON_COMMAND(ID_STARF_SAVEAS, OnStarfSaveAs)
	ON_COMMAND(ID_STARF_ROTATE, OnStarfRotate)
	ON_COMMAND(ID_STARS_TOGGLE, OnStarsToggle)
	ON_COMMAND(ID_CONST_ADD, OnConstAdd)
	ON_COMMAND(ID_CONST_DELETE, OnConstDelete)
	ON_COMMAND(ID_CONST_RENAME, OnConstRename)
	ON_COMMAND(ID_CONST_HIDE, OnConstHide)
	ON_COMMAND(ID_CONST_ALINE, OnConstAddLine)
	ON_COMMAND(ID_CONST_DLINE, OnConstDeleteLine)
	ON_COMMAND(ID_CONST_SHOWHIDE, OnConstShowHide)
	ON_COMMAND(ID_CONST_HIDEALL, OnConstHideAll)
	ON_COMMAND(ID_CONST_SHOWALL, OnConstShowAll)
	ON_COMMAND(ID_CONST_TOGGLE, OnConstToggle)
	ON_COMMAND(ID_TERR_NEW, OnTerrNew)
	ON_COMMAND(ID_TERR_TOGGLE, OnTerrToggle)
	ON_COMMAND(ID_OPTIONS_GENERAL, OnOptionsGeneral)
	ON_COMMAND(ID_OPTIONS_TIME, OnOptionsTime)
	ON_COMMAND(ID_OPTIONS_LOCATION, OnOptionsLocation)
	ON_COMMAND(ID_OPTIONS_STAR, OnOptionsStar)
	ON_COMMAND(ID_OPTIONS_CONST, OnOptionsConst)
	ON_COMMAND(ID_OPTIONS_SUN, OnOptionsSun)
	ON_COMMAND(ID_OPTIONS_TERR, OnOptionsTerr)
	ON_UPDATE_COMMAND_UI(ID_STARF_ROTATE, OnUpdateStarfRotate)
	ON_UPDATE_COMMAND_UI(ID_STARS_TOGGLE, OnUpdateStarsToggle)
	ON_UPDATE_COMMAND_UI(ID_CONST_LIST, OnUpdateConstList)
	ON_UPDATE_COMMAND_UI(ID_CONST_ADD, OnUpdateConstAdd)
	ON_UPDATE_COMMAND_UI(ID_CONST_DELETE, OnUpdateConstDelete)
	ON_UPDATE_COMMAND_UI(ID_CONST_RENAME, OnUpdateConstRename)
	ON_UPDATE_COMMAND_UI(ID_CONST_HIDE, OnUpdateConstHide)
	ON_UPDATE_COMMAND_UI(ID_CONST_ALINE, OnUpdateConstAddLine)
	ON_UPDATE_COMMAND_UI(ID_CONST_DLINE, OnUpdateConstDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_CONST_HIDEALL, OnUpdateConstHideAll)
	ON_UPDATE_COMMAND_UI(ID_CONST_SHOWALL, OnUpdateConstShowAll)
	ON_UPDATE_COMMAND_UI(ID_CONST_SHOWHIDE, OnUpdateConstShowHide)
	ON_UPDATE_COMMAND_UI(ID_CONST_TOGGLE, OnUpdateConstToggle)
	ON_UPDATE_COMMAND_UI(ID_TERR_TOGGLE, OnUpdateTerrToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR
};

/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

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

	// New document
	documentMgr.NewActual();
	documentMgr.UpdateTitle();

	// Load options
	optionsMgr.Load();

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

void CConStationFrame::OnClose() 
{
	if( documentMgr.CheckModified() == IDCANCEL )
		return;

	/// Save options
	optionsMgr.Save();

	CFrameWnd::OnClose();
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

// Document commands
void CConStationFrame::OnStarfNewActual()	{	documentMgr.NewActual();	}
void CConStationFrame::OnStarfNewRandom()	{	documentMgr.NewRandom();	}
void CConStationFrame::OnStarfOpen()		{	documentMgr.Open();			}
void CConStationFrame::OnStarfSave()		{	documentMgr.Save();			}
void CConStationFrame::OnStarfSaveAs()		{	documentMgr.SaveAs();		}

// Starfield commands
void CConStationFrame::OnStarfRotate()		{	starfieldMgr.Rotate();		}
void CConStationFrame::OnStarsToggle()		{	starfieldMgr.ToggleStars();	}
void CConStationFrame::OnConstToggle()		{	starfieldMgr.ToggleConsts();}
//void CConStationFram::OnSunToggle()			{	starfieldMgr.ToggleSun();	}

// Constellation commands
void CConStationFrame::OnConstAdd()			{	constMgr.Add();				}
void CConStationFrame::OnConstDelete()		{	constMgr.Delete();			}
void CConStationFrame::OnConstRename()		{	constMgr.Rename();			}
void CConStationFrame::OnConstHide()		{	constMgr.Hide();			}
void CConStationFrame::OnConstAddLine()		{	constMgr.AddLine();			}
void CConStationFrame::OnConstDeleteLine()	{	constMgr.DeleteLine();		}
void CConStationFrame::OnConstShowHide()	{	constMgr.ShowHide();		}
void CConStationFrame::OnConstHideAll()		{	constMgr.HideAll();			}
void CConStationFrame::OnConstShowAll()		{	constMgr.ShowAll();			}

// Terrain commands
void CConStationFrame::OnTerrNew()			{	terrainMgr.New();			}
void CConStationFrame::OnTerrToggle()		{	terrainMgr.Toggle();		}

// Options commands
void CConStationFrame::OnOptionsGeneral()	{	optionsMgr.General();		}
void CConStationFrame::OnOptionsTime()		{	starfieldMgr.Time();		}
void CConStationFrame::OnOptionsLocation()	{	starfieldMgr.Location();	}
void CConStationFrame::OnOptionsStar()		{	starfieldMgr.StarOptions();	}
void CConStationFrame::OnOptionsConst()		{	starfieldMgr.ConstOptions();}
void CConStationFrame::OnOptionsSun()		{	starfieldMgr.SunOptions();	}
void CConStationFrame::OnOptionsTerr()		{	terrainMgr.Options();		}


/////////////////////////////////////////////////////////////////////////////
// Updates

void CConStationFrame::OnUpdateStarfRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.IsSpinning() );
}

void CConStationFrame::OnUpdateStarsToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.AreStarsVisible() );	
}

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

void CConStationFrame::OnUpdateConstToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.AreConstsVisible() );	
}

void CConStationFrame::OnUpdateTerrToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( terrain.IsVisible() );
}















void CConStationFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
