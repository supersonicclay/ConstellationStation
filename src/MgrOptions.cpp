//===========================================================================
// MgrOptions.cpp
//
// CMgrOptions
//   description.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrOptions.h"

#include "DlgOptionsGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL( CMgrOptions, CObject, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrOptions::CMgrOptions()
{
	LoadDefaults();
}

CMgrOptions::~CMgrOptions()
{
}

void CMgrOptions::LoadDefaults()
{
	LoadStarDefaults();
	LoadConstDefaults();
	LoadTerrDefaults();
	LoadCompassDefaults();
}

void CMgrOptions::LoadStarDefaults()
{
	starsGamma = DEF_STARS_GAMMA;
	starsContrast = DEF_STARS_CONTRAST;
	starsTextured = DEF_STARS_TEXTURED;
	starsColored = DEF_STARS_COLORED;
}

void CMgrOptions::LoadConstDefaults()
{
	constNormColor = DEF_CONST_NORMCOLOR;
	constSelColor = DEF_CONST_SELCOLOR;
	constActiveColor = DEF_CONST_ACTIVECOLOR;
}

void CMgrOptions::LoadTerrDefaults()
{
	terrRoughness = DEF_TERR_ROUGHNESS;
	terrTextured = DEF_TERR_TEXTURED;
	terrSeason = DEF_TERR_SEASON;
	terrColor = DEF_TERR_COLOR;
}

void CMgrOptions::LoadCompassDefaults()
{
	compassColor = DEF_COMPASS_COLOR;
}


/////////////////////////////////////////////////////////////////////////////
// Gets
int			CMgrOptions::GetStarsGamma()			{	return starsGamma;			}
int			CMgrOptions::GetStarsContrast()			{	return starsContrast;		}
BOOL		CMgrOptions::AreStarsTextured()			{	return starsTextured;		}
BOOL		CMgrOptions::AreStarsColored()			{	return starsColored;		}
color_s		CMgrOptions::GetConstNormColor()		{	return constNormColor;		}
color_s		CMgrOptions::GetConstSelColor()			{	return constSelColor;		}
color_s		CMgrOptions::GetConstActiveColor()		{	return constActiveColor;	}
float		CMgrOptions::GetTerrRoughness()			{	return terrRoughness;		}
BOOL		CMgrOptions::IsTerrTextured()			{	return terrTextured;		}
season_e	CMgrOptions::GetTerrSeason()			{	return terrSeason;			}
color_s		CMgrOptions::GetTerrColor()				{	return terrColor;			}
color_s		CMgrOptions::GetCompassColor()			{	return compassColor;		}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CMgrOptions::SetStarsGamma( int g )			{	starsGamma = g;			}
void CMgrOptions::SetStarsContrast( int c )			{	starsContrast = c;		}
void CMgrOptions::SetStarsTextured( BOOL t )		{	starsTextured = t;		}
void CMgrOptions::SetStarsColored( BOOL c )			{	starsColored = c;		}
void CMgrOptions::SetConstNormColor( color_s c )	{	constNormColor = c;		}
void CMgrOptions::SetConstSelColor( color_s c )		{	constSelColor = c;		}
void CMgrOptions::SetConstActiveColor( color_s c )	{	constActiveColor = c;	}
void CMgrOptions::SetTerrRoughness( float r )		{	terrRoughness = r;		}
void CMgrOptions::SetTerrTextured( BOOL t )			{	terrTextured = t;		}
void CMgrOptions::SetTerrSeason( season_e s )		{	terrSeason = s;			}
void CMgrOptions::SetTerrColor( color_s c )			{	terrColor = c;			}
void CMgrOptions::SetCompassColor( color_s c )		{	compassColor = c;		}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Opens the general options dialog
void CMgrOptions::General()
{
	CDlgOptionsGeneral dialog;
	dialog.DoModal();
}


void CMgrOptions::Serialize( CArchive& ar )
{
	/* ///Wait until everythings done
	if( ar.IsLoading() )
		ar >> starsGamma >> starsContrast >> starsTextured >> starsColored
		   >> constNormColor.r >> constNormColor.g >> constNormColor.b
		   >> constSelColor.r >> constSelColor.g >> constSelColor.b
		   >> constActiveColor.r >> constActiveColor.g >> constActiveColor.b
		   >> terrRoughness >> terrTextured
		   >> terrColor.r >> terrColor.g >> terrColor.b
		   >> compassColor.r >> compassColor.g >> compassColor.b;
	else
		ar << starsGamma << starsContrast << starsTextured << starsColored
		   << constNormColor.r << constNormColor.g << constNormColor.b
		   << constSelColor.r << constSelColor.g << constSelColor.b
		   << constActiveColor.r << constActiveColor.g << constActiveColor.b
		   << terrRoughness << terrTextured 
		   << terrColor.r << terrColor.g << terrColor.b
		   << compassColor.r << compassColor.g << compassColor.b;
	*/
}
