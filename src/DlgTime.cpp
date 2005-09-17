//===========================================================================
// DlgTime.cpp
//
// CDlgTime
//   time dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgTime::CDlgTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTime)
	//}}AFX_DATA_INIT
}


void CDlgTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTime)
	DDX_Control(pDX, IDC_TIME_UT_TIME, utTime);
	DDX_Control(pDX, IDC_TIME_UT_DATE, utDate);
	DDX_Control(pDX, IDC_TIME_LT_TIME, ltTime);
	DDX_Control(pDX, IDC_TIME_LT_DATE, ltDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTime, CDialog)
	//{{AFX_MSG_MAP(CDlgTime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_LT_DATE, OnDateTimeChangeLTDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_LT_TIME, OnDateTimeChangeLTTime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_UT_DATE, OnDateTimeChangeUTDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_UT_TIME, OnDateTimeChangeUTTime)
	ON_BN_CLICKED(IDC_TIME_CALC, OnTimeCalc)
	ON_BN_CLICKED(IDC_TIME_DST, OnTimeDST)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgTime message handlers


BOOL CDlgTime::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Set date range for controls
	COleDateTime minDate(1601, 1, 1, 0, 0, 0);
	COleDateTime maxDate(9999, 12, 31, 0, 0, 0);
	if( !ltDate.SetRange( &minDate, &maxDate ) ||
		!ltTime.SetRange( &minDate, &maxDate ) ||
		!utDate.SetRange( &minDate, &maxDate ) ||
		!utTime.SetRange( &minDate, &maxDate ) )
	{
		CSDebug( "Can't set the date range", "CDlgTime::OnInitDialog" );
		exit(0);
		return false;
	}

	InitOptions();
	
	return TRUE;
}

void CDlgTime::InitOptions()
{
	lt = starfield.GetLT();
	ut = starfield.GetUT();
	julian = starfield.GetJulian();
	tz = starfield.GetLocation().timezone;
	dst = starfield.GetDST();

	ltDate.SetTime(lt);
	ltTime.SetTime(lt);
	utDate.SetTime(ut);
	utTime.SetTime(ut);
	UpdateJulianText();
	CheckDlgButton( IDC_TIME_DST, starfield.GetDST() );
}

void CDlgTime::UpdateJulianText()
{
	char buf[200];
	gcvt( julian, 150, buf );
	SetDlgItemText( IDC_TIME_JULIAN, buf );
}

void CDlgTime::OnDateTimeChangeLTDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Combine date and time
	COleDateTime t, d;
	ltDate.GetTime(d);
	ltTime.GetTime(t);
	lt.SetDateTime( d.GetYear(), d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );

	ut = LTtoUT( lt, tz, dst );
	utDate.SetTime(ut);
	utTime.SetTime(ut);

	julian = UTtoJulian(ut);
	UpdateJulianText();

	*pResult = 0;
}

void CDlgTime::OnDateTimeChangeLTTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Combine date and time
	COleDateTime d, t;
	ltDate.GetTime(d);
	ltTime.GetTime(t);
	lt.SetDateTime( d.GetYear(), d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );

	ut = LTtoUT( lt, tz, dst );
	utDate.SetTime(ut);
	utTime.SetTime(ut);

	julian = UTtoJulian(ut);
	UpdateJulianText();

	*pResult = 0;
}

void CDlgTime::OnDateTimeChangeUTDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Combine date and time
	COleDateTime t, d;
	utTime.GetTime(t);
	utDate.GetTime(d);
	ut.SetDateTime( d.GetYear(), d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );

	lt = UTtoLT( ut, tz, dst );
	ltDate.SetTime(lt);
	ltTime.SetTime(lt);
	
	julian = UTtoJulian(ut);
	UpdateJulianText();

	*pResult = 0;
}

void CDlgTime::OnDateTimeChangeUTTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Combine date and time
	COleDateTime t, d;
	utTime.GetTime(t);
	utDate.GetTime(d);
	ut.SetDateTime( d.GetYear(), d.GetMonth(), d.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond() );

	lt = UTtoLT( ut, tz, dst );
	ltDate.SetTime(lt);
	ltTime.SetTime(lt);
	
	julian = UTtoJulian(ut);
	UpdateJulianText();

	*pResult = 0;
}

void CDlgTime::OnTimeCalc() 
{
	char buf[200];
	GetDlgItemText( IDC_TIME_JULIAN, buf, 200 );

	julian = atof(buf);

	COleDateTime utNew = JulianToUT( julian );
	COleDateTime ltNew = UTtoLT( utNew, tz, dst );

	if( utNew.GetStatus() == COleDateTime::invalid ||
		ltNew.GetStatus() == COleDateTime::invalid )
	{
		CSWarn( GetSafeHwnd(), "Julian date out of range", "Warning" );
		LRESULT pResult;
		OnDateTimeChangeLTTime( NULL, &pResult ); // Fake a local time change
		return;
	}

	ut = utNew;
	lt = ltNew;

	utDate.SetTime(ut);
	utTime.SetTime(ut);
	ltDate.SetTime(lt);
	ltTime.SetTime(lt);
}

void CDlgTime::OnTimeDST() 
{
	dst = IsDlgButtonChecked( IDC_TIME_DST );
	LRESULT pResult;
	OnDateTimeChangeLTTime( NULL, &pResult ); // Fake a local time change
}
