//===========================================================================
// MgrStarfield.cpp
//
// CMgrStarfield
//   manager class for starfield functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrStarfield.h"

#include "DlgLocation.h"
#include "DlgTime.h"
#include "DlgOptionsStar.h"
#include "DlgOptionsConst.h"
#include "DlgOptionsSun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrStarfield::CMgrStarfield()
{
}

CMgrStarfield::~CMgrStarfield()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

CBarStarf* CMgrStarfield::GetStarfBar()
{
	return GetFrame()->GetStarfBar();
}

// Open the star options dialog
void CMgrStarfield::StarOptions()
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

// Open the constellation options dialog
void CMgrStarfield::ConstOptions()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgOptionsConst dialog;
	if( dialog.DoModal() == IDOK )
	{
		// Change constellation settings
		starfield.SetConstsVisible( dialog.visible );
		starfield.SetConstsLabeled( dialog.labeled );
		optionsMgr.SetConstStarsColored( dialog.starsColored );
	}
	else
	{
		// Reset colors (they are updated in realtime)
		optionsMgr.SetConstNormColor( dialog.origNormColor );
		optionsMgr.SetConstSelColor( dialog.origSelColor );
		optionsMgr.SetConstActiveColor( dialog.origActiveColor );
		optionsMgr.SetConstStarColor( dialog.origStarColor );
	}
	Redraw();
}

// Open the sun options dialog
void CMgrStarfield::SunOptions()
{
	CDlgOptionsSun dialog;
	if( dialog.DoModal() == IDOK )
	{
		// Change constellation settings
		starfield.SetSunVisible( dialog.visible );
		starfield.SetSunShine( dialog.sunshine );
	}
	Redraw();
}

// Toggle stars on and off
void CMgrStarfield::ToggleStars()
{
	starfield.SwitchStarsVisible();
}

// Toggle constellations on and off
void CMgrStarfield::ToggleConsts()
{
	starfield.SwitchConstsVisible();
}

// Toggle sun on and off
void CMgrStarfield::ToggleSun()
{
///	starfield.SwitchSunVisible();
}

// Turns starfield spinning on/off
void CMgrStarfield::Rotate()
{
	starfield.SwitchSpinning();
}

/// Open the location dialog
void CMgrStarfield::Location()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgLocation dialog;

	dialog.DoModal();	
}

/// Open the time dialog
void CMgrStarfield::Time()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgTime dialog;
	dialog.DoModal();
}

