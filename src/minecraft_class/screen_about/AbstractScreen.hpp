//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/Tessellator.hpp"
#include <string>

class AbstractScreen
{
public:
	std::string get_screen_name_virtual() const noexcept;
	static void draw_rectangle_area(
		Tessellator& tess,
		RectangleArea& rect,
		int uv_x,
		int uv_y,
		float uv_width,
		float uv_height
	);
};
