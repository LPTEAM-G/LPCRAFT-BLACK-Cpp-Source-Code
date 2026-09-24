//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>
#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/Color.hpp"
#include "minecraft_class/Vec2.hpp"

class InputRenderContext
{
private:
	void** vtable;
	
public:
	RectangleArea measure_text_for_button_virtual(const Vec2& center_pos, const std::string& text) noexcept;
	void set_color_virtual(const Color& color) noexcept;
	void draw_text_virtual(
		const RectangleArea& rect,
		const std::string& text) const noexcept;
};
