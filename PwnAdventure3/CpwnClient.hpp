#pragma once

#include "native.hpp"

#include "Player.hpp"

// name is wrong
struct CpwnClient
{
	union
	{
		struct
		{
			Padding(OFFSET_CpwnClient__m_pPlayer); // 8B ? ? ? ? ? 85 ? 74 ? 8B ? FF ? F3
			Player *m_pPlayer;
		};
	};

	typedef void(__thiscall *PlayerTickT)(CpwnClient *, float fDeltaTime);
};