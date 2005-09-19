//===========================================================================
// MgrStarf.cpp
//
// CMgrStarf
//   manager class for starfield functions.
//===========================================================================

#ifndef CS_MGRSTARF_H
#define CS_MGRSTARF_H 


class CMgrStarf
{
// Construction
public:
	CMgrStarf();


// Attributes
public:
	float starsBrightRadius;
	float starsBrightColor;
	float starsDimRadiusPerc;    // Stored as percent of brightest radius
	float starsDimColorPerc;     // Stored as percent of brightest color
	float starsDimRadius;
	float starsDimColor;


// Methods
public:

// Gets
	CBarStarf* GetStarfBar();
	float GetStarsDimRadius();
	float GetStarsBrightRadius();
	float GetStarsDimColor();
	float GetStarsBrightColor();

// Sets
	void SetStarsDimRadius( float x );
	void SetStarsBrightRadius( float x );
	void SetStarsDimColor( float x );
	void SetStarsBrightColor( float x );

// Starfield methods
	void FindTrack();
	void Location();
	void Time();

// Animation methods
	void ChangeStarfSpeed( speed_e x );
	void Pause();
	void Forward();
	void Reverse();
	void Next();
	void Previous();

// Star methods
	void StarOptions();
	void StarInfo( CDataStar* s );
	void StarInfo( int num );
	void ToggleStars();
	void UpdateStarsAppearance();

// Constellation methods
	void ConstOptions();
	void ConstInfo( CDataConst* c );
	void ConstInfo( int num );
	void ToggleConsts();
	void ToggleConstsLines();

// Sun methods
	void SunOptions();
	void ToggleSun();
	void ToggleSunshine();


// Destruction
public:
	~CMgrStarf();

};

#endif
