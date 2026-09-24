//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/blocks/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/Material.hpp"

class BlockSource
{
public:
	unsigned int get_block_id(const BlockPos& pos) noexcept;
	Block* get_block(const BlockPos& pos) noexcept;
	Material* get_material(const BlockPos& pos) noexcept;
	bool is_snowed(const BlockPos& pos) noexcept;
};
