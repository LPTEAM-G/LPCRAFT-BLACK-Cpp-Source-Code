//Copyright (c) 2026 LPTEAM
#include "BlockTessellator.hpp"
#include "minecraft_class/BlockSource.hpp"
#include <cstdint>

BlockSource* BlockTessellator::get_block_source() noexcept
{
	return *(BlockSource**)((uintptr_t)this + 4);
}
