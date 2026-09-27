//Copyright (c) 2026 LPTEAM
#pragma once

#include "glm/type_vec2.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/touch_gui/ButtonColors.hpp"
#include <functional>
#include <string>

//Inherits from: TouchGlyphButtonControl
class TouchTextButtonControl
{
private:
	void** vtable;
	
public:
	using constructor_type = void(*)(
		TouchTextButtonControl*,
		std::function<glm::vec2()>,
		std::function<bool()>,
		std::function<std::string()>,
		short,
		const ButtonColors*,
		int, int, int, int,
		bool, int
	);
	static constructor_type constructor_orig;
	static void constructor(
		TouchTextButtonControl* this_ptr,
		std::function<glm::vec2()> text_pos_getter,
		std::function<bool()> visible_condition,
		std::function<std::string()> text_getter,
		short p_s1,
		const ButtonColors* colors,
		int uv_x, int uv_y, int uv_width, int uv_height,
		bool p_b1,
		int p_i5
	);
	
	static void render(TouchTextButtonControl* this_ptr, InputRenderContext* context);

	std::function<glm::vec2()>& get_text_pos_getter() noexcept;
	std::function<std::string()>& get_text_getter() noexcept;
	std::string& get_cached_text() noexcept;
	float& get_cached_pos_x() noexcept;
	float& get_cached_pos_y() noexcept;
	RectangleArea& get_measured_area() noexcept;

	static void install() noexcept;
};
