//===========================================================================
// MgrOptions.h
//
// CMgrOptions
//   contains settings that are local to each machine
//   (not saved in document).
//===========================================================================

#ifndef CS_MGROPTIONS_H
#define CS_MGROPTIONS_H 


class CMgrOptions : public CObject
{
DECLARE_SERIAL( CMgrOptions )

// Construction
public:
	CMgrOptions();

	void LoadDefaults();
	void LoadLocationDefaults();
	void LoadStarDefaults();
	void LoadConstDefaults();
	void LoadSunDefaults();
	void LoadTerrDefaults();
	void LoadColorDefaults();
	void LoadTextDefaults();

	void Serialize(CArchive& ar);


// Attributes
private:

	// Location options
	location_s locationHome;

	// Star options
	BOOL starsTextured;
	BOOL starsColored;
	int starsLimMagX10;
	int starsSize;
	int starsSContrast; // Size contrast
	int starsCContrast; // Color contrast

	// Constellation options
	color_s constNormColor;
	color_s constSelColor;
	color_s constActiveColor;
	color_s constStarColor;
	int constLineWidth;

	// Terrain options
	BOOL terrVisible;
	BOOL terrTextured;
	int terrRoughnessX100;
	season_e terrSeason;
	color_s terrWinColor;
	color_s terrSprColor;
	color_s terrSumColor;
	color_s terrAutColor;

	// Text options
	LOGFONT textConstFont;
	LOGFONT textStarFont;
	LOGFONT textDirFont;
	color_s textConstColor;
	color_s textConstSelColor;
	color_s textStarColor;
	color_s textDirColor;

	// Compass options
	color_s compassColor;


// Methods
public:

// Gets
	location_s GetLocationHome();

	BOOL AreStarsTextured();
	BOOL AreStarsColored();
	float GetStarsLimMag();
	int GetStarsLimMagX10();
	int GetStarsSize();
	int GetStarsSContrast();
	int GetStarsCContrast();

	color_s GetConstNormColor();
	color_s GetConstSelColor();
	color_s GetConstActiveColor();
	color_s GetConstStarColor();
	int GetConstLineWidth();

	BOOL IsTerrVisible();
	BOOL IsTerrTextured();
	int GetTerrRoughnessX100();
	float GetTerrRoughness();
	season_e GetTerrSeason();
	color_s GetTerrWinColor();
	color_s GetTerrSprColor();
	color_s GetTerrSumColor();
	color_s GetTerrAutColor();
	color_s GetTerrColor();

	LOGFONT GetTextConstFont();
	LOGFONT GetTextStarFont();
	LOGFONT GetTextDirFont();
	color_s GetTextConstColor();
	color_s GetTextConstSelColor();
	color_s GetTextStarColor();
	color_s GetTextDirColor();

// Sets
	void SetLocationHome( location_s x );

	void SetStarsTextured( BOOL t );
	void SetStarsColored( BOOL c );
	void SetStarsLimMagX10( int m );
	void SetStarsSize( int g );
	void SetStarsSContrast( int c );
	void SetStarsCContrast( int c );

	void SetConstNormColor( color_s c );
	void SetConstSelColor( color_s c );
	void SetConstActiveColor( color_s c );
	void SetConstStarColor( color_s c );
	void SetConstLineWidth( int w );

	void SwitchTerrVisible();
	void SetTerrVisible( BOOL x );
	void SetTerrTextured( BOOL t );
	void SetTerrRoughnessX100( int r );
	void SetTerrSeason( season_e s );
	void SetTerrWinColor( color_s c );
	void SetTerrSprColor( color_s c );
	void SetTerrSumColor( color_s c );
	void SetTerrAutColor( color_s c );
	void SetTerrColor( color_s c );

	void SetTextConstFont( LOGFONT f );
	void SetTextStarFont( LOGFONT f );
	void SetTextDirFont( LOGFONT f );
	void SetTextConstColor( color_s c );
	void SetTextConstSelColor( color_s c );
	void SetTextStarColor( color_s c );
	void SetTextDirColor( color_s c );

// Methods
	void General();
	void ColorOptions();

	void Load();
	void Save();

// Destruction
public:
	~CMgrOptions();

};

#endif
