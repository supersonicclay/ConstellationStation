//===========================================================================
// MgrText.cpp
//
// CMgrText
//   manager class for text functions.
//===========================================================================

#ifndef CS_MGRTEXT_H
#define CS_MGRTEXT_H 


class CMgrText
{
// Construction
public:
	CMgrText();


// Attributes
public:

	LOGFONT constFont;
	LOGFONT	starFont;
	LOGFONT dirFont;
	UINT constBase;
	UINT starBase;
	UINT dirBase;

// Methods
public:
	void InitFonts();
	void BuildFonts();
	void KillFonts();

	void Options();
	void LoadDefaults();

	void TypeConst( CDataConst* constellation );
	void TypeStar( CDataStar* star );
	void TypeDirections( );

// Destruction
public:
	~CMgrText();

};

#endif
