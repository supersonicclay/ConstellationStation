//===========================================================================
// DlgFindTrack.cpp
//
// CDlgFindTrack
//   find and track dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgFindTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgFindTrack::CDlgFindTrack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFindTrack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFindTrack)
	//}}AFX_DATA_INIT
}


void CDlgFindTrack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFindTrack)
	DDX_Control(pDX, IDC_STOP_TRACKING, stopTrackingButton);
	DDX_Control(pDX, IDC_RA_S, raSControl);
	DDX_Control(pDX, IDC_RA_M, raMControl);
	DDX_Control(pDX, IDC_RA_H, raHControl);
	DDX_Control(pDX, IDC_DEC_S, decSControl);
	DDX_Control(pDX, IDC_DEC_M, decMControl);
	DDX_Control(pDX, IDC_DEC_D, decDControl);
	DDX_Control(pDX, IDC_STAR, starControl);
	DDX_Control(pDX, IDC_CONST, constControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFindTrack, CDialog)
	//{{AFX_MSG_MAP(CDlgFindTrack)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_TRACK, OnTrack)
	ON_BN_CLICKED(IDC_ENABLE_CONST, OnEnableConst)
	ON_BN_CLICKED(IDC_ENABLE_STAR, OnEnableStar)
	ON_BN_CLICKED(IDC_ENABLE_RA_DEC, OnEnableRADec)
	ON_BN_CLICKED(IDC_STOP_TRACKING, OnStopTracking)
	ON_EN_CHANGE(IDC_RA_H, OnChangeRAH)
	ON_EN_CHANGE(IDC_RA_M, OnChangeRAM)
	ON_EN_CHANGE(IDC_DEC_D, OnChangeDecD)
	ON_EN_CHANGE(IDC_DEC_M, OnChangeDecM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Combo box dimensions
#define CONSTLIST_HEIGHT	200
#define STARLIST_HEIGHT		200


/////////////////////////////////////////////////////////////////////////////
// CDlgFindTrack message handlers

BOOL CDlgFindTrack::OnInitDialog() 
{
	CDialog::OnInitDialog();

	FindCurrentlyTracked();

	CheckDlgButton( IDC_ENABLE_CONST, TRUE );
	OnEnableConst();

	CString s;

	// Fill constellation list
	for( int ci=0; ci<starfield.GetConstCount(); ++ci )
	{
		s = starfield.GetConst(ci)->GetName();
		constControl.AddString( s );
	}

	// Fill stars list
	for( int si=0; si<starfield.GetStarCount(); ++si )
	{
		s = starfield.GetStar(si)->GetName();
		if( !s.IsEmpty() )
			starControl.AddString( s );
	}

	// Limit ra/dec edit length
	raHControl.SetLimitText(2);
	raMControl.SetLimitText(2);
	decDControl.SetLimitText(3);
	decMControl.SetLimitText(2);

	return TRUE;
}

// Find currently tracked object and fill CEdit
void CDlgFindTrack::FindCurrentlyTracked()
{
	CString s;

	if( starfield.IsTracking() )
	{
		track_e t = starfield.GetTrackingType();
		if( t == track_Star )
			s = "Star: " + starfield.GetTrackingName();
		else if( t == track_Const )
			s = "Constellation: "  + starfield.GetTrackingName();
		else if( t == track_RADec )
		{
			ra_s ra = starfield.GetTrackingRA();
			dec_s dec = starfield.GetTrackingDec();
			CString ras, decs;
			ras.Format( "RA: %ih %im %2.1fs    ", ra.hour, ra.minute, ra.second );
			char sign = dec.positive?'+':'-';
			decs.Format( "Dec: %c%i° %im %2.1fs", sign, dec.degree, dec.minute, dec.second );
			s = ras + decs;
		}

		SetDlgItemText( IDC_CURRENT, s );
	}
	else // not tracking
	{
		SetDlgItemText( IDC_CURRENT, "Not currently tracking" );
		stopTrackingButton.EnableWindow( FALSE );
	}
}

// Fill given right ascension and declination structs
void CDlgFindTrack::FillRADec( ra_s& ra, dec_s& dec )
{
	CString s;

	ra.hour = GetDlgItemInt( IDC_RA_H );
	ra.minute = GetDlgItemInt( IDC_RA_M );
	GetDlgItemText( IDC_RA_S, s );
	ra.second = (float)atof(s);

	dec.minute = GetDlgItemInt( IDC_DEC_M );
	GetDlgItemText( IDC_DEC_S, s );
	dec.second = (float)atof(s);

	int decd = 	GetDlgItemInt( IDC_DEC_D );
	if( decd < 0 )
	{
		dec.positive = FALSE;
		dec.degree = -decd;
	}
	else
	{
		dec.positive = TRUE;
		dec.degree = decd;
	}
}

void CDlgFindTrack::OnFind() 
{
	if( IsDlgButtonChecked( IDC_ENABLE_CONST ) )
		FindConst();
	else if( IsDlgButtonChecked( IDC_ENABLE_STAR ) )
		FindStar();
	else if( IsDlgButtonChecked( IDC_ENABLE_RA_DEC ) )
		FindRADec();
	EndDialog( IDOK );
	Redraw();
}

void CDlgFindTrack::OnTrack() 
{
	if( IsDlgButtonChecked( IDC_ENABLE_CONST ) )
		TrackConst();
	else if( IsDlgButtonChecked( IDC_ENABLE_STAR ) )
		TrackStar();
	else if( IsDlgButtonChecked( IDC_ENABLE_RA_DEC ) )
		TrackRADec();
	EndDialog( IDOK );
	Redraw();
}

void CDlgFindTrack::FindConst() 
{
	CString buf;
	constControl.GetLBText( constControl.GetCurSel(), buf );
	starfield.FindConst( starfield.GetConst( buf ) );
	constMgr.Select( starfield.GetConstIndex(buf) );
}

void CDlgFindTrack::TrackConst() 
{
	CString buf;
	constControl.GetLBText( constControl.GetCurSel(), buf );
	starfield.StartTrackingConst( starfield.GetConst( buf ) );
	constMgr.Select( starfield.GetConstIndex(buf) );
}

void CDlgFindTrack::FindStar() 
{
	CString buf;
	starControl.GetLBText( starControl.GetCurSel(), buf );
	starfield.FindStar( starfield.GetStar( buf ) );
}

void CDlgFindTrack::TrackStar() 
{
	CString buf;
	starControl.GetLBText( starControl.GetCurSel(), buf );
	starfield.StartTrackingStar( starfield.GetStar( buf ) );
}

void CDlgFindTrack::FindRADec() 
{
	ra_s ra;
	dec_s dec;
	FillRADec( ra, dec );
	starfield.FindRADec( ra, dec );
}

void CDlgFindTrack::TrackRADec() 
{
	ra_s ra;
	dec_s dec;
	FillRADec( ra, dec );
	starfield.StartTrackingRADec( ra, dec );
}

void CDlgFindTrack::OnChangeRAH() 
{
	CString s;
	raHControl.GetWindowText( s );

	if( s.GetLength() == 2 )
		raMControl.SetFocus();
}

void CDlgFindTrack::OnChangeRAM() 
{
	CString s;
	raMControl.GetWindowText( s );

	if( s.GetLength() == 2 )
		raSControl.SetFocus();
}

void CDlgFindTrack::OnChangeDecD() 
{
	CString s;
	decDControl.GetWindowText( s );

	if( s.GetLength() == 3 )
		decMControl.SetFocus();
}

void CDlgFindTrack::OnChangeDecM() 
{
	CString s;
	decMControl.GetWindowText( s );

	if( s.GetLength() == 2 )
		decSControl.SetFocus();
}

void CDlgFindTrack::OnEnableConst() 
{
	BOOL b = IsDlgButtonChecked(IDC_ENABLE_CONST);
	constControl.EnableWindow( b );
	starControl.EnableWindow( !b );
	raHControl.EnableWindow( !b );
	raMControl.EnableWindow( !b );
	raSControl.EnableWindow( !b );
	decDControl.EnableWindow( !b );
	decMControl.EnableWindow( !b );
	decSControl.EnableWindow( !b );
}

void CDlgFindTrack::OnEnableStar() 
{
	BOOL b = IsDlgButtonChecked(IDC_ENABLE_STAR);
	constControl.EnableWindow( !b );
	starControl.EnableWindow( b );
	raHControl.EnableWindow( !b );
	raMControl.EnableWindow( !b );
	raSControl.EnableWindow( !b );
	decDControl.EnableWindow( !b );
	decMControl.EnableWindow( !b );
	decSControl.EnableWindow( !b );
}

void CDlgFindTrack::OnEnableRADec() 
{
	BOOL b = IsDlgButtonChecked(IDC_ENABLE_RA_DEC);
	constControl.EnableWindow( !b );
	starControl.EnableWindow( !b );
	raHControl.EnableWindow( b );
	raMControl.EnableWindow( b );
	raSControl.EnableWindow( b );
	decDControl.EnableWindow( b );
	decMControl.EnableWindow( b );
	decSControl.EnableWindow( b );
}

void CDlgFindTrack::OnStopTracking() 
{
	starfield.StopTracking();
	FindCurrentlyTracked();
	Redraw();
}

