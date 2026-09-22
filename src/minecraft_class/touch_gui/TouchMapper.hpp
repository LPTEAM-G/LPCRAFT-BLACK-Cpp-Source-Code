#pragma once

#include "minecraft_class/InputRenderContext.hpp"
#include "minecraft_class/touch_gui/TouchControlSet.hpp"

class TouchMapper
{
public:
	using constructor_type = void(*)(TouchMapper*);
	static constructor_type constructor_orig;

	static void constructor(TouchMapper* this_ptr);
	static int render(TouchMapper* this_ptr, InputRenderContext* context) noexcept;
	TouchControlSet* get_control_set() noexcept;

	static void install() noexcept;
};
