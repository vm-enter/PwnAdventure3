#pragma once

#include "native.hpp"

#include "PwnAdventure.hpp"
#include "ActorRef.hpp"
#include "TimerSet.hpp"
#include "Loot.hpp"
#include "Vector3.hpp"
#include "enums.hpp"

#pragma warning(disable : 4624)

// extras
struct IItem;
struct IPlayer;
struct IUE4Actor;
struct Spawner;
struct AIState;

struct IActorVtbl;
struct IActor
{
	IActorVtbl *vfptr;
};

struct IActorVtbl
{
	union
	{
		void *(__thiscall *__vecDelDtor)(IActor *, unsigned int);
		struct
		{
			Padding(0x10);
			IPlayer *(__thiscall *GetPlayerInterface)(IActor *);
			void(__thiscall *AddRef)(IActor *);
			void(__thiscall *Release)(IActor *);
			void(__thiscall *OnSpawnActor)(IActor *, IUE4Actor *);
			void(__thiscall *OnDestroyActor)(IActor *);
			const char *(__thiscall *GetBlueprintName)(IActor *);
			bool(__thiscall *IsCharacter)(IActor *);
			bool(__thiscall *CanBeDamaged)(IActor *, IActor *);
			int(__thiscall *GetHealth)(IActor *);
			int(__thiscall *GetMaxHealth)(IActor *);
			void(__thiscall *Damage)(IActor *, IActor *, IItem *, int, DamageType);
			void(__thiscall *Tick)(IActor *, float);
			bool(__thiscall *CanUse)(IActor *, IPlayer *);
			void(__thiscall *OnUse)(IActor *, IPlayer *);
			void(__thiscall *OnHit)(IActor *, IActor *, Vector3 *, Vector3 *);
			void(__thiscall *OnAIMoveComplete)(IActor *);
			const char *(__thiscall *GetDisplayName)(IActor *);
			bool(__thiscall *IsElite)(IActor *);
			bool(__thiscall *IsPvPEnabled)(IActor *);
			IItem **(__thiscall *GetShopItems)(IActor *, unsigned int *);
			void(__thiscall *FreeShopItems)(IActor *, IItem **);
			int(__thiscall *GetBuyPriceForItem)(IActor *, IItem *);
			int(__thiscall *GetSellPriceForItem)(IActor *, IItem *);
			Vector3 *(__thiscall *GetLookPosition)(IActor *, Vector3 *result);
			Rotation *(__thiscall *GetLookRotation)(IActor *, Rotation *result);
			IActor *(__thiscall *GetOwner)(IActor *);
		};
	};
};

struct IUE4ActorVtbl;
struct IUE4Actor
{
	IUE4ActorVtbl *vfptr;
};

struct IUE4ActorVtbl
{
	union
	{
		void* (__thiscall *GetUE4Actor)(IUE4Actor *);
		struct
		{
			Padding(0x08);
			Vector3 *(__thiscall *GetPosition)(IUE4Actor *, Vector3 *result); // undocumented...
			Rotation *(__thiscall *GetRotation)(IUE4Actor *, Rotation *result);
			Vector3 *(__thiscall *GetProjectilePosition)(IUE4Actor *, Vector3 *result);
			Vector3 *(__thiscall *GetCharacterVelocity)(IUE4Actor *, Vector3 *result);
			void(__thiscall *SetPosition)(IUE4Actor *, Vector3 *);
			void(__thiscall *SetRotation)(IUE4Actor *, Rotation *);
			void(__thiscall *SetCharacterVelocity)(IUE4Actor *, Vector3 *);
			void(__thiscall *SetForwardAndStrafeMovement)(IUE4Actor *, float, float);
			void(__thiscall *InterpolatePositionAndRotation)(IUE4Actor *, Vector3 *, Rotation *, float, float);
			bool(__thiscall *MoveToLocation)(IUE4Actor *, Vector3 *);
			bool(__thiscall *MoveToRandomLocationInRadius)(IUE4Actor *, float);
			bool(__thiscall *MoveToActor)(IUE4Actor *, IActor *);
			void(__thiscall *OnUpdateState)(IUE4Actor *, const char *, bool);
			void(__thiscall *OnTriggerEvent)(IUE4Actor *, const char *, IActor *);
			void(__thiscall *OnUpdatePvPEnabled)(IUE4Actor *, bool);
			IActor *(__thiscall *LineTraceTo)(IUE4Actor *, Vector3 *);
			void(__thiscall *FireBullets)(IUE4Actor *, IItem *, int, DamageType, Vector3 *, unsigned int, float);
			void(__thiscall *LocalRespawn)(IUE4Actor *, Vector3 *, Rotation *);
			bool(__thiscall *IsOnGround)(IUE4Actor *);
			void(__thiscall *OnReload)(IUE4Actor *, unsigned int);
		};
	};
};
static_assert_size(sizeof(IUE4ActorVtbl), 0x58);

