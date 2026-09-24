//Copyright (c) 2026 LPTEAM
#include "TouchMapper.hpp"
#include "minecraft_app.hpp"
#include "hook_macro.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/touch_gui/TouchControlSet.hpp"
#include "tools/vtable_setter.hpp"
#include <cstdint>

TouchMapper::constructor_type TouchMapper::constructor_orig = nullptr;

void TouchMapper::constructor(TouchMapper* this_ptr)
{
	constructor_orig(this_ptr);
	tools::vtable_setter vs{*(void**)this_ptr, 8};
	vs[7] = (void*)&TouchMapper::render;
}

int TouchMapper::render(TouchMapper* this_ptr, InputRenderContext* context) noexcept
{
	if (not MinecraftClient::pushed_screen_list.hud_screen)
		return 0;
	int result = this_ptr->get_control_set()->render(*context);
	return result;
}

TouchControlSet* TouchMapper::get_control_set() noexcept
{
	return *(TouchControlSet**)((uintptr_t)this + 12);
}

void TouchMapper::install() noexcept
{
	//_ZN11TouchMapperC2Ev
	void* constructor_target = minecraft_app::get_lib_thumb_function_ptr(0x2B3A34);
	MSHook(constructor_target, constructor, constructor_orig);
}
