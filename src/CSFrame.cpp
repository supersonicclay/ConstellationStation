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
	ON_COMMAND(ID_STARS_TOGGLE, OnStarsToggle)
	ON_COMMAND(ID_CONST_ADD, OnConstAdd)
	ON_COMMAND(ID_CONST_DELETE, OnConstDelete)
	ON_COMMAND(ID_CONST_RENAME, OnConstRename)
	ON_COMMAND(ID_CONST_ALINE, OnConstAddLine)
	ON_COMMAND(ID_CONST_DLINE, OnConstDeleteLine)
	ON_COMMAND(ID_CONST_TOGGLE, OnConstToggle)
	ON_COMMAND(ID_CONST_LINESTOGGLE, OnConstLinesToggle)
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
	ON_COMMAND(ID_OPTIONS_COLOR, OnOptionsColor)
	ON_COMMAND(ID_OPTIONS_TEXT, OnOptionsText)
	ON_COMMAND(ID_VIEW_FINDTRACK, OnViewFindTrack)
	ON_COMMAND(ID_ANIM_PREV, OnAnimPrev)
	ON_COMMAND(ID_ANIM_REV, OnAnimRev)
	ON_COMMAND(ID_ANIM_PAUSE, OnAnimPause)
	ON_COMMAND(ID_ANIM_PLAY, OnAnimPlay)
	ON_COMMAND(ID_ANIM_NEXT, OnAnimNext)
	ON_UPDATE_COMMAND_UI(ID_STARS_TOGGLE, OnUpdateStarsToggle)
	ON_UPDATE_COMMAND_UI(ID_CONST_LIST, OnUpdateConstList)
	ON_UPDATE_COMMAND_UI(ID_CONST_ADD, OnUpdateConstAdd)
	ON_UPDATE_COMMAND_UI(ID_CONST_DELETE, OnUpdateConstDelete)
	ON_UPDATE_COMMAND_UI(ID_CONST_RENAME, OnUpdateConstRename)
	ON_UPDATE_COMMAND_UI(ID_CONST_ALINE, OnUpdateConstAddLine)
	ON_UPDATE_COMMAND_UI(ID_CONST_DLINE, OnUpdateConstDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_CONST_TOGGLE, OnUpdateConstToggle)
	ON_UPDATE_COMMAND_UI(ID_CONST_LINESTOGGLE, OnUpdateConstLinesToggle)
	ON_UPDATE_COMMAND_UI(ID_TERR_TOGGLE, OnUpdateTerrToggle)
	ON_UPDATE_COMMAND_UI(ID_SUN_TOGGLE, OnUpdateSunToggle)
	ON_UPDATE_COMMAND_UI(ID_SUNSHINE_TOGGLE, OnUpdateSunshineToggle)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FINDTRACK, OnUpdateViewFindTrack)
	ON_UPDATE_COMMAND_UI(ID_ANIM_PREV, OnUpdateAnimPrev)
	ON_UPDATE_COMMAND_UI(ID_ANIM_REV, OnUpdateAnimRev)
	ON_UPDATE_COMMAND_UI(ID_ANIM_PAUSE, OnUpdateAnimPause)
	ON_UPDATE_COMMAND_UI(ID_ANIM_PLAY, OnUpdateAnimPlay)
	ON_UPDATE_COMMAND_UI(ID_ANIM_NEXT, OnUpdateAnimNext)
	ON_COMMAND(ID_POPUPCONST_CENTER, OnPopupConstCenter)
	ON_COMMAND(ID_POPUPCONST_TRACK, OnPopupConstTrack)
	ON_COMMAND(ID_POPUPCONST_INFO, OnPopupConstInfo)
	ON_COMMAND(ID_POPUPSTAR_CENTER, OnPopupStarCenter)
	ON_COMMAND(ID_POPUPSTAR_TRACK, OnPopupStarTrack)
	ON_COMMAND(ID_POPUPSTAR_INFO, OnPopupStarInfo)
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

	// Try initializing OpenGL
	if( !graphicsMgr.InitializeOpenGL() )
	{
		CSDebug( "Error initializing OpenGL", "CCSView::OnCreate" );
		graphicsMgr.Destroy();
		exit(0);
		return -1;
	}

	// Initialize fonts
	textMgr.InitFonts();

	// Load options
	optionsMgr.Load();
	///optionsMgr.LoadDefaults();/// always defaults

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
void CCSFrame::OnStarsToggle()		{	starfMgr.ToggleStars();			}
void CCSFrame::OnConstToggle()		{	starfMgr.ToggleConsts();		}
void CCSFrame::OnConstLinesToggle()	{	starfMgr.ToggleConstsLines();	}
void CCSFrame::OnSunToggle()		{	starfMgr.ToggleSun();			}
void CCSFrame::OnSunshineToggle()	{	starfMgr.ToggleSunshine();		}

