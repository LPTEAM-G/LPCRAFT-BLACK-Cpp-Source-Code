//Copyright (c) 2026 LPTEAM
#include "MinecraftClient.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform_android.hpp"
#include "minecraft_class/Font.hpp"
#include "minecraft_class/Minecraft.hpp"
#include <cstdint>
#include <cstdlib>
#include <string>

MinecraftClient* MinecraftClient::instance = nullptr;
MinecraftClient::pushed_screen_list_type MinecraftClient::pushed_screen_list;

MinecraftClient::constructor_type MinecraftClient::constructor_orig = nullptr;
MinecraftClient::_pop_screen_type MinecraftClient::_pop_screen_orig = nullptr;
MinecraftClient::push_screen_type MinecraftClient::push_screen_orig = nullptr;

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

Minecraft* MinecraftClient::get_server() noexcept
{
	return *(Minecraft**)((uintptr_t)this + 96);
}

Font* MinecraftClient::get_font() noexcept
{
	return *(Font**)((uintptr_t)this + 124);
}

MinecraftClient::vector_screen& MinecraftClient::get_screen_stack() noexcept
{
	return *(vector_screen*)((uintptr_t)this + 140);
}

void MinecraftClient::constructor(MinecraftClient* this_ptr, int i, char** p_p_c)
{
	constructor_orig(this_ptr, i, p_p_c);
	instance = this_ptr;
	instance->get_mcpe_dirname() = "data";
	instance->get_final_worlds_dir_path() =
		AppPlatform_android::get_instance()->get_user_data_path() +
		"worlds";
}

void MinecraftClient::push_screen_impl(
	MinecraftClient* this_ptr,
	std::shared_ptr<AbstractScreen> screen,
	bool immediate)
{
	std::string screen_name = screen->get_screen_name_virtual();
	if (screen_name == "hud_screen")
	{
		pushed_screen_list.hud_screen = true;
	}
	push_screen_orig(this_ptr, std::move(screen), immediate);
}

void MinecraftClient::_pop_screen_impl(MinecraftClient* this_ptr)
{
	std::string stack_top_screen_name =
			this_ptr->get_screen_stack()
			.back()->get_screen_name_virtual();
	if (stack_top_screen_name == "hud_screen")
	{
		pushed_screen_list.hud_screen = false;
	}
	_pop_screen_orig(this_ptr);
}

void MinecraftClient::install() noexcept
{
	//_ZN15MinecraftClientC2EiPPc
	void* constructor_target = minecraft_app::get_lib_thumb_function_ptr(0x2F28A8);
	MSHook(constructor_target, constructor, constructor_orig);

	//_ZN15MinecraftClient10pushScreenESt10shared_ptrI14AbstractScreenEb
	void* push_screen_target = minecraft_app::get_lib_thumb_function_ptr(0x330A30);
	MSHook(push_screen_target, push_screen_impl, push_screen_orig);

	//_ZN15MinecraftClient10_popScreenEv
	void* _pop_screen_target = minecraft_app::get_lib_thumb_function_ptr(0x2FD170);
	MSHook(_pop_screen_target, _pop_screen_impl, _pop_screen_orig);
}
