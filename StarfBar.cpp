// StarfBar.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "StarfBar.h"

#include "ConStationFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Time and Date dimensions
#define STARFDATE_INDEX		11
#define STARFDATE_WIDTH		100
#define STARFDATE_HEIGHT	25
#define STARFTIME_INDEX		14
#define STARFTIME_WIDTH		100
#define STARFTIME_HEIGHT	25
#define STARFSPEED_INDEX	15
#define STARFSPEED_WIDTH	100
#define STARFSPEED_HEIGHT	100


/////////////////////////////////////////////////////////////////////////////
// CStarfBar

CStarfBar::CStarfBar()
{
}

CStarfBar::~CStarfBar()
{
}

BOOL CStarfBar::Init(CWnd *pParentWnd)
{
	DWORD dwStyle = WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!CreateEx(pParentWnd, TBSTYLE_FLAT, dwStyle) ||
		!LoadToolBar(IDR_STARFIELD))
	{
		TRACE0("Failed to create starfield toolbar\n");
		return FALSE;
	}

	if( !InitDateCtrl() || !InitTimeCtrl() || !InitSpeedCtrl() )
	{
		MessageBox("Error initializing starfield toolbar controls", "ERROR" );
		return FALSE;
	}

	// Timer ticks every second
	SetTimer( 1, 1000, NULL );

	return TRUE;
}

BOOL CStarfBar::InitDateCtrl()
{
	// Place on toolbar
	SetButtonInfo( STARFDATE_INDEX, ID_STARF_DATE, TBBS_SEPARATOR, STARFDATE_WIDTH );

	CRect rect;
	GetItemRect( STARFDATE_INDEX, rect );

	if ( !m_Date.Create( WS_CHILD | DTS_UPDOWN, rect, this,
		ID_STARF_DATE ) )
	{
		return FALSE;
	}

	if ( m_Date.m_hWnd == NULL )
		return FALSE;

	m_Date.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
 		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	m_Date.ShowWindow( SW_SHOW );

	// Set range
	COleDateTime minDate(1601, 1, 1, 0, 0, 0);
	COleDateTime maxDate(9999, 12, 31, 0, 0, 0);
	if( !m_Date.SetRange( &minDate, &maxDate ) )
	{
		MessageBox("Can't set the date range");
		return FALSE;
	}

	return TRUE;
}

BOOL CStarfBar::InitTimeCtrl()
{
	// Place on toolbar
	SetButtonInfo( STARFTIME_INDEX, ID_STARF_TIME, TBBS_SEPARATOR, STARFTIME_WIDTH );

	CRect rect;
	GetItemRect( STARFTIME_INDEX, rect );

	if ( !m_Time.Create( WS_CHILD | DTS_TIMEFORMAT, rect, this,
		ID_STARF_TIME ) )
	{
		return FALSE;
	}

	if ( m_Time.m_hWnd == NULL )
		return FALSE;

	m_Time.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	m_Time.ShowWindow( SW_SHOW );

	// Set range
	COleDateTime minTime(1601, 1, 1, 0, 0, 0);
	COleDateTime maxTime(9999, 12, 31, 0, 0, 0);
	if( !m_Time.SetRange( &minTime, &maxTime ) )
	{
		MessageBox("Can't set the time range");
		return FALSE;
	}

	return TRUE;
}

BOOL CStarfBar::InitSpeedCtrl()
{
	CRect rect( -STARFSPEED_WIDTH, -STARFSPEED_HEIGHT, 0, 0 );

	SetButtonInfo( STARFSPEED_INDEX, ID_STARF_SPEED, TBBS_SEPARATOR, STARFSPEED_WIDTH );

	if ( !m_Speed.Create( WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rect, this,
		ID_CONST_LIST ) )
	{
		return FALSE;
	}

	if ( m_Speed.m_hWnd == NULL )
		return FALSE;

	GetItemRect( STARFSPEED_INDEX, rect );
	m_Speed.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	m_Speed.ShowWindow( SW_SHOW );

	m_Speed.SetCurSel( m_Speed.AddString("Now") );
	m_Speed.AddString("1X");
	m_Speed.AddString("10X");
	m_Speed.AddString("100X");
	m_Speed.AddString("1000X");

	return TRUE;
}


BEGIN_MESSAGE_MAP( CStarfBar, CToolBar )
	//{{AFX_MSG_MAP(CStarfBar)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStarfBar message handlers


void CStarfBar::OnTimer(UINT nIDEvent) 
{
	CToolBar ::OnTimer(nIDEvent);

	/// SPEED
	COleDateTime time = COleDateTime::GetCurrentTime();
	m_Time.SetTime(time);
	m_Date.SetTime(time);
}
