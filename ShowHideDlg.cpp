// ShowHideDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "ShowHideDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "MainFrm.h"
#include "Constellation.h"

/////////////////////////////////////////////////////////////////////////////
// CShowHideDlg dialog


CShowHideDlg::CShowHideDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowHideDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowHideDlg)
	//}}AFX_DATA_INIT
}


void CShowHideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowHideDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowHideDlg, CDialog)
	//{{AFX_MSG_MAP(CShowHideDlg)
	ON_LBN_SELCHANGE(IDC_CONST_LIST, OnSelchangeConstList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShowHideDlg message handlers

BOOL CShowHideDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	VERIFY(m_List.SubclassDlgItem(IDC_CONST_LIST, this));


	constellations = ((CMainFrame*)GetParent())->
										GetStarfield()->GetConstellations();
	numConstellations = ((CMainFrame*)GetParent())->
										GetStarfield()->GetNumConstellations();

	// Add strings to list box
	for (int i=0; i<numConstellations; i++)
	{
		m_List.SetSel(
			m_List.AddString(constellations[i].GetName()),
			constellations[i].IsVisible());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowHideDlg::OnSelchangeConstList() 
{
	for (int i=0; i<numConstellations; i++)
	{
		constellations[i].SetVisible(m_List.GetSel(i));
	}

	// Redraw view
	((CMainFrame*)GetParent())->GetView()->InvalidateRect(NULL, FALSE);
}
