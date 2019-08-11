#include "stdafx.h"
#include "Player.hpp"

void Player::SetHealth(int nHealth)
{
	this->Actor.SetHealth(nHealth);
}

void Player::SetMana(int nMana)
{
	this->m_mana = nMana;
}

void Player::Teleport(float x, float y, float z)
{
	this->Actor.SetPosition(x, y, z);
}

void Player::Teleport(Vector3 * pVec)
{
	this->Actor.SetPosition(pVec);
}

void Player::SetWalkingSpeed(float fSpeed)
{
	this->m_walkingSpeed = fSpeed;
}

void Player::SetJumpSpeed(float fSpeed)
{
	this->m_jumpSpeed = fSpeed;
}