//===========================================================================
// MgrConst.cpp
//
// CMgrConst
//   manager class for constellations functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrConst.h"

#include "DlgConstName.h"
#include "DlgShowHide.h"
#include "DlgOptionsConst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrConst::CMgrConst()
{
}

CMgrConst::~CMgrConst()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

CBarConst* CMgrConst::GetConstBar()
{
	return GetFrame()->GetConstBar();
}

// Prompt user for a name and add a constellation
void CMgrConst::Add()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgConstName dialog;

	// Set name initially to "Constellation"
	CString constName = "Constellation";

	// The total number of created constellaitons (starting at 1)
	const int numNewConstellations = starfield.GetNumNewConstellations();

	// Convert the number to a string and append
	char numString[20];
	itoa (numNewConstellations+1, numString, 10);
	constName += numString;

	dialog.name = constName;

	// If they cancel, return
	if( dialog.DoModal() != IDOK )
		return;

	// Check for duplicate name
	while (starfield.IsDuplicate(dialog.name))
	{
		CSWarn( "There is already a constellation with this name." );

		if (dialog.DoModal() != IDOK)
			return;
	}

	// Add constellation and make it the current constellation
	GetConstBar()->AddConst(dialog.name);
	starfield.AddConstellation(dialog.name);
	starfield.IncNumNewConstellations();
	starfield.SetCurConstellation(dialog.name);

	starfield.SetModified();
	Redraw();
}

// Delete the current constellation
void CMgrConst::Delete()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	if( CSQuestion("Are you sure you want to delete this constellation?") == IDNO )
		return;

	starfield.DeleteConstellation();
	GetConstBar()->DeleteConst();

	// Set newly selected constellation as the current one
	if (starfield.GetNumConstellations() > 0)
		starfield.SetCurConstellation( GetConstBar()->GetCurConst() );

	SetState( state_Viewing );

	starfield.SetModified();
	Redraw();
}

// Rename the current constellation
void CMgrConst::Rename()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgConstName dialog;

	CString origConstName = GetConstBar()->GetCurConst();
	dialog.name = origConstName;

	// If they cancel, return
	if (dialog.DoModal() != IDOK)
		return;

	// Check for duplicate name
	while (starfield.IsDuplicate(dialog.name) &&
		dialog.name != origConstName)
	{
		CSWarn("There is already a constellation with this name.");

		if (dialog.DoModal() != IDOK)
			return;
	}

	// If it wasn't renamed
	if (dialog.name == origConstName)
		return;

	// Otherwise Rename constellation

	// Remove old name from the list and add new name
	GetConstBar()->DeleteConst();
	GetConstBar()->AddConst(dialog.name);

	starfield.RenameConstellation(dialog.name);

	starfield.SetModified();
}

// Hide the current constellation
void CMgrConst::Hide()
{
	starfield.GetCurConstellation()->SwitchVisible();

	starfield.SetModified();
	Redraw();
}

// Set state to AddingLine or back to Viewing
void CMgrConst::AddLine()
{
	if (state == state_AddingLine)
		SetState( state_Viewing );
	else
		SetState( state_AddingLine );
}

// Set state to DeletingLine or back to Viewing
void CMgrConst::DeleteLine()
{
	if (state == state_DeletingLine)
		SetState( state_Viewing );
	else
		SetState( state_DeletingLine );
}

// Hide all constellations
void CMgrConst::HideAll()
{
	for (int i=0; i<starfield.GetNumConstellations(); i++)
	{
		starfield.GetConstellation(i)->SetVisible(FALSE);
	}

	starfield.SetModified();
	Redraw();
}

// Show all constellations
void CMgrConst::ShowAll()
{
	for (int i=0; i<starfield.GetNumConstellations(); i++)
	{
		starfield.GetConstellation(i)->SetVisible(TRUE);
	}

	starfield.SetModified();
	Redraw();
}

// Display show/hide dialog
void CMgrConst::ShowHide()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgShowHide dialog;

	dialog.DoModal();

	starfield.SetModified();
	SetState( state_Viewing );
}


