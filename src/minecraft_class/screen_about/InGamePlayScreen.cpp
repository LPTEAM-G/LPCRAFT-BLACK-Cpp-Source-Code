//Copyright (c) 2026 LPTEAM
#include "InGamePlayScreen.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include <dlfcn.h>

InGamePlayScreen::_initType InGamePlayScreen::_initOrig = nullptr;
InGamePlayScreen::_renderedFramedItemsType InGamePlayScreen::_renderedFramedItemsOrig = nullptr;

int InGamePlayScreen::_init(InGamePlayScreen* this_ptr, int i1, int i2)
{
	return _initOrig(this_ptr, i1, i2);
}

void InGamePlayScreen::_rendered_framed_items(InGamePlayScreen* this_ptr, Vec3 vec, Entity* entity, float tick)
{
	_renderedFramedItemsOrig(this_ptr, vec, entity, tick);
}

void InGamePlayScreen::install() noexcept
{
	//_ZN16InGamePlayScreen5_initEii
	void* _initTarget = minecraft_app::get_lib_thumb_function_ptr(0x3FFEC8);
	MSHook(_initTarget, _init, _initOrig);
	
	//_ZN16InGamePlayScreen20_renderedFramedItemsE4Vec3R13LevelRendererR6Entityf
	void* _renderedFramedItemsTarget = minecraft_app::get_lib_thumb_function_ptr(0x38D48C);
	MSHook(_renderedFramedItemsTarget, _rendered_framed_items, _renderedFramedItemsOrig);
}
