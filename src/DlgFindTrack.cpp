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
	DDX_Control(pDX, IDC_RA_SD, raSDControl);
	DDX_Control(pDX, IDC_DEC_SD, decSDControl);
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
	ON_BN_CLICKED(IDC_FIND_CONST, OnFindConst)
	ON_BN_CLICKED(IDC_TRACK_CONST, OnTrackConst)
	ON_BN_CLICKED(IDC_FIND_STAR, OnFindStar)
	ON_BN_CLICKED(IDC_TRACK_STAR, OnTrackStar)
	ON_BN_CLICKED(IDC_FIND_RADEC, OnFindRaDec)
	ON_BN_CLICKED(IDC_TRACK_RADEC, OnTrackRaDec)
	ON_BN_CLICKED(IDC_STOP_TRACKING, OnStopTracking)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgFindTrack message handlers

BOOL CDlgFindTrack::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString s;
	char buf[100];

	// Find currently tracked object
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
			sprintf( buf, "RA: %ih %im %2.1fs   DEC: %id %im %2.1fs",
				ra.hour, ra.minute, ra.second,
				dec.degree, dec.minute, dec.second );
			s = buf;
		}

		SetDlgItemText( IDC_CURRENT, s );
	}
	else // not tracking
	{
		SetDlgItemText( IDC_CURRENT, "Not currently tracking" );
		stopTrackingButton.EnableWindow( FALSE );
	}


	for( int ci=0; ci<starfield.GetConstCount(); ++ci )
	{
		s = starfield.GetConst(ci)->GetName();
		constControl.AddString( s );
	}

	for( int si=0; si<starfield.GetStarCount(); ++si )
	{
		s = starfield.GetStar(si)->GetName();
		if( !s.IsEmpty() )
			starControl.AddString( s );
	}

	// Limit ra/dec edit length
	raHControl.SetLimitText(2);
	raMControl.SetLimitText(2);
	raSControl.SetLimitText(2);
	raSDControl.SetLimitText(1);
	decDControl.SetLimitText(2);
	decMControl.SetLimitText(2);
	decSControl.SetLimitText(2);
	decSDControl.SetLimitText(1);

	return TRUE;
}

void CDlgFindTrack::OnFindConst() 
{
	CString buf;
	constControl.GetLBText( constControl.GetCurSel(), buf );
	starfield.Find( starfield.GetConst( buf ) );
	constMgr.Select( starfield.GetConstIndex(buf) );
	EndDialog( IDOK );
	Redraw();
}

void CDlgFindTrack::OnTrackConst() 
{
	CString buf;
	constControl.GetLBText( constControl.GetCurSel(), buf );
	starfield.StartTracking( starfield.GetConst( buf ) );
	constMgr.Select( starfield.GetConstIndex(buf) );
	EndDialog( IDOK );
	Redraw();	
}

void CDlgFindTrack::OnFindStar() 
{
	CString buf;
	starControl.GetLBText( starControl.GetCurSel(), buf );
	starfield.Find( starfield.GetStar( buf ) );
	EndDialog( IDOK );
	Redraw();	
}

void CDlgFindTrack::OnTrackStar() 
{
	CString buf;
	starControl.GetLBText( starControl.GetCurSel(), buf );
	starfield.StartTracking( starfield.GetStar( buf ) );
	EndDialog( IDOK );
	Redraw();	
}

void CDlgFindTrack::OnFindRaDec() 
{
	ra_s ra;
	ra.hour = GetDlgItemInt( IDC_RA_H );
	ra.minute = GetDlgItemInt( IDC_RA_M );
	ra.second = GetDlgItemInt( IDC_RA_S );
	ra.second += GetDlgItemInt( IDC_RA_SD )*0.1f;
	dec_s dec;
	dec.degree = GetDlgItemInt( IDC_DEC_D );
	dec.minute = GetDlgItemInt( IDC_DEC_M );
	dec.second = GetDlgItemInt( IDC_DEC_S );
	dec.second += GetDlgItemInt( IDC_DEC_SD )*0.1f;

	starfield.Find( ra, dec );
	EndDialog( IDOK );
	Redraw();
}

void CDlgFindTrack::OnTrackRaDec() 
{
	ra_s ra;
	ra.hour = GetDlgItemInt( IDC_RA_H );
	ra.minute = GetDlgItemInt( IDC_RA_M );
	ra.second = GetDlgItemInt( IDC_RA_S );
	ra.second += GetDlgItemInt( IDC_RA_SD )*0.1f;
	dec_s dec;
	dec.degree = GetDlgItemInt( IDC_DEC_D );
	dec.minute = GetDlgItemInt( IDC_DEC_M );
	dec.second = GetDlgItemInt( IDC_DEC_S );
	dec.second += GetDlgItemInt( IDC_DEC_SD )*0.1f;

	starfield.StartTracking( ra, dec );
	EndDialog( IDOK );
	Redraw();
}


void CDlgFindTrack::OnStopTracking() 
{
	starfield.StopTracking();
	EndDialog( IDOK );
	Redraw();
}
