// DlgOptionsGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "DlgOptionsGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsGeneral dialog


CDlgOptionsGeneral::CDlgOptionsGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOptionsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsGeneral, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsGeneral message handlers
