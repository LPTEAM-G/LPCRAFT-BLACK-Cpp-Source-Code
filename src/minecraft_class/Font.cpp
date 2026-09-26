//Copyright (c) 2026 LPTEAM
#include "Font.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Color.hpp"
#include <string>

int Font::get_line_length(
	const std::string& text,
	bool count_format_codes) noexcept
{
	using get_line_length_type = int(*)(Font*, const std::string*, float, bool);
	get_line_length_type get_line_length_orig = (get_line_length_type)minecraft_app::get_lib_thumb_function_ptr(0x317120);
	return get_line_length_orig(this, &text, 1.0f, count_format_codes);
}

float Font::get_line_length(
	const std::string& text,
	float result_scale,
	bool count_format_codes) noexcept
{
	using get_line_length_type = int(*)(Font*, const std::string*, float, bool);
	get_line_length_type get_line_length_orig = (get_line_length_type)minecraft_app::get_lib_thumb_function_ptr(0x317120);
	int logic_pixel = get_line_length_orig(this, &text, 1.0f, count_format_codes);
	return logic_pixel * result_scale;
}

int Font::get_text_height(const std::string& text) noexcept
{
	using get_text_height_type = int(*)(Font*, const std::string*);
	get_text_height_type get_text_height_orig = (get_text_height_type)minecraft_app::get_lib_thumb_function_ptr(0x2EFCA8);
	return get_text_height_orig(this, &text);
}

void Font::draw(const std::string& text, float x, float y, const Color& color, bool enable_format)
{
	using draw_type = void(*)(Font*, const std::string*, float, float, const Color*, bool);
	draw_type draw_orig = (draw_type)minecraft_app::get_lib_thumb_function_ptr(0x34100C);
	draw_orig(this, &text, x, y, &color, enable_format);
}
