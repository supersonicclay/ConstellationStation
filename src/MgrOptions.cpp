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
#include "DlgOptionsColor.h"

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
}

CMgrOptions::~CMgrOptions()
{
}

void CMgrOptions::LoadDefaults()
{
	LoadLocationDefaults();
	LoadStarDefaults();
	LoadConstDefaults();
	LoadSunDefaults();
	LoadTerrDefaults();
	LoadColorDefaults();
	LoadTextDefaults();
}

void CMgrOptions::LoadLocationDefaults()
{
	locationHome = DEF_LOCATION_HOME;
}

void CMgrOptions::LoadStarDefaults()
{
	starfield.LoadStarDefaults();
	starsTextured = DEF_STARS_TEXTURED;
	starsColored = DEF_STARS_COLORED;
	starsLimMagX10 = DEF_STARS_LIMMAGX10;
	starsSize = DEF_STARS_SIZE;
	starsSContrast = DEF_STARS_SCONTRAST;
	starsCContrast = DEF_STARS_CCONTRAST;

	/// STAR DIFFERENCE DEFAULTS
	starfMgr.SetStarsDimRadius( DEF_STARS_BRIGHT_RADIUS - DEF_STARS_RADIUS_DIFF );
	starfMgr.SetStarsBrightRadius( DEF_STARS_BRIGHT_RADIUS );
	starfMgr.SetStarsDimColor( DEF_STARS_BRIGHT_COLOR - DEF_STARS_COLOR_DIFF );
	starfMgr.SetStarsBrightColor( DEF_STARS_BRIGHT_COLOR );
}

void CMgrOptions::LoadConstDefaults()
{
	starfield.LoadConstDefaults();
	constLineWidth = DEF_CONST_LINEWIDTH;
}

void CMgrOptions::LoadSunDefaults()
{
	starfield.LoadSunDefaults();
}

void CMgrOptions::LoadTerrDefaults()
{
	terrVisible = DEF_TERR_VISIBLE;
	terrTextured = DEF_TERR_TEXTURED;
	terrRoughnessX100 = DEF_TERR_ROUGHNESSX100;
	terrScale = DEF_TERR_SCALE;
	terrTexIters = DEF_TERR_TEX_ITERS;
	terrHeightIters = DEF_TERR_HEIGHT_ITERS;
	terrViewHeight = DEF_TERR_VIEW_HEIGHT;
	terrSeason = DEF_TERR_SEASON;
	terrWinColor = DEF_TERR_WINCOLOR;
	terrSprColor = DEF_TERR_SPRCOLOR;
	terrSumColor = DEF_TERR_SUMCOLOR;
	terrAutColor = DEF_TERR_FALCOLOR;

	terrain.MakeTerrain( TRUE );
}

void CMgrOptions::LoadColorDefaults()
{
	starsColored = DEF_STARS_COLORED;
	constNormColor = DEF_CONST_NORMCOLOR;
	constSelColor = DEF_CONST_SELCOLOR;
	constActiveColor = DEF_CONST_ACTIVECOLOR;
	constStarColor = DEF_CONST_STARCOLOR;
	textConstColor = DEF_TEXT_CONSTCOLOR;
	textConstSelColor = DEF_TEXT_CONSTSELCOLOR;
	textStarColor = DEF_TEXT_STARCOLOR;
	textDirColor = DEF_TEXT_DIRCOLOR;
}

void CMgrOptions::LoadTextDefaults()
{
	textConstFont = DEF_TEXT_CONSTFONT;
	textStarFont = DEF_TEXT_STARFONT;
	textDirFont = DEF_TEXT_DIRFONT;

	// Rebuild fonts
	textMgr.BuildFonts();
}


/////////////////////////////////////////////////////////////////////////////
// Gets
location_s	CMgrOptions::GetLocationHome()			{	return locationHome;			}
BOOL		CMgrOptions::AreStarsTextured()			{	return starsTextured;			}
BOOL		CMgrOptions::AreStarsColored()			{	return starsColored;			}
float		CMgrOptions::GetStarsLimMag()			{	return starsLimMagX10 / 10.0f;	}
int			CMgrOptions::GetStarsLimMagX10()		{	return starsLimMagX10;			}
int			CMgrOptions::GetStarsSize()				{	return starsSize;				}
int			CMgrOptions::GetStarsSContrast()		{	return starsSContrast;			}
int			CMgrOptions::GetStarsCContrast()		{	return starsCContrast;			}

