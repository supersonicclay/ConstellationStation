//===========================================================================
// DlgAbout.cpp
//
// CDlgAbout
//   about dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAbout)
	//}}AFX_DATA_INIT
}


void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	//{{AFX_MSG_MAP(CDlgAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgAbout message handlers