struct ILocalPlayer
{
	IUE4Actor IUE4Actor;
};

struct Actor
{
	union
	{
		IActor IActor;
		struct
		{
			Padding(0x04);
			unsigned int m_refs;
			unsigned int m_id;
			IUE4Actor *m_target;
			TimerSet *m_timers;
			std::string m_blueprintName;
			ActorRef<struct IActor> m_owner;
			int m_health;
			std::map<std::string, bool> m_states;
			float m_forwardMovementFraction;
			float m_strafeMovementFraction;
			Vector3 m_remotePosition;
			Vector3 m_remoteVelocity;
			Rotation m_remoteRotation;
			float m_remoteLocationBlendFactor;
			Spawner *m_spawner;
		};
		Padding(SIZE_Actor);
	};

public:
	Vector3 GetPosition(Vector3 *result);
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 *pVec);
	void SetHealth(int nHealth);
};
static_assert_size(sizeof(Actor), SIZE_Actor)

struct NPCStateTransition
{
	std::string text;
	NPCStateTransitionType type;
	std::string nextState;
};

struct NPCState
{
	std::string text;
	std::vector<NPCStateTransition> transitions;
};

struct NPC : public Actor
{
	std::map<std::string, NPCState> m_states;
};

struct Drop : public Actor
{
	std::map<IItem *, unsigned int> m_items;
	bool m_used;
};

struct ItemPickup : public Actor
{
	~ItemPickup() = delete;

	IItem *m_item;
	std::string m_pickupName;
};

struct GreatBallsOfFirePickup : public ItemPickup
{
};

template <unsigned int EggNumber>
struct GoldenEggPickup : public ItemPickup
{
};

struct RemoteActor : public Actor
{
	~RemoteActor() = delete;

	bool m_isCharacter;
};

struct AIActor : public Actor
{
	~AIActor() = delete;

	std::map<std::string, AIState *> m_states;
	AIState *m_initialState;
	AIState *m_currentState;
	ActorRef<struct Actor> m_target;
};

struct Projectile : public Actor
{
	~Projectile() = delete;

	IItem *m_item;
	float m_lifetime;
};

struct Enemy : public AIActor
{
	~Enemy() = delete;

	LootTable m_loot;
};

struct Magmarok : public Enemy
{
	bool m_healingActive;
	float m_healingTimeLeft;
	float m_advanceQuestTimer;
};

struct CowKing : public Enemy
{
};

struct MadCow : public Enemy
{
};

struct GiantRat : public Enemy
{
};

struct CaveSpider : public Enemy 
{
};

struct IceSpiderQueen : public Enemy 
{
};

struct BearChest;
struct Bear : public Enemy
{
	int m_attacksLeftInPosition;
	ActorRef<BearChest> m_chest;
};

struct BearChest : public Actor
{
	std::vector<ActorRef<Bear>> m_bears;
	std::map<ActorRef<IPlayer>, float> m_playerTimeLeft;
};

struct AngryBear : public Bear 
{
};

#pragma warning(pop)