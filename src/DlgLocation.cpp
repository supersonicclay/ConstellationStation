//===========================================================================
// DlgLocation.cpp
//
// CDlgLocation
//   location dialog.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "DlgLocation.h"

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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLocation, CDialog)
	//{{AFX_MSG_MAP(CDlgLocation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgLocation message handlers
