//Copyright (c) 2026 LPTEAM
#pragma once

#include <cstring>

namespace tools
{
	template<typename T>
	inline T memory_reader(const void* address) noexcept
	{
		T getter;
		memcpy((void*)&getter, address, sizeof(T));
		return getter;
	}
}

