//Copyright (c) 2026 LPTEAM
#include "TouchControlSet.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/render_context/MinecraftInputRenderContext.hpp"

int TouchControlSet::render(InputRenderContext& context) noexcept
{
	MinecraftInputRenderContext* ctx = (MinecraftInputRenderContext*)&context;
	ctx->draw_text("Hello", 0, 0, {1,1,1,1});
	ctx->draw_text("Fucking", 200, 400, {0,1,0,0.8});

	using render_type = int(*)(TouchControlSet*, InputRenderContext*);
	render_type render_orig = (render_type)minecraft_app::get_lib_thumb_function_ptr(0x2B3168);
	int result = render_orig(this, &context);
	
	return result;
}
