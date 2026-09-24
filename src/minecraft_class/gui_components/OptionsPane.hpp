//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <memory>
#include <string>
#include <vector>

class OptionsPane
{
public:
	using vector_group = std::vector<std::shared_ptr<OptionsGroup>>;

	OptionsGroup* create_options_group(const std::string& i18n_key, bool flag) noexcept;
	vector_group& get_groups() noexcept;
};
