//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_BLOCKS_GRASSBLOCK_HPP
#define MINECRAFT_CLASS_BLOCKS_GRASSBLOCK_HPP

#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"

class GrassBlock
{
public:
	using getTextureInWorldFuncType = TextureUVCoordinateSet* (*)(GrassBlock*, BlockSource*, const BlockPos*, signed char);
	static getTextureInWorldFuncType getTextureInWorldOrig;

	static TextureUVCoordinateSet* get_texture_in_world(GrassBlock* this_ptr, BlockSource* block_source, const BlockPos* pos_in_world, signed char face);

	static void install() noexcept;
};

#endif
