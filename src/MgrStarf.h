//===========================================================================
// MgrStarf.cpp
//
// CMgrStarf
//   manager class for starfield functions.
//===========================================================================

#ifndef CS_MGRSTARF_H
#define CS_MGRSTARF_H 


class CMgrStarf
{
// Construction
public:
	CMgrStarf();


// Attributes
public:


// Operations
public:

	CBarStarf* GetStarfBar();

	void Rotate();
	void Location();
	void Time();


// Destruction
public:
	~CMgrStarf();

};

#endif
