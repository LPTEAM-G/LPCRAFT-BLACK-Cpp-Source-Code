#pragma once

#include "minecraft_class/InputHandler.hpp"
#include "minecraft_class/MinecraftClient.hpp"

class MinecraftInputHandler
{
public:
	using render_type = void(*)(MinecraftInputHandler*);
	static render_type render_orig;
	static void render_impl(MinecraftInputHandler* this_ptr);

	MinecraftClient* get_client() noexcept;
	InputHandler* get_input_handler() noexcept;

	static void install() noexcept;
};
