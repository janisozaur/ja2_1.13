#include "types.h"
#include "NewGameSettings.h"
#include "FileMan.h"

#include <windows.h>
#include <stdio.h>

#define GAME_INI_FILE ".\\Ja2_113x.ini"

//#define PROMT_TO_CHECK_SETTINGS_TITLE L"Изменить настройки?" //change settings?
//#define PROMT_TO_CHECK_SETTINGS L"В процессе запуска игры была создана новая копия конфигурационного файла Ja2CW.ini со значениями по умолчанию. Желаете ли вы прервать запуск игры и изменить настройки?"
//new copy of config file Ja2CW.ini was created. do you want to change settings?

//UINT8 gubDeadLockDelay = 15;

//extern UINT16 SCREEN_WIDTH;
//extern UINT16 SCREEN_HEIGHT;

BOOLEAN gfStretch = FALSE;
BOOLEAN gfStretchWinGDI = FALSE;
BOOLEAN gfVSync = FALSE;

BOOLEAN gfAllowRain = TRUE;


UINT16 gusRainChancePerDay = 100, gusRainMinLength = 60, gusRainMaxLength = 180;

//BOOLEAN gfUseABResources = FALSE;

//UINT32  guiMaxTossSearchDist = 2;

//BOOLEAN gfShowItemShadow = TRUE;

extern UINT8 gubPlayerTurnSpeedUpFactor;
extern UINT8 gubEnemyTurnSpeedUpFactor;
extern UINT8 gubCreatureTurnSpeedUpFactor;
extern UINT8 gubMilitiaTurnSpeedUpFactor;
extern UINT8 gubCivTurnSpeedUpFactor;

extern UINT32 guiMinLightningInterval;
extern UINT32 guiMaxLightningInterval;
extern UINT32 guiMinDLInterval;
extern UINT32 guiMaxDLInterval;
extern UINT32 guiProlongLightningIfSeenSomeone;
extern UINT32 guiChanceToDoLightningBetweenTurns;

extern UINT32 guiMaxRainDrops;

//UINT32 guiMaxStrategicTeamSize = 48;

//BOOLEAN gfEnableEmergencyButton_SkipStrategicEvents = FALSE;

//extern FLOAT gdMajorMapVersion;

//#define MAJOR_MAP_VERSION		( gfUseABResources ? 6.00 : 5.00 )

//void NSInitGlobals()
//{
//	gdMajorMapVersion = (FLOAT)MAJOR_MAP_VERSION;
//}

typedef struct
{
	CHAR8* strParamName;
	CHAR8* strSectionName;
	LPVOID pVar;
	UINT8 ubVarType;
}TSetting;

//#define SET_SYSTEM "JA2 System Settings"
#define SET_RESOLUTION "JA2 Screen Resolution Settings"
#define SET_RAIN "JA2 Rain Settings"
#define SET_THUNDER "JA2 Thunder Settings"
#define SET_TURN_SPEED "JA2 Turnbased Animation Speed Settings"
//#define SET_STRATEGIC "JA2 Strategic Settings"
//#define SET_SPECIAL "JA2 Special Settings"
//#define SET_TACTICAL_AI "JA2 Tactical AI Settings"
//#define SET_GRAPHIC "JA2 Graphic Settings"

enum
{
	VT_UINT32,
	VT_UINT16,
	VT_UINT8,
	VT_INT32,
	VT_INT16,
	VT_INT8,
	VT_BOOLEAN
};

