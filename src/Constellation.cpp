//===========================================================================
// Constellation.cpp
//
// CConstLine
//   constellation line that uses pointers to stars
//
// CConstellation
//   constellation class
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "Constellation.h"

#include "Starfield.h"

IMPLEMENT_SERIAL( CConstLine, CObject, 1 )
IMPLEMENT_SERIAL( CConstellation, CObject, 1 )


//===========================================================================
// CConstLine
//===========================================================================


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CConstLine::CConstLine()
{
	star1 = star2 = -1;
}

CConstLine::CConstLine( int star1_, int star2_ )
{
	star1 = star1_;
	star2 = star2_;
}

CConstLine::CConstLine( const CConstLine& c )
{
	*this = c;
}

CConstLine::~CConstLine()
{
}

const CConstLine& CConstLine::operator=( const CConstLine& c )
{
	star1 = c.star1;
	star2 = c.star2;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

int		CConstLine::GetStar1()	{	return star1;			}
int		CConstLine::GetStar2()	{	return star2;			}
float	CConstLine::GetX1()	{	return starfield.GetStar(star1)->GetX();	}
float	CConstLine::GetY1()	{	return starfield.GetStar(star1)->GetY();	}
float	CConstLine::GetZ1()	{	return starfield.GetStar(star1)->GetZ();	}
float	CConstLine::GetX2()	{	return starfield.GetStar(star2)->GetX();	}
float	CConstLine::GetY2()	{	return starfield.GetStar(star2)->GetY();	}
float	CConstLine::GetZ2()	{	return starfield.GetStar(star2)->GetZ();	}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CConstLine::SetStar1( int star1_ )	{	star1 = star1_;	}
void CConstLine::SetStar2( int star2_ )	{	star2 = star2_;	}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CConstLine::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	// Serialize CConstLine attributes
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
// CConstellation
//===========================================================================


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CConstellation::CConstellation()
{
	numLines = 0;
	visible = TRUE;
}

CConstellation::CConstellation( CString name_ )
{
	numLines = 0;
	visible = TRUE;
	name = name_;
}

CConstellation::CConstellation( const CConstellation& c )
{
	*this = c;
}

CConstellation::~CConstellation()
{
}

const CConstellation& CConstellation::operator=( const CConstellation& c )
{
	name = c.name;
	numLines = c.numLines;
	lines = c.lines;
	visible = c.visible;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CString		CConstellation::GetName()		{	return name;		}
int			CConstellation::GetNumLines()	{	return numLines;	}
BOOL		CConstellation::IsVisible()		{	return visible;		}
CConstLine*	CConstellation::GetLine(int i)	{	return &lines[i];	}
CConstLine*	CConstellation::GetNewLine()	{	return &newLine;	}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CConstellation::SetName( CString name_ )		{	name = name_;		}
void CConstellation::SwitchVisible()				{	visible = !visible;	}
void CConstellation::SetVisible( BOOL visible_ )	{	visible = visible_;	}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Determine whether star number i is part of this constellation
BOOL CConstellation::StarIsActive( int i )
{
	if( i == newLine.GetStar1() || i == newLine.GetStar2() )
		return TRUE;
	for( int lineIndex=0; lineIndex<numLines; ++lineIndex )
	{
		if(	i == lines[lineIndex].GetStar1() ||
			i == lines[lineIndex].GetStar2() )
			return TRUE;
	}
	return FALSE;
}

// Make newLine a real constellation line
void CConstellation::AddLine()
{
	if( newLine.GetStar1() == newLine.GetStar2() )
	{
		newLine.SetStar1(-1); newLine.SetStar2(-1);
		return;
	}

	if( newLine.GetStar1() == -1 || newLine.GetStar2() == -1 )
	{
		newLine.SetStar1(-1); newLine.SetStar2(-1);
		CSWarn( "One of newLine's stars aren't initialized", "CConstellation::AddLine" );
	}

	lines.push_back( CConstLine(newLine) );
	numLines++;

	CheckForDuplicateLines();
}

// Delete a line from this constellation indexed by lineNum
void CConstellation::DeleteLine( int lineNum )
{
	// Sanity check
	if( lineNum > numLines )
		CSError( "lineNum out of range", "CConstellation::DeleteLine" );

	line_vi li = lines.begin();
	for( int i=0; i<lineNum; ++i )
		++li;
	lines.erase( li );
	--numLines;
}

// Check this constellation for lines with the same endpoints
void CConstellation::CheckForDuplicateLines()
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

void CConstellation::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int i;

	// Serialize CConstellation attributes
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
			lines.push_back( CConstLine() );
	}

	// Serialize lines
	for( i=0; i<numLines; ++i )
		lines[i].Serialize(ar);
}
