//===========================================================================
// Terrain.cpp
//
// CTerrain
//   contains height information, roughness settings, and surface texture.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "Terrain.h"

IMPLEMENT_SERIAL( CTerrain, CObject, 1 )


const float DEF_ROUGHNESS = 0.2f;
const color_s DEF_COLOR = {0.1f, 0.2f, 0.1f};


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CTerrain::CTerrain( float r, color_s c )
{
	heights = upperNormals = lowerNormals = NULL;	/// UGLY!

	New( r, c );
}

CTerrain::~CTerrain()
{
	delete[] heights;
	delete[] upperNormals;
	delete[] lowerNormals;
}

void CTerrain::New( float r, color_s c )
{
	scale = 1;
	iterations = 2;
	roughness = r;
	color = c;
	viewHeight = 0.0f;

	size = (int)pow(2, iterations);

	arraySize = size + 1;

	/// UGLY!
	delete[] heights;
	delete[] upperNormals;
	delete[] lowerNormals;

	heights = new float[arraySize * arraySize];

	upperNormals = new float[ size*size*3 ];
	lowerNormals = new float[ size*size*3 ];

	MakeTerrain();
}

/////////////////////////////////////////////////////////////////////////////
// Gets

float*	CTerrain::GetHeights()		{	return heights;		}
int		CTerrain::GetArraySize()	{	return arraySize;	}
float	CTerrain::GetScale()		{	return scale;		}
int		CTerrain::GetIterations()	{	return iterations;	}
float	CTerrain::GetRoughness()	{	return roughness;	}
int		CTerrain::GetSize()			{	return size;		}
color_s	CTerrain::GetColor()		{	return color;		}
float	CTerrain::GetViewHeight()	{	return viewHeight;	}

float CTerrain::GetHeight( int i, int j )
{
	return heights[ i*arraySize + j ];
}

float* CTerrain::GetUpperNormal( int i, int j )
{
	return &upperNormals [ (size*j*3 + i*3) ];
}

float* CTerrain::GetLowerNormal( int i, int j )
{
	return &lowerNormals [ (size*j*3 + i*3) ];
}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CTerrain::SetRoughness( float r )
{
	roughness = r;

	MakeTerrain();
}

void CTerrain::SetColor( color_s color_ )
{
	color = color_;
}

void CTerrain::SetUpperNormal( int i, int j, float* n )
{
	upperNormals[ (size*j*3 + i*3 + 0) ] = n[0];
	upperNormals[ (size*j*3 + i*3 + 1) ] = n[1];
	upperNormals[ (size*j*3 + i*3 + 2) ] = n[2];
}

void CTerrain::SetLowerNormal( int i, int j, float* n )
{
	lowerNormals[ (size*j*3 + i*3 + 0) ] = n[0];
	lowerNormals[ (size*j*3 + i*3 + 1) ] = n[1];
	lowerNormals[ (size*j*3 + i*3 + 2) ] = n[2];
}


/////////////////////////////////////////////////////////////////////////////
// Methods

