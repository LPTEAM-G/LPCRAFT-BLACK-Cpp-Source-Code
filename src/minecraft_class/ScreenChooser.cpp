//Copyright (c) 2026 LPTEAM
#include "ScreenChooser.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"

ScreenChooser::pushHudScreenType ScreenChooser::pushHudScreenOrig = nullptr;

int ScreenChooser::push_hud_screen(ScreenChooser* this_ptr)
{
	return pushHudScreenOrig(this_ptr);
}

void ScreenChooser::install() noexcept
{
	//_ZN13ScreenChooser13pushHudScreenEv
	void* pushHudScreenTarget = minecraft_app::get_lib_thumb_function_ptr(0x3FFE10);
	MSHook(pushHudScreenTarget, push_hud_screen, pushHudScreenOrig);
}
