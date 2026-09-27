//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/touch_gui/ButtonColors.hpp"
#include <functional>
#include <string>

class TouchGlyphButtonControl
{
private:
	void** vtable;
	
public:
	using constructor_type = void(*)(
		TouchGlyphButtonControl*,
		std::function<RectangleArea()>,
		std::function<bool()>,
		short,
		const ButtonColors*,
		int,
		int,
		int,
		int,
		bool,
		int,
		float,
		//NOTE: 此处按值传递
		std::string,
		bool
	);
	static constructor_type constructor_orig;

	static void constructor(
		TouchGlyphButtonControl* this_ptr,
		std::function<RectangleArea()> rect_getter,
		std::function<bool()> visible_condition,
		short p_s1,
		const ButtonColors* color,
		int uv_x,
		int uv_y,
		int uv_width,
		int uv_height,
		bool p_b1,
		int p_i5,
		float p_f1,
		std::string str,
		bool p_b2
	);

	static void render(TouchGlyphButtonControl* this_ptr, InputRenderContext* context);

	std::function<RectangleArea()>& get_rect_getter() noexcept;
	std::function<bool()>& get_visible_condition() noexcept;
	bool get_hovered_state() const noexcept;
	const ButtonColors& get_colors() const noexcept;
	int get_uv_x() const noexcept;
	int get_uv_y() const noexcept;
	int get_uv_width() const noexcept;
	int get_uv_height() const noexcept;
	float get_scale() const noexcept;

	static void install() noexcept;
};
