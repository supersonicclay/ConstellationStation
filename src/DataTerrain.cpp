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


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataTerrain::CDataTerrain()
{
	// Initialize array pointers to NULL
	heights = NULL;
	upperNormals = lowerNormals = NULL;

	size = arraySize = 0;

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
}

void CDataTerrain::Clear()
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

	size = arraySize = 0;

	viewHeight = 0.0f;
}

// Make a new terrain with a random seed
void CDataTerrain::New()
{
	Clear();

	int i;

	// Generate new seed
	seed = (unsigned)clock();

	size = 1<<optionsMgr.GetTerrIters();

	arraySize = size + 1;

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

	MakeTerrain();
}


/////////////////////////////////////////////////////////////////////////////
// Gets

float**		CDataTerrain::GetHeights()						{	return heights;				}
int			CDataTerrain::GetArraySize()					{	return arraySize;			}
int			CDataTerrain::GetSize()							{	return size;				}
float		CDataTerrain::GetViewHeight()					{	return viewHeight;			}
float		CDataTerrain::GetHeight( int i, int j )			{	return heights[i][j];		}
vector3		CDataTerrain::GetUpperNormal( int i, int j )	{	return upperNormals[i][j];	}
vector3		CDataTerrain::GetLowerNormal( int i, int j )	{	return lowerNormals[i][j];	}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataTerrain::SetUpperNormal( int i, int j, vector3 n )	{	upperNormals[i][j] = n;	}
void CDataTerrain::SetLowerNormal( int i, int j, vector3 n )	{	lowerNormals[i][j] = n;	}

void CDataTerrain::IncViewHeight()///
{	viewHeight += 0.01f;	}
void CDataTerrain::DecViewHeight()///
{	viewHeight -= 0.01f;	}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Make a new terrain with the current seed and current options
void CDataTerrain::MakeTerrain()
{
	// Set seed so terrain is predictable
	srand( seed );

	float roughness = optionsMgr.GetTerrRoughness();

	int i;        // row index
	int j;        // col index
	float range;  // range of offset
	int midSize;  // used to keep track of current iteration
	BOOL findingOddPoints;

	for (i=0; i<arraySize; ++i)
	{
		for (j=0; j<arraySize; ++j)
		{
			heights[i][j] = 0.0f;
		}
	}

	range = roughness;
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
		for (i=midSize; i<size; i+=midSize)
		{
			for (j=midSize; j<size; j+=midSize)
			{
				heights[i][j] = 
					RandomOffset(range) + 
					AvgSquare(i, j, midSize);
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

				heights[i][j] =
					RandomOffset(range) +
					AvgDiamond(i, j, midSize);
			}
		}

		midSize /= 2;
		range *= roughness;
	}

	CalculateNormals();
	CalculateViewHeight();
}

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

// Pick random offset preferrably negative (valleys)
float CDataTerrain::RandomOffset( float range )
{
	float ratio = (float)(rand()%10000)/10000;

	return ratio * (2 * range) - range;
}

// Calculate normals for upper and lower triangles
void CDataTerrain::CalculateNormals()
{
	vector3 vec1;
	vector3 vec2;
	vector3 normal;

	int iterations = optionsMgr.GetTerrIters();

	for( int x=0; x<size; x++ )
	{
		for( int z=0; z<size; z++ )
		{
			// Upper triangle
			vec1.x = (float) pow(2, -iterations+1);
			vec1.y = GetHeight( x+1, z ) - GetHeight( x, z );
			vec1.z = 0;
			vec2.x = 0;
			vec2.y = GetHeight( x, z+1 ) - GetHeight( x, z );
			vec2.z = (float) pow(2, -iterations+1);

			normal = CrossProduct( vec1, vec2 );
			normal.normalize();
			// Make sure normal points upward
			if( normal.y < 0 )
				normal = -normal;
			SetUpperNormal( x, z, normal );

			// Lower triangle
			vec1.x = -(float) pow(2, -iterations+1);
			vec1.y = GetHeight( x+1, z ) - GetHeight( x+1, z+1 );
			vec1.z = 0;
			vec2.x = 0;
			vec2.y = GetHeight( x, z+1 ) - GetHeight( x+1, z+1 );
			vec2.z = -(float) pow(2, -iterations+1);

			normal = CrossProduct( vec1, vec2 );
			normal.normalize();
			// Make sure normal points upward
			if( normal.y < 0 )
				normal = -normal;
			SetLowerNormal( x, z, normal );
		}
	}
}

// Calculate the viewing height
void CDataTerrain::CalculateViewHeight()
{
	// Get the index of the midpoint
	int middleIndex = size / 2;

	// Just set the viewer a little above the midpoint
	viewHeight = GetHeight( middleIndex, middleIndex ) + 0.05f;
}



