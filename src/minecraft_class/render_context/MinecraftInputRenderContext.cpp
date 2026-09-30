//Copyright (c) 2026 LPTEAM
#include "MinecraftInputRenderContext.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Color.hpp"
#include "minecraft_class/GuiData.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include "mods/touchgui_render_components.hpp"
#include <string>

MinecraftInputRenderContext::MinecraftInputRenderContext(MinecraftClient* client) noexcept:
	input_render_context_vtable((void**)minecraft_app::get_lib_vtable_address(0x6F00D8)),
	gui_component_vtable((void**)minecraft_app::get_lib_vtable_address(0x6F00F8)),
	color{0, 0,0, 0},
	font(client->get_font()),
	text_elements(),
	client(client),
	render_elements()
{}

MinecraftInputRenderContext::~MinecraftInputRenderContext() noexcept
{
	for (auto& element : render_elements)
	{
		element.render();
	}
}

RectangleArea MinecraftInputRenderContext::get_scaled_text_area(const std::string& text, float x, float y) noexcept
{
	float width = font->get_line_length(text, GuiData::get_gui_scale(), false);
	float height = font->get_text_height(text) * GuiData::get_gui_scale();
	return RectangleArea
	{
		x, y,
		x + width, y + height
	};
}

void MinecraftInputRenderContext::draw_square(float x, float y, float width, float height, const Color& color)
{
	render_elements.emplace_back(
		touchgui_render_components::square_element_type
		{
			RectangleArea(x, y, x + width, y + height),
			color
		}
	);
}

void MinecraftInputRenderContext::draw_square(const RectangleArea& rect, const Color& color)
{
	render_elements.emplace_back(
		touchgui_render_components::square_element_type
		{
			rect,
			color
		}
	);
}

void MinecraftInputRenderContext::draw_image(
	const std::string& texture_path,
	const RectangleArea& rect,
	int uv_x, int uv_y,
	int uv_width, int uv_height,
	const Color& color)
{
	render_elements.emplace_back(
		touchgui_render_components::image_element_type
		{
			rect,
			color,
			uv_x, uv_y,
			uv_width, uv_height,
			texture_path
		}
	);
}

void MinecraftInputRenderContext::draw_text(
	const std::string& text,
	float x,
	float y,
	const Color& color)
{
	render_elements.emplace_back(
		touchgui_render_components::text_element_type
		{
			x * GuiData::get_inv_gui_scale(),
			y * GuiData::get_inv_gui_scale(),
			color,
			text
		}
	);
}

void MinecraftInputRenderContext::draw_text_centered_in_rect(
	const std::string& text,
	const RectangleArea& rect,
	const Color& color)
{
	int text_logic_width = font->get_line_length(text, false);
	int text_logic_height = font->get_text_height(text);

	float center_x = rect.center_x();
	float center_y = rect.center_y();

	float inv_scale = GuiData::get_inv_gui_scale();
	float draw_x = center_x * inv_scale - text_logic_width * 0.5f;
	float draw_y = center_y * inv_scale - text_logic_height * 0.5f;

	render_elements.emplace_back(
		touchgui_render_components::text_element_type
		{
			draw_x,
			draw_y,
			color,
			text
		}
	);
}
