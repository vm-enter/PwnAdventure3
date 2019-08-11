#include "stdafx.h"

#include "CAutoHack.hpp"
#include "CMainHack.hpp"
#include "utils.hpp"
#include "headers.hpp"

#include "log.hpp"

static CpwnClient::PlayerTickT _CpwnClient__PlayerTick =
reinterpret_cast<CpwnClient::PlayerTickT>(ADDRESS_CpwnClient__PlayerTick);
void(__fastcall *CpwnClient__PlayerTick__Hook)(CpwnClient *, LPVOID, float fDeltaTime) = [](
	CpwnClient *pPwnClient, LPVOID, float fDeltaTime) -> void
{
	CAutoHack *pAutoHack;
	Player *pPlayer;

	if (pPwnClient->m_pPlayer != NULL)
	{
		pPlayer = (Player *)pPwnClient->m_pPlayer->IPlayer.vfptr->GetActorInterface(&pPwnClient->m_pPlayer->IPlayer);
		if (pPlayer != NULL)
		{
			pAutoHack = CAutoHack::GetInstance();
			pAutoHack->ProcessActorHack(pPlayer);
			pAutoHack->ProcessPlayerHack(pPlayer);
		}
	}

	return _CpwnClient__PlayerTick(pPwnClient, fDeltaTime);
};

CAutoHack::CAutoHack()
{
}

CAutoHack::~CAutoHack()
{
}

BOOL CAutoHack::Init()
{
	if (DetourFunction(TRUE, reinterpret_cast<LPVOID*>(&_CpwnClient__PlayerTick), CpwnClient__PlayerTick__Hook))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CAutoHack::ProcessActorHack(Player *pPlayer)
{
	World *pWorld;
	Actor *pActor;

	if (!this->m_bMobVac && !this->m_bItemVac && !this->m_bKamiVac)
		return FALSE;

	pWorld = World::GetInstance();
	if (!pWorld)
		return FALSE;

	DWORD dwClosestDistance = 0x7FFFFFFF, dwCurrentDistance = 0;
	Vector3 vecClosestPosition;
	Vector3 vec;

	pPlayer->Actor.GetPosition(&vec);
	vec.x += this->m_fMobDistanceX;
	vec.y += this->m_fMobDistanceY;
	vec.z += this->m_fMobDistanceZ;

	for (auto it = pWorld->m_actors.begin(); it != pWorld->m_actors.end(); it++)
	{
		pActor = (Actor *)it->p;
		if (pActor == (Actor *)pPlayer)
			continue;

		if (pActor->m_health > 0 &&
			pActor->IActor.vfptr->IsCharacter(&pActor->IActor))
		{
			if (this->m_bMobVac)
			{
				pActor->SetPosition(&vec);
			}

			Vector3 vecActor;
			pActor->GetPosition(&vecActor);

			dwCurrentDistance = (DWORD)vec.ToDistance(&vecActor);
			if (dwCurrentDistance < dwClosestDistance)
			{
				dwClosestDistance = dwCurrentDistance;
				vecClosestPosition = vecActor;
			}
		}
	}

	if (this->m_bKamiVac)
	{
		if (!vecClosestPosition.IsZero())
		{
			pPlayer->Teleport(&vecClosestPosition);
		}
	}

	return TRUE;
}

BOOL CAutoHack::ProcessPlayerHack(Player *pPlayer)
{
	CMainHack::GetInstance()->ProcessPlayerHack(pPlayer);

	return TRUE;
}
