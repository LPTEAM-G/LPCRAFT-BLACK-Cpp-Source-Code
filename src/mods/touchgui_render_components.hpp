//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/Color.hpp"
#include "minecraft_class/RectangleArea.hpp"
#include <string>

namespace touchgui_render_components
{
	struct text_element_type
	{
		float x;
		float y;
		Color color;
		std::string text;

		void render() noexcept;
	};

	struct image_element_type
	{
		RectangleArea rect;
		Color color;
		int uv_x;
		int uv_y;
		int uv_width;
		int uv_height;
		std::string texture_path;

		void render() noexcept;
	};

	struct square_element_type
	{
		RectangleArea rect;
		Color color;

		void render() noexcept;
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

		struct render_visitor
		{
			template<typename T>
			void operator()(T& src) const
			{
				src.render();
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

		void render() noexcept;
	};
}
