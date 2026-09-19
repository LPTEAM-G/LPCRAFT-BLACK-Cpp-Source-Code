//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"

class GrassBlock
{
private:
	static TextureUVCoordinateSet* get_texture_in_world_impl(GrassBlock* this_ptr, BlockSource* block_source, const BlockPos* pos_in_world, signed char face);
	static TextureUVCoordinateSet* get_carried_texture_impl(GrassBlock* this_ptr, signed char face, int data);

public:
	using get_texture_in_world_type = TextureUVCoordinateSet*(*)(GrassBlock*, BlockSource*, const BlockPos*, signed char);
	static get_texture_in_world_type get_texture_in_world_orig;

	using get_carried_texture_type = TextureUVCoordinateSet*(*)(GrassBlock*, signed char, int);
	static get_carried_texture_type get_carried_texture_orig;

	TextureUVCoordinateSet* get_top_texture() noexcept;				//未着色
	TextureUVCoordinateSet* get_carried_top_texture() noexcept;		//已着色
	TextureUVCoordinateSet* get_bottom_texture() noexcept;
	TextureUVCoordinateSet* get_snowed_side_texture() noexcept;

	static void install() noexcept;
};

