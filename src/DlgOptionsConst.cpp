// DlgOptionsConst.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "DlgOptionsConst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsConst dialog


CDlgOptionsConst::CDlgOptionsConst(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsConst::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsConst)
	visible = FALSE;
	labeled = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsConst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsConst)
	DDX_Check(pDX, IDC_CONST_VISIBLE, visible);
	DDX_Check(pDX, IDC_CONST_LABELED, labeled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsConst, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsConst)
	ON_BN_CLICKED(IDC_CONST_NORMCOLOR, OnConstNormColor)
	ON_BN_CLICKED(IDC_CONST_SELCOLOR, OnConstSelColor)
	ON_BN_CLICKED(IDC_CONST_ACTIVECOLOR, OnConstActiveColor)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsConst message handlers


BOOL CDlgOptionsConst::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Initialize controls
	CheckDlgButton( IDC_CONST_VISIBLE, starfield.AreConstsVisible() );
	CheckDlgButton( IDC_CONST_LABELED, starfield.AreConstsLabeled() );

	// Initialize data that are updated realtime (in case of cancel button)
	origNormColor = normColor = optionsMgr.GetConstNormColor();
	origSelColor = selColor = optionsMgr.GetConstSelColor();
	origActiveColor = activeColor = optionsMgr.GetConstActiveColor();

	return TRUE;
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
		InvalidateRect( NULL, FALSE ); // Redraw dialog for color preview
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
		InvalidateRect( NULL, FALSE ); // Redraw dialog for color preview
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
		InvalidateRect( NULL, FALSE ); // Redraw dialog for color preview
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

	else // not interested
		return CDialog::OnCtlColor( pDC, pWnd, nCtlColor );

	// Set DC and brush to paint the color
	pDC->SetBkColor(c);
	colorBrush.DeleteObject();
	colorBrush.CreateSolidBrush(c);

	// Return color preview brush
	return (HBRUSH)colorBrush.GetSafeHandle();
}
