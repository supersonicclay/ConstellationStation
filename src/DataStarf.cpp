//===========================================================================
// DataStarf.cpp
//
// CDataStarf
//   starfield data.
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain options. A CDataStarf and 
//   most attributes of a CDataStarf can be saved and opened.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataStarf.h"

#include "DataStar.h"
#include "DataConst.h"
#include "fstream.h"

IMPLEMENT_SERIAL( CDataStarf, CObject, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataStarf::CDataStarf()
{
	Clear();
}

CDataStarf::~CDataStarf()
{
}

// Clear starfield. Also clear stars if told to do so
void CDataStarf::Clear( BOOL clearStars )
{
	// Stars
	if( clearStars )
	{
		seed = 0;
		starCount = 0;
		stars.clear();
	}

	// Constellations
	constCount = 0;
	newConstCount = 0;
	curConstNum = 0;
	consts.clear();

	// Time
	lt.m_dt = 0;
	ut.m_dt = 0;
	julian = 0;
	animation = animation_Forward;
	speed = speed_Now;

	// Location
	location.country = CString();
	location.state = CString();
	location.city = CString();
	location.latd = 0;
	location.latm = 0;
	location.lond = 0;
	location.lonm = 0;
	latitude = 0.0f;
	longitude = 0.0;

	// Viewing
	viewMat.identity();
	starfMat.identity();
	timeMat.identity();
	latMat.identity();

	rotX = 0.0f;
	rotY = 0.0f;
	tempRotX = 0.0f;
	tempRotY = 0.0f;
	rotTime = 0.0f;
	zoom = 0.0f;

	tracking = FALSE;
	trackingType = track_None;
	trackingName = "";
	trackingRA.hour = 0;
	trackingRA.minute = 0;
	trackingRA.second = 0.0f;
	trackingDec.degree = 0;
	trackingDec.minute = 0;
	trackingDec.second = 0.0f;
	trackVec = vector3( 0.0f, 0.0f, 0.0f );

	// Defaults
	LoadStarDefaults();
	LoadConstDefaults();
	LoadSunDefaults();
}

// Create a new random or actual starfield
void CDataStarf::New( BOOL actual )
{
	/// actual = false; /// faster loads

	// Don't clear stars if we don't need to
	if( actual && seed == -1 )
		Clear( FALSE );
	else
		Clear();

	if( actual )
	{
		// Check if we've already loaded actual stars
		if( seed != -1 )
		{
			seed = -1;
			InitActualStars();
		}
		InitActualConsts();
	}
	else
	{
		seed = clock();
//		InitRandomStars();
		InitTestStars();
	}

	dst = _daylight;
	SetLocation( optionsMgr.GetLocationHome() );
	SetAnimation( animation_Forward );
	SetSpeed( speed_Now );
	UpdateMats();
}

// Creates sphere of random stars
void CDataStarf::InitRandomStars()
{
	// Seed random numbers for predictable random starfield
	srand( (unsigned)seed );

	starCount = MAX_STARS;
	CDataStar newStar;

	for (int i=0; i<starCount; ++i)
	{
		newStar.Randomize();
		stars.push_back( CDataStar(newStar) );
	}

	// Sort stars by magnitude
	std::sort( stars.begin(), stars.end() );

	CountStars();
	starfMgr.UpdateStarsAppearance();
}

// Create sphere of evenly distributed stars
void CDataStarf::InitTestStars()
{
	int latCount = 40;
	int longCount = 50;

	CDataStar newStar;
	float phi, theta;

	for( int i=0; i<latCount; ++i )
	{
		phi = (float)i/latCount*PI;
		for( int j=0; j<longCount; ++j )
		{
			theta = (float)j/longCount*PIX2;

			newStar.SetPhi( phi );
			newStar.SetTheta( theta );
			newStar.SetMag( 2.0f );

			newStar.UpdatePosFromPhiTheta();
			stars.push_back( CDataStar( newStar ) );
		}
	}

	// Fill in the rest with blanks
	for( int rem = latCount*longCount; rem < MAX_STARS; ++rem )
	{
		stars.push_back( CDataStar() );
	}

	// Sort stars by magnitude
	std::sort( stars.begin(), stars.end() );

	CountStars();
	starfMgr.UpdateStarsAppearance();
}

// Load the actual stars from the magnitude-sorted, extend hipparcos catalog
void CDataStarf::InitActualStars()
{
	CDataStar newStar;

	CFile file;
	if( !file.Open( "data\\stars.dat", CFile::modeRead | CFile::shareDenyNone ) )
	{
		CSDebug( "Unable to open star catalog", "CDataStarf::InitActualStars" );
		exit(0);
		return;
	}

	char buffer[100];
	int hid;
	CString name;
	ra_s ra = {0};
	dec_s dec = {0};
	float mag = 0;
	char spectral;

	// Initially load all stars
	for( int i=0; i<MAX_STARS; ++i )
	{
		ZeroMemory(&buffer, sizeof(buffer));

		// Hipparcos id
		file.Read( buffer, 7 );
		hid = atoi( buffer );
		ZeroMemory(&buffer, sizeof(buffer));

		// Right Ascension
		file.Read( buffer, 3 );
		ra.hour = atoi( buffer );
		file.Read( buffer, 3 );
		ra.minute = atoi( buffer );
		file.Read( buffer, 6 );
		ra.second = (float) atof( buffer );
		ZeroMemory(&buffer, sizeof(buffer));

		// Declination
		file.Read( buffer, 1 );
		dec.positive = buffer[0] == '+';
		file.Read( buffer, 3 );
		dec.degree = atoi( buffer );
		file.Read( buffer, 3 );
		dec.minute = atoi( buffer );
		file.Read( buffer, 5 );
		dec.second = (float) atof( buffer);
		ZeroMemory(&buffer, sizeof(buffer));

		// Magnitude
		file.Read( buffer, 7 );
		mag = (float) atof( buffer );
		ZeroMemory(&buffer, sizeof(buffer));

		// Spectral type
		file.Read( buffer, 2 );
		if( buffer[0] == ' ' )
			spectral = 'A';
		else
			spectral = buffer[0];

		// Name
		file.Read( buffer, 9 );
		name = buffer;
		name.TrimRight();

		// Ignore rest of line
		file.Seek( 2, CFile::current );

		newStar.SetHID( hid );
		newStar.SetName( name );
		newStar.SetRA( ra );
		newStar.SetDec( dec );
		newStar.SetMag( mag );
		newStar.SetSpectral( spectral );
		newStar.UpdatePosFromRADec();

		stars.push_back( CDataStar(newStar) );
	}

	CountStars();
	starfMgr.UpdateStarsAppearance();

	file.Close();
}

// Load actual constellations somehow
void CDataStarf::InitActualConsts()
{
	ImportConsts();
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CDataStar*		CDataStarf::GetStar(int i)			{	return &stars[i];				}
int				CDataStarf::GetStarCount()			{	return starCount;				}
CDataSun*		CDataStarf::GetSun()				{	return &sun;					}
CDataConst*		CDataStarf::GetConst(int i)			{	return &consts[i];				}
CDataConst*		CDataStarf::GetCurConst()			{	return &consts[curConstNum];	}
int				CDataStarf::GetConstCount()			{	return constCount;				}
int				CDataStarf::GetCurConstNum()		{	return curConstNum;				}
int				CDataStarf::GetNewConstCount()		{	return newConstCount;			}

COleDateTime	CDataStarf::GetLT()					{	return lt;						}
COleDateTime	CDataStarf::GetUT()					{	return ut;						}
double			CDataStarf::GetJulian()				{	return julian;					}
BOOL			CDataStarf::GetDST()				{	return dst;						}

animation_e		CDataStarf::GetAnimation()			{	return animation;				}
speed_e			CDataStarf::GetSpeed()				{	return speed;					}

location_s		CDataStarf::GetLocation()			{	return location;				}
float			CDataStarf::GetLatitude()			{	return latitude;				}
float			CDataStarf::GetLongitude()			{	return longitude;				}

BOOL			CDataStarf::AreStarsVisible()		{	return starsVisible;			}
BOOL			CDataStarf::AreStarsDaylight()		{	return starsDaylight;			}
BOOL			CDataStarf::AreStarsLabeled()		{	return starsLabeled;			}
BOOL			CDataStarf::AreConstsVisible()		{	return constsVisible;			}
BOOL			CDataStarf::AreConstsDaylight()		{	return constsDaylight;			}
BOOL			CDataStarf::AreConstsLabeled()		{	return constsLabeled;			}
BOOL			CDataStarf::AreConstsLinesVisible()	{	return constsLinesVisible;		}
BOOL			CDataStarf::IsSunVisible()			{	return sunVisible;				}
BOOL			CDataStarf::IsSunShining()			{	return sunShine;				}

matrix44*		CDataStarf::GetViewMat()			{	return &viewMat;				}
matrix44*		CDataStarf::GetStarfMat()			{	return &starfMat;				}
matrix44*		CDataStarf::GetTimeMat()			{	return &timeMat;				}
matrix44*		CDataStarf::GetLatMat()				{	return &latMat;					}
float			CDataStarf::GetRotX()				{	return rotX;					}
float			CDataStarf::GetRotY()				{	return rotY;					}
float			CDataStarf::GetTempRotX()			{	return tempRotX;				}
float			CDataStarf::GetTempRotY()			{	return tempRotY;				}
float			CDataStarf::GetRotTime()			{	return rotTime;					}
float			CDataStarf::GetZoom()				{	return zoom;					}
BOOL			CDataStarf::IsTracking()			{	return tracking;				}
track_e			CDataStarf::GetTrackingType()		{	return trackingType;			}
CString			CDataStarf::GetTrackingName()		{	return trackingName;			}
ra_s			CDataStarf::GetTrackingRA()			{	return trackingRA;				}
dec_s			CDataStarf::GetTrackingDec()		{	return trackingDec;				}

// Find the star with the given name
CDataStar* CDataStarf::GetStar( CString& name )
{
	int i = GetStarIndex( name );
	if( i != -1 )
		return &stars[i];
	return NULL;
}

// Find the constellation with the given name
CDataConst* CDataStarf::GetConst( CString& name )
{
	int i = GetConstIndex( name );
	if( i != -1 )
		return &consts[i];
	return NULL;
}

// Find the star index with the given name
int CDataStarf::GetStarIndex( CString& name )
{
	for( int i=0; i<MAX_STARS; ++i )
	{
		if( GetStar(i)->GetName() == name )
			return i;
	}
	CSDebug( "Star name not found", "CDataStarf::GetStarIndex" );
	return -1;
}

// Find the constellation index with the given name
int CDataStarf::GetConstIndex( CString& name )
{
	for( int i=0; i<constCount; ++i )
	{
		if( GetConst(i)->GetName() == name )
			return i;
	}
	CSDebug( "Constellation name not found", "CDataStarf::GetConstIndex" );
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataStarf::IncNewConstCount()				{	newConstCount++;							}
void CDataStarf::SwitchStarsVisible()			{	starsVisible = !starsVisible;				}
void CDataStarf::SetStarsVisible( BOOL x )		{	starsVisible = x;							}
void CDataStarf::SetStarsDaylight( BOOL x )		{	starsDaylight = x;							}
void CDataStarf::SetStarsLabeled( BOOL x )		{	starsLabeled = x;							}
void CDataStarf::SwitchConstsVisible()			{	constsVisible = !constsVisible;				}
void CDataStarf::SetConstsVisible( BOOL x )		{	constsVisible = x;							}
void CDataStarf::SetConstsDaylight( BOOL x )	{	constsDaylight = x;							}
void CDataStarf::SetConstsLabeled( BOOL x )		{	constsLabeled = x;							}
void CDataStarf::SwitchConstsLinesVisible()		{	constsLinesVisible = !constsLinesVisible;	}
void CDataStarf::SetConstsLinesVisible( BOOL x ){	constsLinesVisible = x;						}
void CDataStarf::SwitchSunVisible()				{	sunVisible = !sunVisible;					}
void CDataStarf::SetSunVisible( BOOL x )		{	sunVisible = x;								}
void CDataStarf::SwitchSunShine()				{	sunShine = !sunShine;						}
void CDataStarf::SetSunShine( BOOL x )			{	sunShine = x;								}
void CDataStarf::SetAnimation( animation_e x )	{	animation = x;								}
void CDataStarf::SetSpeed( speed_e x )			{	speed = x;									}

void CDataStarf::SetRotX( float x, BOOL updateMat )
{
	rotX = x;
	if( updateMat )
		UpdateViewMat();
}

void CDataStarf::SetRotY( float x, BOOL updateMat )
{
	rotY = x;
	if( updateMat )
		UpdateViewMat();
}

void CDataStarf::SetTempRotX( float x, BOOL updateMat )
{
	if( rotX+x > PIHALF )
		tempRotX = PIHALF-rotX;
	else if( rotX+x < -PIHALF )
		tempRotX = -PIHALF-rotX;
	else
		tempRotX = x;
	if( updateMat )
		UpdateViewMat();
}

void CDataStarf::SetTempRotY( float x, BOOL updateMat )
{
	tempRotY = x;
	if( updateMat )
		UpdateViewMat();
}

void CDataStarf::AdjRotX( float delta, BOOL updateMat )
{	
	// Restrict up and down rotation
	float newRotX = rotX + delta;

	if( newRotX < -PIHALF )
		rotX = -PIHALF;
	else if( newRotX > PIHALF )
		rotX = PIHALF;
	else
		rotX = newRotX;

	if( updateMat )
		UpdateViewMat();
}

void CDataStarf::AdjRotY( float delta, BOOL updateMat )
{
	rotY += delta;

	// Keep rotY between 0 and 2*PI
	if( rotY < 0.0f )
		rotY += PIX2;
	if( rotY > PIX2 )
		rotY -= PIX2;

	if( updateMat )
		UpdateViewMat();
}

void CDataStarf::AdjZoom( float delta )
{
	zoom += delta;
}


/////////////////////////////////////////////////////////////////////////////
// Methods


/////////////////////////////////////////////////////////////////////////////
// Star Methods

// Load default star options
void CDataStarf::LoadStarDefaults()
{
	starsVisible = DEF_STARS_VISIBLE;
	starsDaylight = DEF_STARS_DAYLIGHT;
	starsLabeled = DEF_STARS_LABELED;
}

// Count the number of stars brighter than the limiting magnitude
void CDataStarf::CountStars()
{
	starCount = 0;

	for( int i=0; i<MAX_STARS; ++i )
	{
		if( GetStar(i)->GetMag() <= optionsMgr.GetStarsLimMag() )
			++starCount;
		else
			break;
	}
}

// Find index into stars array with specified hid
int CDataStarf::FindHID( int hid )
{
	for( int i=0; i<MAX_STARS; ++i )
	{
		if( stars[i].GetHID() == hid )
			return i;
	}
	return -1;
}

// Check if the given star number belongs to a hidden constellation
BOOL CDataStarf::IsStarInCurConst( int i )
{
	CDataConst* c = starfield.GetCurConst();

	for( int li=0; li<c->GetLineCount(); ++li )
	{
		if( i == c->GetLine(li)->GetStar1() ||
			i == c->GetLine(li)->GetStar2() )
			return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Constellation Methods

// Load default constellation options
void CDataStarf::LoadConstDefaults()
{
	constsVisible = DEF_CONST_VISIBLE;
	constsDaylight = DEF_CONST_DAYLIGHT;
	constsLabeled = DEF_CONST_LABELED;
	constsLinesVisible = DEF_CONST_LINESVISIBLE;
}

// Check if the given name is already in use
BOOL CDataStarf::IsDuplicate( CString& name )
{
	for( int i=0; i<constCount; ++i )
	{
		if( GetConst(i)->GetName() == name )
			return TRUE;
	}

	return FALSE;
}

// Add a new constellation with the given name
void CDataStarf::AddConst( CString& name )
{
	consts.push_back( CDataConst(name) );
	++constCount;
}

// Delete the current constellation
void CDataStarf::DeleteConst()
{
	// Use an iterator to find the current constellation
	const_vi constsItor = consts.begin();
	for( int i=0; i<curConstNum; ++i )
		++constsItor;

	// Delete the constellation
	consts.erase( constsItor );

	--constCount;
}

// Rename the current constellation to the given name
void CDataStarf::RenameConst( CString& name )
{
	GetCurConst()->SetName(name);
}

// Set the current constellation to the one with the given name
BOOL CDataStarf::SelectConst( CString& name )
{
	// Search for constellation name
	for( int i=0; i<constCount; ++i )
	{
		if( GetConst(i)->GetName() == name )
		{
			curConstNum = i;
			return TRUE;
		}
	}

	// Return FALSE if name wasn't found
	return FALSE;
}

// Set the current constellation to the one with the given number
void CDataStarf::SelectConst( int i )
{
	curConstNum = i;
}


/////////////////////////////////////////////////////////////////////////////
// Sun methods

// Load default sun options
void CDataStarf::LoadSunDefaults()
{
	sunVisible = DEF_SUN_VISIBLE;
	sunShine = DEF_SUN_SHINE;
}


/////////////////////////////////////////////////////////////////////////////
// Time Methods

// UpdateTime updates all time-critical information
void CDataStarf::UpdateTime()
{
	julian = UTtoJulian( ut.GetYear(), ut.GetMonth(), ut.GetDay(), ut.GetHour(), ut.GetMinute(), ut.GetSecond() );
	sun.UpdatePosition( ut, latitude, longitude);
	UpdateTimeMat();
	UpdateStarfMat();
	if( tracking )
		Track();
}

void CDataStarf::SetDST( BOOL x )
{
	dst = x;
	SetLT( lt ); // Keep local time the same, but refresh UT
}

void CDataStarf::SetLT( COleDateTime& dt )
{
	lt = dt;
	ut = LTtoUT( lt, location.timezone, dst );
	UpdateTime();
}

void CDataStarf::SetUT(COleDateTime& dt )
{
	ut = dt;
	lt = UTtoLT( ut, location.timezone, dst );
	UpdateTime();
}

void CDataStarf::SetJulian( double j )
{
	julian = j;
	ut = JulianToUT( julian );
	lt = UTtoLT( ut, location.timezone, dst );
	UpdateTime();
}

/////////////////////////////////////////////////////////////////////////////
// View Methods

// Update starfield rotations based on current julian date
void CDataStarf::CalculateRotTime()
{
	// Days and fraction (+ or -) from 2000 January 1, 12h UT
	double D = julian - 2451545;

	// Sidereal time in hours
	double GMST = 18.697374558 + 24.06570982441908*D;

	// Longitude adjustment in hours
	float longfix = longitude / 15.0f;

	// Convert to radians and negate for rotation
	rotTime = -(GMST+longfix)*PIX2/24.0;
}

// Update all matrices
void CDataStarf::UpdateMats()
{
	UpdateViewMat();
	UpdateTimeMat();
	UpdateLatMat();
	UpdateStarfMat();
	sun.UpdateSunMat();
}
// Update view matrix
void CDataStarf::UpdateViewMat()
{
	if( dbgGod )
		viewMat = TranslateMatrix44( 0, 0,-3 ) * RotateRadMatrix44( 'x', rotX+tempRotX ) * RotateRadMatrix44( 'y', rotY+tempRotY );
	else
		viewMat = RotateRadMatrix44( 'x', rotX+tempRotX ) * RotateRadMatrix44( 'y', rotY+tempRotY );
}

// Update starfield matrix
void CDataStarf::UpdateStarfMat()
{
	starfMat = latMat * timeMat;
}

// Update time matrix
void CDataStarf::UpdateTimeMat()
{
	CalculateRotTime();
	timeMat = RotateRadMatrix44( 'y', rotTime );
}

// Update latitude matrix
void CDataStarf::UpdateLatMat()
{
	latMat = RotateRadMatrix44( 'x', DegToRad( latitude-90.0f ) );
}

// Rotate methods (for keyboard)
void CDataStarf::RotateUp()		{	AdjRotX( -0.005f*(1-zoom) );	}
void CDataStarf::RotateDown()	{	AdjRotX(  0.005f*(1-zoom) );	}
void CDataStarf::RotateLeft()	{	AdjRotY( -0.005f*(1-zoom) );	}
void CDataStarf::RotateRight()	{	AdjRotY(  0.005f*(1-zoom) );	}

// Zoom methods (for keyboard and mousewheel)
void CDataStarf::ZoomIn()
{
	if( zoom < 0.9f )
		zoom += 0.02f*(1-zoom);
}
void CDataStarf::ZoomOut()
{
	if( zoom > -0.8f )
		zoom -= 0.02f*(1-zoom);
}

// Reset viewing rotation and zoom
void CDataStarf::ResetView()
{
	ResetRot();
	ResetZoom();
}

// Reset rotation
void CDataStarf::ResetRot()
{
	rotX = 0.0f;
	rotY = 0.0f;
	rotTime = 0.0f;
	latitude = 34.6f;
	UpdateViewMat();
	UpdateTimeMat();
	UpdateStarfMat();
}

// Reset zoom
void CDataStarf::ResetZoom()
{
	zoom = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Location Methods

void CDataStarf::SetLocation( location_s x )
{
	location = x;

	if( x.ns == 'N' )
		SetLatitude( x.latd + x.latm/60.0f, FALSE );
	else
		SetLatitude( -x.latd - x.latm/60.0f, FALSE );
	if( x.ew == 'E' )
		SetLongitude( x.lond + x.lonm/60.0f );
	else
		SetLongitude( -x.lond - x.lonm/60.0f );
}

void CDataStarf::SetLatitude( float x, BOOL updateMat )
{
	latitude = x;
	UpdateLatMat();
	sun.UpdatePosition( ut, latitude, longitude);
	if( updateMat )
		UpdateStarfMat();
}
void CDataStarf::SetLongitude( float x, BOOL updateMat )
{
	longitude = x;
	UpdateTimeMat();
	sun.UpdatePosition( ut, latitude, longitude);
	if( updateMat )
	{
		UpdateStarfMat();
	}
}


/////////////////////////////////////////////////////////////////////////////
// Tracking Methods

// Find the specified star
void CDataStarf::FindStar( int num )
{
	if( num == -1 )
	{
		CSDebug( "Shouldn't be finding a star number -1", "CDataStarf::FindStar" );
		return;
	}
	FindStar( &stars[num] );
}

// Find the specified star
void CDataStarf::FindStar( CDataStar* star )
{
	if( tracking )
		StopTracking();

	CenterView( star->GetCenter() );
}   

// Find the specified constellation
void CDataStarf::FindConst( int num )
{
	if( num == -1 )
	{
		CSDebug( "Shouldn't be finding a constellation number -1", "CDataStarf::FindConst" );
		return;
	}
	FindConst( &consts[num] );
}

// Find the specified constellation
void CDataStarf::FindConst( CDataConst* constellation )
{
	if( constellation->GetLineCount() == 0 )
	{
		CSWarn( "Can't find a constellation with no lines" );
		return;
	}

	if( tracking )
		StopTracking();

	CenterView( constellation->GetCenter() );
}

// Find the specified right ascension and declination
void CDataStarf::FindRADec( ra_s ra, dec_s dec )
{
	// Make a fake star so we can use it's methods
	CDataStar s;
	s.SetRA( ra );
	s.SetDec( dec );
	s.UpdatePosFromRADec();

	if( tracking )
		StopTracking();

	CenterView( s.GetCenter() );
}

// Center the view on the specified spherical coordinates
void CDataStarf::CenterView( vector3 t )
{
//  Coordinates specify a point on celectial sphere
//  (ie. doesn't include latitude or time rotation)

	// Find world coordinates (ie. after latitude and time rotation)
	vector3 worldVec = latMat * timeMat * t;

	// Make up a fake star so we can use its methods
	//   (little sloppy, but it'll work)
	CDataStar fakeStar;
	fakeStar.SetCenter( worldVec );
	fakeStar.UpdatePosFromXYZ();

	rotX = fakeStar.GetPhi() - PIHALF;
	rotY = PI - fakeStar.GetTheta();

	UpdateViewMat();
}

// Track the specified star
void CDataStarf::StartTrackingStar( int num )
{
	if( num == -1 )
	{
		CSDebug( "Shouldn't be tracking a star number -1", "CDataStarf::StarTrackingStar" );
		return;
	}
	StartTrackingStar( &stars[num] );
}

// Track the specified star
void CDataStarf::StartTrackingStar( CDataStar* star )
{
	trackingType = track_Star;
	trackingName = star->GetName();
	StartTracking( star->GetCenter() );
}

// Track the specified star
void CDataStarf::StartTrackingConst( int num )
{
	if( num == -1 )
	{
		CSDebug( "Shouldn't be tracking a cosntellation number -1", "CDataStarf::StarTrackingConst" );
		return;
	}
	StartTrackingConst( &consts[num] );
}

// Track the specified constellation
void CDataStarf::StartTrackingConst( CDataConst* constellation )
{
	if( constellation->GetLineCount() == 0 )
	{
		CSWarn( "Can't track a constellation with no lines" );
		return;
	}

	trackingType = track_Const;
	trackingName = constellation->GetName();

	StartTracking( constellation->GetCenter() );
}

// Track the specified right ascension and declination
void CDataStarf::StartTrackingRADec( ra_s ra, dec_s dec )
{
	trackingType = track_RADec;
	trackingRA = ra;
	trackingDec = dec;

	// Make a fake star so we can use it's methods
	CDataStar s;
	s.SetRA( ra );
	s.SetDec( dec );
	s.UpdatePosFromRADec();

	StartTracking( s.GetCenter() );
}

// Start tracking the specified spherical coordinates
void CDataStarf::StartTracking( vector3 t )
{
	tracking = TRUE;
	trackVec = t;
	Track();
}

// Stop tracking
void CDataStarf::StopTracking()
{
	trackingType = track_None;
	trackingName = "";
	tracking = FALSE;
}

// Track the spherical coordinates set in StartTracking
void CDataStarf::Track()
{
	CenterView( trackVec );
}


/////////////////////////////////////////////////////////////////////////////
// Import / Export Constellations

void CDataStarf::ExportConsts()
{
	ofstream file( "data\\consts.dat" );
	if( !file.is_open() )
	{
		CSDebug( "Error opening output file", "CDataStarf::ExportConsts" );
		return;
	}

	CDataConst* c;
	CDataConstLine* l;

	// Write constellation count
	file << constCount << "\n\n";
	for( int ci=0; ci<constCount; ++ci )
	{
		c = &consts[ci];
		// Write current constellation's name and line count
		file << c->GetName() << '\n';
		file << c->GetLineCount() << '\n';
		for( int li=0; li<c->GetLineCount(); ++li )
		{
			l = c->GetLine(li);
			// Write HIDs of stars of current line
			file << stars[l->GetStar1()].GetHID() << ' ';
			file << stars[l->GetStar2()].GetHID() << '\n';			
		}
		file << '\n';
	}

	file.close();

}

void CDataStarf::ImportConsts()
{
	ifstream file( "data\\consts.dat" );
	if( !file.is_open() )
	{
		CSDebug( "Error opening input file", "CDataStarf::ImportConsts" );
		exit(0);
		return;
	}

	int x;
	char buf[100];
	CDataConst c;
	int lineCount;

	// Read constellation count
	file >> x;
	constCount = x;

	// Clear all constellations
	consts.clear();

	for( int ci=0; ci<constCount; ++ci )
	{
		// Create new temp constellation
		c = CDataConst();

		// Read name and line count
		file.get(); file.get(); // Get two newlines
		file.getline(buf, 100);
		//file >> buf;
		file >> x;
		c.SetName( buf );
		lineCount = x;

		for( int li=0; li<lineCount; ++li )
		{
			// Read star 1
			file >> x;
			x = FindHID(x); // Find index into stars array
			c.GetNewLine()->SetStar1( x );

			// Read star 2
			file >> x;
			x = FindHID(x); // Find index into stars array
			c.GetNewLine()->SetStar2( x );

			// Sanity check
			if( c.GetNewLine()->GetStar1()==-1 || c.GetNewLine()->GetStar2()==-1 )
			{
				CSDebug( "Bad HID", "CDataStarf::ImportConsts" );
				exit(0);
				return;
			}

			c.AddLine();			
		}

		consts.push_back( c );
	}

	// Update listbox
	GetFrame()->GetConstBar()->UpdateList();

	file.close();
	Redraw();
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataStarf::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int i, s;
	COleDateTime dt;

	// Serialize sun
	sun.Serialize( ar );

	// Serialize CDataStarf attributes
	if( ar.IsLoading() )
	{
		// Prevent loading actual stars over again
		BOOL isActual = seed == -1;

		ar >> seed
		   >> constCount >> newConstCount >> curConstNum
		   >> dt.m_dt >> dst >> s
		   >> location >> latitude >> longitude
		   >> rotX >> rotY >> rotTime
		   >> zoom;
		speed = (speed_e)s;

		// If we're loading an actual starfield
		if( seed == -1 )
		{
			// Only InitActualStars if we haven't already
			if( !isActual )
			{
				stars.clear();
				InitActualStars();
			}
			UpdateMats();
		}
		// Otherwise initialize random starfield
		else
		{
			stars.clear();
			InitRandomStars();
			UpdateMats();
		}

		GetFrame()->GetStarfBar()->ChangeSpeed( speed );
		starfMgr.Pause();
		// Update time
		SetUT( dt );
		GetFrame()->GetStarfBar()->SetTime( lt );
	}
	else
	{
		if( speed == speed_Now )
			s = speed_Realtime;
		ar << seed
		   << constCount << newConstCount << curConstNum
		   << ut.m_dt << dst << s
		   << location << latitude << longitude
		   << rotX << rotY << rotTime
		   << zoom;
	}

	// If we're loading, get the constellations vector ready
	if( ar.IsLoading() )
	{
		consts.clear();
		for( i=0; i<constCount; ++i )
			consts.push_back( CDataConst() );
	}

	// Serialize constellations
	for( i=0; i<constCount; ++i )
		GetConst(i)->Serialize( ar );
}



