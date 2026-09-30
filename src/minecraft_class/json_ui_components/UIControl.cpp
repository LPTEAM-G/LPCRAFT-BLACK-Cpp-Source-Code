//Copyright (c) 2026 LPTEAM
#include "UIControl.hpp"
#include "minecraft_app.hpp"
#include <cstdint>
#include <string>

std::string& UIControl::get_name() noexcept
{
	return *(std::string*)((uintptr_t)this + 12);
}

void UIControl::set_visible(bool visible_flag) noexcept
{
	using set_visible_type = void(*)(UIControl*, bool);
	set_visible_type set_visible_orig = (set_visible_type)minecraft_app::get_lib_thumb_function_ptr(0x2ECE64);
	set_visible_orig(this, visible_flag);
}

UIControl::vector_controls& UIControl::get_children() noexcept
{
	return *(vector_controls*)((uintptr_t)this + 64);
}
