//===========================================================================
// DlgConstName.cpp
//
// CDlgConstName
//   constellation name dialog.
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "DlgConstName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgConstName::CDlgConstName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConstName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConstName)
	name = _T("");
	//}}AFX_DATA_INIT
}


void CDlgConstName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConstName)
	DDX_Text(pDX, IDC_CONST_NAME, name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConstName, CDialog)
	//{{AFX_MSG_MAP(CDlgConstName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgConstName message handlers
