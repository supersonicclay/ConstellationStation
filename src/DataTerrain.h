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
	int arraySize;  // size + 1

	vector3** upperNormals;
	vector3** lowerNormals;

	float viewHeight;


// Methods
public:

// Gets
	float** GetHeights();
	float GetHeight( int i, int j );

	int GetArraySize();
	int GetSize();
	float GetViewHeight();

	vector3 GetUpperNormal( int i, int j );
	vector3 GetLowerNormal( int i, int j );

// Sets
	void SetUpperNormal( int i, int j, vector3 n );
	void SetLowerNormal( int i, int j, vector3 n );

	void IncViewHeight();///
	void DecViewHeight();///

// Methods
	void MakeTerrain();

	float AvgSquare( int i, int j, int midSize );
	float AvgDiamond( int i, int j, int midSize );
	float RandomOffset( float range );

	void CalculateNormals();
	void CalculateNormal( vector3 vec1, vector3 vec2, vector3 normal );

	void CalculateViewHeight();

};

#endif
