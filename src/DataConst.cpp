//===========================================================================
// DataConstellation.cpp
//
// CDataConstLine
//   constellation line data.
//   CDataConstLine uses indexes to stars.
//
// CDataConst
//   constellation data.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataConst.h"

IMPLEMENT_SERIAL( CDataConstLine, CObject, 1 )
IMPLEMENT_SERIAL( CDataConst, CObject, 1 )


//===========================================================================
// CDataConstLine
//===========================================================================


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataConstLine::CDataConstLine()
{
	star1 = star2 = -1;
}

CDataConstLine::CDataConstLine( int star1_, int star2_ )
{
	star1 = star1_;
	star2 = star2_;
}

CDataConstLine::CDataConstLine( const CDataConstLine& c )
{
	*this = c;
}

CDataConstLine::~CDataConstLine()
{
}

const CDataConstLine& CDataConstLine::operator=( const CDataConstLine& c )
{
	star1 = c.star1;
	star2 = c.star2;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

int		CDataConstLine::GetStar1()	{	return star1;								}
int		CDataConstLine::GetStar2()	{	return star2;								}
float	CDataConstLine::GetX1()		{	return starfield.GetStar(star1)->GetX();	}
float	CDataConstLine::GetY1()		{	return starfield.GetStar(star1)->GetY();	}
float	CDataConstLine::GetZ1()		{	return starfield.GetStar(star1)->GetZ();	}
float	CDataConstLine::GetX2()		{	return starfield.GetStar(star2)->GetX();	}
float	CDataConstLine::GetY2()		{	return starfield.GetStar(star2)->GetY();	}
float	CDataConstLine::GetZ2()		{	return starfield.GetStar(star2)->GetZ();	}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataConstLine::SetStar1( int star1_ )	{	star1 = star1_;	}
void CDataConstLine::SetStar2( int star2_ )	{	star2 = star2_;	}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataConstLine::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	// Serialize CDataConstLine attributes
	if( ar.IsLoading() )
	{
		ar >> star1 >> star2;
	}
	else
	{
		ar << star1 << star2;
	}
}



//===========================================================================
// CDataConst
//===========================================================================


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataConst::CDataConst()
{
	lineCount = 0;
	activeLineNum = -1;
	visible = TRUE;
}

CDataConst::CDataConst( CString n )
{
	name = n;
	lineCount = 0;
	activeLineNum = -1;
	visible = TRUE;
}

CDataConst::CDataConst( const CDataConst& c )
{
	*this = c;
}

CDataConst::~CDataConst()
{
}

const CDataConst& CDataConst::operator=( const CDataConst& c )
{
	name = c.name;
	lineCount = c.lineCount;
	lines = c.lines;
	activeLineNum = c.activeLineNum;
	visible = c.visible;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CString			CDataConst::GetName()			{	return name;			}
int				CDataConst::GetLineCount()		{	return lineCount;		}
int				CDataConst::GetActiveLineNum()	{	return activeLineNum;	}
BOOL			CDataConst::IsVisible()			{	return visible;			}
CDataConstLine*	CDataConst::GetLine(int i)		{	return &lines[i];		}
CDataConstLine*	CDataConst::GetNewLine()		{	return &newLine;		}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataConst::SetName( CString n )		{	name = n;			}
void CDataConst::SetActiveLineNum( int n )	{	activeLineNum = n;	}
void CDataConst::SwitchVisible()			{	visible = !visible;	}
void CDataConst::SetVisible( BOOL v )		{	visible = v;		}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Make newLine a real constellation line
void CDataConst::AddLine()
{
	if( newLine.GetStar1() == newLine.GetStar2() )
	{
		newLine.SetStar1(-1); newLine.SetStar2(-1);
		return;
	}

	if( newLine.GetStar1() == -1 || newLine.GetStar2() == -1 )
	{
		newLine.SetStar1(-1); newLine.SetStar2(-1);
		CSDebug( "A newLine's star isn't initialized", "CDataConst::AddLine" );
		return;
	}

	lines.push_back( CDataConstLine(newLine) );
	lineCount++;

	CheckForDuplicateLines();
}

// Delete a line from this constellation indexed by lineNum
void CDataConst::DeleteLine( int lineNum )
{
	// Sanity check
	if( lineNum > lineCount )
	{
		CSDebug( "lineNum out of range", "CDataConst::DeleteLine" );
		return;
	}

	line_vi li = lines.begin();
	for( int i=0; i<lineNum; ++i )
		++li;
	lines.erase( li );
	--lineCount;
}

// Check this constellation for lines with the same endpoints
void CDataConst::CheckForDuplicateLines()
{
	for( int i=0; i<lineCount; ++i )
	{
		for( int j=0; j<lineCount; ++j )
		{
			// we don't check for duplicate against itself
			if( i != j )
			{
				if( (lines[i].GetStar1() == lines[j].GetStar1()  &&
					 lines[i].GetStar2() == lines[j].GetStar2()) ||
					(lines[i].GetStar1() == lines[j].GetStar2()  &&
					 lines[i].GetStar2() == lines[j].GetStar1()) )
				{
					DeleteLine( j );
					return;
				}
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataConst::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int i;

	// Serialize CDataConst attributes
	if( ar.IsLoading() )
	{
		ar >> name
		   >> visible
		   >> lineCount;
	}
	else
	{
		ar << name
		   << visible
		   << lineCount;
	}

	// If we're loading, get the lines vector ready
	if( ar.IsLoading() )
	{
		lines.clear();
		for( int i=0; i<lineCount; ++i )
			lines.push_back( CDataConstLine() );
	}

	// Serialize lines
	for( i=0; i<lineCount; ++i )
		lines[i].Serialize(ar);
}
