//===========================================================================
// DataStarf.h
//
// CDataStarf
//   starfield data.
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain options. A CDataStarf and 
//   most attributes of a CDataStarf can be saved and opened.
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

	void Clear( BOOL clearStars=TRUE );

	void New( BOOL actual );

	void InitRandomStars();
	void InitActualStars();
	void InitActualConsts();

	void Serialize( CArchive& ar );


// Attributes
private:

// Starfield
	// Random seed or -1 for actual
	int seed;

	// Location & Time
	struct tm gregorian;	// Gregorian time - people's time
	long julian;			// Julian date
	float latitude;
	float longitude;

	// Matrices
	matrix44 viewMat;
	matrix44 timeMat;
	matrix44 latMat;
	matrix44 longMat;

	// Viewing
	float rotX;
	float rotY;
	float rotTime;
	float zoom;
	BOOL  spinning;
	BOOL  tracking;
	float trackX;
	float trackY;
	float trackZ;


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

// Constellation options
	BOOL constsVisible;
	BOOL constsLabeled;

// Sun options
	BOOL sunVisible;
	BOOL sunShine;


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

	BOOL AreConstsVisible();
	BOOL AreConstsLabeled();

	BOOL IsSunVisible();
	BOOL IsSunShining();

	matrix44* GetViewMat();
	matrix44* GetTimeMat();
	matrix44* GetLatMat();

	float GetRotX();
	float GetRotY();
	float GetRotTime();
	float GetZoom();

	BOOL  IsSpinning();
	BOOL  IsTracking();


// Sets
	void IncNewConstCount();

	void SwitchStarsVisible();
	void SetStarsVisible( BOOL x );
	void SwitchStarsLabeled();
	void SetStarsLabeled( BOOL x );

	void SwitchConstsVisible();
	void SetConstsVisible( BOOL x );
	void SwitchConstsLabeled();
	void SetConstsLabeled( BOOL x );

	void SwitchSunVisible();
	void SetSunVisible( BOOL x );
	void SwitchSunShine();
	void SetSunShine( BOOL x );

	void SetRotTime( float r, BOOL updateMat=TRUE );
	void AdjRotX( float delta, BOOL updateMat=TRUE );
	void AdjRotY( float delta, BOOL updateMat=TRUE );
	void AdjRotTime( float delta, BOOL updateMat=TRUE );
	void AdjZoom( float delta );

	void SwitchSpinning();


// Star methods
	void LoadStarDefaults();
	void CountStars();
	BOOL IsStarInHiddenConst( int i );


// Constellation methods
	void LoadConstDefaults();
	BOOL IsDuplicate( CString& name );
	void AddConst( CString& name );
	void DeleteConst();
	void RenameConst( CString& name );
	BOOL SelectConst( CString& name );
	void SelectConst( int i );


// Sun methods
	void LoadSunDefaults();


// View methods
	void UpdateMats();
	void UpdateViewMat();
	void UpdateTimeMat();
	void UpdateLatMat();
	void UpdateLongMat();

	void RotateUp();
	void RotateDown();
	void RotateLeft();
	void RotateRight();
	void ZoomIn();
	void ZoomOut();
	void ResetView();
	void ResetRot();
	void ResetZoom();

	void StopTracking();
	void StartTracking( float x, float y, float z );
	void Track();

	void Find( float x, float y, float z );

};

#endif