// Constellation commands
void CCSFrame::OnConstAdd()			{	constMgr.Add();					}
void CCSFrame::OnConstDelete()		{	constMgr.Delete();				}
void CCSFrame::OnConstRename()		{	constMgr.Rename();				}
void CCSFrame::OnConstAddLine()		{	constMgr.AddLine();				}
void CCSFrame::OnConstDeleteLine()	{	constMgr.DeleteLine();			}

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
void CCSFrame::OnOptionsColor()		{	optionsMgr.ColorOptions();		}
void CCSFrame::OnOptionsText()		{	textMgr.Options();				}

// View commands
void CCSFrame::OnViewFindTrack()	{	starfMgr.FindTrack();			}

// Animation commands
void CCSFrame::OnAnimPrev()			{	starfMgr.Previous();			}
void CCSFrame::OnAnimRev()			{	starfMgr.Reverse();				}
void CCSFrame::OnAnimPause()		{	starfMgr.Pause();				}
void CCSFrame::OnAnimPlay()			{	starfMgr.Forward();				}
void CCSFrame::OnAnimNext()			{	starfMgr.Next();				}

// Popup commands
void CCSFrame::OnPopupConstCenter() 
{
	starfield.FindConst( inputMgr.popupConstNum );
	constMgr.Select( inputMgr.popupConstNum );
	Redraw();
}

void CCSFrame::OnPopupConstTrack() 
{
	starfield.StartTrackingConst( inputMgr.popupConstNum );
	constMgr.Select( inputMgr.popupConstNum );
	Redraw();
}

void CCSFrame::OnPopupConstInfo() 
{
	starfMgr.ConstInfo( inputMgr.popupConstNum );
}

void CCSFrame::OnPopupStarCenter() 
{
	starfield.FindStar( inputMgr.popupStarNum );
	Redraw();
}

void CCSFrame::OnPopupStarTrack() 
{
	starfield.StartTrackingStar( inputMgr.popupStarNum );
	Redraw();
}

void CCSFrame::OnPopupStarInfo() 
{
	starfMgr.StarInfo( inputMgr.popupStarNum );
}

/////////////////////////////////////////////////////////////////////////////
// Updates

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

void CCSFrame::OnUpdateConstAddLine(CCmdUI* pCmdUI) 
{
	if( starfield.GetConstCount() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield.AreConstsVisible() && starfield.AreConstsLinesVisible() );
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
		pCmdUI->Enable( starfield.AreConstsVisible() && starfield.AreConstsLinesVisible() );
		pCmdUI->SetCheck( state == state_DeletingLine );
	}
}

void CCSFrame::OnUpdateConstToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.AreConstsVisible() );	
}

void CCSFrame::OnUpdateConstLinesToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( !starfield.AreConstsLinesVisible() );	
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

void CCSFrame::OnUpdateViewFindTrack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing );
	
}

void CCSFrame::OnUpdateAnimPrev(CCmdUI* pCmdUI) 
{
}

void CCSFrame::OnUpdateAnimRev(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.GetAnimation() == animation_Reverse );
}

void CCSFrame::OnUpdateAnimPause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.GetAnimation() == animation_Paused );
}

void CCSFrame::OnUpdateAnimPlay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield.GetAnimation() == animation_Forward );
}

void CCSFrame::OnUpdateAnimNext(CCmdUI* pCmdUI) 
{
}















