// Terrain.h : interface of the CTerrain class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef TERRAIN_H
#define TERRAIN_H

class CTerrain : public CObject
{
DECLARE_SERIAL(CTerrain)

public:
	CTerrain();
	~CTerrain();

	void Serialize(CArchive& ar);

private:
	float* heights;
	int arraySize;
	int size;	// arraySize - 1

	// Settings
	float scale;
	int iterations;
	float roughness;


public:
	float* GetHeights() const;
	float GetHeight(int i, int j) const;

	int GetArraySize() const;
	
	float GetScale() const;
	int GetIterations() const;
	float GetRoughness() const;

	int GetSize() const;

	void MakeTerrain();

	float AvgSquare(int i, int j, int midSize);
	float AvgDiamond(int i, int j, int midSize);
	float RandomOffset( float range );

};

#endif