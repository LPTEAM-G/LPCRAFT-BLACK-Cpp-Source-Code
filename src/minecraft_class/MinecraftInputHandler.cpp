#include "MinecraftInputHandler.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/InputHandler.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"
#include "minecraft_class/render_context/MinecraftInputRenderContext.hpp"
#include <cstdint>

MinecraftInputHandler::render_type MinecraftInputHandler::render_orig = nullptr;

void MinecraftInputHandler::render_impl(MinecraftInputHandler* this_ptr)
{
	MinecraftInputRenderContext ctx{this_ptr->get_client()};
	this_ptr->get_input_handler()->render(*(InputRenderContext*)&ctx);
}

MinecraftClient* MinecraftInputHandler::get_client() noexcept
{
	return *(MinecraftClient**)((uintptr_t)this + 12);
}

InputHandler* MinecraftInputHandler::get_input_handler() noexcept
{
	return *(InputHandler**)((uintptr_t)this + 16);
}

void MinecraftInputHandler::install() noexcept
{
	//_ZN21MinecraftInputHandler6renderEv
	void* render_target = minecraft_app::get_lib_thumb_function_ptr(0x384E20);
	MSHook(render_target, render_impl, render_orig);
}
