//===========================================================================
// MgrConst.cpp
//
// CMgrConst
//   manager class for constellations functions.
//===========================================================================

#ifndef CS_MGRCONST_H
#define CS_MGRCONST_H 

#include "BarConst.h"

class CMgrConst
{
// Construction
public:
	CMgrConst();

// Attributes
public:


// Operations
public:
	CBarConst* GetConstBar();

	void Add();
	void Delete();
	void Rename();
	void Hide();
	void AddLine();
	void DeleteLine();
	void HideAll();
	void ShowAll();
	void ShowHide();

	void Options();
	void Toggle();


// Destruction
public:
	~CMgrConst();

};

#endif
