//Copyright (c) 2026 LPTEAM
#include "AppPlatform.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform_android.hpp"
#include "tools/memory_page_guard.hpp"
#include <dlfcn.h>
#include <string>

std::string& AppPlatform::home_path() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<std::string>(0x75F23C);
}

AppPlatform* AppPlatform::get_instance_as_base() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<AppPlatform*>(0x75F238);
}

AppPlatform_android* AppPlatform::get_instance_as_android_derived() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<AppPlatform_android*>(0x75F238);
}

bool AppPlatform::use_centered_gui() noexcept
{
	return false;
}

void AppPlatform::change_game_home_path() noexcept
{
	std::string& path = home_path();
	path = "/minecraft-clients/lpcraft-black/";
}

void AppPlatform::install() noexcept
{
	void** table = (void**)dlsym(minecraft_app::game_lib_handler, "_ZTV19AppPlatform_android");
	tools::vtable_area_writable_guard guard{(void*)table, 2};
	table[60] = (void*)&use_centered_gui;
	change_game_home_path();
}
