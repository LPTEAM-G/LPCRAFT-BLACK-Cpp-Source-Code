//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/Color.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include <algorithm>
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

		void draw() noexcept;
	};

	using text_element_type = TextItem;

	struct image_element_type
	{
		RectangleArea rect;
		Color color;
		int uv_x;
		int uv_y;
		int uv_width;
		int uv_height;
		std::string texture_path;

		void draw() noexcept;
	};

	struct square_element_type
	{
		RectangleArea rect;
		Color color;

		void draw() noexcept;
	};

	class render_element_type
	{
	private:
		enum class element_enum
		{
			none,
			square,
			image,
			text
		};
		
		union element_union
		{
			square_element_type square_element;
			image_element_type image_element;
			text_element_type text_element;

			element_union() noexcept {}
			~element_union() noexcept {}
		};

		element_enum type;
		element_union element;

		/*--- Visotor About ---*/
		template<typename F>
		void visitor(F&& f)
		{
			switch (type)
			{
				case element_enum::none: break;
				case element_enum::square: f(element.square_element); break;
				case element_enum::image: f(element.image_element); break;
				case element_enum::text: f(element.text_element); break;
			}
		}

		template<typename F>
		void visitor(F&& f) const
		{
			switch (type)
			{
				case element_enum::none: break;
				case element_enum::square: f(element.square_element); break;
				case element_enum::image: f(element.image_element); break;
				case element_enum::text: f(element.text_element); break;
			}
		}

		struct copy_to_visitor
		{
			void* dest_element;
			
			template<typename T>
			void operator()(const T& src) const
			{
				new (dest_element) T(src);
			}
		};

		struct move_to_visitor
		{
			void* dest_element;

			template<typename T>
			void operator()(T& src) const noexcept
			{
				new (dest_element) T(std::move(src));
			}
		};

		struct destroy_visitor
		{
			template<typename T>
			void operator()(T& src) const noexcept
			{
				src.~T();
			}
		};

		struct draw_visitor
		{
			template<typename T>
			void operator()(T& src) const
			{
				src.draw();
			}
		};
		
		void destroy() noexcept;

	public:
		render_element_type() noexcept;
		render_element_type(const render_element_type& other);
		render_element_type(render_element_type&& other) noexcept;
		render_element_type(const square_element_type& square) noexcept;
		render_element_type(const image_element_type& image);
		render_element_type(const text_element_type& text);
		render_element_type& operator=(const render_element_type& other);
		render_element_type& operator=(render_element_type&& other) noexcept;
		~render_element_type() noexcept;

		void draw() noexcept;
	};
	

	void** input_render_context_vtable;
	void** gui_component_vtable;
	Color color;
	Font* font;
	std::vector<TextItem> text_elements;
	MinecraftClient* client;
	//额外添加的成员
	std::vector<render_element_type> render_elements;

public:	
	using draw_rect_type = void(*)(MinecraftInputRenderContext*, const RectangleArea*, int, int, int, int);
	static draw_rect_type draw_rect_orig;
	static void draw_rect_impl(MinecraftInputRenderContext* this_ptr, RectangleArea* area, int uv_x, int uv_y, int uv_width, int uv_height);

	MinecraftInputRenderContext(MinecraftClient* client) noexcept;
	~MinecraftInputRenderContext() noexcept;
	
	void draw_text(const std::string& text, float x, float y, const Color& color) noexcept;
	
	static void install() noexcept;
};
