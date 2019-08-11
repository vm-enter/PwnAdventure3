#pragma once

#include "native.hpp"

#include "ActorRef.hpp"
#include "Vector3.hpp"
#include "AIZone.hpp"

#include <vector>

// extras
struct Actor;

struct Spawner
{
	~Spawner() = delete;

	union
	{
		AIZoneListener AIZoneListener;
		struct
		{
			Padding(0x08);
			std::vector<ActorRef<Actor>> m_actors;
			Vector3 m_position;
			Rotation m_rotation;
			unsigned int m_maxActors;
			float m_maxSpawnTimer;
			float m_currentSpawnTimer;
		};
	};
};

typedef Spawner CaveSpiderSpawner;
typedef Spawner GiantRatSpawner;
typedef Spawner PirateRatSpawner;
typedef Spawner CliffRatSpawner;

static_assert_size(sizeof(Spawner), 0x38)