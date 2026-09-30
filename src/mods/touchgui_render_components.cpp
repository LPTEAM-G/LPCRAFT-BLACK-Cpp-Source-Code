//Copyright (c) 2026 LPTEAM
#include "touchgui_render_components.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/ScreenRenderer.hpp"
#include "minecraft_class/Tessellator.hpp"

namespace touchgui_render_components
{
	void square_element_type::render() noexcept
	{
		Tessellator& tess = Tessellator::get_instance();
		tess.begin(0).color(color);
		//需要保证安装包里有一个纯白的图片, 路径应该由开发者自己负责
		AbstractScreen::draw_rectangle_area(tess, rect, 1, 1, 1, 1);
		mce::MaterialPtr* material = ScreenRenderer::get_screen_material(3);
		mce::TextureGroup* texture_group = MinecraftClient::instance->get_texture_group();
		mce::TexturePtr tex = texture_group->get_texture("LPCRAFT/white.png", false);
		tess.draw(*material, tex);
	}

	void image_element_type::render() noexcept
	{
		Tessellator& tess = Tessellator::get_instance();
		tess.begin(0).color(color);
		AbstractScreen::draw_rectangle_area(tess, rect, uv_x, uv_y, uv_width, uv_height);
		mce::MaterialPtr* material = ScreenRenderer::get_screen_material(3);
		mce::TextureGroup* texture_group = MinecraftClient::instance->get_texture_group();
		mce::TexturePtr tex = texture_group->get_texture(texture_path, false);
		tess.draw(*material, tex);
	}

	void text_element_type::render() noexcept
	{
		Font* font = MinecraftClient::instance->get_font();
		font->draw(text, x, y, color, false);
	}

	render_element_type::render_element_type() noexcept:
		type(element_enum::none),
		element()
	{}

	render_element_type::render_element_type(const render_element_type& other):
		type(other.type),
		element()
	{
		other.visitor(copy_to_visitor{&element});
	}

	render_element_type::render_element_type(render_element_type&& other) noexcept:
		type(other.type),
		element()
	{
		other.visitor(move_to_visitor{&element});
		other.destroy();
	}

	render_element_type::render_element_type(const square_element_type& square) noexcept:
		type(element_enum::square),
		element()
	{
		new (&element.square_element) square_element_type(square);
	}

	render_element_type::render_element_type(const image_element_type& image):
		type(element_enum::image),
		element()
	{
		new (&element.image_element) image_element_type(image);
	}

	render_element_type::render_element_type(const text_element_type& text):
		type(element_enum::text),
		element()
	{
		new (&element.text_element) text_element_type(text);
	}

	render_element_type::~render_element_type() noexcept
	{
		this->destroy();
	}

	render_element_type& render_element_type
		::operator=(const render_element_type& other)
	{
		if (this == &other) return *this;
		this->destroy();
		other.visitor(copy_to_visitor{&element});
		this->type = other.type;
		return *this;
	}

	render_element_type& render_element_type
		::operator=(render_element_type&& other) noexcept
	{
		if (this == &other) return *this;
		this->destroy();
		other.visitor(move_to_visitor{&element});
		this->type = other.type;
		other.destroy();
		return *this;
	}

	void render_element_type::destroy() noexcept
	{
		visitor(destroy_visitor{});
		type = element_enum::none;
	}

	void render_element_type::render() noexcept
	{
		visitor(render_visitor{});
	}
}
