//===========================================================================
// MgrOptions.cpp
//
// CMgrOptions
//   description.
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
	void LoadTerrDefaults();
	void LoadCompassDefaults();

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

	// Terrain options
	float terrRoughness;
	BOOL terrTextured;
	season_e terrSeason;
	color_s terrColor;

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

	float GetTerrRoughness();
	BOOL IsTerrTextured();
	season_e GetTerrSeason();
	color_s GetTerrColor();

	color_s GetCompassColor();

	// Sets
	void SetStarsGamma( int g );
	void SetStarsContrast( int c );
	void SetStarsTextured( BOOL t );
	void SetStarsColored( BOOL c );

	void SetConstNormColor( color_s c );
	void SetConstSelColor( color_s c );
	void SetConstActiveColor( color_s c );

	void SetTerrRoughness( float r );
	void SetTerrTextured( BOOL t );
	void SetTerrSeason( season_e s );
	void SetTerrColor( color_s c );

	void SetCompassColor( color_s c );

	// General Options
	void General();


// Destruction
public:
	~CMgrOptions();

};

#endif
