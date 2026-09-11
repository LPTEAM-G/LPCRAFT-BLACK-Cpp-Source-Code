//Copyright (c) 2026 LPTEAM
#include <cstdio>
#include <cstring>
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"

GrassBlock::getTextureInWorldFuncType GrassBlock::getTextureInWorldOrig = nullptr;

TextureUVCoordinateSet* GrassBlock::get_texture_in_world(GrassBlock* this_ptr, BlockSource* block_source, const BlockPos* pos, signed char face)
{
	constexpr signed char bottom_face = 0;
	constexpr signed char top_face = 1;
	
	TextureUVCoordinateSet* top_set = (TextureUVCoordinateSet*)((char*)this_ptr + 176);
	TextureUVCoordinateSet* bottom_set = (TextureUVCoordinateSet*)((char*)this_ptr + 152);
	TextureUVCoordinateSet* snowed_side_set = (TextureUVCoordinateSet*)((char*)this_ptr + 212);

	if (face == bottom_face)
		return bottom_set;
	else if (face == top_face)
		return top_set;
	else
	{
		if (block_source->is_snowed(pos))
			return snowed_side_set;
		//侧面也使用顶部纹理
		//强制实现BetterGrass纹理
		else
			return top_set;
	}
}

void GrassBlock::install() noexcept
{
	//_ZN10GrassBlock10getTextureER11BlockSourceRK8BlockPosa
	void* get_textrue_in_world_target = minecraft_app::get_lib_thumb_function_ptr(0x5A8DE4);
	MSHook(get_textrue_in_world_target, get_texture_in_world, getTextureInWorldOrig);
}
