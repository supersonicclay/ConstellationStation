//===========================================================================
// DlgOptionsStar.cpp
//
// CDlgOptionsStar
//   star options dialog.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
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
	contrast = 0;
	gamma = 0;
	colored = FALSE;
	textured = FALSE;
	visible = FALSE;
	labeled = FALSE;
	limitingMag = 0;
	//}}AFX_DATA_INIT
}


void CDlgOptionsStar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsStar)
	DDX_Check(pDX, IDC_STARS_VISIBLE, visible);
	DDX_Check(pDX, IDC_STARS_LABELED, labeled);
	DDX_Check(pDX, IDC_STARS_TEXTURED, textured);
	DDX_Check(pDX, IDC_STARS_COLORED, colored);
	DDX_Slider(pDX, IDC_STARS_GAMMA, gamma);
	DDX_Control(pDX, IDC_STARS_GAMMA, gammaSlider);
	DDX_Slider(pDX, IDC_STARS_CONTRAST, contrast);
	DDX_Control(pDX, IDC_STARS_CONTRAST, contrastSlider);
	DDX_Slider(pDX, IDC_STARS_LIMMAG, limitingMag);
	DDX_Control(pDX, IDC_STARS_LIMMAG, limMagSlider);
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

	/// HOW IMPORTANT IS ROUNDOFF ERROR?
	float f = 5.1f;
	float fX10 = f*10;
	int i = fX10;

	// Initialize sliders
	gammaSlider.SetRange( 0, 100 );
	contrastSlider.SetRange( 0, 100 );
	limMagSlider.SetRange( 30, 90 );
	limMagSlider.SetTicFreq( 10 );

	InitOptions();

	return TRUE;
}

void CDlgOptionsStar::InitOptions()
{
	CheckDlgButton( IDC_STARS_VISIBLE, starfield.AreStarsVisible() );
	CheckDlgButton( IDC_STARS_LABELED, starfield.AreStarsLabeled() );
	CheckDlgButton( IDC_STARS_TEXTURED, optionsMgr.AreStarsTextured() );
	CheckDlgButton( IDC_STARS_COLORED, optionsMgr.AreStarsColored() );
	SetDlgItemInt( IDC_STARS_GAMMA, optionsMgr.GetStarsGamma() );
	SetDlgItemInt( IDC_STARS_CONTRAST, optionsMgr.GetStarsContrast() );
	SetDlgItemInt( IDC_STARS_LIMMAG, (int)(starfield.GetLimitingMag()*10) );

	gammaSlider.SetPos( GetDlgItemInt(IDC_STARS_GAMMA) );
	contrastSlider.SetPos( GetDlgItemInt(IDC_STARS_CONTRAST) );
	limMagSlider.SetPos( GetDlgItemInt(IDC_STARS_LIMMAG) );

	// Initialize data that are updated realtime (in case of cancel button)
	origGamma = gamma = optionsMgr.GetStarsGamma();
	origContrast = contrast = optionsMgr.GetStarsContrast();

	UpdateLimMagTxt();
}

void CDlgOptionsStar::OnStarsDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault star options?" ) == IDYES )
	{
		optionsMgr.LoadStarDefaults();
		InitOptions();

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
	// Update brightness
	if( gamma != gammaSlider.GetPos() )
	{
		gamma = gammaSlider.GetPos();
		optionsMgr.SetStarsGamma( gammaSlider.GetPos() );
		Redraw();
	}

	// Update contrast
	if( contrast != contrastSlider.GetPos() )
	{
		contrast = contrastSlider.GetPos();
		optionsMgr.SetStarsContrast( contrastSlider.GetPos() );
		Redraw();
	}

	UpdateLimMagTxt();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

