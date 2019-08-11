#pragma once

#include "native.hpp"

#include "PwnAdventure.hpp"
#include "ActorRef.hpp"
#include "Vector3.hpp"
#include "Actor.hpp"

#include <string>
#include <vector>
#include <map>
#include <set>

// extras
struct IItem;
struct ItemAndCount;
struct IInventory;
struct IFastTravel;
struct IAchievement;
struct IQuest;
struct IQuestState;
struct ILocalPlayer;
struct PlayerQuestState;
struct NPC;
struct WriteStream;

struct IPlayerVtbl;
struct IPlayer
{
	IPlayerVtbl *vfptr;
};

struct IPlayerVtbl
{
	union
	{
		IActor *(__thiscall *GetActorInterface)(IPlayer *);
		struct
		{
			Padding(0x24);
			IInventory *(__thiscall *GetInventory)(IPlayer *);
			unsigned int(__thiscall *GetItemCount)(IPlayer *, IItem *);
			unsigned int(__thiscall *GetLoadedAmmo)(IPlayer *, IItem *);
			bool(__thiscall *AddItem)(IPlayer *, IItem *, unsigned int count, bool allowPartial);
			bool(__thiscall *RemoveItem)(IPlayer *, IItem *, unsigned int);
			bool(__thiscall *AddLoadedAmmo)(IPlayer *, IItem *, IItem *, unsigned int);
			bool(__thiscall *RemoveLoadedAmmo)(IPlayer *, IItem *, unsigned int);
			IItem *(__thiscall *GetItemForSlot)(IPlayer *, unsigned int);
			void(__thiscall *EquipItem)(IPlayer *, unsigned int, IItem *);
			unsigned int(__thiscall *GetCurrentSlot)(IPlayer *);
			void(__thiscall *SetCurrentSlot)(IPlayer *, unsigned int);
			IItem *(__thiscall *GetCurrentItem)(IPlayer *);
			int(__thiscall *GetMana)(IPlayer *);
			bool(__thiscall *UseMana)(IPlayer *, int);
			void(__thiscall *SetItemCooldown)(IPlayer *, IItem *, float, bool);
			bool(__thiscall *IsItemOnCooldown)(IPlayer *, IItem *);
			float(__thiscall *GetItemCooldown)(IPlayer *, IItem *);
			bool(__thiscall *HasPickedUp)(IPlayer *, const char *);
			void(__thiscall *MarkAsPickedUp)(IPlayer *, const char *);
			IQuest **(__thiscall *GetQuestList)(IPlayer *, unsigned int *);
			void(__thiscall *FreeQuestList)(IPlayer *, IQuest **);
			IQuest *(__thiscall *GetCurrentQuest)(IPlayer *);
			void(__thiscall *SetCurrentQuest)(IPlayer *, IQuest *);
			PlayerQuestState(__thiscall *GetStateForQuest)(IPlayer *, IQuest *);
			void(__thiscall *StartQuest)(IPlayer *, IQuest *);
			void(__thiscall *AdvanceQuestToState)(IPlayer *, IQuest *, IQuestState *);
			void(__thiscall *CompleteQuest)(IPlayer *, IQuest *);
			bool(__thiscall *IsQuestStarted)(IPlayer *, IQuest *);
			bool(__thiscall *IsQuestCompleted)(IPlayer *, IQuest *);
			void(__thiscall *EnterAIZone)(IPlayer *, const char *);
			void(__thiscall *ExitAIZone)(IPlayer *, const char *);
			void(__thiscall *UpdateCountdown)(IPlayer *, int);
			bool(__thiscall *CanReload)(IPlayer *);
			void(__thiscall *RequestReload)(IPlayer *);
			float(__thiscall *GetWalkingSpeed)(IPlayer *);
			float(__thiscall *GetSprintMultiplier)(IPlayer *);
			float(__thiscall *GetJumpSpeed)(IPlayer *);
			float(__thiscall *GetJumpHoldTime)(IPlayer *);
			bool(__thiscall *CanJump)(IPlayer *);
			void(__thiscall *SetJumpState)(IPlayer *, bool);
			void(__thiscall *SetSprintState)(IPlayer *, bool);
			void(__thiscall *SetFireRequestState)(IPlayer *, bool);
			void(__thiscall *TransitionToNPCState)(IPlayer *, const char *);
			void(__thiscall *BuyItem)(IPlayer *, IActor *, IItem *, unsigned int);
			void(__thiscall *SellItem)(IPlayer *, IActor *, IItem *, unsigned int);
			void(__thiscall *EnterRegion)(IPlayer *, const char *);
			void(__thiscall *Respawn)(IPlayer *);
			void(__thiscall *Teleport)(IPlayer *, const char *);
			void(__thiscall *Chat)(IPlayer *, const char *);
			IFastTravel *(__thiscall *GetFastTravelDestinations)(IPlayer *, const char *);
			void(__thiscall *FastTravel)(IPlayer *, const char *, const char *);
			void(__thiscall *MarkAsAchieved)(IPlayer *, IAchievement *);
			bool(__thiscall *HasAchieved)(IPlayer *, IAchievement *);
			void(__thiscall *SubmitDLCKey)(IPlayer *, const char *);
			unsigned int(__thiscall *GetCircuitInputs)(IPlayer *, const char *);
			void(__thiscall *SetCircuitInputs)(IPlayer *, const char *, unsigned int);
			void(__thiscall *GetCircuitOutputs)(IPlayer *, const char *, bool *, unsigned int);
		};
	};
};

