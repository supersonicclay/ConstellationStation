//===========================================================================
// MgrOptions.cpp
//
// CMgrOptions
//   contains settings that are local to each machine
//   (not saved in document).
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
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
	LoadSunDefaults();
	LoadTerrDefaults();
}

void CMgrOptions::LoadStarDefaults()
{
	starfield.LoadStarDefaults();
	starsGamma = DEF_STARS_GAMMA;
	starsContrast = DEF_STARS_CONTRAST;
	starsTextured = DEF_STARS_TEXTURED;
	starsColored = DEF_STARS_COLORED;
}

void CMgrOptions::LoadConstDefaults()
{
	starfield.LoadConstDefaults();
	constNormColor = DEF_CONST_NORMCOLOR;
	constSelColor = DEF_CONST_SELCOLOR;
	constActiveColor = DEF_CONST_ACTIVECOLOR;
	constStarColor = DEF_CONST_STARCOLOR;
	constStarsColored = DEF_CONST_STARSCOLORED;
}

void CMgrOptions::LoadSunDefaults()
{
	starfield.LoadSunDefaults();
}

void CMgrOptions::LoadTerrDefaults()
{
	terrVisible = DEF_TERR_VISIBLE;
	terrTextured = DEF_TERR_TEXTURED;
	terrRoughness = DEF_TERR_ROUGHNESS;
	terrScale = DEF_TERR_SCALE;
	terrIters = DEF_TERR_ITERS;
	terrSeason = DEF_TERR_SEASON;
	terrWinColor = DEF_TERR_WINCOLOR;
	terrSprColor = DEF_TERR_SPRCOLOR;
	terrSumColor = DEF_TERR_SUMCOLOR;
	terrFalColor = DEF_TERR_FALCOLOR;
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
color_s		CMgrOptions::GetConstStarColor()		{	return constStarColor;		}
BOOL		CMgrOptions::AreConstStarsColored()		{	return constStarsColored;	}
BOOL		CMgrOptions::IsTerrVisible()			{	return terrVisible;			}
BOOL		CMgrOptions::IsTerrTextured()			{	return terrTextured;		}
float		CMgrOptions::GetTerrRoughness()			{	return terrRoughness;		}
int			CMgrOptions::GetTerrScale()				{	return terrScale;			}
int			CMgrOptions::GetTerrIters()				{	return terrIters;			}
season_e	CMgrOptions::GetTerrSeason()			{	return terrSeason;			}
color_s		CMgrOptions::GetTerrWinColor()			{	return terrWinColor;		}
color_s		CMgrOptions::GetTerrSprColor()			{	return terrSprColor;		}
color_s		CMgrOptions::GetTerrSumColor()			{	return terrSumColor;		}
color_s		CMgrOptions::GetTerrFalColor()			{	return terrFalColor;		}

// Get terrain color for the current season
color_s CMgrOptions::GetTerrColor()
{
	if( terrSeason == season_Winter )
		return terrWinColor;
	else if( terrSeason == season_Spring )
		return terrSprColor;
	else if( terrSeason == season_Summer )
		return terrSumColor;
	else
		return terrFalColor;
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CMgrOptions::SetStarsGamma( int g )			{	starsGamma = g;				}
void CMgrOptions::SetStarsContrast( int c )			{	starsContrast = c;			}
void CMgrOptions::SetStarsTextured( BOOL t )		{	starsTextured = t;			}
void CMgrOptions::SetStarsColored( BOOL c )			{	starsColored = c;			}
void CMgrOptions::SetConstNormColor( color_s c )	{	constNormColor = c;			}
void CMgrOptions::SetConstSelColor( color_s c )		{	constSelColor = c;			}
void CMgrOptions::SetConstActiveColor( color_s c )	{	constActiveColor = c;		}
void CMgrOptions::SetConstStarColor( color_s c )	{	constStarColor = c;			}
void CMgrOptions::SetConstStarsColored( BOOL x )	{	constStarsColored = x;		}
void CMgrOptions::SwitchTerrVisible()				{	terrVisible = !terrVisible;	}
void CMgrOptions::SetTerrVisible( BOOL x )			{	terrVisible = x;			}
void CMgrOptions::SetTerrTextured( BOOL t )			{	terrTextured = t;			}
void CMgrOptions::SetTerrRoughness( float r )		{	terrRoughness = r;			}
void CMgrOptions::SetTerrScale( int s )				{	terrScale = s;				}
void CMgrOptions::SetTerrIters( int i )				{	terrIters = i;				}
void CMgrOptions::SetTerrSeason( season_e s )		{	terrSeason = s;				}
void CMgrOptions::SetTerrWinColor( color_s c )		{	terrWinColor = c;			}
void CMgrOptions::SetTerrSprColor( color_s c )		{	terrSprColor = c;			}
void CMgrOptions::SetTerrSumColor( color_s c )		{	terrSumColor = c;			}
void CMgrOptions::SetTerrFalColor( color_s c )		{	terrFalColor = c;			}

// Set terrain color for the current season
void CMgrOptions::SetTerrColor( color_s c )
{
	if( terrSeason == season_Winter )
		terrWinColor = c;
	else if( terrSeason == season_Spring )
		terrSprColor = c;
	else if( terrSeason == season_Summer )
		terrSumColor = c;
	else
		terrFalColor = c;
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Opens the general options dialog
void CMgrOptions::General()
{
	CDlgOptionsGeneral dialog;
	dialog.DoModal();
}

/// Load options from storage
void CMgrOptions::Load()
{
	CFile file;
	if( !file.Open( "ConStation.opt", CFile::modeRead ) )
	{
		CSError( "Unable to open options file.\nLoading default options." );
		LoadDefaults();
		return;
	}

	CArchive ar( &file, CArchive::load );
	Serialize( ar );

	ar.Close();
	file.Close();
}

/// Save options to storage
void CMgrOptions::Save()
{
	CFile file;
	if( !file.Open( "ConStation.opt", CFile::modeCreate | CFile::modeWrite ) )
	{
		CSDebug( "Unable to open options file for writing", "CMgrOptions::Save" );
		return;
	}

	CArchive ar( &file, CArchive::store );
	Serialize( ar );

	ar.Close();
	file.Close();
}

void CMgrOptions::Serialize( CArchive& ar )
{
	if( ar.IsLoading() )
	{
		try
		{
			ar

			// Star Options
			>> starsGamma
			>> starsContrast
			>> starsTextured
			>> starsColored

			// Constellation Options
			>> constNormColor
			>> constSelColor
			>> constActiveColor
			>> constStarColor
			>> constStarsColored

			// Terrain options
			>> terrVisible
			>> terrTextured
			>> terrRoughness
			>> terrScale
			>> terrIters
			>> terrSeason
			>> terrWinColor
			>> terrSprColor
			>> terrSumColor
			>> terrFalColor

			// Compass options
			>> compassColor;
		}
		catch( CException* e )
		{
			CSDebug( "Unable to read options.\nLoading default options.", "CMgrOptions::Serialize" );
			LoadDefaults();
			e->Delete();
		}
	}
	else
	{
		ar

		// Star Options
		<< starsGamma
		<< starsContrast
		<< starsTextured
		<< starsColored

		// Constellation Options
		<< constNormColor
		<< constSelColor
		<< constActiveColor
		<< constStarColor
		<< constStarsColored

		// Terrain options
		<< terrVisible
		<< terrTextured
		<< terrRoughness
		<< terrScale
		<< terrIters
		<< terrSeason
		<< terrWinColor
		<< terrSprColor
		<< terrSumColor
		<< terrFalColor

		// Compass options
		<< compassColor;
	}
}
