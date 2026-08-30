//Copyright (c) 2026 LPTEAM
#include "BlockSource.hpp"
#include "hook_macro.hpp"
#include "init.hpp"
#include "minecraft_class/Block.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>
#include <dlfcn.h>

BlockSource::getBlockIDByPosType BlockSource::getBlockIDByPosOrig = nullptr;
BlockSource::getBlockByPosType BlockSource::getBlockByPosOrig = nullptr;

void* BlockSource::get_block_id_by_pos(uint32_t* result, BlockSource* this_ptr, const BlockPos* pos)
{
	return getBlockIDByPosOrig(result, this_ptr, pos);
}

Block* BlockSource::get_block_by_pos(BlockSource* this_ptr, const BlockPos* pos)
{
	uint32_t block_id = 0;
	get_block_id_by_pos(&block_id, this_ptr, pos);
	return Block::get_block_table()[block_id];
}

Material* BlockSource::getMaterial(BlockSource* this_ptr, const BlockPos* pos) noexcept
{
	Block* block = get_block_by_pos(this_ptr, pos);
	return Block::getMaterial(block);
}

bool BlockSource::is_snowed(BlockSource* this_ptr, const BlockPos* pos) noexcept
{
	BlockPos above_pos = *pos;
	above_pos.y += 1;
	Material* material = getMaterial(this_ptr, &above_pos);
	if (
		Material::isType(material, MaterialType::top_snow) or
		Material::isType(material, MaterialType::snow_block)
	)
		return true;
	else
		return false;
}

void BlockSource::install() noexcept
{
	void* getBlockIDByPosTarget = dlsym(minecraft_app::game_lib_handler, "_ZN11BlockSource10getBlockIDERK8BlockPos");
	MSHook(getBlockIDByPosTarget, get_block_id_by_pos, getBlockIDByPosOrig);
	void* getBlockByPosTarget = dlsym(minecraft_app::game_lib_handler, "_ZN11BlockSource8getBlockERK8BlockPos");
	MSHook(getBlockByPosTarget, get_block_by_pos, getBlockByPosOrig);
}
