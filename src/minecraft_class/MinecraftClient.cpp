//Copyright (c) 2026 LPTEAM
#include "MinecraftClient.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"

MinecraftClient* MinecraftClient::instance = nullptr;

MinecraftClient::tickInputType MinecraftClient::tickInputOrig = nullptr;

int MinecraftClient::get_width() noexcept
{
	return *((int*)this + 20);
}

int MinecraftClient::tick_input(MinecraftClient* this_ptr)
{
	instance = this_ptr;
	return tickInputOrig(this_ptr);
}

void MinecraftClient::install() noexcept
{
	void* tick_input_target = minecraft_app::get_lib_thumb_function_ptr(0x3442FC);
	MSHook(tick_input_target, tick_input, tickInputOrig);
}
