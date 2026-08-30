//Copyright (c) 2026 LPTEAM
#include "AppPlatform.hpp"
#include "init.hpp"
#include <string>

std::string& AppPlatform::get_home_path() noexcept
{
	return *(std::string*)(minecraft_app::game_lib_base + 0x0075f23c);
}
