//===========================================================================
// DlgOptionsSun.cpp
//
// CDlgOptionsSun
//   sun options dialog.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "DlgOptionsSun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsSun::CDlgOptionsSun(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsSun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsSun)
	visible = FALSE;
	sunshine = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsSun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSun)
	DDX_Check(pDX, IDC_SUN_VISIBLE, visible);
	DDX_Check(pDX, IDC_SUN_SHINE, sunshine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSun, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsSun)
	ON_BN_CLICKED(IDC_SUN_VISIBLE, OnSunVisible)
	ON_BN_CLICKED(IDC_SUN_DEFAULTS, OnSunDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsSun message handlers

BOOL CDlgOptionsSun::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitOptions();
	
	return TRUE;
}

void CDlgOptionsSun::InitOptions()
{
	CheckDlgButton( IDC_SUN_VISIBLE, starfield.IsSunVisible() );
	CheckDlgButton( IDC_SUN_SHINE, starfield.IsSunShining() );

	OnSunVisible(); // update state of sunshine control
}

void CDlgOptionsSun::OnSunVisible() 
{
	// Uncheck and disable sunshine control if sun isn't visible
	if( !IsDlgButtonChecked( IDC_SUN_VISIBLE ) )
	{
		CheckDlgButton( IDC_SUN_SHINE, FALSE );
		GetDlgItem(IDC_SUN_SHINE)->EnableWindow( FALSE );
	}
	// Otherwise enable control
	else
		GetDlgItem(IDC_SUN_SHINE)->EnableWindow();
}

void CDlgOptionsSun::OnSunDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault sun options?" ) == IDYES )
	{
		optionsMgr.LoadSunDefaults();

		InitOptions();

		Redraw();
	}
	SetFocus();
}
