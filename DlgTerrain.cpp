// CDlgTerrain.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "DlgTerrain.h"
#include "Terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTerrain dialog


CDlgTerrain::CDlgTerrain( float roughness_, color_s color_, CWnd* pParent /*=NULL*/ )
	: CDialog(CDlgTerrain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTerrain)
	//}}AFX_DATA_INIT
	roughness = (int) (roughness_ * 10);
	color = color_;

	lastRoughness = roughness;
	needsUpdate = false;
}

void CDlgTerrain::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTerrain)
	DDX_Control(pDX, IDC_ROUGHNESS, roughnessSlider);
	DDX_Slider(pDX, IDC_ROUGHNESS, roughness);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTerrain, CDialog)
	//{{AFX_MSG_MAP(CDlgTerrain)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_NEW, OnNewTerrain)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgTerrain message handlers

BOOL CDlgTerrain::OnInitDialog() 
{
	CDialog::OnInitDialog();

	roughnessSlider.SetRange( 0, 5 );
	roughnessSlider.SetTicFreq( 1 );
	roughnessSlider.SetPos( roughness );

	return TRUE;
}

void CDlgTerrain::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	roughness = roughnessSlider.GetPos();
	if( roughness != lastRoughness )
	{
		terrain->SetRoughness( (float)roughness/10 );
		needsUpdate = true;
		lastRoughness = roughness;
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgTerrain::OnNewTerrain() 
{
	terrain->MakeTerrain();

	RedrawView();
	
	needsUpdate = false;
}

void CDlgTerrain::OnColor() 
{
	CColorDialog dialog;

	dialog.m_cc.Flags = CC_FULLOPEN | CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( color.r * 256, color.g * 256, color.b * 256 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF c = dialog.GetColor();

		color.r = (float) GetRValue(c) / 256;
		color.g = (float) GetGValue(c) / 256;
		color.b = (float) GetBValue(c) / 256;
	
		terrain->SetColor( color );

		RedrawView();
	}
}

