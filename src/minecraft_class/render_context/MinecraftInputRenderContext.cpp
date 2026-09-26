//Copyright (c) 2026 LPTEAM
#include "MinecraftInputRenderContext.hpp"
#include "mce/MaterialPtr.hpp"
#include "mce/TextureGroup.hpp"
#include "mce/TexturePtr.hpp"
#include "minecraft_app.hpp"
#include "hook_macro.hpp"
#include "minecraft_class/GuiData.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/ScreenRenderer.hpp"
#include "minecraft_class/Tessellator.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/screen_about/AbstractScreen.hpp"

void MinecraftInputRenderContext::square_element_type::draw() noexcept
{
	
}

void MinecraftInputRenderContext::image_element_type::draw() noexcept
{
	Tessellator& tess = Tessellator::get_instance();
	tess.begin(0).color(color);
	AbstractScreen::draw_rectangle_area(tess, rect, uv_x, uv_y, uv_width, uv_height);
	mce::MaterialPtr* material = ScreenRenderer::get_screen_material(3);
	mce::TextureGroup* texture_group = MinecraftClient::instance->get_texture_group();
	mce::TexturePtr tex = texture_group->get_texture(texture_path, false);
	tess.draw(*material, tex);
}

void MinecraftInputRenderContext::TextItem::draw() noexcept
{
	Font* font = MinecraftClient::instance->get_font();
	int width = font->get_line_length(text, false);
	int height = font->get_text_height(text);

	float center_x = rect.center_x();
	float center_y = rect.center_y();

	float inv_scale = GuiData::get_inv_gui_scale();
	float draw_x = center_x * inv_scale - width * 0.5f;
	float draw_y = center_y * inv_scale - height * 0.5f;

	font->draw(text, draw_x, draw_y, color, false);
}

MinecraftInputRenderContext::render_element_type::render_element_type() noexcept:
	type(element_enum::none),
	element()
{}

MinecraftInputRenderContext::render_element_type::render_element_type(const render_element_type& other):
	type(other.type),
	element()
{
	other.visitor(copy_to_visitor{&element});
}

MinecraftInputRenderContext::render_element_type::render_element_type(render_element_type&& other) noexcept:
	type(other.type),
	element()
{
	other.visitor(move_to_visitor{&element});
	other.destroy();
}

MinecraftInputRenderContext::render_element_type::render_element_type(const square_element_type& square) noexcept:
	type(element_enum::square),
	element()
{
	new (&element.square_element) square_element_type(square);
}

MinecraftInputRenderContext::render_element_type::render_element_type(const image_element_type& image):
	type(element_enum::image),
	element()
{
	new (&element.image_element) image_element_type(image);
}

MinecraftInputRenderContext::render_element_type::render_element_type(const TextItem& text):
	type(element_enum::text),
	element()
{
	new (&element.text_element) TextItem(text);
}

MinecraftInputRenderContext::render_element_type::~render_element_type() noexcept
{
	this->destroy();
}

MinecraftInputRenderContext::render_element_type& MinecraftInputRenderContext::render_element_type
	::operator=(const render_element_type& other)
{
	if (this == &other) return *this;
	this->destroy();
	other.visitor(copy_to_visitor{&element});
	this->type = other.type;
	return *this;
}

MinecraftInputRenderContext::render_element_type& MinecraftInputRenderContext::render_element_type
	::operator=(render_element_type&& other) noexcept
{
	if (this == &other) return *this;
	this->destroy();
	other.visitor(move_to_visitor{&element});
	this->type = other.type;
	other.destroy();
	return *this;
}

void MinecraftInputRenderContext::render_element_type::destroy() noexcept
{
	visitor(destroy_visitor{});
	type = element_enum::none;
}

void MinecraftInputRenderContext::render_element_type::draw() noexcept
{
	visitor(draw_visitor{});
}

MinecraftInputRenderContext::draw_rect_type MinecraftInputRenderContext::draw_rect_orig = nullptr;

void MinecraftInputRenderContext::draw_rect_impl(MinecraftInputRenderContext* this_ptr, RectangleArea* area, int uv_x, int uv_y, int uv_width, int uv_height)
{
	this_ptr->render_elements.emplace_back(
		image_element_type
		{
			.rect = *area,
			.color = this_ptr->color,
			.uv_x = uv_x,
			.uv_y = uv_y,
			.uv_width = uv_width,
			.uv_height = uv_height,
			.texture_path = "gui/gui.png"
		}
	);
	//draw_rect_orig(this_ptr, area, uv_x, uv_y, uv_width, uv_height);
}

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
		element.draw();
	}
}

void MinecraftInputRenderContext::draw_text(
	const std::string& text,
	float x,
	float y,
	const Color& color) noexcept
{
	InputRenderContext* base = (InputRenderContext*)this;
	Font* font = MinecraftClient::instance->get_font();
	float width = font->get_line_length(text, GuiData::get_gui_scale(), false);
	float height = font->get_text_height(text) * GuiData::get_gui_scale();
	RectangleArea rect
	{
		.x_start = x,
		.x_end = x + width,
		.y_start = y,
		.y_end = y + height
	};
	
	render_elements.emplace_back(text_element_type{rect, color, text});
}

void MinecraftInputRenderContext::install() noexcept
{
	//_ZNK27MinecraftInputRenderContext8drawRectERK13RectangleAreaiiii
	void* draw_rect_target = minecraft_app::get_lib_thumb_function_ptr(0x361FD4);
	MSHook(draw_rect_target, draw_rect_impl, draw_rect_orig);
}
