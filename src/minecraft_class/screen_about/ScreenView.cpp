//Copyright (c) 2026 LPTEAM
#include "ScreenView.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/GuiData.hpp"
#include "minecraft_class/json_ui_components/VisualTree.hpp"
#include <cstdint>
#include <string>
#include "hook_macro.hpp"
#include "minecraft_class/screen_about/AbstractScreen.hpp"
#include "minecraft_class/screen_about/ScreenContext.hpp"

ScreenView::render_type ScreenView::render_orig = nullptr;

void ScreenView::render_impl(ScreenView* this_ptr, ScreenContext* context)
{
	std::string screen_name = ((AbstractScreen*)this_ptr)->get_screen_name_virtual();
	if (screen_name == "start_screen")
	{
		//纯自定义行为
		//防止GUI缩放过大时导致布局异常
		//按需开启
		auto tree = this_ptr->get_visual_tree();
		auto root_control = tree->get_root_control();

		for (auto& control : root_control->get_children())
		{
			if (control->get_name() == "paper_doll_panel_ref")
			{
				if (GuiData::get_gui_scale() >= 4.0f)
					control->set_visible(false);
				else
					control->set_visible(true);
			}
		}
	}
	render_orig(this_ptr, context);
}

VisualTree* ScreenView::get_visual_tree() noexcept
{
	return *(VisualTree**)((uintptr_t)this + 80);
}

void ScreenView::install() noexcept
{
	//_ZN10ScreenView6renderER13ScreenContext
	void* render_target = minecraft_app::get_lib_thumb_function_ptr(0x41AB5C);
	MSHook(render_target, render_impl, render_orig);
}
