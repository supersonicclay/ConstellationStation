//===========================================================================
// DataStarf.cpp
//
// CDataStarf
//   starfield data.
//   a starfield contains stars, constellations, information about time and
//   location on Earth, as well as certain options. A CDataStarf and 
//   everything in a CDataStarf can be saved and opened.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataStarf.h"

#include "DataStar.h"
#include "DataConst.h"

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

void CDataStarf::Clear()
{
	modified = FALSE;

	starCount = 0;
	constCount = 0;
	newConstCount = 0;
	curConstNum = 0;

	stars.clear();
	consts.clear();

	rotX = 0.0f;
	rotY = 0.0f;
	zoom = 0.0f;
	spinning = FALSE;

	LoadStarDefaults();
	LoadConstDefaults();
	LoadSunDefaults();

	// Time
	time_t seconds = time(NULL);
	gregorian = *(localtime( &seconds ));
	gregorian.tm_year += 1900;
///	julian = 
	rotTime = 0.0f;

	// Latitude & Longitude
	rotLatitude = 50.0f;
}

void CDataStarf::New( BOOL actual )
{
	Clear();

	if( actual )
	{
		InitActualStars();
		InitActualConsts();
	}
	else
	{
		InitRandomStars();
	}
}

// Creates sphere of random stars with radius of 1
void CDataStarf::InitRandomStars()
{
	starCount = 8000;
	CDataStar newStar;

	/* /// North Star
	newStar.SetColor( COLOR_NORTHSTAR );
	newStar.SetMag( 2.0f );
	newStar.SetRA( 0, 0, 0.0f );
	newStar.SetDec( 90, 0, 0.0f );
	newStar.SetX( 0.0f );
	newStar.SetY( 1.0f );
	newStar.SetZ( 0.0f );
	stars.push_back( CDataStar(newStar) );
	*/

	// Sun Corona
	newStar.SetColor( COLOR_WHITE );
	newStar.SetMag( 60.0f );
	newStar.SetRA( 12, 0, 0.0f );
	newStar.SetDec( TRUE, 0, 0, 0.0f );
	newStar.SetX( 0.0f );
	newStar.SetY( 0.0f );
	newStar.SetZ(-1.0f );
	stars.push_back( CDataStar(newStar) );

	// Randomize the rest
	for (int i=1; i<starCount; i++)
	{
		newStar.Randomize();
		stars.push_back( CDataStar(newStar) );
	}
}

// Load the actual stars from the magnitude-sorted hipparcos catalog
void CDataStarf::InitActualStars()
{
	CDataStar newStar;

	starCount = MAX_STARS;///
	stars.reserve( starCount );

	CFile file( "data\\hip_main.txt", CFile::modeRead );

	char buffer[100];
	ra_s ra = {0};
	dec_s dec = {0};
	float mag = 0;

	for( int i=0; i<starCount; ++i )
	{
		file.Seek( 17, CFile::current );
		ZeroMemory(&buffer, sizeof(buffer));

		// Right Ascension
		file.Read( buffer, 2 );
		ra.hour = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 2 );
		ra.minute = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 5 );
		ra.second = (float) atof( buffer );

		file.Seek( 1, CFile::current );
		ZeroMemory(&buffer, sizeof(buffer));

		// Declination
		file.Read( buffer, 1 );
		dec.positive = buffer[0] == '+';

		file.Read( buffer, 2 );
		dec.degree = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 2 );
		dec.minute = atoi( buffer );
			file.Seek( 1, CFile::current );
			ZeroMemory(&buffer, sizeof(buffer));
		file.Read( buffer, 4 );
		dec.second = (float) atof( buffer);

		file.Seek( 1, CFile::current );
		ZeroMemory(&buffer, sizeof(buffer));

		// Magnitude
		file.Read( buffer, 5 );
		mag = (float) atof( buffer );

		// Ignore rest of line
		file.Seek( 406, CFile::current );

		newStar.SetRA( ra );
		newStar.SetDec( dec );
		newStar.SetXYZFromRADec();
		newStar.SetMag( mag );
		newStar.SetColorFromMag();
		newStar.SetRadiusFromMag();

		stars.push_back( CDataStar(newStar) );
	}

	file.Close();

}

