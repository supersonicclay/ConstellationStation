//===========================================================================
// DlgLocation.cpp
//
// CDlgLocation
//   location dialog
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "DlgLocation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation dialog


CDlgLocation::CDlgLocation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLocation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLocation, CDialog)
	//{{AFX_MSG_MAP(CDlgLocation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation message handlers
