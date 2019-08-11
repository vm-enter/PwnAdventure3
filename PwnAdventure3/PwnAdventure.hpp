#pragma once

//////////////////////////////////////////////////////////////////
// GameLogic.dll
//////////////////////////////////////////////////////////////////

// Global Variables
#define GLOBAL_World								0x00097D7C
#define GLOBAL_GameAPI								0x00097D80
#define GLOBAL_GameServerConnection					0x00097D94
#define GLOBAL_MasterServerConnection				0x00097D84
#define GLOBAL_ServerThread							0x00097D88

#define ADDRESS_g_masterServerHeartbeatTimer		0x00097D8C
#define ADDRESS_g_init								0x00097D90
#define ADDRESS_g_transitioning						0x00097D91
#define ADDRESS_g_watcherProcess					0x00097D92
#define ADDRESS_g_adminCharacter					0x00097D93

#define ADDRESS_GameAPI__GetItemByName				0x0001DE20

#define SIZE_Actor									0x00000070

#define OFFSET_Player__m_characterId				0x00000074
#define OFFSET_Player__m_currentSlot				0x00000180

// PwnAdeventure3.exe
#define ADDRESS_CpwnClient__PlayerTick				0x004C3760 // F3 ? ? 44 24 04 56 51 8B ? F3 ? ? ? ? E8 ? ? ? ? 8B ? ? ? ? ? 85 ? 74
#define OFFSET_CpwnClient__m_pPlayer				0x0000050C // 8B ? ? ? ? ? 85 ? 74 ? 8B ? FF ? F3