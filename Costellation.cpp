// Constellation.cpp : implementation of the CConstellation class
//

#include "stdafx.h"
#include "ConStation.h"

#include "Constellation.h"
#include "Starfield.h"


////////////////
// CConstLine //
////////////////
CConstLine::CConstLine()
{
}

CConstLine::CConstLine(CStar* star1, CStar* star2)
{
	srcStar1 = star1;
	srcStar2 = star2;
}

CConstLine::~CConstLine()
{
}

void CConstLine::SetStars(CStar* star1, CStar* star2)
{
	srcStar1 = star1;
	srcStar2 = star2;
}

float CConstLine::GetX1() const
{
	return srcStar1->GetX();
}

float CConstLine::GetY1() const
{
	return srcStar1->GetY();
}

float CConstLine::GetZ1() const
{
	return srcStar1->GetZ();
}

float CConstLine::GetX2() const
{
	return srcStar2->GetX();
}

float CConstLine::GetY2() const
{
	return srcStar2->GetY();
}

float CConstLine::GetZ2() const
{
	return srcStar2->GetZ();
}


////////////////////
// CConstellation //
////////////////////
CConstellation::CConstellation()
{
	numLines = 0;
	visible = false;
}

CConstellation::~CConstellation()
{
}

CString CConstellation::GetName() const
{
	return name;
}

void CConstellation::SetName(CString name_)
{
	name = name_;
}

bool CConstellation::IsVisible() const
{
	return visible;
}

void CConstellation::SetVisible(bool visible_)
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
	lines[i].SetStars(star1, star2);
}

void CConstellation::DelLine(int lineNum)
{
	numLines--;
	// 
	for (int i=lineNum; i<numLines; i++)
		lines[i] = lines[i+1];
}
