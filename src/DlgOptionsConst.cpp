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
	starsColored = FALSE;
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
	DDX_Check(pDX, IDC_CONST_STARSCOLORED, starsColored);
	DDX_CBIndex(pDX, IDC_CONST_LINEWIDTH, lineWidth);
	DDX_Check(pDX, IDC_CONST_DAYLIGHT, daylight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsConst, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsConst)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CONST_NORMCOLOR, OnConstNormColor)
	ON_BN_CLICKED(IDC_CONST_SELCOLOR, OnConstSelColor)
	ON_BN_CLICKED(IDC_CONST_ACTIVECOLOR, OnConstActiveColor)
	ON_BN_CLICKED(IDC_CONST_STARCOLOR, OnConstStarColor)
	ON_BN_CLICKED(IDC_CONST_STARSCOLORED, OnConstStarsColored)
	ON_BN_CLICKED(IDC_CONST_DEFAULTS, OnConstDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsConst message handlers

BOOL CDlgOptionsConst::OnInitDialog() 
{
	CDialog::OnInitDialog();

	/// Set lineWidthControl height taller here

	InitOptions();

	return TRUE;
}

void CDlgOptionsConst::InitOptions()
{
	CheckDlgButton( IDC_CONST_VISIBLE, starfield.AreConstsVisible() );
	CheckDlgButton( IDC_CONST_DAYLIGHT, starfield.AreConstsDaylight() );
	CheckDlgButton( IDC_CONST_LABELED, starfield.AreConstsLabeled() );
	CheckDlgButton( IDC_CONST_STARSCOLORED, optionsMgr.AreConstStarsColored() );
	lineWidthControl.SetCurSel( optionsMgr.GetConstLineWidth()-1 );

	// Initialize data that are updated realtime (in case of cancel button)
	origNormColor = normColor = optionsMgr.GetConstNormColor();
	origSelColor = selColor = optionsMgr.GetConstSelColor();
	origActiveColor = activeColor = optionsMgr.GetConstActiveColor();
	origStarColor = starColor = optionsMgr.GetConstStarColor();

	OnConstStarsColored();	// Update Star Color button
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

void CDlgOptionsConst::OnConstStarsColored()
{
	if( IsDlgButtonChecked(IDC_CONST_STARSCOLORED) )
		GetDlgItem(IDC_CONST_STARCOLOR)->EnableWindow();
	else
		GetDlgItem(IDC_CONST_STARCOLOR)->EnableWindow( FALSE );

	InvalidateRect( NULL ); // Redraw dialog for color preview
}

void CDlgOptionsConst::OnConstNormColor() 
{
	CColorDialog dialog;

	dialog.m_cc.Flags = CC_FULLOPEN | CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( normColor.r * 255, normColor.g * 255, normColor.b * 255 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF c = dialog.GetColor();

		normColor.r = (float) GetRValue(c) / 255;
		normColor.g = (float) GetGValue(c) / 255;
		normColor.b = (float) GetBValue(c) / 255;

		optionsMgr.SetConstNormColor( normColor );

		Redraw();
		InvalidateRect( NULL ); // Redraw dialog for color preview
	}
}

void CDlgOptionsConst::OnConstSelColor() 
{
	CColorDialog dialog;

	dialog.m_cc.Flags = CC_FULLOPEN | CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( selColor.r * 255, selColor.g * 255, selColor.b * 255 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF c = dialog.GetColor();

		selColor.r = (float) GetRValue(c) / 255;
		selColor.g = (float) GetGValue(c) / 255;
		selColor.b = (float) GetBValue(c) / 255;

		optionsMgr.SetConstSelColor( selColor );

		Redraw();
		InvalidateRect( NULL ); // Redraw dialog for color preview
	}
}

void CDlgOptionsConst::OnConstActiveColor() 
{
	CColorDialog dialog;

	dialog.m_cc.Flags = CC_FULLOPEN | CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( activeColor.r * 255, activeColor.g * 255, activeColor.b * 255 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF c = dialog.GetColor();

		activeColor.r = (float) GetRValue(c) / 255;
		activeColor.g = (float) GetGValue(c) / 255;
		activeColor.b = (float) GetBValue(c) / 255;

		optionsMgr.SetConstActiveColor( activeColor );

		Redraw();
		InvalidateRect( NULL ); // Redraw dialog for color preview
	}
}

void CDlgOptionsConst::OnConstStarColor() 
{
	CColorDialog dialog;

	dialog.m_cc.Flags = CC_FULLOPEN | CC_ENABLEHOOK | CC_RGBINIT;
	dialog.m_cc.rgbResult = RGB( starColor.r * 255, starColor.g * 255, starColor.b * 255 );

	if( dialog.DoModal() == IDOK )
	{
		COLORREF c = dialog.GetColor();

		starColor.r = (float) GetRValue(c) / 255;
		starColor.g = (float) GetGValue(c) / 255;
		starColor.b = (float) GetBValue(c) / 255;

		optionsMgr.SetConstStarColor( starColor );

		Redraw();
		InvalidateRect( NULL ); // Redraw dialog for color preview
	}
}

// Overridden for color previews
HBRUSH CDlgOptionsConst::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// Set color if we need to
	COLORREF c;
	if( pWnd->GetDlgCtrlID() == IDC_CONST_NORMCOLOR_PREV )
		c = RGB( normColor.r * 255, normColor.g * 255, normColor.b * 255 );

	else if( pWnd->GetDlgCtrlID() == IDC_CONST_SELCOLOR_PREV )
		c = RGB( selColor.r * 255, selColor.g * 255, selColor.b * 255 );

	else if( pWnd->GetDlgCtrlID() == IDC_CONST_ACTIVECOLOR_PREV )
		c = RGB( activeColor.r * 255, activeColor.g * 255, activeColor.b * 255 );

	else if( pWnd->GetDlgCtrlID() == IDC_CONST_STARCOLOR_PREV )
	{
		if( !GetDlgItem(IDC_CONST_STARCOLOR)->IsWindowEnabled() ) // not interested
			return CDialog::OnCtlColor( pDC, pWnd, nCtlColor );
		else
			c = RGB( starColor.r * 255, starColor.g * 255, starColor.b * 255 );
	}
	else // not interested
		return CDialog::OnCtlColor( pDC, pWnd, nCtlColor );

	// Set DC and brush to paint the color
	pDC->SetBkColor(c);
	colorBrush.DeleteObject();
	colorBrush.CreateSolidBrush(c);

	// Return color preview brush
	return (HBRUSH)colorBrush.GetSafeHandle();
}

