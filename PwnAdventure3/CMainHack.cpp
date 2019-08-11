#include "stdafx.h"

#include "CMainHack.hpp"
#include "headers.hpp"

CMainHack::CMainHack()
{
	this->m_bUnlimitedHealth = FALSE;
	this->m_bUnlimitedMana = FALSE;
	this->m_bUnlimitedItem = FALSE;
	this->m_bNoCooldown = FALSE;
	this->m_bWalkingSpeed = FALSE;
	this->m_bJumpSpeed = FALSE;
	this->m_fWalkingSpeed = 200.f;	// default
	this->m_fJumpSpeed = 420.f;		// defualt
}

CMainHack::~CMainHack()
{
}

void CMainHack::ProcessPlayerHack(Player *pPlayer)
{
	if (this->m_bUnlimitedHealth)
		pPlayer->SetHealth(9999);

	if (this->m_bUnlimitedMana)
		pPlayer->SetMana(9999);

	if (this->m_bUnlimitedItem)
	{
		for (std::map<IItem *, ItemAndCount>::iterator it =
			pPlayer->m_inventory.begin(); it != pPlayer->m_inventory.end(); it++)
		{
			it->second.count = 999;
			it->second.loadedAmmo = 999;
		}
	}

	if (this->m_bNoCooldown)
	{
		for (std::map<IItem *, float>::iterator it =
			pPlayer->m_cooldowns.begin(); it != pPlayer->m_cooldowns.end(); it++)
		{
			it->second = 0.f;
		}
	}

	if (this->m_bWalkingSpeed)
		pPlayer->SetWalkingSpeed(this->m_fWalkingSpeed);

	if (this->m_bJumpSpeed)
		pPlayer->SetJumpSpeed(this->m_fJumpSpeed);
}

void CMainHack::ToggleUnlimitedHealth(BOOL bToggled)
{
	this->m_bUnlimitedHealth = bToggled;
}

void CMainHack::ToggleUnlimitedMana(BOOL bToggled)
{
	this->m_bUnlimitedMana = bToggled;
}

void CMainHack::ToggleUnlimitedItem(BOOL bToggled)
{
	this->m_bUnlimitedItem = bToggled;
}

void CMainHack::ToggleNoCooldown(BOOL bToggled)
{
	this->m_bNoCooldown = bToggled;
}

void CMainHack::ToggleWalkingSpeedHack(BOOL bToggled)
{
	this->m_bWalkingSpeed = bToggled;
}

void CMainHack::ToggleJumpSpeedHack(BOOL bToggled)
{
	this->m_bJumpSpeed = bToggled;
}

void CMainHack::SetWalkingSpeed(float fSpeed)
{
	this->m_fWalkingSpeed = fSpeed;
}

void CMainHack::SetJumpSpeed(float fSpeed)
{
	this->m_fJumpSpeed = fSpeed;
}
