// ConStationDoc.cpp : implementation of the CConStationDoc class
//

#include "stdafx.h"
#include "ConStation.h"

#include "ConStationDoc.h"

#include "Starfield.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc

IMPLEMENT_DYNCREATE(CConStationDoc, CDocument)

BEGIN_MESSAGE_MAP(CConStationDoc, CDocument)
	//{{AFX_MSG_MAP(CConStationDoc)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_STARFIELD_SAVE, CDocument::OnFileSave)
	ON_COMMAND(ID_STARFIELD_SAVEAS, CDocument::OnFileSaveAs)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc construction/destruction

CConStationDoc::CConStationDoc()
{
	starfield = new CStarfield;
}

CConStationDoc::~CConStationDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc serialization

void CConStationDoc::Serialize(CArchive& ar)
{
	CDocument::Serialize( ar );    // Always call base class Serialize.

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar.WriteObject(this);
	}
	else
	{
		// TODO: add loading code here
		//ar.ReadObject(this);
	}
/* ////
CFile myFile("myfile.dat", CFile::modeCreate | CFile::modeReadWrite);
CAge  age(21), *pAge;

// Create a storing archive.
CArchive arStore(&myFile, CArchive::store);

// Write the object to the archive
arStore.WriteObject( &age );

// Close the storing archive
arStore.Close();

// Create a loading archive.
myFile.SeekToBegin();
CArchive arLoad(&myFile, CArchive::load);

// Verify the object is in the archive.
pAge = (CAge*) arLoad.ReadObject( RUNTIME_CLASS(CAge) );
ASSERT( age == *pAge );
*/
}

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc diagnostics

#ifdef _DEBUG
void CConStationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CConStationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CConStationDoc commands

BOOL CConStationDoc::OnNewDocument() 
{
////MessageBox("New Document!");

	starfield = new CStarfield;
//	return TRUE;
	
	return CDocument::OnNewDocument();
}

CStarfield* CConStationDoc::GetStarfield()
{
	return starfield;
}

