// TerrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "TerrainDlg.h"
#include "Terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTerrainDlg dialog


CTerrainDlg::CTerrainDlg( int roughness, CWnd* pParent /*=NULL*/)
	: CDialog(CTerrainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTerrainDlg)
	m_Roughness = roughness;
	m_RoughnessTxt = _T("");
	//}}AFX_DATA_INIT

	lastRoughness = m_Roughness;
	needsUpdate = false;
}

CTerrain* CTerrainDlg::GetTerrain() const
{
	return ((CMainFrame*)GetParent())->GetTerrain();

}

void CTerrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTerrainDlg)
	DDX_Control(pDX, IDC_ROUGHNESS, m_RoughnessSlider);
	DDX_Slider(pDX, IDC_ROUGHNESS, m_Roughness);
	DDX_Text(pDX, IDC_ROUGHNESS_TXT, m_RoughnessTxt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTerrainDlg, CDialog)
	//{{AFX_MSG_MAP(CTerrainDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_NEW, OnNewTerrain)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTerrainDlg message handlers

BOOL CTerrainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_RoughnessSlider.SetRange( 1, 10 );
	m_RoughnessSlider.SetTicFreq( 1 );
	m_RoughnessSlider.SetPos( m_Roughness );

	return TRUE;
}

void CTerrainDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Roughness = m_RoughnessSlider.GetPos();
	if( m_Roughness != lastRoughness )
	{
		needsUpdate = true;
		lastRoughness = m_Roughness;
	}

	CString r;
	if( m_Roughness < 3 )
	{
		r = "Smooth";
	}
	else if( m_Roughness < 7 )
	{
		r = "Medium";
	}
	else
	{
		r = "Rough";
	}

///	MessageBox(r);
	m_RoughnessTxt = _T( "CLAY" );

	UpdateData();
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTerrainDlg::OnNewTerrain() 
{
	((CMainFrame*)GetParent())->GetView()->NewTerrain( (float)m_Roughness / 10 );
	
	needsUpdate = false;
}

void CTerrainDlg::OnColor() 
{
	CColorDialog dialog;

	CColor color = GetTerrain()->GetColor();

	dialog.m_cc.Flags = CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( color.r, color.g, color.b );

	dialog.DoModal();

	///
	
}
