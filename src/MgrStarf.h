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


// Methods
public:

	CBarStarf* GetStarfBar();

	void StarOptions();
	void ConstOptions();
	void SunOptions();

	void ToggleStars();
	void ToggleConsts();
	void ToggleSun();
	void ToggleSunshine();

	void Rotate();
	void Location();
	void Time();


// Destruction
public:
	~CMgrStarf();

};

#endif
