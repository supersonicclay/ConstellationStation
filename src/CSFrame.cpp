//===========================================================================
// CSFrame.cpp
//
// CCSFrame
//   handles (forwards) most non-view related commands and messages.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "CSFrame.h"

#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CCSFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CCSFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
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
	ON_COMMAND(ID_SUN_TOGGLE, OnSunToggle)
	ON_COMMAND(ID_SUNSHINE_TOGGLE, OnSunshineToggle)
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
	ON_UPDATE_COMMAND_UI(ID_SUN_TOGGLE, OnUpdateSunToggle)
	ON_UPDATE_COMMAND_UI(ID_SUNSHINE_TOGGLE, OnUpdateSunshineToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR
};


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CCSFrame::CCSFrame()
{
}

CCSFrame::~CCSFrame()
{
}

int CCSFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	// Load options
	optionsMgr.Load();

	// New document
	documentMgr.NewActual();
	documentMgr.UpdateTitle();


	return 0;
}

BOOL CCSFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

void CCSFrame::OnClose() 
{
	if( documentMgr.CheckModified() == IDCANCEL )
		return;

	// Save options
	optionsMgr.Save();

	CFrameWnd::OnClose();
}


/////////////////////////////////////////////////////////////////////////////
// CCSFrame diagnostics

#ifdef _DEBUG
void CCSFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CCSFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// Gets

CCSView* CCSFrame::GetView()
{
	return &view;
}

CBarConst* CCSFrame::GetConstBar()
{
	return &constBar;
}

CBarStarf* CCSFrame::GetStarfBar()
{
	return &starfBar;
}


/////////////////////////////////////////////////////////////////////////////
// CCSFrame message handlers

void CCSFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	view.SetFocus();
}

BOOL CCSFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (view.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// Application commands
void CCSFrame::OnAppAbout()			{	CDlgAbout().DoModal();			}

// Document commands
void CCSFrame::OnStarfNewActual()	{	documentMgr.NewActual();		}
void CCSFrame::OnStarfNewRandom()	{	documentMgr.NewRandom();		}
void CCSFrame::OnStarfOpen()		{	documentMgr.Open();				}
void CCSFrame::OnStarfSave()		{	documentMgr.Save();				}
void CCSFrame::OnStarfSaveAs()		{	documentMgr.SaveAs();			}

// Starfield commands
void CCSFrame::OnStarfRotate()		{	starfMgr.Rotate();				}
void CCSFrame::OnStarsToggle()		{	starfMgr.ToggleStars();			}
void CCSFrame::OnConstToggle()		{	starfMgr.ToggleConsts();		}
void CCSFrame::OnSunToggle()		{	starfMgr.ToggleSun();			}
void CCSFrame::OnSunshineToggle()	{	starfMgr.ToggleSunshine();		}

// Constellation commands
void CCSFrame::OnConstAdd()			{	constMgr.Add();					}
void CCSFrame::OnConstDelete()		{	constMgr.Delete();				}
void CCSFrame::OnConstRename()		{	constMgr.Rename();				}
void CCSFrame::OnConstHide()		{	constMgr.Hide();				}
void CCSFrame::OnConstAddLine()		{	constMgr.AddLine();				}
void CCSFrame::OnConstDeleteLine()	{	constMgr.DeleteLine();			}
void CCSFrame::OnConstShowHide()	{	constMgr.ShowHide();			}
void CCSFrame::OnConstHideAll()		{	constMgr.HideAll();				}
void CCSFrame::OnConstShowAll()		{	constMgr.ShowAll();				}

// Terrain commands
void CCSFrame::OnTerrNew()			{	terrainMgr.New();				}
void CCSFrame::OnTerrToggle()		{	terrainMgr.Toggle();			}

// Options commands
void CCSFrame::OnOptionsGeneral()	{	optionsMgr.General();			}
void CCSFrame::OnOptionsTime()		{	starfMgr.Time();				}
void CCSFrame::OnOptionsLocation()	{	starfMgr.Location();			}
void CCSFrame::OnOptionsStar()		{	starfMgr.StarOptions();			}
void CCSFrame::OnOptionsConst()		{	starfMgr.ConstOptions();		}
void CCSFrame::OnOptionsSun()		{	starfMgr.SunOptions();			}
void CCSFrame::OnOptionsTerr()		{	terrainMgr.Options();			}


/////////////////////////////////////////////////////////////////////////////
// Updates

void CCSFrame::OnUpdateStarfRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.IsSpinning() );
}

void CCSFrame::OnUpdateStarsToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.AreStarsVisible() );	
}

void CCSFrame::OnUpdateConstList(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing );
}

void CCSFrame::OnUpdateConstAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing );
}

void CCSFrame::OnUpdateConstDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
					starfield.GetConstCount() > 0 );
}

void CCSFrame::OnUpdateConstRename(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
					starfield.GetConstCount() > 0);
}

void CCSFrame::OnUpdateConstHide(CCmdUI* pCmdUI) 
{
	if( starfield.GetConstCount() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( state == state_Viewing );
		pCmdUI->SetCheck(!starfield.GetCurConst()->IsVisible());
	}
}

void CCSFrame::OnUpdateConstAddLine(CCmdUI* pCmdUI) 
{
	if( starfield.GetConstCount() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield.GetCurConst()->IsVisible() );
		pCmdUI->SetCheck( state == state_AddingLine );
	}
}

void CCSFrame::OnUpdateConstDeleteLine(CCmdUI* pCmdUI) 
{
	if( starfield.GetConstCount() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield.GetCurConst()->IsVisible() );
		pCmdUI->SetCheck( state == state_DeletingLine );
	}
}

void CCSFrame::OnUpdateConstHideAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield.GetConstCount() > 0 );
}

void CCSFrame::OnUpdateConstShowAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield.GetConstCount() > 0 );
}

void CCSFrame::OnUpdateConstShowHide(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield.GetConstCount() > 0 );
}

void CCSFrame::OnUpdateConstToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.AreConstsVisible() );	
}

void CCSFrame::OnUpdateTerrToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( optionsMgr.IsTerrVisible() );
}

void CCSFrame::OnUpdateSunToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.IsSunVisible() );
}

void CCSFrame::OnUpdateSunshineToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.IsSunShining() );
}