struct Player
{
	~Player() = delete;

	union
	{
		Actor Actor;	 // baseclass_00
		IPlayer IPlayer; // baseclass_70
		/* fuckstructoffset
		struct
		{
			Actor Actor;		// 0x0000(0x0070)
			IPlayer IPlayer;	// 0x0070
		}; */
		struct
		{
			Padding(OFFSET_Player__m_characterId);
			unsigned int m_characterId;
			std::string m_playerName;
			std::string m_teamName;
			char m_avatarIndex;
			unsigned int m_colors[4];
			std::map<IItem *, ItemAndCount> m_inventory;
			std::set<std::string> m_pickups;
			std::map<IItem *, float> m_cooldowns;
			std::map<std::string, unsigned int> m_circuitInputs;
			std::map<std::string, std::vector<bool>> m_circuitOutputs;
			bool m_adming;
			bool m_pvpEnabled;
			bool m_pvpDesired;
			float m_pvpChangeTimer;
			float m_pvpChangeReportedTimer;
			bool m_changingServerRegion;
			std::string m_currentRegion;
			std::string m_changeRegionDestination;
			std::set<std::string> m_aiZones;
			int m_mana;
			float m_manaRegenTimer;
			float m_healthRegenCooldown;
			float m_healthRegenTimer;
			int m_countdown;
			Vector3 m_remoteLockPosition;
			Rotation m_remoteLockRotation;
			IItem *m_equipped[10];
			unsigned int m_currentSlot;
			std::map<IQuest *, PlayerQuestState> m_questStates;
			IQuest *m_currentQuest;
			float m_walkingSpeed;
			float m_jumpSpeed;
			float m_jumpHoldTime;
			ActorRef<NPC> m_currentNPC;
			std::string m_currentNPCState;
			ILocalPlayer *m_localPlayer;
			WriteStream *m_eventsToSend;
			bool m_itemsUpdated;
			float m_itemSyncTimer;
			unsigned int m_chatMessageCounter;
			float m_chatFloodDecayTimer;
			IItem *m_lastHitByItem;
			float m_lastHitItemTimeLeft;
			float m_circuitStateCooldownTimer;
		};
	};

public:
	void SetHealth(int nHealth);
	void SetMana(int nMana);
	void SetWalkingSpeed(float fSpeed);
	void SetJumpSpeed(float fSpeed);
	void Teleport(float x, float y, float z);
	void Teleport(Vector3 *pVec);
};

static_assert_offset(Player, m_currentSlot, OFFSET_Player__m_currentSlot)
static_assert_offset(Player, m_circuitStateCooldownTimer, 0x1D8)