void CTerrain::MakeTerrain()
{
	int i, j;
	float range;
	int midSize;
	BOOL findingOddPoints;

	for (i=0; i<arraySize; i++)
	{
		for (j=0; j<arraySize; j++)
		{
			heights[(i*arraySize) + j] = 0.0f;
		}
	}

	range = roughness;
	midSize = size / 2;

	while (midSize > 0)
	{
		/*
			X . . . X
			. . . . .
			. . * . .
			. . . . .
			X . . . X
		*/
		for (i=midSize; i<size; i+=midSize)
		{
			for (j=midSize; j<size; j+=midSize)
			{
				heights[(i*arraySize) + j] = 
					RandomOffset(range) + 
					AvgSquare(i, j, midSize);
			}
		}

		/*
			X . * . X
			. . . . .
			* . X . *
			. . . . .
			X . * . X
		*/
		findingOddPoints = FALSE;
		for (i=0; i<=size; i+=midSize)
		{
			findingOddPoints = !findingOddPoints;
			for (j=0; j<=size; j+=midSize*2)
			{
				if (findingOddPoints && j==0)
					j += midSize;

				heights[ (i*arraySize) + j ] =
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

float CTerrain::AvgSquare(int i, int j, int midSize)
{
	float total = 
		heights[ ((i + midSize) * arraySize) + (j + midSize) ] +
		heights[ ((i + midSize) * arraySize) + (j - midSize) ] +
		heights[ ((i - midSize) * arraySize) + (j + midSize) ] +
		heights[ ((i - midSize) * arraySize) + (j - midSize) ];

	return total / 4;
}

float CTerrain::AvgDiamond(int i, int j, int midSize)
{
	float total;
    if (i == 0)
	total = heights[ (i*arraySize) + j-midSize ] +
			heights[ (i*arraySize) + j+midSize ] +
			heights[ ((size-midSize)*arraySize) + j ] +
			heights[ ((i+midSize)*arraySize) + j ];
    else if (i == arraySize-1)
	total = heights[ (i*arraySize) + j-midSize ] +
			heights[ (i*arraySize) + j+midSize ] +
			heights[ ((i-midSize)*arraySize) + j ] +
			heights[ ((0+midSize)*arraySize) + j ];
    else if (j == 0)
	total = heights[ ((i-midSize)*arraySize) + j ] +
			heights[ ((i+midSize)*arraySize) + j ] +
			heights[ (i*arraySize) + j+midSize ] +
			heights[ (i*arraySize) + size-midSize] ;
    else if (j == arraySize-1)
	total = heights[ ((i-midSize)*arraySize) + j ] +
			heights[ ((i+midSize)*arraySize) + j ] +
			heights[ (i*arraySize) + j-midSize ] +
			heights[ (i*arraySize) + 0+midSize ];
    else
	total = heights[ ((i-midSize)*arraySize) + j ] +
			heights[ ((i+midSize)*arraySize) + j ] +
			heights[ (i*arraySize) + j-midSize ] +
			heights[ (i*arraySize) + j+midSize ];
	return total / 4;
}

// Pick random offset preferrably negative (valleys]
float CTerrain::RandomOffset( float range )
{
	float ratio = (float)(rand()%10000)/10000;

	return ratio * (2 * range) - range;
}


void CTerrain::CalculateNormals()
{
	float vec1[3];
	float vec2[3];
	float normal[3];

//	inc = (float)pow(2, -iterations+1);

	for( int x=0; x<size; x++ )
	{
		for( int z=0; z<size; z++ )
		{
			// Upper triangle
			vec1[0] = (float) pow(2, -iterations+1);
			vec1[1] = GetHeight( x+1, z ) - GetHeight( x, z );
			vec1[2] = 0;
			vec2[0] = 0;
			vec2[1] = GetHeight( x, z+1 ) - GetHeight( x, z );
			vec2[2] = (float) pow(2, -iterations+1);

			CalculateNormal( vec1, vec2, normal );
			SetUpperNormal( x, z, normal );

			// Lower triangle
			vec1[0] = -(float) pow(2, -iterations+1);
			vec1[1] = GetHeight( x+1, z ) - GetHeight( x+1, z+1 );
			vec1[2] = 0;
			vec2[0] = 0;
			vec2[1] = GetHeight( x, z+1 ) - GetHeight( x+1, z+1 );
			vec2[2] = -(float) pow(2, -iterations+1);

			CalculateNormal( vec1, vec2, normal );
			SetLowerNormal( x, z, normal );
		}
	}
}

void CTerrain::CalculateNormal( float* vec1, float* vec2, float* normal )
{
	normal[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1];
	normal[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2];
	normal[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0];

	float normalLength = (float) sqrt (
		normal[0]*normal[0] +
		normal[1]*normal[1] +
		normal[2]*normal[2] );

	normal[0] /= normalLength;
	normal[1] /= normalLength;
	normal[2] /= normalLength;

	// Make sure we have upward normals
	if( normal[1] < 0 )
	{
		normal[0] = -normal[0];
		normal[1] = -normal[1];
		normal[2] = -normal[2];
	}
}

void CTerrain::CalculateViewHeight()
{
	// Get the index of the midpoint
	int middleIndex = size / 2;

	// Average the heights around the midpoint,
	//  so the viewer isn't placed in a deep pit.

	// Average of square points directly around middle
	float avg1 = AvgSquare(middleIndex, middleIndex, 1);
	// Average of diamond points directly around middle
	float avg2 = AvgDiamond(middleIndex, middleIndex, 1);

	// Average the two averages
	viewHeight = ((avg1 + avg2) / 2);

	// Make sure the new height is not less than the height at the midpoint
	//  (this would put the viewer under the terrain)
	// If it is, then switch to the height of the midpoint
	if (viewHeight < GetHeight(middleIndex, middleIndex))
		viewHeight = GetHeight(middleIndex, middleIndex) + 0.2f;

	// Move it down a little more than that so the viewer isn't exactly on the surface
	viewHeight += 0.05f;

}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CTerrain::Serialize(CArchive& ar)///
{
	CObject::Serialize(ar);
}

