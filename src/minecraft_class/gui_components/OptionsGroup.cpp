//Copyright (c) 2026 LPTEAM
#include "OptionsGroup.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/gui_components/OptionsItem.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include <cstdint>

OptionsItem* OptionsGroup::add_option_item(const Options::Option& option, MinecraftClient* mcc) noexcept
{
	using add_option_item_type = void(*)(OptionsGroup*, const Options::Option*, MinecraftClient*);
	add_option_item_type add_option_item_orig = (add_option_item_type)minecraft_app::get_lib_thumb_function_ptr(0x328150);

	add_option_item_orig(this, &option, mcc);
	vector_item& items = get_items();
	auto& item = items.back();
	return item.get();
}

OptionsGroup::vector_item& OptionsGroup::get_items() noexcept
{
	return *(vector_item*)((uintptr_t)this + 48);
}
