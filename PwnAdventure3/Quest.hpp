#pragma once

#include "native.hpp"

#include "PwnAdventure.hpp"
#include "ActorRef.hpp"
#include "enums.hpp"

#include <string>
#include <map>

#pragma warning(disable : 4624)

// extras
struct IItem;
struct IPlayer;
struct IQuestState;

struct IQuestVtbl;
struct IQuest
{
	IQuestVtbl *vfptr;
};

struct IQuestVtbl
{
	const char *(__thiscall *GetName)(IQuest *);
	const char *(__thiscall *GetDescription)(IQuest *);
	IQuestState *(__thiscall *GetStartingState)(IQuest *);
	IQuestState *(__thiscall *GetStateByName)(IQuest *, const char *);
};

struct Quest : public IQuest
{
	std::string m_name;
	std::string m_description;
	std::map<std::string, IQuestState *> m_states;
	IQuestState *m_startState;
};

struct IQuestStateVtbl;
struct IQuestState
{
	IQuestStateVtbl *vfptr;
};

struct IQuestStateVtbl
{
	const char *(__thiscall *GetName)(IQuestState *);
	const char *(__thiscall *GetDescription)(IQuestState *);
	void(__thiscall *CheckForEarlyCompletion)(IQuestState *, IPlayer *);
	void(__thiscall *OnItemAcquired)(IQuestState *, IPlayer *, IItem *);
	void(__thiscall *OnItemPickupUsed)(IQuestState *, IPlayer *, const char *);
};

struct QuestState : public IQuestState
{
	Quest *m_quest;
	std::string m_name;
	std::string m_description;
};

struct ItemQuestState : public QuestState
{
	IItem *m_item;
	std::string m_nextState;
};

struct PickupQuestState : public QuestState
{
	std::string m_pickupName;
	std::string m_nextState;
};

struct QuestStateInfo
{
	std::string state;
	unsigned int count;
};

struct PlayerQuestState
{
	IQuestState *state;
	unsigned int count;
};

#pragma warning(pop)