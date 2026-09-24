//Copyright (c) 2026 LPTEAM
#include "MinecraftInputRenderContext.hpp"
#include "minecraft_app.hpp"
#include "hook_macro.hpp"
#include "minecraft_class/GuiData.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"

MinecraftInputRenderContext::destructor_type MinecraftInputRenderContext::destructor_orig = nullptr;
MinecraftInputRenderContext::draw_rect_type MinecraftInputRenderContext::draw_rect_orig = nullptr;

void MinecraftInputRenderContext::destructor(MinecraftInputRenderContext* this_ptr)
{
	destructor_orig(this_ptr);
	new (&this_ptr->text_elements) std::vector<TextElement>{};
}

void MinecraftInputRenderContext::draw_rect_impl(MinecraftInputRenderContext* this_ptr, RectangleArea* area, int uv_x, int uv_y, int uv_width, int uv_height)
{
	draw_rect_orig(this_ptr, area, uv_x, uv_y, uv_width, uv_height);
}

MinecraftInputRenderContext::MinecraftInputRenderContext(MinecraftClient* client) noexcept:
	input_render_context_vtable((void**)minecraft_app::get_lib_vtable_address(0x6F00D8)),
	gui_component_vtable((void**)minecraft_app::get_lib_vtable_address(0x6F00F8)),
	color{0, 0,0, 0},
	font(client->get_font()),
	text_elements(),
	client(client)
{}

MinecraftInputRenderContext::~MinecraftInputRenderContext() noexcept
{
	destructor(this);
}

void MinecraftInputRenderContext::draw_text_at_once(
	const std::string& text,
	float x,
	float y,
	const Color& color) noexcept
{
	InputRenderContext* base = (InputRenderContext*)this;
	auto temp_rect = base->measure_text_for_button_virtual({0, 0}, text);
	Font* font = MinecraftClient::instance->get_font();
	float width = font->get_line_length(text, GuiData::get_gui_scale(), false);
	float height = temp_rect.y_end - temp_rect.y_start;
	RectangleArea rect
	{
		.x_start = x,
		.x_end = x + width,
		.y_start = y,
		.y_end = y + height
	};
	base->set_color_virtual(color);
	base->draw_text_virtual(rect, text);
	//set_color_virtual({0,0,0,0.5});
	//MinecraftInputRenderContext::draw_rect_impl((MinecraftInputRenderContext*)this, &rect, 10, 10, 1, 1);
}

void MinecraftInputRenderContext::install() noexcept
{
	//_ZN27MinecraftInputRenderContextD2Ev
	void* destructor_target = minecraft_app::get_lib_thumb_function_ptr(0x384C9C);
	MSHook(destructor_target, destructor, destructor_orig);
	
	//_ZNK27MinecraftInputRenderContext8drawRectERK13RectangleAreaiiii
	void* draw_rect_target = minecraft_app::get_lib_thumb_function_ptr(0x361FD4);
	MSHook(draw_rect_target, draw_rect_impl, draw_rect_orig);
}
