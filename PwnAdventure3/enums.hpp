#pragma once

enum DamageType
{
	PhysicalDamage = 0,
	FireDamage = 1,
	ColdDamage = 2,
	ShockDamage = 3,
};

enum ItemRarity
{
	ResourceItem = 0,
	NormalItem = 1,
	RareItem = 2,
	LegendaryItem = 3,
	LeetItem = 4,
};

enum EnemyRank
{
	NormalEnemy = 0,
	EliteEnemy = 1,
	LegendaryEnemy = 2,
};

enum NPCStateTransitionType
{
	EndConversationTransition = 0,
	ContinueConversationTransition = 1,
	ShopTransition = 2,
};