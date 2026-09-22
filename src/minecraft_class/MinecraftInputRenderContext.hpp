//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/RectangleArea.hpp"

class MinecraftInputRenderContext
{
public:
	using drawRectType = void(*)(MinecraftInputRenderContext*, const RectangleArea*, int, int, int, int);
	static drawRectType drawRectOrig;

	static void draw_rect(MinecraftInputRenderContext* this_ptr, RectangleArea* area, int uv_x, int uv_y, int uv_width, int uv_height);

	static void install() noexcept;
};
