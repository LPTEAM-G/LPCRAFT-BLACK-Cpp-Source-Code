//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/Color.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include <string>
#include <vector>

struct TextElement
{
	RectangleArea rect;
	Color color;
	std::string text;
};

class MinecraftInputRenderContext
{
private:
	void** input_render_context_vtable;
	void** gui_component_vtable;
	Color color;
	Font* font;
	std::vector<TextElement> text_elements;
	MinecraftClient* client;
	//额外添加的成员

public:
	using destructor_type = void(*)(MinecraftInputRenderContext*);
	static destructor_type destructor_orig;
	static void destructor(MinecraftInputRenderContext*);
	
	using draw_rect_type = void(*)(MinecraftInputRenderContext*, const RectangleArea*, int, int, int, int);
	static draw_rect_type draw_rect_orig;
	static void draw_rect_impl(MinecraftInputRenderContext* this_ptr, RectangleArea* area, int uv_x, int uv_y, int uv_width, int uv_height);

	MinecraftInputRenderContext(MinecraftClient* client) noexcept;
	~MinecraftInputRenderContext() noexcept;
	
	void draw_text_at_once(const std::string& text, float x, float y, const Color& color) noexcept;
	
	static void install() noexcept;
};
