//Copyright (c) 2026 LPTEAM
#include "TouchControlSet.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/render_context/MinecraftInputRenderContext.hpp"

int TouchControlSet::render(InputRenderContext& context) noexcept
{
	MinecraftInputRenderContext* ctx = (MinecraftInputRenderContext*)&context;
	ctx->draw_text_at_once("Hello", 0, 0, {1,1,1,1});
	ctx->draw_text_at_once("Fuck", 200, 300, {0,0,0,0.1});

	using render_type = int(*)(TouchControlSet*, InputRenderContext*);
	render_type render_orig = (render_type)minecraft_app::get_lib_thumb_function_ptr(0x2B3168);
	int result = render_orig(this, &context);
	
	return result;
}
