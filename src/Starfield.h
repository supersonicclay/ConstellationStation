// Starfield.h : interface of the CStarfield class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef STARFIELD_H
#define STARFIELD_H

#include "Star.h"
#include "Constellation.h"

class CStarfield : public CObject
{

public:
	CStarfield( bool random=false );
	~CStarfield();

	void Init();
	void InitRandomStars();
	void InitActualStars();
	void InitRandomConstellations();
	void InitActualConstellations();

private:
	CStar* stars;
	CConstellation* constellations;

	long numStars;

	int numConstellations;
	int numNewConstellations;
	int numCurConstellation;

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

public:

// Gets
	CStar* GetStars() const;
	CConstellation* GetConstellations() const;
	CStar* GetStar( int i ) const;
	CConstellation* GetConstellation( int i ) const;
	CConstellation* GetConstellation( CString &name ) const;
	CConstellation* GetCurConstellation() const;

	int GetNumStars() const;
	int GetNumConstellations() const;
	int GetNumNewConstellations() const;
	int GetNumCurConstellation() const;

	float GetRotLatitude() const;
	float GetRotTime() const;
	BOOL  IsSpinning() const;

	float GetRotX() const;
	float GetRotY() const;
	float GetZoom() const;

// Sets
	void IncNumNewConstellations();
	void SetNumCurConstellation( int i );
	void SetRotLatitude( float rotLatitude_ );
	void SetRotTime( float time_ );
	void SwitchSpinning();
	// Adjusts
	void AdjRotTime( float deltaTime );
	void AdjRotX( float deltaRotX );
	void AdjRotY( float deltaRotY );
	void AdjZoom( float deltaZoom );

// Constellation functions
	BOOL IsDuplicate( CString &name );
	void AddConstellation( CString &name );
	void DeleteConstellation();
	void RenameConstellation( CString &name );
	BOOL SetCurConstellation( CString name );
	void AddConstLine( int starNum1, int starNum2 );

// View Manipulation
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn  ();
	void ZoomOut ();
	// View resets
	void ResetView ();
	void ResetRot  ();
	void ResetZoom ();

};

#endif