color_s		CMgrOptions::GetConstNormColor()		{	return constNormColor;			}
color_s		CMgrOptions::GetConstSelColor()			{	return constSelColor;			}
color_s		CMgrOptions::GetConstActiveColor()		{	return constActiveColor;		}
color_s		CMgrOptions::GetConstStarColor()		{	return constStarColor;			}
int			CMgrOptions::GetConstLineWidth()		{	return constLineWidth;			}

BOOL		CMgrOptions::IsTerrVisible()			{	return terrVisible;				}
BOOL		CMgrOptions::IsTerrTextured()			{	return terrTextured;			}
int			CMgrOptions::GetTerrRoughnessX100()		{	return terrRoughnessX100;		}
float		CMgrOptions::GetTerrRoughness()			{	return terrRoughnessX100/100.0f;}
int			CMgrOptions::GetTerrScale()				{	return terrScale;				}
int			CMgrOptions::GetTerrTexIters()			{	return terrTexIters;			}
int			CMgrOptions::GetTerrHeightIters()		{	return terrHeightIters;			}
float		CMgrOptions::GetTerrViewHeight()		{	return terrViewHeight;			}
season_e	CMgrOptions::GetTerrSeason()			{	return terrSeason;				}
color_s		CMgrOptions::GetTerrWinColor()			{	return terrWinColor;			}
color_s		CMgrOptions::GetTerrSprColor()			{	return terrSprColor;			}
color_s		CMgrOptions::GetTerrSumColor()			{	return terrSumColor;			}
color_s		CMgrOptions::GetTerrAutColor()			{	return terrAutColor;			}

LOGFONT		CMgrOptions::GetTextConstFont()			{	return textConstFont;			}
LOGFONT		CMgrOptions::GetTextStarFont()			{	return textStarFont;			}
LOGFONT		CMgrOptions::GetTextDirFont()			{	return textDirFont;				}
color_s		CMgrOptions::GetTextConstColor()		{	return textConstColor;			}
color_s		CMgrOptions::GetTextConstSelColor()		{	return textConstSelColor;		}
color_s		CMgrOptions::GetTextStarColor()			{	return textStarColor;			}
color_s		CMgrOptions::GetTextDirColor()			{	return textDirColor;			}

