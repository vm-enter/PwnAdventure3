#pragma once

#include "native.hpp"

#include <string>
#include <set>

struct Spawner;
struct AIZoneListener;
struct AIZone
{
	std::string m_name;
	unsigned int m_playerCount;
	std::set<AIZoneListener *> m_listeners;

	typedef void(__thiscall *OnPlayerEnteredT)(AIZone *);
	typedef void(__thiscall *OnPlayerLeftT)(AIZone *);

public:
	std::string GetName();
	unsigned int GetPlayerCount();
};

struct AIZoneListenerVtbl;
struct AIZoneListener
{
	AIZoneListenerVtbl *vfptr;
	AIZone *m_pZone;
};

struct AIZoneListenerVtbl
{
	union
	{
		void *(__thiscall *__vecDelDtor)(AIZoneListener *, unsigned int);
		struct // AIZoneListenerVtbl
		{
			Padding(0x04);
			void(__thiscall *OnAIZoneActivated)(AIZoneListener *);
			void(__thiscall *OnAIZoneDeactivated)(AIZoneListener *);
		};
		struct // SpawnerVtbl
		{
			Padding(0x0C);
			void(__thiscall *Tick)(Spawner *, float deltaTime);
			Padding(0x04); // __purecall
			unsigned int(__thiscall *GetOwner)(Spawner *);
			float(__thiscall *GetSpawnTimer)(Spawner *);
		};
	};
};

static_assert_size(sizeof(AIZone), 0x24)
static_assert_size(sizeof(AIZoneListener), 0x8)