//===========================================================================
// DataConstellation.h
//
// CDataConstLine
//   constellation line data.
//   CDataConstLine uses indexes to stars.
//
// CDataConst
//   constellation data.
//===========================================================================

#ifndef CS_DATACONST_H
#define CS_DATACONST_H


/////////////////////////////////////////////////////////////////////////////
// CDataConstLine

class CDataConstLine : public CObject
{
DECLARE_SERIAL( CDataConstLine )

// Construction / Destruction
public:
	CDataConstLine();
	CDataConstLine( int star1_, int star2_ );
	CDataConstLine( const CDataConstLine& c );
	~CDataConstLine();

	const CDataConstLine& operator=( const CDataConstLine& c );
	void Serialize(CArchive& ar);


// Attributes
private:
	int star1;
	int star2;


// Methods
public:

// Gets
	int   GetStar1();
	int   GetStar2();
	float GetX1();
	float GetY1();
	float GetZ1();
	float GetX2();
	float GetY2();
	float GetZ2();

// Sets
	void SetStar1( int star1_ );
	void SetStar2( int star2_ );
};

// CDataConstLine vector
typedef std::vector<CDataConstLine> line_v;
typedef line_v::iterator            line_vi;


/////////////////////////////////////////////////////////////////////////////
// CDataConst

class CDataConst : public CObject
{
DECLARE_SERIAL( CDataConst )

// Construction / Destruction
public:
	CDataConst();
	CDataConst( CString name_ );
	CDataConst( const CDataConst& c );
	~CDataConst();

	const CDataConst& operator=( const CDataConst& c );
	void Serialize( CArchive& ar );


// Attributes
private:
	CString name;

	BOOL visible;

	int lineCount;
	line_v lines;

	int activeLineNum;

	CDataConstLine newLine;	// new (proposed) line


// Methods
public:

// Gets
	CString GetName();
	int GetLineCount();
	int GetActiveLineNum();
	CDataConstLine* GetLine( int i );
	CDataConstLine* GetNewLine();
	BOOL IsVisible();

// Sets
	void SetName( CString n );
	void SetActiveLineNum( int n );
	void SwitchVisible();
	void SetVisible( BOOL v );

// Methods
	void AddLine();
	void DeleteLine( int lineNum );
	void CheckForDuplicateLines();
};

// CDataConst Vector
typedef std::vector<CDataConst> const_v;
typedef const_v::iterator       const_vi;


#endif
