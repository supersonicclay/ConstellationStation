// DlgOptionsTerr.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "DlgOptionsTerr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsTerr dialog


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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsTerr message handlers

BOOL CDlgOptionsTerr::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Initialize controls
	CheckDlgButton( IDC_TERR_VISIBLE, terrain.IsVisible() );
	CheckDlgButton( IDC_TERR_TEXTURED, optionsMgr.IsTerrTextured() );
	SetDlgItemInt( IDC_TERR_ROUGHNESS, (int)(optionsMgr.GetTerrRoughness()*100) );
	if( IsDlgButtonChecked(IDC_TERR_TEXTURED) )
		GetDlgItem(IDC_TERR_COLOR)->EnableWindow( FALSE );

	// Initialize slider
	roughnessSlider.SetRange( 0, 30 );
	roughnessSlider.SetTicFreq( 10 );
	roughnessSlider.SetPos( GetDlgItemInt(IDC_TERR_ROUGHNESS) );

	// Initialize list box
	seasonsListBox.AddString( "Winter" );
	seasonsListBox.AddString( "Spring" );
	seasonsListBox.AddString( "Summer" );
	seasonsListBox.AddString( "Fall"   );
	seasonsListBox.SetCurSel( optionsMgr.GetTerrSeason() );

	// Initialize data that are updated realtime (in case of cancel button)
	origRoughness = roughness = (int)(optionsMgr.GetTerrRoughness()*100);
	origSeason = season = optionsMgr.GetTerrSeason();
	origColor = color = optionsMgr.GetTerrColor();

	UpdateRoughnessTxt();

	return TRUE;
}

void CDlgOptionsTerr::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Check if changed
	if( roughness != roughnessSlider.GetPos() )
	{
		needsUpdate = TRUE;
		roughness = roughnessSlider.GetPos();
		optionsMgr.SetTerrRoughness( roughness / 100.0f );

		terrain.New();

		UpdateRoughnessTxt();

		Redraw();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
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
	optionsMgr.SetTerrTextured( GetDlgItemInt(IDC_TERR_TEXTURED) );

	terrain.New();

	starfield.SetModified();
	Redraw();

	needsUpdate = FALSE;
}

void CDlgOptionsTerr::OnSeasonChange() 
{
	season = (season_e)seasonsListBox.GetCurSel();
}

void CDlgOptionsTerr::OnTerrColor() 
{
	CColorDialog dialog;

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
		InvalidateRect( NULL, FALSE ); // Redraw dialog for color preview
	}
}

// Overridden for color previews
HBRUSH CDlgOptionsTerr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// Call parent if not color preview control
	if( pWnd->GetDlgCtrlID() != IDC_TERR_COLOR_PREV )
		return CDialog::OnCtlColor( pDC, pWnd, nCtlColor);

	COLORREF c = RGB( color.r*255, color.g*255, color.b*255 );

	// Set DC and brush to paint the color
	pDC->SetBkColor(c);
	colorBrush.DeleteObject();
	colorBrush.CreateSolidBrush(c);

	// Return color preview brush
	return (HBRUSH)colorBrush.GetSafeHandle();
}


void CDlgOptionsTerr::OnTerrTextured() 
{
	if( IsDlgButtonChecked(IDC_TERR_TEXTURED) )
		GetDlgItem(IDC_TERR_COLOR)->EnableWindow( FALSE );
	else
		GetDlgItem(IDC_TERR_COLOR)->EnableWindow();
}

