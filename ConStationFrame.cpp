// ConStationFrame.cpp : implementation of the CConStationFrame class
//

#include "stdafx.h"
#include "ConStation.h"
#include "ConStationFrame.h"

#include "DlgConstName.h"
#include "DlgShowHide.h"
#include "DlgTerrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConStationFrame

IMPLEMENT_DYNCREATE(CConStationFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CConStationFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CConStationFrame)
	ON_WM_CREATE()
	ON_CBN_CLOSEUP(ID_CONST_LIST, OnConstListCloseUp)
	ON_COMMAND(ID_CONST_ADD, OnConstAdd)
	ON_COMMAND(ID_CONST_DELETE, OnConstDelete)
	ON_COMMAND(ID_CONST_RENAME, OnConstRename)
	ON_COMMAND(ID_CONST_HIDE, OnConstHide)
	ON_COMMAND(ID_CONST_ALINE, OnConstAddLine)
	ON_COMMAND(ID_CONST_APOLY, OnConstAddPoly)
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
	ON_UPDATE_COMMAND_UI(ID_CONST_APOLY, OnUpdateConstAddPoly)
	ON_UPDATE_COMMAND_UI(ID_CONST_DLINE, OnUpdateConstDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_STARF_ROTATE, OnUpdateStarfRotate)
	ON_UPDATE_COMMAND_UI(ID_CONST_HIDEALL, OnUpdateConstHideAll)
	ON_UPDATE_COMMAND_UI(ID_CONST_SHOWALL, OnUpdateConstShowAll)
	ON_UPDATE_COMMAND_UI(ID_CONST_SHOWHIDE, OnUpdateConstShowHide)
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

	// Starfield ToolBar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	/* ///
	CToolBar* constToolBar = new CToolBar;
	if (!constToolBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!constToolBar->LoadToolBar(IDR_CONSTELLATION))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	*/

	// Constellation ToolBar
	if (!m_wndConstBar.Init(this))
	{
		TRACE0("Failed to create constellation bar\n");
		return -1;		// fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators, 1))
		  //sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Docking
	EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndConstBar.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndConstBar);

	return 0;
}

BOOL CConStationFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

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

CConStationView* CConStationFrame::GetView() const
{
#ifdef _DEBUG
	ASSERT (GetActiveView()->IsKindOf( RUNTIME_CLASS (CConStationView)));
#endif
	return (CConStationView *) GetActiveView();
}


// Make sure ConstList is consistent with the constellation names in Starfield
void CConStationFrame::UpdateList()
{
	int numConstellations = starfield->GetNumConstellations();
	int numCurrent = starfield->GetNumCurConstellation();
	CString* constellationNames = new CString[numConstellations];

	for (int i=0; i<numConstellations; i++)
	{
		constellationNames[i] = starfield->GetConstellation(i)->GetName();
	}

	// Send the names to ConstList
	m_wndConstBar.UpdateList(constellationNames, numConstellations, numCurrent);

	delete[] constellationNames;
}


/////////////////////////////////////////////////////////////////////////////
// CConStationFrame message handlers

void CConStationFrame::OnConstListCloseUp()
{
	if (m_wndConstBar.m_List.GetCurSel() != CB_ERR)
	{
		starfield->SetCurConstellation(m_wndConstBar.GetCurConst());
		GetView()->Redraw();
	}

	SetFocus();
}

void CConStationFrame::OnConstAdd() 
{
	if( starfield->IsSpinning() )
		starfield->SwitchSpinning();

	CDlgConstName dialog;

	// Set name initially to "Constellation" prepended to a number
	//  the 
	CString constName = "Constellation";

	// The total number of created constellaitons (starting at 1)
	const int numNewConstellations = starfield->GetNumNewConstellations();

	// Convert the number to a string and append
	char numString[20];
	itoa (numNewConstellations+1, numString, 10);
	constName += numString;

	dialog.SetConstName(constName);

	// If they cancel, return
	if (dialog.DoModal() != IDOK)
		return;

	// Check for duplicate name
	while (starfield->IsDuplicate(dialog.m_Name))
	{
		MessageBox("There is already a constellation with this name.",
			"Error", MB_OK | MB_ICONEXCLAMATION);

		if (dialog.DoModal() != IDOK)
			return;
	}

	// Add constellation and make it the current constellation
	m_wndConstBar.AddConst(dialog.m_Name);
	starfield->AddConstellation(dialog.m_Name);
	starfield->IncNumNewConstellations();
	starfield->SetCurConstellation(dialog.m_Name);

	GetActiveDocument()->SetModifiedFlag();
	GetView()->Redraw();
}

void CConStationFrame::OnConstDelete() 
{
	if( starfield->IsSpinning() )
		starfield->SwitchSpinning();

	int m = MessageBox("Are you sure you want to delete this constellation?",
		"Delete Constellation?", MB_YESNO | MB_ICONEXCLAMATION);

	if (m == IDYES)
	{
		starfield->DeleteConstellation();
		m_wndConstBar.DeleteConst();

		// Set newly selected constellation as the current one
		if (starfield->GetNumConstellations() > 0)
			starfield->SetCurConstellation(m_wndConstBar.GetCurConst());

		SetState( state_Viewing );

		GetActiveDocument()->SetModifiedFlag();
		GetView()->Redraw();
	}
}

