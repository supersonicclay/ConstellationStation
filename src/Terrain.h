//===========================================================================
// Terrain.h
//
// CTerrain
//   contains height information, roughness settings, and surface texture.
//===========================================================================

#ifndef CS_TERRAIN_H
#define CS_TERRAIN_H


extern const float		DEF_ROUGHNESS;
extern const color_s	DEF_COLOR;

class CTerrain : public CObject
{
DECLARE_SERIAL( CTerrain )

// Construction / Destruction
public:

	CTerrain( float r=DEF_ROUGHNESS, color_s c=DEF_COLOR );
	~CTerrain();

	void New( float r=DEF_ROUGHNESS, color_s c=DEF_COLOR );

	void Serialize( CArchive& ar );


// Attributes
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

	color_s color;

	float viewHeight;


// Methods
public:
	void MakeTerrain();
	void SetRoughness( float r );
	void SetColor( color_s color_ );

	float* GetHeights();
	float GetHeight( int i, int j );

	int GetArraySize();
	int GetSize();
	float GetScale();
	int GetIterations();
	float GetRoughness();
	color_s GetColor();
	float GetViewHeight();

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
