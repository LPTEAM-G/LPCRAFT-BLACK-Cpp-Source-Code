//Copyright (c) 2026 LPTEAM
#include "TouchTextButtonControl.hpp"
#include "glm/type_vec2.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/render_context/MinecraftInputRenderContext.hpp"
#include "minecraft_class/touch_gui/TouchGlyphButtonControl.hpp"
#include "tools/vtable_setter.hpp"
#include <cstdint>
#include <functional>
#include <string>

TouchTextButtonControl::constructor_type TouchTextButtonControl::constructor_orig = nullptr;

void TouchTextButtonControl::constructor(
	TouchTextButtonControl* this_ptr,
	std::function<glm::vec2()> text_pos_getter,
	std::function<bool()> visible_condition,
	std::function<std::string()> text_getter,
	short p_s1,
	const ButtonColors* colors,
	int uv_x, int uv_y, int uv_width, int uv_height,
	bool p_b1,
	int p_i5)
{
	constructor_orig(
		this_ptr,
		std::move(text_pos_getter),
		std::move(visible_condition),
		std::move(text_getter),
		p_s1,
		colors,
		uv_x, uv_y, uv_width, uv_height,
		p_b1,
		p_i5
	);

	tools::vtable_setter setter
	{
		this_ptr->vtable,
		5
	};

	setter[2] = (void*)&TouchTextButtonControl::render;
}

void TouchTextButtonControl::render(TouchTextButtonControl* this_ptr, InputRenderContext* context)
{
	TouchGlyphButtonControl* base = (TouchGlyphButtonControl*)this_ptr;
	auto& visible_condition = base->get_visible_condition();
	if (not visible_condition or not visible_condition())
		return;

	auto& text_getter = this_ptr->get_text_getter();
	std::string text = text_getter ? text_getter() : "";

	auto& text_pos_getter = this_ptr->get_text_pos_getter();
	if (not text_pos_getter)
		throw std::bad_function_call{};

	glm::vec2 pos = text_pos_getter();

	auto& cached_pos_x = this_ptr->get_cached_pos_x();
	auto& cached_pos_y = this_ptr->get_cached_pos_y();
	auto& cached_text = this_ptr->get_cached_text();
	
	if (text != cached_text or cached_pos_x != pos.x or cached_pos_y != pos.y)
	{
		cached_pos_x = pos.x;
		cached_pos_y = pos.y;
		cached_text = text;

		this_ptr->get_measured_area() = context->measure_text_for_button_virtual({pos.x, pos.y}, text);
	}

	std::string display_text = text_getter();
	MinecraftInputRenderContext* ctx = (MinecraftInputRenderContext*)context;
	ctx->draw_image(
		"gui/newgui/classic-button.png",
		this_ptr->get_measured_area(),
		1, 1, 1, 1,
		{1, 1, 1, 1}
	);
	ctx->draw_text_centered_in_rect(display_text, this_ptr->get_measured_area(), {1, 1, 1, 1});
}

std::function<glm::vec2()>& TouchTextButtonControl::get_text_pos_getter() noexcept
{
	return *(std::function<glm::vec2()>*)((uintptr_t)this + 124);
}

std::function<std::string()>& TouchTextButtonControl::get_text_getter() noexcept
{
	return *(std::function<std::string()>*)((uintptr_t)this + 140);
}

std::string& TouchTextButtonControl::get_cached_text() noexcept
{
	return *(std::string*)((uintptr_t)this + 28);
}

float& TouchTextButtonControl::get_cached_pos_x() noexcept
{
	return *(float*)((uintptr_t)this + 156);
}

float& TouchTextButtonControl::get_cached_pos_y() noexcept
{
	return *(float*)((uintptr_t)this + 160);
}

RectangleArea& TouchTextButtonControl::get_measured_area() noexcept
{
	return *(RectangleArea*)((uintptr_t)this + 164);
}

void TouchTextButtonControl::install() noexcept
{
	//_ZN22TouchTextButtonControlC2ESt8functionIFN3glm6detail5tvec2IfEEvEES0_IFbvEES0_IFSsvEEsRK12ButtonColorsiiiibi
	void* constructor_target = minecraft_app::get_lib_thumb_function_ptr(0x2B2BAC);
	MSHook(constructor_target, constructor, constructor_orig);
}
