// ConstNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "ConstNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstNameDlg dialog


CConstNameDlg::CConstNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConstNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstNameDlg)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CConstNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstNameDlg)
	DDX_Text(pDX, IDC_CONST_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstNameDlg, CDialog)
	//{{AFX_MSG_MAP(CConstNameDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstNameDlg operations

void CConstNameDlg::SetConstName(CString name)
{
	m_Name = name;
}


/////////////////////////////////////////////////////////////////////////////
// CConstNameDlg message handlers

void CConstNameDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	// Give focus to edit box
	CEdit* pNameBox;
	pNameBox = (CEdit*) GetDlgItem(IDC_CONST_NAME);
	GotoDlgCtrl(pNameBox);
}

