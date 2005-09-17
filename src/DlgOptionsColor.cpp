//===========================================================================
// DlgOptionsColor.cpp
//
// CDlgOptionsColor
//   color options dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgOptionsColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsColor::CDlgOptionsColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsColor)
	//}}AFX_DATA_INIT
}


void CDlgOptionsColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsColor)
	DDX_Check(pDX, IDC_COLOR_STARCOLORED, starColored);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsColor, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsColor)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_COLOR_CONSTLABELS, OnColorConstLabels)
	ON_BN_CLICKED(IDC_COLOR_CONSTSELLABELS, OnColorConstSelLabels)
	ON_BN_CLICKED(IDC_COLOR_CONSTNORM, OnColorConstNorm)
	ON_BN_CLICKED(IDC_COLOR_CONSTSEL, OnColorConstSel)
	ON_BN_CLICKED(IDC_COLOR_CONSTACTIVE, OnColorConstActive)
	ON_BN_CLICKED(IDC_COLOR_STARLABELS, OnColorStarLabels)
	ON_BN_CLICKED(IDC_COLOR_STARCONST, OnColorStarConst)
	ON_BN_CLICKED(IDC_COLOR_DIRLABELS, OnColorDirLabels)
	ON_BN_CLICKED(IDC_COLOR_DEFAULTS, OnColorDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsColor message handlers

BOOL CDlgOptionsColor::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitOptions();

	return TRUE;
}

void CDlgOptionsColor::InitOptions()
{
	CheckDlgButton( IDC_COLOR_STARCOLORED, optionsMgr.AreStarsColored() );

	// Initialize data that are updated realtime (in case of cancel button)
	origConstLabels = constLabels = optionsMgr.GetTextConstColor();
	origConstSelLabels = constSelLabels = optionsMgr.GetTextConstSelColor();
	origConstNorm = constNorm = optionsMgr.GetConstNormColor();
	origConstSel = constSel = optionsMgr.GetConstSelColor();
	origConstActive = constActive = optionsMgr.GetConstActiveColor();
	origStarLabels = starLabels = optionsMgr.GetTextStarColor();
	origConstStar = constStar = optionsMgr.GetConstStarColor();
	origDirLabels = dirLabels = optionsMgr.GetTextDirColor();
}

void CDlgOptionsColor::OnColorDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault color options?" ) == IDYES )
	{
		optionsMgr.LoadColorDefaults();

		InitOptions();

		Redraw();
		InvalidateRect( NULL ); // redraw dialog for color preview
	}
	SetFocus();
}


color_s CDlgOptionsColor::SelectColor( color_s& c )
{
	CColorDialog dialog;

	dialog.m_cc.Flags = CC_FULLOPEN | CC_RGBINIT | CC_ENABLEHOOK;
	dialog.m_cc.rgbResult = RGB( c.r * 255, c.g * 255, c.b * 255 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF cr = dialog.GetColor();

		c.r = (float) GetRValue(cr) / 255;
		c.g = (float) GetGValue(cr) / 255;
		c.b = (float) GetBValue(cr) / 255;
	}
	return c;
}

void CDlgOptionsColor::OnColorConstLabels()
{
	optionsMgr.SetTextConstColor( SelectColor( constLabels ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorConstSelLabels()
{
	optionsMgr.SetTextConstSelColor( SelectColor( constSelLabels ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorConstNorm()
{
	optionsMgr.SetConstNormColor( SelectColor( constNorm ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorConstSel()
{
	optionsMgr.SetConstSelColor( SelectColor( constSel ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorConstActive()
{
	optionsMgr.SetConstActiveColor( SelectColor( constActive ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorStarLabels()
{
	optionsMgr.SetTextStarColor( SelectColor( starLabels ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorStarConst()
{
	optionsMgr.SetConstStarColor( SelectColor( constStar ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsColor::OnColorDirLabels()
{
	optionsMgr.SetTextDirColor( SelectColor( dirLabels ) );

	Redraw();
	InvalidateRect( NULL ); // Redraw dialog for color preview
}

// Overridden for color previews
HBRUSH CDlgOptionsColor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// Set color if we need to
	COLORREF c;

	if( pWnd->GetDlgCtrlID() == IDC_COLOR_CONSTLABELS_PREV )
		c = RGB( constLabels.r * 255, constLabels.g * 255, constLabels.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_CONSTSELLABELS_PREV )
		c = RGB( constSelLabels.r * 255, constSelLabels.g * 255, constSelLabels.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_CONSTNORM_PREV )
		c = RGB( constNorm.r * 255, constNorm.g * 255, constNorm.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_CONSTSEL_PREV )
		c = RGB( constSel.r * 255, constSel.g * 255, constSel.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_CONSTACTIVE_PREV )
		c = RGB( constActive.r * 255, constActive.g * 255, constActive.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_STARLABELS_PREV )
		c = RGB( starLabels.r * 255, starLabels.g * 255, starLabels.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_CONSTSTAR_PREV )
		c = RGB( constStar.r * 255, constStar.g * 255, constStar.b * 255 );
	else if( pWnd->GetDlgCtrlID() == IDC_COLOR_DIRLABELS_PREV )
		c = RGB( dirLabels.r * 255, dirLabels.g * 255, dirLabels.b * 255 );

	else // not interested
		return CDialog::OnCtlColor( pDC, pWnd, nCtlColor );

	// Set DC and brush to paint the color
	pDC->SetBkColor(c);
	colorBrush.DeleteObject();
	colorBrush.CreateSolidBrush(c);

	// Return color preview brush
	return (HBRUSH)colorBrush.GetSafeHandle();
}

