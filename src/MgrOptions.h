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
	void LoadStarDefaults();
	void LoadConstDefaults();
	void LoadSunDefaults();
	void LoadTerrDefaults();

	void Serialize(CArchive& ar);


// Attributes
private:

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
	BOOL constStarsColored;
	int constLineWidth;

	// Terrain options
	BOOL terrVisible;
	BOOL terrTextured;
	int terrRoughnessX100;
	int terrScale;
	int terrTexIters;
	int terrHeightIters;
	season_e terrSeason;
	color_s terrWinColor;
	color_s terrSprColor;
	color_s terrSumColor;
	color_s terrFalColor;

	// Compass options
	color_s compassColor;


// Methods
public:

// Gets
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
	BOOL AreConstStarsColored();
	int GetConstLineWidth();

	BOOL IsTerrVisible();
	BOOL IsTerrTextured();
	int GetTerrRoughnessX100();
	float GetTerrRoughness();
	int GetTerrScale();
	int GetTerrTexIters();
	int GetTerrHeightIters();
	season_e GetTerrSeason();
	color_s GetTerrWinColor();
	color_s GetTerrSprColor();
	color_s GetTerrSumColor();
	color_s GetTerrFalColor();
	color_s GetTerrColor();

// Sets
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
	void SetConstStarsColored( BOOL x );
	void SetConstLineWidth( int w );

	void SwitchTerrVisible();
	void SetTerrVisible( BOOL x );
	void SetTerrTextured( BOOL t );
	void SetTerrRoughnessX100( int r );
	void SetTerrScale( int s );
	void SetTerrTexIters( int i );
	void SetTerrHeightIters( int i );
	void SetTerrSeason( season_e s );
	void SetTerrWinColor( color_s c );
	void SetTerrSprColor( color_s c );
	void SetTerrSumColor( color_s c );
	void SetTerrFalColor( color_s c );
	void SetTerrColor( color_s c );

// Methods
	void General();

	void Load();
	void Save();

// Destruction
public:
	~CMgrOptions();

};

#endif
