//===========================================================================
// BarStarf.cpp
//
// CBarStarf
//   starfield toolbar
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "BarStarf.h"

#include "ConStationFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Time, Date, and Speed dimensions
#define STARFDATE_INDEX		7
#define STARFTIME_INDEX		9
#define STARFSPEED_INDEX	11
#define STARFDATE_WIDTH		100
#define STARFDATE_HEIGHT	25
#define STARFTIME_WIDTH		100
#define STARFTIME_HEIGHT	25
#define STARFSPEED_WIDTH	100
#define STARFSPEED_HEIGHT	100


/////////////////////////////////////////////////////////////////////////////
// CBarStarf

CBarStarf::CBarStarf()
{
}

CBarStarf::~CBarStarf()
{
}

BOOL CBarStarf::Init(CWnd *pParentWnd)
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
		CSError( "Error initializing starfield toolbar controls", "CBarStarf::Init" );
		return FALSE;
	}

	// Timer ticks every second
	SetTimer( 1, 1000, NULL );

	return TRUE;
}

BOOL CBarStarf::InitDateCtrl()
{
	// Place on toolbar
	SetButtonInfo( STARFDATE_INDEX, ID_STARF_DATE, TBBS_SEPARATOR, STARFDATE_WIDTH );

	CRect rect;
	GetItemRect( STARFDATE_INDEX, rect );

	if ( !date.Create( WS_CHILD | DTS_UPDOWN, rect, this,
		ID_STARF_DATE ) )
	{
		return false;
	}

	if ( date.m_hWnd == NULL )
		return false;

	date.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
 		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	date.ShowWindow( SW_SHOW );

	// Set range
	COleDateTime minDate(1601, 1, 1, 0, 0, 0);
	COleDateTime maxDate(9999, 12, 31, 0, 0, 0);
	if( !date.SetRange( &minDate, &maxDate ) )
	{
		CSError( "Can't set the date range", "CBarStarf::InitDateCtrl" );
		return false;
	}

	return true;
}

BOOL CBarStarf::InitTimeCtrl()
{
	// Place on toolbar
	SetButtonInfo( STARFTIME_INDEX, ID_STARF_TIME, TBBS_SEPARATOR, STARFTIME_WIDTH );

	CRect rect;
	GetItemRect( STARFTIME_INDEX, rect );

	if ( !time.Create( WS_CHILD | DTS_TIMEFORMAT, rect, this,
		ID_STARF_TIME ) )
	{
		return false;
	}

	if ( time.m_hWnd == NULL )
		return false;

	time.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	time.ShowWindow( SW_SHOW );

	// Set range
	COleDateTime minTime(1601, 1, 1, 0, 0, 0);
	COleDateTime maxTime(9999, 12, 31, 0, 0, 0);
	if( !time.SetRange( &minTime, &maxTime ) )
	{
		CSError( "Can't set the time range", "CBarStarf::InitTimeCtrl" );
		return false;
	}

	return true;
}

BOOL CBarStarf::InitSpeedCtrl()
{
	CRect rect( -STARFSPEED_WIDTH, -STARFSPEED_HEIGHT, 0, 0 );

	SetButtonInfo( STARFSPEED_INDEX, ID_STARF_SPEED, TBBS_SEPARATOR, STARFSPEED_WIDTH );

	if ( !speed.Create( WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rect, this,
		ID_CONST_LIST ) )
	{
		return false;
	}

	if ( speed.m_hWnd == NULL )
		return false;

	GetItemRect( STARFSPEED_INDEX, rect );
	speed.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	speed.ShowWindow( SW_SHOW );

	speed.SetCurSel( speed.AddString("Now") );
	speed.AddString("1X");
	speed.AddString("10X");
	speed.AddString("100X");
	speed.AddString("1000X");

	return true;
}


BEGIN_MESSAGE_MAP( CBarStarf, CToolBar )
	//{{AFX_MSG_MAP(CBarStarf)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBarStarf message handlers


void CBarStarf::OnTimer(UINT nIDEvent) 
{
	CToolBar ::OnTimer(nIDEvent);

	/// SPEED
	COleDateTime curTime = COleDateTime::GetCurrentTime();
	time.SetTime(curTime);
	date.SetTime(curTime);
}
