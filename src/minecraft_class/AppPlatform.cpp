//Copyright (c) 2026 LPTEAM
#include "AppPlatform.hpp"
#include "minecraft_app.hpp"
#include <string>

void AppPlatform::change_game_home_path() noexcept
{
	std::string& path = get_home_path();
	path = "/minecraft-clients/lpcraft-black/";
}

std::string& AppPlatform::get_home_path() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<std::string>(0x75F23C);
}

void AppPlatform::install() noexcept
{
	change_game_home_path();
}
