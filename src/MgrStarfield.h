//===========================================================================
// MgrStarfield.cpp
//
// CMgrStarfield
//   manager class for starfield functions.
//===========================================================================

#ifndef CS_MGRSTARFIELD_H
#define CS_MGRSTARFIELD_H 


class CMgrStarfield
{
// Construction
public:
	CMgrStarfield();


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

	void Rotate();
	void Location();
	void Time();


// Destruction
public:
	~CMgrStarfield();

};

#endif
