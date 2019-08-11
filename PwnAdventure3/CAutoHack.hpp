#pragma once

#include "CAutoHackCtrl.hpp"

// extras
struct Player;

class CAutoHack : public CAutoHackCtrl
{
public:
	CAutoHack();
	~CAutoHack();

	static CAutoHack *GetInstance()
	{
		static CAutoHack instance;
		return &instance;
	}

public:
	BOOL Init();

	BOOL ProcessActorHack(Player *pPlayer);
	BOOL ProcessPlayerHack(Player *pPlayer);
};