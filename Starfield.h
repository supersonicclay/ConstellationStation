// Starfield.h : interface of the CStarfield class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef STARFIELD_H
#define STARFIELD_H

#include "Star.h"
#include "Constellation.h"

class CStarfield : public CObject
{
DECLARE_SERIAL(CStarfield)

public:
	CStarfield();
	~CStarfield();

	void Serialize(CArchive& ar);
	void SerializeConstLines(CArchive& ar);

private:
	CStar* stars;
	CConstellation* constellations;

	int numStars;

	int numConstellations;
	int numNewConstellations;
	int numCurConstellation;

	// Settings
	float latitude;
	float season;
	float time;
	BOOL  spinning;

	float rotX;
	float rotY;
	float zoom;

public:

// Gets
	CStar* GetStars() const;
	CConstellation* GetConstellations() const;
	CStar* GetStar(int i) const;
	CConstellation* GetConstellation(int i) const;
	CConstellation* GetConstellation(CString &name) const;
	CConstellation* GetCurConstellation() const;

	int GetNumStars() const;
	int GetNumConstellations() const;
	int GetNumNewConstellations() const;
	int GetNumCurConstellation() const;

	float GetLatitude() const;
	float GetSeason() const;
	float GetTime() const;
	BOOL  IsSpinning() const;

	float GetRotX() const;
	float GetRotY() const;
	float GetZoom() const;

// Sets
	void IncNumNewConstellations();
	void SetNumCurConstellation(int i);
	void SetLatitude(float latitude_);
	void SetSeason(float season_);
	void SetTime(float time_);
	void SwitchSpinning();
	// Adjusts
	void AdjTime(float deltaTime);
	void AdjRotX(float deltaRotX);
	void AdjRotY(float deltaRotY);
	void AdjZoom(float deltaZoom);

// Star functions
	void SetupStars();

// Constellation functions
	BOOL IsDuplicate(CString &name);
	void AddConstellation(CString &name);
	void DeleteConstellation();
	void RenameConstellation(CString &name);
	BOOL SetCurConstellation(CString name);
	void AddConstLine(int starNum1, int starNum2);

// View Manipulation
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn  ();
	void ZoomOut ();
	// View resets
	void ResetView ();
	void ResetRot  ();
	void ResetZoom ();

};

#endif