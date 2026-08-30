//Copyright (c) 2026 LPTEAM
#include <cstring>
#include <dlfcn.h>
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "hook_macro.hpp"
#include "init.hpp"
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
		if (BlockSource::is_snowed(block_source, pos))
			return snowed_side_set;
		//侧面也使用顶部纹理
		//强制实现BetterGrass纹理
		else
			return top_set;
	}
}

void GrassBlock::install() noexcept
{
	void* getTextureInWorldTarget = dlsym(minecraft_app::game_lib_handler, "_ZN10GrassBlock10getTextureER11BlockSourceRK8BlockPosa");
	MSHook(getTextureInWorldTarget, get_texture_in_world, getTextureInWorldOrig);
}
