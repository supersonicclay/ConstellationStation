// Terrain.h : interface of the CTerrain class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef TERRAIN_H
#define TERRAIN_H

#define DEF_ROUGHNESS	0.2f

class CTerrain : public CObject
{
DECLARE_SERIAL( CTerrain )

public:
	CTerrain();
	CTerrain( float r, CColor c );
	~CTerrain();

	void Serialize( CArchive& ar );

private:
	float* heights;
	int arraySize;
	int size;	// arraySize - 1

	float* upperNormals;
	float* lowerNormals;

	// Settings
	float scale;
	int iterations;
	float roughness;

	CColor color;


public:
	float* GetHeights() const;
	float GetHeight( int i, int j ) const;

	float* GetUpperNormal( int i, int j );
	float* GetLowerNormal( int i, int j );

	int GetArraySize() const;
	int GetSize() const;
	
	float GetScale() const;
	int GetIterations() const;
	float GetRoughness() const;

	CColor GetColor() const;

	void SetUpperNormal( int i, int j, float* n );
	void SetLowerNormal( int i, int j, float* n );
	void SetRoughness( float r );
	void SetColor( CColor color_ );

	void MakeTerrain();

	float AvgSquare( int i, int j, int midSize );
	float AvgDiamond( int i, int j, int midSize );
	float RandomOffset( float range );

	void CalculateNormals();
	void CalculateNormal( float* vec1, float* vec2, float* normal );

};

#endif