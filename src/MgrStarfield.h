//===========================================================================
// MgrStarfield.cpp
//
// CMgrStarfield
//   manager class for starfield functions.
//===========================================================================

#ifndef CS_MGRSTARFIELD_H
#define CS_MGRSTARFIELD_H 

#define MAX_DOCNAMELENGTH 50


class CMgrStarfield
{
// Construction
public:
	CMgrStarfield();


// Attributes
public:
	char title[MAX_DOCNAMELENGTH];	// Document's title

	// Saving / Opening
	OPENFILENAME ofn;
	char filename[MAX_PATH];		// Current open document's filename
	char cwd[MAX_PATH];				// Current working directory
	char starfieldDir[MAX_PATH];	// Starfield directory


// Operations
public:

	CBarStarf* GetStarfBar();

	void NewActual();
	void NewRandom();
	void Open();
	void Save();
	void SaveAs();

	void InitOFN( BOOL saving );
	int  CheckModified();
	void UpdateTitle();

	void Rotate();
	void Location();
	void Time();


// Destruction
public:
	~CMgrStarfield();

};

#endif
