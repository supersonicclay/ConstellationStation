//===========================================================================
// DlgOptionsGeneral.cpp
//
// CDlgOptionsGeneral
//   general options dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgOptionsGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgOptionsGeneral::CDlgOptionsGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsGeneral)
	//}}AFX_DATA_INIT
}


void CDlgOptionsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsGeneral)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsGeneral, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsGeneral)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsGeneral message handlers
