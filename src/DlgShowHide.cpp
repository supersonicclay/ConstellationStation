// ShowHideDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConStation.h"
#include "DlgShowHide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "Constellation.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHide dialog


CDlgShowHide::CDlgShowHide(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowHide::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowHide)
	//}}AFX_DATA_INIT
}

CDlgShowHide::~CDlgShowHide()
{
	delete[] constellations;
}


void CDlgShowHide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHide)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowHide, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHide)
	ON_LBN_SELCHANGE(IDC_CONST_LIST, OnSelchangeConstList)
	ON_BN_CLICKED(IDC_SHOWALL, OnShowAll)
	ON_BN_CLICKED(IDC_HIDEALL, OnHideAll)
	ON_BN_CLICKED(IDC_INVERT, OnInvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgShowHide message handlers

BOOL CDlgShowHide::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	VERIFY(m_List.SubclassDlgItem(IDC_CONST_LIST, this));


	constellations = starfield->GetConstellations();
	constellationCount = starfield->GetNumConstellations();
	curConstellationNum = starfield->GetNumCurConstellation();

	CString str;

	// Add strings to list box
	for (int i=0; i<constellationCount; i++)
	{
		// Get name
		str = constellations[i].GetName();

		// If this constellation is current
		if (i == curConstellationNum)
			str += " <--";

		// Add name to list
		m_List.SetSel(
			m_List.AddString(str),
			constellations[i].IsVisible());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgShowHide::OnSelchangeConstList() 
{
	for (int i=0; i<constellationCount; i++)
	{
		constellations[i].SetVisible(m_List.GetSel(i));
	}

	RedrawView();
}


void CDlgShowHide::OnShowAll() 
{
	for (int i=0; i<m_List.GetCount(); i++)
	{
		m_List.SetSel(i, TRUE);
	}

	// Update
	OnSelchangeConstList();
}

void CDlgShowHide::OnHideAll() 
{
	for (int i=0; i<m_List.GetCount(); i++)
	{
		m_List.SetSel(i, FALSE);
	}

	// Update
	OnSelchangeConstList();
}

void CDlgShowHide::OnInvert() 
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
