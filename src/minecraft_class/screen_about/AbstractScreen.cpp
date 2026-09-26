//Copyright (c) 2026 LPTEAM
#include "AbstractScreen.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/Tessellator.hpp"
#include <string>

std::string AbstractScreen::get_screen_name_virtual() const noexcept
{
	using get_screen_name_virtual_type = void(*)(std::string*, const AbstractScreen*);
	void** vtable = *((void***)this);
	get_screen_name_virtual_type get_screen_name_virtual_orig = (get_screen_name_virtual_type)(vtable[48]);
	std::string sret;
	get_screen_name_virtual_orig(&sret, this);
	return sret;
}

void AbstractScreen::draw_rectangle_area(
	Tessellator& tess,
	RectangleArea& rect,
	int uv_x, int uv_y,
	float uv_width, float uv_height)
{
	using draw_rectangle_area_type = void(*)(Tessellator*, RectangleArea*, int, int, float, float);
	draw_rectangle_area_type draw_rectangle_area_orig = (draw_rectangle_area_type)minecraft_app::get_lib_thumb_function_ptr(0x2F4DA8);
	draw_rectangle_area_orig(&tess, &rect, uv_x, uv_y, uv_width, uv_height);
}
