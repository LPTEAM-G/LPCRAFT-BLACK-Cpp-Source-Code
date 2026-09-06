//Copyright (c) 2026 LPTEAM
#include "Block.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>

Block** Block::get_block_table() noexcept
{
	return minecraft_app::get_lib_global_variable_ptr<Block*>(0x7CAE6C);
}

Material* Block::getMaterial() noexcept
{
	return *((Material**)((uint32_t)this + 84));
}
