//===========================================================================
// DlgOptionsStar.cpp
//
// CDlgOptionsStar
//   star options dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgOptionsStar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsStar::CDlgOptionsStar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsStar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsStar)
	visible = FALSE;
	labeled = FALSE;
	textured = FALSE;
	colored = FALSE;
	limMagX10 = 0;
	size = 0;
	sContrast = 0;
	cContrast = 0;
	daylight = FALSE;
	//}}AFX_DATA_INIT

	origLimMagX10 = 0;
}


void CDlgOptionsStar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsStar)
	DDX_Check(pDX, IDC_STARS_VISIBLE, visible);
	DDX_Check(pDX, IDC_STARS_LABELED, labeled);
	DDX_Check(pDX, IDC_STARS_TEXTURED, textured);
	DDX_Check(pDX, IDC_STARS_COLORED, colored);
	DDX_Slider(pDX, IDC_STARS_LIMMAG, limMagX10);
	DDX_Slider(pDX, IDC_STARS_SIZE, size);
	DDX_Slider(pDX, IDC_STARS_SCONTRAST, sContrast);
	DDX_Slider(pDX, IDC_STARS_CCONTRAST, cContrast);
	DDX_Control(pDX, IDC_STARS_SIZE, sizeSlider);
	DDX_Control(pDX, IDC_STARS_SCONTRAST, sContrastSlider);
	DDX_Control(pDX, IDC_STARS_CCONTRAST, cContrastSlider);
	DDX_Control(pDX, IDC_STARS_LIMMAG, limMagSlider);
	DDX_Check(pDX, IDC_STARS_DAYLIGHT, daylight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsStar, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsStar)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_STARS_DEFAULTS, OnStarsDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsStar message handlers

BOOL CDlgOptionsStar::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Initialize sliders
	sizeSlider.SetRange( 0, 100 );
	sContrastSlider.SetRange( 0, 100 );
	cContrastSlider.SetRange( 0, 100 );
	limMagSlider.SetRange( 30, 90 );
	limMagSlider.SetTicFreq( 10 );

	InitOptions();

	return TRUE;
}

void CDlgOptionsStar::InitOptions()
{
	CheckDlgButton( IDC_STARS_VISIBLE, starfield.AreStarsVisible() );
	CheckDlgButton( IDC_STARS_DAYLIGHT, starfield.AreStarsDaylight() );
	CheckDlgButton( IDC_STARS_LABELED, starfield.AreStarsLabeled() );
	CheckDlgButton( IDC_STARS_TEXTURED, optionsMgr.AreStarsTextured() );
	CheckDlgButton( IDC_STARS_COLORED, optionsMgr.AreStarsColored() );
	SetDlgItemInt( IDC_STARS_SIZE, optionsMgr.GetStarsSize() );
	SetDlgItemInt( IDC_STARS_SCONTRAST, optionsMgr.GetStarsSContrast() );
	SetDlgItemInt( IDC_STARS_CCONTRAST, optionsMgr.GetStarsCContrast() );
	SetDlgItemInt( IDC_STARS_LIMMAG, optionsMgr.GetStarsLimMagX10() );

	sizeSlider.SetPos( GetDlgItemInt(IDC_STARS_SIZE) );
	sContrastSlider.SetPos( GetDlgItemInt(IDC_STARS_SCONTRAST) );
	cContrastSlider.SetPos( GetDlgItemInt(IDC_STARS_CCONTRAST) );
	limMagSlider.SetPos( GetDlgItemInt(IDC_STARS_LIMMAG) );

	// Initialize data that are updated realtime (in case of cancel button)
	origLimMagX10 = limMagX10 = optionsMgr.GetStarsLimMagX10();

	UpdateLimMagTxt();
}

void CDlgOptionsStar::OnStarsDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault star options?" ) == IDYES )
	{
		optionsMgr.LoadStarDefaults();
		InitOptions();
		
		starfield.CountStars();
		Redraw();
	}
	SetFocus();
}

void CDlgOptionsStar::UpdateLimMagTxt()
{
	char buffer[10];
	itoa( limMagSlider.GetPos(), buffer, 10 );

	// Divide the 2 digit number string by 10
	buffer[3] = '\0';
	buffer[2] = buffer[1];
	buffer[1] = '.';

	SetDlgItemText( IDC_STARS_LIMMAG_TXT, buffer );
}

// User is or is about to move slider
void CDlgOptionsStar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Update limiting magnitude
	if( limMagX10 != limMagSlider.GetPos() )
	{
		limMagX10 = limMagSlider.GetPos();
		optionsMgr.SetStarsLimMagX10( limMagX10 );
		starfield.CountStars();
		starfMgr.UpdateStarsAppearance();
		Redraw();
	}

	UpdateLimMagTxt();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}



