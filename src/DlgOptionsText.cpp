//===========================================================================
// DlgOptionsText.cpp
//
// CDlgOptionsText
//   text options dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgOptionsText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsText::CDlgOptionsText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsText)
	//}}AFX_DATA_INIT
}


void CDlgOptionsText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsText)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsText, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsText)
	ON_BN_CLICKED(IDC_TEXT_CONSTFONT, OnTextConstFont)
	ON_BN_CLICKED(IDC_TEXT_STARFONT, OnTextStarFont)
	ON_BN_CLICKED(IDC_TEXT_DIRFONT, OnTextDirFont)
	ON_BN_CLICKED(IDC_TEXT_DEFAULTS, OnTextDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsText message handlers

BOOL CDlgOptionsText::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitOptions();

	return TRUE;
}

void CDlgOptionsText::InitOptions()
{
	// Initialize data that are updated realtime (in case of cancel button)
	origConstFont = constFont = optionsMgr.GetTextConstFont();
	origStarFont = starFont = optionsMgr.GetTextStarFont();
	origDirFont = dirFont = optionsMgr.GetTextDirFont();
}

void CDlgOptionsText::OnTextDefaults() 
{
	if( CSQuestion( GetSafeHwnd(),
		"Are you sure you want to load\ndefault text options?" ) == IDYES )
	{
		optionsMgr.LoadTextDefaults();

		InitOptions();

		Redraw();
		InvalidateRect( NULL ); // redraw dialog for color preview
	}
	SetFocus();
}

BOOL CDlgOptionsText::SelectFont( LOGFONT* f )
{
	CHOOSEFONT cf;
	ZeroMemory( &cf, sizeof(cf) );
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = GetSafeHwnd();
	cf.lpLogFont = f;
	cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;


	return ChooseFont(&cf);
}

void CDlgOptionsText::OnTextConstFont() 
{
	if( SelectFont( &constFont ) )
	{
		optionsMgr.SetTextConstFont( constFont );
		textMgr.BuildFonts();
		Redraw();
	}
}

void CDlgOptionsText::OnTextStarFont() 
{
	if( SelectFont( &starFont ) )
	{
		optionsMgr.SetTextStarFont( starFont );
		textMgr.BuildFonts();
		Redraw();
	}
}

void CDlgOptionsText::OnTextDirFont() 
{
	if( SelectFont( &dirFont ) )
	{
		optionsMgr.SetTextDirFont( dirFont );
		textMgr.BuildFonts();
		Redraw();
	}
}

