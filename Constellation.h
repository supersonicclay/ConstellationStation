// Constellation.h : interface of the CConstellation class
//
/////////////////////////////////////////////////////////////////////////////


#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include "Star.h"

class CConstLine
{

public:
	CConstLine();
	CConstLine( CStar* star1_, CStar* star2_ );
	~CConstLine();

private:
	CStar* star1;
	CStar* star2;

public:
	void SetStar1( CStar* star1_ );
	void SetStar2( CStar* star2_ );

	CStar* GetStar1() const;
	CStar* GetStar2() const;
	float GetX1() const;
	float GetY1() const;
	float GetZ1() const;
	float GetX2() const;
	float GetY2() const;
	float GetZ2() const;

};

class CConstellation : public CObject
{
DECLARE_SERIAL( CConstellation )

public:
	CConstellation();
	CConstellation( CString name_ );
	~CConstellation();

	const CConstellation& operator=( const CConstellation& c );

	void Serialize( CArchive& ar );

private:
	CString name;

	BOOL visible;

	int numLines;
	CConstLine* lines;

	int arraySize;

public:
	CString GetName() const;
	void SetName( CString name_ );

	BOOL IsVisible() const;
	void SwitchVisible();
	void SetVisible( BOOL visible_ );

	int GetNumLines() const;
	CConstLine* GetLine( int i ) const;

	void AddLine( CStar* star1, CStar* star2 );
	void DeleteLine( int lineNum );
	void CheckForDuplicateLines();
};

#endif
