//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_TOUCH_GUI_TOUCHGLYPHBUTTONCONTROL_HPP
#define MINECRAFT_CLASS_TOUCH_GUI_TOUCHGLYPHBUTTONCONTROL_HPP

#include "minecraft_class/RectangleArea.hpp"
#include "minecraft_class/touch_gui/ButtonColors.hpp"
#include <functional>
#include <string>

class TouchGlyphButtonControl
{
public:
	using constructor_type = TouchGlyphButtonControl*(*)(
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

	static TouchGlyphButtonControl* constructor(
		TouchGlyphButtonControl* this_ptr,
		std::function<RectangleArea()> rect_getter,
		std::function<bool()> func,
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

	static void install() noexcept;
};

#endif
