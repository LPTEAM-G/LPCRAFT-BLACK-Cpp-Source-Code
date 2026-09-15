//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSPANE_HPP
#define MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSPANE_HPP

#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <memory>
#include <vector>

class OptionsPane
{
public:
	using vector_group = std::vector<std::shared_ptr<OptionsGroup>>;

	vector_group& get_groups() noexcept;
};

#endif
