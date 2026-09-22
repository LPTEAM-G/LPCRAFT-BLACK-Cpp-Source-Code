//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/blocks/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/Material.hpp"

class BlockSource
{
private:
	static void get_block_id_by_pos_impl(unsigned int* result, BlockSource* this_ptr, const BlockPos* pos);
	static Block* get_block_by_pos_impl(BlockSource* this_ptr, const BlockPos* pos);


public:
	using getBlockIDByPosType = void(*)(unsigned int*, BlockSource*, const BlockPos*);
	static getBlockIDByPosType getBlockIDByPosOrig;

	using getBlockByPosType = Block*(*)(BlockSource* , const BlockPos*);
	static getBlockByPosType getBlockByPosOrig;

	unsigned int get_block_id(const BlockPos& pos) noexcept;
	Block* get_block(const BlockPos& pos) noexcept;
	Material* get_material(const BlockPos& pos) noexcept;
	bool is_snowed(const BlockPos& pos) noexcept;

	static void install() noexcept;
};
