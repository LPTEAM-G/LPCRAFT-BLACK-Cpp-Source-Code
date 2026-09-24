//Copyright (c) 2026 LPTEAM
#include "OptionsScreen.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Level.hpp"
#include "minecraft_class/Minecraft.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <cstdint>
#include <cstdio>
#include <string>
#include <utility>
#include "log_lib.hpp"

OptionsScreen::_generate_option_screens_default_type OptionsScreen::_generate_option_screens_default_orig = nullptr;

int OptionsScreen::_generate_option_screens_default(OptionsScreen* this_ptr)
{
	int result = _generate_option_screens_default_orig(this_ptr);

	auto& panes = this_ptr->get_panes();
	auto graphics_pane = panes[2];
	auto graphics_group = graphics_pane->get_groups()[0];
	auto gui_group = graphics_pane->create_options_group("options.group.gui", true);

	int gui_scale_index = 2;
	gui_group->get_items().push_back(std::move(graphics_group->get_items()[gui_scale_index]));
	graphics_group->get_items().erase(graphics_group->get_items().begin() + gui_scale_index);
	gui_group->add_option_item(
		Options::CENTERED_HUD,
		this_ptr->get_minecraft_client()
	);
	
	graphics_group->add_option_item(
		Options::BETTER_GRASS,
		this_ptr->get_minecraft_client()
	);

	std::swap(graphics_pane->get_groups()[1], graphics_pane->get_groups()[2]);
	std::swap(graphics_pane->get_groups()[0], graphics_pane->get_groups()[1]);

	return result;
}

MinecraftClient* OptionsScreen::get_minecraft_client() noexcept
{
	return *(MinecraftClient**)((uintptr_t)this + 20);
}

OptionsScreen::vector_panes& OptionsScreen::get_panes() noexcept
{
	return *(vector_panes*)((uintptr_t)this + 140);
}

void OptionsScreen::install() noexcept
{
	//_ZN13OptionsScreen29_generateOptionScreensDefaultEv
	void* _generate_option_screens_default_target = minecraft_app::get_lib_thumb_function_ptr(0x3F0C44);
	MSHook(
		_generate_option_screens_default_target,
		_generate_option_screens_default,
		_generate_option_screens_default_orig
	);
}
