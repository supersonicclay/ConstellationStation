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
#include "DataSun.h"
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
	void InitTestStars();///
	void InitActualStars();
	void InitActualConsts();

	void ExportConsts();
	void ImportConsts();

	void Serialize( CArchive& ar );


// Attributes
private:

// Starfield
	// Random seed or -1 for actual
	int seed;

	// Time
	COleDateTime lt;		// Local time
	COleDateTime ut;		// Universal time
	double julian;			// Julian date
	BOOL dst;

	// Animation
	animation_e animation;
	speed_e speed;

	// Location
	location_s location;
	float latitude;
	float longitude;

	// Matrices
	matrix44 viewMat;
	matrix44 timeMat;
	matrix44 latMat;
	matrix44 starfMat;      // composition of latMat and timeMat

	// Viewing
	float rotX;
	float rotY;
	float tempRotX;
	float tempRotY;
	float rotTime;
	float zoom;

	// Tracking
	BOOL  tracking;
	track_e trackingType;
	CString trackingName;
	ra_s trackingRA;
	dec_s trackingDec;	
	vector3 trackVec;


// Stars
	star_v stars;
	int starCount;

// Sun
	CDataSun sun;

// Constellations
	const_v  consts;
	int constCount;
	int newConstCount;
	int curConstNum;

// Star options
	BOOL starsVisible;
	BOOL starsDaylight;   // stars visible during daylight
	BOOL starsLabeled;

// Constellation options
	BOOL constsVisible;
	BOOL constsDaylight;  // constellations visible during daylight
	BOOL constsLabeled;
	BOOL constsLinesVisible;     // constellation lines visible

// Sun options
	BOOL sunVisible;
	BOOL sunShine;


// Methods
public:

// Gets
	CDataStar* GetStar( int i );
	CDataStar* GetStar( CString& name );
	int GetStarIndex( CString& name );
	int GetStarCount();

	CDataSun* GetSun();

	CDataConst* GetConst( int i );
	CDataConst* GetConst( CString& name );
	int GetConstIndex( CString& name );
	CDataConst* GetCurConst();
	int GetConstCount();
	int GetNewConstCount();
	int GetCurConstNum();

	COleDateTime GetLT();
	COleDateTime GetUT();
	double GetJulian();
	BOOL GetDST();

	animation_e GetAnimation();
	speed_e GetSpeed();

	location_s GetLocation();
	float GetLatitude();
	float GetLongitude();

	BOOL AreStarsVisible();
	BOOL AreStarsDaylight();
	BOOL AreStarsLabeled();
	BOOL AreConstsVisible();
	BOOL AreConstsDaylight();
	BOOL AreConstsLabeled();
	BOOL AreConstsLinesVisible();
	BOOL IsSunVisible();
	BOOL IsSunShining();

	matrix44* GetViewMat();
	matrix44* GetStarfMat();
	matrix44* GetTimeMat();
	matrix44* GetLatMat();

	float GetRotX();
	float GetRotY();
	float GetTempRotX();
	float GetTempRotY();
	float GetRotTime();
	float GetZoom();

	BOOL  IsTracking();
	track_e GetTrackingType();
	CString GetTrackingName();
	ra_s GetTrackingRA();
	dec_s GetTrackingDec();


// Sets
	void IncNewConstCount();

	void SwitchStarsVisible();
	void SetStarsVisible( BOOL x );
	void SetStarsDaylight( BOOL x );
	void SetStarsLabeled( BOOL x );

	void SwitchConstsVisible();
	void SetConstsVisible( BOOL x );
	void SetConstsDaylight( BOOL x );
	void SetConstsLabeled( BOOL x );
	void SwitchConstsLinesVisible();
	void SetConstsLinesVisible( BOOL x );

	void SwitchSunVisible();
	void SetSunVisible( BOOL x );
	void SwitchSunShine();
	void SetSunShine( BOOL x );

	void SetAnimation( animation_e x );
	void SetSpeed( speed_e x );

	void SetLocation( location_s x );
	void SetLatitude( float x, BOOL updateMat=TRUE );
	void SetLongitude( float x, BOOL updateMat=TRUE );

	void SetRotX( float r, BOOL updateMat=TRUE );
	void SetRotY( float r, BOOL updateMat=TRUE );
	void SetTempRotX( float r, BOOL updateMat=TRUE );
	void SetTempRotY( float r, BOOL updateMat=TRUE );
	void AdjRotX( float delta, BOOL updateMat=TRUE );
	void AdjRotY( float delta, BOOL updateMat=TRUE );
	void AdjZoom( float delta );


// Methods

// Star methods
	void LoadStarDefaults();
	void CountStars();
	int  FindHID( int hid );
	BOOL IsStarInCurConst( int i );

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
	void UpdateSunRADec();

// Time methods
	void UpdateTime();
	void SetDST( BOOL x );
	void SetLT( COleDateTime& dt );
	void SetUT( COleDateTime& dt );
	void SetJulian( double j );

// View methods
	void CalculateRotTime();
	void UpdateMats();
	void UpdateViewMat();
	void UpdateStarfMat();
	void UpdateTimeMat();
	void UpdateLatMat();

	void RotateUp();
	void RotateDown();
	void RotateLeft();
	void RotateRight();
	void ZoomIn();
	void ZoomOut();
	void ResetView();
	void ResetRot();
	void ResetZoom();

// Tracking methods
	void CenterView( vector3 t );

	void FindStar( int num );
	void FindStar( CDataStar* star );
	void FindConst( int num );
	void FindConst( CDataConst* constellation );
	void FindRADec( ra_s ra, dec_s dec );

	void StartTrackingStar( int num );
	void StartTrackingStar( CDataStar* star );
	void StartTrackingConst( int num );
	void StartTrackingConst( CDataConst* constellation );
	void StartTrackingRADec( ra_s ra, dec_s dec );
	void StartTracking( vector3 t );
	void StopTracking();
	void Track();


};

#endif