void CConStationFrame::OnConstRename() 
{
	if( starfield->IsSpinning() )
		starfield->SwitchSpinning();

	CDlgConstName dialog;

	CString origConstName = m_wndConstBar.GetCurConst();
	dialog.SetConstName(origConstName);

	// If they cancel, return
	if (dialog.DoModal() != IDOK)
		return;

	// Check for duplicate name
	while (starfield->IsDuplicate(dialog.m_Name) &&
		dialog.m_Name != origConstName)
	{
		MessageBox("There is already a constellation with this name.",
			"Error", MB_OK | MB_ICONEXCLAMATION);

		if (dialog.DoModal() != IDOK)
			return;
	}

	// If it wasn't renamed
	if (dialog.m_Name == origConstName)
		return;

	// Otherwise Rename constellation

	// Remove old name from the list and add new name
	m_wndConstBar.DeleteConst();
	m_wndConstBar.AddConst(dialog.m_Name);

	starfield->RenameConstellation(dialog.m_Name);

	GetActiveDocument()->SetModifiedFlag();
}

void CConStationFrame::OnConstHide() 
{
	starfield->GetCurConstellation()->SwitchVisible();

	GetActiveDocument()->SetModifiedFlag();
	GetView()->Redraw();
}

void CConStationFrame::OnConstAddLine() 
{
	if (state == state_AddingLine)
		SetState( state_Viewing );
	else
		SetState( state_AddingLine );
}

void CConStationFrame::OnConstAddPoly() 
{
	if( state == state_AddingPoly )
		SetState( state_Viewing );
	else
		SetState( state_AddingPoly );
}

void CConStationFrame::OnConstDeleteLine() 
{
	if (state == state_DeletingLine)
		SetState( state_Viewing );
	else
		SetState( state_DeletingLine );
}

void CConStationFrame::OnStarfRotate() 
{
	starfield->SwitchSpinning();	
}

void CConStationFrame::OnConstShowHide() 
{
	if( starfield->IsSpinning() )
		starfield->SwitchSpinning();

	CDlgShowHide dialog;

	dialog.DoModal();

	GetActiveDocument()->SetModifiedFlag();
	SetState( state_Viewing );
}

void CConStationFrame::OnConstHideAll() 
{
	for (int i=0; i<starfield->GetNumConstellations(); i++)
	{
		starfield->GetConstellation(i)->SetVisible(FALSE);
	}

	GetActiveDocument()->SetModifiedFlag();
	GetView()->Redraw();
}

void CConStationFrame::OnConstShowAll() 
{
	for (int i=0; i<starfield->GetNumConstellations(); i++)
	{
		starfield->GetConstellation(i)->SetVisible(TRUE);
	}

	GetActiveDocument()->SetModifiedFlag();
	GetView()->Redraw();
}

void CConStationFrame::OnTerrainNew() 
{
	terrain->MakeTerrain();
	RedrawView();
}

void CConStationFrame::OnOptionsTerrain() 
{
	if( starfield->IsSpinning() )
		starfield->SwitchSpinning();

	float r = terrain->GetRoughness();
	color_t c = terrain->GetColor();

	CDlgTerrain* dialog = new CDlgTerrain( r, c );

	dialog->DoModal();

	if( dialog->needsUpdate )
	{
		terrain->MakeTerrain();
		RedrawView();
	}

	delete dialog;
}

void CConStationFrame::OnOptionsLocation() 
{
	if( starfield->IsSpinning() )
		starfield->SwitchSpinning();

	/// LOCATION DIALOG
	
}


/////////////
// Updates //
/////////////
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
					starfield->GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateConstRename(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
					starfield->GetNumConstellations() > 0);
}

void CConStationFrame::OnUpdateConstHide(CCmdUI* pCmdUI) 
{
	if( starfield->GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( state == state_Viewing );
		pCmdUI->SetCheck(!starfield->GetCurConstellation()->IsVisible());
	}
}

void CConStationFrame::OnUpdateConstAddLine(CCmdUI* pCmdUI) 
{
	if( starfield->GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield->GetCurConstellation()->IsVisible() );
		pCmdUI->SetCheck( state == state_AddingLine );
	}
}

void CConStationFrame::OnUpdateConstAddPoly(CCmdUI* pCmdUI) 
{
	if( starfield->GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield->GetCurConstellation()->IsVisible() );
		pCmdUI->SetCheck( state == state_AddingPoly );
	}
}

void CConStationFrame::OnUpdateConstDeleteLine(CCmdUI* pCmdUI) 
{
	if( starfield->GetNumConstellations() == 0 )
	{
		pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck( FALSE );
	}
	else
	{
		pCmdUI->Enable( starfield->GetCurConstellation()->IsVisible() );
		pCmdUI->SetCheck( state == state_DeletingLine );
	}
}

void CConStationFrame::OnUpdateConstHideAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield->GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateConstShowAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield->GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateConstShowHide(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( state == state_Viewing &&
		starfield->GetNumConstellations() > 0 );
}

void CConStationFrame::OnUpdateStarfRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( starfield->IsSpinning() );
}


