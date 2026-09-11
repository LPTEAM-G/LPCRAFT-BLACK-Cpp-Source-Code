//Copyright (c) 2026 LPTEAM
#include "AppPlatform.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform_android.hpp"
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

void AppPlatform::change_game_home_path() noexcept
{
	std::string& path = home_path();
	path = "/minecraft-clients/lpcraft-black/";
}

void AppPlatform::install() noexcept
{
	change_game_home_path();
}
