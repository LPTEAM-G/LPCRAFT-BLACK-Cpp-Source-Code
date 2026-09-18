//Copyright (c) 2026 LPTEAM
#include "AppPlatform_android.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include "tools/vtable_setter.hpp"
#include <cstdint>
#include <string>

AppPlatform_android* AppPlatform_android::get_instance() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<AppPlatform_android*>(0x75F238);
}

std::string& AppPlatform_android::get_user_data_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 140);
}

bool AppPlatform_android::use_centered_gui(AppPlatform_android* this_ptr) noexcept
{
	return Options::opt_vars::gui::centered_hud;
}

void AppPlatform_android::install() noexcept
{
	auto* global_instance = get_instance();
	tools::vtable_setter setter
	{
		*(void**)global_instance,
		86
	};
	setter[59] = (void*)&use_centered_gui;
}
