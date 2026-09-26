#include "Tessellator.hpp"
#include "mce/MaterialPtr.hpp"
#include "mce/PrimitiveMode.hpp"
#include "mce/TexturePtr.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Color.hpp"

Tessellator& Tessellator::get_instance() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<Tessellator>(0x75F2B8);
}

Tessellator& Tessellator::begin(mce::PrimitiveMode mode, int count) noexcept
{
	using begin_type = void(*)(Tessellator*, mce::PrimitiveMode, int);
	begin_type begin_orig = (begin_type)minecraft_app::get_lib_thumb_function_ptr(0x44FB80);
	begin_orig(this, mode, count);
	return *this;
}

Tessellator& Tessellator::begin(int count) noexcept
{
	return this->begin((mce::PrimitiveMode)1, count);
}

Tessellator& Tessellator::color(const Color& color) noexcept
{
	using color_type = void(*)(Tessellator*, const Color*);
	color_type color_orig = (color_type)minecraft_app::get_lib_thumb_function_ptr(0x44FC94);
	color_orig(this, &color);
	return *this;
}

void Tessellator::draw(mce::MaterialPtr& material, mce::TexturePtr& texture)
{
	using draw_type = void(*)(Tessellator*, mce::MaterialPtr*, mce::TexturePtr*);
	draw_type draw_orig = (draw_type)minecraft_app::get_lib_thumb_function_ptr(0x450400);
	draw_orig(this, &material, &texture);
}
