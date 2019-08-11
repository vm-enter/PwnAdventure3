#include "stdafx.h"

#include "CAutoHackCtrl.hpp"

CAutoHackCtrl::CAutoHackCtrl()
{
	this->m_bMobVac = FALSE;
	this->m_bItemVac = FALSE;
	this->m_bKamiVac = FALSE;

	this->m_fMobDistanceX = 0.f;
	this->m_fMobDistanceY = 0.f;
	this->m_fMobDistanceZ = 0.f;
}

CAutoHackCtrl::~CAutoHackCtrl()
{

}

void CAutoHackCtrl::ToggleMobVac(BOOL bToggled)
{
	this->m_bMobVac = bToggled;
}

void CAutoHackCtrl::ToggleItemVac(BOOL bToggled)
{
	this->m_bItemVac = bToggled;
}

void CAutoHackCtrl::ToggleKamiVac(BOOL bToggled)
{
	this->m_bKamiVac = bToggled;
}

void CAutoHackCtrl::SetMobDistanceX(float fDistance)
{
	this->m_fMobDistanceX = fDistance;
}

void CAutoHackCtrl::SetMobDistanceY(float fDistance)
{
	this->m_fMobDistanceY = fDistance;
}

void CAutoHackCtrl::SetMobDistanceZ(float fDistance)
{
	this->m_fMobDistanceZ = fDistance;
}

