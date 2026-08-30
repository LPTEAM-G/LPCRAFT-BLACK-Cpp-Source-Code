//Copyright (c) 2026 LPTEAM
#include "BlockOccluder.hpp"
#include <cstdint>

bool BlockOccluder::occludes(signed char face) noexcept
{
	return ((1u << (face & 0x1F)) & *(uint32_t*)this) != 0;
}
