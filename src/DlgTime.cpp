//===========================================================================
// DlgTime.cpp
//
// CDlgTime
//   time dialog.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTime, CDialog)
	//{{AFX_MSG_MAP(CDlgTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgTime message handlers
