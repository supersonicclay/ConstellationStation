//===========================================================================
// DlgShowHide.cpp
//
// CDlgShowHide
//   show / hide constellation list dialog.
//===========================================================================

#include "stdafx.h"
#include "CSApp.h"
#include "DlgShowHide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
	DDX_Control(pDX, IDC_CONST_LIST, list);
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
	
	// Add strings to list box
	for (int i=0; i<starfield.GetConstCount(); ++i)
	{
		// Add name to list
		list.SetSel(
			list.AddString( starfield.GetConst(i)->GetName() ),
			starfield.GetConst(i)->IsVisible() );
	}

	return TRUE;
}

void CDlgShowHide::OnSelChange() 
{
	CString name;

	for (int i=0; i<starfield.GetConstCount(); ++i)
	{
		// Get name of constellation
		list.GetText( i, name );

		// Set visibility of constellation
		starfield.GetConst( name )->SetVisible( list.GetSel(i) );
	}

	Redraw();
}

void CDlgShowHide::OnShowAll() 
{
	for (int i=0; i<list.GetCount(); ++i)
	{
		list.SetSel(i, TRUE);
	}

	// Update
	OnSelChange();
}

void CDlgShowHide::OnHideAll() 
{
	for (int i=0; i<list.GetCount(); ++i)
	{
		list.SetSel(i, FALSE);
	}

	// Update
	OnSelChange();
}

void CDlgShowHide::OnInvert() 
{
	for (int i=0; i<list.GetCount(); ++i)
	{
		if (list.GetSel(i) == TRUE)
			list.SetSel(i, FALSE);
		else
			list.SetSel(i, TRUE);
	}

	// Update
	OnSelChange();
}
