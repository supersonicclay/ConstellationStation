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

CConstLine::CConstLine(CStar* star1_, CStar* star2_)
{
	star1 = star1_;
	star2 = star2_;
}

CConstLine::~CConstLine()
{
}

void CConstLine::SetStar1(CStar* star1_)
{
	star1 = star1_;
}

void CConstLine::SetStar2(CStar* star2_)
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
	current = false;
}

CConstellation::CConstellation(CString name_)
{
	numLines = 0;
	visible = true;
	name = name_;
}

CConstellation::~CConstellation()
{
	delete lines;
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

BOOL CConstellation::IsCurrent() const
{
	return current;
}

void CConstellation::SetCurrent(BOOL current_)
{
	current = current_;

	/*
	if (current)
	{
		for (int i=0; i<numLines; i++)
		{
			lines[i].GetStar1()->SetColor(RED);
			lines[i].GetStar2()->SetColor(RED);
		}
	}
	else
	{
		for (int i=0; i<numLines; i++)
		{
			lines[i].GetStar1()->RestoreColor();
			lines[i].GetStar2()->RestoreColor();
		}
	}
	*/
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
	int i;
	CConstLine* copy = new CConstLine[numLines];

	// Backup lines
	for (i=0; i<numLines; i++)
		copy[i] = lines[i];

	// Increase array size
	lines = new CConstLine[++numLines];

	// Restore lines
	for (i=0; i<numLines-1; i++)
		lines[i] = copy[i];

	// Make the newest line
	lines[i].SetStar1(star1);
	lines[i].SetStar2(star2);
}

void CConstellation::DeleteLine(int lineNum)
{
	int i;

	/*
	/////////////////////////////
	// Check for isolated star //
	/////////////////////////////
	BOOL star1used = false;
	BOOL star2used = false;

	for (i=0; i<numLines; i++)
	{
		if (lines[lineNum].GetStar1() == lines[i].GetStar1() ||
			lines[lineNum].GetStar1() == lines[i].GetStar2())
		{
			star1used = true;
			break;
		}
	}
	for (i=0; i<numLines; i++)
	{
		if (lines[lineNum].GetStar2() == lines[i].GetStar1() ||
			lines[lineNum].GetStar2() == lines[i].GetStar2())
		{
			star2used = true;
			break;
		}
	}

	// Restore color of isolated stars
	if (!star1used)
		lines[lineNum].GetStar1()->RestoreColor();
	if (!star2used)
		lines[lineNum].GetStar2()->RestoreColor();
*/


	//////////////////////////////
	// Delete the selected line //
	//////////////////////////////

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

	// resize array
	lines = new CConstLine[numLines];

	// copy back into array
	for (i=0; i<numLines; i++)
	{
		lines[i] = newList[i];
	}

}

const CConstellation& CConstellation::operator =(const CConstellation& c)
{
	name = c.name;
	current = c.current;
	visible = c.visible;
	numLines = c.numLines;

	lines = new CConstLine[numLines];
	for (int i=0; i<numLines; i++)
	{
		lines[i] = c.lines[i];
	}

	return *this;
}

///Do you need??
void CConstellation::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << name
		   << current << visible
		   << numLines;
	}
	else
	{
		ar >> name
		   >> current >> visible
		   >> numLines;
	}

	// If were loading we need to allocate space for lines
	if (ar.IsLoading())
	{
		lines = new CConstLine[numLines];
	}

	/*///
	for (int i=0; i<numLines; i++)
	{
		lines[i].Serialize(ar);
	}
	*/
}
