//===========================================================================
// DlgOptionsTerr.cpp
//
// CDlgOptionsTerr
//   terrain options dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgOptionsTerr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsTerr::CDlgOptionsTerr( CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsTerr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsTerr)
	visible = FALSE;
	textured = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsTerr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsTerr)
	DDX_Control(pDX, IDC_TERR_COLOR_PREV, colorPrev);
	DDX_Check(pDX, IDC_TERR_VISIBLE, visible);
	DDX_Check(pDX, IDC_TERR_TEXTURED, textured);
	DDX_Slider(pDX, IDC_TERR_ROUGHNESS, roughness);
	DDX_Control(pDX, IDC_TERR_ROUGHNESS, roughnessSlider);
	DDX_Control(pDX, IDC_TERR_SEASONS, seasonsListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsTerr, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsTerr)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_TERR_NEW, OnTerrNew)
	ON_BN_CLICKED(IDC_TERR_COLOR, OnTerrColor)
	ON_LBN_SELCHANGE(IDC_TERR_SEASONS, OnSeasonChange)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_TERR_TEXTURED, OnTerrTextured)
	ON_BN_CLICKED(IDC_TERR_DEFAULTS, OnTerrDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsTerr message handlers

BOOL CDlgOptionsTerr::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Initialize slider
	roughnessSlider.SetRange( 0, 40 );
	roughnessSlider.SetTicFreq( 10 );

	// Initialize list box
	seasonsListBox.AddString( "Winter" );
	seasonsListBox.AddString( "Spring" );
	seasonsListBox.AddString( "Summer" );
	seasonsListBox.AddString( "Fall"   );

	InitOptions();

	return TRUE;
}

// Set dialog controls to the current options
void CDlgOptionsTerr::InitOptions()
{
	CheckDlgButton( IDC_TERR_VISIBLE, optionsMgr.IsTerrVisible() );
	CheckDlgButton( IDC_TERR_TEXTURED, optionsMgr.IsTerrTextured() );
	SetDlgItemInt( IDC_TERR_ROUGHNESS, (int)(optionsMgr.GetTerrRoughness()*100) );
	roughnessSlider.SetPos( GetDlgItemInt(IDC_TERR_ROUGHNESS) );
	seasonsListBox.SetCurSel( optionsMgr.GetTerrSeason() );

	// Initialize data that are updated realtime (in case of cancel button)
	origRoughness = roughness = (int)(optionsMgr.GetTerrRoughness()*100);
	origSeason = season = optionsMgr.GetTerrSeason();
	origWinColor = winColor = optionsMgr.GetTerrWinColor();
	origSprColor = sprColor = optionsMgr.GetTerrSprColor();
	origSumColor = sumColor = optionsMgr.GetTerrSumColor();
	origFalColor = falColor = optionsMgr.GetTerrFalColor();

	UpdateRoughnessTxt();
	OnTerrTextured();
}

void CDlgOptionsTerr::OnTerrDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault terrain options?" ) == IDYES )
	{
		optionsMgr.LoadTerrDefaults();
		InitOptions();

		Redraw();
		InvalidateRect( NULL ); // redraw dialog for color preview
	}
	SetFocus();
}

void CDlgOptionsTerr::UpdateRoughnessTxt()
{
		CString s;
		// Update roughness text
		if( roughness < 10 )
			s = "Plains";
		else if( roughness < 20 )
			s = "Hills";
		else
			s = "Mountains";
		SetDlgItemText( IDC_TERR_ROUGHNESS_TXT, s );
}

void CDlgOptionsTerr::OnTerrNew() 
{
	terrain.New();

	starfield.SetModified();
	Redraw();
}

void CDlgOptionsTerr::OnSeasonChange() 
{
	season = (season_e)seasonsListBox.GetCurSel();

	optionsMgr.SetTerrSeason( season );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsTerr::OnTerrTextured() 
{
	if( IsDlgButtonChecked(IDC_TERR_TEXTURED) )
		GetDlgItem(IDC_TERR_COLOR)->EnableWindow( FALSE );
	else
		GetDlgItem(IDC_TERR_COLOR)->EnableWindow();

	InvalidateRect( NULL ); // Redraw dialog for color preview
}

// User is or is about to move slider
void CDlgOptionsTerr::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Check if changed
	if( roughness != roughnessSlider.GetPos() )
	{
		roughness = roughnessSlider.GetPos();
		optionsMgr.SetTerrRoughness( roughness / 100.0f );

		// Pick terrain with specified roughness without generating new seed
		terrain.MakeTerrain();

		UpdateRoughnessTxt();
		Redraw();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgOptionsTerr::OnTerrColor() 
{
	CColorDialog dialog;

	color_s color = optionsMgr.GetTerrColor();

	dialog.m_cc.Flags = CC_FULLOPEN | CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( color.r * 255, color.g * 255, color.b * 255 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF c = dialog.GetColor();

		color.r = (float) GetRValue(c) / 255;
		color.g = (float) GetGValue(c) / 255;
		color.b = (float) GetBValue(c) / 255;
	
		optionsMgr.SetTerrColor( color );

		Redraw();
		InvalidateRect( NULL ); // Redraw dialog for color preview
	}
}

// Overridden for color previews
HBRUSH CDlgOptionsTerr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// Call parent if not color preview control or if button is disabled
	if( pWnd->GetDlgCtrlID() != IDC_TERR_COLOR_PREV ||
		!GetDlgItem(IDC_TERR_COLOR)->IsWindowEnabled() )
		return CDialog::OnCtlColor( pDC, pWnd, nCtlColor);

	color_s color = optionsMgr.GetTerrColor();

	COLORREF c = RGB( color.r*255, color.g*255, color.b*255 );

	// Set DC and brush to paint the color
	pDC->SetBkColor(c);
	colorBrush.DeleteObject();
	colorBrush.CreateSolidBrush(c);

	// Return color preview brush
	return (HBRUSH)colorBrush.GetSafeHandle();
}


