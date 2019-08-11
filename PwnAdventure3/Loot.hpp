#pragma once

#include "native.hpp"

#include <vector>

// extras
struct IItem;

struct LootEntry
{
	IItem *item;
	unsigned int minCount;
	unsigned int maxCount;
	float weight;
};

struct LootTier
{
	std::vector<LootEntry> m_loot;
	float m_totalWeight;
};

struct LootTable
{
	struct TableEntry
	{
		unsigned int value;
		float weight;
	};

	float m_dropChance;
	std::vector<TableEntry> m_tiers;
	std::vector<TableEntry> m_counts;
	float m_totalTierWeight;
	float m_totalCountWeight;
	std::vector<LootEntry> m_additionalItems;
};