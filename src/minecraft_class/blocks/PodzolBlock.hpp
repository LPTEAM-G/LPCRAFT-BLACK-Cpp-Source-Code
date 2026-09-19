//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/TextureUVCoordinateSet.hpp"
class PodzolBlock
{
private:
	using get_texture_with_data_type = TextureUVCoordinateSet*(*)(PodzolBlock*, signed char, int);
	static get_texture_with_data_type get_texture_with_data_orig;
	static TextureUVCoordinateSet* get_texture_with_data_impl(PodzolBlock* this_ptr, signed char face, int data);
	
public:
	TextureUVCoordinateSet* get_top_texture() noexcept;
	TextureUVCoordinateSet* get_bottom_texture() noexcept;
	
	static void install() noexcept;
};
