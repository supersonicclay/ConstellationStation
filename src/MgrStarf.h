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
	void Find( CDataStar* star );
	void Find( CDataConst* constellation );
	void StartTracking( CDataStar* star );
	void StartTracking( CDataConst* constellation );
	void Rotate();
	void Location();
	void Time();

// Star methods
	void StarOptions();
	void ToggleStars();
	void UpdateStarsAppearance();

// Constellation methods
	void ConstOptions();
	void ToggleConsts();

// Sun methods
	void SunOptions();
	void ToggleSun();
	void ToggleSunshine();


// Destruction
public:
	~CMgrStarf();

};

#endif
