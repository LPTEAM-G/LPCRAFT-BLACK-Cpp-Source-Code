#pragma once

#include "minecraft_class/InputRenderContext.hpp"

class TouchControlSet
{
public:
	using render_type = int(*)(TouchControlSet*, InputRenderContext*);
	static render_type render_orig;
	static int render_impl(TouchControlSet* this_ptr, InputRenderContext* context);

	int render(InputRenderContext& context) noexcept;

	static void install() noexcept;
};
