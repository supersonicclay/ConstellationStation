// Terrain.cpp : implementation of the CTerrain class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Terrain.h"


IMPLEMENT_SERIAL (CTerrain, CObject, 0)

CTerrain::CTerrain()
{
	scale = 1;
	iterations = 4;
	roughness = 0.2f;

	size = (int)pow(2, iterations);

	arraySize = size + 1;

	heights = new float[arraySize * arraySize];

	MakeTerrain();
}

CTerrain::~CTerrain()
{
}

float* CTerrain::GetHeights() const
{
	return heights;
}

float CTerrain::GetHeight(int i, int j) const
{
	return heights[ (i*arraySize) + j ];
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





void CTerrain::Serialize(CArchive& ar)
{
}
