//===========================================================================
// MgrStarf.cpp
//
// CMgrStarf
//   manager class for starfield functions.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "MgrStarf.h"

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

CMgrStarf::CMgrStarf()
{
}

CMgrStarf::~CMgrStarf()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

/////////////////////////////////////////////////////////////////////////////
// Gets

CBarStarf*	CMgrStarf::GetStarfBar()			{	return GetFrame()->GetStarfBar();	}
float		CMgrStarf::GetStarsDimRadius()		{	return starsDimRadius;				}
float		CMgrStarf::GetStarsBrightRadius()	{	return starsBrightRadius;			}
float		CMgrStarf::GetStarsDimColor()		{	return starsDimColor;				}
float		CMgrStarf::GetStarsBrightColor()	{	return starsBrightColor;			}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CMgrStarf::SetStarsDimRadius( float x )	{	starsDimRadius = x;		}
void CMgrStarf::SetStarsBrightRadius( float x )	{	starsBrightRadius = x;	}
void CMgrStarf::SetStarsDimColor( float x )		{	starsDimColor = x;		}
void CMgrStarf::SetStarsBrightColor( float x )	{	starsBrightColor = x;	}


/////////////////////////////////////////////////////////////////////////////
// Starfield Methods

// Find the specified star
void CMgrStarf::Find( CDataStar* star )
{
	starfield.Find( star->GetX(), star->GetY(), star->GetZ() );
}

// Find the specified constellation
void CMgrStarf::Find( CDataConst* constellation )
{
	/// Average all stars
}

// Track the specified star
void CMgrStarf::StartTracking( CDataStar* star )
{
	starfield.StartTracking( star->GetX(), star->GetY(), star->GetZ() );
}

// Track the specified constellation
void CMgrStarf::StartTracking( CDataConst* constellation )
{
	/// Average all stars
}

// Turns starfield spinning on/off
void CMgrStarf::Rotate()
{
	starfield.SwitchSpinning();
}

/// Open the location dialog
void CMgrStarf::Location()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgLocation dialog;

	dialog.DoModal();	
}

/// Open the time dialog
void CMgrStarf::Time()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgTime dialog;
	dialog.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// Star Methods

// Open the star options dialog
void CMgrStarf::StarOptions()
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
	}
	else
	{
		// Reset options that are changed in realtime
		optionsMgr.SetStarsLimMagX10( dialog.origLimMagX10 );
		optionsMgr.SetStarsSize( dialog.origSize );
		optionsMgr.SetStarsSContrast( dialog.origSContrast );
		optionsMgr.SetStarsCContrast( dialog.origCContrast );
		starfield.CountStars();
		UpdateStarsAppearance();
	}
	Redraw();
}

// Toggle stars on and off
void CMgrStarf::ToggleStars()
{
	starfield.SwitchStarsVisible(); Redraw();
}

// Update the radius and color of all stars
void CMgrStarf::UpdateStarsAppearance()
{
	float mag, radius, alpha;
	color_s color;

	// Brightest color is always max
	starsBrightColor = MAX_STARS_BRIGHT_COLOR;

	// Calculate radius for brightest star
	starsBrightRadius = MIN_STARS_BRIGHT_RADIUS +
		STARS_BRIGHT_RADIUS_RANGE * optionsMgr.GetStarsSize() / 100.0f;

	// Calculate percentage of brightest radius to be dimmest radius
	starsDimRadiusPerc = MAX_STARS_DIM_RADIUS_PERC -
		STARS_DIM_RADIUS_PERC_RANGE * optionsMgr.GetStarsSContrast() / 100.0f;

	// Calculate percentage of brightest color to be dimmest color
	starsDimColorPerc = MAX_STARS_DIM_COLOR_PERC -
		STARS_DIM_COLOR_PERC_RANGE * optionsMgr.GetStarsCContrast() / 100.0f;

	// Calculate actual dimmest radius and color
	starsDimRadius = starsBrightRadius * starsDimRadiusPerc / 100.0f;
	starsDimColor = starsBrightColor * starsDimColorPerc / 100.0f;

	// Calculate difference of the brightest and dimmest radius and color
	float starsRadiusDiff = starsBrightRadius - starsDimRadius;
	float starsColorDiff = starsBrightColor - starsDimColor;

	// Calculate magnitude information
	float starsMinMag = MIN_STARS_MAG;
	float starsMaxMag = optionsMgr.GetStarsLimMag();
	float magDiff = starsMaxMag - starsMinMag;

	/// min/max rad/color check
	float minRadius2=10, maxRadius2=0;
	float minColor2=10, maxColor2=0;

	for( int i=0; i<starfield.GetStarCount(); ++i )
	{
		mag = starfield.GetStar(i)->GetMag();

		// Linearly interpolate radius and color
		radius = starsBrightRadius - starsRadiusDiff * (mag-starsMinMag)/magDiff;
		alpha = starsBrightColor - starsColorDiff * (mag-starsMinMag)/magDiff;
		color.r = alpha;
		color.g = alpha;
		color.b = alpha;

		starfield.GetStar(i)->SetRadius( radius );
		starfield.GetStar(i)->SetColor( color );

		/// min/max rad/color check
		if( starfield.GetStar(i)->GetRadius() < minRadius2 )
			minRadius2 = starfield.GetStar(i)->GetRadius();
		if( starfield.GetStar(i)->GetRadius() > maxRadius2 )
			maxRadius2 = starfield.GetStar(i)->GetRadius();

		if( starfield.GetStar(i)->GetColor().r < minColor2 )
			minColor2 = starfield.GetStar(i)->GetColor().r;
		if( starfield.GetStar(i)->GetColor().r > maxColor2 )
			maxColor2 = starfield.GetStar(i)->GetColor().r;
		
	}
}


/////////////////////////////////////////////////////////////////////////////
// Constellation Methods

// Open the constellation options dialog
void CMgrStarf::ConstOptions()
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

// Toggle constellations on and off
void CMgrStarf::ToggleConsts()
{
	starfield.SwitchConstsVisible(); Redraw();
}


/////////////////////////////////////////////////////////////////////////////
// Sun Methods

// Open the sun options dialog
void CMgrStarf::SunOptions()
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

// Toggle sun on and off
void CMgrStarf::ToggleSun()
{
	starfield.SwitchSunVisible(); Redraw();
}

// Toggle sunshine on and off
void CMgrStarf::ToggleSunshine()
{
	starfield.SwitchSunShine(); Redraw();
}