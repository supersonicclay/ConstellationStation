//===========================================================================
// Starfield.h
//
// CStarfield
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain settings. A CStarfield and 
//   everything in a CStarfield can be saved and opened.
//===========================================================================

#ifndef CS_STARFIELD_H
#define CS_STARFIELD_H


#include "Star.h"
#include "Constellation.h"

class CStarfield : public CObject
{
DECLARE_SERIAL( CStarfield )

// Construction / Destruction
public:
	CStarfield();
	~CStarfield();

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
	CStar* GetStar( int i );
	int GetNumStars();

	CConstellation* GetConstellation( int i );
	CConstellation* GetConstellation( CString &name );
	CConstellation* GetCurConstellation();
	int GetNumConstellations();
	int GetNumNewConstellations();
	int GetNumCurConstellation();

	BOOL AreStarsVisible();
	BOOL AreStarsLabeled();
	float GetLimitingMag();

	BOOL AreConstsVisible();
	BOOL AreConstsLabeled();

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

	void SetModified( BOOL m=TRUE );

	void SetRotLatitude( float rotLatitude_ );
	void SetRotTime( float time_ );
	void SwitchSpinning();
	void AdjRotTime( float deltaTime );
	void AdjRotX( float deltaRotX );
	void AdjRotY( float deltaRotY );
	void AdjZoom( float deltaZoom );

	// Constellation methods
	BOOL IsDuplicate( CString& name );
	void AddConstellation( CString& name );
	void DeleteConstellation();
	void RenameConstellation( CString& name );
	BOOL SetCurConstellation( CString& name );
	void AddConstLine( int starNum1, int starNum2 );

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