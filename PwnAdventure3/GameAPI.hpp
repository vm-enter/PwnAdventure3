#pragma once

#include "native.hpp"
#include "TSingleton.hpp"
#include "PwnAdventure.hpp"

// extras
struct IItem;

struct GameAPIVtbl;
struct GameAPI : public TSingleton_offset<GameAPI, GLOBAL_GameAPI>
{
	GameAPIVtbl *vfptr;

public:
	IItem *GetItemByName(const char* name);
};

struct GameAPIVtbl
{

};