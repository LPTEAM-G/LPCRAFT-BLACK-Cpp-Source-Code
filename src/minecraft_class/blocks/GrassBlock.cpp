//Copyright (c) 2026 LPTEAM
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "block_id_enum.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/blocks/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include "minecraft_class/options_about/Options.hpp"

GrassBlock::get_texture_in_world_type GrassBlock::get_texture_in_world_orig = nullptr;
GrassBlock::get_carried_texture_type GrassBlock::get_carried_texture_orig = nullptr;

TextureUVCoordinateSet* GrassBlock::get_texture_in_world_impl(GrassBlock* this_ptr, BlockSource* block_source, const BlockPos* pos, signed char face)
{
	if (not Options::opt_vars::graphics::better_grass)
		return get_texture_in_world_orig(this_ptr, block_source, pos, face);

	if (face == 0)
		return this_ptr->get_bottom_texture();
	else if (face == 1)
		return this_ptr->get_top_texture();
	else
	{
		//直接复用
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

TextureUVCoordinateSet* GrassBlock::get_carried_texture_impl(GrassBlock* this_ptr, signed char face, int data)
{
	if (not Options::opt_vars::graphics::better_grass)
		return get_carried_texture_orig(this_ptr, face, data);
	
	if (face == 0)
		return this_ptr->get_bottom_texture();
	//其余5面可以都用顶部纹理
	else
		return this_ptr->get_carried_top_texture();
}

TextureUVCoordinateSet* GrassBlock::get_top_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 176);
}

TextureUVCoordinateSet* GrassBlock::get_carried_top_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 236);
}

TextureUVCoordinateSet* GrassBlock::get_bottom_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 152);
}

TextureUVCoordinateSet* GrassBlock::get_snowed_side_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 212);
}

void GrassBlock::install() noexcept
{
	//_ZN10GrassBlock10getTextureER11BlockSourceRK8BlockPosa
	void* get_texture_in_world_target = minecraft_app::get_lib_thumb_function_ptr(0x5A8DE4);
	MSHook(get_texture_in_world_target, get_texture_in_world_impl, get_texture_in_world_orig);

	//_ZN10GrassBlock17getCarriedTextureEai
	void* get_carried_texture_target = minecraft_app::get_lib_thumb_function_ptr(0x586A8C);
	MSHook(get_carried_texture_target, get_carried_texture_impl, get_carried_texture_orig);
}
