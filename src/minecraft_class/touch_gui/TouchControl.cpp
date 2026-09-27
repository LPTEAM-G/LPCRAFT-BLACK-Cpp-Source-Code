//Copyright (c) 2026 LPTEAM
#include "TouchControl.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"

void TouchControl::render_virtual(InputRenderContext& context)
{
	using render_virtual_type = void(*)(TouchControl*, InputRenderContext*);
	render_virtual_type render_virtual_orig = (render_virtual_type)(vtable[2]);
	render_virtual_orig(this, &context);
}
