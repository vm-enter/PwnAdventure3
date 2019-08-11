#include "stdafx.h"

#include "Actor.hpp"

void Actor::SetPosition(float x, float y, float z)
{
	Vector3 vec(x, y, z);

	this->m_remotePosition = vec;
	if (this->m_target)
		this->m_target->vfptr->SetPosition(this->m_target, &vec);
}

void Actor::SetPosition(Vector3 *pVec)
{
	this->SetPosition(pVec->x, pVec->y, pVec->z);
}

Vector3 Actor::GetPosition(Vector3 * result)
{
	if (this->m_target)
		return *this->m_target->vfptr->GetPosition(this->m_target, result);

	Vector3 vec = *result;
	result->x = 0;
	result->y = 0;
	result->z = 0;
	return vec;
}

void Actor::SetHealth(int nHealth)
{
	this->m_health = nHealth;
}
