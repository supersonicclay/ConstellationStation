// ConstBar.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "ConstBar.h"

#include "ConStationFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ConstList dimensions
#define CONSTLIST_INDEX		0
#define CONSTLIST_WIDTH		200
#define CONSTLIST_HEIGHT	100

/////////////////////////////////////////////////////////////////////////////
// CConstBar

CConstBar::CConstBar()
{
}

CConstBar::~CConstBar()
{
}

BOOL CConstBar::Init(CWnd *pParentWnd)
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

BOOL CConstBar::InitList()
{
	CRect rect( -CONSTLIST_WIDTH, -CONSTLIST_HEIGHT, 0, 0 );

	SetButtonInfo( CONSTLIST_INDEX, ID_CONST_LIST, TBBS_SEPARATOR, CONSTLIST_WIDTH );

	if ( !m_List.Create( WS_CHILD | CBS_DROPDOWNLIST | CBS_SORT |
		CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, rect, this,
		ID_CONST_LIST ) )
	{
		return FALSE;
	}

	if ( m_List.m_hWnd != NULL )
	{
		GetItemRect( CONSTLIST_INDEX, rect );

		m_List.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
			SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
		m_List.ShowWindow( SW_SHOW );
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP( CConstBar, CToolBar )
	//{{AFX_MSG_MAP(CConstBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConstBar message handlers

void CConstBar::AddConst( CString &str )
{
	// Add string to list and select
	m_List.SetCurSel( m_List.AddString( str ) );
}

void CConstBar::DeleteConst()
{
	int sel = m_List.GetCurSel();

	if( m_List.DeleteString( sel ) == CB_ERR)
		MessageBox("Can't Delete Constellation");

	// Select previous constellation
	if( sel-1 < 0 )
		m_List.SetCurSel(0);
	else
		m_List.SetCurSel( sel-1 );
}

void CConstBar::UpdateList( CString* names, int numConstellations, int numCurrent )
{
	// Clear the list
	m_List.ResetContent();

	// Cycle through the names
	for( int i=0; i<numConstellations; i++ )
	{
		// If this is the current constellation select it after adding it
		if( i==numCurrent )
			m_List.SetCurSel( m_List.AddString( names[i] ) );
		else	// Just add it
			m_List.AddString( names[i] );
	}
}

void CConstBar::ClearList()
{
	m_List.ResetContent();
}

CString CConstBar::GetCurConst() const
{
	CString str;
	m_List.GetLBText( m_List.GetCurSel(), str );
	return str;
}

