//Copyright (c) 2026 LPTEAM
#include "VisualTree.hpp"
#include "minecraft_class/json_ui_components/UIControl.hpp"
#include <memory>

UIControl* VisualTree::get_root_control() noexcept
{
	return ((std::shared_ptr<UIControl>*)this)->get();
}
