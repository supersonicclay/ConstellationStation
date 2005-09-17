//===========================================================================
// MgrTerrain.cpp
//
// CMgrTerrain
//   manager class for terrain functions.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "MgrTerrain.h"

#include "DlgOptionsTerr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrTerrain::CMgrTerrain()
{
}

CMgrTerrain::~CMgrTerrain()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Generate a new terrain with the same settings
void CMgrTerrain::New()
{
	terrain.New();
	Redraw();
}

// Opens the terrain options dialog
void CMgrTerrain::Options()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgOptionsTerr dialog;

	if( dialog.DoModal() == IDOK )
	{
		// Change terrain settings
		optionsMgr.SetTerrVisible( dialog.visible );
		optionsMgr.SetTerrTextured( dialog.textured );
	}
	else
	{
		// Reset options
		optionsMgr.SetTerrSeason( dialog.origSeason );
		optionsMgr.SetTerrWinColor( dialog.origWinColor );
		optionsMgr.SetTerrSprColor( dialog.origSprColor );
		optionsMgr.SetTerrSumColor( dialog.origSumColor );
		optionsMgr.SetTerrAutColor( dialog.origFalColor );
		optionsMgr.SetTerrRoughnessX100( dialog.origRoughnessX100 );
		terrain.MakeTerrain( TRUE ); // In case roughness was changed
	}

	Redraw();
}

// Toggles the terrain on and off
void CMgrTerrain::Toggle()
{
	optionsMgr.SwitchTerrVisible(); Redraw();
}