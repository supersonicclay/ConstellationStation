// Starfield.h : interface of the CStarfield class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef STARFIELD_H
#define STARFIELD_H

#include "Star.h"
#include "Constellation.h"

class CStarfield
{
private:
	CStar *stars;
	CConstellation *constellations;

	int numStars;
	int numConstellations;

	int numCurConstellation;

////CStar* starMouseOver;

public:
	CStarfield();
	~CStarfield();

	CStar* GetStar(int i) const;
	CConstellation* GetConstellation(int i) const;
	int GetNumStars() const;
	int GetNumConstellations() const;
	int GetNumCurConstellation() const;
	void SetNumCurConstellation(int i);

	// Stars
	void SetupStars();

	// Constellation functions
	void AddConstellation();
	void AddConstLine(int starNum1, int starNum2);


};

#endif