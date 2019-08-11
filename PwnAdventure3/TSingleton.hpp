#pragma once

#include "native.hpp"
#include "extvars.hpp"

template <typename T, int TSingleton_pointer>
class TSingleton
{
	TSingleton() = delete;
	~TSingleton() = delete;

public:
	static T* GetInstance()
	{
		return *reinterpret_cast<T**>(TSingleton_pointer);
	}

	static bool IsInstantiated()
	{
		return (GetInstance() != nullptr);
	}
};

template <typename T, int TSingleton_pointer_offset>
class TSingleton_offset
{
	TSingleton_offset() = delete;
	~TSingleton_offset() = delete;

public:
	static T* GetInstance()
	{
		return *reinterpret_cast<T**>((int)g_GameLogicDLL + TSingleton_pointer_offset);
	}

	static bool IsInstantiated()
	{
		return (GetInstance() != nullptr);
	}
};

static_assert_size(sizeof(TSingleton<long, 0x00000000>), 0x01);
static_assert_size(sizeof(TSingleton_offset<long, 0x00000000>), 0x01);