#include "stdafx.h"

#include "AIZone.hpp"

std::string AIZone::GetName()
{
	return this->m_name;
}

unsigned int AIZone::GetPlayerCount()
{
	return this->m_playerCount;
}