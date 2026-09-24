//Copyright (c) 2026 LPTEAM
#include "OptionsPane.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <cstdint>
#include <string>

OptionsGroup* OptionsPane::create_options_group(
	const std::string& i18n_key,
	bool flag) noexcept
{
	using create_options_group_type = OptionsGroup*(*)(OptionsPane*, const std::string*, bool);
	create_options_group_type create_options_group_orig = (create_options_group_type)minecraft_app::get_lib_thumb_function_ptr(0x3238D0);
	return create_options_group_orig(this, &i18n_key, flag);
}

OptionsPane::vector_group& OptionsPane::get_groups() noexcept
{
	return *(vector_group*)((uintptr_t)this + 48);
}