/// Load actual constellations somehow
void CDataStarf::InitActualConsts()
{
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CDataStar*	CDataStarf::GetStar(int i)				{	return &stars[i];					}
int			CDataStarf::GetStarCount()				{	return starCount;					}
CDataConst*	CDataStarf::GetConst(int i)				{	return &consts[i];					}
CDataConst*	CDataStarf::GetCurConst()				{	return &consts[curConstNum];		}
int			CDataStarf::GetConstCount()				{	return constCount;					}
int			CDataStarf::GetCurConstNum()			{	return curConstNum;					}
int			CDataStarf::GetNewConstCount()			{	return newConstCount;				}
BOOL		CDataStarf::AreStarsVisible()			{	return starsVisible;				}
BOOL		CDataStarf::AreStarsLabeled()			{	return starsLabeled;				}
float		CDataStarf::GetLimitingMag()			{	return limitingMag;					}
///float		CDataStarf::GetLimitingMag()			{	return limitingMagX10 / 10.0f;	}
///int			CDataStarf::GetLimitingMagX10()			{	return limitingMagX10;			}
BOOL		CDataStarf::AreConstsVisible()			{	return constsVisible;				}
BOOL		CDataStarf::AreConstsLabeled()			{	return constsLabeled;				}
BOOL		CDataStarf::IsSunVisible()				{	return sunVisible;					}
BOOL		CDataStarf::IsSunShining()				{	return sunShine;					}
BOOL		CDataStarf::IsModified()				{	return modified;					}
float		CDataStarf::GetRotLatitude()			{	return rotLatitude;					}
float		CDataStarf::GetRotTime()				{	return rotTime;						}
BOOL		CDataStarf::IsSpinning()				{	return spinning;					}
float		CDataStarf::GetRotX()					{	return rotX;						}
float		CDataStarf::GetRotY()					{	return rotY;						}
float		CDataStarf::GetZoom()					{	return zoom;						}

// Find the constellation with the given name
CDataConst*	CDataStarf::GetConst( CString& name )
{
	for (int i=0; i<constCount; i++)
	{
		if (consts[i].GetName() == name)
			return &consts[i];
	}
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataStarf::IncNewConstCount()						{	newConstCount++;				}
void CDataStarf::SwitchStarsVisible()					{	starsVisible = !starsVisible;	}
void CDataStarf::SetStarsVisible( BOOL x )				{	starsVisible = x;				}
void CDataStarf::SwitchStarsLabeled()					{	starsLabeled = !starsLabeled;	}
void CDataStarf::SetStarsLabeled( BOOL x )				{	starsLabeled = x;				}
void CDataStarf::SetLimitingMag( float m )				{	limitingMag = m;				}
///void CDataStarf::SetLimitingMagX10( int x )			{	limitingMagX10 = x;				}
void CDataStarf::SwitchConstsVisible()					{	constsVisible = !constsVisible;	}
void CDataStarf::SetConstsVisible( BOOL x )				{	constsVisible = x;				}
void CDataStarf::SwitchConstsLabeled()					{	constsLabeled = !constsLabeled;	}
void CDataStarf::SetConstsLabeled( BOOL x )				{	constsLabeled = x;				}
void CDataStarf::SwitchSunVisible()						{	sunVisible = !sunVisible;		}
void CDataStarf::SetSunVisible( BOOL x )				{	sunVisible = x;					}
void CDataStarf::SwitchSunShine()						{	sunShine = !sunShine;			}
void CDataStarf::SetSunShine( BOOL x )					{	sunShine = x;					}
void CDataStarf::SetRotLatitude( float rotLatitude_ )	{	rotLatitude = rotLatitude_;		}
void CDataStarf::SetRotTime( float rotTime_ )			{	rotTime = rotTime_;				}
void CDataStarf::SwitchSpinning()						{	spinning = !spinning;			}

void CDataStarf::SetModified( BOOL m )
{
	modified = m; documentMgr.UpdateTitle();
}

void CDataStarf::AdjRotX( float deltaRotX )
{	
	// Restrict up and down rotation
	float newRotX = rotX + deltaRotX;

	if (newRotX > -90 && newRotX < 90) /// < 30
		rotX = newRotX;
}

void CDataStarf::AdjRotY(float deltaRotY)
{
	rotY += deltaRotY;

	// Keep rotY between -360 and 360
	if (rotY < 360.0f)
		rotY += 360.0f;
	if (rotY > 360.0f)
		rotY -= 360.0f;
}

void CDataStarf::AdjRotTime( float deltaTime )
{
	rotTime += deltaTime;
}

void CDataStarf::AdjZoom( float deltaZoom )
{
	zoom += deltaZoom;
}


/////////////////////////////////////////////////////////////////////////////
// Methods


/////////////////////////////////////////////////////////////////////////////
// View Methods

void CDataStarf::RotateUp()		{	AdjRotX(-0.5f);	}
void CDataStarf::RotateDown()	{	AdjRotX( 0.5f);	}
void CDataStarf::RotateLeft()	{	AdjRotY(-0.5f);	}
void CDataStarf::RotateRight()	{	AdjRotY(0.5f);	}

void CDataStarf::ZoomIn()
{
	if (zoom < 0.9f)
		zoom += 0.01f;
}

void CDataStarf::ZoomOut()
{
	if (zoom > -0.8f)
		zoom -= 0.01f;
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
}

// Reset zoom
void CDataStarf::ResetZoom()
{
	zoom = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////
// Star Methods

// Load default star options
void CDataStarf::LoadStarDefaults()
{
	starsVisible = DEF_STARS_VISIBLE;
	starsLabeled = DEF_STARS_LABELED;
	limitingMag = DEF_STARS_LIMMAG;
}

// Check if the given star number belongs to a hidden constellation
BOOL CDataStarf::IsStarInHiddenConst( int i )
{
	for( int ci=0; ci<constCount; ++ci )
	{
		// Continue if this constellation isn't hidden
		if( consts[ci].IsVisible() )
			continue;
		// Otherwise search through lines
		for( int li=0; li<consts[ci].GetLineCount(); ++li )
		{
			if( i == consts[ci].GetLine(li)->GetStar1() ||
				i == consts[ci].GetLine(li)->GetStar2() )
				return TRUE;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Constellation Methods

// Load default constellation options
void CDataStarf::LoadConstDefaults()
{
	constsVisible = DEF_CONST_VISIBLE;
	constsLabeled = DEF_CONST_LABELED;
}

// Check if the given name is already in use
BOOL CDataStarf::IsDuplicate( CString& name )
{
	for (int i=0; i<constCount; i++)
	{
		if (consts[i].GetName() == name)
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
	for (int i=0; i<constCount; i++)
	{
		if (consts[i].GetName() == name)
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
// Serialization

void CDataStarf::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int i;

	modified = FALSE;

	// Serialize CDataStarf attributes
	if( ar.IsLoading() )
	{
		ar >> starCount
		   >> constCount >> newConstCount >> curConstNum
		   >> rotLatitude >> rotTime
		   >> rotX >> rotY >> zoom;
	}
	else
	{
		ar << starCount
		   << constCount << newConstCount << curConstNum
		   << rotLatitude << rotTime
		   << rotX << rotY << zoom;
	}

	// If we're loading, get the stars and constellations vectors ready
	if( ar.IsLoading() )
	{
		stars.clear();
		for( i=0; i<starCount; ++i )
			stars.push_back( CDataStar() );

		consts.clear();
		for( i=0; i<constCount; ++i )
			consts.push_back( CDataConst() );
	}

	// Serialize stars
	for( i=0; i<starCount; ++i )
		stars[i].Serialize( ar );

	// Serialize constellations
	for( i=0; i<constCount; ++i )
		consts[i].Serialize( ar );
}



