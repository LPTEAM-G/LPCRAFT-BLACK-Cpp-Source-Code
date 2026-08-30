//Copyright (c) 2026 LPTEAM
#include "Block.hpp"
#include "init.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>

Block** Block::get_block_table() noexcept
{
	return (Block**)(minecraft_app::game_lib_base + 0x7CAE6C);
}

Material* Block::getMaterial(Block* this_ptr) noexcept
{
	return *((Material**)((uint32_t)this_ptr + 84));
}
