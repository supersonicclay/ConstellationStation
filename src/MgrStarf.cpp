//===========================================================================
// MgrStarf.cpp
//
// CMgrStarf
//   manager class for starfield functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrStarf.h"

#include "DlgLocation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrStarf::CMgrStarf()
{
}

CMgrStarf::~CMgrStarf()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

CBarStarf* CMgrStarf::GetStarfBar()
{
	return GetFrame()->GetStarfBar();
}

// Turns starfield spinning on/off
void CMgrStarf::Rotate()
{
	starfield.SwitchSpinning();
}

/// Opens the location dialog
void CMgrStarf::Location()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgLocation dialog;

	dialog.DoModal();	
}

/// Opens the time dialog
void CMgrStarf::Time()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

///	CDlgTime dialog;

///	dialog.DoModal();
}

