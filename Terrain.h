// Terrain.h : interface of the CTerrain class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef TERRAIN_H
#define TERRAIN_H

extern const float		DEF_ROUGHNESS;
extern const color_t	DEF_COLOR;

class CTerrain : public CObject
{
DECLARE_SERIAL( CTerrain )

public:

	CTerrain( float r=DEF_ROUGHNESS, color_t c=DEF_COLOR );
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

	color_t color;

	float viewHeight;


public:
	void MakeTerrain();
	void SetRoughness( float r );
	void SetColor( color_t color_ );

	float* GetHeights() const;
	float GetHeight( int i, int j ) const;

	int GetArraySize() const;
	int GetSize() const;
	float GetScale() const;
	int GetIterations() const;
	float GetRoughness() const;
	color_t GetColor() const;
	float GetViewHeight() const;

	float* GetUpperNormal( int i, int j );
	float* GetLowerNormal( int i, int j );
	void SetUpperNormal( int i, int j, float* n );
	void SetLowerNormal( int i, int j, float* n );

	float AvgSquare( int i, int j, int midSize );
	float AvgDiamond( int i, int j, int midSize );
	float RandomOffset( float range );

	void CalculateNormals();
	void CalculateNormal( float* vec1, float* vec2, float* normal );

	void CalculateViewHeight();

};

#endif
