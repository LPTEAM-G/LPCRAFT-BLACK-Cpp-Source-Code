//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/gui_components/OptionsItem.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include <memory>
#include <vector>

class OptionsGroup
{
private:
	static void add_option_item_impl(OptionsGroup* this_ptr, const Options::Option* option, MinecraftClient* mcc);	

public:
	using add_option_item_type = void(*)(OptionsGroup*, const Options::Option*, MinecraftClient*);
	static add_option_item_type add_option_item_orig;

	using vector_item = std::vector<std::shared_ptr<OptionsItem>>;

	OptionsItem* add_option_item(const Options::Option& option, MinecraftClient* mcc) noexcept;

	vector_item& get_items() noexcept;

	static void install() noexcept;
};

