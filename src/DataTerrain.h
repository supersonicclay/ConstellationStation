//===========================================================================
// DataTerrain.h
//
// CDataTerrain
//   terrain data.
//   Contains height information, roughness settings, and surface texture.
//===========================================================================

#ifndef CS_DATATERRAIN_H
#define CS_DATATERRAIN_H


class CDataTerrain : public CObject
{
DECLARE_SERIAL( CDataTerrain )

// Construction / Destruction
public:

	CDataTerrain();
	~CDataTerrain();

	void Clear();
	void New();

	void Serialize( CArchive& ar );


// Attributes
private:
	unsigned int seed; // Used for predictable terrain

	float* heights;
	int arraySize;
	int size;	// arraySize - 1

	float* upperNormals;
	float* lowerNormals;

	BOOL visible;

	// Settings
	float scale;
	int iterations;

	float viewHeight;


// Methods
public:

// Gets
	float* GetHeights();
	float GetHeight( int i, int j );

	int GetArraySize();
	int GetSize();
	float GetScale();
	int GetIterations();
	float GetViewHeight();

	float* GetUpperNormal( int i, int j );
	float* GetLowerNormal( int i, int j );

	BOOL IsVisible();

// Sets
	void SetUpperNormal( int i, int j, float* n );
	void SetLowerNormal( int i, int j, float* n );

	void SwitchVisible();
	void SetVisible( BOOL x );

// Methods
	void LoadDefaults();

	void MakeTerrain();

	float AvgSquare( int i, int j, int midSize );
	float AvgDiamond( int i, int j, int midSize );
	float RandomOffset( float range );

	void CalculateNormals();
	void CalculateNormal( float* vec1, float* vec2, float* normal );

	void CalculateViewHeight();

};

#endif
