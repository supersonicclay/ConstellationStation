//===========================================================================
// DlgConstName.cpp
//
// CDlgConstName
//   constellation name dialog
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "DlgConstName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConstName dialog


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
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConstName operations

void CDlgConstName::SetConstName(CString name_)
{
	name = name_;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgConstName message handlers

