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

	SetDlgItemText( IDC_STAR_NAME, star->GetName() );

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
	if( dec.positive ) s += '+';
	else s += '-';
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

	s = CString();
	float mag = star->GetMag();
	if( mag < 0 ) s += '-';
	s += (char)((int)(mag)%10+'0');
	s += '.';
	s += (char)((int)(mag*10)%10+'0');
	s += (char)((int)(mag*100)%10+'0');
	SetDlgItemText( IDC_STAR_MAG, s );


	SetDlgItemText( IDC_STAR_SPECTRAL, CString(star->GetSpectral()) );
	
	return TRUE;
}
