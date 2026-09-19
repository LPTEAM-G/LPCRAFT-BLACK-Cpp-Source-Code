//Copyright (c) 2026 LPTEAM
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "minecraft_class/blocks/MyceliumBlock.hpp"
#include "block_id_enum.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include "minecraft_class/options_about/Options.hpp"

MyceliumBlock::get_texture_in_world_type MyceliumBlock::get_texture_in_world_orig = nullptr;
MyceliumBlock::get_texture_with_data_type MyceliumBlock::get_texture_with_data_orig = nullptr;

TextureUVCoordinateSet* MyceliumBlock::get_texture_in_world_impl(MyceliumBlock* this_ptr, BlockSource* block_source, const BlockPos* pos, signed char face)
{
	if (not Options::opt_vars::graphics::better_grass)
		return get_texture_in_world_orig(this_ptr, block_source, pos, face);

	if (face == 0)
		return this_ptr->get_bottom_texture();
	else if (face == 1)
		return this_ptr->get_top_texture();
	else
	{
		if (block_source->is_snowed(*pos))
		{
			Block* block = Block::get_block_table()[block_id_enum::snow_block];
			return block->get_texture_virtual(face);
		}
		//侧面也使用顶部纹理
		//强制实现BetterGrass纹理
		else
			return this_ptr->get_top_texture();
	}
}

TextureUVCoordinateSet* MyceliumBlock::get_texture_with_data_impl(MyceliumBlock* this_ptr, signed char face, int data)
{
	if (not Options::opt_vars::graphics::better_grass)
	{
		if (face == 0)
			return this_ptr->get_bottom_texture();
		else if (face == 1)
			return this_ptr->get_top_texture();
		else
			return this_ptr->get_side_texture();
	}

	if (face == 0)
		return this_ptr->get_bottom_texture();
	else
		return this_ptr->get_top_texture();
}

TextureUVCoordinateSet* MyceliumBlock::get_top_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 176);
}

TextureUVCoordinateSet* MyceliumBlock::get_side_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 200);
}

TextureUVCoordinateSet* MyceliumBlock::get_bottom_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 152);
}

void MyceliumBlock::install() noexcept
{
	//_ZN13MyceliumBlock10getTextureER11BlockSourceRK8BlockPosa
	void* get_texture_in_world_target = minecraft_app::get_lib_thumb_function_ptr(0x58759C);
	MSHook(get_texture_in_world_target, get_texture_in_world_impl, get_texture_in_world_orig);

	//_ZN13MyceliumBlock10getTextureEai
	void* get_texture_with_data_target = minecraft_app::get_lib_thumb_function_ptr(0x582CF4);
	MSHook(get_texture_with_data_target, get_texture_with_data_impl, get_texture_with_data_orig);
}