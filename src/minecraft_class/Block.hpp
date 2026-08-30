//Copyright (c) 2026 LPTEAM
#ifndef MINECRACT_CLASS_BLOCK_HPP
#define MINECRACT_CLASS_BLOCK_HPP

#include "minecraft_class/Material.hpp"

class Block
{
public:
	static Block** get_block_table() noexcept;
	static Material* getMaterial(Block* this_ptr) noexcept;
};

#endif
