//===========================================================================
// BarConst.cpp
//
// CBarConst
//   constellation toolbar.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "BarConst.h"

#include "CSFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP( CBarConst, CToolBar )
	//{{AFX_MSG_MAP(CBarConst)
	ON_CBN_SELCHANGE(ID_CONST_LIST, OnConstSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Constellation list control dimensions
#define CONSTLIST_INDEX		0
#define CONSTLIST_WIDTH		200
#define CONSTLIST_HEIGHT	200


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CBarConst::CBarConst()
{
}

CBarConst::~CBarConst()
{
}

BOOL CBarConst::Init(CWnd *pParentWnd)
{
	DWORD dwStyle = WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!CreateEx(pParentWnd, TBSTYLE_FLAT, dwStyle) ||
		!LoadToolBar(IDR_CONSTELLATION))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	if (!InitList())
		return FALSE;

	return TRUE;
}

BOOL CBarConst::InitList()
{
	CRect rect( -CONSTLIST_WIDTH, -CONSTLIST_HEIGHT, 0, 0 );

	SetButtonInfo( CONSTLIST_INDEX, ID_CONST_LIST, TBBS_SEPARATOR, CONSTLIST_WIDTH );

	if ( !constList.Create( WS_CHILD | CBS_DROPDOWNLIST | CBS_SORT |
		CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, rect, this,
		ID_CONST_LIST ) )
	{
		return FALSE;
	}

	if ( constList.m_hWnd != NULL )
	{
		GetItemRect( CONSTLIST_INDEX, rect );

		constList.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
			SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
		constList.ShowWindow( SW_SHOW );
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CBarConst message handlers

void CBarConst::OnConstSelChange()
{
	if (constList.GetCurSel() != CB_ERR)
	{
		starfield.SelectConst( GetCurConst() );
		Redraw();
	}
}

void CBarConst::AddConst( CString &str )
{
	// Add string to constList and select
	constList.SetCurSel( constList.AddString( str ) );
}

void CBarConst::DeleteConst()
{
	int sel = constList.GetCurSel();

	if( constList.DeleteString( sel ) == CB_ERR)
	{
		CSDebug( "Can't Delete Constellation", "CBarConst::DeleteConst" );
		PostQuitMessage(0);
		return;
	}

	// Select previous constellation
	if( sel-1 < 0 )
		constList.SetCurSel(0);
	else
		constList.SetCurSel( sel-1 );
}

void CBarConst::UpdateList()
{
	// Clear the constList
	constList.ResetContent();

	// Cycle through the names
	for( int i=0; i<starfield.GetConstCount(); i++ )
	{
		// If this is the current constellation select it after adding it
		if( i == starfield.GetCurConstNum() )
			constList.SetCurSel( constList.AddString
				( starfield.GetConst(i)->GetName() ) );
		else	// Just add it
			constList.AddString( starfield.GetConst(i)->GetName() );
	}
}

CString CBarConst::GetCurConst() const
{
	CString str;
	constList.GetLBText( constList.GetCurSel(), str );
	return str;
}

