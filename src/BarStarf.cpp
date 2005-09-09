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
	ON_CBN_SELCHANGE(ID_STARF_SPEED, OnSpeedChange)
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
#define STARFSPEED_WIDTH	120
#define STARFSPEED_HEIGHT	200


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

	// Timer ticks every second by default
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
		ID_STARF_SPEED ) )
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

	// MUST BE ADDED IN SAME ORDER as in speed_e declaration
	//  so that index number will be same as integer value of enum
	speed.SetCurSel( speed.AddString("Now") );
	speed.AddString("Realtime");
	speed.AddString("Seconds");
	speed.AddString("Minutes");
	speed.AddString("Hours");
	speed.AddString("Days");
	speed.AddString("Years");
	speed.AddString("Sidereal Days");

	return true;
}


/////////////////////////////////////////////////////////////////////////////
// CBarStarf message handlers

void CBarStarf::OnTimer(UINT nIDEvent) 
{
	CToolBar::OnTimer(nIDEvent);
	
	if( !inputMgr.mouseRotatingXY &&
		!inputMgr.mouseRotatingY &&
		nIDEvent == 1 &&
		state == state_Viewing )
	{
		if( starfield.GetAnimation() == animation_Forward )
			AnimationAdjustTime( 1 );
		else
			AnimationAdjustTime( -1 );
	}
}

void CBarStarf::UpdateStarfieldTime()
{
	COleDateTime t, d, lt;
	time.GetTime(t);
	date.GetTime(d);
	lt.SetDateTime( d.GetYear(), d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );
	starfield.SetLT(lt);

	Redraw();
}

void CBarStarf::SetTimeToNow()
{
	COleDateTime dt = COleDateTime::GetCurrentTime();
	time.SetTime(dt);
	date.SetTime(dt);
	UpdateStarfieldTime();
}

void CBarStarf::SetTime( COleDateTime& lt )
{
	time.SetTime(lt);
	date.SetTime(lt);
	UpdateStarfieldTime();
}

void CBarStarf::AdjustTime( int years, int days, int hours, int minutes, int seconds )
{
	COleDateTime t, d, dt;
	time.GetTime(t);
	date.GetTime(d);

	// Adjust time
	dt.SetDateTime( d.GetYear()+years, d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );
	dt += COleDateTimeSpan( days, hours, minutes, seconds );
	if( dt.GetStatus() != COleDateTime::valid )
	{
		CSDebug( "COleDateTime not valid", "CBarStarf::AdjustTime" );
		starfield.SetAnimation( animation_Paused );
	}

	time.SetTime(dt);
	date.SetTime(dt);
	starfield.SetLT(dt);

	Redraw();
}

void CBarStarf::ChangeSpeed( speed_e x )
{
	speed.SetCurSel(x);
	OnSpeedChange();
}

void CBarStarf::AnimationAdjustTime( int m )
{
	switch( starfield.GetSpeed() )
	{
		case speed_Now:
			SetTimeToNow();
			break;
		case speed_Realtime:
			AdjustTime( 0, 0, 0, 0, m );
			break;
		case speed_Seconds:
			AdjustTime( 0, 0, 0, 0, m );
			break;
		case speed_Minutes:
			AdjustTime( 0, 0, 0, m, 0 );
			break;
		case speed_Hours:
			AdjustTime( 0, 0, m, 0, 0 );
			break;
		case speed_Days:
			AdjustTime( 0, m, 0, 0, 0 );
			break;
		case speed_Years:
			AdjustTime( m, 0, 0, 0, 0 );
			break;
		case speed_SiderealDays:
			AdjustTime( 0, 0, 23*m, 56*m, 4*m );/// How's it look?
			break;
		default:
			break;
	}
	Redraw();
}

void CBarStarf::AnimationSetTimer()
{
	switch( starfield.GetSpeed() )
	{
		case speed_Now:
			SetTimeToNow();
			SetTimer( 1, 1000, NULL );
			break;
		case speed_Realtime:
			SetTimer( 1, 1000, NULL );
			break;
		case speed_Seconds:
			SetTimer( 1, 40, NULL );
			break;
		case speed_Minutes:
			SetTimer( 1, 40, NULL );
			break;
		case speed_Hours:
			SetTimer( 1, 40, NULL );
			break;
		case speed_Days:
			SetTimer( 1, 40, NULL );
			break;
		case speed_Years:
			SetTimer( 1, 40, NULL );
			break;
		case speed_SiderealDays:
			SetTimer( 1, 40, NULL );
			break;
		default:
			break;
	}
}

void CBarStarf::OnDateChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	if( starfield.GetSpeed() == speed_Now )
		ChangeSpeed( speed_Realtime );
	UpdateStarfieldTime();
}

void CBarStarf::OnTimeChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	if( starfield.GetSpeed() == speed_Now )
		ChangeSpeed( speed_Realtime );
	UpdateStarfieldTime();
}

void CBarStarf::OnSpeedChange()
{
	starfMgr.ChangeStarfSpeed( (speed_e) speed.GetCurSel() );
}
