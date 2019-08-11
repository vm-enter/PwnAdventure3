#pragma once

#include "native.hpp"
#include "TSingleton.hpp"
#include "PwnAdventure.hpp"

#include "ActorRef.hpp"

#include <string>
#include <vector>
#include <set>

struct Vector3;
struct Rotation;

struct IActor;
struct IPlayer;
struct ILocalPlayer;
struct IItem;
struct IQuest;
struct IQuestState;

struct Actor;
struct Player;
struct AIZone;

struct WorldVtbl;
struct World : public TSingleton_offset<World, GLOBAL_World>
{
	~World() = delete;

	union
	{
		WorldVtbl *vfptr;
		struct
		{
			Padding(0x04); // vfptr
			std::set<ActorRef<IPlayer>> m_players;
			std::set<ActorRef<IActor>> m_actors;
			std::map<unsigned int, ActorRef<IActor>> m_mActorsById;
			ILocalPlayer *m_pLocalPlayer;
			unsigned int m_nNextID;
			std::map<std::string, AIZone *> m_mAIZones;
		};
	};
};

static_assert_size(sizeof(World), 0x2C);

struct ClientWorld
{
	~ClientWorld() = delete;

	union
	{
		World World;
		struct
		{
			Padding(0x2C);
			ActorRef<IPlayer> m_pActivePlayer;
			float m_fTimeUntilNextNetTick;
		};
	};
};

typedef World ServerWorld;
typedef World LocalWorld;

struct WorldVtbl
{
	union
	{	
		void* (__thiscall *__vecDelDtor)(World *, unsigned int);
		struct // ClientWorldVtbl
		{
			Padding(0x04);  // __vecDelDtor
			void(__thiscall *Tick)(ClientWorld *, float deltaTime);
			Padding(0x08);	// ZeroCool::CanEquip
							// CowKing::ShouldWander
			void(__thiscall *AddLocalPlayer)(ClientWorld *, Player *player, ILocalPlayer *local);
			void(__thiscall *AddRemotePlayer)(World *, Player *player); // World::AddRemotePlayer
			void(__thiscall *AddRemotePlayerWithId)(World *, unsigned int id, Player *player);
			void(__thiscall *RemovePlayer)(World *, Player *player);
			void(__thiscall *Use)(ClientWorld *, Player *player, Actor *actor);
		};
		struct // WorldVtbl
		{			
			Padding(0x24);
			void(__thiscall *Activate)(World *, Player *, IItem *);
			void(__thiscall *Reload)(World *, Player *);
			void(__thiscall *Jump)(World *, bool);
			void(__thiscall *Sprint)(World *, bool);
			void(__thiscall *FireRequest)(World *, bool);
			void(__thiscall *TransitionToNPCState)(World *, Player *, std::string *);
			void(__thiscall *BuyItem)(World *, Player *, Actor *, IItem *, unsigned int);
			void(__thiscall *SellItem)(World *, Player *, Actor *, IItem *, unsigned int);
			void(__thiscall *Respawn)(World *, Player *);
			void(__thiscall *Teleport)(World *, Player *, std::string *);
			void(__thiscall *Chat)(World *, Player *, std::string *);
			void(__thiscall *FastTravel)(World *, Player *, std::string *);
			void(__thiscall *SetPvPDesired)(World *, Player *, bool);
			void(__thiscall *SubmitDLCKey)(World *, Player *, std::string *);
			void(__thiscall *SetCircuitInputs)(World *, Player *, std::string *, unsigned int);
			void(__thiscall *SendAddItemEvent)(World *, Player *, IItem *, unsigned int);
			void(__thiscall *SendRemoveItemEvent)(World *, Player *, IItem *, unsigned int);
			void(__thiscall *SendLoadedAmmoEvent)(World *, Player *, IItem *, unsigned int);
			void(__thiscall *SendPickedUpEvent)(World *, Player *, std::string *);
			void(__thiscall *EquipItem)(World *, Player *, char, IItem *);
			void(__thiscall *SetCurrentSlot)(World *, Player *, char);
			void(__thiscall *SendEquipItemEvent)(World *, Player *, char, IItem *);
			void(__thiscall *SendCurrentSlotEvent)(World *, Player *, char);
			void(__thiscall *SetCurrentQuest)(World *, Player *, IQuest *);
			void(__thiscall *SendSetCurrentQuestEvent)(World *, Player *, IQuest *);
			void(__thiscall *SendStartQuestEvent)(World *, Player *, IQuest *);
			void(__thiscall *SendAdvanceQuestToStateEvent)(World *, Player *, IQuest *, IQuestState *);
			void(__thiscall *SendCompleteQuestEvent)(World *, Player *, IQuest *);
			void(__thiscall *SendHealthUpdateEvent)(World *, Actor *, int);
			void(__thiscall *SendManaUpdateEvent)(World *, Player *, int);
			void(__thiscall *SendCountdownUpdateEvent)(World *, Player *, int);
			void(__thiscall *SendPvPCountdownUpdateEvent)(World *, Player *, bool, int);
			void(__thiscall *SendPvPEnableEvent)(World *, Player *, bool);
			void(__thiscall *SendStateEvent)(World *, Actor *, std::string *, bool);
			void(__thiscall *SendTriggerEvent)(World *, Actor *, std::string *, Actor *, bool);
			void(__thiscall *SendFireBulletsEvent)(World *, Actor *, IItem *, Vector3 *, unsigned int, float);
			void(__thiscall *SendDisplayEvent)(World *, Player *, std::string *);
			void(__thiscall *SendNPCConversationStateEvent)(World *, Player *, Actor *, std::string *);
			void(__thiscall *SendNPCConversationEndEvent)(World *, Player *);
			void(__thiscall *SendNPCShopEvent)(World *, Player *, Actor *);
			void(__thiscall *SendRespawnEvent)(World *, Player *, Vector3 *, Rotation *);
			void(__thiscall *SendTeleportEvent)(World *, Actor *, Vector3 *, Rotation *);
			void(__thiscall *SendRelativeTeleportEvent)(World *, Actor *, Vector3 *);
			void(__thiscall *SendReloadEvent)(World *, Player *, IItem *, IItem *, unsigned int);
			void(__thiscall *SendPlayerJoinedEvent)(World *, Player *);
			void(__thiscall *SendPlayerLeftEvent)(World *, Player *);
			void(__thiscall *SendPlayerItemEvent)(World *, Player *);
			void(__thiscall *SendActorSpawnEvent)(World *, Actor *);
			void(__thiscall *SendActorDestroyEvent)(World *, Actor *);
			void(__thiscall *SendExistingPlayerEvent)(World *, Player *, Player *);
			void(__thiscall *SendExistingActorEvent)(World *, Player *, Actor *);
			void(__thiscall *SendChatEvent)(World *, Player *, std::string *);
			void(__thiscall *SendKillEvent)(World *, Player *, Actor *, IItem *);
			void(__thiscall *SendCircuitOutputEvent)(World *, Player *, std::string *, unsigned int, std::vector<bool> *);
			void(__thiscall *SendActorPositionEvents)(World *, Player *);
			void(__thiscall *SendRegionChangeEvent)(World *, Player *, std::string *);
			void(__thiscall *SendLastHitByItemEvent)(World *, Player *, IItem *);
		};
	};
};