// Constellation.h : interface of the CConstellation class
//
/////////////////////////////////////////////////////////////////////////////


#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include "Star.h"

class CConstLine
{
private:
	CStar* star1;
	CStar* star2;

public:
	CConstLine();
	CConstLine(CStar* star1_, CStar* star2_);
	~CConstLine();

	void SetStars(CStar* star1_, CStar* star2_);

	CStar* GetStar1() const;
	CStar* GetStar2() const;
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

	BOOL visible;
	BOOL active;

	int numLines;
	CConstLine* lines;

public:
	CConstellation();
	CConstellation(CString name_);
	~CConstellation();

	CString GetName() const;
	void SetName(CString name_);

	BOOL IsVisible() const;
	void SwitchVisible();
	void SetVisible(BOOL visible_);

	BOOL GetActive() const;
	void SetActive(BOOL active_=true);

	int GetNumLines() const;
	CConstLine* GetLine(int i) const;

	void AddLine(CStar* star1, CStar* star2);
	void DeleteLine(int lineNum);
};

#endif
