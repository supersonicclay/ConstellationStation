// Constellation.h : interface of the CConstellation class
//
/////////////////////////////////////////////////////////////////////////////


#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include "Star.h"

class CConstLine
{
private:
	CStar* srcStar1;
	CStar* srcStar2;

public:
	CConstLine();
	CConstLine(CStar* star1, CStar* star2);
	~CConstLine();

	void SetStars(CStar* star1, CStar* star2);

	float GetX1() const;
	float GetY1() const;
	float GetZ1() const;
	float GetX2() const;
	float GetY2() const;
	float GetZ2() const;

};

class CConstellation
{
private:
	CString name;

	bool visible;

	int numLines;
	CConstLine* lines;

public:
	CConstellation();
	~CConstellation();

	CString GetName() const;
	void SetName(CString name_);

	bool IsVisible() const;
	void SetVisible(bool visible_);

	int GetNumLines() const;
	CConstLine* GetLine(int i) const;

	void AddLine(CStar* star1, CStar* star2);
	void DelLine(int lineNum);
};

#endif
