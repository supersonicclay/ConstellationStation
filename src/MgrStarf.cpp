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
#include "DlgStarInfo.h"
#include "DlgFindTrack.h"

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

// Open Find / Track dialog
void CMgrStarf::FindTrack()
{
	CDlgFindTrack dialog;

	dialog.DoModal();
}

// Turns starfield spinning on/off
void CMgrStarf::Rotate()
{
	starfield.SwitchSpinning();
}

// Open the location dialog
void CMgrStarf::Location()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgLocation dialog;

	if( dialog.DoModal() == IDOK )
	{
		starfield.SetLocation( dialog.location );
		documentMgr.SetModified();
	}

	Redraw();
}

// Open the time dialog
void CMgrStarf::Time()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();
	if( starfield.GetSpeed() == speed_Now )
		GetStarfBar()->ChangeSpeed( speed_Realtime );
	starfMgr.Pause();

	CDlgTime dialog;
	if( dialog.DoModal() == IDOK )
	{
		starfield.SetDST( dialog.dst );
		GetStarfBar()->SetTime( dialog.lt );
		documentMgr.SetModified();
	}
}


/////////////////////////////////////////////////////////////////////////////
// Animation Methods

void CMgrStarf::ChangeStarfSpeed( speed_e x )
{
	starfield.SetSpeed(x);
	if( x == speed_Now )
		starfield.SetAnimation( animation_Forward );
	if( starfield.GetAnimation() != animation_Paused )
		GetStarfBar()->AnimationSetTimer();
}

void CMgrStarf::Pause()
{
	starfield.SetAnimation( animation_Paused );
	GetStarfBar()->KillTimer( 1 );
	if( starfield.GetSpeed() == speed_Now )
		GetStarfBar()->ChangeSpeed( speed_Realtime );
}

void CMgrStarf::Forward()
{
	starfield.SetAnimation( animation_Forward );
	GetStarfBar()->AnimationSetTimer();
}

void CMgrStarf::Reverse()
{
	starfield.SetAnimation( animation_Reverse );
	GetStarfBar()->AnimationSetTimer();
	if( starfield.GetSpeed() == speed_Now )
		GetStarfBar()->ChangeSpeed( speed_Realtime );
}

void CMgrStarf::Next()
{
	starfield.SetAnimation( animation_Paused );
	GetStarfBar()->KillTimer( 1 );
	GetStarfBar()->AnimationAdjustTime( 1 );
	if( starfield.GetSpeed() == speed_Now )
		GetStarfBar()->ChangeSpeed( speed_Realtime );
}

void CMgrStarf::Previous()
{
	starfield.SetAnimation( animation_Paused );
	GetStarfBar()->KillTimer( 1 );
	GetStarfBar()->AnimationAdjustTime( -1 );
	if( starfield.GetSpeed() == speed_Now )
		GetStarfBar()->ChangeSpeed( speed_Realtime );
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
		starfield.SetStarsDaylight( dialog.daylight );
		starfield.SetStarsLabeled( dialog.labeled );
		optionsMgr.SetStarsTextured( dialog.textured );
		optionsMgr.SetStarsColored( dialog.colored );
		optionsMgr.SetStarsSize( dialog.size );
		optionsMgr.SetStarsSContrast( dialog.sContrast );
		optionsMgr.SetStarsCContrast( dialog.cContrast );
		UpdateStarsAppearance();
	}
	else
	{
		// Reset options that are changed in realtime
		optionsMgr.SetStarsLimMagX10( dialog.origLimMagX10 );
		starfield.CountStars();
		UpdateStarsAppearance();
	}
	Redraw();
}

void CMgrStarf::StarInfo( CDataStar* star )
{
	CDlgStarInfo dialog( star );

	dialog.DoModal();
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

	for( int i=0; i<starfield.GetStarCount(); ++i )
	{
		mag = starfield.GetStar(i)->GetMag();

		// Linearly interpolate radius and color
		radius = starsBrightRadius - starsRadiusDiff * (mag-starsMinMag)/magDiff;
		alpha = starsBrightColor - starsColorDiff * (mag-starsMinMag)/magDiff;

		starfield.GetStar(i)->SetRadius( radius );
		starfield.GetStar(i)->SetAlpha( alpha );
		starfield.GetStar(i)->UpdateVerts();
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
		starfield.SetConstsDaylight( dialog.daylight );
		starfield.SetConstsLabeled( dialog.labeled );
		optionsMgr.SetConstLineWidth( dialog.lineWidth+1 );
	}
	else
	{
		// Reset options that are updated in realtime
	}
	Redraw();
}

// Toggle constellations on and off
void CMgrStarf::ToggleConsts()
{
	starfield.SwitchConstsVisible(); Redraw();
}

// Toggle constellation lines on and off
void CMgrStarf::ToggleConstsLines()
{
	starfield.SwitchConstsLinesVisible();
	SetState( state_Viewing );
	Redraw();
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