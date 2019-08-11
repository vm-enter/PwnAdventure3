#include "stdafx.h"

#include "GameAPI.hpp"
#include "extvars.hpp"

IItem *GameAPI::GetItemByName(const char * name)
{
	typedef IItem *(__thiscall *GetItemByNameT)(GameAPI *, const char *name);
	GetItemByNameT _GetItemByName =
		reinterpret_cast<GetItemByNameT>((int)g_GameLogicDLL + ADDRESS_GameAPI__GetItemByName);
	return _GetItemByName(this, name);
}
