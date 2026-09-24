//Copyright (c) 2026 LPTEAM
#include "PodzolBlock.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include <cstdint>

PodzolBlock::get_texture_with_data_type PodzolBlock::get_texture_with_data_orig = nullptr;

TextureUVCoordinateSet* PodzolBlock::get_texture_with_data_impl(PodzolBlock* this_ptr, signed char face, int data)
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

TextureUVCoordinateSet* PodzolBlock::get_top_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 176);
}

TextureUVCoordinateSet* PodzolBlock::get_side_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 200);
}

TextureUVCoordinateSet* PodzolBlock::get_bottom_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 152);
}

void PodzolBlock::install() noexcept
{
	//_ZN11PodzolBlock10getTextureEai
	void* get_texture_with_data_target = minecraft_app::get_lib_thumb_function_ptr(0x582E0C);
	MSHook(get_texture_with_data_target, get_texture_with_data_impl, get_texture_with_data_orig);
}
