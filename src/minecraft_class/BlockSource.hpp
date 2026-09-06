//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_BLOCKS_BLOCKSOURCE_HPP
#define MINECRAFT_CLASS_BLOCKS_BLOCKSOURCE_HPP

#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>

class BlockSource
{
public:
	using getBlockIDByPosType = void*(*)(uint32_t*, BlockSource*, const BlockPos*);
	static getBlockIDByPosType getBlockIDByPosOrig;

	using getBlockByPosType = Block*(*)(BlockSource* , const BlockPos*);
	static getBlockByPosType getBlockByPosOrig;

	//--- Hooked Functions ---//
	static void* get_block_id_by_pos(uint32_t* result, BlockSource* this_ptr, const BlockPos* pos);
	static Block* get_block_by_pos(BlockSource* this_ptr, const BlockPos* pos);

	Material* getMaterial(const BlockPos* pos) noexcept;
	bool is_snowed(const BlockPos* pos) noexcept;

	static void install() noexcept;
};

#endif
