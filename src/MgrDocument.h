//===========================================================================
// MgrDocument.cpp
//
// CMgrDocument
//   manager class for document functions.
//===========================================================================

#ifndef CS_MGRDOCUMENT_H
#define CS_MGRDOCUMENT_H 


class CMgrDocument
{
// Construction
public:
	CMgrDocument();


// Attributes
public:
	char title[MAX_DOC_NAME];		// Document's title

	// Saving / Opening
	OPENFILENAME ofn;
	char filename[MAX_PATH];		// Current open document's filename
	char cwd[MAX_PATH];				// Current working directory
	char starfieldDir[MAX_PATH];	// Starfield directory


// Methods
public:
	void NewActual();
	void NewRandom();
	void Open();
	void Save();
	void SaveAs();

	void InitOFN( BOOL saving );
	int  CheckModified();
	void UpdateTitle();


// Destruction
public:
	~CMgrDocument();

};

#endif
