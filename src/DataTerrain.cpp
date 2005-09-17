//===========================================================================
// DataTerrain.cpp
//
// CDataTerrain
//   terrain data.
//   Contains height information, roughness settings, and surface texture.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataTerrain.h"

IMPLEMENT_SERIAL( CDataTerrain, CObject, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataTerrain::CDataTerrain()
{
	// Initialize array pointers to NULL
	heights = NULL;
	upperNormals = lowerNormals = NULL;

	size = arraySize = 0;

	winterTex.data = springTex.data = summerTex.data = autumnTex.data = NULL;

	Clear();
}

CDataTerrain::~CDataTerrain()
{
	// Delete any memory reserved for arrays
	int i;
	for( i=0; i<arraySize; ++i )
		delete[] heights[i];
	for( i=0; i<size; ++i )
	{
		delete[] upperNormals[i];
		delete[] lowerNormals[i];
	}
	delete[] heights;
	delete[] upperNormals;
	delete[] lowerNormals;

	delete[] winterTex.data;
	delete[] springTex.data;
	delete[] summerTex.data;
	delete[] autumnTex.data;
}

void CDataTerrain::Clear()
{
	minHeight = 1000.0f;
	maxHeight = -1000.0f;

	size = arraySize = 0;
	texIters = 0;
	roughness = 0.0f;

	DeleteArrays();
}

// Make a new terrain with a random seed
void CDataTerrain::New()
{
	// Generate new seed
	seed = (unsigned)clock();

	MakeTerrain( TRUE );
}


/////////////////////////////////////////////////////////////////////////////
// Gets

float**		CDataTerrain::GetHeights()						{	return heights;					}
float		CDataTerrain::GetHeight( int i, int j )			{	return heights[i][j];			}
float		CDataTerrain::GetMiddleHeight()					{	return heights[size/2][size/2];	}
int			CDataTerrain::GetSize()							{	return size;					}
int			CDataTerrain::GetArraySize()					{	return arraySize;				}
int			CDataTerrain::GetTexIters()						{	return texIters;				}
int			CDataTerrain::GetHeightIters()					{	return heightIters;				}
float		CDataTerrain::GetRoughness()					{	return roughness;				}
vector3**	CDataTerrain::GetUpperNormals()					{	return upperNormals;			}
vector3**	CDataTerrain::GetLowerNormals()					{	return lowerNormals;			}
vector3		CDataTerrain::GetUpperNormal( int i, int j )	{	return upperNormals[i][j];		}
vector3		CDataTerrain::GetLowerNormal( int i, int j )	{	return lowerNormals[i][j];		}
UINT		CDataTerrain::GetTexID()						{	return texID;					}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataTerrain::SetRoughness( float x )		{	roughness = x;	}



/////////////////////////////////////////////////////////////////////////////
// Methods

// Initializes all terrain options and arrays
void CDataTerrain::InitArrays()
{
	DeleteArrays();

	size = 1<<texIters;
	arraySize = size + 1;

	// Set seed so terrain is predictable
	srand( seed );

	int i;
	int j;

	// Reserve memory for heights array
	heights = new float*[arraySize];
	for( i=0; i<arraySize; ++i )
		heights[i] = new float[arraySize];

	// Reserve memory for normals arrays
	upperNormals = new vector3*[size];
	lowerNormals = new vector3*[size];
	for( i=0; i<size; ++i )
	{
		upperNormals[i] = new vector3[size];
		lowerNormals[i] = new vector3[size];
	}

	// Initialize edge heights to 0 and all other heights to -1
	for (i=0; i<arraySize; ++i)
	{
		for (j=0; j<arraySize; ++j)
		{
			// Set outside heights to 0 for horizon
///			if( i==0 || i==size || j==0 || j==size )
///				heights[i][j] = 0.0f;
///			else
				heights[i][j] = 0.0f;
		}
	}
	// Set midpoint to 1
	///heights[size/2][size/2] = 0.0f;
}

// Delete memory for arrays
void CDataTerrain::DeleteArrays()
{
	// Delete any memory reserved for arrays
	int i;
	for( i=0; i<arraySize; ++i )
		delete[] heights[i];
	for( i=0; i<size; ++i )
	{
		delete[] upperNormals[i];
		delete[] lowerNormals[i];
	}
	delete[] heights;
	delete[] upperNormals;
	delete[] lowerNormals;
}



// Get values that are stored in options
void CDataTerrain::GetValuesFromOptions()
{
	season = optionsMgr.GetTerrSeason();
	texIters = optionsMgr.GetTerrTexIters();
	heightIters = optionsMgr.GetTerrHeightIters();
	roughness = optionsMgr.GetTerrRoughness();
}

// Make a new terrain with the current seed and current options
void CDataTerrain::MakeTerrain( BOOL loadOptions )
{
	if( loadOptions )
		GetValuesFromOptions();
	InitArrays();

	int i;        // row index
	int j;        // col index
	float range;  // range of offset
	int midSize;  // used to keep track of current iteration
	BOOL findingOddPoints;

	range = MAX_TERR_ROUGHNESS;
	midSize = size / 2;

	while (midSize > 0)
	{
		/* FINDING * BY OFFSETTING AVERAGE OF X's
		    In this case size = 8, arraySize = 9, midSize = 2.
			X . . . X . . . X
			. . . . . . . . .
			. . * . . . * . .
			. . . . . . . . .
			X . . . X . . . X
			. . . . . . . . .
			. . * . . . * . .
			. . . . . . . . .
			X . . . X . . . X
		*/
		for (i=midSize; i<size; i+=midSize*2)
		{
			for (j=midSize; j<size; j+=midSize*2)
			{
				// Only set height if it hasn't already been set
				if( heights[i][j] == 0.0f )
					heights[i][j] = RandomOffset(range) + AvgSquare(i, j, midSize);
				if( heights[i][j] > maxHeight )
					maxHeight = heights[i][j];
				else if( heights[i][j] < minHeight )
					minHeight = heights[i][j];
			}
		}

		/* FINDING * BY OFFSETTING AVERAGE OF X's
		    In this case size = 8, arraySize = 9, midSize = 2.
			X . * . X . * . X
			. . . . . . . . .
			* . X . * . X . *
			. . . . . . . . .
			X . * . X . * . X
			. . . . . . . . .
			* . X . * . X . *
			. . . . . . . . .
			X . * . X . * . X
		*/
		findingOddPoints = FALSE;
		for (i=0; i<=size; i+=midSize)
		{
			findingOddPoints = !findingOddPoints;
			for (j=0; j<=size; j+=midSize*2)
			{
				// Offset initial j for odd points (1st row, 3rd row, ...)
				if (findingOddPoints && j==0)
					j += midSize;

				// Only set height if it hasn't already been set
				if( heights[i][j] == 0.0f )
					 heights[i][j] = RandomOffset(range) + AvgDiamond(i, j, midSize);
				if( heights[i][j] > maxHeight )
					maxHeight = heights[i][j];
				else if( heights[i][j] < minHeight )
					minHeight = heights[i][j];
			}
		}

		midSize /= 2;

		// Calculate decrease in range
		if( midSize > (1<<(texIters-heightIters-1)) )
		{
			// We're still generating heights for polygons
			range *= MAX_TERR_ROUGHNESS;
		}
		else
		{
			// We're generating heights for texture
			range *= MAX_TERR_ROUGHNESS*MAX_TERR_ROUGHNESS*MAX_TERR_ROUGHNESS;
		}
	}

	CalculateNormals();
	MakeTexture();
}

// Load terrain height map textures
BOOL CDataTerrain::LoadTextures()
{

	if( !graphicsMgr.LoadTGA( winterTex, "data/terrWinter.tga" ) )
	{
		CSDebug( "Unable to load winter terrain texture", "CDataTerrain::LoadTextures" );
		return FALSE;
	}

	if( !graphicsMgr.LoadTGA( springTex, "data/terrSpring.tga" ) )
	{
		CSDebug( "Unable to load spring terrain texture", "CDataTerrain::LoadTextures" );
		return FALSE;
	}

	if( !graphicsMgr.LoadTGA( summerTex, "data/terrSummer.tga" ) )
	{
		CSDebug( "Unable to load summer terrain texture", "CDataTerrain::LoadTextures" );
		return FALSE;
	}

	if( !graphicsMgr.LoadTGA( autumnTex, "data/terrAutumn.tga" ) )
	{
		CSDebug( "Unable to load autumn terrain texture", "CDataTerrain::LoadTextures" );
		return FALSE;
	}

	glGenTextures( 1, &texID );
	glBindTexture( GL_TEXTURE_2D, texID );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	return TRUE;
}

// Generate terrain texture based on heights array
void CDataTerrain::MakeTexture()
{
	int i, j;
	int dims = (1<<texIters);

	// Get texture of current season
	texture_s* tex;
	switch( season )
	{
	case season_Winter:
		tex = &winterTex; break;
	case season_Spring:
		tex = &springTex; break;
	case season_Summer:
		tex = &summerTex; break;
	case season_Autumn:
		tex = &autumnTex; break;
	default:
		break;
	}

	// Initialize pixels array
	GLubyte* pixels = new GLubyte[dims*dims*3];
	int pixelIndex = 0;
	float ratio;

	int c1=0, c2=0, c3=0, c4=0;///

	float absDiff = maxHeight-minHeight;

	// Fill in pixels based on heights
	for( i=0; i<dims; ++i )
	{
		for( j=0; j<dims; ++j )
		{
			// Calculate ratio (0..1) to use as color index
			/*
			if( roughness != 0.0f )
				ratio = heights[j][i]*roughness/(2*maxOffset)+0.5f;
			else
				ratio = 0.5f;
///			*/
			ratio = roughness*(heights[j][i]-minHeight)/absDiff;

			// Sanity check
			if( ratio > 1.0f )
			{
				CSDebug( "Texture ratio shouldn't be > 1", "CDataTerrain::MakeTexture" );
				exit(0);
			}
			if( ratio < 0.0f )
			{
				CSDebug( "Texture ratio shouldn't be < 0", "CDataTerrain::MakeTexture" );
				exit(0);
			}

			if( ratio < 0.25f )
				++c1;
			else if( ratio < 0.5f )
				++c2;
			else if( ratio < 0.75f )
				++c3;
			else
				++c4;

			// Fill RGB of cuurent pixel
			pixels[pixelIndex++] = tex->data[ (int)(ratio*(tex->height-1))*3+0 ];
			pixels[pixelIndex++] = tex->data[ (int)(ratio*(tex->height-1))*3+1 ];
			pixels[pixelIndex++] = tex->data[ (int)(ratio*(tex->height-1))*3+2 ];
		}
	}

	glBindTexture( GL_TEXTURE_2D, texID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, dims, dims, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );

	delete pixels;
}

// Return average height of square around (i,j)
float CDataTerrain::AvgSquare(int i, int j, int midSize)
{
	/* RETURN AVERAGE OF X's
		X . . . X
		. . . . .
		. . * . .
		. . . . .
		X . . . X
	*/
	float total = 
		heights [i + midSize] [j + midSize] +
		heights [i + midSize] [j - midSize] +
		heights [i - midSize] [j + midSize] +
		heights [i - midSize] [j - midSize];

	return total / 4;
}

// Return average height of diamond around (i,j)
float CDataTerrain::AvgDiamond(int i, int j, int midSize)
{
	/* RETURN AVERAGE OF X's
		. . X . .
		. . . . .
		X . * . X
		. . . . .
		. . X . .
	*/
	float total;
	if (i == 0)
	total = heights [i]            [j-midSize] +
			heights [i]            [j+midSize] +
			heights [size-midSize] [j] +
			heights [i+midSize]    [j];
	else if (i == arraySize-1)
	total = heights [i]            [j-midSize] +
			heights [i]            [j+midSize] +
			heights [i-midSize]    [j] +
			heights [0+midSize]    [j];
	else if (j == 0)
	total = heights [i-midSize]    [j] +
			heights [i+midSize]    [j] +
			heights [i]            [j+midSize] +
			heights [i]            [size-midSize];
	else if (j == arraySize-1)
	total = heights [i-midSize]    [j] +
			heights [i+midSize]    [j] +
			heights [i]            [j-midSize] +
			heights [i]            [0+midSize];
	else
	total = heights [i-midSize]    [j] +
			heights [i+midSize]    [j] +
			heights [i]            [j-midSize] +
			heights [i]            [j+midSize];
	return total / 4;
}

// Pick random offset
float CDataTerrain::RandomOffset( float range )
{
	float factor = (float)(rand()%10000)/10000-0.5f;
	return factor*range;
}

// Calculate normals for upper and lower triangles
void CDataTerrain::CalculateNormals()
{
	vector3 vec1;
	vector3 vec2;
	vector3 normal;

	// Coordinate increment
	float cInc = (float) pow(2, -heightIters+1);
	// Array index increment
	int iInc = (1<<(texIters-heightIters));

	for( int i=0; i<size; i+=iInc )
	{
		for( int j=0; j<size; j+=iInc )
		{
			// Upper triangle
			vec1.x = cInc;
			vec1.y = GetHeight( i+iInc, j ) - GetHeight( i, j );
			vec1.z = 0;
			vec2.x = 0;
			vec2.y = GetHeight( i, j+iInc ) - GetHeight( i, j );
			vec2.z = cInc;

			normal = CrossProduct( vec1, vec2 );
			normal.normalize();
			// Make sure normal points upward
			if( normal.y < 0 )
				normal = -normal;
			upperNormals[i][j] = normal;

			// Lower triangle
			vec1.x = -cInc;
			vec1.y = GetHeight( i+iInc, j ) - GetHeight( i+iInc, j+iInc );
			vec1.z = 0;
			vec2.x = 0;
			vec2.y = GetHeight( i, j+iInc ) - GetHeight( i+iInc, j+iInc );
			vec2.z = -cInc;

			normal = CrossProduct( vec1, vec2 );
			normal.normalize();
			// Make sure normal points upward
			if( normal.y < 0 )
				normal = -normal;
			lowerNormals[i][j] = normal;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataTerrain::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if( ar.IsLoading() )
	{
		ar >> seed >> season ///>> maxOffset
		   >> texIters >> heightIters >> roughness;
		InitArrays();
		MakeTerrain( FALSE );
	}
	else
	{
		ar << seed << season ///<< maxOffset
		   << texIters << heightIters << roughness;
	}
}
