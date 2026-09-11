//Copyright (c) 2026 LPTEAM
#include "MinecraftClient.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class/AppPlatform_android.hpp"
#include <cstdint>
#include <string>

MinecraftClient* MinecraftClient::instance = nullptr;

MinecraftClient::constructor_type MinecraftClient::constructor_orig = nullptr;
MinecraftClient::tickInputType MinecraftClient::tickInputOrig = nullptr;

int MinecraftClient::get_screen_width() noexcept
{
	return *(int*)((uintptr_t)this + 80);
}

std::string& MinecraftClient::get_mcpe_dirname() noexcept
{
	return *(std::string*)((uintptr_t)this + 72);
}

std::string& MinecraftClient::get_worlds_dirname() noexcept
{
	return *(std::string*)((uintptr_t)this + 68);
}

std::string& MinecraftClient::get_final_worlds_dir_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 76);
}

void MinecraftClient::constructor(MinecraftClient* this_ptr, int i, char** p_p_c)
{
	constructor_orig(this_ptr, i, p_p_c);
	instance = this_ptr;
	instance->get_mcpe_dirname() = "data";
	instance->get_final_worlds_dir_path() =
		AppPlatform::get_instance_as_android_derived()->get_user_data_path() +
		"worlds";
}

int MinecraftClient::tick_input(MinecraftClient* this_ptr)
{
	return tickInputOrig(this_ptr);
}

void MinecraftClient::install() noexcept
{
	//_ZN15MinecraftClientC2EiPPc
	void* constructor_target = minecraft_app::get_lib_thumb_function_ptr(0x2F28A8);
	MSHook(constructor_target, constructor, constructor_orig);

	//_ZN15MinecraftClient9tickInputEv
	void* tick_input_target = minecraft_app::get_lib_thumb_function_ptr(0x3442FC);
	MSHook(tick_input_target, tick_input, tickInputOrig);
}
