//Copyright (c) 2026 LPTEAM
#include "MinecraftInputRenderContext.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"

MinecraftInputRenderContext::drawRectType MinecraftInputRenderContext::drawRectOrig = nullptr;

void MinecraftInputRenderContext::draw_rect(MinecraftInputRenderContext* this_ptr, RectangleArea* area, int uv_x, int uv_y, int uv_width, int uv_height)
{
	if (uv_width == 18)
	{
		//LOGI("%f, %f, %f, %f", area->x_start, area->y, area->width, area->height);
		area->x_start = 0;
		area->x_end = 100;
		area->y_start = 0;
		area->y_end = 100;
	}
	drawRectOrig(this_ptr, area, uv_x, uv_y, uv_width, uv_height);
}

void MinecraftInputRenderContext::install() noexcept
{
	//_ZNK27MinecraftInputRenderContext8drawRectERK13RectangleAreaiiii
	void* drawRectTarget = minecraft_app::get_lib_thumb_function_ptr(0x361FD4);
	MSHook(drawRectTarget, draw_rect, drawRectOrig);
}
