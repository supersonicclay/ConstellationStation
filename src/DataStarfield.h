//===========================================================================
// DataStarfield.h
//
// CDataStarfield
//   starfield data.
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain options. A CDataStarfield and 
//   everything in a CDataStarfield can be saved and opened.
//===========================================================================

#ifndef CS_DATASTARFIELD_H
#define CS_DATASTARFIELD_H

#include "DataStar.h"
#include "DataConst.h"


class CDataStarfield : public CObject
{
DECLARE_SERIAL( CDataStarfield )

// Construction / Destruction
public:
	CDataStarfield();
	~CDataStarfield();

	void Clear();
	void New( BOOL actual );
	void InitRandomStars();
	void InitActualStars();
	void InitActualConstellations();

	void Serialize( CArchive& ar );


// Attributes
private:
	// Stars
	star_v stars;
	long numStars;

	// Constellations
	constellation_v  constellations;
	constellation_vi constellationsItor;
	int numConstellations;
	int numNewConstellations;
	int numCurConstellation;

	// Star options
	BOOL starsVisible;
	BOOL starsLabeled;
	float limitingMag;

	// Constellation options
	BOOL constsVisible;
	BOOL constsLabeled;

	// Sun options
	BOOL sunVisible;
	BOOL sunShine;

	// Document
	BOOL modified;

	// Location & Time
	struct tm gregorian;	// Gregorian time - people's time
	long julian;			// Julian date
	float latitude;
	float longitude;

	// Rotation
	float rotLatitude;
	float rotTime;
	float rotX;
	float rotY;
	BOOL  spinning;

	// Zoom
	float zoom;


// Methods
public:

// Gets
	CDataStar* GetStar( int i );
	int GetNumStars();

	CDataConst* GetConstellation( int i );
	CDataConst* GetConstellation( CString &name );
	CDataConst* GetCurConstellation();
	int GetNumConstellations();
	int GetNumNewConstellations();
	int GetNumCurConstellation();

	BOOL AreStarsVisible();
	BOOL AreStarsLabeled();
	float GetLimitingMag();

	BOOL AreConstsVisible();
	BOOL AreConstsLabeled();

	BOOL IsSunVisible();
	BOOL IsSunShining();

	BOOL IsModified();

	float GetRotLatitude();
	float GetRotTime();
	BOOL  IsSpinning();

	float GetRotX();
	float GetRotY();
	float GetZoom();

// Sets
	void IncNumNewConstellations();
	void SetNumCurConstellation( int i );

	void SwitchStarsVisible();
	void SetStarsVisible( BOOL x );
	void SwitchStarsLabeled();
	void SetStarsLabeled( BOOL x );
	void SetLimitingMag( float m );

	void SwitchConstsVisible();
	void SetConstsVisible( BOOL x );
	void SwitchConstsLabeled();
	void SetConstsLabeled( BOOL x );

	void SwitchSunVisible();
	void SetSunVisible( BOOL x );
	void SwitchSunShine();
	void SetSunShine( BOOL x );

	void SetModified( BOOL m=TRUE );

	void SetRotLatitude( float rotLatitude_ );
	void SetRotTime( float time_ );
	void SwitchSpinning();
	void AdjRotTime( float deltaTime );
	void AdjRotX( float deltaRotX );
	void AdjRotY( float deltaRotY );
	void AdjZoom( float deltaZoom );

// Star methods
	void LoadStarDefaults();
	BOOL IsStarInHiddenConst( int i );

// Constellation methods
	void LoadConstDefaults();
	BOOL IsDuplicate( CString& name );
	void AddConstellation( CString& name );
	void DeleteConstellation();
	void RenameConstellation( CString& name );
	BOOL SetCurConstellation( CString& name );
	void AddConstLine( int starNum1, int starNum2 );

// Sun methods
	void LoadSunDefaults();

// View methods
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn  ();
	void ZoomOut ();
	void ResetView ();
	void ResetRot  ();
	void ResetZoom ();

};

#endif