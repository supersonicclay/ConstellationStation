//===========================================================================
// MgrStars.cpp
//
// CMgrStars
//   manager class for star functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrStars.h"

#include "DlgOptionsStar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrStars::CMgrStars()
{
}

CMgrStars::~CMgrStars()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Opens the star options dialog
void CMgrStars::Options()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgOptionsStar dialog;
	if( dialog.DoModal() == IDOK )
	{
		// Change star settings
		starfield.SetStarsVisible( dialog.visible );
		starfield.SetStarsLabeled( dialog.labeled );
		optionsMgr.SetStarsTextured( dialog.textured );
		optionsMgr.SetStarsColored( dialog.colored );
		starfield.SetLimitingMag( dialog.limitingMag / 10.0f );
	}
	else
	{
		// Reset brightness and contrast (they are updated in realtime)
		optionsMgr.SetStarsGamma( dialog.origGamma );
		optionsMgr.SetStarsContrast( dialog.origContrast );
	}
	Redraw();
}

// Toggles stars on and off
void CMgrStars::Toggle()
{
	starfield.SwitchStarsVisible(); Redraw();
}