// Get terrain color for the current season
color_s CMgrOptions::GetTerrColor()
{
	switch( terrSeason )
	{
	case season_Winter:
		return terrWinColor; break;
	case season_Spring:
		return terrSprColor; break;
	case season_Summer:
		return terrSumColor; break;
	case season_Autumn:
		return terrAutColor; break;
	default:
		return COLOR_WHITE;  break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CMgrOptions::SetLocationHome( location_s x )	{	locationHome = x;			}
void CMgrOptions::SetStarsTextured( BOOL t )		{	starsTextured = t;			}
void CMgrOptions::SetStarsColored( BOOL c )			{	starsColored = c;			}
void CMgrOptions::SetStarsLimMagX10( int x )		{	starsLimMagX10 = x;			}
void CMgrOptions::SetStarsSize( int g )				{	starsSize = g;				}
void CMgrOptions::SetStarsSContrast( int c )		{	starsSContrast = c;			}
void CMgrOptions::SetStarsCContrast( int c )		{	starsCContrast = c;			}

void CMgrOptions::SetConstNormColor( color_s c )	{	constNormColor = c;			}
void CMgrOptions::SetConstSelColor( color_s c )		{	constSelColor = c;			}
void CMgrOptions::SetConstActiveColor( color_s c )	{	constActiveColor = c;		}
void CMgrOptions::SetConstStarColor( color_s c )	{	constStarColor = c;			}
void CMgrOptions::SetConstLineWidth( int w )		{	constLineWidth = w;			}

void CMgrOptions::SwitchTerrVisible()				{	terrVisible = !terrVisible;	}
void CMgrOptions::SetTerrVisible( BOOL x )			{	terrVisible = x;			}
void CMgrOptions::SetTerrTextured( BOOL t )			{	terrTextured = t;			}
void CMgrOptions::SetTerrRoughnessX100( int r )		{	terrRoughnessX100 = r;		}
void CMgrOptions::SetTerrScale( int s )				{	terrScale = s;				}
void CMgrOptions::SetTerrTexIters( int i )			{	terrTexIters = i;			}
void CMgrOptions::SetTerrHeightIters( int i )		{	terrHeightIters = i;		}
void CMgrOptions::SetTerrViewHeight( float x )		{	terrViewHeight = x;			}
void CMgrOptions::SetTerrSeason( season_e s )		{	terrSeason = s;				}
void CMgrOptions::SetTerrWinColor( color_s c )		{	terrWinColor = c;			}
void CMgrOptions::SetTerrSprColor( color_s c )		{	terrSprColor = c;			}
void CMgrOptions::SetTerrSumColor( color_s c )		{	terrSumColor = c;			}
void CMgrOptions::SetTerrAutColor( color_s c )		{	terrAutColor = c;			}

void CMgrOptions::SetTextConstFont( LOGFONT f )		{	textConstFont = f;			}
void CMgrOptions::SetTextStarFont( LOGFONT f )		{	textStarFont = f;			}
void CMgrOptions::SetTextDirFont( LOGFONT f )		{	textDirFont = f;			}
void CMgrOptions::SetTextConstColor( color_s c )	{	textConstColor = c;			}
void CMgrOptions::SetTextConstSelColor( color_s c )	{	textConstSelColor = c;		}
void CMgrOptions::SetTextStarColor( color_s c )		{	textStarColor = c;			}
void CMgrOptions::SetTextDirColor( color_s c )		{	textDirColor = c;			}

// Set terrain color for the current season
void CMgrOptions::SetTerrColor( color_s c )
{
	switch( terrSeason )
	{
	case season_Winter:
		terrWinColor = c; break;
	case season_Spring:
		terrSprColor = c; break;
	case season_Summer:
		terrSumColor = c; break;
	case season_Autumn:
		terrAutColor = c; break;
	default:
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Opens the general options dialog
void CMgrOptions::General()
{
	CDlgOptionsGeneral dialog;
	dialog.DoModal();
}

// Opens the color options dialog
void CMgrOptions::ColorOptions()
{
	CDlgOptionsColor dialog;

	if( dialog.DoModal() == IDOK )
	{
		optionsMgr.SetStarsColored( dialog.starColored );
	}
	else
	{
		// Reset colors (they are updated in realtime)
		optionsMgr.SetTextConstColor( dialog.origConstLabels );
		optionsMgr.SetTextConstSelColor( dialog.origConstSelLabels );
		optionsMgr.SetConstNormColor( dialog.origConstNorm );
		optionsMgr.SetConstSelColor( dialog.origConstSel );
		optionsMgr.SetConstActiveColor( dialog.origConstActive );
		optionsMgr.SetTextStarColor( dialog.origStarLabels );
		optionsMgr.SetConstStarColor( dialog.origConstStar );
		optionsMgr.SetTextDirColor( dialog.origDirLabels );
	}

	Redraw();
}

// Load options from storage
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

// Save options to storage
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

			// Location options
			>> locationHome

			// Star options
			>> starsTextured
			>> starsColored
			>> starsLimMagX10
			>> starsSize
			>> starsSContrast
			>> starsCContrast

			// Constellation options
			>> constNormColor
			>> constSelColor
			>> constActiveColor
			>> constStarColor
			>> constLineWidth

			// Terrain options
			>> terrVisible
			>> terrTextured
			>> terrRoughnessX100
			>> terrScale
			>> terrTexIters
			>> terrHeightIters
			>> terrViewHeight
			>> terrSeason
			>> terrWinColor
			>> terrSprColor
			>> terrSumColor
			>> terrAutColor

			// Text options
			>> textConstFont
			>> textStarFont
			>> textDirFont
			>> textConstColor
			>> textConstSelColor
			>> textStarColor
			>> textDirColor

			// Compass options
			>> compassColor;

			terrScale = DEF_TERR_SCALE; ///
		}
		catch( CException* e )
		{
			CSError( "Unable to read options file.\nLoading default options." );
			LoadDefaults();
			e->Delete();
		}

		textMgr.BuildFonts();
	}
	else
	{
		ar

		// Location options
		<< locationHome

		// Star options
		<< starsTextured
		<< starsColored
		<< starsLimMagX10
		<< starsSize
		<< starsSContrast
		<< starsCContrast

		// Constellation options
		<< constNormColor
		<< constSelColor
		<< constActiveColor
		<< constStarColor
		<< constLineWidth

		// Terrain options
		<< terrVisible
		<< terrTextured
		<< terrRoughnessX100
		<< terrScale
		<< terrTexIters
		<< terrHeightIters
		<< terrViewHeight
		<< terrSeason
		<< terrWinColor
		<< terrSprColor
		<< terrSumColor
		<< terrAutColor

		// Text options
		<< textConstFont
		<< textStarFont
		<< textDirFont
		<< textConstColor
		<< textConstSelColor
		<< textStarColor
		<< textDirColor

		// Compass options
		<< compassColor;
	}
}