TSetting gpSettings[] = {
	//{"fUse_AB_Buka_ResourceFormat", SET_SYSTEM, &gfUseABResources, VT_BOOLEAN},

	//{"iScreenResolutionX", SET_RESOLUTION, &SCREEN_WIDTH, VT_UINT16},
	//{"iScreenResolutionY", SET_RESOLUTION, &SCREEN_HEIGHT, VT_UINT16},
	//{"fStretchScreen", SET_RESOLUTION, &gfStretch, VT_BOOLEAN},
	{"fVSync", SET_RESOLUTION, &gfVSync, VT_BOOLEAN},

	//{"fShowItemShadow", SET_GRAPHIC, &gfShowItemShadow, VT_BOOLEAN},

	{"iPlayerTurnSpeedUpFactor", SET_TURN_SPEED, (LPVOID)&gubPlayerTurnSpeedUpFactor, VT_UINT8},
	{"iEnemyTurnSpeedUpFactor", SET_TURN_SPEED, (LPVOID)&gubEnemyTurnSpeedUpFactor, VT_UINT8},
	{"iCreatureTurnSpeedUpFactor", SET_TURN_SPEED, (LPVOID)&gubCreatureTurnSpeedUpFactor, VT_UINT8},
	{"iMilitiaTurnSpeedUpFactor", SET_TURN_SPEED, (LPVOID)&gubMilitiaTurnSpeedUpFactor, VT_UINT8},
	{"iCivTurnSpeedUpFactor", SET_TURN_SPEED, (LPVOID)&gubCivTurnSpeedUpFactor, VT_UINT8},

	{"fAllowRain", SET_RAIN, &gfAllowRain, VT_BOOLEAN},
	{"iRainChancePerDay", SET_RAIN, &gusRainChancePerDay, VT_UINT16},
	{"iRainMinLengthInMinutes", SET_RAIN, &gusRainMinLength, VT_UINT16},
	{"iRainMaxLengthInMinutes", SET_RAIN, &gusRainMaxLength, VT_UINT16},
	{"iMaxRainDrops", SET_RAIN, &guiMaxRainDrops, VT_UINT32},

	{"iMinIntervalBetweenLightningsInRealtimeInSeconds", SET_THUNDER, &guiMinLightningInterval, VT_UINT32},
	{"iMaxIntervalBetweenLightningsInRealtimeInSeconds", SET_THUNDER, &guiMaxLightningInterval, VT_UINT32},
	{"iMinIntervalBetweenLightningAndThunderclapInSeconds", SET_THUNDER, &guiMinDLInterval, VT_UINT32},
	{"iMaxIntervalBetweenLightningAndThunderclapInSeconds", SET_THUNDER, &guiMaxDLInterval, VT_UINT32},
	{"iProlongDelayIfSeenSomeoneDuringLightningInTurnbasedInSeconds", SET_THUNDER, &guiProlongLightningIfSeenSomeone, VT_UINT32},
	{"iChanceToDoLightningBetweenTurns", SET_THUNDER, &guiChanceToDoLightningBetweenTurns, VT_UINT32},

//	{"iMaxStrategicTeamSize", SET_STRATEGIC, &guiMaxStrategicTeamSize, VT_UINT32},

//	{"iMaxTossSearchDist", SET_TACTICAL_AI, &guiMaxTossSearchDist, VT_UINT32},

//	{"fEnableEmergencyButton_NumLock_ToSkipStrategicEvents", SET_SPECIAL, &gfEnableEmergencyButton_SkipStrategicEvents, VT_BOOLEAN},

	{0,0,0,VT_UINT8}
};


void NSSaveSettings()
{
	CHAR8 zStr[ 256 ];
	TSetting* pCurr = gpSettings;
	INT32 iBuf;
	BOOLEAN fFileCreated = !FileExists( GAME_INI_FILE );

	//if( fFileCreated && FileExists( "Data\\russian.slf" ) )
	//	gfUseABResources = TRUE;

	FileDelete( GAME_INI_FILE );

	while( pCurr->pVar )
	{
			switch( pCurr->ubVarType )
			{
			case VT_UINT32:
				iBuf = *((UINT32*)pCurr->pVar);
				break;
			case VT_UINT16:
				iBuf = *((UINT16*)pCurr->pVar);
				break;
			case VT_UINT8:
				iBuf = *((UINT8*)pCurr->pVar);
				break;
			case VT_INT32:
				iBuf = *((INT32*)pCurr->pVar);
				break;
			case VT_INT16:
				iBuf = *((INT16*)pCurr->pVar);
				break;
			case VT_INT8:
				iBuf = *((INT8*)pCurr->pVar);
				break;
			case VT_BOOLEAN:
				iBuf = *((BOOLEAN*)pCurr->pVar);
				break;
			}

		sprintf( zStr, "%d", iBuf );

		WritePrivateProfileString( pCurr->strSectionName, pCurr->strParamName, zStr, GAME_INI_FILE );

		++pCurr;
	}

	//if( fFileCreated && MessageBoxW(0, PROMT_TO_CHECK_SETTINGS, PROMT_TO_CHECK_SETTINGS_TITLE, MB_YESNO) == IDYES )
	//{
	//	ShellExecuteW( 0, L"open", L"Ja2_113x.ini", 0, 0, SW_SHOWNORMAL);
	//	ExitProcess(0);
	//}

}

void NSLoadSettings()
{
	CHAR8 zStr[ 256 ];
	UINT32	uiRetVal=0;
	TSetting* pCurr = gpSettings;
	INT32 iBuf;

	while( pCurr->pVar )
	{
		uiRetVal = GetPrivateProfileString( pCurr->strSectionName, pCurr->strParamName, "", zStr, 256, GAME_INI_FILE );
		if( uiRetVal && strlen( zStr ) )
		{
			sscanf( zStr, "%d", &iBuf );
			switch( pCurr->ubVarType )
			{
			case VT_UINT32:
				*((UINT32*)pCurr->pVar) = iBuf;
				break;
			case VT_UINT16:
				*((UINT16*)pCurr->pVar) = iBuf;
				break;
			case VT_UINT8:
				*((UINT8*)pCurr->pVar) = iBuf;
				break;
			case VT_INT32:
				*((INT32*)pCurr->pVar) = iBuf;
				break;
			case VT_INT16:
				*((INT16*)pCurr->pVar) = iBuf;
				break;
			case VT_INT8:
				*((INT8*)pCurr->pVar) = iBuf;
				break;
			case VT_BOOLEAN:
				*((BOOLEAN*)pCurr->pVar) = iBuf;
				break;
			}
		}
		pCurr++;
	}

	//NSInitGlobals();
}