//Copyright (c) 2026 LPTEAM
#include "BlockSource.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Block.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>

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

Material* BlockSource::getMaterial(const BlockPos* pos) noexcept
{
	Block* block = get_block_by_pos(this, pos);
	return block->getMaterial();
}

bool BlockSource::is_snowed(const BlockPos* pos) noexcept
{
	BlockPos above_pos = *pos;
	above_pos.y += 1;
	Material* material = getMaterial(&above_pos);
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
	//_ZN11BlockSource10getBlockIDERK8BlockPos
	void* get_block_id_by_pos_target = minecraft_app::get_lib_thumb_function_ptr(0x524C74);
	MSHook(get_block_id_by_pos_target, get_block_id_by_pos, getBlockIDByPosOrig);

	//_ZN11BlockSource8getBlockERK8BlockPos
	void* get_block_by_pos_target = minecraft_app::get_lib_thumb_function_ptr(0x525138);
	MSHook(get_block_by_pos_target, get_block_by_pos, getBlockByPosOrig);
}
