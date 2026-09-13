#include "OptionsGroup.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"

OptionsGroup::add_option_item_type OptionsGroup::add_option_item_orig = nullptr;

void OptionsGroup::add_option_item(OptionsGroup* this_ptr, const Options::Option* option, MinecraftClient* mcc)
{
	add_option_item_orig(this_ptr, option, mcc);
}

void OptionsGroup::install() noexcept
{
	//_ZN12OptionsGroup13addOptionItemERKN7Options6OptionER15MinecraftClient
	void* add_option_item_target = minecraft_app::get_lib_thumb_function_ptr(0x328150);
	MSHook(add_option_item_target, add_option_item, add_option_item_orig);
}
