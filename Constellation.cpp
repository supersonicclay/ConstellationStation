// Constellation.cpp : implementation of the CConstellation class
//

#include "stdafx.h"
#include "ConStation.h"
#include "Constellation.h"

#include "Starfield.h"


IMPLEMENT_SERIAL (CConstellation, CObject, 0)


////////////////
// CConstLine //
////////////////
CConstLine::CConstLine()
{
}

CConstLine::CConstLine( CStar* star1_, CStar* star2_ )
{
	star1 = star1_;
	star2 = star2_;
}

CConstLine::~CConstLine()
{
}

void CConstLine::SetStar1( CStar* star1_ )
{
	star1 = star1_;
}

void CConstLine::SetStar2( CStar* star2_ )
{
	star2 = star2_;
}

CStar* CConstLine::GetStar1() const
{
	return star1;
}

CStar* CConstLine::GetStar2() const
{
	return star2;
}

float CConstLine::GetX1() const
{
	return star1->GetX();
}

float CConstLine::GetY1() const
{
	return star1->GetY();
}

float CConstLine::GetZ1() const
{
	return star1->GetZ();
}

float CConstLine::GetX2() const
{
	return star2->GetX();
}

float CConstLine::GetY2() const
{
	return star2->GetY();
}

float CConstLine::GetZ2() const
{
	return star2->GetZ();
}



////////////////////
// CConstellation //
////////////////////
CConstellation::CConstellation()
{
	numLines = 0;
	visible = true;

	// Reserve space for 5 lines
	arraySize = 5;
	lines = new CConstLine[arraySize];
}

CConstellation::CConstellation(CString name_)
{
	numLines = 0;
	visible = true;
	name = name_;
}

CConstellation::~CConstellation()
{
//	delete lines;
}

CString CConstellation::GetName() const
{
	return name;
}

void CConstellation::SetName(CString name_)
{
	name = name_;
}

BOOL CConstellation::IsVisible() const
{
	return visible;
}

void CConstellation::SwitchVisible()
{
	visible = !visible;
}

void CConstellation::SetVisible(BOOL visible_)
{
	visible = visible_;
}

int CConstellation::GetNumLines() const
{
	return numLines;
}

CConstLine* CConstellation::GetLine(int i) const
{
	return &lines[i];
}

void CConstellation::AddLine(CStar* star1, CStar* star2)
{
	numLines++;

	// If we have enough space
	if ( numLines <= arraySize )
	{
		lines[numLines-1].SetStar1(star1);
		lines[numLines-1].SetStar2(star2);
	}
	else	// We need to allocate more space
	{
		int i;
		CConstLine* copy = new CConstLine[arraySize];

		// Copy lines
		for (i=0; i<numLines-1; i++)
			copy[i] = lines[i];

		// Increase array size
		arraySize += 5;
		lines = new CConstLine[arraySize];

		// Restore lines
		for (i=0; i<numLines-1; i++)
			lines[i] = copy[i];

		// Make the newest line
		lines[i].SetStar1(star1);
		lines[i].SetStar2(star2);
	}

	CheckForDuplicateLines();
}

void CConstellation::DeleteLine(int lineNum)
{
	int i;

	// new temporary constellation list
	CConstLine* newList = new CConstLine[numLines-1];

	// copy old list into new list without the constellation being deleted
	int newListIndex = 0;
	for (i=0; i<numLines; i++)
	{
		if (i != lineNum)
			newList[newListIndex++] = lines[i];
	}

	numLines--;

	// erase array
	lines = new CConstLine[arraySize];

	// copy back into array
	for (i=0; i<numLines; i++)
	{
		lines[i] = newList[i];
	}
}

void CConstellation::CheckForDuplicateLines()
{
	// Since we check for duplicates every time we add a line,
	//  there should never be more than 1 duplicate

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

const CConstellation& CConstellation::operator =(const CConstellation& c)
{
	name = c.name;
	visible = c.visible;
	numLines = c.numLines;

	lines = new CConstLine[numLines];
	for (int i=0; i<numLines; i++)
	{
		lines[i] = c.lines[i];
	}

	return *this;
}

void CConstellation::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << name
		   << visible
		   << numLines;
	}
	else
	{
		ar >> name
		   >> visible
		   >> numLines;
	}

	// If were loading we need to allocate space for lines
	if (ar.IsLoading())
	{
		lines = new CConstLine[numLines];
	}

	// NOTE: Serialization for ConstLines is done in CStarfield
}
