//Copyright (c) 2026 LPTEAM
#include "BlockSource.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/blocks/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/Material.hpp"
#include <cstdint>

unsigned int BlockSource::get_block_id(const BlockPos& pos) noexcept
{
	using get_block_id_type = void(*)(unsigned int*, BlockSource*, const BlockPos*);
	get_block_id_type get_block_id_orig = (get_block_id_type)minecraft_app::get_lib_thumb_function_ptr(0x524C74);
	
	unsigned int sret = 0;
	get_block_id_orig(&sret, this, &pos);
	return sret;
}

Block* BlockSource::get_block(const BlockPos& pos) noexcept
{
	uint32_t id = this->get_block_id(pos);
	return Block::get_block_table()[id];
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
