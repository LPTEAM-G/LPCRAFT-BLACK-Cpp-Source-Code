//Copyright (c) 2026 LPTEAM
#pragma  once

#include "minecraft_class/Color.hpp"
#include <string>

class Font
{
public:
	int get_line_length(
		const std::string& text,
		bool count_format_codes
	) noexcept;

	float get_line_length(
		const std::string& text,
		float result_scale,
		bool count_format_codes
	) noexcept;

	int get_text_height(const std::string& text) noexcept;

	void draw(const std::string& text, float x, float y, const Color& color, bool enable_format);
};
