#pragma once

#include "native.hpp"

#include <string>
#include <map>
#include <functional>

struct Actor;

struct TimerSet
{
	~TimerSet() = delete;

	struct TimerEvent
	{
		~TimerEvent() = delete;

		union
		{
			struct
			{
				float timeLeft;
				float initialTime;
				bool recurring;
				bool withContext;
			};
			struct
			{
				Padding(0x10);
				std::function<void __cdecl(void)> callback;	
				std::function<void __cdecl(Actor *)> contextCallback;
			};
			Padding(0x40);
		};	
	};

	std::map<std::string, TimerEvent> m_mTimers;
};