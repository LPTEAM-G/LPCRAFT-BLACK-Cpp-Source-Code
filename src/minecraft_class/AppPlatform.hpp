//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_APPPLATFORM_HPP
#define MINECRAFT_CLASS_APPPLATFORM_HPP

#include <string>

class AppPlatform
{
private:
	static void change_game_home_path() noexcept;
	
public:
	static AppPlatform* get_instance() noexcept;
	static std::string& home_path() noexcept;
	static void install() noexcept;
};

#endif
