#pragma once

#include "native.hpp"
#include "TSingleton.hpp"
#include "PwnAdventure.hpp"

#include <thread>
#include <mutex>
#include <queue>
#include <functional>

struct ServerConnectionVtbl;
struct ServerConnection
{
	~ServerConnection() = delete;

	union
	{
		ServerConnectionVtbl *vfptr;
		struct
		{
			bool m_bRunning;
			bool m_bValid;
			bool m_bReadyToDisconnect;
		};
		struct
		{
			Padding(0x08);
			std::thread m_thread;
			std::mutex m_mutex;
			std::queue<std::function<void __cdecl(void)>> m_serverQueue;
			std::condition_variable m_serverQueueEvent;

			struct ThreadActionQueue
			{
				std::mutex m_mutex;
				std::vector<std::function<void __cdecl(void)>> m_actions;
			} m_gameThreadActions;
		};
	};
};

struct ServerConnectionVtbl
{
	const char*(__thiscall *GetServerType)(ServerConnection *);
};

struct GameServerConnection : 
	public TSingleton_offset<GameServerConnection, GLOBAL_GameServerConnection>
{
	~GameServerConnection() = delete;

	union
	{
		ServerConnection ServerConnection;
		struct
		{
			Padding(0x3C);
			SOCKET m_sock;
		};
	};
};