#ifndef __MILITIA_CONTROL_H
#define __MILITIA_CONTROL_H

#include "Types.h"
#include "Soldier Control.h"
#include "mousesystem.h"
#include "Strategic Movement.h"

void PrepareMilitiaForTactical();
void RemoveMilitiaFromTactical();
void ResetMilitia();
void HandleMilitiaPromotions();

extern BOOLEAN gfStrategicMilitiaChangesMade;

extern INT32 ghMilitiaControlBox;
//extern INT32 ghTalkToAllBox;

extern MOUSE_REGION    gMilitiaControlScreenMaskRegion;
extern MOUSE_REGION    gMilitiaControlMenuRegion[  ];
//extern MOUSE_REGION	   gTalkToAllMenuRegion[  ];

extern BOOLEAN fShownMilitiaControlMenu;
extern BOOLEAN fFirstClickInMilitiaControlScreenMask;


// figure out the assignment menu pop up box positions
void DetermineMilitiaControlBoxPositions( void );

// set x,y position in tactical 
void SetTacticalPopUpMilitiaControlBoxXY( SOLDIERTYPE *pSoldier );

// pop up menu mouse regions
void CreateDestroyMouseRegionsForMilitiaControlMenu( void );
void MilitiaControlMenuMvtCallBack(MOUSE_REGION * pRegion, INT32 iReason );
void MilitiaControlMenuBtnCallBack( MOUSE_REGION * pRegion, INT32 iReason );

//void CreateDestroyMouseRegionsForTalkToAllMenu( void );
//void TalkToAllMenuMvtCallBack(MOUSE_REGION * pRegion, INT32 iReason );
//void TalkToAllMenuBtnCallback( MOUSE_REGION * pRegion, INT32 iReason );


// misc assignment GUI functions
void HandleShadingOfLinesForMilitiaControlMenu( void );
void CreateDestroyScreenMaskForMilitiaControlMenus( void );

// rebuild assignments box
void RebuildMilitiaControlBox( void );

void CreateMilitiaControlBox( void );
//void CreateTalkToAllBox( void );

BOOLEAN CreateDestroyMilitiaControlPopUpBoxes( void );

extern SOLDIERTYPE *pTMilitiaSoldier;



#endif