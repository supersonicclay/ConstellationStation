//===========================================================================
// DlgShowHide.cpp
//
// CDlgShowHide
//   show / hide list dialog
//===========================================================================

#include "stdafx.h"
#include "ConStation.h"
#include "DlgShowHide.h"

#include "Constellation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
}


void CDlgShowHide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHide)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowHide, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHide)
	ON_LBN_SELCHANGE(IDC_CONST_LIST, OnSelChange)
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
	
	VERIFY(list.SubclassDlgItem(IDC_CONST_LIST, this));

	CString str;

	// Add strings to list box
	for (int i=0; i<starfield.GetNumConstellations(); i++)
	{
		// Get name
		str = starfield.GetConstellation(i)->GetName();

		// If this constellation is current
		if (i == starfield.GetNumCurConstellation())
			str += " <--";

		// Add name to list
		list.SetSel(
			list.AddString(str),
			starfield.GetConstellation(i)->IsVisible());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgShowHide::OnSelChange() 
{
	for (int i=0; i<starfield.GetNumConstellations(); i++)
	{
		starfield.GetConstellation(i)->SetVisible(list.GetSel(i));
	}

	Redraw();
}


void CDlgShowHide::OnShowAll() 
{
	for (int i=0; i<list.GetCount(); i++)
	{
		list.SetSel(i, TRUE);
	}

	// Update
	OnSelChange();
}

void CDlgShowHide::OnHideAll() 
{
	for (int i=0; i<list.GetCount(); i++)
	{
		list.SetSel(i, FALSE);
	}

	// Update
	OnSelChange();
}

void CDlgShowHide::OnInvert() 
{
	for (int i=0; i<list.GetCount(); i++)
	{
		if (list.GetSel(i) == TRUE)
			list.SetSel(i, FALSE);
		else
			list.SetSel(i, TRUE);
	}

	// Update
	OnSelChange();
}
