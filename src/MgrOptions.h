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
	int starsGamma;
	int starsContrast;
	BOOL starsTextured;
	BOOL starsColored;

	// Constellation options
	color_s constNormColor;
	color_s constSelColor;
	color_s constActiveColor;
	color_s constStarColor;
	BOOL constStarsColored;

	// Terrain options
	float terrRoughness;
	BOOL terrTextured;
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
	int GetStarsGamma();
	int GetStarsContrast();
	BOOL AreStarsTextured();
	BOOL AreStarsColored();

	color_s GetConstNormColor();
	color_s GetConstSelColor();
	color_s GetConstActiveColor();
	color_s GetConstStarColor();
	BOOL AreConstStarsColored();

	float GetTerrRoughness();
	BOOL IsTerrTextured();
	season_e GetTerrSeason();
	color_s GetTerrWinColor();
	color_s GetTerrSprColor();
	color_s GetTerrSumColor();
	color_s GetTerrFalColor();
	color_s GetTerrColor();

// Sets
	void SetStarsGamma( int g );
	void SetStarsContrast( int c );
	void SetStarsTextured( BOOL t );
	void SetStarsColored( BOOL c );

	void SetConstNormColor( color_s c );
	void SetConstSelColor( color_s c );
	void SetConstActiveColor( color_s c );
	void SetConstStarColor( color_s c );
	void SetConstStarsColored( BOOL x );

	void SetTerrRoughness( float r );
	void SetTerrTextured( BOOL t );
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
