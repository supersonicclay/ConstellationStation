// ConStationDoc.cpp : implementation of the CConStationDoc class
//

#include "stdafx.h"
#include "ConStation.h"
#include "ConStationDoc.h"

#include "ConStationView.h"

#include "Starfield.h"
#include "Terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc

IMPLEMENT_DYNCREATE( CConStationDoc, CDocument )

BEGIN_MESSAGE_MAP( CConStationDoc, CDocument )
	//{{AFX_MSG_MAP(CConStationDoc)
	ON_COMMAND( ID_STARF_SAVE, CDocument::OnFileSave )
	ON_COMMAND( ID_STARF_SAVEAS, CDocument::OnFileSaveAs )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc construction/destruction

CConStationDoc::CConStationDoc()
{
}

CConStationDoc::~CConStationDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc serialization

void CConStationDoc::Serialize( CArchive& ar )
{
	CDocument::Serialize(ar);    // Always call base class Serialize.

	starfield->Serialize( ar );
	terrain->Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// CConStationDoc diagnostics

#ifdef _DEBUG
void CConStationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CConStationDoc::Dump( CDumpContext& dc ) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CConStationDoc commands
