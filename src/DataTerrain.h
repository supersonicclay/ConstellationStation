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

// Construction / Destruction
public:

	CDataTerrain();
	~CDataTerrain();

	void Clear();
	void New();


// Attributes
private:
	UINT seed; // Used for predictable terrain

	float** heights;
	int size;
	int arraySize;    // size + 1
	float maxOffset;  // maximum absolute-valued height

	int texIters;
	int heightIters;
	float roughness;

	vector3** upperNormals;
	vector3** lowerNormals;

	UINT texID;
	texture_s winterTex;
	texture_s springTex;
	texture_s summerTex;
	texture_s autumnTex;

	float viewHeight;///
	float viewDistance;///


// Methods
public:

// Gets
	float** GetHeights();
	float GetHeight( int i, int j );

	int GetSize();
	int GetArraySize();

	vector3** GetUpperNormals();
	vector3** GetLowerNormals();
	vector3 GetUpperNormal( int i, int j );
	vector3 GetLowerNormal( int i, int j );

	UINT GetTexID();

/// Debug View
	float GetViewHeight();
	float GetViewDistance();
	void IncViewHeight();
	void DecViewHeight();
	void IncViewDistance();
	void DecViewDistance();


// Methods

	void Init();
	void MakeTerrain();

	BOOL LoadTextures();
	void MakeTexture();

	float AvgSquare( int i, int j, int midSize );
	float AvgDiamond( int i, int j, int midSize );
	float RandomOffset( float range );

	void CalculateNormals();
	void CalculateNormal( vector3 vec1, vector3 vec2, vector3 normal );

	void CalculateViewHeight();

};

#endif
