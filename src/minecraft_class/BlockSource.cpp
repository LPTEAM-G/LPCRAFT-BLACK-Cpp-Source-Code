//Copyright (c) 2026 LPTEAM
#include "BlockSource.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/blocks/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>

BlockSource::getBlockIDByPosType BlockSource::getBlockIDByPosOrig = nullptr;
BlockSource::getBlockByPosType BlockSource::getBlockByPosOrig = nullptr;

void BlockSource::get_block_id_by_pos_impl(unsigned int* result, BlockSource* this_ptr, const BlockPos* pos)
{
	return getBlockIDByPosOrig(result, this_ptr, pos);
}

Block* BlockSource::get_block_by_pos_impl(BlockSource* this_ptr, const BlockPos* pos)
{
	uint32_t id = this_ptr->get_block_id(*pos);
	return Block::get_block_table()[id];
}

unsigned int BlockSource::get_block_id(const BlockPos& pos) noexcept
{
	unsigned int id = 0;
	get_block_id_by_pos_impl(&id, this, &pos);
	return id;
}

Block* BlockSource::get_block(const BlockPos& pos) noexcept
{
	return get_block_by_pos_impl(this, &pos);
}

Material* BlockSource::get_material(const BlockPos& pos) noexcept
{
	Block* block = this->get_block(pos);
	return block->get_material();
}

bool BlockSource::is_snowed(const BlockPos& pos) noexcept
{
	BlockPos above_pos = pos;
	above_pos.y += 1;
	Material* material = get_material(above_pos);
	if (
		material->is_type(MaterialType::top_snow) or
		material->is_type(MaterialType::snow_block)
	)
		return true;
	else
		return false;
}

void BlockSource::install() noexcept
{
	//_ZN11BlockSource10getBlockIDERK8BlockPos
	void* get_block_id_by_pos_target = minecraft_app::get_lib_thumb_function_ptr(0x524C74);
	MSHook(get_block_id_by_pos_target, get_block_id_by_pos_impl, getBlockIDByPosOrig);

	//_ZN11BlockSource8getBlockERK8BlockPos
	void* get_block_by_pos_target = minecraft_app::get_lib_thumb_function_ptr(0x525138);
	MSHook(get_block_by_pos_target, get_block_by_pos_impl, getBlockByPosOrig);
}
