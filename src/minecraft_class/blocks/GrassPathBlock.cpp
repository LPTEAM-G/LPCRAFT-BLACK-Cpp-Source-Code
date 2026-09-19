#include "GrassPathBlock.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include <cstdint>

GrassPathBlock::get_texture_with_data_type GrassPathBlock::get_texture_with_data_orig = nullptr;

TextureUVCoordinateSet* GrassPathBlock::get_texture_with_data_impl(GrassPathBlock* this_ptr, signed char face, int data)
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

TextureUVCoordinateSet* GrassPathBlock::get_top_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 200);
}

TextureUVCoordinateSet* GrassPathBlock::get_side_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 176);
}

TextureUVCoordinateSet* GrassPathBlock::get_bottom_texture() noexcept
{
	return (TextureUVCoordinateSet*)((uintptr_t)this + 152);
}

void GrassPathBlock::install() noexcept
{
	//_ZN14GrassPathBlock10getTextureEai
	void* get_texture_with_data_target = minecraft_app::get_lib_thumb_function_ptr(0x582A04);
	MSHook(get_texture_with_data_target, get_texture_with_data_impl, get_texture_with_data_orig);
}
