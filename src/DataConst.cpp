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

int		CDataConstLine::GetStar1()	{	return star1;	}
int		CDataConstLine::GetStar2()	{	return star2;	}


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
}

CDataConst::CDataConst( CString n )
{
	name = n;
	lineCount = 0;
	activeLineNum = -1;
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
	center = c.center;
	lineCount = c.lineCount;
	lines = c.lines;
	activeLineNum = c.activeLineNum;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// Gets

CString			CDataConst::GetName()			{	return name;			}
vector3			CDataConst::GetCenter()			{	return center;			}
int				CDataConst::GetLineCount()		{	return lineCount;		}
int				CDataConst::GetActiveLineNum()	{	return activeLineNum;	}
CDataConstLine*	CDataConst::GetLine(int i)		{	return &lines[i];		}
CDataConstLine*	CDataConst::GetNewLine()		{	return &newLine;		}


/////////////////////////////////////////////////////////////////////////////
// Sets

void CDataConst::SetName( CString n )		{	name = n;			}
void CDataConst::SetActiveLineNum( int n )	{	activeLineNum = n;	}


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
	UpdateCenter();
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

	UpdateCenter();
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

// Update the center of this constellation
void CDataConst::UpdateCenter()
{
	int starCount = lineCount*2;
	CDataStar* s1;
	CDataStar* s2;

	// Find minimums and maximumss
	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	// Set max/min to initial star
	s1 = starfield.GetStar( GetLine(0)->GetStar1() );
	minX = maxX = s1->GetCenter().x;
	minY = maxY = s1->GetCenter().y;
	minZ = maxZ = s1->GetCenter().z;

	// Search constellation's stars
	for( int lineIndex = 0; lineIndex < lineCount; ++lineIndex )
	{
		s1 = starfield.GetStar( GetLine( lineIndex )->GetStar1() );
		s2 = starfield.GetStar( GetLine( lineIndex )->GetStar2() );

		// Check for minimum
		if( s1->GetCenter().x < minX )
			minX = s1->GetCenter().x;
		if( s1->GetCenter().y < minY )
			minY = s1->GetCenter().y;
		if( s1->GetCenter().z < minZ )
			minZ = s1->GetCenter().z;
		if( s2->GetCenter().x < minX )
			minX = s2->GetCenter().x;
		if( s2->GetCenter().y < minY )
			minY = s2->GetCenter().y;
		if( s2->GetCenter().z < minZ )
			minZ = s2->GetCenter().z;

		// Check for maximum
		if( s1->GetCenter().x > maxX )
			maxX = s1->GetCenter().x;
		if( s1->GetCenter().y > maxY )
			maxY = s1->GetCenter().y;
		if( s1->GetCenter().z > maxZ )
			maxZ = s1->GetCenter().z;
		if( s2->GetCenter().x > maxX )
			maxX = s2->GetCenter().x;
		if( s2->GetCenter().y > maxY )
			maxY = s2->GetCenter().y;
		if( s2->GetCenter().z > maxZ )
			maxZ = s2->GetCenter().z;
	}

	// Find center
	center.x = (maxX + minX) / 2;
	center.y = (maxY + minY) / 2;
	center.z = (maxZ + minZ) / 2;
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
		   >> center
		   >> lineCount;
	}
	else
	{
		ar << name
		   << center
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
