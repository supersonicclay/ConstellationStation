// DlgTime.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "DlgTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTime dialog


CDlgTime::CDlgTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTime)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTime, CDialog)
	//{{AFX_MSG_MAP(CDlgTime)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTime message handlers
