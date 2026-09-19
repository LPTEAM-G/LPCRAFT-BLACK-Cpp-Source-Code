//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"

class MyceliumBlock
{
private:
	static TextureUVCoordinateSet* get_texture_in_world_impl(MyceliumBlock* this_ptr, BlockSource* block_source, const BlockPos* pos_in_world, signed char face);
	static TextureUVCoordinateSet* get_texture_with_data_impl(MyceliumBlock* this_ptr, signed char face, int data);

public:
	using get_texture_in_world_type = TextureUVCoordinateSet*(*)(MyceliumBlock*, BlockSource*, const BlockPos*, signed char);
	static get_texture_in_world_type get_texture_in_world_orig;

	using get_texture_with_data_type = TextureUVCoordinateSet*(*)(MyceliumBlock*, signed char, int);
	static get_texture_with_data_type get_texture_with_data_orig;

	TextureUVCoordinateSet* get_top_texture() noexcept;
	TextureUVCoordinateSet* get_side_texture() noexcept;
	TextureUVCoordinateSet* get_bottom_texture() noexcept;

	static void install() noexcept;
};