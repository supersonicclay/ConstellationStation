//===========================================================================
// DlgLocation.cpp
//
// CDlgLocation
//   location dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgLocation.h"

#include "fstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgLocation::CDlgLocation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLocation)
	//}}AFX_DATA_INIT
}


void CDlgLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocation)
	DDX_Control(pDX, IDC_LOCATION_COMBO, locationCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLocation, CDialog)
	//{{AFX_MSG_MAP(CDlgLocation)
	ON_BN_CLICKED(IDC_LOCATION_SEARCH, OnLocationSearch)
	ON_BN_CLICKED(IDC_LOCATION_SETHOME, OnLocationSetHome)
	ON_CBN_SELCHANGE(IDC_LOCATION_COMBO, OnSelChangeLocationCombo)
	ON_EN_CHANGE(IDC_LOCATION_LATITUDE_D, OnChangeLocationLatitudeD)
	ON_EN_CHANGE(IDC_LOCATION_LATITUDE_M, OnChangeLocationLatitudeM)
	ON_EN_CHANGE(IDC_LOCATION_LONGITUDE_D, OnChangeLocationLongitudeD)
	ON_EN_CHANGE(IDC_LOCATION_LONGITUDE_M, OnChangeLocationLongitudeM)
	ON_BN_CLICKED(IDC_LOCATION_E, OnLocationE)
	ON_BN_CLICKED(IDC_LOCATION_W, OnLocationW)
	ON_BN_CLICKED(IDC_LOCATION_N, OnLocationN)
	ON_BN_CLICKED(IDC_LOCATION_S, OnLocationS)
	ON_EN_CHANGE(IDC_LOCATION_TIMEZONE, OnChangeLocationTimezone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgLocation message handlers

BOOL CDlgLocation::OnInitDialog() 
{
	CDialog::OnInitDialog();

	location = starfield.GetLocation();

	locationCombo.AddString( " Custom..." );
	LoadLocations();
	GetCurrentLocation();
	
	return TRUE;
}

void CDlgLocation::GetCurrentLocation()
{
	if( location.state.IsEmpty() )
	{
		if( !Search( location.country + ", " + location.city ) )
			CSWarn( this->GetSafeHwnd(), "Couldn't find your current location" );
	}
	else
	{
		if( !Search( location.country + ", " + location.state + ", " + location.city ) )
			CSWarn( this->GetSafeHwnd(), "Couldn't find your current location" );
	}
}

void CDlgLocation::LoadLocations()
{
	location_s loc;

	ifstream file( "data\\locations.dat" );
	if( !file.is_open() )
	{
		CSDebug( "Error opening locations input file", "CDlgLocation::LoadLocations" );
		exit(0);
		return;
	}

	while( file.peek() != EOF )
	{
		file.getline( loc.country.GetBuffer(100), 100, ',' ); file.ignore();
		file.getline( loc.state.GetBuffer(100), 100, ',' ); file.ignore();
		file.read( loc.city.GetBuffer(100), 26 );
		loc.city.GetBuffer(100)[26] = '\0';
		file >> loc.latd >> loc.latm >> loc.ns;
		file >> loc.lond >> loc.lonm >> loc.ew;
		file >> loc.timezone;
		file.ignore();

		loc.country.ReleaseBuffer();
		loc.state.ReleaseBuffer();
		loc.city.ReleaseBuffer();
		loc.city.TrimRight();

		locationsVec.push_back( loc );
		DWORD vectorIndex = locationsVec.size()-1;

		CString display;
		if( loc.state.IsEmpty() )
			display = loc.country + ", " + loc.city;
		else
			display = loc.country + ", " + loc.state + ", " + loc.city;

		int i = locationCombo.AddString( display );
		locationCombo.SetItemData( i, vectorIndex );
	}
}

void CDlgLocation::OnSelChangeLocationCombo() 
{
	// Update location
	location = locationsVec[ locationCombo.GetItemData(locationCombo.GetCurSel()) ];

	char buf[100];

	// Fill latitude edits
	itoa( location.latd, buf, 10 );
	SetDlgItemText( IDC_LOCATION_LATITUDE_D, buf );
	itoa( location.latm, buf, 10 );
	SetDlgItemText( IDC_LOCATION_LATITUDE_M, buf );

	// Fill longitude edits
	itoa( location.lond, buf, 10 );
	SetDlgItemText( IDC_LOCATION_LONGITUDE_D, buf );
	itoa( location.lonm, buf, 10 );
	SetDlgItemText( IDC_LOCATION_LONGITUDE_M, buf );

	// Select N/S/E/W
	CheckDlgButton( IDC_LOCATION_N, location.ns == 'N' );
	CheckDlgButton( IDC_LOCATION_S, location.ns == 'S' );
	CheckDlgButton( IDC_LOCATION_E, location.ew == 'E' );
	CheckDlgButton( IDC_LOCATION_W, location.ew == 'W' );

	// Fill timezone edit
	if( location.timezone == (int)location.timezone )
		itoa( (int)location.timezone, buf, 10 );
	else
		gcvt( location.timezone, 3, buf );
	SetDlgItemText( IDC_LOCATION_TIMEZONE, buf );
}

BOOL CDlgLocation::Search( CString t )
{
	t.MakeLower();

	int i;
	CString s;
	for( i=locationCombo.GetCurSel()+1; i<locationsVec.size(); ++i )
	{
		locationCombo.GetLBText( i, s );
		s.MakeLower();
		if( s.Find( t ) != -1 )
		{
			locationCombo.SetCurSel(i);
			OnSelChangeLocationCombo();
			return TRUE;
		}
	}
	for( i=0; i<locationCombo.GetCurSel(); ++i )
	{
		locationCombo.GetLBText( i, s );
		s.MakeLower();
		if( s.Find( t ) != -1 )
		{
			locationCombo.SetCurSel(i);
			OnSelChangeLocationCombo();
			return TRUE;
		}
	}
	return FALSE;
}

void CDlgLocation::OnLocationSearch() 
{
	CString t;
	GetDlgItemText( IDC_LOCATION_SEARCH_TEXT, t );
	if( !Search( t ) )
		CSWarn( this->GetSafeHwnd(), "Finished searching the database" );
}

void CDlgLocation::OnLocationSetHome() 
{
	optionsMgr.SetLocationHome( locationsVec[ locationCombo.GetItemData(locationCombo.GetCurSel()) ] );
}

void CDlgLocation::OnChangeLocationLatitudeD() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnChangeLocationLatitudeM() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnChangeLocationLongitudeD() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnChangeLocationLongitudeM() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnLocationN() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnLocationS() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnLocationE() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnLocationW() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgLocation::OnChangeLocationTimezone() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
