//===========================================================================
// BarStarf.cpp
//
// CBarStarf
//   starfield toolbar.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "BarStarf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP( CBarStarf, CToolBar )
	//{{AFX_MSG_MAP(CBarStarf)
	ON_WM_TIMER()
	ON_NOTIFY(DTN_DATETIMECHANGE, ID_STARF_DATE, OnDateChange)
	ON_NOTIFY(DTN_DATETIMECHANGE, ID_STARF_TIME, OnTimeChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Time, Date, and Speed control dimensions
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
// Construction / Destruction

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
		CSDebug( "Error initializing starfield toolbar controls", "CBarStarf::Init" );
		exit(0);
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
		CSDebug( "Can't create date control", "CBarStarf::InitDateCtrl" );
		exit(0);
		return false;
	}

	if ( date.m_hWnd == NULL )
	{
		CSDebug( "Can't create date control", "CBarStarf::InitDateCtrl" );
		exit(0);
		return false;
	}

	date.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
 		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	date.ShowWindow( SW_SHOW );

	// Set range
	COleDateTime minDate(1601, 1, 1, 0, 0, 0);
	COleDateTime maxDate(9999, 12, 31, 0, 0, 0);
	if( !date.SetRange( &minDate, &maxDate ) )
	{
		CSDebug( "Can't set the date range", "CBarStarf::InitDateCtrl" );
		exit(0);
		return false;
	}

	// Set to current date
	date.SetTime(COleDateTime::GetCurrentTime());

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
		CSDebug( "Can't create time control", "CBarStarf::InitDateCtrl" );
		exit(0);
		return FALSE;
	}

	if ( time.m_hWnd == NULL )
	{
		CSDebug( "Can't create time control", "CBarStarf::InitDateCtrl" );
		exit(0);
		return FALSE;
	}

	time.SetWindowPos( NULL, rect.left, rect.top, 0, 0,
		SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS );
	time.ShowWindow( SW_SHOW );

	// Set range
	COleDateTime minTime(1601, 1, 1, 0, 0, 0);
	COleDateTime maxTime(9999, 12, 31, 0, 0, 0);
	if( !time.SetRange( &minTime, &maxTime ) )
	{
		CSDebug( "Can't set the time range", "CBarStarf::InitTimeCtrl" );
		exit(0);
		return false;
	}

	// Set to current time
	time.SetTime(COleDateTime::GetCurrentTime());

	return true;
}

BOOL CBarStarf::InitSpeedCtrl()
{
	CRect rect( -STARFSPEED_WIDTH, -STARFSPEED_HEIGHT, 0, 0 );

	SetButtonInfo( STARFSPEED_INDEX, ID_STARF_SPEED, TBBS_SEPARATOR, STARFSPEED_WIDTH );

	if ( !speed.Create( WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rect, this,
		ID_CONST_LIST ) )
	{
		CSDebug( "Can't create speed control", "CBarStarf::InitSpeedCtrl" );
		exit(0);
		return false;
	}

	if ( speed.m_hWnd == NULL )
	{
		CSDebug( "Can't create speed control", "CBarStarf::InitSpeedCtrl" );
		exit(0);
		return false;
	}

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


/////////////////////////////////////////////////////////////////////////////
// CBarStarf message handlers

void CBarStarf::OnTimer(UINT nIDEvent) 
{
	CToolBar ::OnTimer(nIDEvent);

	/*
	COleDateTime curTime = COleDateTime::GetCurrentTime();
	time.SetTime(curTime);
	date.SetTime(curTime);
	*/
}

void CBarStarf::UpdateTime()
{
	COleDateTime t, d;
	time.GetTime(t);
	date.GetTime(d);
	t.SetDateTime( d.GetYear(), d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );
	// Convert to UTC
	t.m_dt += _timezone/60/60/24.0;
	starfield.SetGregorian(t);

	/// Format to string
//	char str[100];

	/*
	sprintf( str, "%f", starfield.GetJulian() );
	CSInfo( str );

	sprintf( str, "%i/%i/%i %02i:%02i:%02i",
		t.GetMonth(),
		t.GetDay(),
		t.GetYear(),
		t.GetHour(),
		t.GetMinute(),
		t.GetSecond() );
	CSInfo( str );
	*/

	Redraw();
}

void CBarStarf::OnDateChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	UpdateTime();
}

void CBarStarf::OnTimeChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	UpdateTime();
}
