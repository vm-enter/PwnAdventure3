#pragma once

#include "native.hpp"

#include "enums.hpp"

// extras
struct IPlayer;

struct IItemVtbl;
struct IItem
{
	IItemVtbl *vfptr;
};

struct IItemVtbl
{
	union
	{
		void *(__thiscall *__vecDelDtor)(IItem *, unsigned int);
		struct
		{
			Padding(0x10);
			const char *(__thiscall *GetDescription)(IItem *);
			const char *(__thiscall *GetFlavorText)(IItem *);
			bool(__thiscall *CanEquip)(IItem *);
			unsigned int(__thiscall *GetMaximumCount)(IItem *);
			bool(__thiscall *CanActivate)(IItem *, IPlayer *);
			bool(__thiscall *CanActivateInInventory)(IItem *);
			void(__thiscall *Activate)(IItem *, IPlayer *);
			bool(__thiscall *ShowInInventory)(IItem *);
			bool(__thiscall *ShowEventOnPickup)(IItem *);
			bool(__thiscall *ShowEventOnDuplicatePickup)(IItem *);
			bool(__thiscall *ShowNotificationOnPickup)(IItem *);
			float(__thiscall *GetCooldownTime)(IItem *);
			ItemRarity(__thiscall *GetItemRarity)(IItem *);
			IItem *(__thiscall *GetAmmoType)(IItem *);
			unsigned int(__thiscall *GetClipSize)(IItem *);
			int(__thiscall *GetDamage)(IItem *);
			int(__thiscall *GetDamagePerSecond)(IItem *);
			DamageType(__thiscall *GetDamageType)(IItem *);
			int(__thiscall *GetManaCost)(IItem *);
			const char *(__thiscall *GetCustomCostDescription)(IItem *);
			bool(__thiscall *IsAutoFire)(IItem *);
			unsigned int(__thiscall *GetNumberOfProjectiles)(IItem *);
			float(__thiscall *GetReloadTime)(IItem *, int);
			bool(__thiscall *HasPartialReload)(IItem *);
			float(__thiscall *GetRange)(IItem *);
			int(__thiscall *GetTradeValue)(IItem *);
			bool(__thiscall *IsDynamic)(IItem *);
			bool(__thiscall *IsUpdating)(IItem *);
		};
	};
};

/*
struct Item
{
	union
	{
		IItem IItem;
		struct
		{
		};
	};
};
*/

typedef IItem Item;

struct ZeroCool
{
	union
	{
		Item Item;
		struct
		{
		};
	};
};

struct ItemCountInfo
{
	unsigned int count;
	unsigned int loadedAmmo;
};

struct ItemAndCount
{
	IItem *item;
	unsigned int count;
	unsigned int loadedAmmo;
};

struct IInventoryVtbl;
struct IInventory
{
	IInventoryVtbl *vfptr;
};

struct IInventoryVtbl
{
	void *(__thiscall *__vecDelDtor)(IInventory *, unsigned int);
	unsigned int(__thiscall *GetCount)(IInventory *);
	IItem *(__thiscall *GetItem)(IInventory *, unsigned int);
	unsigned int(__thiscall *GetItemCount)(IInventory *, unsigned int);
	unsigned int(__thiscall *GetItemLoadedAmmo)(IInventory *, unsigned int);
	void(__thiscall *Destroy)(IInventory *);
};

struct Inventory
{
	~Inventory() = delete;

	union
	{
		IInventory IInventory;
		struct
		{
			Padding(0x04);
			std::vector<ItemAndCount> m_items;
		};
	};
};