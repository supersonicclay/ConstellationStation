//===========================================================================
// DlgStarInfo.cpp
//
// CDlgStarInfo
//   time dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgStarInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgStarInfo::CDlgStarInfo( CDataStar* s, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStarInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStarInfo)
	//}}AFX_DATA_INIT
	star = s;
}

void CDlgStarInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStarInfo)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStarInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgStarInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgStarInfo message handlers

BOOL CDlgStarInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString s;
	char buf[100];
	char sign;

	// Identification
	itoa( star->GetHID(), buf, 10 );
	SetDlgItemText( IDC_STAR_HID, buf );
	SetDlgItemText( IDC_STAR_NAME, star->GetName() );

	// Appearance
	gcvt( star->GetMag(), 5, buf );
	SetDlgItemText( IDC_STAR_MAG, buf );
	SetDlgItemText( IDC_STAR_SPECTRAL, CString(star->GetSpectral()) );

	// Position

	// Right ascension
	ra_s ra = star->GetRA();
	itoa( ra.hour, buf, 10 );
	s = CString(buf) + "h ";
	itoa( ra.minute, buf, 10 );
	s += CString(buf) + "m ";
	itoa( (int)ra.second, buf, 10 );
	s += CString(buf) + "s";
	SetDlgItemText( IDC_STAR_RA, s );

	// Declination
	dec_s dec = star->GetDec();
	sign = dec.positive?'+':'-';
	s = sign;
	itoa( abs(dec.degree), buf, 10 );
	s += CString(buf) + "° ";
	itoa( dec.minute, buf, 10 );
	s += CString(buf) + "' ";
	itoa( (int)dec.second, buf, 10 );
	s += CString(buf) + "''";
	SetDlgItemText( IDC_STAR_DEC, s );

	// Azimuth
	float azimuth = star->GetAzimuth();
	itoa( (int)azimuth, buf, 10 );
	s = CString(buf) + "° ";
	azimuth = (azimuth - (int)azimuth)*60;
	itoa( (int)azimuth, buf, 10 );
	s += CString(buf) + "' ";
	azimuth = (azimuth - (int)azimuth)*60;
	itoa( (int)azimuth, buf, 10 );
	s += CString(buf) + "''";
	SetDlgItemText( IDC_STAR_AZIMUTH, s );

	// Altitude
	float altitude = star->GetAltitude();
	sign = (altitude > 0.0f)?'+':'-';
	altitude = fabs(altitude);
	s = sign;
	itoa( (int)altitude, buf, 10 );
	s += CString(buf) + "° ";
	altitude = (altitude - (int)altitude)*60;
	itoa( (int)altitude, buf, 10 );
	s += CString(buf) + "' ";
	altitude = (altitude - (int)altitude)*60;
	itoa( (int)altitude, buf, 10 );
	s += CString(buf) + "''";
	SetDlgItemText( IDC_STAR_ALTITUDE, s );

	/*/// before gcvt
	s = CString();
	float mag = star->GetMag();
	if( mag < 0 ) s += '-';
	s += (char)((int)(mag)%10+'0');
	s += '.';
	s += (char)((int)(mag*10)%10+'0');
	s += (char)((int)(mag*100)%10+'0');
	SetDlgItemText( IDC_STAR_MAG, s );

	s = CString();
	ra_s ra = star->GetRA();
	s += (char)(ra.hour/10+'0');
	s += (char)(ra.hour%10+'0');
	s += "h ";
	s += (char)(ra.minute/10+'0');
	s += (char)(ra.minute%10+'0');
	s += "m ";
	s += (char)((int)(ra.second)/10+'0');
	s += (char)((int)(ra.second)%10+'0');
	s += '.';
	s += (char)((int)(ra.second*10)%10+'0');
	s += (char)((int)(ra.second*100)%10+'0');
	s += "s";
	SetDlgItemText( IDC_STAR_RA, s );

	s = CString();
	dec_s dec = star->GetDec();
	char sign = dec.positive?'+':'-';
	s += (char)(dec.degree/10+'0');
	s += (char)(dec.degree%10+'0');
	s += "d ";
	s += (char)(dec.minute/10+'0');
	s += (char)(dec.minute%10+'0');
	s += "m ";
	s += (char)((int)(dec.second)/10+'0');
	s += (char)((int)(dec.second)%10+'0');
	s += '.';
	s += (char)((int)(dec.second*10)%10+'0');
	s += "s";
	SetDlgItemText( IDC_STAR_DEC, s );
	*/

	return TRUE;
}
