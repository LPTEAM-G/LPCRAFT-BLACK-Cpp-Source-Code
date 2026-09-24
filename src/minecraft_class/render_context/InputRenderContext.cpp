#include "InputRenderContext.hpp"
#include "minecraft_class/Color.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/Vec2.hpp"
#include <string>

RectangleArea InputRenderContext::measure_text_for_button_virtual(
	const Vec2& center_pos,
	const std::string& text) noexcept
{
	using measure_text_for_button_virtual_type = void(*)(RectangleArea*, InputRenderContext*, const Vec2*, const std::string*);
	measure_text_for_button_virtual_type measure_text_for_button_virtual_orig = (measure_text_for_button_virtual_type)(vtable[4]);
	RectangleArea sret;
	measure_text_for_button_virtual_orig(&sret, this, &center_pos, &text);
	return sret;
}

void InputRenderContext::set_color_virtual(const Color& color) noexcept
{
	using set_color_virtual_type = void(*)(InputRenderContext*, const Color*);
	set_color_virtual_type set_color_virtual_orig = (set_color_virtual_type)(vtable[2]);
	set_color_virtual_orig(this, &color);
}

void InputRenderContext::draw_text_virtual(
	const RectangleArea& rect,
	const std::string& text) const noexcept
{
	using draw_text_virtual_type = void(*)(
		const InputRenderContext*,
		const RectangleArea*, const std::string*);
	draw_text_virtual_type draw_text_virtual_orig = (draw_text_virtual_type)(vtable[5]);
	draw_text_virtual_orig(this, &rect, &text);
}
