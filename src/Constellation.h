//===========================================================================
// Constellation.h
//
// CConstLine
//   constellation line that uses pointers to stars
//
// CConstellation
//   constellation class
//===========================================================================

#ifndef CS_CONSTELLATION_H
#define CS_CONSTELLATION_H

#include "Star.h"


/////////////////////////////////////////////////////////////////////////////
// CConstLine

class CConstLine : public CObject
{
DECLARE_SERIAL( CConstLine )

// Construction / Destruction
public:
	CConstLine();
	CConstLine( int star1_, int star2_ );
	CConstLine( const CConstLine& c );
	~CConstLine();

	const CConstLine& operator=( const CConstLine& c );
	void Serialize(CArchive& ar);


// Attributes
private:
	int star1;
	int star2;

// Methods
public:
	void SetStar1( int star1_ );
	void SetStar2( int star2_ );

	int   GetStar1();
	int   GetStar2();
	float GetX1();
	float GetY1();
	float GetZ1();
	float GetX2();
	float GetY2();
	float GetZ2();

};

// CConstLine vector
typedef std::vector<CConstLine> line_v;
typedef line_v::iterator        line_vi;


/////////////////////////////////////////////////////////////////////////////
// CConstellation

class CConstellation : public CObject
{
DECLARE_SERIAL( CConstellation )

// Construction / Destruction
public:
	CConstellation();
	CConstellation( CString name_ );
	CConstellation( const CConstellation& c );
	~CConstellation();

	const CConstellation& operator=( const CConstellation& c );
	void Serialize( CArchive& ar );


// Attributes
private:
	CString name;

	BOOL visible;

	int numLines;
	line_v lines;

	CConstLine newLine;	// new (proposed) line

// Methods
public:
	CString GetName();
	void SetName( CString name_ );

	int GetNumLines();
	CConstLine* GetLine( int i );
	CConstLine* GetNewLine();

	BOOL IsVisible();
	void SwitchVisible();
	void SetVisible( BOOL visible_ );

	BOOL StarIsActive( int i );

	void AddLine();
	void DeleteLine( int lineNum );
	void CheckForDuplicateLines();
};

// CConstellation Vector
typedef std::vector<CConstellation> constellation_v;
typedef constellation_v::iterator   constellation_vi;


#endif
