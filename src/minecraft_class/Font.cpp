//Copyright (c) 2026 LPTEAM
#include "Font.hpp"
#include "minecraft_app.hpp"
#include <string>

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
