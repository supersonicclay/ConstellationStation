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
#include "ConStation.h"
#include "DataConst.h"

#include "DataStarfield.h"

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

int		CDataConstLine::GetStar1()	{	return star1;			}
int		CDataConstLine::GetStar2()	{	return star2;			}
float	CDataConstLine::GetX1()	{	return starfield.GetStar(star1)->GetX();	}
float	CDataConstLine::GetY1()	{	return starfield.GetStar(star1)->GetY();	}
float	CDataConstLine::GetZ1()	{	return starfield.GetStar(star1)->GetZ();	}
float	CDataConstLine::GetX2()	{	return starfield.GetStar(star2)->GetX();	}
float	CDataConstLine::GetY2()	{	return starfield.GetStar(star2)->GetY();	}
float	CDataConstLine::GetZ2()	{	return starfield.GetStar(star2)->GetZ();	}


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
	numLines = 0;
	visible = TRUE;
}

CDataConst::CDataConst( CString name_ )
{
	numLines = 0;
	visible = TRUE;
	name = name_;
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
	numLines = c.numLines;
	lines = c.lines;
	visible = c.visible;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CString		CDataConst::GetName()		{	return name;		}
int			CDataConst::GetNumLines()	{	return numLines;	}
BOOL		CDataConst::IsVisible()		{	return visible;		}
CDataConstLine*	CDataConst::GetLine(int i)	{	return &lines[i];	}
CDataConstLine*	CDataConst::GetNewLine()	{	return &newLine;	}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataConst::SetName( CString name_ )		{	name = name_;		}
void CDataConst::SwitchVisible()				{	visible = !visible;	}
void CDataConst::SetVisible( BOOL visible_ )	{	visible = visible_;	}


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
		CSWarn( "One of newLine's stars aren't initialized", "CDataConst::AddLine" );
	}

	lines.push_back( CDataConstLine(newLine) );
	numLines++;

	CheckForDuplicateLines();
}

// Delete a line from this constellation indexed by lineNum
void CDataConst::DeleteLine( int lineNum )
{
	// Sanity check
	if( lineNum > numLines )
		CSError( "lineNum out of range", "CDataConst::DeleteLine" );

	line_vi li = lines.begin();
	for( int i=0; i<lineNum; ++i )
		++li;
	lines.erase( li );
	--numLines;
}

// Check this constellation for lines with the same endpoints
void CDataConst::CheckForDuplicateLines()
{
	for( int i=0; i<numLines; i++ )
	{
		for( int j=0; j<numLines; j++ )
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
		   >> numLines;
	}
	else
	{
		ar << name
		   << visible
		   << numLines;
	}

	// If we're loading, get the lines vector ready
	if( ar.IsLoading() )
	{
		lines.clear();
		for( int i=0; i<numLines; ++i )
			lines.push_back( CDataConstLine() );
	}

	// Serialize lines
	for( i=0; i<numLines; ++i )
		lines[i].Serialize(ar);
}
