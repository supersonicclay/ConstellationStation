// Terrain.cpp : implementation of the CTerrain class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Terrain.h"


IMPLEMENT_SERIAL (CTerrain, CObject, 0)

CTerrain::CTerrain()
{
	CColor c = {0.2f, 0.2f, 0.2f};

	CTerrain( DEF_ROUGHNESS, c );
}

CTerrain::CTerrain( float r, CColor c )
{
	scale = 1;
	iterations = 2;
	roughness = r;
	color = c;

	size = (int)pow(2, iterations);

	arraySize = size + 1;

	heights = new float[arraySize * arraySize];

	upperNormals = new float[ size*size*3 ];
	lowerNormals = new float[ size*size*3 ];

	MakeTerrain();
}

CTerrain::~CTerrain()
{
	delete heights;
	delete upperNormals;
	delete lowerNormals;
}

float* CTerrain::GetHeights() const
{
	return heights;
}

float CTerrain::GetHeight( int i, int j ) const
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

int CTerrain::GetArraySize() const
{
	return arraySize;
}

float CTerrain::GetScale() const
{
	return scale;
}

int CTerrain::GetIterations() const
{
	return iterations;
}

float CTerrain::GetRoughness() const
{
	return roughness;
}

int CTerrain::GetSize() const
{
	return size;
}

CColor CTerrain::GetColor() const
{
	return color;
}

void CTerrain::SetRoughness( float r )
{
	roughness = r;
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

void CTerrain::SetColor( CColor color_ )
{
	color = color_;
}


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
	float* vec1 = new float[3];
	float* vec2 = new float[3];
	float* normal = new float[3];

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


void CTerrain::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << arraySize << size
		   << scale << iterations
		   << roughness;

		for( int i=0; i < arraySize*arraySize; i++ )
		{
			ar << heights[i];
		}
	}
	else
	{
		ar >> arraySize >> size
		   >> scale >> iterations
		   >> roughness;

		heights = new float[arraySize * arraySize];

		for( int i=0; i < arraySize*arraySize; i++ )
		{
			ar >> heights[i];
		}
	}
}
