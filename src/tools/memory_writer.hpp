//Copyright (c) 2026 LPTEAM
#pragma once

#include <cstdint>
#include <cstring>

namespace tools
{
	template<typename T>
	inline void memory_writer(void* target, T* src) noexcept
	{
		memcpy((void*)target, (void*)src, sizeof(T));
		__builtin___clear_cache((char*)target, (char*)((uintptr_t)target + sizeof(T)));
	}
}
