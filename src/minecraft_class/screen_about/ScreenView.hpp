//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/json_ui_components/VisualTree.hpp"
#include "minecraft_class/screen_about/ScreenContext.hpp"

class ScreenView
{
public:
	using render_type = void(*)(ScreenView*, ScreenContext*);
	static render_type render_orig;
	static void render_impl(ScreenView* this_ptr, ScreenContext* context);
	
	VisualTree* get_visual_tree() noexcept;

	static void install() noexcept;
};
