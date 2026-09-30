//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/Color.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include "mods/touchgui_render_components.hpp"
#include <string>
#include <vector>

class MinecraftInputRenderContext
{
private:
	
	struct TextItem
	{
		RectangleArea rect;
		Color color;
		std::string text;
	};

	void** input_render_context_vtable;
	void** gui_component_vtable;
	Color color;
	Font* font;
	std::vector<TextItem> text_elements;
	MinecraftClient* client;
	//额外添加的成员
	std::vector<touchgui_render_components::render_element_type> render_elements;

public:	
	MinecraftInputRenderContext(MinecraftClient* client) noexcept;
	~MinecraftInputRenderContext() noexcept;

	RectangleArea get_scaled_text_area(const std::string& text, float x, float y) noexcept;

	void draw_square(float x, float y, float width, float height, const Color& color);
	void draw_square(const RectangleArea& rect, const Color& color);
	void draw_image(
		const std::string& texture_path,
		const RectangleArea& rect,
		int uv_x, int uv_y,
		int uv_width, int uv_height,
		const Color& color
	);
	void draw_text(const std::string& text, float x, float y, const Color& color);
	void draw_text_centered_in_rect(const std::string& text, const RectangleArea& rect, const Color& color);
};
