//Copyright (c) 2026 LPTEAM
#include "OptionsScreen.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <cstdint>

OptionsScreen::_generateOptionScreensDefaultType OptionsScreen::_generateOptionScreensDefaultOrig = nullptr;

int OptionsScreen::_generate_option_screens_default(OptionsScreen* this_ptr)
{
	int result = _generateOptionScreensDefaultOrig(this_ptr);
	auto& panes = this_ptr->get_panes();
	auto& graphics_pane = panes[2];
	auto& graphics_group = graphics_pane->get_groups()[0];
	OptionsGroup::add_option_item(graphics_group.get(), &Options::USE_CENTERED_GUI, this_ptr->get_minecraft_client());
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
	void* _generateOptionScreensDefaultTarget = minecraft_app::get_lib_thumb_function_ptr(0x3F0C44);
	MSHook(
		_generateOptionScreensDefaultTarget,
		_generate_option_screens_default,
		_generateOptionScreensDefaultOrig
	);
}
