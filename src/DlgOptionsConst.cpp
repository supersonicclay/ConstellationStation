//===========================================================================
// DlgOptionsConst.cpp
//
// CDlgOptionsConst
//   constellation options dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgOptionsConst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsConst::CDlgOptionsConst(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsConst::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsConst)
	visible = FALSE;
	labeled = FALSE;
	lineWidth = -1;
	daylight = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsConst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsConst)
	DDX_Control(pDX, IDC_CONST_LINEWIDTH, lineWidthControl);
	DDX_Check(pDX, IDC_CONST_VISIBLE, visible);
	DDX_Check(pDX, IDC_CONST_LABELED, labeled);
	DDX_CBIndex(pDX, IDC_CONST_LINEWIDTH, lineWidth);
	DDX_Check(pDX, IDC_CONST_DAYLIGHT, daylight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsConst, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsConst)
	ON_BN_CLICKED(IDC_CONST_DEFAULTS, OnConstDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsConst message handlers

BOOL CDlgOptionsConst::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Make lineWidthControl listbox taller
	CRect r;
	lineWidthControl.GetDroppedControlRect( &r );
	lineWidthControl.GetParent()->ScreenToClient( &r );
	r.bottom = r.top + 150;
	lineWidthControl.MoveWindow( &r );

	InitOptions();

	return TRUE;
}

void CDlgOptionsConst::InitOptions()
{
	CheckDlgButton( IDC_CONST_VISIBLE, starfield.AreConstsVisible() );
	CheckDlgButton( IDC_CONST_DAYLIGHT, starfield.AreConstsDaylight() );
	CheckDlgButton( IDC_CONST_LABELED, starfield.AreConstsLabeled() );
	lineWidthControl.SetCurSel( optionsMgr.GetConstLineWidth()-1 );
}

void CDlgOptionsConst::OnConstDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault constellation options?" ) == IDYES )
	{
		optionsMgr.LoadConstDefaults();

		InitOptions();

		Redraw();
		InvalidateRect( NULL ); // redraw dialog for color preview
	}
	SetFocus();
}


