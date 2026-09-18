//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSPANE_HPP
#define MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSPANE_HPP

#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <memory>
#include <string>
#include <vector>

class OptionsPane
{
private:
	static OptionsGroup* create_options_group_impl(
		OptionsPane* this_ptr,
		const std::string* i18n_key,
		bool flag
	);
	
public:
	using create_options_group_type = OptionsGroup*(*)(OptionsPane*, const std::string*, bool);
	static create_options_group_type create_options_group_orig;
	
	using vector_group = std::vector<std::shared_ptr<OptionsGroup>>;

	OptionsGroup* create_options_group(const std::string& i18n_key, bool flag) noexcept;

	vector_group& get_groups() noexcept;

	static void install() noexcept;
};

#endif
