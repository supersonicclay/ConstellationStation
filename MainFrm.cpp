// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ConStation.h"
#include "MainFrm.h"

#include "ConstNameDlg.h"
#include "ShowHideDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_CBN_CLOSEUP(ID_CONST_LIST, OnConstListCloseUp)
	ON_COMMAND(ID_CONST_ADD, OnConstAdd)
	ON_COMMAND(ID_CONST_DELETE, OnConstDelete)
	ON_COMMAND(ID_CONST_RENAME, OnConstRename)
	ON_COMMAND(ID_CONST_HIDE, OnConstHide)
	ON_COMMAND(ID_CONST_ALINE, OnConstAddLine)
	ON_COMMAND(ID_CONST_APOLY, OnConstAddPoly)
	ON_COMMAND(ID_CONST_DLINE, OnConstDeleteLine)
	ON_COMMAND(ID_STARF_ROTATE, OnStarfRotate)
	ON_UPDATE_COMMAND_UI(ID_CONST_LIST, OnUpdateConstList)
	ON_UPDATE_COMMAND_UI(ID_CONST_ADD, OnUpdateConstAdd)
	ON_UPDATE_COMMAND_UI(ID_CONST_DELETE, OnUpdateConstDelete)
	ON_UPDATE_COMMAND_UI(ID_CONST_RENAME, OnUpdateConstRename)
	ON_UPDATE_COMMAND_UI(ID_CONST_HIDE, OnUpdateConstHide)
	ON_UPDATE_COMMAND_UI(ID_CONST_ALINE, OnUpdateConstAddLine)
	ON_UPDATE_COMMAND_UI(ID_CONST_APOLY, OnUpdateConstAddPoly)
	ON_UPDATE_COMMAND_UI(ID_CONST_DLINE, OnUpdateConstDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_STARF_ROTATE, OnUpdateStarfRotate)
	ON_COMMAND(ID_SHOW_HIDE, OnShowHide)
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
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	/*
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
///	m_wndDlgBar.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndConstBar);
///	DockControlBar(&m_wndDlgBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////

CStarfield* CMainFrame::GetStarfield() const
{
	return GetView()->GetDocument()->GetStarfield();
}

CConStationView* CMainFrame::GetView() const
{
	return (CConStationView *) GetActiveView();
}


////////////////////////////
// CConStationView States //
////////////////////////////
StateType CMainFrame::GetState() const
{
	return ((CConStationView *)GetActiveView())->GetState();
}

void CMainFrame::SetState(StateType state) const
{
	((CConStationView *)GetActiveView())->SetState(state);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnConstListCloseUp()
{
	if (m_wndConstBar.m_List.GetCurSel() != CB_ERR)
	{
		GetStarfield()->SetCurConstellation(m_wndConstBar.GetCurConst());
		GetView()->InvalidateRect(NULL, FALSE);
	}

	SetFocus();
}

void CMainFrame::OnConstAdd() 
{
	CConstNameDlg dialog;

	CString constName = "Untitled ";

	// Check for other untitled constellations
	int numUntitled = 1;
	for (int i=0; i<GetStarfield()->GetNumConstellations(); i++)
	{
		if (GetStarfield()->IsDuplicate(constName + char('0' + numUntitled)))
			numUntitled++;
		else
			break;
	}

	// Set the name in dialog to the appropriate untitled number
	dialog.SetConstName(constName + char('0' + numUntitled));

	// If they cancel, return
	if (dialog.DoModal() != IDOK)
		return;

	// Check for duplicate name
	while (GetStarfield()->IsDuplicate(dialog.m_Name))
	{
		MessageBox("There is already a constellation with this name.",
			"Error", MB_OK | MB_ICONEXCLAMATION);

		if (dialog.DoModal() != IDOK)
			return;
	}

	// Add constellation and make it the current constellation
	m_wndConstBar.AddConst(dialog.m_Name);
	GetStarfield()->AddConstellation(dialog.m_Name);
	GetStarfield()->SetCurConstellation(dialog.m_Name);
	GetView()->InvalidateRect(NULL, FALSE);
}

void CMainFrame::OnConstDelete() 
{
	int m = MessageBox("Are you sure you want to delete this constellation?",
		"Delete Constellation?", MB_YESNO | MB_ICONEXCLAMATION);

	if (m == IDYES)
	{
		GetStarfield()->DeleteConstellation();
		m_wndConstBar.DeleteConst();
		SetState(Viewing);
		GetView()->InvalidateRect(NULL, FALSE);
	}
}

void CMainFrame::OnConstRename() 
{
	CConstNameDlg dialog;

	CString constName = m_wndConstBar.GetCurConst();
	dialog.SetConstName(constName);

	// If they cancel, return
	if (dialog.DoModal() != IDOK)
		return;

	// Check for duplicate name
	while (GetStarfield()->IsDuplicate(dialog.m_Name))
	{
		MessageBox("There is already a constellation with this name.",
			"Error", MB_OK | MB_ICONEXCLAMATION);

		if (dialog.DoModal() != IDOK)
			return;
	}

	// Rename constellation

	// Add constellation and make it the current constellation
	m_wndConstBar.DeleteConst();
	m_wndConstBar.AddConst(dialog.m_Name);

	GetStarfield()->RenameConstellation(dialog.m_Name);
///	m_wndConstBar.AddConst(dialog.m_Name);
///	GetStarfield()->AddConstellation(dialog.m_Name);
///	GetStarfield()->SetCurConstellation(dialog.m_Name);
///	GetView()->InvalidateRect(NULL, FALSE);

}

void CMainFrame::OnConstHide() 
{
	GetStarfield()->GetCurConstellation()->SwitchVisible();

	GetActiveView()->InvalidateRect(NULL, FALSE);
}

void CMainFrame::OnConstAddLine() 
{
	if (GetState() == AddingLine)
		SetState(Viewing);
	else
		SetState(AddingLine);
}

void CMainFrame::OnConstAddPoly() 
{
	if (GetState() == AddingPoly)
		SetState(Viewing);
	else
		SetState(AddingPoly);
}

void CMainFrame::OnConstDeleteLine() 
{
	if (GetState() == DeletingLine)
		SetState(Viewing);
	else
		SetState(DeletingLine);
}

void CMainFrame::OnStarfRotate() 
{
	GetStarfield()->SwitchSpinning();	
}


/////////////
// Updates //
/////////////
void CMainFrame::OnUpdateConstList(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetState() == Viewing);
}

void CMainFrame::OnUpdateConstAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetState() == Viewing);
}

void CMainFrame::OnUpdateConstDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndConstBar.m_List.GetCount() != 0 &&
					GetState() == Viewing);
}

void CMainFrame::OnUpdateConstRename(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndConstBar.m_List.GetCount() != 0);
}

void CMainFrame::OnUpdateConstHide(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndConstBar.m_List.GetCount() != 0 &&
					GetState() == Viewing);
	pCmdUI->SetCheck(!GetStarfield()->GetCurConstellation()->IsVisible());
}

void CMainFrame::OnUpdateConstAddLine(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndConstBar.m_List.GetCount() != 0);
	pCmdUI->SetCheck(GetState() == AddingLine);
}

void CMainFrame::OnUpdateConstAddPoly(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndConstBar.m_List.GetCount() != 0);
	pCmdUI->SetCheck(GetState() == AddingPoly);
}

void CMainFrame::OnUpdateConstDeleteLine(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndConstBar.m_List.GetCount() != 0);
	pCmdUI->SetCheck(GetState() == DeletingLine);
}

void CMainFrame::OnUpdateStarfRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetStarfield()->IsSpinning());
}

void CMainFrame::OnShowHide() 
{
	CShowHideDlg dialog;

	dialog.DoModal();

}
