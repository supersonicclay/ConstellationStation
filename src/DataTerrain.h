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
	UINT seed; // Used for predictable terrain

	float** heights;
	int size;
	int arraySize;    // size + 1
	float maxHeight;  // used to compute ratio for texture
	float minHeight;  // used to compute ratio for texture

	season_e season;

	int heightIters;
	float roughness;

	vector3** upperNormals;
	vector3** lowerNormals;

	UINT texID;
	texture_s winterTex;
	texture_s springTex;
	texture_s summerTex;
	texture_s autumnTex;


// Methods
public:

// Gets
	float** GetHeights();
	float GetHeight( int i, int j );
	float GetMiddleHeight();

	int GetSize();
	int GetArraySize();

	float GetRoughness();

	vector3** GetUpperNormals();
	vector3** GetLowerNormals();
	vector3 GetUpperNormal( int i, int j );
	vector3 GetLowerNormal( int i, int j );

	UINT GetTexID();

// Sets
	void SetRoughness( float x );


// Methods

	void GetValuesFromOptions();

	void InitArrays();
	void DeleteArrays();

	void MakeTerrain( BOOL loadOptions );

	BOOL LoadTextures();
	void MakeTexture();

	float AvgSquare( int i, int j, int midSize );
	float AvgDiamond( int i, int j, int midSize );
	float RandomOffset( float range );

	void CalculateNormals();
	void CalculateNormal( vector3 vec1, vector3 vec2, vector3 normal );

};

#endif
