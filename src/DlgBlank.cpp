//===========================================================================
// DlgBlank.cpp
//
// CDlgBlank
//   blank dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgBlank.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgBlank::CDlgBlank(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBlank::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBlank)
	//}}AFX_DATA_INIT
}


void CDlgBlank::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBlank)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBlank, CDialog)
	//{{AFX_MSG_MAP(CDlgBlank)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgBlank message handlers
