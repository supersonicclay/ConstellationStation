//===========================================================================
// DataStarf.h
//
// CDataStarf
//   starfield data.
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain options. A CDataStarf and 
//   everything in a CDataStarf can be saved and opened.
//===========================================================================

#ifndef CS_DATASTARF_H
#define CS_DATASTARF_H

#include "DataStar.h"
#include "DataConst.h"


class CDataStarf : public CObject
{
DECLARE_SERIAL( CDataStarf )

// Construction / Destruction
public:
	CDataStarf();
	~CDataStarf();

	void Clear();
	void New( BOOL actual );
	void InitRandomStars();
	void InitActualStars();
	void InitActualConsts();

	void Serialize( CArchive& ar );


// Attributes
private:
	// Stars
	star_v stars;
	int starCount;

	// Constellations
	const_v  consts;
	int constCount;
	int newConstCount;
	int curConstNum;

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
	int GetStarCount();

	CDataConst* GetConst( int i );
	CDataConst* GetConst( CString &name );
	CDataConst* GetCurConst();
	int GetConstCount();
	int GetNewConstCount();
	int GetCurConstNum();

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
	void IncNewConstCount();

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
	void AddConst( CString& name );
	void DeleteConst();
	void RenameConst( CString& name );
	BOOL SelectConst( CString& name );
	void SelectConst( int i );
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