//Copyright (c) 2026 LPTEAM
#include "OptionsGroup.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include <cstdint>

OptionsGroup::add_option_item_type OptionsGroup::add_option_item_orig = nullptr;

void OptionsGroup::add_option_item_impl(OptionsGroup* this_ptr, const Options::Option* option, MinecraftClient* mcc)
{
	add_option_item_orig(this_ptr, option, mcc);
}

void OptionsGroup::add_option_item(const Options::Option& option, MinecraftClient* mcc) noexcept
{
	add_option_item_impl(this, &option, mcc);
}

OptionsGroup::vector_item& OptionsGroup::get_items() noexcept
{
	return *(vector_item*)((uintptr_t)this + 48);
}

void OptionsGroup::install() noexcept
{
	//_ZN12OptionsGroup13addOptionItemERKN7Options6OptionER15MinecraftClient
	void* add_option_item_target = minecraft_app::get_lib_thumb_function_ptr(0x328150);
	MSHook(add_option_item_target, add_option_item_impl, add_option_item_orig);
}
