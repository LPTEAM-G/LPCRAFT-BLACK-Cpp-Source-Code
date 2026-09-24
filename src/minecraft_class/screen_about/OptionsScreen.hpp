//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/gui_components/OptionsPane.hpp"
#include <memory>
#include <vector>

class OptionsScreen
{
public:
	using vector_panes = std::vector<std::shared_ptr<OptionsPane>>;
	
	using _generate_option_screens_default_type = int(*)(OptionsScreen* this_ptr);
	static _generate_option_screens_default_type _generate_option_screens_default_orig;

	static int _generate_option_screens_default(OptionsScreen* this_ptr);

	MinecraftClient* get_minecraft_client() noexcept;
	vector_panes& get_panes() noexcept;

	static void install() noexcept;
};

