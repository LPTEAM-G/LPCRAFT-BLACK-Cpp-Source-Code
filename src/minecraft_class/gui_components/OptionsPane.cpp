//Copyright (c) 2026 LPTEAM
#include "OptionsPane.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/gui_components/OptionsGroup.hpp"
#include <cstdint>
#include <string>

OptionsPane::create_options_group_type OptionsPane::create_options_group_orig = nullptr;

OptionsGroup* OptionsPane::create_options_group_impl(
	OptionsPane* this_ptr,
	const std::string* i18n_key,
	bool flag)
{
	return create_options_group_orig(this_ptr, i18n_key, flag);
}

OptionsGroup* OptionsPane::create_options_group(
	const std::string& i18n_key,
	bool flag) noexcept
{
	return create_options_group_impl(this, &i18n_key, flag);
}

OptionsPane::vector_group& OptionsPane::get_groups() noexcept
{
	return *(vector_group*)((uintptr_t)this + 48);
}

void OptionsPane::install() noexcept
{
	//_ZN11OptionsPane18createOptionsGroupERKSsb
	void* create_options_group_target = minecraft_app::get_lib_thumb_function_ptr(0x3238D0);
	MSHook(create_options_group_target, create_options_group_impl, create_options_group_orig);
}
