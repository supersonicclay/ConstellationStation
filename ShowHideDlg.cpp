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
	ON_BN_CLICKED(IDC_SHOWALL, OnShowAll)
	ON_BN_CLICKED(IDC_HIDEALL, OnHideAll)
	ON_BN_CLICKED(IDC_INVERT, OnInvert)
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

	CString str;

	// Add strings to list box
	for (int i=0; i<numConstellations; i++)
	{
		// Get name
		str = constellations[i].GetName();

		// If this constellation is current
		if (constellations[i].IsCurrent())
			str += " <--";

		// Add name to list
		m_List.SetSel(
			m_List.AddString(str),
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


void CShowHideDlg::OnShowAll() 
{
	for (int i=0; i<m_List.GetCount(); i++)
	{
		m_List.SetSel(i, TRUE);
	}

	// Update
	OnSelchangeConstList();
}

void CShowHideDlg::OnHideAll() 
{
	for (int i=0; i<m_List.GetCount(); i++)
	{
		m_List.SetSel(i, FALSE);
	}

	// Update
	OnSelchangeConstList();
}

void CShowHideDlg::OnInvert() 
{
	for (int i=0; i<m_List.GetCount(); i++)
	{
		if (m_List.GetSel(i) == TRUE)
			m_List.SetSel(i, FALSE);
		else
			m_List.SetSel(i, TRUE);
	}

	// Update
	OnSelchangeConstList();
}
